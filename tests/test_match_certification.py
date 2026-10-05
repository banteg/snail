"""Negative controls for relocation and local-helper exact certification."""

import struct
from dataclasses import replace

import pytest

from snail import match as m


def summarize(result):
    return {
        "exact": result.exact,
        "body_byte_exact": result.body_byte_exact,
        "ratio": result.ratio,
        "audit": [
            (
                e.status,
                [(r.key, r.normalized_code) for r in e.target_references],
                [(r.key, r.normalized_code) for r in e.candidate_references],
            )
            for e in result.masked_operand_audit.entries
        ],
    }


def content_reference(kind, addend, target_addend=0, symbol_value=0):
    blob = b"hello\0" if kind == "string" else struct.pack("<ff", 1.0, 2.0)
    code = (
        (b"\xb8" if kind == "string" else b"\xd9\x05")
        + struct.pack("<I", addend & 0xFFFFFFFF)
        + b"\xc3"
    )
    field = 1 if kind == "string" else 2
    obj = m.CoffObject(
        (
            m.CoffSection(".text", code, 0x20, (m.CoffRelocation(field, 1, 0x06),)),
            m.CoffSection(".rdata", blob, 0x40, ()),
        ),
        (
            m.CoffSymbol(0, "_foo", 0, 1, 0x20, 2),
            m.CoffSymbol(
                1, "$SG1" if kind == "string" else "__real@1", symbol_value, 2, 0, 3
            ),
        ),
    )
    candidate = m.extract_object_function(obj, "foo")
    mapped = bytearray(0x3000)
    mapped[0x2000 : 0x2000 + len(blob)] = blob
    image = m.LoadedImage(
        bytes(mapped),
        0x400000,
        len(mapped),
        sections=(m.ImageSection(".rdata", 0x402000, 0x403000, 0x40),),
    )
    target = (
        (b"\xb8" if kind == "string" else b"\xd9\x05")
        + struct.pack("<I", 0x402000 + target_addend)
        + b"\xc3"
    )
    return m.match_function(target, candidate, image=image, target_va=0x401000)


@pytest.mark.parametrize("kind,bad_addend", [("string", 1), ("float", 4)])
def test_content_reference_must_apply_addend(kind, bad_addend):
    assert content_reference(kind, 0).exact
    result = content_reference(kind, bad_addend)
    assert not result.exact, summarize(result)


def alias_reference(wrong, *, same_section=False, helper_code=None):
    caller = bytes.fromhex("6800000000c3")
    helper = helper_code or bytes.fromhex("a100000000c3")
    obj = m.CoffObject(
        (
            m.CoffSection(".text", caller, 0x20, (m.CoffRelocation(1, 1, 0x06),)),
            m.CoffSection(
                ".text$helper", helper, 0x20, (m.CoffRelocation(1, 2, 0x06),)
            ),
        ),
        (
            m.CoffSymbol(0, "_foo", 0, 1, 0x20, 2),
            m.CoffSymbol(1, "_$E1", 0, 2, 0x20, 3),
            m.CoffSymbol(2, "_wrong_global" if wrong else "_right_global", 0, 0, 0, 2),
        ),
    )
    if same_section:
        obj = m.CoffObject(
            (
                m.CoffSection(
                    ".text",
                    caller + helper,
                    0x20,
                    (m.CoffRelocation(1, 1, 0x06), m.CoffRelocation(7, 2, 0x06)),
                ),
            ),
            (
                obj.symbols[0],
                replace(obj.symbols[1], value=len(caller), section_number=1),
                obj.symbols[2],
            ),
        )
    references = m.ReferenceSymbolManifest(
        "test",
        (
            m.ReferenceSymbol(0x402000, "handler", "function_alias", size=len(helper)),
            m.ReferenceSymbol(0x403000, "right_global", "data", size=4),
            m.ReferenceSymbol(0x403004, "wrong_global", "data", size=4),
        ),
    )
    mapped = bytearray(0x4000)
    mapped[0x2000:0x2006] = bytes.fromhex("a100304000c3")
    return m.match_function(
        bytes.fromhex("6800204000c3"),
        m.extract_object_function(obj, "foo", reference_manifest=references),
        image=m.LoadedImage(bytes(mapped), 0x400000, len(mapped)),
        target_va=0x401000,
        reference_manifest=references,
    )


