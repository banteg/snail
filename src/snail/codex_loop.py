from __future__ import annotations

import argparse
from dataclasses import dataclass
from datetime import UTC, datetime
import hashlib
import json
from pathlib import Path
import shlex
import subprocess
import sys
import time
from typing import Sequence

DEFAULT_PROMPT_PATH = Path("LOOP.md")
DEFAULT_GATE_PATH = Path("analysis/runtime/codex-loop-gate.json")
DEFAULT_STATE_PATH = Path("artifacts/codex-loop/state.json")
DEFAULT_NEXT_ACTION_PATH = Path("artifacts/codex-loop/next-action.md")
DEFAULT_CODEX_ARGS = (
    "--dangerously-bypass-approvals-and-sandbox",
    "-m",
    "gpt-5.4",
    "-c",
    'model_reasoning_effort="xhigh"',
)
LOOP_BLOCKED_EXIT_CODE = 2
SUPPORTED_PHASES = frozenset({"re", "replace", "verify"})
SUPPORTED_CLASSIFICATIONS = frozenset(
    {"static-closable", "runtime-blocked", "scaffold-removal"}
)


@dataclass(frozen=True)
class LoopGate:
    phase: str
    classification: str
    focus: str
    blocker: str
    required_artifacts: tuple[str, ...]
    freshness_artifacts: tuple[str, ...]
    packet_path: str | None = None
    notes: str | None = None


@dataclass(frozen=True)
class LoopState:
    phase: str
    classification: str
    focus: str
    blocker: str
    artifact_signatures: dict[str, str | None]
    status: str


@dataclass(frozen=True)
class LoopDecision:
    should_run: bool
    reason: str | None
    artifact_signatures: dict[str, str | None]


def split_script_and_codex_args(argv: Sequence[str]) -> tuple[list[str], list[str]]:
    parts = list(argv)
    try:
        separator_index = parts.index("--")
    except ValueError:
        return parts, []
    return parts[:separator_index], parts[separator_index + 1 :]


def positive_int(value: str) -> int:
    parsed = int(value)
    if parsed < 1:
        raise argparse.ArgumentTypeError("iterations must be >= 1")
    return parsed


def nonnegative_float(value: str) -> float:
    parsed = float(value)
    if parsed < 0:
        raise argparse.ArgumentTypeError("delay must be >= 0")
    return parsed


def normalize_codex_args(codex_args: Sequence[str]) -> list[str]:
    if codex_args:
        return list(codex_args)
    return list(DEFAULT_CODEX_ARGS)


def load_json_file(path: Path) -> object:
    return json.loads(path.read_text(encoding="utf-8"))


def _require_string(data: dict[str, object], key: str, *, path: Path) -> str:
    value = data.get(key)
    if not isinstance(value, str) or not value.strip():
        raise ValueError(f"{path}: expected a non-empty string for {key!r}")
    return value


def _require_string_list(data: dict[str, object], key: str, *, path: Path) -> tuple[str, ...]:
    value = data.get(key)
    if not isinstance(value, list) or not value:
        raise ValueError(f"{path}: expected a non-empty list for {key!r}")
    parsed: list[str] = []
    for item in value:
        if not isinstance(item, str) or not item.strip():
            raise ValueError(f"{path}: expected only non-empty strings in {key!r}")
        parsed.append(item)
    return tuple(parsed)


