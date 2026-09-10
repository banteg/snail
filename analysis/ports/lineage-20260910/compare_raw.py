"""Build the bounded mobile lineage receipt from raw_inventory.py output."""

import argparse
import collections
import hashlib
import json
import re
import struct
import subprocess
from pathlib import Path

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument(
    "--inventory", type=Path, default=Path("artifacts/mobile-audit-20260910")
)
parser.add_argument("--out", type=Path, required=True)
args = parser.parse_args()
R = args.inventory
keys = ["android-v7", "android-v5", "ios15", "ipad106", "ios19-slice0", "ios19-slice1"]
raw = {k: json.loads((R / f"{k}-raw.json").read_text()) for k in keys}
binaries = {
    "ios15": Path("artifacts/ios/unpacked/Snail Mail/Payload/iSM.app/iSM").read_bytes(),
    "ios19-slice0": (R / "ios19-slice0").read_bytes(),
    "ios19-slice1": (R / "ios19-slice1").read_bytes(),
}
for key, body in binaries.items():
    assert hashlib.sha256(body).hexdigest() == raw[key]["slice_sha256"]


def read(key, address, count):
    section = next(
        s
        for s in raw[key]["sections"]
        if s["address"] <= address and address + count <= s["address"] + s["size"]
    )
    assert section["flags"] & 255 != 1  # No reads from zerofill sections.
    offset = section["offset"] + address - section["address"]
    return binaries[key][offset : offset + count]


def cstring(key, address):
    section = next(
        s
        for s in raw[key]["sections"]
        if s["address"] <= address < s["address"] + s["size"]
    )
    assert section["name"] == "__TEXT,__cstring"
    return (
        read(key, address, min(256, section["address"] + section["size"] - address))
        .split(b"\0", 1)[0]
        .decode()
    )


def symbols(key):
    return {s["name"]: s for s in raw[key]["symbols"] if s["name"] and s["address"]}


cpp = {}
summary = {}
for key in keys:
    d = raw[key]
    elf = d["format"].startswith("ELF")
    functions = [
        s
        for s in d["symbols"]
        if s["name"]
        and (
            (s["type"] == 2 and s["section"] not in [0, 65521])
            if elf
            else (s["type"] == 36 or (s["type"] in [14, 15] and s["section"] == 1))
        )
    ]
    cpp[key] = {
        s["name"][1:] if s["name"].startswith("__Z") else s["name"]
        for s in functions
        if re.match("_{1,2}Z", s["name"])
    }
    demangled = subprocess.run(
        ["c++filt"],
        input="\n".join(sorted(cpp[key])) + "\n",
        text=True,
        capture_output=True,
        check=True,
    ).stdout.splitlines()
    summary[key] = {
        "file_sha256": d["file_sha256"],
        "slice_sha256": d.get("slice_sha256"),
        "size": d.get("slice_size", d["file_size"]),
        "format": d["format"],
        "cpu_subtype": d.get("subtype"),
        "unique_cpp_function_symbols": len(cpp[key]),
        "unique_demangled_functions": len(set(demangled)),
        "vtable_symbols": len(
            {s["name"] for s in d["symbols"] if re.match("_{1,2}ZTV", s["name"])}
        ),
        "typeinfo_symbols": len(
            {s["name"] for s in d["symbols"] if re.match("_{1,2}ZTI", s["name"])}
        ),
        "dwarf_sections": [s["name"] for s in d["sections"] if "debug" in s["name"]],
        "compiler_comments": d.get("comments", []),
        "encryption": d.get("encryption", []),
        "stabs_record_types": dict(
            collections.Counter(
                hex(s["type"]) for s in d["symbols"] if not elf and s["type"] & 0xE0
            )
        ),
    }


def demangle(names):
    return (
        subprocess.run(
            ["c++filt"],
            input="\n".join(sorted(names)) + "\n",
            text=True,
            capture_output=True,
            check=True,
        ).stdout.splitlines()
        if names
        else []
    )


added = cpp["ios19-slice0"] - cpp["ios15"]
new_ios_existing_android = [
    n
    for n in demangle(added & cpp["android-v7"])
    if re.match(r"(cR\w+|tVector|tMatrix|tQuaternian)::", n)
]

