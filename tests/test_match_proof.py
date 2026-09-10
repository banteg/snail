"""Adversarial exact-certification and byte-accounting regressions."""

from dataclasses import replace

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
        lambda _: SimpleNamespace(function="test"),
    )
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
