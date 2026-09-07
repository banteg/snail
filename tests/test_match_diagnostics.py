import json
from dataclasses import replace

import pytest

from snail import match as matchlib
from snail import match_export, match_history
from snail.match_contracts import caller_eax_use, decoder
from snail.match_mutation import (
    MutationChoice,
    MutationEvaluation,
    MutationSpec,
    MutationSweep,
    MutationVariant,
    code_groups,
    load_mutation_spec,
)


@pytest.mark.parametrize(
    ("machine_code", "outcome"),
    [
        ("89c1", "read"),  # mov ecx,eax
        ("8b00", "read"),  # mov eax,[eax] reads before writing
        ("40", "read"),  # inc eax is read/modify/write
        ("b00089c1", "read-after-partial-write"),
        ("66b8000089c1", "read-after-partial-write"),
        ("b000b800000000", "discarded"),
        ("31c0", "discarded"),  # xor eax,eax
        ("29c0", "discarded"),  # sub eax,eax
        ("89d8", "discarded"),  # mov eax,ebx
        ("0f44c1", "unknown-conditional-write"),
        ("7402", "unknown-control-flow"),
        ("e800000000", "unknown-call-contract"),
        ("c3", "unknown-forwarded-return"),
        ("90", "unknown-range-end"),
    ],
)
def test_caller_eax_evidence(machine_code, outcome):
    assert (
        caller_eax_use(list(decoder().disasm(bytes.fromhex(machine_code), 0x1000)))[
            "outcome"
        ]
        == outcome
    )


def test_code_identity_includes_relocation_targets_and_contents():
    reference = matchlib.ObjectRelocationReference(
        offset=1,
        symbol_name="first",
        text="first",
        key="first",
        explained=True,
        symbol_data=b"abc",
        symbol_relocation_offsets=frozenset({2}),
    )
    first = matchlib.ObjectFunction(
        "foo", b"\xe8\0\0\0\0", frozenset({1}), (reference,)
    )
    second = replace(
        first,
        relocation_references=(replace(reference, symbol_name="second", key="second"),),
    )
    third = replace(
        first, relocation_references=(replace(reference, symbol_data=b"abd"),)
    )
    assert (
        len({matchlib.object_function_fingerprint(f) for f in (first, second, third)})
        == 3
    )
    assert matchlib.object_function_fingerprint(
        first
    ) == matchlib.object_function_fingerprint(replace(first, name="renamed"))


def test_history_verifies_recipe_and_preserves_physical_line_numbers(tmp_path):
    recipe = tmp_path / "arbitrary-name.json"
    recipe.write_text(
        json.dumps(
            {
                "schema": 1,
                "sites": [
                    {
                        "name": "return-contract",
                        "find": "int foo()",
                        "replacements": [{"name": "void", "text": "void foo()"}],
                    }
                ],
            }
        )
    )
    spec = load_mutation_spec(recipe)
    record = {
        "spec_sha256": spec.sha256,
        "baseline_epoch": "old",
        "hypothesis": "unused return",
        "results": [
            {
                "label": "return-contract/void",
                "mutations": [
                    {
                        "site": "return-contract",
                        "replacement_index": 1,
                        "replacement": "void",
                    }
                ],
            }
        ],
    }
    ledger = tmp_path / "experiments.jsonl"
    ledger.write_text("\ninvalid\n" + json.dumps(record) + "\n")
    result = match_history.search_history(
        [ledger], query="void foo", current_epochs={tmp_path: "new"}
    )
    assert len(result["errors"]) == 1
    row = result["rows"][0]
    assert row["line"] == 3 and row["epoch"] == "historical"
    assert row["edit_evidence"] == "hash-verified recipe"
    assert row["edits"][0]["replace"] == "void foo()"
    recipe.write_text(
        recipe.read_text() + "\n"
    )  # even innocuous edited bytes invalidate the join
    result = match_history.search_history([ledger], query="unused return")
    assert result["rows"][0]["edit_evidence"] == "unavailable"
    assert result["rows"][0]["edits"] == []
    assert result["rows"][0]["epoch"] == "unknown"


