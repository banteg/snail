"""SIB diagnostics use only paired instructions and never grant proof credit."""

import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).parents[1] / "tools/match/c2"))
import sib_diff

from snail import match as m


def compare(left, right):
    target, candidate = bytes.fromhex(left), bytes.fromhex(right)
    match = m.match_function(
        target, m.ObjectFunction("f", candidate, frozenset()),
        image=m.LoadedImage(b"", 0x400000, 0x10000), target_va=0x401000,
    )
    return match, sib_diff.compare(match, target, candidate)


def test_partial_swap_after_an_insertion_reports_both_offsets():
    # mov eax,[ecx+edx] / mov eax,[edx+ecx], preceded by an extra push in the candidate.
    result, diagnostic = compare("56 8b0411 c3", "56 57 8b040a c3")
    assert result.ratio < 1 and result.encoded_body_differences == ()
    assert result.encoded_body_proof is None
    row, = diagnostic["differences"]
    assert row["swapped"]
    assert (row["target_offset"], row["candidate_offset"]) == (1, 2)
    assert (row["target_sib_offset"], row["candidate_sib_offset"]) == (3, 4)
    alignment = diagnostic["alignment"]
    assert alignment["aligned_instructions"] == 3
    assert alignment["unaligned_candidate_instructions"] == 1
    assert alignment["unaligned_target_instructions"] == 0


@pytest.mark.parametrize("reverse", [False, True])
def test_extra_normalized_duplicate_does_not_manufacture_a_swap(reverse):
    # In the first run either of two loads could be the insertion. After
    # inc eax, context identifies the one remaining load on each side.
    left = "56 8b0411 40 8b0411 c3"
    right = "56 8b040a 8b0411 40 8b040a c3"
    _, diagnostic = compare(right, left) if reverse else compare(left, right)
    row, = diagnostic["differences"]
    assert (row["target_offset"], row["candidate_offset"]) == ((8, 5) if reverse else (5, 8))
    assert diagnostic["alignment"]["ambiguous_alignment_ranks"] == 1


def test_equal_length_alignments_can_choose_different_subsequences():
    # Both AB and BA are optimal. Embedding only the subsequence selected
    # by SequenceMatcher would make its pairings look unique.
    assert sib_diff.unambiguous_pairs("ABAC", "BABC") == ([(3, 3)], 2)


@pytest.mark.parametrize(("left", "right"), [
    ("8b0411 c3", "8b0411 c3"),     # identical SIB
    ("8b0451 c3", "8b044a c3"),     # reversing registers at scale two changes the address
    ("8b0411 c3", "8d040a c3"),     # mov/lea do not align
    ("8b0424 c3", "8b0424 c3"),     # SIB with no index
    ("8b0409 c3", "8b0409 c3"),     # same base and index
])
def test_no_swap_outside_equal_normalized_scale_one_operands(left, right):
    _, diagnostic = compare(left, right)
    assert diagnostic["differences"] == []


@pytest.mark.parametrize("marker", ["dd L12", "db.lookup 02", "db 8b"])
def test_data_and_unknown_bytes_do_not_decode_as_swaps(marker):
    target, candidate = bytes.fromhex("8b0411"), bytes.fromhex("8b040a")
    line = m.DisassemblyLine(0, 0, marker, size=3)
    result = m.MatchResult(1.0, 1, (marker,), (marker,), (line,), (line,))
    diagnostic = sib_diff.compare(result, target, candidate)
    assert diagnostic["differences"] == []
    assert diagnostic["alignment"]["aligned_instructions"] == 0
    assert diagnostic["alignment"]["omitted_target_data_lines"] == 1
    assert diagnostic["alignment"]["omitted_candidate_data_lines"] == 1


def test_full_body_keeps_non_sib_byte_differences():
    # Reversing the opcode direction of a same-register move changes its encoding.
    result, diagnostic = compare("89 c0 c3", "8b c0 c3")
    assert not result.exact
    row, = diagnostic["differences"]
    assert not row["swapped"] and row["unequal_bytes"] == [0]
