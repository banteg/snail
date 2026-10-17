"""The Android release run headless (src/snail/android_game.py), the oracle for the Ultimate profile."""

import pytest

from snail import android_game

pytestmark = pytest.mark.skipif(
    not android_game.LIBRARY.exists() or not android_game.ARCHIVE.exists(),
    reason="needs the unpacked Android APK (libsnailmail.so and assets/asm.mp3)",
)


def test_tutorial_builds_padded_course_from_seed_zero(tmp_path):
    game = android_game.play(tmp_path, ["Play", "Tutorial"])
    (build,) = game.builds
    assert (build.name, build.mode) == ("Tutorial", 7)
    # Padding before each of the 22 listed segments (banteg/snail#98).
    assert (build.rows, build.segments) == (1340, 44)
    assert (build.seed, build.draws) == (0, 49)
    # The intro touch and two menu presses.
    assert [name for _, name in game.sounds[:3]] == ["highlight", "highlight", "select"]


def test_challenge_lays_its_finish_in_random_pick_sized_chunks(tmp_path):
    game = android_game.play(
        tmp_path,
        ["Play", "Challenge Mode", "Play"],
        seed=28745,
        tutorial_done=True,
        sliders=(50, 0.5, 50),
    )
    (build,) = game.builds
    assert (build.name, build.mode, build.rows, build.completion) == ("Challenge 0", 1, 2025, 1865)
    assert build.draws == 147
    assert build.tags.count("Segdif") == 36 and build.tags.count("Mirror") == 72
    # BuildLevel (0007e88c) ends each piece at the length of the segment it picked,
    # even past the finish line, where it lays the Finish segment's rows instead:
    # the 160 finish rows come in pieces as long as the picks and their Padding.
    finish = [length for first, length, _ in build.runs if first >= build.completion]
    assert finish == [37, 4, 24, 4, 37, 4, 50]
    assert sum(finish) == build.rows - build.completion