# Decode RTTI using the relocation naming its runtime record class, rather than
# guessing the kind from adjacent words. The ARM records have 32-bit fields.
rtti = {}
for key in ["ios15", "ios19-slice0"]:
    syms = symbols(key)
    byaddr = {s["address"]: n for n, s in syms.items() if n.startswith("__ZTI")}
    reloc = {r["address"]: r for r in raw[key]["external_relocations"]}
    records = []
    for name, sym in sorted(syms.items()):
        if not re.match(r"__ZTI\d+cR", name):
            continue
        address = sym["address"]
        r = reloc[address]
        assert r["width"] == 4 and r["type"] == 0 and r["pcrel"] == 0
        kind = r["symbol"]
        vptr, nameptr = struct.unpack("<2I", read(key, address, 8))
        assert vptr == 8
        type_name_symbol = name.replace("__ZTI", "__ZTS", 1)
        assert nameptr == syms[type_name_symbol]["address"]
        encoded_name = name.removeprefix("__ZTI").encode() + b"\0"
        assert read(key, nameptr, len(encoded_name)) == encoded_name
        record = {
            "symbol": name,
            "address": hex(address),
            "vptr_relocation": r,
            "vptr_addend": vptr,
            "name_address": hex(nameptr),
            "bases": [],
        }
        if "__si_class_type_info" in kind:
            base = struct.unpack("<I", read(key, address + 8, 4))[0]
            record["bases"].append(
                {"type": byaddr[base], "offset": 0, "public": True, "virtual": False}
            )
        elif "__vmi_class_type_info" in kind:
            flags, count = struct.unpack("<2I", read(key, address + 8, 8))
            assert count < 32
            record["hierarchy_flags"] = flags
            for i in range(count):
                base, offset_flags = struct.unpack(
                    "<Ii", read(key, address + 16 + i * 8, 8)
                )
                record["bases"].append(
                    {
                        "type": byaddr[base],
                        "offset": offset_flags >> 8,
                        "public": bool(offset_flags & 2),
                        "virtual": bool(offset_flags & 1),
                        "encoded_offset_flags": hex(offset_flags),
                    }
                )
        else:
            assert "__class_type_info" in kind
        records.append(record)
    rtti[key] = records

# Compare complete symbol extents, including embedded/trailing literal pools.
# The old STABS ending FUN record supplies its extent. The newer adjacent text
# symbol independently gives the same end in these three selected functions.
comparisons = []
for name in [
    "__ZN11tQuaternianC2ERK7tMatrix",
    "__ZN6cRPath11BuildSlalomEiibPcS0_",
    "__ZN8cRBorder13AddTextNumberEi",
]:
    labels = ["ios15", "ios19-slice0"]
    starts = [symbols(k)[name]["address"] for k in labels]
    oldsyms = raw["ios15"]["symbols"]
    index = next(
        i for i, s in enumerate(oldsyms) if s["name"] == name and s["type"] == 36
    )
    ending = oldsyms[index + 1]
    assert ending["type"] == 36 and not ending["name"]
    size = ending["address"]
    for key, a in zip(labels, starts, strict=True):
        nextaddr = min(
            s["address"]
            for s in raw[key]["symbols"]
            if s["section"] == 1 and s["name"] and s["address"] > a
        )
        assert nextaddr - a == size
    bodies = [read(k, a, size) for k, a in zip(labels, starts, strict=True)]
    maps = []
    for key in labels:
        mapping = collections.defaultdict(set)
        for s in raw[key]["symbols"]:
            if s["name"]:
                mapping[s["address"]].add(s["name"])
        maps.append(mapping)
    changes = []
    for offset in range(0, size, 4):
        words = [struct.unpack("<I", b[offset : offset + 4])[0] for b in bodies]
        if words[0] == words[1]:
            continue
        change = {
            "offset": hex(offset),
            "old_word": hex(words[0]),
            "new_word": hex(words[1]),
        }
        if words[0] >> 24 in [0xEA, 0xEB] and words[1] >> 24 == words[0] >> 24:
            targets = []
            for w, a in zip(words, starts, strict=True):
                disp = w & 0xFFFFFF
                if disp & 0x800000:
                    disp -= 0x1000000
                targets.append(a + offset + 8 + disp * 4)
            common = maps[0][targets[0]] & maps[1][targets[1]]
            assert common
            change.update(
                kind="branch_to_same_symbol",
                targets=[hex(a) for a in targets],
                symbols=sorted(common),
            )
        elif name == "__ZN8cRBorder13AddTextNumberEi" and offset in [8, 12]:
            expected = {8: [0xE2802FB1, 0xE2802FB6], 12: [0xE5D002C4, 0xE5D002D8]}
            assert words == expected[offset]
            change.update(
                kind="text_field_offset", old_offset="0x2c4", new_offset="0x2d8"
            )
        else:
            text = [cstring(k, a) for k, a in zip(labels, words, strict=True)]
            assert text[0] == text[1]
            change.update(kind="pointer_to_same_string", text=text[0])
        changes.append(change)
    comparisons.append(
        {
            "symbol": name,
            "starts": dict(zip(labels, map(hex, starts), strict=True)),
            "full_extent_bytes": size,
            "body_sha256": [hashlib.sha256(b).hexdigest() for b in bodies],
            "changed_words": changes,
            "unchanged_words": size // 4 - len(changes),
            "unexplained_changed_words": 0,
        }
    )

