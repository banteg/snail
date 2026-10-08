"""Serve the browser build of the port (port/web/) on localhost.

The page, the `snail-web.wasm` build and the original `SnailMail.dat` come
from three places; this maps them under one origin. The page and the build are
read per request, so a rebuild shows on reload.

The archive is packed once at startup (`SnailMail.dat.gz`, a quarter of the size):
its XOR obfuscation is removed first, because the mask follows the file offset
and hides nearly all redundancy from the compressor. gzip, because every
browser decompresses it natively as it downloads; the page puts the XOR back.

`pack_site` writes the same three things as static files for hosting, with a
stripped release build of the game.
"""

import gzip
import mimetypes
import shutil
import subprocess
import tempfile
from functools import partial
from http import HTTPStatus
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path

from .archive import decode_bytes

WEB = Path("port/web")
WASM = Path("port/zig-out/bin/snail-web.wasm")
ARCHIVE = Path("artifacts/bin/SnailMail.dat")
CONTENT_TYPES = {".js": "text/javascript", ".wasm": "application/wasm", ".gz": "application/gzip"}


def pack_archive(archive: Path) -> bytes:
    return gzip.compress(decode_bytes(archive.read_bytes()), compresslevel=9, mtime=0)


def pack_site(root: Path, out: Path, archive: Path) -> None:
    """The page, a release build of snail-web.wasm and the packed archive, in `out`."""
    with tempfile.TemporaryDirectory(prefix="snail-site-") as prefix:
        subprocess.run(
            ["zig", "build", "-Doptimize=ReleaseFast", "-Dstrip", "-p", prefix], cwd=root / "port", check=True
        )
        if out.exists():
            shutil.rmtree(out)
        shutil.copytree(root / WEB, out)
        shutil.copy(Path(prefix) / "bin" / WASM.name, out / WASM.name)
    (out / "SnailMail.dat.gz").write_bytes(pack_archive(archive))


def routes(root: Path, archive: Path) -> dict[str, Path | bytes]:
    """Fixed routes; any other top-level name is looked up in port/web/ per request."""
    return {
        "/": root / WEB / "index.html",
        "/snail-web.wasm": root / WASM,
        "/SnailMail.dat.gz": pack_archive(archive),
        "": root / WEB,
    }


def resolve(table: dict[str, Path | bytes], request_path: str) -> Path | bytes | None:
    path = request_path.split("?", 1)[0]
    if path in table:
        return table[path]
    name = path.removeprefix("/")
    return table[""] / name if name and "/" not in name and not name.startswith(".") else None


class Handler(BaseHTTPRequestHandler):
    def __init__(self, *args, table: dict[str, Path | bytes], **kwargs):
        self.table = table
        super().__init__(*args, **kwargs)

    def do_GET(self):
        target = resolve(self.table, self.path)
        if isinstance(target, bytes):
            body, path = target, Path(self.path.split("?", 1)[0])
        elif target is not None and target.is_file():
            body, path = target.read_bytes(), target
        else:
            self.send_error(HTTPStatus.NOT_FOUND, f"{self.path} not found" + (f" ({target})" if target else ""))
            return
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
    archive = archive or root / ARCHIVE
    missing = [str(path) for path in (root / WASM, archive) if not path.is_file()]
    if missing:
        raise FileNotFoundError(f"missing {', '.join(missing)} (build with `zig build` in port/)")
    table = routes(root, archive)
    server = ThreadingHTTPServer(("127.0.0.1", port), partial(Handler, table=table))
    print(f"Snail Mail port at http://127.0.0.1:{server.server_port}/ (Ctrl-C to stop)", flush=True)
    try:
        server.serve_forever()
    except KeyboardInterrupt:
        pass
    finally:
        server.server_close()
