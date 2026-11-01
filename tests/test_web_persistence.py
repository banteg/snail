"""Exercise the production save code in Chromium's IndexedDB."""

import os
import queue
import shutil
import subprocess
import threading
from functools import partial
from http.server import SimpleHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path

import pytest

from snail.symbols import REPO_ROOT


def test_browser_saves_do_not_overwrite_other_tabs(tmp_path):
    chrome = (
        os.environ.get("CHROME_BIN")
        or shutil.which("chromium")
        or shutil.which("google-chrome")
    )
    if chrome is None:
        mac_chrome = Path(
            "/Applications/Google Chrome.app/Contents/MacOS/Google Chrome"
        )
        if not mac_chrome.is_file():
            pytest.skip("requires Chromium or CHROME_BIN")
        chrome = str(mac_chrome)
    web = tmp_path / "web"
    web.mkdir()
    for source in ("tests/web_persistence.html", "port/web/storage.js"):
        shutil.copy(REPO_ROOT / source, web)
    result = queue.Queue()

    class Handler(SimpleHTTPRequestHandler):
        def do_POST(self):
            result.put(self.rfile.read(int(self.headers["Content-Length"])).decode())
            self.send_response(204)
            self.end_headers()

    server = ThreadingHTTPServer(("127.0.0.1", 0), partial(Handler, directory=str(web)))
    threading.Thread(target=server.serve_forever, daemon=True).start()
    try:
        browser = subprocess.Popen(
            [
                chrome,
                "--headless",
                "--disable-gpu",
                "--disable-background-networking",
                "--no-first-run",
                f"--user-data-dir={tmp_path / 'chrome'}",
                f"http://127.0.0.1:{server.server_port}/web_persistence.html",
            ]
        )
        try:
            assert result.get(timeout=30) == "PASS"
        finally:
            browser.kill()
            browser.wait(timeout=10)
    finally:
        server.shutdown()
        server.server_close()
