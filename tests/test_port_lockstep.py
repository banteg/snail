"""The lockstep capture script carries the current generated layout and parses."""

import shutil
import subprocess

import pytest

from snail.port_lockstep import SCRIPT, script_text
from snail.symbols import REPO_ROOT


@pytest.mark.skipif(shutil.which("zig") is None or shutil.which("node") is None, reason="needs zig and node")
def test_capture_script_layout_is_current():
    assert (REPO_ROOT / SCRIPT).read_text() == script_text(REPO_ROOT)


@pytest.mark.skipif(shutil.which("node") is None, reason="needs node")
def test_capture_script_parses():
    subprocess.run(["node", "--check", str(REPO_ROOT / SCRIPT)], check=True)