def load_gate(path: Path) -> LoopGate:
    if not path.is_file():
        raise FileNotFoundError(path)

    data = load_json_file(path)
    if not isinstance(data, dict):
        raise ValueError(f"{path}: expected a JSON object")

    phase = _require_string(data, "phase", path=path)
    if phase not in SUPPORTED_PHASES:
        raise ValueError(f"{path}: unsupported phase {phase!r}")

    classification = _require_string(data, "classification", path=path)
    if classification not in SUPPORTED_CLASSIFICATIONS:
        raise ValueError(f"{path}: unsupported classification {classification!r}")

    packet_path = data.get("packet_path")
    if packet_path is not None and not isinstance(packet_path, str):
        raise ValueError(f"{path}: expected 'packet_path' to be a string when present")

    notes = data.get("notes")
    if notes is not None and not isinstance(notes, str):
        raise ValueError(f"{path}: expected 'notes' to be a string when present")

    required_artifacts = _require_string_list(data, "required_artifacts", path=path)
    freshness_artifacts = data.get("freshness_artifacts")
    if freshness_artifacts is None:
        parsed_freshness = required_artifacts
    else:
        if not isinstance(freshness_artifacts, list) or not freshness_artifacts:
            raise ValueError(f"{path}: expected 'freshness_artifacts' to be a non-empty list")
        parsed_freshness_list: list[str] = []
        required_set = set(required_artifacts)
        for item in freshness_artifacts:
            if not isinstance(item, str) or not item.strip():
                raise ValueError(
                    f"{path}: expected only non-empty strings in 'freshness_artifacts'"
                )
            if item not in required_set:
                raise ValueError(
                    f"{path}: freshness artifact {item!r} must also appear in 'required_artifacts'"
                )
            parsed_freshness_list.append(item)
        parsed_freshness = tuple(parsed_freshness_list)

    return LoopGate(
        phase=phase,
        classification=classification,
        focus=_require_string(data, "focus", path=path),
        blocker=_require_string(data, "blocker", path=path),
        required_artifacts=required_artifacts,
        freshness_artifacts=parsed_freshness,
        packet_path=packet_path,
        notes=notes,
    )


def load_state(path: Path) -> LoopState | None:
    if not path.is_file():
        return None

    data = load_json_file(path)
    if not isinstance(data, dict):
        raise ValueError(f"{path}: expected a JSON object")

    artifact_signatures = data.get("artifact_signatures", data.get("artifact_mtimes"))
    if not isinstance(artifact_signatures, dict):
        raise ValueError(
            f"{path}: expected 'artifact_signatures' (or legacy 'artifact_mtimes') to be a JSON object"
        )

    parsed_signatures: dict[str, str | None] = {}
    for key, value in artifact_signatures.items():
        if not isinstance(key, str):
            raise ValueError(f"{path}: expected string keys in artifact signature data")
        if value is not None and not isinstance(value, (int, str)):
            raise ValueError(f"{path}: expected string, int, or null values in artifact signature data")
        parsed_signatures[key] = None if value is None else str(value)

    return LoopState(
        phase=_require_string(data, "phase", path=path),
        classification=_require_string(data, "classification", path=path),
        focus=_require_string(data, "focus", path=path),
        blocker=_require_string(data, "blocker", path=path),
        artifact_signatures=parsed_signatures,
        status=_require_string(data, "status", path=path),
    )


def resolve_repo_path(repo_root: Path, raw_path: str) -> Path:
    path = Path(raw_path)
    return path if path.is_absolute() else repo_root / path


def resolve_cli_path(repo_root: Path, raw_path: Path) -> Path:
    return raw_path if raw_path.is_absolute() else (repo_root / raw_path).resolve()


