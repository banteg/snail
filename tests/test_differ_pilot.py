"""Trust-boundary checks for the optional diagnostic exporters."""

import importlib.util
from dataclasses import replace
from pathlib import Path

import pytest

from snail import match as m
from snail import match_objdiff


def load_script(name):
    path = Path(__file__).parents[1] / "tools/match/differ_pilot" / f"{name}.py"
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


pilot_compare = load_script("compare")
benchmark = load_script("binexport_benchmark")


@pytest.fixture(params=[pilot_compare, match_objdiff], ids=["pilot", "supported"])
def compare(request):
    return request.param


def native_call():
    # At 0x401000: call 0x400100 (a negative signed REL32 displacement).
    data = bytes.fromhex("e8 fb f0 ff ff c3")
    reference = m.MaskedReference(
        0, "imm", "image", 0x400100, "callee", "ref:callee", True
    )
    line = m.DisassemblyLine(0, 0x401000, "call ADDR", 5, (reference,))
    return data, line


def test_native_rel32_roundtrip_and_reference_identity(compare):
    data, line = native_call()
    blob, refs = compare.lift(data, (line,), 0x401000)
    obj = m.parse_coff_object(blob)
    assert obj.sections[0].data == b"\xe8\0\0\0\0\xc3"
    assert obj.sections[0].relocations[0].relocation_type == 0x14
    assert refs[0]["original"] == "fbf0ffff"
    assert refs[0]["key"] == "ref:callee"
    wrong = replace(
        line, masked_references=(replace(line.masked_references[0], key="ref:wrong"),)
    )
    changed, _ = compare.lift(data, (wrong,), 0x401000)
    changed_obj = m.parse_coff_object(changed)
    assert changed_obj.sections[0].data == obj.sections[0].data
    assert changed_obj.symbols[1].name != obj.symbols[1].name


def test_native_dir32_and_literal_bytes_are_preserved(compare):
    # mov eax,[0x405000]; add eax,8; ret
    data = bytes.fromhex("a1 00 50 40 00 83 c0 08 c3")
    ref = m.MaskedReference(
        0, "disp", "image", 0x405000, "global", "ref:global+4", True
    )
    line = m.DisassemblyLine(0, 0x401000, "mov eax,[ADDR]", 5, (ref,))
    blob, refs = compare.lift(data, (line,), 0x401000)
    obj = m.parse_coff_object(blob)
    assert obj.sections[0].data[5:] == data[5:]
    assert obj.sections[0].relocations[0].relocation_type == 6
    assert refs[0]["original"] == "00504000"


@pytest.mark.parametrize("mutation", ["unknown", "wrong_value", "overlap", "inline"])
def test_unsupported_or_inconsistent_reference_fails_closed(compare, mutation):
    data, line = native_call()
    ref = line.masked_references[0]
    if mutation == "unknown":
        refs = (replace(ref, key=None),)
    elif mutation == "wrong_value":
        refs = (replace(ref, value=0x400104),)
    elif mutation == "overlap":
        refs = (ref, ref)
    else:
        refs = (replace(ref, kind="jump_table"),)
    with pytest.raises(ValueError):
        compare.lift(data, (replace(line, masked_references=refs),), 0x401000)


def test_benchmark_counts_unknown_and_missing_separately():
    truth = [
        ("correct", 1, {101}),
        ("wrong", 2, {102}),
        ("unmatched", 3, {103}),
        ("absent", 4, {104}),
    ]
    predictions = [(1, 101, 0.8, 0.95), (2, 105, 0.9, 0.96), (9, 109, 1.0, 1.0)]
    result = benchmark.score(
        truth, predictions, {1, 2, 3, 4}, {101, 102, 103, 105, 109}
    )
    assert result["counts"] == {
        "truth": 4,
        "eligible": 3,
        "correct": 1,
        "wrong": 1,
        "unmatched": 1,
        "absent_from_export": 1,
    }
    assert result["confidence_thresholds"]["0.9"] == {"correct": 1, "wrong": 1}


def test_segment_reader_requires_complete_file_backed_range():
    read = benchmark.segment_reader(b"paddingABCtail", [(0x100, 7, 3)], bias=0x10000)
    assert read(0x10100, 3) == b"ABC"
    with pytest.raises(ValueError):
        read(0x10100, 4)
