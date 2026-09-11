"""Adversarial exact-certification and byte-accounting regressions."""

from dataclasses import replace
from pathlib import Path

import pytest

from snail import match as m
from snail import match_report as report


def reference_line(index, name, text="mov eax, dword [ADDR]", slot=1, kind="disp"):
    return m.DisassemblyLine(
        index,
        0x401000 + index,
        text,
        size=1,
        masked_references=(
            m.MaskedReference(slot, kind, "image", None, name, f"name:{name}", True),
        ),
    )


@pytest.mark.parametrize(
    "text,slot,kind",
    [
        ("mov eax, dword [ADDR]", 1, "disp"),
        ("call ADDR", 0, "imm"),
    ],
)
@pytest.mark.parametrize("arithmetic", [False, True])
def test_exact_references_cannot_cross_instruction_positions(
    text, slot, kind, arithmetic
):
    target = [
        reference_line(0, "a", text, slot, kind),
        reference_line(2, "b", text, slot, kind),
    ]
    candidate = [
        reference_line(0, "b", text, slot, kind),
        reference_line(2, "a", text, slot, kind),
    ]
    if arithmetic:
        target.insert(1, m.DisassemblyLine(1, 0x401001, "add ecx, eax", size=1))
        candidate.insert(1, target[1])
        target.append(m.DisassemblyLine(3, 0x401003, "sub ecx, eax", size=1))
        candidate.append(target[-1])
    audit = m.audit_masked_operands(tuple(target), tuple(candidate))
    assert audit.mismatch_count == 2
    assert all(e.target_index == e.candidate_index for e in audit.entries)


@pytest.mark.parametrize(
    "changes", [{"operand_index": 0}, {"kind": "imm"}, {"key": "name:a+4"}]
)
def test_exact_reference_requires_operand_slot_kind_and_addend(changes):
    target = reference_line(0, "a")
    candidate = replace(
        target, masked_references=(replace(target.masked_references[0], **changes),)
    )
    assert m.audit_masked_operands((target,), (candidate,)).mismatch_count == 1


def compare(target, candidate=None):
    return m.match_function(
        target,
        candidate or m.ObjectFunction("test", target, frozenset()),
        image=m.LoadedImage(b"", 0x400000, 0x10000),
        target_va=0x401000,
    )


def test_unknown_suffix_remains_visible_and_cannot_be_exact():
    result = compare(bytes.fromhex("c30f"))
    assert result.target_lines == ("ret", "db 0x0f")
    assert result.compared_target_ranges == ((0, 1),)
    assert result.unexplained_target_ranges == ((1, 2),)
    assert not result.body_byte_exact
    assert not m.match_result_payload(result)["exact"]


def test_post_return_code_is_compared_and_padding_is_accounted():
    result = compare(bytes.fromhex("c3b801000000c390cc"))
    assert result.target_lines == ("ret", "mov eax, 0x1", "ret")
    assert result.compared_target_ranges == ((0, 7),)
    assert result.excluded_target_ranges == ((7, 9, "terminal-padding"),)
    assert result.body_byte_exact


def test_raw_extent_does_not_strip_operand_bytes_that_look_like_padding():
    data = bytes.fromhex("b800000090")
    image = m.LoadedImage(data, 0x401000, len(data))
    assert image.function_bytes(0x401000, 0x401005) == data
    assert compare(data).body_byte_exact


def test_normalized_equivalent_encodings_are_not_encoded_exact():
    result = compare(
        bytes.fromhex("8b0431c3"),
        m.ObjectFunction("test", bytes.fromhex("8b040ec3"), frozenset()),
    )
    assert result.ratio == 1
    assert not result.body_byte_exact


def test_encoded_body_masks_only_audited_external_relocation_fields():
    target = bytes.fromhex("e80b000000c3")
    candidate = m.ObjectFunction(
        "test",
        bytes.fromhex("e800000000c3"),
        frozenset({1}),
        (
            m.ObjectRelocationReference(
                1, "helper", "sym:helper", "name:helper", True, 0
            ),
        ),
    )
    # Reuse the real reference resolver rather than granting an audit Boolean.
    from test_match import relocated_candidate, tiny_manifest

    result = m.match_function(
        target,
        relocated_candidate("_right_helper", "name:right_helper"),
        image=m.LoadedImage(b"\0" * 0x2000, 0x401000, 0x2000),
        target_va=0x401000,
        manifest=tiny_manifest(),
    )
    assert result.body_byte_exact
    bad = m.match_function(
        target,
        candidate,
        image=m.LoadedImage(b"\0" * 0x2000, 0x401000, 0x2000),
        target_va=0x401000,
        manifest=tiny_manifest(),
    )
    assert not bad.body_byte_exact