# The Wii addresses are prior discovery seeds; verify the complete record and
# base-list bytes again before comparing the hierarchy with fresh iPhone RTTI.
wii_seed = json.loads(
    Path("analysis/wii/tool-comparison-20260910/type-metadata.json").read_text()
)
wii = Path("artifacts/wii/reference/SnailMail-USA.dol").read_bytes()
assert hashlib.sha256(wii).hexdigest() == wii_seed["input_sha256"]
header = struct.unpack_from(">57I", wii)
regions = []
for count, offsets, addresses, sizes in [(7, 0, 18, 36), (11, 7, 25, 43)]:
    for n in range(count):
        if header[sizes + n]:
            regions.append(
                (header[addresses + n], header[sizes + n], header[offsets + n])
            )


def wii_read(address, count):
    start, _size, offset = next(
        s for s in regions if s[0] <= address and address + count <= s[0] + s[1]
    )
    return wii[offset + address - start : offset + address - start + count]


wii_ancestors = {}
for record in wii_seed["records"]:
    address = int(record["address"], 16)
    name, bases = struct.unpack(">2I", wii_read(address, 8))
    assert name == int(record["name_address"], 16) and bases == int(
        record["base_table"], 16
    )
    expected = record["name"].encode() + b"\0"
    assert wii_read(name, len(expected)) == expected
    for n, base in enumerate(record["base_entries"]):
        target, offset = struct.unpack(">2I", wii_read(bases + n * 8, 8))
        assert target == int(base["descriptor"], 16) and offset == int(
            base["offset_word"], 16
        )
    if bases:
        assert wii_read(bases + len(record["base_entries"]) * 8, 4) == bytes(4)
    wii_ancestors[record["name"]] = {b["name"] for b in record["base_entries"]}


def plain_type(symbol):
    return re.sub(r"^__ZTI\d+", "", symbol)


ios_bases = {
    plain_type(r["symbol"]): {plain_type(b["type"]) for b in r["bases"]}
    for r in rtti["ios15"]
}


def closure(graph, node):
    result = set()
    queue = list(graph[node])
    while queue:
        base = queue.pop()
        assert base != node
        if base in result:
            continue
        result.add(base)
        queue.extend(graph.get(base, ()))
    return result


shared_classes = sorted(ios_bases.keys() & wii_ancestors.keys())
hierarchy = [
    {
        "class": name,
        "ios_ancestors": sorted(closure(ios_bases, name)),
        "wii_ancestors": sorted(closure(wii_ancestors, name)),
    }
    for name in shared_classes
]

receipt = {
    "method": "Direct ELF32/Mach-O32 headers, symbol tables, external relocations and binary bytes; no decompiler corpus is an input to these comparisons.",
    "builds": summary,
    "wii_rtti_recheck": {
        "sha256": wii_seed["input_sha256"],
        "verified_records": len(wii_ancestors),
        "shared_classes": len(shared_classes),
        "hierarchies": hierarchy,
        "scope": "Earlier bounded Wii address seeds, all name/base-list words rechecked in the current DOL; not a complete census.",
    },
    "android_abis_cpp_symbol_symmetric_difference": len(
        cpp["android-v7"] ^ cpp["android-v5"]
    ),
    "other_apk_same_native_libraries": {
        abi: json.loads((R / f"android-other-{abi}-raw.json").read_text())[
            "file_sha256"
        ]
        == raw[key]["file_sha256"]
        for abi, key in [("armeabi", "android-v5"), ("armeabi-v7a", "android-v7")]
    },
    "iphone19_arm_slices_cpp_symbol_symmetric_difference": len(
        cpp["ios19-slice0"] ^ cpp["ios19-slice1"]
    ),
    "iphone19_cpp_symbols_absent_from_15": demangle(added),
    "iphone19_game_methods_also_in_android_but_absent_from_15": new_ios_existing_android,
    "iphone_rtti": rtti,
    "iphone15_19_complete_extent_comparisons": comparisons,
    "limits": [
        "Symbol absence is not proof of source absence; inlining, stripping and library selection differ.",
        "Matched names and cross-version instruction correspondence do not establish exact original C++ or direct ancestry order.",
        "No full member type records or executable runtime equivalence are claimed.",
        "Three function comparisons are bounded samples, not whole-game lineage percentages.",
    ],
}
args.out.parent.mkdir(parents=True, exist_ok=True)
args.out.write_text(json.dumps(receipt, indent=2) + "\n")
print("Wrote", args.out)
print("RTTI game records", {k: len(v) for k, v in rtti.items()})
print(
    "iPhone 1.9 new C++ symbols",
    len(added),
    "game methods already in Android",
    len(new_ios_existing_android),
)
print(
    "Complete extent comparisons",
    [
        (
            c["full_extent_bytes"],
            len(c["changed_words"]),
            c["unexplained_changed_words"],
        )
        for c in comparisons
    ],
)
