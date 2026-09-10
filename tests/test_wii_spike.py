"""Keep the spelling adapter from silently changing a PowerPC condition."""

import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).parents[1] / "tools/wii"))
from spike import normalize_cror


def test_cror_aliases_preserve_encoded_condition():
    source = "/* 8000AA0C 00003F4C  4C 41 13 82 */\tcror eq, gt, eq\n"
    output, changes = normalize_cror(source)
    assert output == source.replace("eq, gt, eq", "2, 1, 2")
    assert changes == ["0x8000AA0C"]
    assert normalize_cror(output) == (output, [])


@pytest.mark.parametrize("encoded", ["4C 41 03 82", "00 00 00 00"])
def test_cror_alias_must_agree_with_native_operands(encoded):
    with pytest.raises(ValueError, match="does not encode"):
        normalize_cror(f"/* 8000AA0C 00003F4C  {encoded} */\tcror eq, gt, eq\n")


def test_unannotated_alias_cannot_be_rewritten():
    with pytest.raises(ValueError, match="does not encode"):
        normalize_cror("cror eq, gt, eq\n")
