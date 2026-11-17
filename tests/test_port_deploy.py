import importlib.util
import io
import json
from pathlib import Path
import sys
import tarfile
from urllib.error import URLError

import pytest

spec = importlib.util.spec_from_file_location("port_deploy", Path(__file__).resolve().parents[1] / "tools/port/deploy.py")
deploy = importlib.util.module_from_spec(spec)
spec.loader.exec_module(deploy)


def asset_bundle(tmp_path):
    assets = tmp_path / "original/artifacts/bin"
    assets.mkdir(parents=True)
    for name in deploy.ASSETS:
        (assets / name).write_bytes(name.encode() * 10)
    bundle = tmp_path / "assets.tar.gz"
    manifest = deploy.package_assets(tmp_path / "original", bundle, "https://example.com/assets.tar.gz")
    return bundle, manifest


def test_pinned_assets_are_reproducible_and_cached(tmp_path, monkeypatch):
    bundle, manifest = asset_bundle(tmp_path)
    second = tmp_path / "second.tar.gz"
    assert deploy.package_assets(tmp_path / "original", second, manifest["url"]) == manifest
    assert second.read_bytes() == bundle.read_bytes()
    monkeypatch.setattr(deploy, "download", lambda *args: bundle.read_bytes())
    target = tmp_path / "target"
    deploy.fetch_assets(target, manifest)
    monkeypatch.setattr(deploy, "download", lambda *args: pytest.fail("unexpected download"))
    deploy.fetch_assets(target, manifest)
    for name in deploy.ASSETS:
        assert (target / "artifacts/bin" / name).read_bytes() == name.encode() * 10


def test_bad_download_does_not_write_assets(tmp_path, monkeypatch):
    _, manifest = asset_bundle(tmp_path)
    monkeypatch.setattr(deploy, "download", lambda *args: b"corrupt")
    with pytest.raises(ValueError, match="mismatch"):
        deploy.fetch_assets(tmp_path / "target", manifest)
    assert not (tmp_path / "target").exists()


def test_existing_wrong_assets_are_preserved(tmp_path, monkeypatch):
    _, manifest = asset_bundle(tmp_path)
    target = tmp_path / "target/artifacts/bin"
    target.mkdir(parents=True)
    (target / "SnailMail.dat").write_bytes(b"another archive")
    monkeypatch.setattr(deploy, "download", lambda *args: pytest.fail("unexpected download"))
    with pytest.raises(ValueError, match="mismatch"):
        deploy.fetch_assets(tmp_path / "target", manifest)
    assert (target / "SnailMail.dat").read_bytes() == b"another archive"


@pytest.mark.parametrize("kind", ["traversal", "symlink", "tampered", "missing"])
def test_bundle_members_are_checked_before_writes(tmp_path, monkeypatch, kind):
    _, manifest = asset_bundle(tmp_path)
    stream = io.BytesIO()
    with tarfile.open(fileobj=stream, mode="w:gz") as tar:
        for name in sorted(deploy.ASSETS):
            if kind == "missing" and name == "SnailMailExtras.dat":
                continue
            info = tarfile.TarInfo("../escape" if kind == "traversal" else name)
            data = name.encode() * 10
            info.size = len(data)
            if kind == "symlink":
                info.type = tarfile.SYMTYPE
                info.linkname = "/tmp/escape"
                info.size = 0
            if kind == "tampered":
                data = b"x" * len(data)
            tar.addfile(info, io.BytesIO(data))
    raw = stream.getvalue()
    manifest["bundle"] = deploy.identity(raw)
    monkeypatch.setattr(deploy, "download", lambda *args: raw)
    with pytest.raises(ValueError):
        deploy.fetch_assets(tmp_path / "target", manifest)
    assert not (tmp_path / "target").exists()


def site_receipt(tmp_path):
    (tmp_path / "pyproject.toml").write_text('[project]\nversion = "0.3.0"\n')
    site = tmp_path / "site"
    site.mkdir()
    for name in ("index.html", "snail-web.wasm", "SnailMail.dat.gz", "SnailMailExtras.dat.gz"):
        (site / name).write_bytes(name.encode())
    deploy.write_receipt(tmp_path, site, "a" * 40, "v0.3.0", {"bundle": {"sha256": "b" * 64}})
    return site


