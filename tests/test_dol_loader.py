"""Malformed headers and mapping contracts require no Binary Ninja license."""

import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).parents[1] / "tools/binja"))
from dol_loader.format import InvalidDOL, parse_header


def dol(*, text=None, data=(), bss=(0, 0), entry=0x80004000, size=0x800):
    words = [0] * 64
    if text is None:
        text = [(0, 0x100, 0x80004000, 0x40)]
    for slots, offsets, addresses, sizes in ((text, 0, 18, 36), (data, 7, 25, 43)):
        for index, offset, address, length in slots:
            words[offsets + index] = offset
            words[addresses + index] = address
            words[sizes + index] = length
    words[54:57] = [*bss, entry]
    return struct.pack(">64I", *words), size


def test_sparse_slots_and_exact_sizes():
    header, size = dol(
        text=[(6, 0x100, 0x80004000, 4)],
        data=[(10, 0x104, 0x90000000, 3)],
    )
    result = parse_header(header, size)
    assert [(s.name, s.address, s.offset, s.size) for s in result.sections] == [
        (".text6", 0x80004000, 0x100, 4),
        (".data10", 0x90000000, 0x104, 3),
    ]


@pytest.mark.parametrize("base", [0x80000000, 0x90000000, 0xC0000000, 0xD0000000])
def test_memory_banks(base):
    assert (
        parse_header(*dol(text=[(0, 0x100, base, 4)], entry=base)).entry_point == base
    )


@pytest.mark.parametrize(
    "kwargs",
    [
        {"text": []},
        {"size": 0xFF},
        {"size": 0x100000000},
        {"entry": 0x80004001},
        {"entry": 0x80004040},
        {"text": [(0, 0xFC, 0x80004000, 0x40)]},
        {"text": [(0, 0x7F0, 0x80004000, 0x40)]},
        {"text": [(0, 0x100, 0x80004000, 3)]},
        {"text": [(0, 0x100, 0x80004001, 4)]},
        {"data": [(0, 0x120, 0x80005000, 0x40)]},  # file overlap
        {"data": [(0, 0x200, 0x80004020, 0x40)]},  # memory overlap
        {"data": [(0, 0x200, 0x817FFFF0, 0x20)]},
        {"data": [(0, 0x200, 0xFFFFFFFF, 4)]},
        {"data": [(0, 0xFFFFFFF0, 0x80005000, 0x40)]},
        {"data": [(0, 0, 0x80005000, 4)]},
        {"bss": (0x817FFFF0, 0x20)},
        {"bss": (0, 4)},
    ],
)
def test_invalid_layout(kwargs):
    with pytest.raises(InvalidDOL):
        parse_header(*dol(**kwargs))


@pytest.mark.parametrize("length", [0, 4, 0xE3, 0xE4, 0xFF])
def test_truncated_header(length):
    with pytest.raises(InvalidDOL):
        parse_header(bytes(length), 0x800)


@pytest.mark.parametrize(
    ("data", "expected"),
    [
        ([], [(0x80005000, 0x100)]),
        ([(0, 0x200, 0x80005200, 0x20)], [(0x80005000, 0x100)]),
        ([(0, 0x200, 0x80005100, 0x20)], [(0x80005000, 0x100)]),
        ([(0, 0x200, 0x80004F80, 0x200)], []),
        ([(0, 0x200, 0x80004FE0, 0x40)], [(0x80005020, 0xE0)]),
        ([(0, 0x200, 0x800050E0, 0x40)], [(0x80005000, 0xE0)]),
        ([(0, 0x200, 0x80005040, 0x40)], [(0x80005000, 0x40), (0x80005080, 0x80)]),
        (
            [(0, 0x200, 0x80005020, 0x20), (3, 0x240, 0x80005040, 0x20)],
            [(0x80005000, 0x20), (0x80005060, 0xA0)],
        ),
    ],
)
def test_bss_interval_subtraction(data, expected):
    layout = parse_header(*dol(data=data, bss=(0x80005000, 0x100)))
    assert [(s.address, s.size) for s in layout.bss] == expected
    assert all(s.offset is None for s in layout.bss)


def test_zero_sized_slot_ignores_unused_fields():
    header, size = dol(data=[(0, 0xFFFFFFFF, 0xFFFFFFFF, 0), (2, 0x200, 0x80005000, 4)])
    assert [s.name for s in parse_header(header, size).sections] == [".text0", ".data2"]
