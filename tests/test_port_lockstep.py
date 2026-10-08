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


def test_capture_script_calls_only_defined_functions():
    # A syntax check passes a script that calls a function an edit deleted
    # (version 3 lost bindWin32); Frida only fails once the game is running.
    import re

    text = (REPO_ROOT / SCRIPT).read_text()
    code = re.sub(r"//[^\n]*", "", text)
    defined = set(re.findall(r"function (\w+)\(", code)) | set(re.findall(r"(?:const|let) (\w+) =", code))
    called = set(re.findall(r"(?<![\w.])([a-z]\w*)\(", code))
    keywords = {"if", "for", "while", "switch", "catch", "function", "return", "typeof", "ptr", "setTimeout"}
    methods = {"onEnter", "onLeave"}  # hook callbacks, defined as object methods
    assert called - defined - keywords - methods == set()