def test_helper_alias_must_audit_nested_reference():
    assert alias_reference(False).exact
    result = alias_reference(True)
    assert not result.exact, summarize(result)


def external_call(relocation_type):
    obj = m.CoffObject(
        (
            m.CoffSection(
                ".text",
                bytes.fromhex("e800000000c3"),
                0x20,
                (m.CoffRelocation(1, 1, relocation_type),),
            ),
        ),
        (
            m.CoffSymbol(0, "_foo", 0, 1, 0x20, 2),
            m.CoffSymbol(1, "_helper", 0, 0, 0x20, 2),
        ),
    )
    references = m.ReferenceSymbolManifest(
        "test", (m.ReferenceSymbol(0x401010, "helper", "function"),)
    )
    return m.match_function(
        bytes.fromhex("e80b000000c3"),
        m.extract_object_function(obj, "foo", reference_manifest=references),
        image=m.LoadedImage(bytes(0x3000), 0x400000, 0x3000),
        target_va=0x401000,
        reference_manifest=references,
    )


@pytest.mark.parametrize("bad_type", [0x06, 0x07])
def test_relative_call_requires_rel32(bad_type):
    assert external_call(0x14).exact
    result = external_call(bad_type)
    assert not result.exact, summarize(result)


@pytest.mark.parametrize("kind,addend", [("string", 1), ("float", 4)])
def test_interior_content_reference_accepts_only_the_effective_destination(
    kind, addend
):
    assert content_reference(kind, addend, target_addend=addend).exact
    # A symbol at a later byte with a signed negative addend still points at base.
    assert content_reference(kind, -addend, symbol_value=addend).exact
    assert not content_reference(kind, 100).exact


def test_same_section_helper_alias_audits_references():
    assert alias_reference(False, same_section=True).exact
    result = alias_reference(True, same_section=True)
    assert not result.exact
    assert result.masked_operand_audit.mismatch_count == 1


def test_helper_evidence_survives_detailed_cache_roundtrip():
    audit = alias_reference(False).masked_operand_audit
    restored = m._masked_audit_from_cache(m._masked_audit_cache_payload(audit))
    assert restored == audit
    entry = restored.entries[0]
    assert (
        m._reference_status(
            entry.target_references, entry.candidate_references, strict=True
        )
        == "ok"
    )
    changed = replace(entry.candidate_references[0], code_evidence=None)
    assert (
        m._reference_status(entry.target_references, (changed,), strict=True)
        == "unresolved"
    )


def test_helper_alias_requires_equal_encodings_and_decodable_body():
    # Different SIB encodings can have identical normalized text.
    for bad_helper in (bytes.fromhex("8b040ec3"), bytes.fromhex("8b0431c30f")):
        native = bytes.fromhex("8b0431c3")
        obj = m.CoffObject(
            (
                m.CoffSection(
                    ".text",
                    bytes.fromhex("6800000000c3"),
                    0x20,
                    (m.CoffRelocation(1, 1, 0x06),),
                ),
                m.CoffSection(".text$helper", bad_helper, 0x20, ()),
            ),
            (
                m.CoffSymbol(0, "_foo", 0, 1, 0x20, 2),
                m.CoffSymbol(1, "_$E1", 0, 2, 0x20, 3),
            ),
        )
        mapped = bytearray(0x3000)
        mapped[0x2000:0x2004] = native
        refs = m.ReferenceSymbolManifest(
            "test", (m.ReferenceSymbol(0x402000, "helper", "function_alias", size=4),)
        )
        result = m.match_function(
            bytes.fromhex("6800204000c3"),
            m.extract_object_function(obj, "foo"),
            image=m.LoadedImage(bytes(mapped), 0x400000, len(mapped)),
            target_va=0x401000,
            reference_manifest=refs,
        )
        assert not result.exact


