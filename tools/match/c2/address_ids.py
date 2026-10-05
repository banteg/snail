"""Score a scratch or overlay and list the slot ids behind its SIB orderings (diagnostic only).

Prints the normalized ratio and encoded differences; when the normalized text
matches, also traces the address-order pass and lists each two-symbol address
sum that reaches DISPLACEMENT with its first (SIB base) and second operand's
class, slot id and cost. A run takes a few seconds, so it suits source searches.

    uv run tools/match/c2/address_ids.py initialize_halfpipe_path_template_pair \
        [--source overlay.cpp] [--displacement 0x90]
"""

import argparse
import contextlib
import io
import json
import shutil
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import addrorder as ao
import rotation as rot

from snail import match as m


def address_ids(function, source_text, displacement=None):
    scratch = m.DEFAULT_MATCH_ROOT / "scratches" / function
    matches = []
    status = m.evaluate_source_overlay(
        m.load_scratch_config(scratch), source_text, on_match=matches.append
    )
    result = {
        "ratio": status.ratio,
        "byte_exact": status.body_byte_exact,
        "encoded_differences": [
            hex(d["offset"]) for d in (matches[0].encoded_body_differences if matches else ())
        ],
    }
    if status.ratio != 1.0:
        return result
    work = Path(tempfile.mkdtemp(prefix="snail-ids-"))
    try:
        source = work / "overlay.cpp"
        source.write_text(source_text)
        frozen = rot.prepare(scratch, source, work / "input")
        with contextlib.redirect_stdout(io.StringIO()):
            _, events, allocations, address_pass = ao.run_observer(frozen, work / "trace")
    finally:
        shutil.rmtree(work)
    c0, _ = ao.cse_origin(allocations)
    (event,) = [e for e in events if e["target_rva"] == address_pass]
    result["c0"] = hex(c0) if c0 is not None else None
    result["sums"] = [
        {
            "accesses": [[hex(d), use] for d, use in row["accesses"]],
            **{
                side: [row[side]["class"], hex(row[side]["id"]), hex(row[side]["cost"])]
                for side in ("first", "second")
            },
        }
        for row in ao.address_sums(event)
        if displacement is None or any(d == displacement for d, _ in row["accesses"])
    ]
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("function")
    parser.add_argument("--source", type=Path, help="overlay source replacing scratch.cpp")
    parser.add_argument("--displacement", type=lambda v: int(v, 0), help="only sums addressing this displacement")
    args = parser.parse_args()
    scratch = m.DEFAULT_MATCH_ROOT / "scratches" / args.function
    text = (args.source or scratch / "scratch.cpp").read_text()
    print(json.dumps(address_ids(args.function, text, args.displacement), indent=2))


if __name__ == "__main__":
    main()
