from __future__ import annotations

import json
from pathlib import Path

from snail.codex_loop import (
    DEFAULT_CODEX_ARGS,
    DEFAULT_GATE_PATH,
    DEFAULT_STATE_PATH,
    build_codex_command,
    build_prompt_input,
    build_parser,
    evaluate_gate,
    load_gate,
    load_state,
    normalize_codex_args,
    snapshot_artifacts,
    split_script_and_codex_args,
    write_state,
)


def test_normalize_codex_args_defaults_to_yolo_mode_gpt_5_4_and_xhigh() -> None:
    args = normalize_codex_args([])

    assert args == list(DEFAULT_CODEX_ARGS)
    assert "--dangerously-bypass-approvals-and-sandbox" in args
    assert ["-m", "gpt-5.4"] == args[1:3]
    assert 'model_reasoning_effort="xhigh"' in args


def test_normalize_codex_args_keeps_explicit_exec_args() -> None:
    assert normalize_codex_args(["--full-auto", "-m", "gpt-5-codex"]) == [
        "--full-auto",
        "-m",
        "gpt-5-codex",
    ]


def test_build_codex_command_uses_stdin_prompt_and_cd_path(tmp_path: Path) -> None:
    assert build_codex_command(
        codex_args=["--full-auto"],
        cd_path=tmp_path,
    ) == ["codex", "exec", "--full-auto", "-C", str(tmp_path), "-"]


def test_split_script_and_codex_args_uses_separator() -> None:
    script_args, codex_args = split_script_and_codex_args(
        ["--dry-run", "3", "--", "--full-auto", "-m", "gpt-5-codex"]
    )

    assert script_args == ["--dry-run", "3"]
    assert codex_args == ["--full-auto", "-m", "gpt-5-codex"]


def test_build_parser_accepts_script_flags_without_remainder_capture() -> None:
    parser = build_parser()
    args = parser.parse_args(["--dry-run", "3"])

    assert args.iterations == 3
    assert args.dry_run is True
    assert args.gate_file == DEFAULT_GATE_PATH
    assert args.state_file == DEFAULT_STATE_PATH


def test_load_gate_parses_supported_phase_and_classification(tmp_path: Path) -> None:
    gate_path = tmp_path / "gate.json"
    gate_path.write_text(
        json.dumps(
            {
                "phase": "replace",
                "classification": "static-closable",
                "focus": "outer bridge",
                "blocker": "Need one more saved-owner writer.",
                "required_artifacts": ["docs/re/windows-debugging-wants.md"],
                "packet_path": "analysis/runtime/windows-re-batch.md",
                "notes": "keep this narrow",
            }
        ),
        encoding="utf-8",
    )

    gate = load_gate(gate_path)

    assert gate.phase == "replace"
    assert gate.classification == "static-closable"
    assert gate.required_artifacts == ("docs/re/windows-debugging-wants.md",)


def test_evaluate_gate_blocks_runtime_blocked_targets(tmp_path: Path) -> None:
    artifact = tmp_path / "artifact.txt"
    artifact.write_text("ready\n", encoding="utf-8")
    gate = load_gate(
        _write_gate(
            tmp_path,
            phase="re",
            classification="runtime-blocked",
            required_artifacts=[artifact.name],
        )
    )

    decision = evaluate_gate(gate, previous_state=None, repo_root=tmp_path)

    assert decision.should_run is False
    assert "runtime-blocked" in decision.reason


def test_evaluate_gate_blocks_same_blocker_without_fresh_artifacts(tmp_path: Path) -> None:
    artifact = tmp_path / "artifact.txt"
    artifact.write_text("ready\n", encoding="utf-8")
    gate_path = _write_gate(
        tmp_path,
        phase="replace",
        classification="static-closable",
        required_artifacts=[artifact.name],
    )
    gate = load_gate(gate_path)
    state_path = tmp_path / "state.json"

    write_state(
        path=state_path,
        gate=gate,
        artifact_mtimes=snapshot_artifacts(tmp_path, gate.required_artifacts),
        status="executed",
        prompt_path=tmp_path / "LOOP.md",
        gate_path=gate_path,
    )
    previous_state = load_state(state_path)

    decision = evaluate_gate(gate, previous_state=previous_state, repo_root=tmp_path)

    assert decision.should_run is False
    assert "same unresolved blocker" in decision.reason


def test_evaluate_gate_allows_same_blocker_after_fresh_artifact(tmp_path: Path) -> None:
    artifact = tmp_path / "artifact.txt"
    artifact.write_text("ready\n", encoding="utf-8")
    gate_path = _write_gate(
        tmp_path,
        phase="replace",
        classification="static-closable",
        required_artifacts=[artifact.name],
    )
    gate = load_gate(gate_path)
    state_path = tmp_path / "state.json"

    write_state(
        path=state_path,
        gate=gate,
        artifact_mtimes=snapshot_artifacts(tmp_path, gate.required_artifacts),
        status="executed",
        prompt_path=tmp_path / "LOOP.md",
        gate_path=gate_path,
    )
    artifact.write_text("fresh\n", encoding="utf-8")
    previous_state = load_state(state_path)

    decision = evaluate_gate(gate, previous_state=previous_state, repo_root=tmp_path)

    assert decision.should_run is True
    assert decision.reason is None


def test_build_prompt_input_includes_gate_header(tmp_path: Path) -> None:
    gate = load_gate(
        _write_gate(
            tmp_path,
            phase="verify",
            classification="scaffold-removal",
            required_artifacts=["docs/re/windows-debugging-wants.md"],
        )
    )

    prompt = build_prompt_input("body", gate)

    assert "## Active Loop Gate" in prompt
    assert "classification: `scaffold-removal`" in prompt
    assert prompt.endswith("body")


def _write_gate(
    root: Path,
    *,
    phase: str,
    classification: str,
    required_artifacts: list[str],
) -> Path:
    gate_path = root / "gate.json"
    gate_path.write_text(
        json.dumps(
            {
                "phase": phase,
                "classification": classification,
                "focus": "focus",
                "blocker": "blocker",
                "required_artifacts": required_artifacts,
            }
        ),
        encoding="utf-8",
    )
    return gate_path
