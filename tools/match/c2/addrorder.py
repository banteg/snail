"""Report how VC6 C2 orders the two registers of `[a + b + disp]` addresses (diagnostic only).

C2 sorts the operands of every commutative node by a packed cost, descending
unsigned. For two symbol operands the cost is `0x10000 | hash(symbol)`, and
the hash comes from the symbol record's slot id (address-order.md). The first
operand of the address sum becomes the SIB base, the second the index. This
tool traces one scratch or overlay through Crimson's preserving observer. It
captures the symbol record behind each symbol operand and every symbol-record
allocation. It then lists each two-operand address sum with each operand's
class, slot id and cost, and, for temporaries, their position n after the
first CSE slot C0. Finally it lists the matcher's encoded differences and
marks base/index swaps.

`--nodes LINE` also lists every commutative add/mul on one source line with
its operands in sorted order. For x87 arithmetic the first operand is the
one loaded (`fld`), the second becomes the memory or `st(i)` operand
(x87-order.md).

    uv run tools/match/c2/addrorder.py initialize_loopout_path_template_pair \
        [--source overlay.cpp] [--line N] [--nodes LINE] [--out DIR]
"""

import argparse
import json
import re
import struct
import sys
import tempfile
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import trace as t

import rotation as rot

from snail import match as m

c2 = t.c2

# C2.DLL RVAs (image base 0x10700000), pinned by the profile's C2 SHA-256.
FUNCTION_ENTRY_HOOK = {"site": 0x581EE, "target": 0x130CB, "return": False}
# Entry of the pass after the early expression passes; operand order is final.
ADDRESS_PASS_HOOK = {"site": 0x58249, "target": 0x281CD, "return": False}

# The only CALLs of the symbol-record allocator C2+0x17eb: temporaries (0x2afa,
# 0x10038), CSE/induction temporaries (0x7ec1), inline copies (0x3c34),
# IL symbols (0x1db6b) and the per-function sentinel (0x1ba48).
ALLOCATOR_SITES = (0x2AFA, 0x7EC1, 0x10038, 0x3C34, 0x1DB6B, 0x1BA48)
ALLOCATOR = 0x17EB
CSE_CLASS = 15  # allocation class of pool E, whose records become class 3

ADD = 0x16D
SUB = 0x16E
DISPLACEMENT_SIGN = {ADD: 1, SUB: -1}  # sum +/- constant before the access
SYMBOL_KINDS = (2, 3, 4)
CLASSES = {3: "temp", 4: "local", 5: "param"}
INDUCTION_FLAG = 0x2000000  # symbol +4 flag on strength-reduced induction temps

# The stock observer copies 16 words of the temporary behind kind-1 operands.
# Also copy the symbol record behind symbol operands (12 words) plus four
# words of its storage descriptor (+0x0).
# For memory operands (kind 6) copy +0x1c..+0x3c, which include the
# displacement (+0x24) and address operand (+0x28), and that operand's kind,
# symbol (+0x14) and temporary (+0x18), plus that symbol's id and class.
STOCK_CAPTURE = """                    if (*(unsigned char *)(op+8)==1) {
                        unsigned long temp=*(unsigned long *)(op+0x18), q;
                        if (temp) for(q=0;q<16;++q) record[at+1+k*23+7+q]=*(unsigned long *)(temp+q*4);
                    }
"""
SYMBOL_CAPTURE = """                    if (*(unsigned char *)(op+8)>=2 && *(unsigned char *)(op+8)<=4) {
                        unsigned long symbol=*(unsigned long *)(op+0x14), q;
                        if (symbol) for(q=0;q<12;++q) record[at+1+k*23+7+q]=*(unsigned long *)(symbol+q*4);
                        if (symbol && *(unsigned long *)symbol) for(q=0;q<4;++q) record[at+1+k*23+19+q]=*(unsigned long *)(*(unsigned long *)symbol+q*4);
                    }
                    if (*(unsigned char *)(op+8)==6) {
                        unsigned long child=*(unsigned long *)(op+0x28), q;
                        for(q=0;q<9;++q) record[at+1+k*23+7+q]=*(unsigned long *)(op+0x1c+q*4);
                        if (child) {
                            record[at+1+k*23+16]=*(unsigned char *)(child+8);
                            record[at+1+k*23+17]=*(unsigned long *)(child+0x14);
                            record[at+1+k*23+18]=*(unsigned long *)(child+0x18);
                            if (*(unsigned char *)(child+8)>=2 && *(unsigned char *)(child+8)<=4 && *(unsigned long *)(child+0x14)) {
                                record[at+1+k*23+19]=*(unsigned long *)(*(unsigned long *)(child+0x14)+0x1c);
                                record[at+1+k*23+20]=*(unsigned long *)(*(unsigned long *)(child+0x14)+4);
                            }
                        }
                    }
"""


