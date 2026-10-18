"""Path and camera rules in each profile, one tick at a time through the browser reactor (tests/port_path_rules.mjs)."""

import json
import math
import shutil
import struct
import subprocess

import pytest

from snail.symbols import REPO_ROOT

WASM = REPO_ROOT / "port/zig-out/bin/snail-web.wasm"
ASSETS = REPO_ROOT / "artifacts/bin"

pytestmark = pytest.mark.skipif(
    shutil.which("node") is None
    or not WASM.exists()
    or not all((ASSETS / name).exists() for name in ("SnailMail.dat", "SnailMailExtras.dat")),
    reason="needs browser WASM, node, and game archives",
)


@pytest.fixture(scope="module")
def layout(port_layout_env):
    return json.loads(port_layout_env["SNAIL_LAYOUT"])


@pytest.fixture(scope="module")
def rules(tmp_path_factory, port_layout_env):
    run = tmp_path_factory.mktemp("path-rules")
    # The reactor's file system is rooted at the run directory, so links out of it don't resolve.
    for name in ("SnailMail.dat", "SnailMailExtras.dat"):
        shutil.copyfile(ASSETS / name, run / name)
    # The harness opens Pro 1, which needs the Fluctuosa unlock.
    config = bytearray(196)
    struct.pack_into("<ff", config, 0, 1.0, 1.0)
    config[0x60:0x69] = b"Fluctuosa"
    struct.pack_into("<ifi", config, 0x40, 50, 0.5, 50)
    struct.pack_into("<ii", config, 0xA0, 50, 7)
    config[0xC0] = 1
    (run / "SnailMail.cfg").write_bytes(config)
    (run / "SnailMailMobile.cfg").write_bytes(config)
    result = subprocess.run(
        ["node", str(REPO_ROOT / "tests/port_path_rules.mjs"), str(WASM)],
        cwd=run,
        env=port_layout_env,
        capture_output=True,
        text=True,
        check=True,
    )
    return json.loads(result.stdout.splitlines()[-1])


def test_mobile_paths_carry_the_snail_across_their_width(rules):
    # Android's cRPath::GetNodes (0004e910) starts every sample at lateral_scale 1,
    # and BuildShimmy and BuildDetour rely on it; at 0 the snail rides the centre line.
    assert {name: values for name, values in rules["lateralScales"].items() if values != [1]} == {}


def test_ultimate_sbends_lift_the_camera_linearly(rules, layout):
    for name in ("SBEND", "SBEND1", "SBEND2", "SBEND4"):
        assert rules["kinds"][name] == layout["mobile_sbend"]
    sbend = rules["profiles"]["ultimate"]["sbend"]
    assert sbend["active"] == 1
    phase = (sbend["z"] - sbend["cellZ"]) / sbend["count"]
    assert 0 < phase < 1
    assert sbend["lift"] == pytest.approx(phase * 0.55, rel=1e-6)
    # The PC rule has no lift for the mobile kind.
    assert rules["profiles"]["original"]["sbend"]["lift"] == 0


def test_ultimate_camera_lift_eases_out_after_a_path(rules):
    ultimate, original = rules["profiles"]["ultimate"], rules["profiles"]["original"]
    assert ultimate["liftOffPath"] == pytest.approx(0.5 * 0.98)
    assert original["liftOffPath"] == 0
    # A supertramp's pitch cycle restarts the lift from 0 in both.
    assert ultimate["liftDuringPitch"] == original["liftDuringPitch"] > 0


def test_ultimate_paths_without_a_heading_keep_their_roll(rules):
    turnover = rules["turnover"]
    ride = rules["profiles"]["ultimate"]["turnover"]
    index = ride["index"]
    step = turnover["roll"][index + 1] - turnover["roll"][index]
    if step > math.pi:
        step -= 2 * math.pi
    elif step < -math.pi:
        step += 2 * math.pi
    alpha = ride["progress"] / turnover["deltaLength"][index]
    assert ride["roll"] == pytest.approx(turnover["roll"][index] + alpha * step, abs=1e-5)
    assert ride["roll"] < -1
    assert rules["profiles"]["original"]["turnover"]["roll"] == 0
    # An installed heading still sets the roll in both.
    for profile in rules["profiles"].values():
        ride = profile["turnoverWithHeading"]
        alpha = ride["progress"] / turnover["deltaLength"][ride["index"]]
        assert ride["roll"] == pytest.approx((alpha + ride["index"]) / turnover["count"], rel=1e-6)


def test_ultimate_snail_leaves_a_path_sideways_while_hovering(rules):
    assert rules["profiles"]["ultimate"]["hoverSideExit"]["active"] == 0
    assert rules["profiles"]["original"]["hoverSideExit"]["active"] == 1


def test_trampoline_rings_come_only_from_the_bounce(rules):
    ultimate, original = rules["profiles"]["ultimate"], rules["profiles"]["original"]
    for profile in (ultimate, original):
        assert profile["trampolineBounce"]["y"] == pytest.approx(-3 + 0.49)
        assert profile["noFallClamp"]["y"] == pytest.approx(0.49)
    assert ultimate["trampolineBounce"]["rings"] == 1
    # The no-fall clamp squashes the snail without a ring.
    assert ultimate["noFallClamp"]["rings"] == 0
    assert original["trampolineBounce"]["rings"] == original["noFallClamp"]["rings"] == 0


def test_ultimate_swept_path_reentry_plane_quad_and_seed(rules):
    ultimate, original = rules["profiles"]["ultimate"], rules["profiles"]["original"]
    # PC catches a frame early while the new position is still above the plane
    # (y = +0.05 > 0, next probe <= 0.001); Android requires crossing below it.
    assert original["reentryBeforeCrossing"]["active"] == 1
    assert ultimate["reentryBeforeCrossing"]["active"] == 0
    # Once the snail crosses below the plane (y = -0.05 < 0), both catch, and
    # Android seeds progress from the pre-move position instead of the new one.
    assert original["reentryAfterCrossing"]["active"] == 1
    assert ultimate["reentryAfterCrossing"]["active"] == 1
    assert ultimate["reentryAfterCrossing"]["progress"] < original["reentryAfterCrossing"]["progress"]
    # For width_cells = 2, Android's quad half-width is 1.0 (w * 0.5) whereas
    # the PC box accepts up to (2 / 2) + 0.3 = 1.3.
    assert original["reentryOutsideHalfWidth"]["active"] == 1
    assert ultimate["reentryOutsideHalfWidth"]["active"] == 0
