"""Inline switch remaps need both byte bounds and real code boundaries."""

from copy import deepcopy
from dataclasses import replace
import struct

import pytest

from snail import match as m
from snail import match_report as report


def lookup_fixture(*, lookup=b'\x00\x01\x00', movzx=False, padding=b'\x90' * 8):
    base = 0x401000
    code = bytearray(bytes.fromhex('83f9007700'))
    code[2] = len(lookup) - 1
    if not movzx:
        code += bytes.fromhex('31d2')
    load = len(code)
    code += bytes.fromhex('0fb69100000000' if movzx else '8a9100000000')
    load_disp = load + (3 if movzx else 2)
    dispatch = len(code)
    code += bytes.fromhex('ff249500000000')
    first = len(code)
    code += bytes.fromhex('31c0c3')
    second = len(code)
    code += bytes.fromhex('b801000000c3')
    default = len(code)
    code += bytes.fromhex('b8ffffffffc3')
    code[4] = default - 5
    jump_offset = len(code)
    destinations = (first, second) + (first,) * max(0, max(lookup) - 1)
    lookup_offset = jump_offset + 4 * len(destinations)
    native = bytearray(code)
    struct.pack_into('<I', native, load_disp, base + lookup_offset)
    struct.pack_into('<I', native, dispatch + 3, base + jump_offset)
    native += struct.pack('<' + 'I' * len(destinations), *(base + x for x in destinations))
    native += lookup + padding
    obj = m.CoffObject(
        sections=(m.CoffSection('.text', bytes(code) + struct.pack(
            '<' + 'I' * len(destinations), *destinations,
        ) + lookup + padding, 0x20, (
            m.CoffRelocation(load_disp, 2, m.IMAGE_REL_I386_DIR32),
            m.CoffRelocation(dispatch + 3, 1, m.IMAGE_REL_I386_DIR32),
            *(m.CoffRelocation(jump_offset + 4 * i, 0, m.IMAGE_REL_I386_DIR32)
              for i in range(len(destinations))),
        )),),
        symbols=(
            m.CoffSymbol(0, '_foo', 0, 1, 0x20, 2),
            m.CoffSymbol(1, '$Ljump', jump_offset, 1, 0, 3),
            m.CoffSymbol(2, '$Llookup', lookup_offset, 1, 0, 3),
        ),
    )
    references = m.ReferenceSymbolManifest('test', (
        m.ReferenceSymbol(base + jump_offset, 'foo_jump', 'jump_table', size=4 * len(destinations)),
        m.ReferenceSymbol(base + lookup_offset, 'foo_lookup', 'lookup_table', size=len(lookup)),
    ))
    offsets = dict(load=load, load_disp=load_disp, dispatch=dispatch, first=first,
                   default=default, jump=jump_offset, lookup=lookup_offset,
                   end=lookup_offset + len(lookup))
    return bytes(native), m.extract_object_function(obj, 'foo'), references, offsets


def compare(target, candidate, references):
    return m.match_function(
        target, candidate, image=m.LoadedImage(target, 0x401000, len(target)),
        target_va=0x401000, reference_manifest=references,
    )


@pytest.mark.parametrize('movzx', [False, True])
@pytest.mark.parametrize('lookup', [b'\x00\x01\x00', b'\x0f', b'\xe8\x00\x00\x00\x00', b'\x90'])
def test_bounded_switch_remap_compares_literal_bytes_and_excludes_only_padding(movzx, lookup):
    target, candidate, references, at = lookup_fixture(lookup=lookup, movzx=movzx)
    result = compare(target, candidate, references)
    assert result.exact and result.body_byte_exact
    assert result.target_instruction_count == (10 if movzx else 11)
    assert result.target_inline_data_ranges == ((at['jump'], at['end']),)
    assert result.candidate_inline_data_ranges == result.target_inline_data_ranges
    assert result.target_inline_lookup_ranges == ((at['lookup'], at['end']),)
    assert result.candidate_inline_lookup_ranges == result.target_inline_lookup_ranges
    assert result.compared_target_ranges == ((0, at['end']),)
    assert result.excluded_target_ranges == ((at['end'], len(target), 'terminal-padding'),)
    assert [x.text for x in result.target_disassembly if x.text.startswith('db.lookup ')] == [
        f'db.lookup 0x{byte:02x}' for byte in lookup
    ]
    assert result.encoded_body_proof['literal_inline_data_ranges'] == [[at['lookup'], at['end']]]
    assert not any(m._is_inline_data(line) for block in m.build_basic_blocks(result.target_disassembly)
                   for line in result.target_disassembly[block.start_instruction:block.end_instruction])


def test_lookup_byte_difference_cannot_be_hidden_by_reference_normalization():
    target, candidate, references, at = lookup_fixture()
    data = bytearray(candidate.data)
    data[at['lookup']] = 1
    result = compare(target, replace(candidate, data=bytes(data)), references)
    assert result.target_inline_data_ranges and result.candidate_inline_data_ranges
    assert not result.exact and not result.body_byte_exact
    assert result.masked_operand_audit.problem_count


