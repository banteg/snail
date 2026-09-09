"""Do not fabricate code adjacency while searching discontiguous ranges."""

import importlib.util
import sys
from pathlib import Path

import pytest

TOOL_ROOT = Path(__file__).resolve().parents[1] / "tools/match"
sys.path.insert(0, str(TOOL_ROOT))
try:
    SPEC = importlib.util.spec_from_file_location(
        "snail_test_scan_call_continuations", TOOL_ROOT / "scan_call_continuations.py",
    )
    scanner = importlib.util.module_from_spec(SPEC)
    SPEC.loader.exec_module(scanner)
finally:
    sys.path.remove(str(TOOL_ROOT))


def fixture():
    # jne alternate; ordinary argument; common receiver/call; ret;
    # alternate: mov edx,[esp+4]; push edx; jmp common receiver.
    return scanner.p.decode(bytes.fromhex(
        "7510 8b442404 50 b978563412 e800000000 c3 8b542404 52 ebee"
    ), 0x1000)


def test_backward_argument_continuation_after_return_is_found():
    result = scanner.scan_instructions(fixture())
    assert len(result) == 1
    assert result[0]["branch"]["address"] == "0x1000"
    assert result[0]["receiver"]["address"] == "0x1007"
    assert result[0]["call"]["address"] == "0x100c"


@pytest.mark.parametrize("gap", ["alternate", "receiver"])
def test_discontiguous_instruction_fragments_cannot_form_a_continuation(gap):
    instructions = fixture()
    if gap == "alternate":
        # The same mnemonics survive, but the JMP is physically elsewhere.
        instructions[-1] = scanner.p.decode(bytes.fromhex("ebe9"), 0x101C)[0]
    else:
        instructions[4] = scanner.p.decode(bytes.fromhex("e800000000"), 0x100D)[0]
    assert scanner.scan_instructions(instructions) == []


def test_alternate_argument_must_push_the_loaded_register():
    instructions = fixture()
    instructions[-2] = scanner.p.decode(bytes.fromhex("51"), 0x1016)[0]
    assert scanner.scan_instructions(instructions) == []


def test_incomplete_alternate_block_is_not_a_positive_control():
    assert scanner.scan_instructions(fixture()[:-1]) == []


def test_source_change_during_compilation_invalidates_the_search(tmp_path, monkeypatch):
    directory = tmp_path / "scratches" / "one"
    directory.mkdir(parents=True)
    (directory / "scratch.conf").write_text("FUNCTION=one\n")
    source = directory / "scratch.cpp"
    source.write_text("void one() {}\n")
    obj = directory / "scratch.obj"
    obj.write_bytes(b"untrusted object bytes")
    monkeypatch.setattr(scanner.p, "DEFAULT_MATCH_ROOT", tmp_path)
    monkeypatch.setattr(scanner, "scratch_dependency_sha256",
                        lambda config: scanner.p.digest(source.read_bytes()))

    def compile_changed_source(config):
        source.write_text("void one() { changed(); }\n")
        return obj

    monkeypatch.setattr(scanner, "compile_scratch", compile_changed_source)
    with pytest.raises(ValueError, match="source inputs changed"):
        scanner.scan_sources()