def test_coverage_excludes_owned_padding_and_unknown_bytes():
    row = {
        "address": 100,
        "scratch_target_bytes": 10,
        "compared_target_ranges": [[100, 105]],
        "excluded_target_ranges": [[105, 108, "terminal-padding"]],
        "unexplained_target_ranges": [[108, 110]],
    }
    report.validate_comparison_ranges(row)
    assert report.intersection_size(row["compared_target_ranges"], [[100, 110]]) == 5
    row["compared_target_ranges"].append([104, 105])
    with pytest.raises(ValueError, match="partition"):
        report.validate_comparison_ranges(row)


def test_report_uses_readable_names_for_treemap():
    from test_match_report import row

    before = report.build_report([row(name="old")])["units"][0]
    after = report.build_report([row(name="recovered")])["units"][0]
    assert before["name"] == before["functions"][0]["name"] == "old"
    assert after["name"] == after["functions"][0]["name"] == "recovered"
    assert after["functions"][0]["metadata"]["demangled_name"] == "recovered"


def test_encoded_local_relative_relocation_is_resolved():
    candidate = m.ObjectFunction(
        "test",
        bytes.fromhex("e90000000090c3"),
        frozenset({1}),
        (
            m.ObjectRelocationReference(
                1, "$Lret", "sym:$Lret", "name:$Lret", True, 0, symbol_offset=6
            ),
        ),
    )
    result = compare(bytes.fromhex("e90100000090c3"), candidate)
    assert result.ratio == 1
    assert result.body_byte_exact
    assert result.encoded_body_proof["resolved_local_relocations"] == [1]
    assert result.encoded_body_proof["masked_relocation_ranges"] == []


def test_unexplained_relocation_cannot_be_hidden_by_equal_encodings():
    result = compare(
        bytes.fromhex("c3"), m.ObjectFunction("test", b"\xc3", frozenset({0}))
    )
    assert result.ratio == 1
    assert not result.body_byte_exact
    assert result.encoded_body_proof is None


def test_strict_jump_table_does_not_accept_same_offset_at_wrong_instruction():
    target = reference_line(0, "table", "jmp dword [ADDR]", 0)
    target = replace(
        target,
        masked_references=(
            replace(
                target.masked_references[0],
                text="jump_table:table",
                jump_table_entries=(1, 2),
            ),
        ),
    )
    candidate = replace(
        target,
        masked_references=(
            replace(
                target.masked_references[0],
                source="reloc",
                text="sym:$Ltable",
                jump_table_entries=(1, 2),
            ),
        ),
    )
    a = (
        target,
        m.DisassemblyLine(1, 1, "nop", size=1),
        m.DisassemblyLine(2, 2, "ret", size=1),
    )
    b = (
        candidate,
        m.DisassemblyLine(2, 2, "nop", size=1),
        m.DisassemblyLine(3, 3, "ret", size=1),
    )
    assert m.audit_masked_operands(a, b).mismatch_count == 1
    good = replace(
        candidate,
        masked_references=(
            replace(candidate.masked_references[0], jump_table_entries=(2, 3)),
        ),
    )
    assert m.audit_masked_operands(a, (good, *b[1:])).problem_count == 0


