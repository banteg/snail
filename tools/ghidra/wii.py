#!/usr/bin/env python3
"""Import or reopen the persistent Snail Mail Wii DOL and decompile a function."""

import argparse
import json
import os
import subprocess
from pathlib import Path

from decompile_symbol import failure_log_tail
from project import (
    DEFAULT_GHIDRA_DIR,
    DEFAULT_PROJECT_ROOT,
    REPO_ROOT,
    locked_persistent_project,
    prepare_project,
    record_initialized_project,
    sha256_file,
)

SCRIPT_DIR = Path(__file__).resolve().parent
DOL = REPO_ROOT / "artifacts/wii/reference/SnailMail-USA.dol"
DOL_SHA256 = "523f848f2a0b8ef8c9dfe2714744bf0479a4feec79b25f0d1f5e035a6487c096"
LANGUAGE = "PowerPC:BE:32:Gekko_Broadway"


def extension_identity(ghidra_dir: Path) -> dict:
    extension = ghidra_dir / "Ghidra/Extensions/GameCubeLoader"
    inputs = [extension / "extension.properties", extension / "lib/GameCubeLoader.jar"]
    inputs += sorted((extension / "data/languages").glob("*"))
    # Ghidra compiles .sla files lazily; bind the distributed language sources.
    inputs = [path for path in inputs if path.is_file() and path.suffix != ".sla"]
    if not (extension / "lib/GameCubeLoader.jar").is_file():
        raise ValueError(
            f"Install GameCubeLoader first; see {SCRIPT_DIR / 'README.md'}"
        )
    return {str(path.relative_to(extension)): sha256_file(path) for path in inputs}


def run(
    binary: Path, ghidra: Path, project_root: Path, selector: str, analyze: bool
) -> Path:
    if sha256_file(binary) != DOL_SHA256:
        raise ValueError("DOL differs from the committed Wii reference hash")
    identity = extension_identity(ghidra)
    with locked_persistent_project(binary, ghidra, project_root) as project:
        prepare_project(project)
        loader_metadata = project.root / "wii-loader.json"
        if project.exists and (
            not loader_metadata.is_file()
            or json.loads(loader_metadata.read_text()) != identity
        ):
            raise ValueError("Wii extension identity changed; use a new --project-root")
        loader_metadata.write_text(
            json.dumps(identity, indent=2, sort_keys=True) + "\n"
        )
        verification = project.root / "wii-verification.json"
        output = project.root / "decompile.txt"
        for path in (verification, output):
            path.unlink(missing_ok=True)
        command = project.command_prefix(ghidra / "support/analyzeHeadless", binary)
        if project.exists:
            if not analyze:
                command += ["-noanalysis"]
        else:
            command += ["-loader", "GameCubeLoader", "-loader-autoloadMaps", "false"]
        command += ["-analysisTimeoutPerFile", "600", "-scriptPath", str(SCRIPT_DIR)]
        if not project.exists or analyze:
            command += ["-preScript", "ConfigureWii.java"]
        command += [
            "-postScript",
            "ExportWiiProject.java",
            str(binary),
            str(verification),
            "-postScript",
            "DecompileSymbol.java",
            selector,
            str(output),
        ]
        env = os.environ.copy()
        # Ghidra's per-project settings stay isolated from the normal GUI profile.
        temporary = project.root / "tmp"
        temporary.mkdir(exist_ok=True)
        env["JAVA_TOOL_OPTIONS"] = (
            env.get("JAVA_TOOL_OPTIONS", "")
            + f" -Duser.home={project.home} -Djava.io.tmpdir={temporary}"
            f" -Dapplication.cachedir={temporary}"
        ).strip()
        log = project.root / "headless.log"
        print(
            f"{'Reopening' if project.exists else 'Importing'} persistent Wii project: {project.project_file}",
            flush=True,
        )
        with log.open("w") as stream:
            completed = subprocess.run(
                command, env=env, stdout=stream, stderr=subprocess.STDOUT, check=False
            )
        if project.project_file.is_file() and (
            project.exists or "Import succeeded" in log.read_text()
        ):
            record_initialized_project(project)
        if completed.returncode or not verification.is_file() or not output.is_file():
            raise RuntimeError(
                f"Wii analysis/export failed; log: {log}\n"
                + failure_log_tail(log.read_text())
            )
        report = json.loads(verification.read_text())
        if report["input_sha256"] != DOL_SHA256 or report["language"] != LANGUAGE:
            raise RuntimeError("Unexpected Wii verification identity")
        print(output.read_text(), end="")
        return project.root


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "selector", nargs="?", default="initialize_quaternion_from_matrix"
    )
    parser.add_argument("--binary", type=Path, default=DOL)
    fallback = Path("/Applications/ghidra_12.1.2_PUBLIC")
    default = DEFAULT_GHIDRA_DIR if DEFAULT_GHIDRA_DIR.is_dir() else fallback
    parser.add_argument("--ghidra-dir", type=Path, default=default)
    parser.add_argument("--project-root", type=Path, default=DEFAULT_PROJECT_ROOT)
    parser.add_argument(
        "--analyze",
        action="store_true",
        help="Explicitly rerun analysis on the existing database",
    )
    args = parser.parse_args()
    run(
        args.binary.resolve(),
        args.ghidra_dir.resolve(),
        args.project_root.resolve(),
        args.selector,
        args.analyze,
    )


if __name__ == "__main__":
    main()
