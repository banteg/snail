"""The recovered source tree stays consistent with link order and scratch configs."""

from snail.decomp_layout import build_layout, layout_problems, order_problems
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
    assert {unit["sequence"] for unit in layout["units"]} == {"game", "engine", "d3dx8"}


def test_order_problems_flag_objects_out_of_alphabetical_order():
    link_order = {
        "sequences": [
            {"name": "game", "start": "0x1000", "order": "alphabetical"},
            {"name": "lib", "start": "0x3000", "order": "library"},
        ],
        "objects": [
            {"object": "Golb.o", "start": "0x1000"},
            {"object": None, "candidate": "GDX.o", "start": "0x1100"},
            {"object": None, "start": "0x1200"},
            {"object": "GUI.o", "start": "0x1300"},
            {"object": "zeta.obj", "start": "0x3000"},
            {"object": "alpha.obj", "start": "0x3100"},
        ],
    }
    assert order_problems(link_order) == ["GDX does not sort after Golb in the game link order"]
