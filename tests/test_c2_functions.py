import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).parents[1] / "tools/match/c2"))

import trace as c2_trace

from snail import match as m

CODE = 0x20  # IMAGE_SCN_CNT_CODE


def coff(*functions):
    """An object whose function symbols are (name, section, offset), in symbol-table order."""
    sections = max(section for _, section, _ in functions)
    return m.CoffObject(
        sections=tuple(m.CoffSection(".text", b"\xc3" * 0x40, CODE, ()) for _ in range(sections)),
        symbols=(
            m.CoffSymbol(0, ".text", 0, 1, 0, 3),
            *(
                m.CoffSymbol(index + 1, name, offset, section, 0x20, 2)
                for index, (name, section, offset) in enumerate(functions)
            ),
        ),
    )


UNIT = coff(
    ("?second@cRPath@@QAEXXZ", 2, 0),
    ("?first@cRPath@@QAEXXZ", 1, 0),
    ("?third@cRPath@@QAEXXZ", 2, 0x20),
)


@pytest.mark.parametrize(("name", "ordinal"), [("first", 0), ("second", 1), ("third", 2)])
def test_target_function_is_its_place_in_code_order(name, ordinal):
    assert c2_trace.target_function(UNIT, name, 3) == ordinal


def test_target_function_falls_back_to_the_last_function(capsys):
    assert c2_trace.target_function(UNIT, "missing", 3) == 2
    assert "using the last" in capsys.readouterr().err
    # Entries that do not pair with the object's functions cannot be named.
    assert c2_trace.target_function(UNIT, "first", 4) == 3


def test_target_function_of_a_single_function_is_silent(capsys):
    assert c2_trace.target_function(coff(("_f", 1, 0)), "g", 1) == 0
    assert capsys.readouterr().err == ""


def test_label_functions_counts_entries():
    records = [(5,), (1000,), (3,), (1001,), (1000,), (7,)]
    labelled = list(c2_trace.label_functions(records, lambda r: r[0] == 1000))
    assert [ordinal for ordinal, _ in labelled] == [-1, 0, 0, 0, 1, 1]
    assert [record for _, record in labelled] == records


def test_function_event_selects_one_function():
    events = [
        {"function_ordinal": f, "target_rva": rva, "event": n}
        for n, (f, rva) in enumerate([(0, 1), (0, 2), (1, 1), (1, 2)])
    ]
    assert c2_trace.function_event(events, 1, 2)["event"] == 3
    assert [e["event"] for e in c2_trace.function_events(events, 0)] == [0, 1]
    with pytest.raises(ValueError):
        c2_trace.function_event(events, 2, 1)


def test_gated_trace_keeps_ordinals_of_functions_without_nodes():
    observer = c2_trace.c2
    profile = {"hooks": [{"site": 1, "target": 2, "return": False}], "invoke_rva": 0}
    assert "#define SNAPSHOT_ORDINAL -1\n" in observer.observer_source(profile)
    gated = dict(profile, snapshot_ordinal=1)
    assert "#define SNAPSHOT_ORDINAL 1\n" in observer.observer_source(gated)
    # Two function entries: the first keeps its header without nodes.
    node = struct.pack(f"<{observer.NODE_WORDS}I", 0x1234, 0x16D, 7, 0, *[0] * 738)
    data = (
        struct.pack("<3I", 0x43325431, 1, 0)
        + struct.pack("<3I", 0, 0x100, 0)
        + struct.pack("<3I", 0, 0x200, 1)
        + node
    )
    events = observer.decode_trace(data, gated)
    assert [(e["function_ordinal"], len(e["nodes"])) for e in events] == [(0, 0), (1, 1)]
    assert events[1]["nodes"][0]["op"] == 0x16D


# addrorder and cse_slot_trace read the VC6 backend's C2 profile on import.


@pytest.mark.local_artifacts
def test_cse_origin_is_per_function():
    import addrorder

    def allocation(klass, ident, hook=addrorder.FIRST_ALLOCATOR_HOOK):
        return struct.pack("<4I", hook, klass, hook + 100, ident)

    entry = struct.pack("<2I", 1000, 0)
    data = (
        allocation(4, 0x10)
        + entry
        + allocation(addrorder.CSE_CLASS, 0x80)
        + allocation(addrorder.CSE_CLASS, 0x81)
        + entry
        + allocation(4, 0x20)
        + allocation(addrorder.CSE_CLASS, 0x500)
        + allocation(addrorder.CSE_CLASS, 0x501)
    )
    allocations = addrorder.decode_allocations(data)
    assert [a["function"] for a in allocations] == [-1, 0, 0, 1, 1, 1]
    assert addrorder.cse_origin(allocations, 0) == (0x80, {0x80: 0, 0x81: 1})
    assert addrorder.cse_origin(allocations, 1) == (0x500, {0x500: 0, 0x501: 1})


@pytest.mark.local_artifacts
def test_cse_slots_are_per_function():
    import cse_slot_trace

    table = [{"kind": cse_slot_trace.PASS}, {"kind": cse_slot_trace.CSE_ALLOC}]

    def record(phase, *words):
        return (phase, *[0] * 8, *words, *[0] * (cse_slot_trace.RECORD_WORDS - 9 - len(words)))

    def slot(ident):
        return [record(1, 0x16D, 0x1004), record(101, ident)]

    records = [record(1000), *slot(0x80), record(1000), *slot(0x500), *slot(0x501)]
    assert [s["id"] for s in cse_slot_trace.decode(table, records, 0)] == [0x80]
    assert [s["id"] for s in cse_slot_trace.decode(table, records, 1)] == [0x500, 0x501]
