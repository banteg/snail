"""port/patches/ applies by exact text to copies of the recovered sources."""

import pytest

from snail import port, port_patch
from snail.symbols import REPO_ROOT

PATCH = """Doubles the answer.

--- a/decomp/answer.cpp
+++ b/decomp/answer.cpp
@@ -1,3 +1,3 @@
 int answer()
 {
-    return 21;
+    return 42;
"""


def write_tree(root, source):
    (root / "port/patches").mkdir(parents=True)
    (root / "port/patches/01-answer.patch").write_text(PATCH)
    (root / "decomp/include").mkdir(parents=True)
    (root / "decomp/include/answer.h").write_text("int answer();\n")
    (root / "decomp/answer.cpp").write_text(source)


def test_patches_apply_to_copies_and_leave_the_source(tmp_path):
    source = "int answer()\n{\n    return 21;\n}\n"
    write_tree(tmp_path, source)
    port_patch.write(tmp_path, ["../decomp/answer.cpp"])
    patched = tmp_path / port_patch.PATCHED
    assert (patched / "decomp/answer.cpp").read_text() == "int answer()\n{\n    return 42;\n}\n"
    assert (patched / "decomp/include/answer.h").read_text() == "int answer();\n"
    assert (tmp_path / "decomp/answer.cpp").read_text() == source
    assert port_patch.compile_path("../decomp/answer.cpp") == "generated/patched/decomp/answer.cpp"
    assert port_patch.compile_path("shell/main.cpp") == "shell/main.cpp"


def test_a_hunk_must_match_exactly_once(tmp_path):
    write_tree(tmp_path, "int answer()\n{\n    return 21;\nint answer()\n{\n    return 21;\n}\n")
    with pytest.raises(ValueError, match="matches 2 times"):
        port_patch.write(tmp_path, ["../decomp/answer.cpp"])


def test_patches_only_reach_compiled_files(tmp_path):
    write_tree(tmp_path, "int answer()\n{\n    return 21;\n}\n")
    with pytest.raises(ValueError, match="does not compile"):
        port_patch.write(tmp_path, [])


def test_repository_patches_apply():
    hunks = port_patch.load(REPO_ROOT)
    assert hunks
    compiled = {source.removeprefix("../") for source in port.recovered_sources(REPO_ROOT)}
    for rel in hunks:
        assert rel in compiled or rel.startswith(f"{port_patch.INCLUDE.as_posix()}/"), rel
        port_patch.apply(rel, (REPO_ROOT / rel).read_text(encoding="latin-1"), hunks)