def test_site_receipt_requires_extras_and_detects_replaced_files(tmp_path):
    site = site_receipt(tmp_path)
    deploy.verify_site(site)
    (site / "snail-web.wasm").write_bytes(b"old build")
    with pytest.raises(ValueError, match="mismatch"):
        deploy.verify_site(site)
    (site / "SnailMailExtras.dat.gz").unlink()
    with pytest.raises(ValueError, match="incomplete"):
        deploy.write_receipt(tmp_path, site, "a" * 40, "master", {})


def test_receipt_reads_manifest_from_the_selected_checkout(tmp_path, monkeypatch):
    site = site_receipt(tmp_path)
    pin = tmp_path / "port/deploy-assets.json"
    pin.parent.mkdir()
    pin.write_text(json.dumps({"bundle": {"sha256": "c" * 64}}))
    monkeypatch.setattr(sys, "argv", ["deploy.py", "receipt", "--root", str(tmp_path),
                        "--site", str(site), "--revision", "a" * 40, "--ref", "v0.4.0"])
    deploy.main()
    assert json.loads((site / "build.json").read_bytes())["assets"] == "c" * 64


def test_live_verification_checks_build_identity_and_every_file(tmp_path, monkeypatch):
    site = site_receipt(tmp_path)
    calls = []

    def fetch(url, size):
        calls.append(url)
        return (site / url.split("?")[0].rsplit("/", 1)[1]).read_bytes()

    monkeypatch.setattr(deploy, "download", fetch)
    deploy.verify_site(site, "https://snail.example")
    assert len(calls) == 5
    assert all(f"?revision={'a' * 40}" in url for url in calls)
    monkeypatch.setattr(deploy, "LIVE_RETRY_SECONDS", 0)
    monkeypatch.setattr(deploy, "download", lambda *args: b"old deployment")
    with pytest.raises(ValueError, match="live build.json"):
        deploy.verify_site(site, "https://snail.example")


def test_live_verification_retries_stale_receipt_and_unavailable_file(tmp_path, monkeypatch):
    site = site_receipt(tmp_path)
    calls = []
    delays = []

    def fetch(url, size):
        name = url.split("?")[0].rsplit("/", 1)[1]
        calls.append(name)
        if name == "build.json" and calls.count(name) == 1:
            return b"old deployment"
        if name == "snail-web.wasm" and calls.count(name) == 1:
            raise URLError("asset unavailable")
        return (site / name).read_bytes()

    monkeypatch.setattr(deploy, "download", fetch)
    monkeypatch.setattr(deploy, "sleep", delays.append)
    deploy.verify_site(site, "https://snail.example")
    assert calls[:2] == ["build.json", "build.json"]
    assert calls.count("snail-web.wasm") == 2
    assert len(calls) == 7
    assert delays == [5, 5]


def test_live_verification_shares_retry_deadline_across_files(tmp_path, monkeypatch):
    site = site_receipt(tmp_path)
    delays = []

    def fetch(url, size):
        name = url.split("?")[0].rsplit("/", 1)[1]
        if not delays or name == "snail-web.wasm":
            return b"old deployment"
        return (site / name).read_bytes()

    monkeypatch.setattr(deploy, "download", fetch)
    monkeypatch.setattr(deploy, "LIVE_RETRY_SECONDS", 7)
    monkeypatch.setattr(deploy, "monotonic", lambda: sum(delays))
    monkeypatch.setattr(deploy, "sleep", delays.append)
    with pytest.raises(ValueError, match="snail-web.wasm: size or SHA-256 mismatch"):
        deploy.verify_site(site, "https://snail.example")
    assert delays == [5, 2]


def test_site_receipt_cannot_escape_output_directory(tmp_path):
    site = site_receipt(tmp_path)
    receipt = json.loads((site / "build.json").read_text())
    receipt["files"]["../escape"] = deploy.identity(b"escape")
    (site / "build.json").write_text(json.dumps(receipt))
    with pytest.raises(ValueError, match="invalid site file"):
        deploy.verify_site(site)
