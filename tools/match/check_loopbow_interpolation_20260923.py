"""Recompile LoopBow and audit the sole remaining literal byte."""

import copy
import dataclasses
import hashlib
import json
from pathlib import Path

from check_cage_loopbow_owners_20260921 import verify

from snail import match

ROOT = Path(__file__).resolve().parents[2]
SCRATCH = ROOT / "tools/match/scratches/initialize_loopbow_path_template_pair"
RECEIPT = ROOT / "tools/match/loop-circle-owners-20260921.json"
SOURCE_SHA256 = "7b603a9ce3d2faeb84d64a6c0f30b98aea44400c0c97a76296554763e3231242"


def main() -> None:
    source = (SCRATCH / "scratch.cpp").read_bytes()
    assert hashlib.sha256(source).hexdigest() == SOURCE_SHA256
    previous = json.loads(RECEIPT.read_text())["proofs"][
        "initialize_loopbow_path_template_pair"
    ]
    assert verify(previous) == previous["expected"]

    config = match.load_scratch_config(SCRATCH)
    obj_path = match.compile_scratch(config)
    manifest = match.load_function_symbol_manifest(
        match.DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH
    )
    result = match.run_match(
        obj_path=obj_path,
        function_name=config.function,
        end_va=config.end_va,
        symbol_name=config.symbol,
        manifest=manifest,
        image_path=ROOT / manifest.primary_target,
    )
    function = match.extract_object_function(
        match.parse_coff_object(obj_path.read_bytes()),
        config.symbol or config.function,
        reference_manifest=match.load_default_reference_symbol_manifest(),
    )
    assert result.ratio == 1.0
    assert result.target_instruction_count == result.candidate_instruction_count == 796
    assert result.instruction_prefix_count == 796
    assert result.masked_operand_audit.ok_count == 63
    assert result.masked_operand_audit.problem_count == 0
    assert not result.body_byte_exact and not result.exact

    proof = copy.deepcopy(previous)
    proof["retained"]["candidate_hex"] = function.data.hex()
    proof["retained"]["relocations"] = [
        dataclasses.asdict(entry) for entry in function.relocation_references
    ]
    proof["retained"]["references"] = {
        "entries": [
            dataclasses.asdict(entry) for entry in result.masked_operand_audit.entries
        ]
    }
    proof["retained"]["measured"].update(
        target_instructions=result.target_instruction_count,
        candidate_instructions=result.candidate_instruction_count,
        body_byte_exact=result.body_byte_exact,
    )
    audit = verify(proof)
    assert audit["body_bytes"] == 2939
    assert audit["padding_bytes"] == 5
    assert audit["audited_relocations"] == 63
    assert audit["positional_reference_instructions"] == 63
    assert audit["literal_local_branches"] == 28
    assert audit["unequal_literal_offsets"] == [809]
    native = bytes.fromhex(proof["retained"]["native_hex"])
    assert (native[809], function.data[809]) == (0x03, 0x18)

    for corruption in ("body", "reference", "relocation", "padding"):
        bad = copy.deepcopy(proof)
        if corruption == "reference":
            bad["retained"]["references"]["entries"][0]["target_references"][0][
                "value"
            ] ^= 1
        elif corruption == "relocation":
            bad["retained"]["relocations"][0]["addend"] ^= 1
        else:
            data = bytearray.fromhex(bad["retained"]["candidate_hex"])
            data[20 if corruption == "body" else -1] ^= 1
            bad["retained"]["candidate_hex"] = data.hex()
        try:
            assert verify(bad) == audit
        except AssertionError:
            pass
        else:
            raise AssertionError(f"Accepted {corruption} corruption")

    print(json.dumps(audit, sort_keys=True))


if __name__ == "__main__":
    main()