@pytest.fixture
def source_evidence(monkeypatch, tmp_path):
    from hashlib import sha256
    from types import SimpleNamespace

    from test_match_report import row

    function = row(
        address=100,
        size=1,
        source="test/scratch.cpp",
        scratch_target_bytes=1,
        covered_code_bytes=1,
        normalized_ratio=1.0,
        matching_state="match",
        reference_audit_mode="positional",
        references={"ok": 0, "mismatched": 0, "unresolved": 0, "unaudited": 0},
        compared_target_ranges=[[100, 101]],
        excluded_target_ranges=[],
        unexplained_target_ranges=[],
        body_byte_exact=True,
        candidate_object_sha256="a" * 64,
        encoded_body_proof={
            "target_sha256": sha256(b"\xc3").hexdigest(),
            "candidate_sha256": sha256(b"\xc3").hexdigest(),
            "body_size": 1,
            "masked_relocation_ranges": [],
            "resolved_local_relocations": [],
        },
    )
    fields = ("address", "name", "size", "ranges", "is_function")
    monkeypatch.setattr(report, "inventory", lambda: [{k: function[k] for k in fields}])
    monkeypatch.setattr(report, "REPO_ROOT", tmp_path)
    monkeypatch.setattr(report.matchlib, "DEFAULT_MATCH_ROOT", tmp_path / "tools/match")
    monkeypatch.delenv("WIBO", raising=False)
    monkeypatch.setattr(
        report,
        "load_function_symbol_manifest",
        lambda _: SimpleNamespace(
            primary_target="target.exe", unwrapped_sha256="b" * 64
        ),
    )
    monkeypatch.setattr(
        report.matchlib,
        "_function_symbols_by_name",
        lambda _: {"test": SimpleNamespace(address=100)},
    )
    monkeypatch.setattr(
        report.matchlib,
        "load_scratch_config",
        lambda _: SimpleNamespace(function="test", end_va=None),
    )
    monkeypatch.setattr(report.matchlib, "resolve_function_extent", lambda *_: (100, 101))
    monkeypatch.setattr(report.matchlib, "validate_scratch_source", lambda _: None)
    inputs = {"test/scratch.cpp": "pinned"}
    monkeypatch.setattr(report, "repository_inputs", lambda: inputs)
    external = {
        "image": {"path": "target.exe", "sha256": "b" * 64},
        "compilers": {},
        "runner": {"sha256": "c" * 64},
    }
    evidence = {
        "schema": report.EVIDENCE_SCHEMA,
        "version": report.VERSION,
        "scope": "full-executable-code",
        "inputs": inputs,
        "external_inputs": external,
        "functions": [function],
        "identities": report.measurement_identities(inputs, external),
        "verification_mode": report.VERIFICATION_MODE,
    }
    evidence["progress_delta"] = report.progress_delta(None, evidence)
    report.validate_evidence(evidence)
    return evidence


@pytest.mark.parametrize(
    "change",
    [
        lambda r: r.update(reference_audit_mode="diagnostic"),
        lambda r: r.update(candidate_object_sha256=None),
        lambda r: r["encoded_body_proof"].update(candidate_sha256="d" * 64),
        lambda r: r["encoded_body_proof"].update(body_size=2),
        lambda r: r["references"].update(ok=-1),
        lambda r: r.update(
            compared_target_ranges=[],
            excluded_target_ranges=[[100, 101, "terminal-padding"]],
        ),
        lambda r: r.update(compared_target_ranges=[]),
    ],
)
def test_saved_evidence_rejects_inconsistent_certification(source_evidence, change):
    change(source_evidence["functions"][0])
    with pytest.raises(ValueError):
        report.validate_evidence(source_evidence)


def test_progress_delta_distinguishes_measurement_change(source_evidence):
    from copy import deepcopy

    previous = deepcopy(source_evidence)
    previous["functions"][0]["matched"] = False
    delta = report.progress_delta(previous, source_evidence)
    assert delta["interpretation"] == "comparable-source-progress"
    assert delta["newly_matched_bytes"] == 1
    source_evidence["identities"]["scoring"] = "new-scorer"
    delta = report.progress_delta(previous, source_evidence)
    assert delta["interpretation"] == "measurement-baseline-change"
    assert delta["changed_identities"] == ["scoring"]


def test_progress_delta_tracks_target_span_without_scorer_change(source_evidence):
    from copy import deepcopy

    previous = deepcopy(source_evidence)
    previous["functions"][0].update(matched=False, scratch_target_bytes=20)
    delta = report.progress_delta(previous, source_evidence)
    assert delta["changed_identities"] == []
    assert delta["changed_target_spans"] == [
        {"address": 100, "previous": [100, 120], "current": [100, 101]}
    ]
    assert delta["interpretation"] == "measurement-baseline-change"
    assert delta["newly_matched_bytes"] == 1
    source_evidence["progress_delta"] = delta
    report.validate_evidence(source_evidence)
    delta["interpretation"] = "comparable-source-progress"
    with pytest.raises(ValueError, match="misclassifies"):
        report.validate_evidence(source_evidence)


