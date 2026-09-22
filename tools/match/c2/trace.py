"""Use the sibling Crimson preserving C2 observer with Snail compilation and metrics."""

import argparse
import importlib.util
import json
import sys
import types
from dataclasses import dataclass
from pathlib import Path

from snail import match as m

CRIMSON = Path(m.__file__).resolve().parents[3] / "crimson"


@dataclass(frozen=True, slots=True)
class Config(m.ScratchConfig):
    source: str = "scratch.cpp"


def load_config(directory):
    c = m.load_scratch_config(directory)
    return Config(**{field: getattr(c, field) for field in c.__dataclass_fields__})


def compile_scratch(c, force=False):
    # Traces freeze the source into new directories, so no old build can be reused.
    if force and (c.directory / "build").exists():
        raise ValueError("Expected a fresh frozen source directory")
    return m.compile_scratch(c)


package = types.ModuleType("_snail_crimson_c2")
package.__path__ = []
sys.modules[package.__name__] = package
facade = types.ModuleType(package.__name__ + ".match")
facade.DEFAULT_MATCH_ROOT = CRIMSON / "tools/match"
facade.REPO_ROOT = CRIMSON
facade.load_scratch_config = load_config
facade.compile_scratch = compile_scratch
facade.parse_coff_object = m.parse_coff_object
sys.modules[facade.__name__] = facade


def imported(name):
    spec = importlib.util.spec_from_file_location(
        package.__name__ + "." + name, CRIMSON / "src/crimson" / (name + ".py")
    )
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


replay = imported("match_c2_replay")
c2 = imported("match_c2")


def metrics(config, object_path):
    manifest = m.load_function_symbol_manifest(m.DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH)
    result = m.run_match(
        obj_path=object_path,
        function_name=config.function,
        end_va=config.end_va,
        symbol_name=config.symbol,
        manifest=manifest,
        image_path=Path(m.__file__).resolve().parents[2] / manifest.primary_target,
    )
    return {
        "ratio": result.ratio,
        "target_instructions": result.target_instruction_count,
        "candidate_instructions": result.candidate_instruction_count,
        "prefix_instructions": result.instruction_prefix_count,
        "references_ok": result.masked_operand_audit.ok_count,
        "reference_problems": result.masked_operand_audit.problem_count,
        "exact": result.exact,
        "body_byte_exact": result.body_byte_exact,
    }


replay.function_metrics = metrics

EARLY_ADDRESS_HOOKS = (
    (0x58147, 0x592F),
    (0x5815A, 0x18EAF),
    (0x5817A, 0x12B1A),
    (0x5818F, 0x53DE),
    (0x581A4, 0xFC45),
    (0x581B2, 0xFCDA),
    (0x581BE, 0x448F),
    (0x581C5, 0x12DCB),
    (0x581CC, 0x12F4E),
    (0x581DB, 0x12FAA),
    (0x581EE, 0x130CB),
    (0x581FC, 0xFCDA),
)


def trace(scratch, out, *, passes_only=False, early_addresses=False):
    """Retain Crimson's observer and verification; compile and measure with Snail."""
    config = load_config(scratch.resolve())
    if m.scratch_translation_unit(config):
        raise ValueError(
            "Trace a standalone scratch; translation units need explicit freezing"
        )
    # Both the normal Snail driver and the Crimson capture/replay helpers must
    # use the same compiler bundle. Do not silently replace a scratch's profile.
    if config.compiler != "msvc6.5":
        raise ValueError("Only the pinned msvc6.5 profile is supported")
    for name in ("CL.EXE", "C1.DLL", "C1XX.DLL", "C2.DLL", "MSPDB60.DLL", "LINK.EXE"):
        local = m.DEFAULT_MATCH_ROOT / "compilers/msvc6.5/Bin" / name
        if local.read_bytes() != (replay.COMPILER / "Bin" / name).read_bytes():
            raise ValueError(
                f"Compiler bundle differs between Snail and Crimson: {name}"
            )
    dependency_hash = m.scratch_dependency_sha256(config)
    source_hash = replay.sha((scratch / "scratch.cpp").read_bytes())
    loader = c2.load_profile
    profile = loader()  # Check the original C2 hash before selecting diagnostic hooks.
    if early_addresses:
        profile = {
            **profile,
            "name": profile["name"] + "-early-addresses",
            "hooks": [
                {"site": a, "target": b, "return": False}
                for a, b in EARLY_ADDRESS_HOOKS
            ],
        }
        c2.load_profile = lambda: profile
    try:
        result = c2.trace(scratch, out, passes_only=passes_only)
    finally:
        c2.load_profile = loader
    events = c2.read_verified(out)
    if source_hash != result[
        "source_sha256"
    ] or dependency_hash != m.scratch_dependency_sha256(config):
        raise ValueError("Snail build inputs changed during observation")
    result["snail_adapter_sha256"] = replay.sha(Path(__file__).read_bytes())
    result["snail_dependency_sha256"] = dependency_hash
    result["snail_inputs"] = {
        str(p): replay.sha(p.read_bytes())
        for p in [Path(m.__file__), m.DEFAULT_MATCH_ROOT / "cl.sh"]
    }
    result["early_addresses"] = early_addresses
    (out / "snail-receipt.json").write_text(json.dumps(result, indent=2) + "\n")
    return result, events


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("scratch", type=Path)
    parser.add_argument("--out", required=True, type=Path)
    parser.add_argument("--passes-only", action="store_true")
    parser.add_argument(
        "--early-addresses",
        action="store_true",
        help="Observe the 12 earlier expression-lowering boundaries",
    )
    args = parser.parse_args()
    result, events = trace(
        args.scratch,
        args.out,
        passes_only=args.passes_only,
        early_addresses=args.early_addresses,
    )
    print(
        json.dumps(
            {
                "out": str(args.out),
                "events": len(events),
                "metrics": result["metrics"],
                "whole_coff_equal_except_timestamp": True,
            },
            indent=2,
        )
    )


if __name__ == "__main__":
    main()