@pytest.mark.parametrize("bad_type", [None, 0x06, 0x07])
def test_local_relative_branch_requires_rel32(bad_type):
    candidate = m.ObjectFunction(
        "foo",
        bytes.fromhex("e90000000090c3"),
        frozenset({1}),
        (
            m.ObjectRelocationReference(
                1,
                "$Lret",
                "sym:$Lret",
                "name:$Lret",
                True,
                0,
                symbol_offset=6,
                relocation_type=bad_type,
            ),
        ),
    )
    image = m.LoadedImage(bytes(0x3000), 0x400000, 0x3000)
    target = bytes.fromhex("e90100000090c3")
    assert not m.match_function(
        target, candidate, image=image, target_va=0x401000
    ).exact
    good = replace(
        candidate,
        relocation_references=(
            replace(candidate.relocation_references[0], relocation_type=0x14),
        ),
    )
    assert m.match_function(target, good, image=image, target_va=0x401000).exact


def test_recursive_local_branch_has_a_bounded_exact_proof():
    # push local helper; helper calls itself. Neither extraction nor evidence
    # generation may recurse forever or grant unbounded reference proof.
    obj = m.CoffObject(
        (
            m.CoffSection(
                ".text",
                bytes.fromhex("6800000000c3"),
                0x20,
                (m.CoffRelocation(1, 1, 0x06),),
            ),
            m.CoffSection(
                ".text$helper",
                bytes.fromhex("e800000000c3"),
                0x20,
                (m.CoffRelocation(1, 1, 0x14),),
            ),
        ),
        (
            m.CoffSymbol(0, "_foo", 0, 1, 0x20, 2),
            m.CoffSymbol(1, "_$E1", 0, 2, 0x20, 3),
        ),
    )
    refs = m.ReferenceSymbolManifest(
        "test", (m.ReferenceSymbol(0x402000, "helper", "function_alias", size=6),)
    )
    mapped = bytearray(0x3000)
    mapped[0x2000:0x2006] = bytes.fromhex("e8fbffffffc3")
    result = m.match_function(
        bytes.fromhex("6800204000c3"),
        m.extract_object_function(obj, "foo"),
        image=m.LoadedImage(bytes(mapped), 0x400000, len(mapped)),
        target_va=0x401000,
        reference_manifest=refs,
    )
    # Local self-calls have a proven function-relative target and require no
    # recursive external reference. The finite extractor still handles them.
    assert result.exact


def test_cyclic_address_alias_stays_unresolved():
    obj = m.CoffObject(
        (
            m.CoffSection(
                ".text",
                bytes.fromhex("6800000000c3"),
                0x20,
                (m.CoffRelocation(1, 1, 0x06),),
            ),
            m.CoffSection(
                ".text$helper",
                bytes.fromhex("6800000000c3"),
                0x20,
                (m.CoffRelocation(1, 1, 0x06),),
            ),
        ),
        (
            m.CoffSymbol(0, "_foo", 0, 1, 0x20, 2),
            m.CoffSymbol(1, "_$E1", 0, 2, 0x20, 3),
        ),
    )
    refs = m.ReferenceSymbolManifest(
        "test", (m.ReferenceSymbol(0x402000, "helper", "function_alias", size=6),)
    )
    mapped = bytearray(0x3000)
    mapped[0x2000:0x2006] = bytes.fromhex("6800204000c3")
    result = m.match_function(
        bytes.fromhex("6800204000c3"),
        m.extract_object_function(obj, "foo"),
        image=m.LoadedImage(bytes(mapped), 0x400000, len(mapped)),
        target_va=0x401000,
        reference_manifest=refs,
    )
    assert not result.exact
    assert result.masked_operand_audit.unresolved_count == 1


