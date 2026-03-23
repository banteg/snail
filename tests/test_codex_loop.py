from __future__ import annotations

import json
from pathlib import Path

from snail.codex_loop import (
    DEFAULT_CODEX_ARGS,
    DEFAULT_GATE_PATH,
    DEFAULT_NEXT_ACTION_PATH,
    DEFAULT_POLICY_PATH,
    DEFAULT_STATE_PATH,
    build_codex_command,
    build_prompt_input,
    build_parser,
    evaluate_gate,
    load_gate,
    load_state,
    normalize_codex_args,
    resolve_task_path,
    snapshot_artifacts,
    split_script_and_codex_args,
    write_next_action,
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
    assert args.policy_file == DEFAULT_POLICY_PATH
    assert args.prompt_file is None
    assert args.gate_file == DEFAULT_GATE_PATH
    assert args.state_file == DEFAULT_STATE_PATH
    assert args.next_action_file == DEFAULT_NEXT_ACTION_PATH


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
                "freshness_artifacts": ["docs/re/windows-debugging-wants.md"],
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
    assert gate.freshness_artifacts == ("docs/re/windows-debugging-wants.md",)


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
        artifact_signatures=snapshot_artifacts(tmp_path, gate.required_artifacts),
        status="executed",
        policy_path=tmp_path / "LOOP.md",
        task_path=tmp_path / "packet.md",
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
        artifact_signatures=snapshot_artifacts(tmp_path, gate.required_artifacts),
        status="executed",
        policy_path=tmp_path / "LOOP.md",
        task_path=tmp_path / "packet.md",
        gate_path=gate_path,
    )
    artifact.write_text("fresh\n", encoding="utf-8")
    previous_state = load_state(state_path)

    decision = evaluate_gate(gate, previous_state=previous_state, repo_root=tmp_path)

    assert decision.should_run is True
    assert decision.reason is None


def test_only_freshness_artifacts_can_unblock_repeated_blocker(tmp_path: Path) -> None:
    context = tmp_path / "context.txt"
    evidence = tmp_path / "evidence.txt"
    context.write_text("context\n", encoding="utf-8")
    evidence.write_text("evidence\n", encoding="utf-8")
    gate_path = _write_gate(
        tmp_path,
        phase="replace",
        classification="static-closable",
        required_artifacts=[context.name, evidence.name],
        freshness_artifacts=[evidence.name],
    )
    gate = load_gate(gate_path)
    state_path = tmp_path / "state.json"

    write_state(
        path=state_path,
        gate=gate,
        artifact_signatures=snapshot_artifacts(tmp_path, gate.required_artifacts),
        status="executed",
        policy_path=tmp_path / "LOOP.md",
        task_path=tmp_path / "packet.md",
        gate_path=gate_path,
    )
    context.write_text("context changed\n", encoding="utf-8")
    previous_state = load_state(state_path)

    blocked = evaluate_gate(gate, previous_state=previous_state, repo_root=tmp_path)

    assert blocked.should_run is False

    evidence.write_text("evidence changed\n", encoding="utf-8")
    previous_state = load_state(state_path)
    allowed = evaluate_gate(gate, previous_state=previous_state, repo_root=tmp_path)

    assert allowed.should_run is True


def test_build_prompt_input_includes_gate_header(tmp_path: Path) -> None:
    gate = load_gate(
        _write_gate(
            tmp_path,
            phase="verify",
            classification="scaffold-removal",
            required_artifacts=["docs/re/windows-debugging-wants.md"],
        )
    )

    task_path = tmp_path / "packet.md"
    prompt = build_prompt_input("policy", "body", gate, task_path)

    assert "## Active Loop Gate" in prompt
    assert "## Active Task Dossier" in prompt
    assert f"path: `{task_path}`" in prompt
    assert "## Loop Policy" in prompt
    assert "classification: `scaffold-removal`" in prompt
    assert "If it conflicts with anything below, the gate wins." in prompt
    assert prompt.endswith("policy")


def test_resolve_task_path_defaults_to_gate_packet(tmp_path: Path) -> None:
    packet = tmp_path / "packet.md"
    packet.write_text("packet\n", encoding="utf-8")
    gate = load_gate(
        _write_gate(
            tmp_path,
            phase="re",
            classification="runtime-blocked",
            required_artifacts=[packet.name],
            packet_path=packet.name,
        )
    )

    resolved = resolve_task_path(tmp_path, override_path=None, gate=gate)

    assert resolved == packet.resolve()


def test_write_next_action_mentions_policy_and_task_paths(tmp_path: Path) -> None:
    packet = tmp_path / "packet.md"
    packet.write_text("packet\n", encoding="utf-8")
    gate = load_gate(
        _write_gate(
            tmp_path,
            phase="re",
            classification="runtime-blocked",
            required_artifacts=[packet.name],
            packet_path=packet.name,
        )
    )
    next_action = tmp_path / "next-action.md"
    policy_path = tmp_path / "LOOP.md"
    policy_path.write_text("policy\n", encoding="utf-8")

    write_next_action(
        path=next_action,
        gate=gate,
        gate_path=tmp_path / "gate.json",
        policy_path=policy_path,
        task_path=packet,
        reason="blocked",
    )

    text = next_action.read_text(encoding="utf-8")
    assert f"- policy: `{policy_path}`" in text
    assert f"- task dossier: `{packet}`" in text
    assert "- stop reason: blocked" in text


def _write_gate(
    root: Path,
    *,
    phase: str,
    classification: str,
    required_artifacts: list[str],
    freshness_artifacts: list[str] | None = None,
    packet_path: str | None = None,
) -> Path:
    gate_path = root / "gate.json"
    payload = {
        "phase": phase,
        "classification": classification,
        "focus": "focus",
        "blocker": "blocker",
        "required_artifacts": required_artifacts,
    }
    if freshness_artifacts is not None:
        payload["freshness_artifacts"] = freshness_artifacts
    if packet_path is not None:
        payload["packet_path"] = packet_path
    gate_path.write_text(
        json.dumps(payload),
        encoding="utf-8",
    )
    return gate_path
