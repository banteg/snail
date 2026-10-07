"""The replay oracle: report parsing, and one real replay when the build is present."""

import shutil

import pytest

from snail import port_oracle
from snail.symbols import REPO_ROOT

OUTPUT = """snail: world initialized
oracle: replaying postal #8: score 10540, level 8, mode 0, 849 samples
oracle: first divergence at sample 700 (tick 1500): port z 9.0000, original z 8.5000
oracle: compared 695 of 695 samples up to the run's end (849 recorded); max |dz| 0.5000 at sample 700; diverges
"""


def test_report_parsing(monkeypatch, tmp_path):
    class Completed:
        stderr = OUTPUT
        returncode = 3

    monkeypatch.setattr(port_oracle.subprocess, "run", lambda *args, **kwargs: Completed())
    result = port_oracle.run_replay(REPO_ROOT, tmp_path, "A8")
    assert (result.score, result.level, result.samples, result.run_samples) == (10540, 8, 849, 695)
    assert result.first_divergence == 700
    assert not result.matches
    assert "diverges from sample 700" in port_oracle.report_text([result])


def test_empty_rows_are_skipped(monkeypatch, tmp_path):
    class Completed:
        stderr = "oracle: the replay never started\n"
        returncode = 1

    monkeypatch.setattr(port_oracle.subprocess, "run", lambda *args, **kwargs: Completed())
    assert port_oracle.run_replay(REPO_ROOT, tmp_path, "A10") is None


@pytest.mark.skipif(
    shutil.which("node") is None
    or not (REPO_ROOT / port_oracle.WASM).exists()
    or not (REPO_ROOT / port_oracle.ARCHIVE).exists(),
    reason="needs node, the headless port build and SnailMail.dat",
)
def test_a_recorded_run_replays_like_the_original():
    (result,) = port_oracle.run_oracle(REPO_ROOT, ["A8"], jobs=1)
    assert result.matches, port_oracle.report_text([result])
