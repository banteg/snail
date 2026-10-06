"""The recovered source tree stays consistent with link order and scratch configs."""

from snail.decomp_layout import build_layout, layout_problems
from snail.symbols import REPO_ROOT


def test_committed_tree_matches_link_order_layout():
    assert layout_problems(REPO_ROOT) == []


def test_every_function_has_one_unit():
    layout = build_layout(REPO_ROOT)
    functions = [source["function"] for unit in layout["units"] for source in unit["sources"]]
    assert len(functions) == len(set(functions))
    names = [unit["name"].casefold() for unit in layout["units"]]
    # Unit directories must stay distinct on case-insensitive file systems.
    assert len(names) == len(set(names))
    assert {unit["sequence"] for unit in layout["units"]} == {"game", "engine"}
