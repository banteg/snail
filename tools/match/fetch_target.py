"""Download and verify the canonical native image used by the matching harness."""

import hashlib
import json
from pathlib import Path
import tempfile
from urllib.request import Request, urlopen


TARGET_BASE_URL = "https://reflexive.banteg.xyz/snail"
TARGET_SIZE = 741376


def fetch_target(root: Path) -> Path:
    manifest = json.loads(
        (root / "analysis/symbols/gameplay-functions.json").read_text()
    )
    expected = manifest["unwrapped_sha256"]
    target = root / manifest["primary_target"]
    if target.exists():
        if hashlib.sha256(target.read_bytes()).hexdigest() != expected:
            raise ValueError(
                f"{target}: existing file has the wrong SHA-256; move it aside first"
            )
        return target

    url = f"{TARGET_BASE_URL}/{expected}/{target.name}"
    request = Request(
        url,
        headers={"User-Agent": "snail-matching/0.1 (+https://github.com/banteg/snail)"},
    )
    with urlopen(request, timeout=60) as response:
        payload = response.read(TARGET_SIZE + 1)
    if len(payload) != TARGET_SIZE:
        raise ValueError(f"download size mismatch: expected {TARGET_SIZE}, got {len(payload)}")
    actual = hashlib.sha256(payload).hexdigest()
    if actual != expected:
        raise ValueError(f"download SHA-256 mismatch: expected {expected}, got {actual}")

    target.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.NamedTemporaryFile(dir=target.parent, delete=False) as stream:
        temporary = Path(stream.name)
        try:
            stream.write(payload)
            stream.close()
            temporary.replace(target)
        finally:
            temporary.unlink(missing_ok=True)
    return target


if __name__ == "__main__":
    target = fetch_target(Path(__file__).resolve().parents[2])
    print(f"Verified {target} ({target.stat().st_size:,} bytes)")
