"""Disassemble bounded Android samples, honoring ELF code/data mapping symbols."""

import argparse
import collections
import hashlib
import json
import struct
from itertools import pairwise
from pathlib import Path

from capstone import CS_ARCH_ARM, CS_MODE_ARM, Cs

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument(
    "--inventory", type=Path, default=Path("artifacts/mobile-audit-20260910")
)
parser.add_argument("--out", type=Path, required=True)
args = parser.parse_args()
args.out.mkdir(parents=True, exist_ok=True)
for key, abi in [("android-v7", "armeabi-v7a"), ("android-v5", "armeabi")]:
    body = Path(
        f"artifacts/android/unpacked/com.sandlotgames.snailmail.1/lib/{abi}/libsnailmail.so"
    ).read_bytes()
    data = json.loads((args.inventory / f"{key}-raw.json").read_text())
    assert hashlib.sha256(body).hexdigest() == data["file_sha256"]
    byname = {s["name"]: s for s in data["symbols"] if s["type"] == 2}
    byaddr = collections.defaultdict(set)
    for s in data["symbols"]:
        if s["type"] == 2 and s["section"] != 0:
            byaddr[s["address"]].add(s["name"])
    mappings = sorted(
        {
            (s["address"], s["name"].split(".")[0])
            for s in data["symbols"]
            if s["name"].split(".")[0] in ["$a", "$d", "$t"]
        }
    )

    def read(address, count, data=data, body=body):
        section = next(
            s
            for s in data["sections"]
            if s["address"] <= address and address + count <= s["address"] + s["size"]
        )
        offset = section["offset"] + address - section["address"]
        return body[offset : offset + count]

    lines = ["; ELF link-time virtual addresses. $d ranges are literal data."]
    for name in ["_Z4Sqrtf", "_ZN11tQuaternianC1ERK7tMatrix", "_ZN11cRGameInput2AIEv"]:
        symbol = byname[name]
        start = symbol["address"]
        end = start + symbol["size"]
        lines.append(f"\n{name} {start:08x} size {symbol['size']}")
        mode = max((a, m) for a, m in mappings if a <= start)[1]
        bounds = (
            [(start, mode)]
            + [(a, m) for a, m in mappings if start < a < end]
            + [(end, "end")]
        )
        for (address, mode), (stop, _) in pairwise(bounds):
            payload = read(address, stop - address)
            if mode == "$d":
                assert len(payload) % 4 == 0
                for n in range(0, len(payload), 4):
                    word = struct.unpack_from("<I", payload, n)[0]
                    lines.append(
                        f"{address + n:08x} {payload[n : n + 4].hex()} .word 0x{word:08x}"
                    )
                continue
            assert mode == "$a"
            decoded = list(Cs(CS_ARCH_ARM, CS_MODE_ARM).disasm(payload, address))
            assert sum(i.size for i in decoded) == len(payload)
            for i in decoded:
                annotation = ""
                if i.mnemonic in ["b", "bl"] and i.op_str.startswith("#0x"):
                    target = int(i.op_str[1:], 16)
                    annotation = (
                        " " + ",".join(sorted(byaddr[target]))
                        if target in byaddr
                        else ""
                    )
                lines.append(
                    f"{i.address:08x} {i.bytes.hex()} {i.mnemonic} {i.op_str}{annotation}"
                )
    (args.out / f"{key}-native.asm").write_text("\n".join(lines) + "\n")
    print(key, "verified complete decoding with ELF mapping symbols")
