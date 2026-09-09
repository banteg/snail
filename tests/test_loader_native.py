"""Integrity gates for isolated original-code loader comparisons."""

import importlib.util
import struct
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

TOOLS = Path(__file__).resolve().parents[1] / "tools/match"
sys.path.insert(0, str(TOOLS))
try:
    SPEC = importlib.util.spec_from_file_location(
        "snail_test_loader_native", TOOLS / "compare_loaders_native.py"
    )
    loaders = importlib.util.module_from_spec(SPEC)
    SPEC.loader.exec_module(loaders)
    from compare_sbend_native import oracle_reference_entries
finally:
    sys.path.remove(str(TOOLS))


def entry(**overrides):
    fields = {
        "status": "unaudited",
        "target_index": None,
        "target_offset": None,
        "target_references": (),
        "candidate_references": (object(),),
        "candidate_offset": 12,
        "instruction": "push ADDR",
    }
    return SimpleNamespace(**(fields | overrides))


def test_source_only_audit_debt_requires_explicit_diagnostic_opt_in():
    audit = SimpleNamespace(entries=[entry()])
    with pytest.raises(ValueError, match="clean native"):
        oracle_reference_entries(audit)
    native, omitted = oracle_reference_entries(audit, allow_candidate_only=True)
    assert native == []
    assert omitted == [{"candidate_offset": 12, "instruction": "push ADDR"}]


@pytest.mark.parametrize(
    "changes",
    [
        {"target_index": 2},
        {"target_offset": 3},
        {"target_references": (object(),)},
        {"status": "mismatch"},
        {"status": "unresolved"},
        {"candidate_references": ()},
    ],
)
def test_source_only_exception_cannot_remove_native_reference_debt(changes):
    with pytest.raises(ValueError, match="clean native"):
        oracle_reference_entries(
            SimpleNamespace(entries=[entry(**changes)]), allow_candidate_only=True
        )


def test_clean_native_reference_is_retained():
    clean = entry(
        status="ok", target_index=4, target_offset=9, target_references=(object(),)
    )
    kept, omitted = oracle_reference_entries(SimpleNamespace(entries=[clean]))
    assert kept == [clean] and omitted == []


def header(size=8, fill=0xA5):
    return b"catalog\0".ljust(128, b"\0") + struct.pack("<II", size, fill)


def span(start, data):
    return struct.pack("<II", start, len(data)) + data


def test_sparse_output_covers_every_byte_and_detects_changed_field():
    end = struct.pack("<I", 0xFFFFFFFF)
    original = header() + span(2, b"\x00\x01") + end
    different = header() + span(2, b"\x00\x02") + end
    assert loaders.decode_regions(original) == [
        ("catalog", bytearray(b"\xa5\xa5\0\1\xa5\xa5\xa5\xa5"))
    ]
    result = loaders.compare_regions(original, different)
    assert result["equal"] is False and result["compared_bytes"] == 8
    assert result["differences"][0]["first_offsets"] == [3]


@pytest.mark.parametrize(
    "encoded",
    [
        header()[:-1],
        header() + b"\0",
        header() + struct.pack("<I", 0),
        header() + span(7, b"12") + struct.pack("<I", 0xFFFFFFFF),
        header() + span(1, b"12") + span(2, b"3") + struct.pack("<I", 0xFFFFFFFF),
        header(size=0) + struct.pack("<I", 0xFFFFFFFF),
        header(fill=256) + struct.pack("<I", 0xFFFFFFFF),
    ],
)
def test_corrupt_sparse_coverage_is_rejected(encoded):
    with pytest.raises(ValueError):
        loaders.decode_regions(encoded)
