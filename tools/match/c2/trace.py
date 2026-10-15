"""Run Snail scratches through the vendored preserving C2 observer."""

import argparse
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import c2_observer as c2
import c2_replay as replay

from snail import match as m

STOCK_LOADER = c2.load_profile


def trace(scratch, out, *, passes_only=False, early_addresses=False):
    """Preserving observation: whole-COFF identity and matcher metrics are checked."""
    config = m.load_scratch_config(scratch.resolve())
    if m.scratch_translation_unit(config):
        raise ValueError(
            "Trace a standalone scratch; translation units need explicit freezing"
        )
    dependency_hash = m.scratch_dependency_sha256(config)
    source_hash = replay.sha(config.source_path.read_bytes())
    loader = c2.load_profile
    # A caller may already have selected diagnostic hooks; otherwise use the
    # scratch's compiler profile, whose C2 hash is checked before any hook.
    profile = loader() if loader is not STOCK_LOADER else loader(config.compiler)
    if early_addresses:
        profile = {
            **profile,
            "name": profile["name"] + "-early-addresses",
            "hooks": profile["early_address_hooks"],
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
    obj = m.parse_coff_object((out / result["object_paths"][0]).read_bytes())
    result["function_ordinal"] = target_function(
        obj, config.symbol or config.function, events[-1]["function_ordinal"] + 1
    )
    (out / "snail-receipt.json").write_text(json.dumps(result, indent=2) + "\n")
    return result, events


def target_function(obj, name, count):
    """Ordinal of the function `name` among the `count` functions C2 entered.

    C2 compiles a source's functions in order and emits each one as it goes,
    so the n-th function entry is the n-th function symbol in code order. A
    name the object does not resolve falls back to the last function.
    """
    functions = m.object_function_symbols(obj)
    if len(functions) == count:
        try:
            return functions.index(m.find_object_function_symbol(obj, name))
        except ValueError:
            pass
    if count > 1:
        print(
            f"warning: {name!r} is not one of the {count} traced functions; using the last",
            file=sys.stderr,
        )
    return count - 1


def function_events(events, ordinal):
    """The snapshots of function `ordinal`, in hook order."""
    return [e for e in events if e["function_ordinal"] == ordinal]


def function_event(events, ordinal, target_rva):
    """The one snapshot of function `ordinal` at the hook into `target_rva`."""
    (event,) = [
        e for e in function_events(events, ordinal) if e["target_rva"] == target_rva
    ]
    return event


def label_functions(records, is_entry):
    """Pair each side-stream record with the ordinal of the function it falls in.

    Records before the first function entry get -1.
    """
    ordinal = -1
    for record in records:
        ordinal += bool(is_entry(record))
        yield ordinal, record


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
