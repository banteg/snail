"""Pinned deployment assets and file-by-file release verification."""

import argparse
import gzip
import hashlib
from http.client import HTTPException
import io
import json
from pathlib import Path
import sys
import tarfile
from time import monotonic, sleep
import tomllib
from urllib.request import Request, urlopen

ROOT = Path(__file__).resolve().parents[2]
ASSETS = {"SnailMail.dat", "SnailMailExtras.dat"}
LIVE_RETRY_SECONDS = 90
LIVE_RETRY_INTERVAL = 5


class IdentityMismatch(ValueError):
    """A downloaded or local file differs from its pinned identity."""


def identity(data: bytes) -> dict:
    return {"size": len(data), "sha256": hashlib.sha256(data).hexdigest()}


def checked(data: bytes, expected: dict, name: str) -> bytes:
    if identity(data) != expected:
        raise IdentityMismatch(f"{name}: size or SHA-256 mismatch")
    return data


def download(url: str, size: int) -> bytes:
    if not url.startswith("https://"):
        raise ValueError("deployment downloads require HTTPS")
    with urlopen(Request(url, headers={"User-Agent": "snail-deploy"}), timeout=120) as response:
        return response.read(size + 1)


def package_assets(root: Path, output: Path, url: str) -> dict:
    files = {}
    archive = io.BytesIO()
    with tarfile.open(fileobj=archive, mode="w") as tar:
        for name in sorted(ASSETS):
            data = (root / "artifacts/bin" / name).read_bytes()
            files[name] = identity(data)
            info = tarfile.TarInfo(name)
            info.size = len(data)
            info.mode = 0o644
            tar.addfile(info, io.BytesIO(data))
    payload = gzip.compress(archive.getvalue(), mtime=0)
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_bytes(payload)
    return {"url": url, "bundle": identity(payload), "files": files}


def fetch_assets(root: Path, manifest: dict) -> None:
    files = manifest["files"]
    if set(files) != ASSETS:
        raise ValueError("asset manifest must contain the PC and extras archives")
    target = root / "artifacts/bin"
    for name, expected in files.items():
        path = target / name
        if path.exists():
            checked(path.read_bytes(), expected, name)
    if all((target / name).exists() for name in files):
        return
    raw = checked(download(manifest["url"], manifest["bundle"]["size"]), manifest["bundle"], "asset bundle")
    staged = {}
    with tarfile.open(fileobj=io.BytesIO(raw), mode="r:gz") as tar:
        members = tar.getmembers()
        if len(members) != len(files) or {m.name for m in members} != set(files):
            raise ValueError("unexpected asset bundle members")
        for member in members:
            expected = files[member.name]
            if not member.isfile() or member.size != expected["size"]:
                raise ValueError(f"invalid asset member: {member.name}")
            staged[member.name] = checked(tar.extractfile(member).read(), expected, member.name)
    # Validate the whole bundle before writing either file; never extract paths from tar.
    target.mkdir(parents=True, exist_ok=True)
    for name, data in staged.items():
        (target / name).write_bytes(data)


def write_receipt(root: Path, site: Path, revision: str, ref: str, manifest: dict) -> dict:
    required = {"index.html", "snail-web.wasm", "SnailMail.dat.gz", "SnailMailExtras.dat.gz"}
    if not required <= {p.name for p in site.iterdir() if p.is_file()}:
        raise ValueError("incomplete site: both game archives and the WASM build are required")
    receipt = {
        "revision": revision,
        "ref": ref,
        "version": tomllib.loads((root / "pyproject.toml").read_text())["project"]["version"],
        "assets": manifest["bundle"]["sha256"],
        "files": {
            p.name: identity(p.read_bytes())
            for p in sorted(site.iterdir())
            if p.is_file() and p.name != "build.json" and not p.name.startswith("_")
        },
    }
    (site / "build.json").write_text(json.dumps(receipt, indent=2) + "\n")
    return receipt


def verify_live_file(url: str, expected: dict, name: str, deadline: float) -> None:
    while True:
        try:
            checked(download(url, expected["size"]), expected, name)
            return
        except (IdentityMismatch, OSError, HTTPException) as error:
            remaining = deadline - monotonic()
            if remaining <= 0:
                raise
            delay = min(LIVE_RETRY_INTERVAL, remaining)
            print(f"Retrying live verification in {delay:.1f}s ({error})", file=sys.stderr, flush=True)
            sleep(delay)


def verify_site(site: Path, url: str | None = None) -> None:
    raw = (site / "build.json").read_bytes()
    receipt = json.loads(raw)
    files = receipt["files"]
    for name in files:
        if Path(name).name != name or name in {".", ".."}:
            raise ValueError("invalid site file name")
    if url:
        base = url.rstrip("/")
        query = f"?revision={receipt['revision']}"
        deadline = monotonic() + LIVE_RETRY_SECONDS
        verify_live_file(f"{base}/build.json{query}", identity(raw), "live build.json", deadline)
        for name, expected in files.items():
            verify_live_file(f"{base}/{name}{query}", expected, name, deadline)
        return
    for name, expected in files.items():
        checked((site / name).read_bytes(), expected, name)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("command", choices=("package-assets", "fetch-assets", "receipt", "verify"))
    parser.add_argument("--root", type=Path, default=ROOT)
    parser.add_argument("--site", type=Path, default=ROOT / "artifacts/web")
    parser.add_argument("--manifest", type=Path, help="Defaults to port/deploy-assets.json in the selected root.")
    parser.add_argument("--out", type=Path)
    parser.add_argument("--url")
    parser.add_argument("--revision")
    parser.add_argument("--ref")
    args = parser.parse_args()
    manifest_path = args.manifest or args.root / "port/deploy-assets.json"
    if args.command == "package-assets":
        if not args.out or not args.url:
            parser.error("package-assets requires --out and --url")
        manifest = package_assets(args.root, args.out, args.url)
        manifest_path.write_text(json.dumps(manifest, indent=2) + "\n")
    elif args.command == "fetch-assets":
        fetch_assets(args.root, json.loads(manifest_path.read_text()))
    elif args.command == "receipt":
        if not args.revision or not args.ref:
            parser.error("receipt requires --revision and --ref")
        write_receipt(args.root, args.site, args.revision, args.ref, json.loads(manifest_path.read_text()))
    else:
        verify_site(args.site, args.url)
    print(f"{args.command}: verified")


if __name__ == "__main__":
    main()
