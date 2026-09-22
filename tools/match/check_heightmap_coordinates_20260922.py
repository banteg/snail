"""Check the heightmap improvement, including its remaining pointer-base difference."""

import argparse
import concurrent.futures
import copy
import hashlib
import json
from pathlib import Path

import capstone
from check_cage_loopbow_owners_20260921 import verify as verify_bytes
from replay_four_builder_controls_20260912 import reconstruct

ROOT = Path(__file__).resolve().parents[2]
RECEIPT = Path(__file__).with_name("heightmap-coordinates-20260922.json")
FUNCTION = "sample_smtrack_heightmap"


def sha(data):
    return hashlib.sha256(data).hexdigest()


def pointer_region(proof):
    """Prove the two seven-instruction regions access the same bytes in order."""
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    decoded = []
    addresses = []
    for key, bias in (("native_hex", 0), ("candidate_hex", 18)):
        code = bytes.fromhex(proof["retained"][key])
        instructions = list(md.disasm(code[:364], 0))
        decoded.append({i.address: i for i in instructions})
        region = [i for i in instructions if 233 <= i.address < 254]
        assert [(i.mnemonic, i.op_str) for i in region] == [
            ("lea", "eax, [ecx + esi]" if bias == 0 else "eax, [ecx + esi + 0x12]"),
            ("xor", "ecx, ecx"),
            (
                "mov",
                "cl, byte ptr [eax + 0x14]" if bias == 0 else "cl, byte ptr [eax + 2]",
            ),
            ("mov", "dword ptr [esp + 0x2c], ecx"),
            ("xor", "ecx, ecx"),
            ("fild", "dword ptr [esp + 0x2c]"),
            ("mov", "cl, byte ptr [eax + 0x12]" if bias == 0 else "cl, byte ptr [eax]"),
        ]
        # EAX = incoming ECX + ESI + bias. Both byte addresses are affine
        # expressions over the same incoming registers, including 32-bit wrap.
        addresses.append([bias + region[j].operands[1].mem.disp for j in (2, 6)])
    assert addresses == [[20, 18], [20, 18]]
    # Both zero-extend red into ECX, store/fild it, then zero-extend blue.
    # EDX, all other registers, flags, stack writes and x87 effects agree.
    # Only EAX retains the pointer bias; establish its deadness over the CFG.
    masks = {"eax": 0xFFFFFFFF, "ax": 0xFFFF, "al": 0xFF, "ah": 0xFF00}
    ftol_calls = {
        entry["candidate_offset"]
        for entry in proof["retained"]["references"]["entries"]
        if any(r["key"] == "ref:ftol" for r in entry["candidate_references"])
    }
    assert ftol_calls == {33, 178, 191}
    queue = [(254, 0xFFFFFFFF)]
    seen = set()
    instructions = decoded[1]
    while queue:
        offset, taint = queue.pop()
        if (offset, taint) in seen or taint == 0:
            continue
        seen.add((offset, taint))
        insn = instructions[offset]
        reads, writes = insn.regs_access()
        assert all(not (masks.get(insn.reg_name(r), 0) & taint) for r in reads)
        for reg in writes:
            taint &= ~masks.get(insn.reg_name(reg), 0)
        if insn.mnemonic == "call":
            assert offset in ftol_calls
            taint = 0  # The audited float-to-integer helper returns a fresh EAX.
        if insn.mnemonic == "ret":
            continue  # Authored void function; EAX is caller-clobbered.
        if insn.group(capstone.CS_GRP_JUMP):
            queue.append((insn.operands[0].imm, taint))
            if insn.mnemonic == "jmp":
                continue
        queue.append((offset + insn.size, taint))
    return {"same_byte_offsets": addresses[0], "dead_pointer_cfg_states": len(seen)}


def verify(receipt):
    baseline = receipt["baselines"][FUNCTION]
    assert sha(baseline["source"].encode()) == baseline["source_sha256"]
    for control in receipt["controls"]:
        reconstruct(baseline["source"], control)
        assert control["measured"]["error"] is None
        assert control["measured"]["body_byte_exact"] is False
    proof = receipt["proof"]
    assert sha(receipt["retained_source"].encode()) == proof["canonical_source_sha256"]
    assert verify_bytes(proof) == proof["expected"]
    assert pointer_region(proof) == proof["pointer_region"]
    measured = proof["retained"]["measured"]
    assert measured["match_ratio"] == 106 / 109
    assert measured["prefix_instructions"] == 67
    assert measured["candidate_instructions"] == measured["target_instructions"] == 109
    assert measured["references"] == {
        "ok": 13,
        "unresolved": 0,
        "mismatch": 0,
        "unaudited": 0,
    }
    return proof["expected"]


def replay(receipt):
    from snail import match

    for filename, digest in receipt["build_inputs"].items():
        assert sha((ROOT / filename).read_bytes()) == digest, filename
    config = match.load_scratch_config(ROOT / "tools/match/scratches" / FUNCTION)
    keys = (
        "body_byte_exact",
        "code_sha256",
        "match_ratio",
        "target_instructions",
        "candidate_instructions",
        "prefix_instructions",
        "references",
        "error",
    )

    def one(control):
        source = reconstruct(receipt["baselines"][FUNCTION]["source"], control)
        actual = match.scratch_status_payload(
            match.evaluate_source_overlay(config, source)
        )
        assert {k: actual[k] for k in keys} == {
            k: control["measured"][k] for k in keys
        }, control["label"]

    with concurrent.futures.ThreadPoolExecutor(max_workers=6) as pool:
        list(pool.map(one, receipt["controls"]))
    print(f"Recompiled all {len(receipt['controls'])} frozen source controls")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--replay", action="store_true")
    args = parser.parse_args()
    receipt = json.loads(RECEIPT.read_text())
    expected = verify(receipt)
    source = ROOT / "tools/match/scratches" / FUNCTION / "scratch.cpp"
    assert sha(source.read_bytes()) == receipt["proof"]["canonical_source_sha256"]
    for corruption in (
        "body",
        "pointer",
        "reference",
        "relocation",
        "padding",
        "claim",
    ):
        bad = copy.deepcopy(receipt)
        retained = bad["proof"]["retained"]
        if corruption in ("body", "pointer", "padding"):
            data = bytearray.fromhex(retained["candidate_hex"])
            data[{"body": 20, "pointer": 236, "padding": -1}[corruption]] ^= 1
            retained["candidate_hex"] = data.hex()
        elif corruption == "reference":
            retained["references"]["entries"][0]["target_references"][0]["value"] ^= 1
        elif corruption == "relocation":
            retained["relocations"][0]["addend"] ^= 1
        else:
            retained["measured"]["body_byte_exact"] = True
        try:
            verify(bad)
        except (AssertionError, KeyError):
            pass
        else:
            raise AssertionError(f"Accepted corrupt {corruption}")
    print(json.dumps(expected, sort_keys=True))
    print("Validated source recipes, pointer equivalence and six corruption rejections")
    if args.replay:
        replay(receipt)


if __name__ == "__main__":
    main()
