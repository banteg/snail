"""Serve the browser build of the port (port/web/) on localhost.

The page, the `snail-web.wasm` build and the original `SnailMail.dat` come
from three places; this maps them under one origin. Nothing is cached, so a
rebuild shows on reload.
"""

import mimetypes
from functools import partial
from http import HTTPStatus
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path

WEB = Path("port/web")
WASM = Path("port/zig-out/bin/snail-web.wasm")
ARCHIVE = Path("artifacts/bin/SnailMail.dat")
CONTENT_TYPES = {".js": "text/javascript", ".wasm": "application/wasm", ".dat": "application/octet-stream"}


def routes(root: Path, archive: Path) -> dict[str, Path]:
    """Fixed routes; any other top-level name is looked up in port/web/ per request."""
    return {
        "/": root / WEB / "index.html",
        "/snail-web.wasm": root / WASM,
        "/SnailMail.dat": archive,
        "": root / WEB,
    }


def resolve(table: dict[str, Path], request_path: str) -> Path | None:
    path = request_path.split("?", 1)[0]
    if path in table:
        return table[path]
    name = path.removeprefix("/")
    return table[""] / name if name and "/" not in name and not name.startswith(".") else None


class Handler(BaseHTTPRequestHandler):
    def __init__(self, *args, table: dict[str, Path], **kwargs):
        self.table = table
        super().__init__(*args, **kwargs)

    def do_GET(self):
        path = resolve(self.table, self.path)
        if path is None or not path.is_file():
            self.send_error(HTTPStatus.NOT_FOUND, f"{self.path} not found" + (f" ({path})" if path else ""))
            return
        body = path.read_bytes()
        self.send_response(HTTPStatus.OK)
        content_type = CONTENT_TYPES.get(path.suffix) or mimetypes.guess_type(path.name)[0] or "application/octet-stream"
        self.send_header("Content-Type", content_type)
        self.send_header("Content-Length", str(len(body)))
        self.send_header("Cache-Control", "no-store")
        self.end_headers()
        self.wfile.write(body)

    def log_message(self, format, *args):
        pass


def serve(root: Path, *, port: int, archive: Path | None = None) -> None:
    table = routes(root, archive or root / ARCHIVE)
    missing = [str(path) for path in (table["/snail-web.wasm"], table["/SnailMail.dat"]) if not path.is_file()]
    if missing:
        raise FileNotFoundError(f"missing {', '.join(missing)} (build with `zig build` in port/)")
    server = ThreadingHTTPServer(("127.0.0.1", port), partial(Handler, table=table))
    print(f"Snail Mail port at http://127.0.0.1:{server.server_port}/ (Ctrl-C to stop)", flush=True)
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        pass
    finally:
        server.server_close()