# Allocation records: {phase, class (entry) or slot id (return)}. Phases
# below 100 are allocator entries, 100+ returns; the two pass hooks write a
# marker 1000+phase so allocations can be placed relative to them.
RECORDER = r"""
static HANDLE alloc_file;
static void alloc_observe(unsigned long phase, unsigned long *registers)
{
    unsigned long rec[2];
    DWORD written;
    rec[0] = phase;
    if (phase >= 1000) rec[1] = 0;
    else if (phase >= 100) rec[1] = registers[7] ? ((unsigned long *)registers[7])[7] : 0xffffffff;
    else rec[1] = registers[6] & 0xff;
    if (!WriteFile(alloc_file, rec, sizeof(rec), &written, 0) || written != sizeof(rec))
        ExitProcess(74);
}
"""
FIRST_ALLOCATOR_HOOK = 2


def observer(profile, stock_source):
    source = stock_source(profile)
    anchors = (
        STOCK_CAPTURE,
        "    unsigned long first, node, count = 0, record[742], op, side, j, k, at;\n",
        "    trace_file = CreateFileA(",
        "    CloseHandle(trace_file);",
        "static void __cdecl observe(",
    )
    for anchor in anchors:
        if source.count(anchor) != 1:
            raise ValueError(f"Unexpected Crimson observer template near {anchor!r}")
    source = source.replace(STOCK_CAPTURE, STOCK_CAPTURE + SYMBOL_CAPTURE)
    # Truncate operand chains longer than the stock 16-entry snapshot instead
    # of aborting; only the recorded diagnostics change.
    source = source.replace("if(op) ExitProcess(98);", "")
    source = source.replace(anchors[4], RECORDER + anchors[4])
    source = source.replace(
        anchors[1],
        anchors[1]
        + f"    if (phase % 100 >= {FIRST_ALLOCATOR_HOOK}) {{ alloc_observe(phase, registers); return; }}\n"
        + "    alloc_observe(phase + 1000, registers);\n",
    )
    source = source.replace(
        anchors[2],
        '    alloc_file = CreateFileA("alloc.bin", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);\n'
        "    if (alloc_file == INVALID_HANDLE_VALUE) ExitProcess(73);\n" + anchors[2],
    )
    return source.replace(anchors[3], "    CloseHandle(alloc_file);\n" + anchors[3])


def run_observer(scratch, out):
    """Preserving run: whole-COFF identity and matcher metrics are checked by the adapter."""
    stock_profile, stock_source = c2.load_profile, c2.observer_source
    profile = stock_profile()
    hooks = [FUNCTION_ENTRY_HOOK, ADDRESS_PASS_HOOK] + [
        {"site": site, "target": ALLOCATOR, "return": True} for site in ALLOCATOR_SITES
    ]
    profile = dict(profile, name=profile["name"] + "-address-order", hooks=hooks)
    c2.load_profile = lambda: profile
    c2.observer_source = lambda p: observer(p, stock_source)
    try:
        result, events = t.trace(scratch, out)
    finally:
        c2.load_profile, c2.observer_source = stock_profile, stock_source
    return result, events, decode_allocations((out / "observed/alloc.bin").read_bytes())


def decode_allocations(data):
    """Allocated slots in order, each with its class and whether it follows function entry."""
    rows, pending, entered = [], None, False
    for phase, value in struct.iter_unpack("<2I", data):
        if phase >= 1000:
            entered = entered or phase == 1000 + 0
            continue
        if phase < 100:
            if pending is not None:
                raise ValueError("Allocator entry without return")
            pending = value
            continue
        if pending is None:
            raise ValueError("Allocator return without entry")
        rows.append({"id": value, "class": pending, "after_entry": entered})
        pending = None
    if pending is not None:
        raise ValueError("Truncated allocation trace")
    return rows


def cse_origin(allocations):
    """C0 (first CSE slot after function entry) and each CSE slot's creation index."""
    fresh = [
        a["id"] for a in allocations if a["after_entry"] and a["class"] == CSE_CLASS
    ]
    if not fresh:
        return None, {}
    return fresh[0], {ident: n for n, ident in enumerate(fresh)}


def symbol_hash(kind, record):
    """Low 16 bits of the operand cost, re-derived from the symbol record (C2+0xdb59)."""
    ident = record[7]
    if record[1] & 0xFF == 3 and kind in (1, 2):
        return (ident << 6) & 0xFFFF
    folded = (ident >> 16) ^ (ident & 0xFFFF)
    if kind == 3:
        return folded
    signed = folded << 5 & 0xFFFFFFFF
    signed = signed - (1 << 32) if signed & 0x80000000 else signed
    return ((signed >> 16) ^ ((folded & 0x7FF) << 5)) & 0xFFFF


