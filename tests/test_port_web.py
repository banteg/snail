"""The browser build's server and the presenter's view of the render state."""

import re
import threading
import urllib.request
from functools import partial
from http.server import ThreadingHTTPServer

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
    archive.write_bytes(b"dat")

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
        with urllib.request.urlopen(f"{base}/SnailMail.dat") as response:
            assert response.read() == b"dat"
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
