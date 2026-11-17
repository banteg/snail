"""The replay oracle: report parsing, and one real replay when the build is present."""

import math
import shutil
import subprocess

import pytest

from snail import main, port_oracle
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


def test_missing_launch_fails_the_requested_replays(monkeypatch, capsys):
    completed = subprocess.CompletedProcess([], 1, stderr="oracle: the replay never started\n")
    monkeypatch.setattr(port_oracle.subprocess, "run", lambda *args, **kwargs: completed)
    assert main(["port", "oracle", "A10", "B1"]) == 1
    assert "0/2 replays match the original" in capsys.readouterr().out


def test_abnormal_exit_after_a_matching_summary(monkeypatch, tmp_path):
    output = "\n".join(line for line in OUTPUT.splitlines() if "first divergence" not in line)
    output = output.replace("0.5000 at sample 700; diverges", "0.0000 at sample -1; matches the original")
    completed = subprocess.CompletedProcess([], 1, stderr=output)
    monkeypatch.setattr(port_oracle.subprocess, "run", lambda *args, **kwargs: completed)
    result = port_oracle.run_replay(REPO_ROOT, tmp_path, "A8")
    assert not result.matches and "status 1" in result.error


@pytest.mark.skipif(shutil.which("zig") is None or shutil.which("node") is None, reason="needs zig and node")
def test_nonfinite_distance_fails_the_optimized_oracle(monkeypatch, tmp_path):
    # Drive the real oracle from its high-score launch through one corrupt simulation sample.
    source = tmp_path / "bad_position.cpp"
    source.write_text("""
#include <math.h>
#include <stdlib.h>
#include "game_root.h"
#include "replay_oracle.h"

cRGame* g_game;
void cRHighScore::UnInit() {}
float MathType16to32(short value, float scale) { return value / scale; }

int main() {
    g_game = (cRGame*)calloc(1, sizeof(cRGame));
    SubSolution* record = (SubSolution*)calloc(1, sizeof(SubSolution));
    record->replay_sample_count = 1;
    g_game->subgame.sub_high_score.active_record_bank = record;
    g_game->players[0].frontend_state = 19;
    replay_oracle_configure("A1");
    replay_oracle_tick(0);
    g_game->subgame.selected_level_record_active = 1;
    g_game->subgame.player.transform.position.z = NAN;
    replay_oracle_tick(1);
    return replay_oracle_report();
}
""")
    shell = REPO_ROOT / "port/shell"
    program = tmp_path / "oracle.wasm"
    subprocess.run([
        "zig", "c++", "-O3", "-target", "wasm32-wasi", "-std=c++17", "-fms-extensions", "-fdeclspec",
        "-DSNAIL_PORT", "-Wno-everything", f"-I{shell}", f"-I{REPO_ROOT / 'decomp/include'}",
        str(source), str(shell / "replay_oracle.cpp"), "-o", str(program),
    ], check=True)
    monkeypatch.setattr(port_oracle, "WASM", program)
    result = port_oracle.run_replay(REPO_ROOT, tmp_path, "A1")
    assert not result.matches and result.first_divergence == 0
    assert math.isinf(result.max_error)


@pytest.mark.skipif(
    shutil.which("node") is None
    or not (REPO_ROOT / port_oracle.WASM).exists()
    or not (REPO_ROOT / port_oracle.ARCHIVE).exists(),
    reason="needs node, the headless port build and SnailMail.dat",
)
def test_a_recorded_run_replays_like_the_original():
    (result,) = port_oracle.run_oracle(REPO_ROOT, ["A8"], jobs=1)
    assert result.matches, port_oracle.report_text([result])
