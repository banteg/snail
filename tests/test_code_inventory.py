import pytest

from snail.code_inventory import DENOMINATOR_CLASSES, merge_ranges, partition_section


def totals(partition):
    return {
        "all": sum(b - a for a, b, *_ in partition),
        "denominator": sum(b - a for a, b, kind, _ in partition if kind in DENOMINATOR_CLASSES),
    }


def test_three_analyzer_union_keeps_disagreements_and_unknowns():
    # BN alone identifies [0,2), IDA [2,4), Ghidra [4,6).
    # The unknown [6,8) must not disappear; only the last two bytes are padding.
    result = partition_section(
        0, 10, [[0, 2]],
        [[0, 2, "alignment"], [2, 4, "code"], [4, 6, "data"],
         [6, 8, "unknown"], [8, 10, "alignment"]],
        [[0, 4, "unknown"], [4, 6, "code"], [6, 10, "unknown"]],
    )
    assert totals(result) == {"all": 10, "denominator": 8}
    assert result[0][2] == "disputed_code"
    assert any(row[2] == "unclassified" for row in result)


def test_shared_tails_and_overlapping_functions_are_counted_once():
    classification = [[100, 120, "unknown"]]
    result = partition_section(
        100, 120, [[95, 110], [105, 115], [105, 115], [115, 125]],
        classification, classification,
    )
    assert totals(result) == {"all": 20, "denominator": 20}
    assert merge_ranges([[10, 20], [5, 15], [20, 25]]) == [[5, 25]]


def test_noncode_disagreement_is_not_excluded():
    result = partition_section(0, 4, [], [[0, 4, "data"]], [[0, 4, "alignment"]])
    assert totals(result)["denominator"] == 4
    assert result[0][2] == "unclassified"


@pytest.mark.parametrize("broken", [
    [[0, 3, "code"]],
    [[0, 2, "code"], [3, 4, "data"]],
    [[0, 3, "code"], [2, 4, "data"]],
    [[0, 5, "code"]],
])
def test_incomplete_or_overlapping_analyzer_partition_fails(broken):
    with pytest.raises(ValueError, match="classification"):
        partition_section(0, 4, [], broken, [[0, 4, "unknown"]])


def test_identified_data_is_excluded_only_without_any_code_claim():
    result = partition_section(
        0, 8, [[0, 2]], [[0, 8, "data"]], [[0, 8, "unknown"]],
    )
    assert totals(result) == {"all": 8, "denominator": 2}
