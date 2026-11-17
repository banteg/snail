from pathlib import Path

import pytest

from snail import port_serve


def test_failed_pack_keeps_previous_site_and_rejects_unrelated_output(tmp_path, monkeypatch):
    web = tmp_path / "port/web"
    web.mkdir(parents=True)
    (web / "index.html").write_text("new page")
    out = tmp_path / "site"
    out.mkdir()
    for name in ("index.html", "snail-web.wasm", "SnailMail.dat.gz"):
        (out / name).write_bytes(b"previous build")

    def build(argv, **kwargs):
        binary = Path(argv[-1]) / "bin/snail-web.wasm"
        binary.parent.mkdir(parents=True)
        binary.write_bytes(b"new wasm")

    monkeypatch.setattr(port_serve.subprocess, "run", build)
    archive = tmp_path / "SnailMail.dat"
    with pytest.raises(FileNotFoundError):
        port_serve.pack_site(tmp_path, out, archive)
    assert all(path.read_bytes() == b"previous build" for path in out.iterdir())

    unrelated = out / "saved-work"
    unrelated.write_text("keep")
    with pytest.raises(ValueError, match="outside a packed"):
        port_serve.pack_site(tmp_path, out, archive)
    assert unrelated.read_text() == "keep"

    unrelated.unlink()
    archive.write_bytes(b"test archive")
    monkeypatch.setattr(port_serve, "page_images", lambda archive: {"card.jpg": b"card"})
    port_serve.pack_site(tmp_path, out, archive)
    assert (out / "index.html").read_text() == "new page"
    assert (out / "snail-web.wasm").read_bytes() == b"new wasm"
    assert (out / "card.jpg").read_bytes() == b"card"
