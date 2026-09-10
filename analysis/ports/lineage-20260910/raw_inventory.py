"""Inspect the specific retained mobile ELF/Mach-O builds; run from the repo root."""

import argparse
import collections
import hashlib
import json
import struct
import zipfile
from pathlib import Path

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument("--out", type=Path, default=Path("artifacts/mobile-audit-20260910"))
OUT = parser.parse_args().out
OUT.mkdir(parents=True, exist_ok=True)


def cstr(b, o):
    return b[o : b.index(b"\0", o)].decode("utf-8", "replace")


def elf(b):
    assert b[:6] == b"\x7fELF\x01\x01"
    h = struct.unpack_from("<16sHHIIIIIHHHHHH", b)
    assert h[2] == 40
    sections = []
    shoff, shsz, shnum, shstr = h[6], h[11], h[12], h[13]
    rows = [struct.unpack_from("<10I", b, shoff + i * shsz) for i in range(shnum)]
    strtab = b[rows[shstr][4] : rows[shstr][4] + rows[shstr][5]]
    for r in rows:
        sections.append(
            {
                "name": cstr(strtab, r[0]),
                "type": r[1],
                "flags": r[2],
                "address": r[3],
                "offset": r[4],
                "size": r[5],
                "link": r[6],
                "entsize": r[9],
            }
        )
    syms = []
    for s in sections:
        if s["type"] not in [2, 11]:
            continue
        t = sections[s["link"]]
        st = b[t["offset"] : t["offset"] + t["size"]]
        for pos in range(s["offset"], s["offset"] + s["size"], s["entsize"]):
            n, v, size, info, _other, section = struct.unpack_from("<IIIBBH", b, pos)
            syms.append(
                {
                    "name": cstr(st, n),
                    "address": v,
                    "size": size,
                    "type": info & 15,
                    "binding": info >> 4,
                    "section": section,
                    "table": s["name"],
                }
            )
    return {
        "format": "ELF32-LE-ARM",
        "sections": sections,
        "symbols": syms,
        "comments": sorted(
            {
                v.decode("utf-8", "replace")
                for s in sections
                if s["name"] == ".comment"
                for v in b[s["offset"] : s["offset"] + s["size"]].split(b"\0")
                if v
            }
        ),
    }


def macho(b):
    if b[:4] == b"\xca\xfe\xba\xbe":
        n = struct.unpack_from(">I", b, 4)[0]
        out = []
        for i in range(n):
            _cpu, _sub, off, size, _align = struct.unpack_from(">5I", b, 8 + i * 20)
            s = macho(b[off : off + size])
            s["fat_offset"] = off
            s["slice_size"] = size
            out.append(s)
        return out
    assert b[:4] == b"\xce\xfa\xed\xfe", b[:4]
    h = struct.unpack_from("<7I", b)
    assert h[1] == 12
    off = 28
    sections = []
    enc = []
    tab = None
    dyn = None
    for _ in range(h[4]):
        cmd, size = struct.unpack_from("<II", b, off)
        if cmd == 1:
            seg = struct.unpack_from("<II16s8I", b, off)
            for j in range(seg[9]):
                r = struct.unpack_from("<16s16s9I", b, off + 56 + j * 68)
                sections.append(
                    {
                        "name": r[1].rstrip(b"\0").decode()
                        + ","
                        + r[0].rstrip(b"\0").decode(),
                        "address": r[2],
                        "size": r[3],
                        "offset": r[4],
                        "flags": r[8],
                    }
                )
        elif cmd == 2:
            tab = struct.unpack_from("<6I", b, off)[2:]
        elif cmd == 11:
            dyn = struct.unpack_from("<20I", b, off)
        elif cmd == 0x21:
            enc.append(
                dict(
                    zip(
                        ["offset", "size", "cryptid"],
                        struct.unpack_from("<5I", b, off)[2:],
                    )
                )
            )
        off += size
    syms = []
    if tab:
        so, sn, stro, strsz = tab
        st = b[stro : stro + strsz]
        src = obj = None
        for i in range(sn):
            n, t, sec, desc, val = struct.unpack_from("<IBBHI", b, so + i * 12)
            name = cstr(st, n)
            if t == 0x64:
                src = name
            if t == 0x66:
                obj = name
            syms.append(
                {
                    "name": name,
                    "type": t,
                    "section": sec,
                    "desc": desc,
                    "address": val,
                    "source": src,
                    "object": obj,
                }
            )
    relocs = []
    if dyn:
        for pos in range(dyn[16], dyn[16] + dyn[17] * 8, 8):
            address, info = struct.unpack_from("<II", b, pos)
            assert info & (1 << 27)
            relocs.append(
                {
                    "address": address,
                    "symbol": syms[info & 0xFFFFFF]["name"],
                    "pcrel": (info >> 24) & 1,
                    "width": 1 << ((info >> 25) & 3),
                    "type": info >> 28,
                }
            )
    return {
        "slice_sha256": hashlib.sha256(b).hexdigest(),
        "external_relocations": relocs,
        "format": "MachO32-LE-ARM",
        "cpu": h[1],
        "subtype": h[2],
        "sections": sections,
        "symbols": syms,
        "encryption": enc,
    }


inputs = {
    "android-v7": Path(
        "artifacts/android/unpacked/com.sandlotgames.snailmail.1/lib/armeabi-v7a/libsnailmail.so"
    ).read_bytes(),
    "android-v5": Path(
        "artifacts/android/unpacked/com.sandlotgames.snailmail.1/lib/armeabi/libsnailmail.so"
    ).read_bytes(),
    "ios15": Path("artifacts/ios/unpacked/Snail Mail/Payload/iSM.app/iSM").read_bytes(),
    "ipad106": Path(
        "artifacts/ios/unpacked/SnailMailforiPad-v1.0.5/Payload/PSM-iPad.app/PSM-iPad"
    ).read_bytes(),
}
with zipfile.ZipFile("artifacts/4pda/snail_mail_v1.9.0.ipa") as z:
    inputs["ios19"] = z.read(next(n for n in z.namelist() if n.endswith(".app/iSM")))
with zipfile.ZipFile("artifacts/4pda/snailmail.apk") as z:
    for n in z.namelist():
        if n.endswith("libsnailmail.so"):
            inputs["android-other-" + n.split("/")[-2]] = z.read(n)
for key, b in inputs.items():
    data = elf(b) if b.startswith(b"\x7fELF") else macho(b)
    slices = data if isinstance(data, list) else [data]
    for j, s in enumerate(slices):
        label = key if len(slices) == 1 else f"{key}-slice{j}"
        s["file_sha256"] = hashlib.sha256(b).hexdigest()
        s["file_size"] = len(b)
        (OUT / f"{label}-raw.json").write_text(json.dumps(s, indent=2) + "\n")
        print(
            label,
            s["file_sha256"],
            len(b),
            "symbols",
            len(s["symbols"]),
            "debug sections",
            [
                x["name"]
                for x in s["sections"]
                if "debug" in x["name"] or "stab" in x["name"]
            ],
            s.get("comments", s.get("encryption")),
        )
        print("symboltypes", collections.Counter(x["type"] for x in s["symbols"]))
        if key == "ios19":
            off = s["fat_offset"]
            (OUT / label).write_bytes(b[off : off + s["slice_size"]])
        print(
            "files",
            [
                (x["name"], x["address"])
                for x in s["symbols"]
                if x["type"] in ([4] if s["format"].startswith("ELF") else [0x64, 0x66])
            ][:5],
        )
