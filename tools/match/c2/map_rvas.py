"""Map C2.DLL RVAs from one VC6 backend to another (diagnostic profile derivation).

A routine is located by its first instructions with absolute addresses and
relative branch targets masked; a CALL site by the masked instructions around
it, among the calls to the mapped routine. Every result prints its context
score so weak matches stay visible.

    uv run tools/match/c2/map_rvas.py msvc6.5 msvc6.3 --profile
    uv run tools/match/c2/map_rvas.py msvc6.5 msvc6.3 --function 0xdb59 --site 0x581ee:0x130cb
"""

import argparse
import collections
import json
import re
from pathlib import Path

import capstone
import pefile

from snail import match as m

HEX = re.compile(r"0x[0-9a-f]+")


class Backend:
    def __init__(self, compiler):
        path = next(
            p for p in (m.DEFAULT_MATCH_ROOT / "compilers" / compiler / "Bin").iterdir()
            if p.name.lower() == "c2.dll"
        )
        pe = pefile.PE(str(path))
        self.base = pe.OPTIONAL_HEADER.ImageBase
        text = next(s for s in pe.sections if s.Name.startswith(b".text"))
        self.data, self.va = text.get_data(), text.VirtualAddress
        self.exports = {e.name.decode(): e.address for e in pe.DIRECTORY_ENTRY_EXPORT.symbols if e.name}
        self.md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        self.tokens = {}
        self.calls = collections.defaultdict(list)
        for offset in range(len(self.data) - 5):
            if self.data[offset] == 0xE8:
                target = self.va + offset + 5 + int.from_bytes(self.data[offset + 1 : offset + 5], "little", signed=True)
                if self.va <= target < self.va + len(self.data):
                    self.calls[target].append(self.va + offset)

    def token(self, insn):
        if (insn.mnemonic == "call" or insn.mnemonic.startswith("j")) and insn.op_str.startswith("0x"):
            return insn.mnemonic + " REL"
        return insn.mnemonic + " " + HEX.sub(
            lambda h: "A" if int(h.group(), 16) >= self.base else h.group(), insn.op_str
        )

    def forward(self, rva, count):
        key = (rva, count)
        if key not in self.tokens:
            offset = rva - self.va
            out = []
            for insn in self.md.disasm(self.data[offset : offset + 16 * count], self.base + rva):
                out.append(self.token(insn))
                if len(out) == count:
                    break
            self.tokens[key] = tuple(out)
        return self.tokens[key]

    def backward(self, rva, count):
        for back in range(16 * count, 0, -1):
            insns = list(self.md.disasm(self.data[rva - back - self.va : rva - self.va], self.base + rva - back))
            if len(insns) >= count and insns[-1].address + insns[-1].size == self.base + rva:
                return tuple(self.token(i) for i in insns[-count:])
        return ()


def map_function(old, new, rva):
    for length in (40, 24, 16, 12):
        signature = old.forward(rva, length)
        hits = [t for t in new.calls if new.forward(t, length) == signature]
        if len(hits) == 1:
            return hits[0], length
    return None, 0


def containing_function(image, rva):
    starts = [t for t in image.calls if t <= rva]
    return max(starts) if starts else None


def map_data(old, new, rva):
    """Map a data RVA through instructions that reference it absolutely.

    Each referencing instruction is located by its index inside its routine;
    the mapped routine's instruction at the same index supplies the operand.
    Returns {new_rva: votes}.
    """
    needle = (old.base + rva).to_bytes(4, "little")
    votes = collections.Counter()
    for offset in range(len(old.data) - 4):
        if old.data[offset : offset + 4] != needle:
            continue
        site = old.va + offset
        start = containing_function(old, site)
        if start is None:
            continue
        mapped, _ = map_function(old, new, start)
        if mapped is None:
            continue
        old_insns = list(old.md.disasm(old.data[start - old.va : site - old.va + 16], old.base + start))
        index = next((i for i, insn in enumerate(old_insns)
                      if insn.address - old.base <= site < insn.address - old.base + insn.size), None)
        if index is None:
            continue
        new_insns = list(new.md.disasm(new.data[mapped - new.va : mapped - new.va + 16 * (index + 2)], new.base + mapped))
        if index >= len(new_insns) or new_insns[index].mnemonic != old_insns[index].mnemonic:
            continue
        delta = site - (old_insns[index].address - old.base)
        raw = bytes(new_insns[index].bytes)[delta : delta + 4]
        if len(raw) == 4:
            value = int.from_bytes(raw, "little") - new.base
            votes[value + 0] += 1
    return votes


def map_site(old, new, site, new_target, width=12):
    before, after = old.backward(site, width), old.forward(site + 5, width)
    scored = sorted(
        (
            sum(a == b for a, b in zip(reversed(before), reversed(new.backward(s, width))))
            + sum(a == b for a, b in zip(after, new.forward(s + 5, width))),
            s,
        )
        for s in new.calls.get(new_target, [])
    )
    return scored[-1] if scored else (0, None), (scored[-2][0] if len(scored) > 1 else None)


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("source")
    parser.add_argument("target")
    parser.add_argument("--function", type=lambda v: int(v, 0), action="append", default=[])
    parser.add_argument("--site", action="append", default=[], help="SITE:TARGET in the source backend")
    parser.add_argument("--data", type=lambda v: int(v, 0), action="append", default=[], help="data RVA")
    parser.add_argument("--profile", action="store_true", help="map every hook in observer/<source>.json")
    args = parser.parse_args()
    old, new = Backend(args.source), Backend(args.target)
    sites = [tuple(int(v, 0) for v in item.split(":")) for item in args.site]
    if args.profile:
        profile = json.loads((Path(__file__).parent / "observer" / f"{args.source}.json").read_text())
        order = profile["address_order"]
        hooks = profile["hooks"] + [order["function_entry"], order["address_pass"]] + profile["early_address_hooks"]
        sites += [(h["site"], h["target"]) for h in hooks]
        sites += [(s, order["allocator"]) for s in order["allocator_sites"]]
        print("invoke", hex(old.exports["_InvokeCompilerPass@12"]), "->", hex(new.exports["_InvokeCompilerPass@12"]))
    for rva in args.data:
        votes = map_data(old, new, rva)
        print(f"data {rva:#x} -> " + (", ".join(f"{v:#x} ({n})" for v, n in votes.most_common(3)) or "unmapped"))
    for rva in args.function:
        mapped, length = map_function(old, new, rva)
        print(f"function {rva:#x} -> {mapped:#x} (signature {length})" if mapped else f"function {rva:#x} -> unmapped")
    for site, target in sites:
        mapped_target, length = map_function(old, new, target)
        if mapped_target is None:
            print(f"site {site:#x}: target {target:#x} unmapped")
            continue
        (score, mapped_site), runner_up = map_site(old, new, site, mapped_target)
        print(f"site {site:#x} -> {mapped_site:#x} score {score}/24 (next {runner_up}); "
              f"target {target:#x} -> {mapped_target:#x} (signature {length})")


if __name__ == "__main__":
    main()
