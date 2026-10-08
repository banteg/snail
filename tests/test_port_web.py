"""The browser build's server and the presenter's view of the render state."""

import gzip
import re
import threading
import urllib.error
import urllib.request
from functools import partial
from http.server import ThreadingHTTPServer

from snail.archive import decode_bytes
from snail.port_serve import Handler, routes
from snail.symbols import REPO_ROOT


def test_routes_serve_page_build_and_archive(tmp_path):
    web = tmp_path / "port/web"
    web.mkdir(parents=True)
    (web / "index.html").write_text("<!doctype html>")
    (web / "snail.js").write_text("export {};")
    wasm = tmp_path / "port/zig-out/bin/snail-web.wasm"
    wasm.parent.mkdir(parents=True)
    wasm.write_bytes(b"\0asm")
    archive = tmp_path / "SnailMail.dat"
    archive.write_bytes(bytes(range(256)) * 3)

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