@pytest.mark.parametrize('offset,replacement', [
    (1, b'\xf8'),  # Compare EAX, but read the table with ECX.
    (3, b'\x76'),  # JBE does not bound the fallthrough to unsigned <= max.
    (6, b'\xc0'),  # Zero EAX instead of the dispatch's EDX.
    (8, b'\xb1'),  # A high-byte load leaves the low byte uncontrolled.
])
def test_lookup_requires_the_complete_matching_unsigned_guard(offset, replacement):
    target, candidate, references, _ = lookup_fixture()
    native, data = bytearray(target), bytearray(candidate.data)
    native[offset:offset + len(replacement)] = data[offset:offset + len(replacement)] = replacement
    result = compare(bytes(native), replace(candidate, data=bytes(data)), references)
    assert not any(x.text.startswith('db.lookup ') for x in result.target_disassembly)
    assert not any(x.text.startswith('db.lookup ') for x in result.candidate_disassembly)


@pytest.mark.parametrize('mode', ['missing-native', 'wrong-native-size', 'short-object-symbol',
                                 'wrong-addend', 'relocated-byte', 'overlapping-relocation',
                                 'out-of-range-entry'])
def test_lookup_needs_curation_complete_storage_and_literal_valid_indices(mode):
    target, candidate, references, at = lookup_fixture()
    relocs = list(candidate.relocation_references)
    if mode == 'missing-native':
        references = replace(references, symbols=references.symbols[:1])
    elif mode == 'wrong-native-size':
        references = replace(references, symbols=(references.symbols[0], replace(references.symbols[1], size=2)))
    elif mode == 'short-object-symbol':
        relocs[0] = replace(relocs[0], symbol_size=2)
    elif mode == 'wrong-addend':
        data = bytearray(candidate.data)
        struct.pack_into('<I', data, at['load_disp'], 1)
        candidate = replace(candidate, data=bytes(data))
    elif mode in {'relocated-byte', 'overlapping-relocation'}:
        offset = at['lookup'] - (mode == 'overlapping-relocation')
        relocs.append(replace(relocs[0], offset=offset))
        candidate = replace(candidate, relocation_offsets=candidate.relocation_offsets | {offset})
    else:
        data = bytearray(candidate.data)
        data[at['lookup']] = 2
        candidate = replace(candidate, data=bytes(data))
    result = compare(target, replace(candidate, relocation_references=tuple(relocs)), references)
    assert not result.body_byte_exact
    side = result.target_disassembly if mode.startswith(('missing-', 'wrong-native')) else result.candidate_disassembly
    assert not any(x.text.startswith('db.lookup ') for x in side)


@pytest.mark.parametrize('destination', ['load', 'dispatch', 'lookup'])
def test_code_branch_cannot_bypass_the_guard_or_enter_lookup_data(destination):
    target, candidate, references, at = lookup_fixture()
    native, data = bytearray(target), bytearray(candidate.data)
    jump = bytes((0xeb, (at[destination] - at['first'] - 2) & 0xff))
    native[at['first']:at['first'] + 2] = data[at['first']:at['first'] + 2] = jump
    result = compare(bytes(native), replace(candidate, data=bytes(data)), references)
    assert not any(x.text.startswith('db.lookup ') for x in result.target_disassembly)
    assert not any(x.text.startswith('db.lookup ') for x in result.candidate_disassembly)


def test_post_lookup_code_is_decoded_and_cannot_branch_back_into_data():
    target, candidate, references, at = lookup_fixture(padding=b'\xe9' + bytes(4))
    native, data = bytearray(target), bytearray(candidate.data)
    struct.pack_into('<i', native, at['end'] + 1, at['lookup'] - at['end'] - 5)
    struct.pack_into('<i', data, at['end'] + 1, at['lookup'] - at['end'] - 5)
    result = compare(bytes(native), replace(candidate, data=bytes(data)), references)
    assert not any(x.text.startswith('db.lookup ') for x in result.target_disassembly)
    assert not any(x.text.startswith('db.lookup ') for x in result.candidate_disassembly)


@pytest.mark.parametrize('mode', ['gap', 'overlap', 'mask', 'branch-relocation', 'outside',
                                 'address-as-literal', 'wrong-literal-position'])
def test_public_lookup_proof_covers_every_literal_byte_without_masking(mode):
    target, candidate, references, at = lookup_fixture()
    result = compare(target, candidate, references)
    row = {
        'address': 0x401000,
        'target_inline_data_ranges': [[0x401000 + at['jump'], 0x401000 + at['end']]],
        'candidate_inline_data_ranges': [[at['jump'], at['end']]],
        'target_inline_lookup_ranges': [[0x401000 + at['lookup'], 0x401000 + at['end']]],
        'candidate_inline_lookup_ranges': [[at['lookup'], at['end']]],
        'compared_target_ranges': [[0x401000, 0x401000 + at['end']]],
        'encoded_body_proof': result.encoded_body_proof,
    }
    report.validate_inline_table_evidence(row)
    row = deepcopy(row)
    proof = row['encoded_body_proof']
    if mode == 'gap':
        proof['literal_inline_data_ranges'][0][0] += 1
    elif mode == 'overlap':
        proof['literal_inline_data_ranges'][0][0] -= 1
    elif mode == 'mask':
        proof['masked_relocation_ranges'].append([at['lookup'], at['end']])
    elif mode == 'branch-relocation':
        proof['resolved_local_relocations'].append(at['lookup'])
    elif mode == 'address-as-literal':
        proof['resolved_local_data_relocations'].clear()
        proof['literal_inline_data_ranges'] = [[at['jump'], at['end']]]
    elif mode == 'wrong-literal-position':
        row['target_inline_lookup_ranges'][0][0] += 1
    else:
        proof['literal_inline_data_ranges'][0][1] += 1
    with pytest.raises(ValueError):
        report.validate_inline_table_evidence(row)