def hash_file(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def snapshot_artifacts(repo_root: Path, required_artifacts: Sequence[str]) -> dict[str, str | None]:
    artifact_signatures: dict[str, str | None] = {}
    for artifact in required_artifacts:
        resolved = resolve_repo_path(repo_root, artifact)
        artifact_signatures[artifact] = hash_file(resolved) if resolved.exists() else None
    return artifact_signatures


def artifacts_are_fresh(
    current: dict[str, str | None], previous: dict[str, str | None] | None, freshness_artifacts: Sequence[str]
) -> bool:
    if any(current.get(path) is None for path in freshness_artifacts):
        return False
    if previous is None:
        return True
    return any(previous.get(path) != current.get(path) for path in freshness_artifacts)


def evaluate_gate(gate: LoopGate, previous_state: LoopState | None, repo_root: Path) -> LoopDecision:
    artifact_signatures = snapshot_artifacts(repo_root, gate.required_artifacts)
    missing = [path for path, signature in artifact_signatures.items() if signature is None]
    if missing:
        missing_list = ", ".join(missing)
        return LoopDecision(
            should_run=False,
            reason=f"missing required evidence artifacts: {missing_list}",
            artifact_signatures=artifact_signatures,
        )

    previous_artifacts = previous_state.artifact_signatures if previous_state is not None else None
    fresh_artifacts = artifacts_are_fresh(
        artifact_signatures,
        previous_artifacts,
        gate.freshness_artifacts,
    )
    same_blocker = (
        previous_state is not None
        and previous_state.phase == gate.phase
        and previous_state.classification == gate.classification
        and previous_state.blocker == gate.blocker
    )

    if gate.classification == "runtime-blocked":
        packet_hint = f" Update {gate.packet_path} before rerunning." if gate.packet_path else ""
        return LoopDecision(
            should_run=False,
            reason=f"gate is runtime-blocked: {gate.blocker}.{packet_hint}",
            artifact_signatures=artifact_signatures,
        )

    if previous_state is not None and not fresh_artifacts:
        if same_blocker:
            return LoopDecision(
                should_run=False,
                reason="same unresolved blocker as the previous run and no fresh BN/IDA/Frida artifact was detected",
                artifact_signatures=artifact_signatures,
            )
        return LoopDecision(
            should_run=False,
            reason="no fresh BN/IDA/Frida artifact was detected for the current question",
            artifact_signatures=artifact_signatures,
        )

    return LoopDecision(should_run=True, reason=None, artifact_signatures=artifact_signatures)


def write_state(
    *,
    path: Path,
    gate: LoopGate,
    artifact_signatures: dict[str, str | None],
    status: str,
    prompt_path: Path,
    gate_path: Path,
    stop_reason: str | None = None,
) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    payload = {
        "updated_at": datetime.now(UTC).isoformat(),
        "phase": gate.phase,
        "classification": gate.classification,
        "focus": gate.focus,
        "blocker": gate.blocker,
        "artifact_signatures": artifact_signatures,
        "status": status,
        "prompt_path": str(prompt_path),
        "gate_path": str(gate_path),
        "stop_reason": stop_reason,
    }
    path.write_text(json.dumps(payload, indent=2, sort_keys=True) + "\n", encoding="utf-8")


def write_next_action(
    *,
    path: Path,
    gate: LoopGate,
    gate_path: Path,
    prompt_path: Path,
    reason: str,
) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    packet_line = f"- packet: `{gate.packet_path}`\n" if gate.packet_path is not None else ""
    notes_line = f"- notes: {gate.notes}\n" if gate.notes is not None else ""
    evidence_lines = "\n".join(f"- `{artifact}`" for artifact in gate.required_artifacts)
    freshness_lines = "\n".join(f"- `{artifact}`" for artifact in gate.freshness_artifacts)
    text = (
        "# Codex Loop Next Action\n\n"
        f"- updated: {datetime.now(UTC).isoformat()}\n"
        f"- prompt: `{prompt_path}`\n"
        f"- gate: `{gate_path}`\n"
        f"- phase: `{gate.phase}`\n"
        f"- classification: `{gate.classification}`\n"
        f"- focus: {gate.focus}\n"
        f"- blocker: {gate.blocker}\n"
        f"{packet_line}"
        f"{notes_line}"
        f"- stop reason: {reason}\n\n"
        "Required artifacts:\n"
        f"{evidence_lines}\n\n"
        "Freshness artifacts that must materially change before rerun:\n"
        f"{freshness_lines}\n"
    )
    path.write_text(text, encoding="utf-8")


def build_prompt_input(prompt_text: str, gate: LoopGate) -> str:
    artifact_lines = "\n".join(f"- `{artifact}`" for artifact in gate.required_artifacts)
    freshness_lines = "\n".join(f"- `{artifact}`" for artifact in gate.freshness_artifacts)
    packet_line = f"- packet: `{gate.packet_path}`\n" if gate.packet_path is not None else ""
    notes_line = f"- notes: {gate.notes}\n" if gate.notes is not None else ""
    header = (
        "## Active Loop Gate\n"
        f"- phase: `{gate.phase}`\n"
        f"- classification: `{gate.classification}`\n"
        f"- focus: {gate.focus}\n"
        f"- blocker: {gate.blocker}\n"
        f"{packet_line}"
        f"{notes_line}"
        "Required evidence artifacts:\n"
        f"{artifact_lines}\n\n"
        "Freshness artifacts:\n"
        f"{freshness_lines}\n\n"
        "Treat this gate as authoritative. If it conflicts with anything below, the gate wins. "
        "`runtime-blocked` means no Zig edits and no broad ledger churn; "
        "prepare or update only the focused RE packet. `static-closable` means code is allowed only when "
        "writer, consumer, guard, and lifetime are already known. `scaffold-removal` means delete or isolate "
        "fake behavior without introducing a new proxy.\n\n"
    )
    return header + prompt_text


def build_codex_command(*, codex_args: Sequence[str], cd_path: Path | None) -> list[str]:
    command = ["codex", "exec", *codex_args]
    if cd_path is not None:
        command.extend(["-C", str(cd_path)])
    command.append("-")
    return command


def run_iterations(
    *,
    iterations: int,
    prompt_path: Path,
    gate_path: Path,
    state_path: Path,
    next_action_path: Path,
    codex_args: Sequence[str],
    cd_path: Path | None,
    continue_on_error: bool,
    delay_seconds: float,
    dry_run: bool,
) -> int:
    command = build_codex_command(codex_args=codex_args, cd_path=cd_path)
    failures: list[tuple[int, int]] = []
    repo_root = cd_path if cd_path is not None else Path.cwd()

    for iteration in range(1, iterations + 1):
        gate = load_gate(gate_path)
        previous_state = load_state(state_path)
        decision = evaluate_gate(gate, previous_state, repo_root)
        prompt_text = prompt_path.read_text(encoding="utf-8")
        print(f"==> Iteration {iteration}/{iterations}", flush=True)
        print(f"    Prompt: {prompt_path}", flush=True)
        print(f"    Gate: {gate_path}", flush=True)
        print(f"    Phase: {gate.phase}", flush=True)
        print(f"    Classification: {gate.classification}", flush=True)
        print(f"    Focus: {gate.focus}", flush=True)
        print(f"    Command: {shlex.join(command)}", flush=True)

        if not decision.should_run:
            print(f"Blocked: {decision.reason}", file=sys.stderr, flush=True)
            if gate.packet_path is not None:
                print(f"Packet: {gate.packet_path}", file=sys.stderr, flush=True)
            print(f"Next action: {next_action_path}", file=sys.stderr, flush=True)
            write_next_action(
                path=next_action_path,
                gate=gate,
                gate_path=gate_path,
                prompt_path=prompt_path,
                reason=decision.reason or "blocked",
            )
            if dry_run:
                return 0
            if not dry_run:
                write_state(
                    path=state_path,
                    gate=gate,
                    artifact_signatures=decision.artifact_signatures,
                    status="blocked",
                    prompt_path=prompt_path,
                    gate_path=gate_path,
                    stop_reason=decision.reason,
                )
                return LOOP_BLOCKED_EXIT_CODE
            continue

        if dry_run:
            continue

        completed = subprocess.run(
            command,
            input=build_prompt_input(prompt_text, gate),
            text=True,
            check=False,
        )
        current_artifacts = snapshot_artifacts(repo_root, gate.required_artifacts)
        write_next_action(
            path=next_action_path,
            gate=gate,
            gate_path=gate_path,
            prompt_path=prompt_path,
            reason="loop executed; update the gate before the next batch if the blocker changed",
        )
        write_state(
            path=state_path,
            gate=gate,
            artifact_signatures=current_artifacts,
            status="failed" if completed.returncode != 0 else "executed",
            prompt_path=prompt_path,
            gate_path=gate_path,
            stop_reason=None if completed.returncode == 0 else f"codex exited {completed.returncode}",
        )
        if completed.returncode != 0:
            failures.append((iteration, completed.returncode))
            print(
                f"Iteration {iteration} failed with exit code {completed.returncode}.",
                file=sys.stderr,
                flush=True,
            )
            if not continue_on_error:
                break

        if delay_seconds > 0 and iteration < iterations:
            time.sleep(delay_seconds)

    if dry_run:
        return 0
    if not failures:
        return 0

    summary = ", ".join(
        f"iteration {iteration} -> exit {returncode}" for iteration, returncode in failures
    )
    print(f"Failures: {summary}", file=sys.stderr, flush=True)
    return failures[-1][1]


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description="Run `codex exec` against a prompt file for N iterations.",
        epilog=(
            "Default exec args are yolo mode plus `-m gpt-5.4` and "
            "`-c 'model_reasoning_effort=\"xhigh\"'`. "
            "Pass explicit exec args after `--` to override them, for example: "
            "`uv run tools/codex_loop.py --dry-run 5 -- --full-auto -m gpt-5.4`."
        ),
    )
    parser.add_argument("iterations", type=positive_int, help="How many times to run `codex exec`.")
    parser.add_argument(
        "--prompt-file",
        type=Path,
        default=DEFAULT_PROMPT_PATH,
        help="Prompt file to feed to Codex on each iteration (default: LOOP.md).",
    )
    parser.add_argument(
        "--gate-file",
        type=Path,
        default=DEFAULT_GATE_PATH,
        help="JSON gate file that classifies the current phase and blocker.",
    )
    parser.add_argument(
        "--state-file",
        type=Path,
        default=DEFAULT_STATE_PATH,
        help="JSON state file used to detect repeated blockers and stale evidence.",
    )
    parser.add_argument(
        "--next-action-file",
        type=Path,
        default=DEFAULT_NEXT_ACTION_PATH,
        help="Markdown handoff file written when the loop is blocked or completes a batch.",
    )
    parser.add_argument(
        "--cd",
        type=Path,
        default=Path.cwd(),
        help="Working tree passed to `codex exec -C` (default: current directory).",
    )
    parser.add_argument(
        "--continue-on-error",
        action="store_true",
        help="Keep going even if one iteration exits non-zero.",
    )
    parser.add_argument(
        "--delay-seconds",
        type=nonnegative_float,
        default=0.0,
        help="Optional delay between iterations.",
    )
    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="Print the commands that would be run without executing them.",
    )
    return parser


def main(argv: Sequence[str] | None = None) -> int:
    parser = build_parser()
    script_args, codex_args = split_script_and_codex_args(sys.argv[1:] if argv is None else argv)
    args = parser.parse_args(script_args)

    cd_path = args.cd.resolve() if args.cd is not None else Path.cwd()
    prompt_path = resolve_cli_path(cd_path, args.prompt_file)
    if not prompt_path.is_file():
        parser.error(f"prompt file does not exist: {prompt_path}")

    gate_path = resolve_cli_path(cd_path, args.gate_file)
    if not gate_path.is_file():
        parser.error(f"gate file does not exist: {gate_path}")

    state_path = resolve_cli_path(cd_path, args.state_file)
    next_action_path = resolve_cli_path(cd_path, args.next_action_file)
    codex_args = normalize_codex_args(codex_args)

    return run_iterations(
        iterations=args.iterations,
        prompt_path=prompt_path,
        gate_path=gate_path,
        state_path=state_path,
        next_action_path=next_action_path,
        codex_args=codex_args,
        cd_path=cd_path,
        continue_on_error=args.continue_on_error,
        delay_seconds=args.delay_seconds,
        dry_run=args.dry_run,
    )


if __name__ == "__main__":
    raise SystemExit(main())
