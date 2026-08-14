from pathlib import Path

import pytest

from snail.recon import (
    find_signature_offsets,
    inspect_path,
    shannon_entropy,
    summarize_rich_header,
)

EXE_PATH = Path(__file__).resolve().parents[1] / "artifacts/bin/SnailMail_unwrapped.exe"


def test_find_signature_offsets_respects_limit() -> None:
    data = b"BMxxxxBMxxxxBM"
    hits = find_signature_offsets(data, signatures={"bmp": b"BM"}, limit=2)

    assert len(hits) == 1
    assert hits[0].name == "bmp"
    assert hits[0].offsets == [0, 6]


def test_shannon_entropy_for_constant_data_is_zero() -> None:
    assert shannon_entropy(b"\x00" * 32) == 0.0


def test_shannon_entropy_for_balanced_two_symbol_data_is_one() -> None:
    assert shannon_entropy(b"\x00\x01" * 32) == 1.0


@pytest.mark.skipif(not EXE_PATH.is_file(), reason="local unwrapped image is required")
def test_inspect_path_reports_ordered_pe_provenance() -> None:
    report = inspect_path(EXE_PATH)
    pe = report["pe"]
    rich = pe["rich_header"]

    assert pe["linker_version"] == {"major": 6, "minor": 0}
    assert pe["coff_timestamp"] == {
        "raw": 1102199912,
        "utc": "2004-12-04T22:38:32+00:00",
    }
    assert pe["data_directories"]["debug"] == {
        "virtual_address": 0,
        "size": 0,
    }
    assert rich["offset_start"] == 0x80
    assert rich["offset_end"] == 0x118
    assert rich["xor_key"] == "0xc5bcc11a"
    assert rich["calculated_checksum"] == rich["xor_key"]
    assert rich["checksum_valid"] is True
    assert rich["structure_valid"] is True
    assert rich["entry_count"] == 16
    assert rich["entries"][0] == {
        "component_id": "0x000c1c7b",
        "product_id": 12,
        "build": 7291,
        "count": 1,
    }
    assert rich["entries"][-1] == {
        "component_id": "0x000606c7",
        "product_id": 6,
        "build": 1735,
        "count": 1,
    }


@pytest.mark.skipif(not EXE_PATH.is_file(), reason="local unwrapped image is required")
def test_rich_header_checksum_detects_stub_tampering() -> None:
    image = bytearray(EXE_PATH.read_bytes())
    nt_header_offset = int.from_bytes(image[0x3C:0x40], "little")

    original = summarize_rich_header(bytes(image), nt_header_offset)
    assert original is not None
    assert original["checksum_valid"] is True

    image[0x50] ^= 1
    tampered = summarize_rich_header(bytes(image), nt_header_offset)
    assert tampered is not None
    assert tampered["checksum_valid"] is False