def describe(operand):
    record = operand["temp_words"]
    if record[5]:
        raise ValueError("Symbol aliases another operand; hash rule not modelled")
    ident, flags = record[7], record[1]
    klass = CLASSES.get(flags & 0xFF, f"class{flags & 0xFF}")
    if flags & 0xFF == 3 and flags & INDUCTION_FLAG:
        klass = "iv-temp"
    cost = operand["raw"][3]
    if cost & 0xFFFF != symbol_hash(operand["kind"], record):
        raise ValueError(f"Hash rule mismatch for slot {ident:#x}: cost {cost:#x}")
    return {
        "class": klass,
        "id": ident,
        "cost": cost,
    }


def memory_uses(node, temp):
    """'load'/'store' for each memory operand of `node` addressed by `temp`."""
    uses = []
    for side, name in (("src", "load"), ("dst", "store")):
        for operand in node[side]:
            words = operand["temp_words"]
            if operand["kind"] == 6 and words[9] == 1 and words[11] == temp:
                uses.append(name)
    return uses


def address_sums(event):
    """Every ADD of two symbol operands that addresses memory.

    Sums whose operand is an expression or a reloaded member are ordered by
    expression cost (node count and depth), not by slot, and are not listed.
    """
    nodes = event["nodes"]
    users = {}
    for index, node in enumerate(nodes):
        for operand in node["src"]:
            if operand["kind"] == 1:
                users.setdefault(operand["raw"][6], []).append(index)
    rows = []
    for index, node in enumerate(nodes):
        if node["op"] != ADD or len(node["src"]) != 2 or len(node["dst"]) != 1:
            continue
        if any(o["kind"] not in SYMBOL_KINDS for o in node["src"]):
            continue
        if node["dst"][0]["kind"] != 1:
            continue  # a named sum (strength-reduced address), not an address
        first, second = (describe(o) for o in node["src"])
        if first["cost"] < second["cost"]:
            raise ValueError("Operands are not in descending cost order")
        temp = node["dst"][0]["raw"][6]
        accesses = []
        for user in users.get(temp, []):
            consumer = nodes[user]
            accesses += [(0, use) for use in memory_uses(consumer, temp)]
            constants = [o["raw"][6] for o in consumer["src"] if o["kind"] == 7]
            sign = DISPLACEMENT_SIGN.get(consumer["op"])
            if sign and constants and consumer["dst"][0]["kind"] == 1:
                inner = consumer["dst"][0]["raw"][6]
                for follow in users.get(inner, []):
                    accesses += [
                        (sign * constants[0], use)
                        for use in memory_uses(nodes[follow], inner)
                    ]
        if not accesses:
            continue  # arithmetic, not an address
        rows.append(
            {
                "node": index,
                "label": node["line"],
                "first": first,
                "second": second,
                "accesses": sorted(set(accesses)),
                "tie": first["cost"] == second["cost"],
            }
        )
    return rows


COMMUTATIVE = {ADD: "add", 0x16F: "mul"}


def operand_brief(operand):
    """Kind, cost and identity of any operand, for the per-line node listing."""
    kind, raw, words = operand["kind"], operand["raw"], operand["temp_words"]
    cost = f"cost {raw[3]:#x}"
    if kind in SYMBOL_KINDS:
        # Costs are only refreshed where C2 sorted the node; 0 means stale.
        klass = CLASSES.get(words[1] & 0xFF, f"class{words[1] & 0xFF}")
        return f"{klass} slot {words[7]:#x} {cost}"
    if kind == 6:
        if words[9] in SYMBOL_KINDS:
            klass = CLASSES.get(words[13] & 0xFF, f"class{words[13] & 0xFF}")
            base = f"{klass} slot {words[12]:#x}"
        else:
            base = f"expr temp {words[11] & 0xFFFF:04x}"
        return f"memory [{base}] {cost}"
    if kind == 1:
        return f"expr temp {raw[6] & 0xFFFF:04x}"
    if kind == 7:
        return f"const {raw[6]:#x}"
    return f"kind {kind} {cost}"


def line_nodes(event, label):
    """Commutative nodes on one C2 line label, operands in sorted order."""
    rows = []
    for index, node in enumerate(event["nodes"]):
        if node["line"] != label or node["op"] not in COMMUTATIVE:
            continue
        rows.append(
            f"{index:5d} {COMMUTATIVE[node['op']]}  "
            + "  >  ".join(operand_brief(o) for o in node["src"])
        )
    return rows


