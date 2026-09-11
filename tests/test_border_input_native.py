"""Reject incomplete native editor comparisons and detect state/event changes."""
import importlib.util
import struct
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1] / "tools/match"
sys.path.insert(0, str(TOOLS))
try:
    SPEC = importlib.util.spec_from_file_location(
        "snail_test_border_input_native", TOOLS / "compare_border_input_native.py"
    )
    editor = importlib.util.module_from_spec(SPEC)
    SPEC.loader.exec_module(editor)
finally:
    sys.path.remove(str(TOOLS))


def output(cases=2):
    data = bytearray(editor.HEADER.pack(0x314f4942, cases, editor.RECORD_SIZE, editor.WIDGET_SIZE))
    for case in range(cases):
        record = bytearray(editor.RECORD_SIZE)
        struct.pack_into("<II", record, 0, case, 2)
        struct.pack_into("<I", record, 8, 1)
        struct.pack_into("<I", record, 28, 3)
        struct.pack_into("<II", record, 8 + editor.EVENT_BYTES + 0x2c4, 0xf00d0001, 0xf00d0002)
        data.extend(record)
    return data


def compare(tmp_path, left, right):
    a, b = tmp_path / "a.bin", tmp_path / "b.bin"
    a.write_bytes(left)
    b.write_bytes(right)
    return editor.compare_outputs(a, b)


def test_complete_objects_and_events_are_compared(tmp_path):
    data = output()
    result = compare(tmp_path, data, data)
    assert result["equal"] and result["object_regions"] == 4
    assert result["compared_object_bytes"] == 4 * 0x724
    assert result["event_totals"] == [4, 4]
    # Last byte of the second object in the final case must remain visible.
    changed = bytearray(data)
    changed[-1] = 1
    result = compare(tmp_path, data, changed)
    assert result["differing_cases"] == 1
    assert result["differences"][0]["case"] == 1
    assert result["differences"][0]["first_record_offsets"] == [editor.RECORD_SIZE - 1]


def test_callback_argument_change_is_visible(tmp_path):
    data = output()
    changed = bytearray(data)
    changed[editor.HEADER.size + 28 + 4] ^= 1
    result = compare(tmp_path, data, changed)
    assert not result["equal"] and result["differences"][0]["different_bytes"] == 1


@pytest.mark.parametrize("damage", [
    "short_header", "wrong_magic", "zero_cases", "wrong_width", "wrong_widget_size",
    "truncated_record", "trailing_byte", "duplicate_case", "zero_events", "too_many_events",
    "wrong_first_callback", "wrong_callback_order", "unused_event_data", "wrong_pointer_token",
])
def test_identically_corrupt_outputs_cannot_pass(tmp_path, damage):
    data = output()
    record = editor.HEADER.size
    if damage == "short_header":
        data = data[:8]
    elif damage == "wrong_magic":
        struct.pack_into("<I", data, 0, 0)
    elif damage == "zero_cases":
        struct.pack_into("<I", data, 4, 0)
    elif damage == "wrong_width":
        struct.pack_into("<I", data, 8, editor.RECORD_SIZE - 1)
    elif damage == "wrong_widget_size":
        struct.pack_into("<I", data, 12, 0x720)
    elif damage == "truncated_record":
        data = data[:-1]
    elif damage == "trailing_byte":
        data += b"\0"
    elif damage == "duplicate_case":
        struct.pack_into("<I", data, record + editor.RECORD_SIZE, 0)
    elif damage == "zero_events":
        struct.pack_into("<I", data, record + 4, 0)
    elif damage == "too_many_events":
        struct.pack_into("<I", data, record + 4, 5)
    elif damage == "wrong_first_callback":
        struct.pack_into("<I", data, record + 8, 3)
    elif damage == "wrong_callback_order":
        struct.pack_into("<I", data, record + 28, 2)
    elif damage == "unused_event_data":
        data[record + 48] = 1
    elif damage == "wrong_pointer_token":
        data[record + 8 + editor.EVENT_BYTES + 0x2c4] ^= 1
    with pytest.raises(ValueError):
        compare(tmp_path, data, data)


def test_unequal_headers_cannot_hide_missing_cases(tmp_path):
    with pytest.raises(ValueError, match="unequal output headers"):
        compare(tmp_path, output(2), output(1))
