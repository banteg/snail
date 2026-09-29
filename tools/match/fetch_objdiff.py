"""Install the SHA-256-pinned objdiff release used by public fuzzy refresh."""

from hashlib import sha256
from pathlib import Path
import tempfile
from urllib.request import urlopen

from snail import match_fuzzy


def fetch_objdiff():
    destination = Path(__file__).resolve().parent / "bin/objdiff-cli"
    name = match_fuzzy.release_name()
    expected = match_fuzzy.BINARIES[name]
    if destination.exists():
        if sha256(destination.read_bytes()).hexdigest() != expected:
            raise ValueError(
                "Existing objdiff differs from pinned release; move it aside first"
            )
        return destination
    url = f"https://github.com/encounter/objdiff/releases/download/v{match_fuzzy.VERSION}/{name}"
    with urlopen(url, timeout=60) as response:
        data = response.read(50_000_001)
    if sha256(data).hexdigest() != expected:
        raise ValueError("Downloaded objdiff SHA-256 differs from pinned release")
    destination.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.NamedTemporaryFile(dir=destination.parent, delete=False) as stream:
        temporary = Path(stream.name)
        try:
            stream.write(data)
            stream.close()
            temporary.chmod(0o755)
            temporary.replace(destination)
        finally:
            temporary.unlink(missing_ok=True)
    return destination


if __name__ == "__main__":
    print(f"Verified {fetch_objdiff()}")
