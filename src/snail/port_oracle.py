"""Run the port's replay oracle over the original's recorded high-score runs.

The fixtures in tests/fixtures/replays are score banks the original Windows
game wrote (ScoreA.dat postal, ScoreB.dat challenge). Each high-score record
embeds its run as per-tick samples. For each record, the headless port replays
it (port/shell/replay_oracle.cpp) and compares its simulated z, tick by tick,
with the z the original recorded; see docs/port/README.md, "Oracles".
"""

import re
import subprocess
import tempfile
from concurrent.futures import ThreadPoolExecutor
from dataclasses import dataclass
from pathlib import Path

FIXTURES = Path("tests/fixtures/replays")
BANKS = {"A": "ScoreA.windows-2026-04-17.dat", "B": "ScoreB.windows-2026-04-17.dat"}
WASM = Path("port/zig-out/bin/snail.wasm")
RUNNER = Path("port/shell/run.mjs")
SCRIPT = Path("port/scripts/high_scores.keys")
ARCHIVE = Path("artifacts/bin/SnailMail.dat")
ROWS = 10

STARTED = re.compile(r"oracle: replaying \w+ #\d+: score (\d+), level (\d+), mode (\d+), (\d+) samples")
SUMMARY = re.compile(
    r"oracle: compared (\d+) of (\d+) samples up to the run's end \((\d+) recorded\); "
    r"max \|dz\| ([\d.]+) at sample (-?\d+)"
)
DIVERGENCE = re.compile(r"oracle: first divergence at sample (\d+)")


@dataclass
class ReplayResult:
    spec: str
    score: int | None = None
    level: int | None = None
    samples: int = 0  # recorded
    run_samples: int = 0  # up to the run's end marker, where playback stops
    compared: int = 0
    max_error: float = 0.0
    max_error_sample: int = -1
    first_divergence: int | None = None
    error: str | None = None

    @property
    def matches(self) -> bool:
        return (
            self.error is None and self.compared > 0 and self.compared == self.run_samples
            and self.first_divergence is None
        )


def run_replay(root: Path, workdir: Path, spec: str, draw_distance: float = 1.0) -> ReplayResult | None:
    """Replay one record; None when the bank has no record in that row.

    `draw_distance` renders with the port's longer view, which must not change the run.
    """
    command = ["node", str(root / RUNNER), str(root / WASM), "--keys", str(root / SCRIPT), "--replay", spec]
    completed = subprocess.run(
        [*command, "--draw-distance", str(draw_distance)],
        cwd=workdir,
        capture_output=True,
        text=True,
        check=False,
    )
    output = completed.stderr
    result = ReplayResult(spec)
    if started := STARTED.search(output):
        result.score, result.level, _, result.samples = (int(g) for g in started.groups())
    elif "the replay never started" in output:
        return None
    if summary := SUMMARY.search(output):
        result.compared, result.run_samples, result.samples = int(summary[1]), int(summary[2]), int(summary[3])
        result.max_error, result.max_error_sample = float(summary[4]), int(summary[5])
    else:
        result.error = (output.strip().splitlines() or [f"exit {completed.returncode}"])[-1]
    if divergence := DIVERGENCE.search(output):
        result.first_divergence = int(divergence[1])
    return result


def stage(root: Path, workdir: Path) -> Path:
    """A game directory: the archive and the fixture score banks under their game names."""
    workdir.mkdir()
    (workdir / "SnailMail.dat").symlink_to((root / ARCHIVE).resolve())
    for letter, name in BANKS.items():
        (workdir / f"Score{letter}.dat").write_bytes((root / FIXTURES / name).read_bytes())
    return workdir


def run_oracle(
    root: Path, specs: list[str] | None = None, *, jobs: int = 8, draw_distance: float = 1.0
) -> list[ReplayResult]:
    specs = specs or [f"{letter}{row}" for letter in BANKS for row in range(1, ROWS + 1)]
    # The game writes (and deletes) tBass.dll where it runs, so each replay gets its own directory.
    with tempfile.TemporaryDirectory(prefix="snail-oracle-") as temp, ThreadPoolExecutor(jobs) as pool:
        results = list(
            pool.map(lambda spec: run_replay(root, stage(root, Path(temp) / spec), spec, draw_distance), specs)
        )
    return [result for result in results if result is not None]


def report_text(results: list[ReplayResult]) -> str:
    lines = [f"{'replay':7} {'score':>7} {'level':>5} {'run':>6} {'compared':>8} {'max |dz|':>9}  result"]
    for r in results:
        if r.error:
            verdict = f"error: {r.error}"
        elif r.first_divergence is not None:
            verdict = f"diverges from sample {r.first_divergence}"
        elif r.compared != r.run_samples:
            verdict = "playback stopped before the run's end"
        else:
            verdict = "matches"
        lines.append(
            f"{r.spec:7} {r.score or 0:>7} {r.level or 0:>5} {r.run_samples:>6} {r.compared:>8} {r.max_error:>9.4f}  {verdict}"
        )
    matched = sum(r.matches for r in results)
    ticks = sum(r.compared for r in results if r.matches)
    lines.append(f"{matched}/{len(results)} replays match the original ({ticks} ticks)")
    return "\n".join(lines)
