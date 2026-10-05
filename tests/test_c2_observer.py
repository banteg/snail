import json
import struct
import sys
from pathlib import Path

C2 = Path(__file__).parents[1] / "tools/match/c2"
sys.path.insert(0, str(C2))

import c2_replay


def test_alias_object_emits_weak_externals_to_targets():
    data = c2_replay.alias_object({"__imp__LoadLibraryA@4": "__imp__LoadLibraryA"})
    machine, sections, _, table, count, _, _ = struct.unpack_from("<HHIIIHH", data)
    assert (machine, sections, table, count) == (0x14C, 0, 20, 3)
    strings = data[table + 18 * count :]
    names = []
    for index in (0, 1):
        entry = data[table + 18 * index : table + 18 * (index + 1)]
        zero, offset = struct.unpack_from("<II", entry)
        names.append(strings[offset:].split(b"\0")[0] if zero == 0 else entry[:8].rstrip(b"\0"))
        assert entry[16] == (2, 105)[index]
    assert names == [b"__imp__LoadLibraryA", b"__imp__LoadLibraryA@4"]
    tag, kind = struct.unpack_from("<II", data, table + 36)
    assert (tag, kind) == (0, 3)


def test_profiles_pin_one_backend_with_complete_hook_sets():
    for path in (C2 / "observer").glob("*.json"):
        profile = json.loads(path.read_text())
        assert profile["compiler"] == path.stem
        assert len(profile["hooks"]) == 29 and len(profile["early_address_hooks"]) == 12
        order = profile["address_order"]
        assert len(order["allocator_sites"]) == 6
        sites = [h["site"] for h in profile["hooks"]]
        assert len(set(sites)) == len(sites)
