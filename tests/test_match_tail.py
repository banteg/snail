"""Post-return extent diagnostics must never discard target code."""

from pathlib import Path

import pytest

from snail import cli
from snail import match as m

# Native 0x411960..0x411999: two guarded COM Release calls and field clears.
RELEASE_BODY = bytes.fromhex(
    "568bf18b8694bb000085c074108b0850ff5108c78694bb000000000000"
    "8b8690bb000085c074108b1050ff5208c78690bb0000000000005ec3"
)
# Alignment, a separate jump thunk at 0x4119a0, and its return at 0x4119b0.
RELEASE_SUFFIX = b"\x90" * 7 + bytes.fromhex("e90b000000") + b"\x90" * 11 + b"\xc3" + b"\x90" * 15


def compare(target, candidate):
    return m.match_function(
        target,
        m.ObjectFunction("test", candidate, frozenset()),
        image=m.LoadedImage(b"", 0x400000, 0x10000),
        target_va=0x411960,
    )


def test_native_release_extent_preserves_neighboring_stubs_until_explicitly_bounded():
    overlong = compare(RELEASE_BODY + RELEASE_SUFFIX, RELEASE_BODY)
    assert overlong.target_instruction_count == 38
    assert overlong.candidate_instruction_count == overlong.instruction_prefix_count == 18
    payload = m.match_result_payload(overlong)
    tail = payload["post_return_target_tail"]
    assert tail["return_end_address"] == 0x411999
    assert tail["return_end_offset"] == 57
    assert tail["target_tail_end_address"] == 0x4119B1
    assert tail["target_tail_end_offset"] == 81
    assert tail["target_tail_instructions"] == 20
    assert "missing cold code" in tail["caveat"]
    assert not payload["exact"]
    assert not payload["body_byte_exact"]
    assert payload["compared_target_ranges"] == [[0, 81]]
    assert payload["excluded_target_ranges"] == [[81, 96, "terminal-padding"]]

    root = Path(__file__).resolve().parents[1]
    config = m.load_scratch_config(
        root / "tools/match/scratches/release_direct3d_device_interfaces"
    )
    assert config.end_va == 0x411960 + len(RELEASE_BODY)
    bounded = compare(RELEASE_BODY, RELEASE_BODY)
    assert bounded.exact and bounded.body_byte_exact
    assert m.match_result_payload(bounded)["post_return_target_tail"] is None
    assert bounded.compared_target_ranges == ((0, 57),)


@pytest.mark.parametrize("target,candidate", [
    ("c39090", "c3"),  # Ordinary padding is already classified.
    ("90c3", "90"),  # A truncated candidate has no return.
    ("40c3c3", "48c3"),  # The candidate is not an exact prefix.
    ("c3", ""),
])
def test_tail_diagnostic_requires_complete_returning_prefix(target, candidate):
    result = compare(bytes.fromhex(target), bytes.fromhex(candidate))
    assert m.post_return_target_tail_payload(result) is None


def test_cold_code_after_an_early_return_remains_part_of_the_comparison():
    # An ordinary function can branch over a return into a later cold block.
    result = compare(bytes.fromhex("85c07401c331c0c3"), bytes.fromhex("85c07401c3"))
    assert not result.exact
    assert result.compared_target_ranges == ((0, 8),)
    assert result.excluded_target_ranges == ()
    m.match_result_payload(result)
    assert not result.exact
    assert result.target_lines[-2:] == ("xor eax, eax", "ret")


@pytest.mark.parametrize("json_output", [False, True])
def test_inspect_exposes_tail_review_without_changing_the_match(
    tmp_path, monkeypatch, capsys, json_output,
):
    result = compare(RELEASE_BODY + RELEASE_SUFFIX, RELEASE_BODY)
    monkeypatch.setattr(cli, "run_scratch_match", lambda **kwargs: result)
    (tmp_path / "scratch.conf").write_text("FUNCTION=release_direct3d_device_interfaces\n")
    args = ["match", "inspect", str(tmp_path)]
    if json_output:
        args.append("--json")
    assert cli.main(args) == 0
    output = capsys.readouterr().out
    if json_output:
        import json

        payload = json.loads(output)
        assert payload["post_return_target_tail"]["return_end_address"] == 0x411999
        assert not payload["exact"]
    else:
        assert "target-tail: after matching return 0x00411999..0x004119b1" in output
        assert "No target bytes have been excluded" in output
