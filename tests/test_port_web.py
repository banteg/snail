"""The browser build's server and the presenter's view of the render state."""

import gzip
import io
import re
import struct
import threading
import urllib.error
import urllib.request
from functools import partial
from http.server import ThreadingHTTPServer

from PIL import Image

from snail.archive import decode_bytes
from snail.port_serve import (
    CARD,
    CARD_HALVES,
    CARD_WIDTH,
    SPLASH_IMAGES,
    Handler,
    routes,
)
from snail.symbols import REPO_ROOT


def write_archive(path, files: dict[str, bytes]) -> None:
    """A SnailMail.dat: entry count, (path offset, data offset, size) records and paths, then the data, XOR-masked."""
    names = b"".join(name.encode() + b"\0" for name in files)
    index_size = 4 + 12 * len(files) + len(names)
    index, path_offset, data_offset = struct.pack("<I", len(files)), 4 + 12 * len(files), index_size
    for name, data in files.items():
        index += struct.pack("<III", path_offset, data_offset, len(data))
        path_offset += len(name) + 1
        data_offset += len(data)
    path.write_bytes(decode_bytes(index + names + b"".join(files.values())))


def tga(color) -> bytes:
    out = io.BytesIO()
    Image.new("RGB", (8, 8), color).save(out, "TGA")
    return out.getvalue()


def test_routes_serve_page_build_and_archive(tmp_path):
    web = tmp_path / "port/web"
    web.mkdir(parents=True)
    (web / "index.html").write_text("<!doctype html>")
    (web / "snail.js").write_text("export {};")
    wasm = tmp_path / "port/zig-out/bin/snail-web.wasm"
    wasm.parent.mkdir(parents=True)
    wasm.write_bytes(b"\0asm")
    archive = tmp_path / "SnailMail.dat"
    write_archive(archive, {path: tga((40, 10, 70)) for path in (*SPLASH_IMAGES.values(), *CARD_HALVES)})

    table = routes(tmp_path, archive)
    server = ThreadingHTTPServer(("127.0.0.1", 0), partial(Handler, table=table))
    threading.Thread(target=server.serve_forever, daemon=True).start()
    base = f"http://127.0.0.1:{server.server_port}"
    try:
        with urllib.request.urlopen(f"{base}/?warmup=0") as response:
            assert response.read() == b"<!doctype html>"
        with urllib.request.urlopen(f"{base}/snail.js") as response:
            assert response.headers["Content-Type"] == "text/javascript"
        with urllib.request.urlopen(f"{base}/snail-web.wasm") as response:
            assert response.headers["Content-Type"] == "application/wasm"
            assert response.read() == b"\0asm"
        with urllib.request.urlopen(f"{base}/SnailMail.dat.gz") as response:
            assert response.headers["Content-Type"] == "application/gzip"
            assert decode_bytes(gzip.decompress(response.read())) == archive.read_bytes()
        for name in SPLASH_IMAGES:  # the loading screen's textures, from the archive
            with urllib.request.urlopen(f"{base}/{name}") as response:
                assert response.headers["Content-Type"] == "image/avif"
                assert Image.open(io.BytesIO(response.read())).size == (8, 8)
        with urllib.request.urlopen(f"{base}/{CARD}") as response:  # the link-preview card, from the splash art
            assert response.headers["Content-Type"] == "image/jpeg"
            assert Image.open(io.BytesIO(response.read())).width == CARD_WIDTH
        (web / "added.js").write_text("export {};")  # files added after start are served
        with urllib.request.urlopen(f"{base}/added.js") as response:
            assert response.read() == b"export {};"
        for missing in ("/nothing.js", "/../pyproject.toml", "/.hidden"):
            try:
                urllib.request.urlopen(f"{base}{missing}")
                raise AssertionError(missing)
            except urllib.error.HTTPError as error:
                assert error.code == 404
    finally:
        server.shutdown()
        server.server_close()


def test_presenter_reads_the_render_state_layout():
    header = (REPO_ROOT / "port/shell/render_backend.h").read_text()
    renderer = (REPO_ROOT / "port/web/renderer.js").read_text()
    size = int(re.search(r"sizeof\(RenderState\) == (\d+)", header).group(1))
    words = int(re.search(r"const STATE_WORDS = (\d+);", renderer).group(1))
    fields = re.search(r"struct RenderState \{(.*?)\};", header, re.DOTALL).group(1)
    declared = sum(len(line.split(",")) for line in re.findall(r"^\s*(?:int|unsigned int|float) ([^;]+);", fields, re.MULTILINE))
    assert size == words * 4 == declared * 4