def test_progress_delta_new_source_is_not_an_extent_change(source_evidence):
    from copy import deepcopy

    previous = deepcopy(source_evidence)
    previous["functions"][0].update(candidate=None, source=None, matched=False)
    previous["functions"][0].pop("scratch_target_bytes")
    delta = report.progress_delta(previous, source_evidence)
    assert delta["changed_target_spans"] == []
    assert delta["interpretation"] == "comparable-source-progress"


@pytest.mark.parametrize("span", [
    {"address": 100, "previous": [100, 101], "current": [100, 101]},
    {"address": 100, "previous": [100, 120], "current": [100, 102]},
    {"address": 100, "previous": [99, 120], "current": [100, 101]},
    {"address": True, "previous": [100, 120], "current": [100, 101]},
    {"address": 101, "previous": [101, 120], "current": [101, 102]},
])
def test_saved_evidence_rejects_invalid_span_change(source_evidence, span):
    source_evidence["progress_delta"]["changed_target_spans"] = [span]
    with pytest.raises(ValueError, match="target span change"):
        report.validate_evidence(source_evidence)


def test_saved_evidence_rejects_duplicate_span_changes(source_evidence):
    span = {"address": 100, "previous": [100, 120], "current": [100, 101]}
    source_evidence["progress_delta"]["changed_target_spans"] = [span, span]
    with pytest.raises(ValueError, match="target span change"):
        report.validate_evidence(source_evidence)


def test_saved_evidence_binds_extent_to_config(source_evidence):
    source_evidence["functions"][0]["scratch_target_bytes"] = 2
    with pytest.raises(ValueError, match="scratch configuration"):
        report.validate_evidence(source_evidence)


def test_saved_evidence_rejects_false_delta_identity_list(source_evidence):
    source_evidence["progress_delta"]["changed_identities"] = ["scoring"]
    with pytest.raises(ValueError, match="misclassifies"):
        report.validate_evidence(source_evidence)


def test_progress_delta_reconciles_removed_owned_ranges(source_evidence):
    from copy import deepcopy

    previous = deepcopy(source_evidence)
    previous["functions"][0].update(size=2, ranges=[[100, 102]])
    delta = report.progress_delta(previous, source_evidence)
    assert delta["regressed_bytes"] == 1
    assert delta["newly_matched_bytes"] == 0


def test_run_match_hashes_the_supplied_object_snapshot(monkeypatch, tmp_path):
    """A concurrent compiler can replace the path after its bytes were captured."""
    import hashlib
    from types import SimpleNamespace

    captured = b"captured COFF snapshot"
    parsed = []
    candidate = m.ObjectFunction("test", b"\xc3", frozenset())
    result = compare(b"\xc3")
    monkeypatch.setattr(m, "parse_coff_object", lambda data: parsed.append(data))
    monkeypatch.setattr(m, "extract_object_function", lambda *args, **kwargs: candidate)
    monkeypatch.setattr(m, "resolve_function_extent", lambda *args: (0x401000, 0x401001))
    monkeypatch.setattr(
        m, "load_image",
        lambda *args: SimpleNamespace(function_bytes=lambda *extent: b"\xc3"),
    )
    monkeypatch.setattr(m, "match_function", lambda *args, **kwargs: result)

    actual = m.run_match(
        obj_path=tmp_path / "no-longer-present.obj",
        function_name="test",
        image_path=tmp_path / "unused.exe",
        manifest=SimpleNamespace(image_base=0x400000),
        object_data=captured,
        reference_manifest=object(),
    )

    assert parsed == [captured]
    assert actual.candidate_object_sha256 == hashlib.sha256(captured).hexdigest()


def inline_table_fixture(*, entries=(7, 10), native_entries=None, padding=b'\x90' * 8,
                         alignment=b'', base=0x401000):
    """A real indexed dispatch, two return blocks, then a relocated data tail."""
    import struct

    code = bytes.fromhex('ff24850000000031c0c3b801000000c3') + alignment
    table_offset = len(code)
    target = bytearray(code)
    struct.pack_into('<I', target, 3, base + table_offset)
    target += struct.pack('<II', *(base + x for x in (native_entries or entries)))
    target += padding
    obj_data = code + struct.pack('<II', *entries) + padding
    obj = m.CoffObject(
        sections=(m.CoffSection('.text', obj_data, 0x20, (
            m.CoffRelocation(3, 1, 0x06),
            m.CoffRelocation(table_offset, 0, 0x06),
            m.CoffRelocation(table_offset + 4, 0, 0x06),
        )),),
        symbols=(
            m.CoffSymbol(0, '_foo', 0, 1, 0x20, 2),
            m.CoffSymbol(1, '$Ltable', table_offset, 1, 0, 3),
        ),
    )
    candidate = m.extract_object_function(obj, 'foo')
    references = m.ReferenceSymbolManifest('test', (
        m.ReferenceSymbol(base + table_offset, 'foo_table', 'jump_table', size=8),
    ))
    return bytes(target), candidate, references