def rdata_double_reference(candidate_value, target_value=0.25):
    code = bytes.fromhex("dd0500000000c3")  # fld qword [ADDR]; ret
    obj = m.CoffObject(
        (
            m.CoffSection(".text", code, 0x20, (m.CoffRelocation(2, 1, 0x06),)),
            m.CoffSection(".rdata", struct.pack("<d", candidate_value), 0x40, ()),
        ),
        (
            m.CoffSymbol(0, "_foo", 0, 1, 0x20, 2),
            m.CoffSymbol(1, "__real@8@x", 0, 2, 0, 3),
        ),
    )
    mapped = bytearray(0x3000)
    mapped[0x2000:0x2008] = struct.pack("<d", target_value)
    image = m.LoadedImage(
        bytes(mapped),
        0x400000,
        len(mapped),
        sections=(m.ImageSection(".rdata", 0x402000, 0x403000, 0x40),),
    )
    return m.match_function(
        bytes.fromhex("dd0500204000c3"),
        m.extract_object_function(obj, "foo"),
        image=image,
        target_va=0x401000,
    )


def test_wide_constant_identity_covers_every_read_byte():
    # 0.25 and 0.5 share a zero low dword; only the high dword differs.
    assert rdata_double_reference(0.25).exact
    result = rdata_double_reference(0.5)
    assert not result.exact, summarize(result)


def string_literal_reference(literal):
    obj = m.CoffObject(
        (
            m.CoffSection(".text", bytes.fromhex("b800000000c3"), 0x20,
                          (m.CoffRelocation(1, 1, 0x06),)),
            m.CoffSection(".data", literal, 0x40, ()),
        ),
        (
            m.CoffSymbol(0, "_foo", 0, 1, 0x20, 2),
            m.CoffSymbol(1, "$SG1", 0, 2, 0, 3),
        ),
    )
    mapped = bytearray(0x3000)
    mapped[0x2000:0x2008] = b"hello\0\0\0"
    image = m.LoadedImage(
        bytes(mapped),
        0x400000,
        len(mapped),
        sections=(m.ImageSection(".rdata", 0x402000, 0x403000, 0x40),),
    )
    return m.match_function(
        bytes.fromhex("b800204000c3"),
        m.extract_object_function(obj, "foo"),
        image=image,
        target_va=0x401000,
    )


def test_string_literal_identity_includes_data_after_the_first_nul():
    assert string_literal_reference(b"hello\0\0\0").exact
    result = string_literal_reference(b"hello\0evil\0")
    assert not result.exact, summarize(result)


def cpp_member_call(candidate_name, aliases):
    obj = m.CoffObject(
        (
            m.CoffSection(".text", bytes.fromhex("e800000000c3"), 0x20,
                          (m.CoffRelocation(1, 1, 0x14),)),
        ),
        (
            m.CoffSymbol(0, "_foo", 0, 1, 0x20, 2),
            m.CoffSymbol(1, candidate_name, 0, 0, 0x20, 2),
        ),
    )
    references = m.ReferenceSymbolManifest(
        "test", (m.ReferenceSymbol(0x401010, "set_owner", "function", aliases),)
    )
    return m.match_function(
        bytes.fromhex("e80b000000c3"),
        m.extract_object_function(obj, "foo", reference_manifest=references),
        image=m.LoadedImage(bytes(0x3000), 0x400000, 0x3000),
        target_va=0x401000,
        reference_manifest=references,
    )


def test_cpp_member_identity_keeps_its_owner():
    assert m._canonical_symbol_name("?Set@Owner@@QAEXXZ") == "Owner_Set"
    assert m._canonical_symbol_name("__foo") == "_foo"
    aliases = ("Set", "Owner_Set")
    assert cpp_member_call("?Set@Owner@@QAEXXZ", aliases).exact
    result = cpp_member_call("?Set@Other@@QAEXXZ", aliases)
    assert not result.exact, summarize(result)


def test_recorded_decorated_spelling_rejects_other_overloads():
    aliases = ("?Set@Owner@@QAEXH@Z",)
    assert cpp_member_call("?Set@Owner@@QAEXH@Z", aliases).exact
    result = cpp_member_call("?Set@Owner@@QAEXM@Z", aliases)
    assert not result.exact, summarize(result)
