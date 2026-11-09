import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).parents[1] / "tools/match/c2"))

pytestmark = pytest.mark.local_artifacts


@pytest.fixture
def scheduler_unit(tmp_path):
    scratch = tmp_path / "input"
    scratch.mkdir()
    (scratch / "scratch.cpp").write_text(
        """
struct A { int value(int); int other(int); };
struct B { int value(int); };
int A::value(int x) { return x * 3 + 1; }
int A::other(int x) { return x * 5 - 2; }
int B::value(int x) { return x * 7 + 3; }
"""
    )
    return scratch


@pytest.mark.parametrize(
    ("requested", "selected", "error"),
    [
        ("other", "?other@A@@QAEHH@Z", None),
        ("?value@B@@QAEHH@Z", "?value@B@@QAEHH@Z", None),
        ("value", None, "ambiguous function symbol"),
        ("missing", None, "no matching function symbol"),
    ],
)
def test_scheduler_records_only_the_selected_member(scheduler_unit, requested, selected, error):
    import schedtrace

    (scheduler_unit / "scratch.conf").write_text(
        f"FUNCTION=initialize_worm_path_template_pair\nSYMBOL={requested}\n"
    )
    out = scheduler_unit.parent / "trace"
    if error:
        with pytest.raises(ValueError, match=error):
            schedtrace.run_observer(scheduler_unit, out)
    else:
        receipt, _, data = schedtrace.run_observer(scheduler_unit, out)
        assert receipt["whole_coff_equal_except_timestamp"]
        assert {w["function"] for w in schedtrace.decode(data)} == {selected}
