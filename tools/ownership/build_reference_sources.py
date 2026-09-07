#!/usr/bin/env python3
"""Build historical PNG/zlib sources for identity probes, not public match credit."""
from __future__ import annotations

import argparse
import hashlib
import json
import subprocess
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
VARIANTS = {"O1": ["/O1", "/MD"], "O2": ["/O2", "/MD"], "O1-MT": ["/O1", "/MT"]}


def digest(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source_root", type=Path, help="Contains extracted libpng-1.2.5 and zlib-1.2.1 tags")
    args = parser.parse_args()
    base = args.source_root.resolve()
    sources = [*sorted((base / "libpng-1.2.5").glob("png*.c")), *sorted((base / "zlib-1.2.1").glob("*.c"))]
    sources = [p for p in sources if p.stem not in {"pngtest", "example", "minigzip"}]
    if len(sources) != 29:
        raise ValueError(f"unexpected source set: {len(sources)}")

    def build(item: tuple[str, Path]) -> dict:
        variant, source = item
        output = base / "objects" / variant / source.parent.name / (source.stem + ".obj")
        output.parent.mkdir(parents=True, exist_ok=True)
        argv = [str(ROOT / "tools/match/cl.sh"), "/c", *VARIANTS[variant],
                "/IZ:" + str(base / "zlib-1.2.1"), "/FoZ:" + str(output), "Z:" + str(source)]
        # Pin the bundle explicitly rather than inheriting an interactive override.
        import os
        env = {**os.environ, "MSVC_VER": "msvc6.5"}
        completed = subprocess.run(argv, env=env, capture_output=True, text=True, check=False)
        if completed.returncode:
            raise RuntimeError(f"{source}: {completed.stdout}\n{completed.stderr}")
        return {"object": str(output.relative_to(base)), "sha256": digest(output),
                "source": str(source.relative_to(base)), "flags": VARIANTS[variant]}

    with ThreadPoolExecutor(max_workers=8) as executor:
        outputs = list(executor.map(build, [(variant, p) for variant in VARIANTS for p in sources]))
    manifest = {
        "compiler": "msvc6.5",
        "compiler_files": {str(p.relative_to(ROOT / "tools/match/compilers/msvc6.5")): digest(p)
                           for p in sorted((ROOT / "tools/match/compilers/msvc6.5").rglob("*")) if p.is_file()},
        "sources": {str(p.relative_to(base)): digest(p) for package in ("libpng-1.2.5", "zlib-1.2.1")
                    for p in sorted((base / package).glob("*")) if p.suffix in {".c", ".h"}},
        "runner_sha256": digest(ROOT / "tools/match/bin/wibo"),
        "outputs": outputs,
    }
    (base / "build-manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
    print(f"Built {len(outputs)} objects; wrote {base / 'build-manifest.json'}")


if __name__ == "__main__":
    main()
