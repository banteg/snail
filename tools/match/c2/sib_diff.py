"""Diagnostic scale-one SIB reversals in aligned x86 instructions."""

import difflib
from array import array

import capstone

from snail import match as m


def instruction(line):
    return not line.text.startswith(("db ", "db.lookup ", "dd L"))


def decode(md, data, line):
    raw = data[line.offset:line.offset + line.size]
    insn = next(md.disasm(raw, line.offset, 1), None)
    return insn if insn is not None and insn.size == line.size else None


def sib_position(insn):
    # In 32-bit addressing a memory ModR/M with r/m=4 is followed by the
    # SIB. Capstone uses zero register IDs for absent base/index fields.
    if (insn.addr_size == 4 and insn.modrm_offset and insn.modrm >> 6 != 3
            and insn.modrm & 7 == 4 and insn.sib_scale == 1
            and insn.sib_base and insn.sib_index and insn.sib_base != insn.sib_index):
        return insn.modrm_offset + 1
    return None


def prefix_lengths(left, right, missing_left, missing_right):
    """LCS lengths for each prefix, bounded to diagonals an optimum can visit."""
    previous = array("I", [0]) * (missing_left + missing_right + 3)
    yield previous
    for i, token in enumerate(left, 1):
        row = array("I", [0]) * len(previous)
        for j in range(max(1, i - missing_left), min(len(right), i + missing_right) + 1):
            column = j - i + missing_left + 1
            if token == right[j - 1]:
                row[column] = previous[column] + 1
            else:
                row[column] = max(row[column - 1], previous[column + 1])
        yield row
        previous = row


def unambiguous_pairs(left, right):
    """Pairs shared by every longest normalized-equal subsequence alignment."""
    if left == right:
        return [(i, i) for i in range(len(left))], 0
    # SequenceMatcher supplies a cheap lower bound, never the pairing. An
    # optimum can skip at most these many tokens on either side of any pair.
    blocks = difflib.SequenceMatcher(None, left, right, autojunk=False).get_matching_blocks()
    bound = sum(block.size for block in blocks)
    if not bound:
        return [], 0
    n, m = len(left), len(right)
    missing_left, missing_right = n - bound, m - bound
    suffix = list(prefix_lengths(left[::-1], right[::-1], missing_left, missing_right))
    length = suffix[-1][m - n + missing_left + 1]
    pairs = [None] * length
    ambiguous = set()
    for i, (token, row) in enumerate(zip(left, prefix_lengths(left, right, missing_left, missing_right))):
        for j in range(max(0, i - missing_left), min(m, i + missing_right + 1)):
            if token != right[j]:
                continue
            # The pair can occupy rank k in an optimum iff its best prefix
            # and suffix leave precisely one slot for it. Every optimum has
            # one pair per rank, so only a unique candidate is forced.
            rank = row[j - i + missing_left + 1]
            remaining = suffix[n - i - 1][m - n + i - j + missing_left + 1]
            if rank + 1 + remaining == length:
                if pairs[rank] is None:
                    pairs[rank] = (i, j)
                else:
                    ambiguous.add(rank)
    return [pair for k, pair in enumerate(pairs) if k not in ambiguous], len(ambiguous)


def compare(result, target, candidate):
    """Retain audited differences; on partials report only observed SIB swaps.

    Pairs use normalized text including table markers. Encodings are read at
    each side's own offset and ambiguous duplicate alignments are omitted.
    """
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    left, right = result.target_disassembly, result.candidate_disassembly
    audited = {row["offset"]: row for row in result.encoded_body_differences}
    differences = []
    aligned = undecodable = 0
    pairs, ambiguous = unambiguous_pairs(result.target_lines, result.candidate_lines)
    for i, j in pairs:
        a, b = left[i], right[j]
        if not instruction(a):
            continue
        aligned += 1
        a_raw = target[a.offset:a.offset + a.size]
        b_raw = candidate[b.offset:b.offset + b.size]
        existing = audited.get(b.offset)
        if existing is None and a_raw == b_raw:
            continue
        a_ins, b_ins = decode(md, target, a), decode(md, candidate, b)
        if a_ins is None or b_ins is None:
            undecodable += 1
            continue
        a_pos, b_pos = sib_position(a_ins), sib_position(b_ins)
        swap = (a_pos is not None and b_pos is not None
                and a_ins.sib_base == b_ins.sib_index and a_ins.sib_index == b_ins.sib_base)
        if not swap and existing is None:
            continue
        row = dict(existing) if existing else {
            "offset": b.offset, "text": b.text,
            "target": a_raw.hex(), "candidate": b_raw.hex(),
            "target_asm": f"{a_ins.mnemonic} {a_ins.op_str}",
            "candidate_asm": f"{b_ins.mnemonic} {b_ins.op_str}",
        }
        row.update(target_offset=a.offset, candidate_offset=b.offset, swapped=swap)
        if swap:
            row.update(target_sib_offset=a.offset + a_pos, candidate_sib_offset=b.offset + b_pos)
        differences.append(row)
    target_code = sum(map(instruction, left))
    candidate_code = sum(map(instruction, right))
    return {
        "differences": differences,
        "alignment": {
            "mode": "encoded-body" if result.encoded_body_proof is not None else "aligned-sib-only",
            "aligned_instructions": aligned, "undecodable_pairs": undecodable,
            "ambiguous_alignment_ranks": ambiguous,
            "unaligned_target_instructions": target_code - aligned,
            "unaligned_candidate_instructions": candidate_code - aligned,
            "omitted_target_data_lines": len(left) - target_code,
            "omitted_candidate_data_lines": len(right) - candidate_code,
            "omitted_target_tail_bytes": len(target) - (left[-1].offset + left[-1].size if left else 0),
            "omitted_candidate_tail_bytes": len(candidate) - (right[-1].offset + right[-1].size if right else 0),
        },
    }


def from_object(config, path, manifest):
    """Use exactly the observed or intervened COFF selected by this trace."""
    references = m.load_default_reference_symbol_manifest()
    candidate = m.extract_object_function(
        m.parse_coff_object(path.read_bytes()), config.symbol or config.function,
        reference_manifest=references,
    )
    start, end = m.resolve_function_extent(manifest, config.function, config.end_va)
    image = m.load_image(m.REPO_ROOT / manifest.primary_target, manifest.image_base)
    target = image.function_bytes(start, end)
    result = m.match_function(
        target, candidate, image=image, target_va=start, manifest=manifest,
        reference_manifest=references,
    )
    return result, compare(result, target, candidate.data)


def summary(diagnostic):
    a = diagnostic["alignment"]
    swaps = sum(row["swapped"] for row in diagnostic["differences"])
    return (
        f"{a['mode']}: {swaps} SIB swaps in {a['aligned_instructions']} aligned instructions, "
        f"unaligned instructions (target/candidate) {a['unaligned_target_instructions']}/"
        f"{a['unaligned_candidate_instructions']}, omitted data lines "
        f"{a['omitted_target_data_lines']}/{a['omitted_candidate_data_lines']}, "
        f"omitted tail bytes {a['omitted_target_tail_bytes']}/{a['omitted_candidate_tail_bytes']}, "
        f"ambiguous alignment ranks {a['ambiguous_alignment_ranks']}, undecodable pairs {a['undecodable_pairs']}"
    )


def location(row):
    text = f"target +{row['target_offset']:#x}, candidate +{row['candidate_offset']:#x}"
    if row["swapped"]:
        text += f" (SIB +{row['target_sib_offset']:#x}/+{row['candidate_sib_offset']:#x})"
    return text
