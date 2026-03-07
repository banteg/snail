from snail.recon import find_signature_offsets, shannon_entropy


def test_find_signature_offsets_respects_limit() -> None:
    data = b"BMxxxxBMxxxxBM"
    hits = find_signature_offsets(data, signatures={"bmp": b"BM"}, limit=2)

    assert len(hits) == 1
    assert hits[0].name == "bmp"
    assert hits[0].offsets == [0, 6]


def test_shannon_entropy_for_constant_data_is_zero() -> None:
    assert shannon_entropy(b"\x00" * 32) == 0.0


def test_shannon_entropy_for_balanced_two_symbol_data_is_one() -> None:
    assert shannon_entropy(b"\x00\x01" * 32) == 1.0