def compare_inline_table(target, candidate, references, *, base=0x401000):
    return m.match_function(
        target, candidate,
        image=m.LoadedImage(target, base, len(target)),
        target_va=base, reference_manifest=references,
    )


@pytest.mark.parametrize('alignment', ['8d4900', '8d642400', '8da42400000000'])
def test_inline_table_self_lea_alignment_is_retained_in_encoded_body(alignment):
    alignment = bytes.fromhex(alignment)
    target, candidate, references = inline_table_fixture(alignment=alignment)
    result = compare_inline_table(target, candidate, references)
    end = 24 + len(alignment)
    assert result.exact and result.body_byte_exact
    assert result.target_lines[-3].startswith('lea ')
    assert result.compared_target_ranges == ((0, end),)
    assert result.encoded_body_proof['body_size'] == end
    assert result.encoded_body_proof['masked_relocation_ranges'] == [[3, 7]]


@pytest.mark.parametrize('alignment', ['8d4a00', '8d4901', '668d4900', '8d4c0900'])
def test_inline_table_does_not_treat_state_changing_lea_as_alignment(alignment):
    target, candidate, references = inline_table_fixture(alignment=bytes.fromhex(alignment))
    result = compare_inline_table(target, candidate, references)
    assert not result.target_inline_data_ranges
    assert not result.candidate_inline_data_ranges
    assert not result.body_byte_exact


def test_inline_table_does_not_accept_a_destination_in_self_lea_alignment():
    target, candidate, references = inline_table_fixture(entries=(7, 16), alignment=b'\x8d\x49\0')
    result = compare_inline_table(target, candidate, references)
    assert not result.target_inline_data_ranges
    assert not result.candidate_inline_data_ranges
    assert not result.body_byte_exact


@pytest.mark.parametrize('branch', [bytes.fromhex('eb07'), bytes.fromhex('eb0a')])
def test_inline_table_rejects_real_code_branches_into_alignment_or_table(branch):
    target, candidate, references = inline_table_fixture(alignment=b'\x8d\x49\0')
    target = target[:7] + branch + target[9:]
    candidate = replace(candidate, data=candidate.data[:7] + branch + candidate.data[9:])
    result = compare_inline_table(target, candidate, references)
    assert not result.target_inline_data_ranges
    assert not result.candidate_inline_data_ranges
    assert not result.body_byte_exact


def test_inline_table_words_that_decode_as_branches_are_still_compared_as_data():
    # The first native word is 7c 02 40 00: a linear decoder invents a JL
    # from table offset 16 to offset 20, inside the same table.
    base = 0x400275
    target, candidate, references = inline_table_fixture(base=base)
    assert target[16:20] == bytes.fromhex('7c024000')
    result = compare_inline_table(target, candidate, references, base=base)
    assert result.exact and result.body_byte_exact
    assert result.target_inline_data_ranges == ((16, 24),)
    assert result.encoded_body_proof['resolved_local_data_relocations'] == [
        {'offset': 16, 'target_offset': 7}, {'offset': 20, 'target_offset': 10},
    ]


def test_inline_table_rejects_real_post_table_branch_into_data():
    target, candidate, references = inline_table_fixture(padding=bytes.fromhex('ebf6'))
    result = compare_inline_table(target, candidate, references)
    assert not result.target_inline_data_ranges
    assert not result.candidate_inline_data_ranges
    assert not result.body_byte_exact


def test_inline_table_can_start_where_linear_instruction_decoding_fails():
    base = 0x405008
    target, candidate, references = inline_table_fixture(base=base)
    # 0f 50 40 is not a valid MOVMSKPS register operand; this is an address.
    assert target[16:20] == bytes.fromhex('0f504000')
    result = compare_inline_table(target, candidate, references, base=base)
    assert result.exact and result.body_byte_exact
    assert result.target_inline_data_ranges == ((16, 24),)
    assert not result.unexplained_target_ranges


