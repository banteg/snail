"""Serve the browser build of the port (port/web/) on localhost.

The page, the `snail-web.wasm` build and the original `SnailMail.dat` come
from three places; this maps them under one origin. The page and the build are
read per request, so a rebuild shows on reload.

The archive is packed once at startup (`SnailMail.dat.gz`, a quarter of the size):
its XOR obfuscation is removed first, because the mask follows the file offset
and hides nearly all redundancy from the compressor. gzip, because every
browser decompresses it natively as it downloads; the page puts the XOR back.

The splash the page shows while it loads is the game's own loading screen
(cRLoadingBar): its two textures come from the archive as AVIF, small enough to
appear long before the archive arrives. 4:4:4 chroma, because subsampling
smears the thin orange lettering. Link previews get the game's splash art
(Turbo and the Intergalactic Postal Service sign) as `card.jpg`, since cards
don't take AVIF.

`pack_site` writes all of this as static files for hosting, with a stripped
release build of the game.
"""

import gzip
import io
import mimetypes
import shutil
import subprocess
import tempfile
from functools import partial
from http import HTTPStatus
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path

from PIL import Image

from .archive import decode_bytes, parse_archive_index, read_archive_entry

WEB = Path("port/web")
WASM = Path("port/zig-out/bin/snail-web.wasm")
ARCHIVE = Path("artifacts/bin/SnailMail.dat")
CONTENT_TYPES = {".js": "text/javascript", ".wasm": "application/wasm", ".gz": "application/gzip", ".avif": "image/avif"}
SPLASH_IMAGES = {"loading.avif": "Sprites/Loading.tga", "loading-bar.avif": "Sprites/LoadingBarOn.tga"}
CARD = "card.jpg"
CARD_HALVES = ("Backgrounds/Splash_A.tga", "Backgrounds/Splash_B.tga")  # Splash.tga, as 512 + 128 columns
CARD_WIDTH, CARD_ASPECT, CARD_TOP = 1200, 1.91, 12  # a large card's shape; the band keeps the sign and Turbo


def pack_archive(archive: Path) -> bytes:
    return gzip.compress(decode_bytes(archive.read_bytes()), compresslevel=9, mtime=0)


def page_images(archive: Path) -> dict[str, bytes]:
    """The loading screen's textures as AVIF and the link-preview card, from the archive."""
    index = parse_archive_index(archive)

    def texture(path: str) -> Image.Image:
        return Image.open(io.BytesIO(read_archive_entry(archive, index.entry_by_path(path)))).convert("RGB")

    images = {}
    for name, path in SPLASH_IMAGES.items():
        out = io.BytesIO()
        texture(path).save(out, "AVIF", quality=60, subsampling="4:4:4")
        images[name] = out.getvalue()

    halves = [texture(path) for path in CARD_HALVES]
    art = Image.new("RGB", (sum(half.width for half in halves), halves[0].height))
    x = 0
    for half in halves:
        art.paste(half, (x, 0))
        x += half.width
    band = art.crop((0, CARD_TOP, art.width, CARD_TOP + round(art.width / CARD_ASPECT)))
    out = io.BytesIO()
    band.resize((CARD_WIDTH, round(CARD_WIDTH / CARD_ASPECT)), Image.LANCZOS).save(out, "JPEG", quality=88)
    images[CARD] = out.getvalue()
    return images


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
    for name, image in page_images(archive).items():
        (out / name).write_bytes(image)


def routes(root: Path, archive: Path) -> dict[str, Path | bytes]:
    """Fixed routes; any other top-level name is looked up in port/web/ per request."""
    return {
        "/": root / WEB / "index.html",
        "/snail-web.wasm": root / WASM,
        "/SnailMail.dat.gz": pack_archive(archive),
        **{f"/{name}": image for name, image in page_images(archive).items()},
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
