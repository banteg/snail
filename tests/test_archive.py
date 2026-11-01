from __future__ import annotations

import json
from pathlib import Path

import pytest

from snail.archive import extract_archive, parse_archive_index, read_archive_entry, write_archive
from snail.recon import inspect_path


ARCHIVE_PATH = Path(__file__).resolve().parents[1] / "artifacts/bin/SnailMail.dat"


@pytest.mark.parametrize("name", ["../OUTSIDE", "/OUTSIDE", r"C:\OUTSIDE", r"..\OUTSIDE", "manifest.json", "ONE/../TWO"])
def test_unsafe_entries_rejected_before_extracting_anything(tmp_path, name):
    source = tmp_path / "source.dat"
    output = tmp_path / "out"
    write_archive(source, {"SAFE": b"first", name: b"unexpected"})
    with pytest.raises(ValueError, match="archive path"):
        extract_archive(source, output)
    assert not output.exists()
    assert not (tmp_path / "OUTSIDE").exists()


@pytest.mark.parametrize("link", ["PARENT", "PARENT/FILE", "manifest.json"])
def test_existing_symlinks_cannot_redirect_writes(tmp_path, link):
    source = tmp_path / "source.dat"
    write_archive(source, {"SAFE": b"first", "PARENT/FILE": b"unexpected"})
    output = tmp_path / "out"
    symlink = output / link
    symlink.parent.mkdir(parents=True)
    outside = tmp_path / "outside"
    outside.mkdir()
    sentinel = outside / "FILE"
    sentinel.write_bytes(b"original")
    symlink.symlink_to(outside if link == "PARENT" else sentinel, target_is_directory=link == "PARENT")
    with pytest.raises(ValueError, match="symlink"):
        extract_archive(source, output)
    assert sentinel.read_bytes() == b"original"
    assert not (output / "SAFE").exists()


def test_existing_hardlink_is_replaced_without_modifying_other_link(tmp_path):
    source = tmp_path / "source.dat"
    write_archive(source, {"FILE": b"new"})
    output = tmp_path / "out"
    output.mkdir()
    sentinel = tmp_path / "sentinel"
    sentinel.write_bytes(b"original")
    (output / "FILE").hardlink_to(sentinel)
    extract_archive(source, output)
    assert (output / "FILE").read_bytes() == b"new"
    assert sentinel.read_bytes() == b"original"


@pytest.mark.local_artifacts
def test_parse_archive_index_matches_known_layout() -> None:
    index = parse_archive_index(ARCHIVE_PATH)

    assert index.entry_count == 603
    assert index.index_size == 20789
    assert index.entries[0].path == "MUSIC/1.OGG"
    assert index.entries[0].data_offset == 20789
    assert index.entries[0].size == 246566
    assert index.entries[-1].path == "BASS.DLL"
    assert index.entries[-1].size == 97848


@pytest.mark.local_artifacts
def test_read_archive_entry_decodes_representative_formats() -> None:
    index = parse_archive_index(ARCHIVE_PATH)

    ogg = read_archive_entry(ARCHIVE_PATH, index.entry_by_path("MUSIC/1.OGG"))
    texture = read_archive_entry(
        ARCHIVE_PATH,
        index.entry_by_path("OBJECTS/FONT/FONT-MENU-HOVER.TGA"),
    )
    script = read_archive_entry(ARCHIVE_PATH, index.entry_by_path("VOICE/_VOICE.TXT"))
    dll = read_archive_entry(ARCHIVE_PATH, index.entry_by_path("BASS.DLL"))

    assert ogg.startswith(b"OggS")
    assert texture[:3] == b"\x00\x00\x02"
    assert script.startswith(b"/* Voice Script */")
    assert dll.startswith(b"MZ")


@pytest.mark.local_artifacts
def test_extract_archive_writes_files_and_manifest(tmp_path: Path) -> None:
    manifest = extract_archive(
        archive_path=ARCHIVE_PATH,
        output_dir=tmp_path,
        prefix="OBJECTS/FONT3D",
    )

    extracted = tmp_path / "OBJECTS/FONT3D/_OBJECT.TXT"
    manifest_path = tmp_path / "manifest.json"

    assert extracted.exists()
    assert extracted.read_text(encoding="ascii").startswith("****************")
    assert manifest["written_files"] == 2
    assert json.loads(manifest_path.read_text(encoding="utf-8"))["prefix"] == "OBJECTS/FONT3D"


@pytest.mark.local_artifacts
def test_inspect_path_reports_archive_summary() -> None:
    report = inspect_path(ARCHIVE_PATH)

    assert report["kind"] == "blob"
    assert report["archive"]["entry_count"] == 603
    assert report["archive"]["extensions"][".txt"] == 204