@pytest.mark.parametrize('suffix', [b'\x90' * 8, bytes.fromhex('ebee')])
def test_adjacent_inline_tables_are_checked_using_code_boundaries(suffix):
    import struct

    base = 0x405001
    code = bytes.fromhex('ff248500000000ff24850000000031c0c3b801000000c390')
    assert len(code) == 24
    native = bytearray(code)
    struct.pack_into('<I', native, 3, base + 24)
    struct.pack_into('<I', native, 10, base + 32)
    entries = (14, 17, 17, 14)
    native += struct.pack('<IIII', *(base + x for x in entries)) + suffix
    obj_data = code + struct.pack('<IIII', *entries) + suffix
    obj = m.CoffObject(
        sections=(m.CoffSection('.text', obj_data, 0x20, (
            m.CoffRelocation(3, 1, 0x06), m.CoffRelocation(10, 2, 0x06),
            *(m.CoffRelocation(at, 0, 0x06) for at in (24, 28, 32, 36)),
        )),),
        symbols=(
            m.CoffSymbol(0, '_foo', 0, 1, 0x20, 2),
            m.CoffSymbol(1, '$Lfirst', 24, 1, 0, 3),
            m.CoffSymbol(2, '$Lsecond', 32, 1, 0, 3),
        ),
    )
    references = m.ReferenceSymbolManifest('test', (
        m.ReferenceSymbol(base + 24, 'first', 'jump_table', size=8),
        m.ReferenceSymbol(base + 32, 'second', 'jump_table', size=8),
    ))
    result = compare_inline_table(
        bytes(native), m.extract_object_function(obj, 'foo'), references, base=base,
    )
    if suffix.startswith(b'\xeb'):
        # A real jump after both tables enters the first table. Reject it even
        # though decoding the first table word as code stops before this jump.
        assert not result.target_inline_data_ranges
        assert not result.candidate_inline_data_ranges
        assert not result.body_byte_exact
    else:
        assert result.exact and result.body_byte_exact
        assert result.target_inline_data_ranges == ((24, 40),)
        assert result.compared_target_ranges == ((0, 40),)
        assert result.encoded_body_proof['resolved_local_data_relocations'] == [
            {'offset': at, 'target_offset': entry}
            for at, entry in zip((24, 28, 32, 36), entries, strict=True)
        ]


def test_inline_table_is_compared_as_data_and_resolved_without_masking_entries():
    target, candidate, references = inline_table_fixture()
    result = compare_inline_table(target, candidate, references)
    assert result.exact and result.body_byte_exact
    assert result.target_lines[-2:] == ('dd L7', 'dd La')
    assert result.target_instruction_count == result.candidate_instruction_count == 5
    assert result.instruction_prefix_count == 5
    assert result.target_inline_data_ranges == ((16, 24),)
    assert result.candidate_inline_data_ranges == ((16, 24),)
    assert result.compared_target_ranges == ((0, 24),)
    assert result.excluded_target_ranges == ((24, 32, 'terminal-padding'),)
    assert not result.unexplained_target_ranges
    assert result.masked_operand_audit.ok_count == 1
    proof = result.encoded_body_proof
    assert proof['body_size'] == 24
    assert proof['masked_relocation_ranges'] == [[3, 7]]
    assert proof['resolved_local_data_relocations'] == [
        {'offset': 16, 'target_offset': 7}, {'offset': 20, 'target_offset': 10},
    ]
    assert proof['candidate_sha256'] == proof['target_sha256']
    blocks = m.build_basic_blocks(result.target_disassembly)
    assert all(not line.startswith('dd ') for block in blocks for line in block.lines)
    assert all(block.end_offset <= 16 for block in blocks)
    status = m.ScratchStatus(
        config=m.ScratchConfig(Path('/tmp/table-test'), 'foo', 'msvc6.5', '/O2', None, None),
        address=0x401000, **m._scratch_status_fields(len(target), result),
    )
    payload = m.scratch_status_payload(status)
    assert payload['target_instructions'] == payload['prefix_instructions'] == 5
    assert payload['target_inline_data_ranges'] == [[16, 24]]


