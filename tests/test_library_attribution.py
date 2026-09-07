from snail.library_attribution import resolve

BASE = 0x44e950


def candidate(address, symbol, *, size=48, refs=()):
    return {"address": address, "symbol": symbol, "size": size, "refs": list(refs)}


def reference(symbol, target, **changes):
    return {"symbol": symbol, "target": target, "addend": 0, "type": 20,
            "data_hex": None, "readonly": False, **changes}


def run(*rows, image=b"", image_base=0):
    return resolve([{"id": "d3dx8", "matches": rows}], image, image_base, {}, anchors={})


def test_relocation_target_disambiguates_identical_wrappers():
    result = run(
        candidate(BASE, "read", size=5, refs=[reference("read_impl", BASE + 0x100)]),
        candidate(BASE, "write", size=5, refs=[reference("write_impl", BASE + 0x100)]),
        candidate(BASE + 0x100, "read_impl"),
    )
    assert [(r["address"], r["symbol"]) for r in result["accepted"]] == [(BASE, "read"), (BASE + 0x100, "read_impl")]
    assert result["rejected_candidates"][0]["symbol"] == "write"


def test_short_unique_getter_requires_incoming_identity_evidence():
    getter = candidate(BASE + 0x100, "getter", size=6)
    assert not run(getter)["accepted"]
    result = run(getter, candidate(BASE, "caller", refs=[reference("getter", BASE + 0x100)]))
    assert {r["symbol"] for r in result["accepted"]} == {"caller", "getter"}


def test_generic_game_body_cannot_become_library_from_archive_similarity():
    result = run(candidate(0x408000, "library_noop", size=64))
    assert result["accepted"] == []


def test_string_mismatch_rejects_otherwise_unique_body():
    row = candidate(BASE, "png_init", refs=[reference("??_C@version", 0x500000, type=6, data_hex="312e322e3500")])
    assert not run(row, image=b"1.0.5\0", image_base=0x500000)["accepted"]
    valid = run(row, image=b"1.2.5\0", image_base=0x500000)
    assert valid["accepted"][0]["consistent_references"][0]["kind"] == "data"


def test_unknown_references_stay_explicit_and_do_not_resolve_short_body():
    ref = reference("unknown", 0x500000)
    assert not run(candidate(BASE, "wrapper", size=5, refs=[ref]))["accepted"]
    large = run(candidate(BASE, "large_body", refs=[ref]))["accepted"][0]
    assert large["unresolved_references"] == [{"symbol": "unknown", "target": 0x500000}]
    assert "matched" not in large


def test_two_named_incoming_identities_leave_folded_body_ambiguous():
    result = run(candidate(BASE, "owner", refs=[reference("left", BASE + 0x100), reference("right", BASE + 0x100)]),
                 candidate(BASE + 0x100, "left", size=6), candidate(BASE + 0x100, "right", size=6))
    assert [r["symbol"] for r in result["accepted"]] == ["owner"]
    assert str(BASE + 0x100) in result["remaining_candidates"]