def make_sweep(tmp_path, *, error=None):
    config = matchlib.ScratchConfig(tmp_path, "foo", "msvc6.5", "/O2", None, None)
    baseline = matchlib.ScratchStatus(
        config, 0x1000, 1, 1.0, 1, 1, 1, code_sha256="baseline"
    )
    status = replace(
        baseline,
        ratio=0.5 if error is None else None,
        code_sha256="candidate",
        error=error,
    )
    variant = MutationVariant(
        "shape/diagnostic",
        "int foo() { return 2; }",
        "source-hash",
        (MutationChoice("shape", "diagnostic", 1),),
    )
    return MutationSweep(
        MutationSpec((), "spec-hash"),
        baseline,
        (MutationEvaluation(variant, status, baseline),),
        (1,),
        (1,),
    )


def test_groups_do_not_merge_equal_scores_or_errors(tmp_path):
    sweep = make_sweep(tmp_path)
    original = sweep.evaluations[0]
    same = replace(original, variant=replace(original.variant, label="same"))
    different = replace(
        original,
        variant=replace(original.variant, label="different"),
        status=replace(original.status, code_sha256="different"),
    )
    failed = replace(original, status=replace(original.status, error="failure"))
    groups = code_groups(
        replace(sweep, evaluations=(original, same, different, failed))
    )
    assert [g["labels"] for g in groups] == [
        ["shape/diagnostic", "same"],
        ["different"],
    ]


def test_export_nonimproving_candidate_and_refuse_changed_code(tmp_path, monkeypatch):
    sweep = make_sweep(tmp_path)
    assert not sweep.best_improves
    source = tmp_path / "scratch.cpp"
    source.write_text("int foo() { return 1; }")
    obj = tmp_path / "test.obj"
    obj.write_bytes(b"object")
    monkeypatch.setattr(matchlib, "compile_scratch", lambda *a: obj)
    monkeypatch.setattr(matchlib, "parse_coff_object", lambda *a: None)
    monkeypatch.setattr(matchlib, "extract_object_function", lambda *a, **kw: None)
    monkeypatch.setattr(matchlib, "object_function_fingerprint", lambda *a: "candidate")
    monkeypatch.setattr(
        matchlib,
        "run_match",
        lambda **kw: matchlib.MatchResult(0.5, 0, ("ret",), ("nop",)),
    )
    destination = tmp_path / "export"
    options = {
        "source_text": source.read_text(),
        "match_root": tmp_path,
        "image_path": tmp_path / "game",
        "manifest": None,
        "baseline_epoch": "epoch",
    }
    report = match_export.export_candidate(
        sweep, "shape/diagnostic", destination, **options
    )
    assert source.read_text() == "int foo() { return 1; }"
    assert (destination / "candidate.cpp").read_text() == sweep.best.variant.source_text
    assert "-ret" in (destination / "assembly.diff").read_text()
    assert not (destination / "baseline.asm").exists()
    assert not (destination / "baseline.diff").exists()
    assert report["reference_audit"] == {"entries": ()}
    assert (
        json.loads((destination / "report.json").read_text())["baseline_epoch"]
        == "epoch"
    )
    with pytest.raises(ValueError, match="already exists"):
        match_export.export_candidate(sweep, "shape/diagnostic", destination, **options)
    with pytest.raises(ValueError, match="not evaluated"):
        match_export.export_candidate(sweep, "unknown", tmp_path / "unknown", **options)
    monkeypatch.setattr(matchlib, "object_function_fingerprint", lambda *a: "changed")
    with pytest.raises(ValueError, match="does not reproduce"):
        match_export.export_candidate(
            sweep, "shape/diagnostic", tmp_path / "changed", **options
        )
    assert not (tmp_path / "changed").exists()


def test_export_compile_failure_keeps_source_and_error(tmp_path):
    sweep = make_sweep(tmp_path, error="compiler failed")
    report = match_export.export_candidate(
        sweep,
        "shape/diagnostic",
        tmp_path / "export",
        source_text="baseline",
        match_root=tmp_path,
        image_path=tmp_path / "image",
        manifest=None,
        baseline_epoch="epoch",
    )
    assert report["error"] == "compiler failed"
    assert report["diagnostic"] is None
    assert not (tmp_path / "export" / "assembly.diff").exists()