@pytest.mark.parametrize('entries', [(10, 7), (7, 7), (8, 10), (7, 16), (7, 25)])
def test_inline_table_permuted_wrong_or_non_code_targets_do_not_certify(entries):
    target, candidate, references = inline_table_fixture(
        entries=entries, native_entries=(7, 10),
    )
    result = compare_inline_table(target, candidate, references)
    assert not result.exact
    assert not result.body_byte_exact


@pytest.mark.parametrize('mode', ['missing', 'relative-type', 'false-addend', 'external'])
def test_inline_table_requires_each_complete_local_dir32_relocation(mode):
    target, candidate, references = inline_table_fixture()
    relocs = list(candidate.relocation_references)
    if mode == 'missing':
        relocs.pop()
    elif mode == 'relative-type':
        relocs[-1] = replace(relocs[-1], relocation_type=0x14)
    elif mode == 'false-addend':
        relocs[-1] = replace(relocs[-1], addend=7)
    else:
        relocs[-1] = replace(relocs[-1], symbol_offset=None)
    result = compare_inline_table(target, replace(candidate, relocation_references=tuple(relocs)), references)
    assert not result.exact
    assert not result.body_byte_exact


def test_inline_table_needs_native_curation_and_dispatch():
    target, candidate, references = inline_table_fixture()
    result = compare_inline_table(target, candidate, m.ReferenceSymbolManifest('empty'))
    assert not result.target_inline_data_ranges
    assert not result.body_byte_exact
    # A metadata label over the same bytes does not turn ordinary code into a table.
    target = b'\x90' * 7 + target[7:]
    result = compare_inline_table(target, candidate, references)
    assert not result.target_inline_data_ranges
    assert not result.exact


def test_inline_table_does_not_discard_a_post_table_continuation():
    target, candidate, references = inline_table_fixture(padding=bytes.fromhex('b802000000c3'))
    result = compare_inline_table(target, candidate, references)
    assert result.body_byte_exact
    assert result.target_lines[-2:] == ('mov eax, 0x2', 'ret')
    assert result.compared_target_ranges == ((0, 30),)
    assert result.excluded_target_ranges == ()
    assert any(block.start_offset == 24 for block in m.build_basic_blocks(result.target_disassembly))


def test_public_table_evidence_requires_every_entry_and_cannot_mask_table_data():
    import copy

    target, candidate, references = inline_table_fixture()
    result = compare_inline_table(target, candidate, references)
    row = {
        'address': 0x401000,
        'target_inline_data_ranges': [[0x401010, 0x401018]],
        'candidate_inline_data_ranges': [[16, 24]],
        'compared_target_ranges': [[0x401000, 0x401018]],
        'encoded_body_proof': result.encoded_body_proof,
    }
    report.validate_inline_table_evidence(row)
    missing = copy.deepcopy(row)
    missing['encoded_body_proof']['resolved_local_data_relocations'].pop()
    with pytest.raises(ValueError, match='incomplete'):
        report.validate_inline_table_evidence(missing)
    masked = copy.deepcopy(row)
    masked['encoded_body_proof']['masked_relocation_ranges'].append([16, 20])
    with pytest.raises(ValueError, match='inline table relocation'):
        report.validate_inline_table_evidence(masked)
    wrong_position = copy.deepcopy(row)
    wrong_position['candidate_inline_data_ranges'] = [[20, 28]]
    with pytest.raises(ValueError, match='position'):
        report.validate_inline_table_evidence(wrong_position)
    data_destination = copy.deepcopy(row)
    data_destination['encoded_body_proof']['resolved_local_data_relocations'][1]['target_offset'] = 16
    with pytest.raises(ValueError, match='inline table relocation'):
        report.validate_inline_table_evidence(data_destination)


def test_duplicate_inline_table_relocations_are_not_consumed_as_one():
    target, candidate, references = inline_table_fixture()
    candidate = replace(candidate, relocation_references=(
        *candidate.relocation_references, candidate.relocation_references[-1],
    ))
    result = compare_inline_table(target, candidate, references)
    assert not result.body_byte_exact
    assert not result.candidate_inline_data_ranges


def test_inline_table_dispatch_addend_must_match_the_coff_bytes():
    import struct

    target, candidate, references = inline_table_fixture()
    data = bytearray(candidate.data)
    struct.pack_into('<I', data, 3, 4)
    candidate = replace(candidate, data=bytes(data))
    result = compare_inline_table(target, candidate, references)
    assert not result.body_byte_exact
    assert not result.candidate_inline_data_ranges
