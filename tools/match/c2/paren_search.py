"""Search redundant parentheses that move C2 scheduler window cuts (diagnostic only).

Each parenthesized non-leaf float expression adds one IL_FROUND pseudo-tuple:
it emits no code but counts toward the /G5 scheduler's 81-tuple window and
raises node heights (see scheduler.md). Wrapping the right terms can therefore
reorder code without changing it. Both 2026-10-05 msvc6.3 matches
(explode_slug_hazard, release_snail_weapons) came from such wraps.

Candidate terms are assignment right-hand sides plus operator-bearing call
arguments and group contents. Textually identical terms form one group and are
wrapped together, as a macro body or a repeated idiom would be. The search
tries every combination of up to --groups groups at depths 1..--depth.

    uv run tools/match/c2/paren_search.py release_snail_weapons [--groups 3] \
        [--depth 2] [--limit 4000] [--out /private/tmp/paren-hits]

Prints one JSON line per function: the baseline, the best variant and every
byte-exact one. With --out, the best variant's source is written there. A hit
is only a lead: keep it if the grouping reads as plausible original source.
"""

import argparse
import itertools
import json
import re
from collections import defaultdict
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path

from snail import match as m

ASSIGN = re.compile(
    r"(?<![=!<>+\-*/%&|^])(=|\+=|-=|\*=|/=)(?!=)\s*([^;{}]+?);", re.DOTALL
)
OPERATOR = re.compile(r"[+\-*/]")
LEAF = re.compile(r"(?:[\w.\[\]]|->)+|-?\d+(\.\d*)?f?|0x[0-9a-fA-F]+")
KEYWORD_BEFORE_PAREN = re.compile(r"\b(if|while|for|switch|return|sizeof)$")


def wrappable(text):
    """Arithmetic or a cast: terms whose parentheses can add an IL_FROUND."""
    return (
        OPERATOR.search(text.replace("->", "")) or text.startswith("(")
    ) and not LEAF.fullmatch(text)


def body_start(source, config):
    """Offset of the target function's opening brace."""
    name = config.symbol or config.function
    method = re.match(r"\?(\w+)@", name).group(1) if name.startswith("?") else name
    for hit in re.finditer(r"\b" + re.escape(method) + r"\s*\(", source):
        brace, semicolon = source.find("{", hit.start()), source.find(";", hit.start())
        if brace != -1 and (semicolon == -1 or brace < semicolon):
            return brace
    raise ValueError(f"no body for {name}")


def closing_paren(source, index):
    depth = 0
    for position in range(index, len(source)):
        depth += {"(": 1, ")": -1}.get(source[position], 0)
        if depth == 0:
            return position
    return -1


def top_level_parts(source, start, end):
    """Comma-separated spans of source[start:end], ignoring nested commas."""
    parts, depth, part_start = [], 0, start
    for position in range(start, end):
        char = source[position]
        if char in "([":
            depth += 1
        elif char in ")]":
            depth -= 1
        elif char == "," and depth == 0:
            parts.append((part_start, position))
            part_start = position + 1
    return [*parts, (part_start, end)]


def trimmed(source, start, end):
    text = source[start:end]
    return start + len(text) - len(text.lstrip()), end - len(text) + len(text.rstrip())


def term_spans(source, start):
    """Spans of wrappable non-leaf terms after start."""
    spans = set()
    for assignment in ASSIGN.finditer(source, start):
        rhs = assignment.group(2).strip()
        if "?" not in rhs and '"' not in rhs and wrappable(rhs):
            spans.add(trimmed(source, *assignment.span(2)))
    for paren in re.finditer(r"\(", source[start:]):
        open_index = start + paren.start()
        close_index = closing_paren(source, open_index)
        inner = source[open_index + 1 : close_index]
        if close_index < 0 or any(char in inner for char in '"{;'):
            continue
        if KEYWORD_BEFORE_PAREN.search(source[:open_index].rstrip()):
            continue
        for part in top_level_parts(source, open_index + 1, close_index):
            span_start, span_end = trimmed(source, *part)
            if wrappable(source[span_start:span_end]):
                spans.add((span_start, span_end))
    return sorted(spans)


def term_groups(source, spans):
    groups = defaultdict(list)
    for span_start, span_end in spans:
        groups[" ".join(source[span_start:span_end].split())].append(
            (span_start, span_end)
        )
    return list(groups.items())


def wrap(source, edits):
    for span_start, span_end, depth in sorted(
        edits, key=lambda edit: (-edit[0], edit[1])
    ):
        source = (
            source[:span_start]
            + "(" * depth
            + source[span_start:span_end]
            + ")" * depth
            + source[span_end:]
        )
    return source


def score(arguments):
    scratch, source = arguments
    status = m.evaluate_source_overlay(m.load_scratch_config(Path(scratch)), source)
    return status.ratio or 0, status.prefix_instructions, status.body_byte_exact


def search(function, *, max_groups, max_depth, limit, jobs, out=None):
    scratch = m.DEFAULT_MATCH_ROOT / "scratches" / function
    source = (scratch / "scratch.cpp").read_text()
    groups = term_groups(
        source, term_spans(source, body_start(source, m.load_scratch_config(scratch)))
    )
    choices = []
    for size in range(1, max_groups + 1):
        for combination in itertools.combinations(range(len(groups)), size):
            for depths in itertools.product(range(1, max_depth + 1), repeat=size):
                choices.append(tuple(zip(combination, depths)))
        if len(choices) > limit:
            choices = [choice for choice in choices if len(choice) < size] or choices[
                :limit
            ]
            break
    variants = [
        wrap(
            source,
            [(*span, depth) for index, depth in choice for span in groups[index][1]],
        )
        for choice in choices
    ]
    with ProcessPoolExecutor(jobs) as executor:
        baseline = score((str(scratch), source))
        rows = list(
            executor.map(score, [(str(scratch), variant) for variant in variants])
        )

    def describe(choice):
        return [[groups[index][0], depth] for index, depth in choice]

    best = max(
        range(len(rows)),
        key=lambda index: (rows[index][2], rows[index][0], rows[index][1]),
    )
    if out:
        Path(out).mkdir(parents=True, exist_ok=True)
        (Path(out) / f"{function}.cpp").write_text(variants[best])
    return {
        "function": function,
        "baseline": baseline,
        "groups": len(groups),
        "tried": len(choices),
        "best": [rows[best], describe(choices[best])],
        "exact": [describe(choice) for choice, row in zip(choices, rows) if row[2]],
    }


def main():
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument("functions", nargs="+")
    parser.add_argument(
        "--groups", type=int, default=3, help="most term groups wrapped at once"
    )
    parser.add_argument(
        "--depth", type=int, default=2, help="deepest redundant paren level"
    )
    parser.add_argument(
        "--limit",
        type=int,
        default=4000,
        help="drop the largest combination size past this",
    )
    parser.add_argument("--jobs", type=int, default=12)
    parser.add_argument(
        "--out", type=Path, help="write each function's best variant here"
    )
    args = parser.parse_args()
    for function in args.functions:
        result = search(
            function,
            max_groups=args.groups,
            max_depth=args.depth,
            limit=args.limit,
            jobs=args.jobs,
            out=args.out,
        )
        print(json.dumps(result), flush=True)


if __name__ == "__main__":
    main()