def body_line(source_text, symbol):
    """C2 line labels count from the line before the function body's opening brace."""
    lines = source_text.splitlines()
    start = rot.definition_line(source_text, symbol)
    for number in range(start, len(lines) + 1):
        text = lines[number - 1]
        if "{" in text:
            return number - 1 if text.strip() == "{" else number
    raise ValueError("Cannot find the function body")


SIB = re.compile(r"\[(\w+) \+ (\w+)")


def sib_differences(result):
    rows = []
    for difference in result.encoded_body_differences:
        target = SIB.search(difference["target_asm"])
        candidate = SIB.search(difference["candidate_asm"])
        swapped = (
            target is not None
            and candidate is not None
            and target.groups() == candidate.groups()[::-1]
        )
        rows.append(
            dict(
                difference,
                swapped=swapped,
            )
        )
    return rows


def operand_text(o):
    n = f"  n={o['n']}" if o.get("n") is not None else ""
    return f"{o['class']:8} slot {o['id']:#6x}  cost {o['cost']:#x}{n}"


def report(rows, differences, base, source_lines, only_line, c0):
    if c0 is not None:
        print(
            f"C0 (first CSE temporary slot): {c0:#x}; temporaries hash (slot mod 0x400) * 0x40"
        )
    print(
        f"{'line':>5} {'node':>4}  {'access':14} first = SIB base / second = SIB index"
    )
    for row in rows:
        line = base + row["label"]
        row["line"] = line
        if only_line is not None and line != only_line:
            continue
        access = (
            ",".join(
                f"{use}{disp:+#x}" if disp else use for disp, use in row["accesses"]
            )
            or "-"
        )
        tie = "  (equal costs: stable order)" if row["tie"] else ""
        text = (
            source_lines[line - 1].strip()[:70] if 0 < line <= len(source_lines) else ""
        )
        print(
            f"{line:5d} {row['node']:4d}  {access:14} {text}\n"
            f"{'':27}first  {operand_text(row['first'])}\n"
            f"{'':27}second {operand_text(row['second'])}{tie}"
        )
    if differences:
        print("\nencoded differences (native swaps base and index where marked):")
    for d in differences:
        kind = "swapped" if d["swapped"] else "other"
        print(
            f"  +{d['offset']:#x} {kind}\n"
            f"    target    {d['target_asm']}\n    candidate {d['candidate_asm']}"
        )


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("scratch", help="scratch name or directory")
    parser.add_argument(
        "--source", type=Path, help="overlay source replacing scratch.cpp"
    )
    parser.add_argument(
        "--out", type=Path, help="new output directory (default: a temporary one)"
    )
    parser.add_argument("--line", type=int, help="only report sums on this source line")
    parser.add_argument(
        "--nodes",
        type=int,
        metavar="LINE",
        help="also list every commutative add/mul on this source line, operands in sorted order",
    )
    parser.add_argument("--json", action="store_true", help="print rows as JSON")
    args = parser.parse_args()
    scratch = Path(args.scratch)
    if not scratch.is_dir():
        scratch = m.DEFAULT_MATCH_ROOT / "scratches" / args.scratch
    out = args.out or Path(tempfile.mkdtemp(prefix="c2addr-")) / "trace"
    work = rot.prepare(scratch, args.source, out.parent / (out.name + "-input"))
    result, events, allocations = run_observer(work, out)
    c0, creation = cse_origin(allocations)
    (event,) = [e for e in events if e["target_rva"] == ADDRESS_PASS_HOOK["target"]]
    config = m.load_scratch_config(work)
    source_text = (work / "scratch.cpp").read_text()
    base = body_line(source_text, config.symbol or config.function)
    object_path = m.compile_scratch(config)
    rows = address_sums(event)
    for row in rows:
        for operand in (row["first"], row["second"]):
            operand["n"] = (
                creation.get(operand["id"])
                if operand["class"] in ("temp", "iv-temp")
                else None
            )
    manifest = m.load_function_symbol_manifest(m.DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH)
    match = m.run_match(
        obj_path=object_path,
        function_name=config.function,
        end_va=config.end_va,
        symbol_name=config.symbol,
        manifest=manifest,
        image_path=m.REPO_ROOT / manifest.primary_target,
    )
    differences = sib_differences(match)
    (out / "address-order.json").write_text(
        json.dumps({"c0": c0, "sums": rows, "differences": differences}, indent=1)
        + "\n"
    )
    if args.json:
        print(
            json.dumps({"c0": c0, "sums": rows, "differences": differences}, indent=1)
        )
        return
    print(f"trace: {out}  metrics: {json.dumps(result['metrics'])}")
    report(rows, differences, base, source_text.splitlines(), args.line, c0)
    if args.nodes is not None:
        print(f"\ncommutative nodes on line {args.nodes} (first operand is loaded):")
        for row in line_nodes(event, args.nodes - base):
            print(row)


if __name__ == "__main__":
    main()
