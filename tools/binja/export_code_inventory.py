"""Run through `bn py --script`; reads the current view without changing it."""

import hashlib


def merge_ranges(ranges):
    merged = []
    for start, end in sorted(ranges):
        if merged and start <= merged[-1][1]:
            merged[-1][1] = max(end, merged[-1][1])
        else:
            merged.append([start, end])
    return merged

# PE sections only; omit Binary Ninja's synthetic imports/builtins.
sections = [
    s for s in bv.sections.values()
    if s.semantics == bn.SectionSemantics.ReadOnlyCodeSectionSemantics
]
result = {
    "schema_version": 1,
    "tool": "Binary Ninja",
    "tool_version": bn.core_version(),
    "sections": [
        {
            "name": s.name,
            "start": s.start,
            "end": s.end,
            "sha256": hashlib.sha256(bv.read(s.start, s.end - s.start)).hexdigest(),
        }
        for s in sorted(sections, key=lambda s: s.start)
    ],
    "functions": [
        {
            "start": f.start,
            "name": f.name,
            "ranges": merge_ranges((b.start, b.end) for b in f.basic_blocks),
        }
        for f in sorted(bv.functions, key=lambda f: f.start)
        if any(s.start <= f.start < s.end for s in sections)
    ],
}
