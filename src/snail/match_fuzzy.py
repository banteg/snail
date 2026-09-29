"""Pinned objdiff scoring of source-built, bounded linked-PE snapshots.

The snapshot reference model is explicit; these are not recovered original TUs.
Native encoded-body/reference certification is independent of this fuzzy score.
"""

from concurrent.futures import ThreadPoolExecutor
import hashlib
import json
import math
import os
from pathlib import Path
import platform
import subprocess
import tempfile

from . import match as m
from . import match_objdiff as snapshots

VERSION = "3.8.1"
BINARIES = {
    "objdiff-cli-macos-arm64": "98f8275c27900c4fe2248fce3af37617658be49648fa7dbb5b376371f046dfdb",
    "objdiff-cli-linux-x86_64": "c8290281e82114bcc1a06ff73061110d3902a177822e750337de2537188e358f",
}
CONFIG = {"functionRelocDiffs": "name_address"}
POLICY = {
    "engine": "objdiff",
    "version": VERSION,
    "binaries": BINARIES,
    "config": CONFIG,
    "objects": "bounded-code-snapshots; independent matcher reference keys; trailing data/padding separated",
    "aggregation": "target-owned-code-byte-weighted; compared-coverage-discount; missing-source-zero; no-exact-cap",
}


def binary() -> Path:
    path = Path(
        os.environ.get("SNAIL_OBJDIFF_CLI", m.DEFAULT_MATCH_ROOT / "bin/objdiff-cli")
    )
    if not path.is_file():
        raise ValueError(
            "Pinned objdiff is required for refresh; run uv run tools/match/fetch_objdiff.py"
        )
    digest = hashlib.sha256(path.read_bytes()).hexdigest()
    if digest not in BINARIES.values():
        raise ValueError("objdiff CLI SHA-256 differs from the pinned release")
    return path.resolve()


def release_name() -> str:
    names = {
        ("Darwin", "arm64"): "objdiff-cli-macos-arm64",
        ("Linux", "x86_64"): "objdiff-cli-linux-x86_64",
    }
    try:
        return names[(platform.system(), platform.machine())]
    except KeyError:
        raise ValueError("No pinned objdiff release for this platform") from None


def score_objects(cli: Path, directory: Path) -> float:
    args = [
        str(cli),
        "diff",
        "-1",
        str(directory / "target.obj"),
        "-2",
        str(directory / "candidate.obj"),
        "-o",
        "-",
    ]
    for key, value in CONFIG.items():
        args.extend(["-c", f"{key}={value}"])
    result = subprocess.run(
        args, check=True, capture_output=True, text=True, timeout=60
    )
    payload = json.loads(result.stdout)
    symbols = [
        s for s in payload["left"]["symbols"] if s["name"] == snapshots.DISPLAY_SYMBOL
    ]
    peers = [
        s for s in payload["right"]["symbols"] if s["name"] == snapshots.DISPLAY_SYMBOL
    ]
    if (
        len(symbols) != 1
        or len(peers) != 1
        or symbols[0].get("kind") != "SYMBOL_FUNCTION"
    ):
        raise ValueError("objdiff did not compare the bounded function symbol")
    # Protobuf JSON can omit a zero-valued score. The candidate symbol must exist.
    percent = symbols[0].get("match_percent", 0.0)
    if (
        isinstance(percent, bool)
        or not isinstance(percent, (int, float))
        or not math.isfinite(percent)
        or not 0 <= percent <= 100
    ):
        raise ValueError("invalid objdiff function percentage")
    return percent / 100


def collect_scores(statuses, *, jobs: int):
    cli = binary()
    cli_sha = hashlib.sha256(cli.read_bytes()).hexdigest()

    def evaluate(status):
        with tempfile.TemporaryDirectory(prefix="snail-fuzzy-") as temporary:
            directory = Path(temporary) / "snapshot"
            receipt = snapshots.export_snapshot(status.config.directory, directory)
            native = json.loads((directory / "native-diagnostics.json").read_text())
            if (
                receipt["candidate_object_sha256"] != status.candidate_object_sha256
                or native["match_ratio"] != status.ratio
            ):
                raise ValueError(
                    f"Fuzzy snapshot differs from native evidence: {status.config.function}"
                )
            return status.address, {
                "ratio": score_objects(cli, directory),
                "objects": receipt["objects"],
            }

    with ThreadPoolExecutor(max_workers=jobs) as pool:
        return dict(pool.map(evaluate, statuses)), {
            "version": VERSION,
            "sha256": cli_sha,
            "config": CONFIG,
        }


def validate_score(receipt, external):
    if (
        external.get("version") != VERSION
        or external.get("sha256") not in BINARIES.values()
        or external.get("config") != CONFIG
    ):
        raise ValueError("objdiff scoring identity differs from pinned policy")
    ratio = receipt["ratio"]
    if (
        isinstance(ratio, bool)
        or not isinstance(ratio, (int, float))
        or not math.isfinite(ratio)
        or not 0 <= ratio <= 1
    ):
        raise ValueError("invalid objdiff fuzzy score")
    for side in ("target", "candidate"):
        obj = receipt["objects"][side]
        for field in ("input_sha256", "display_object_sha256"):
            digest = obj[field]
            if (
                not isinstance(digest, str)
                or len(digest) != 64
                or any(c not in "0123456789abcdef" for c in digest)
            ):
                raise ValueError("invalid objdiff snapshot identity")
        if (
            any(
                type(obj[k]) is not int or obj[k] < 0
                for k in (
                    "bytes",
                    "code_view_bytes",
                    "trailing_data_and_padding_bytes",
                    "reference_fields",
                    "unexplained_fields",
                )
            )
            or not 0 < obj["code_view_bytes"] <= obj["bytes"]
            or obj["bytes"]
            != obj["code_view_bytes"] + obj["trailing_data_and_padding_bytes"]
            or obj["round_trip"] is not True
        ):
            raise ValueError("invalid objdiff snapshot code boundary")
