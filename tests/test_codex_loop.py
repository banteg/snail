from __future__ import annotations

from pathlib import Path

from snail.codex_loop import (
    DEFAULT_CODEX_ARGS,
    build_codex_command,
    build_parser,
    normalize_codex_args,
    split_script_and_codex_args,
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
