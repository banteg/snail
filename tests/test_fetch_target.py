import hashlib
import importlib.util
import io
import json
from pathlib import Path

import pytest

spec = importlib.util.spec_from_file_location(
    "fetch_target", Path(__file__).resolve().parents[1] / "tools/match/fetch_target.py"
)
assert spec is not None and spec.loader is not None
fetch_target = importlib.util.module_from_spec(spec)
spec.loader.exec_module(fetch_target)


def setup_manifest(tmp_path: Path, payload: bytes) -> Path:
    manifest = tmp_path / "analysis/symbols/gameplay-functions.json"
    manifest.parent.mkdir(parents=True)
    manifest.write_text(json.dumps({
        "primary_target": "artifacts/bin/SnailMail_unwrapped.exe",
        "unwrapped_sha256": hashlib.sha256(payload).hexdigest(),
    }))
    return tmp_path / "artifacts/bin/SnailMail_unwrapped.exe"


def test_verified_download_and_cached_target(tmp_path, monkeypatch):
    payload = b"native image"
    target = setup_manifest(tmp_path, payload)
    monkeypatch.setattr(fetch_target, "TARGET_SIZE", len(payload))
    calls = []

    def download(request, timeout):
        calls.append(request.full_url)
        return io.BytesIO(payload)

    monkeypatch.setattr(fetch_target, "urlopen", download)
    assert fetch_target.fetch_target(tmp_path) == target
    assert target.read_bytes() == payload
    assert fetch_target.fetch_target(tmp_path) == target
    assert len(calls) == 1
    assert hashlib.sha256(payload).hexdigest() in calls[0]
    assert list(target.parent.iterdir()) == [target]


@pytest.mark.parametrize("downloaded", [b"bad", b"wrong image!"])
def test_rejects_corrupt_or_truncated_download(tmp_path, monkeypatch, downloaded):
    payload = b"native image"
    target = setup_manifest(tmp_path, payload)
    monkeypatch.setattr(fetch_target, "TARGET_SIZE", len(payload))
    monkeypatch.setattr(fetch_target, "urlopen", lambda *a, **kw: io.BytesIO(downloaded))
    with pytest.raises(ValueError, match="mismatch"):
        fetch_target.fetch_target(tmp_path)
    assert not target.exists()


def test_preserves_existing_wrong_target(tmp_path, monkeypatch):
    target = setup_manifest(tmp_path, b"native image")
    target.parent.mkdir(parents=True)
    target.write_bytes(b"another build")
    monkeypatch.setattr(fetch_target, "urlopen", lambda *a, **kw: pytest.fail("unexpected download"))
    with pytest.raises(ValueError, match="existing file has the wrong SHA-256"):
        fetch_target.fetch_target(tmp_path)
    assert target.read_bytes() == b"another build"
