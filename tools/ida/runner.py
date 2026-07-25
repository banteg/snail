#!/usr/bin/env python3

from __future__ import annotations

import os
from pathlib import Path
import shlex
import shutil
import subprocess
import tempfile


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_IDA_DB_PATH = REPO_ROOT / "artifacts/ida/SnailMail_unwrapped.exe.i64"
IDA_94_MACOS_HEADLESS_PATH = Path(
    "/Applications/IDA Professional 9.4.app/Contents/MacOS/idat"
)
STRIP_ENV_VARS = {
    "PYTHONHOME",
    "PYTHONPATH",
    "PYTHONSTARTUP",
    "PYTHONUSERBASE",
    "PYTHONEXECUTABLE",
    "VIRTUAL_ENV",
    "__PYVENV_LAUNCHER__",
}


def find_ida_binary(explicit_path: str | None) -> str:
    if explicit_path:
        return explicit_path

    # The project currently standardizes on IDA 9.4.  The macOS application
    # does not install its headless binary on PATH, so prefer the versioned app
    # bundle before considering generic PATH entries that may point to an older
    # install.
    if IDA_94_MACOS_HEADLESS_PATH.is_file():
        return str(IDA_94_MACOS_HEADLESS_PATH)

    for candidate in ("idat64", "idat", "ida64", "ida"):
        resolved = shutil.which(candidate)
        if resolved is not None:
            return resolved

    raise FileNotFoundError(
        "could not find IDA 9.4 in its macOS app bundle or an IDA binary on "
        "PATH; pass --ida-bin explicitly"
    )


def build_child_env() -> dict[str, str]:
    child_env = {
        key: value
        for key, value in os.environ.items()
        if key not in STRIP_ENV_VARS and not key.startswith("UV_")
    }
    virtual_env = os.environ.get("VIRTUAL_ENV")
    if virtual_env and "PATH" in child_env:
        virtual_env_bin = Path(virtual_env).resolve() / "bin"
        child_env["PATH"] = os.pathsep.join(
            entry
            for entry in child_env["PATH"].split(os.pathsep)
            if Path(entry).resolve() != virtual_env_bin
        )
    return child_env


def run_ida_script(
    *,
    ida_bin: str,
    script_path: Path,
    db_path: Path,
    script_args: list[str],
    log_stem: str,
) -> tuple[int, str]:
    log_path = Path(tempfile.gettempdir()) / f"ida-{log_stem}-{db_path.stem}.log"
    if log_path.exists():
        log_path.unlink()

    quoted_args = " ".join(shlex.quote(argument) for argument in script_args)
    command = [
        ida_bin,
        "-A",
        f"-L{log_path}",
        f"-S{script_path} {quoted_args}".rstrip(),
        str(db_path),
    ]
    completed = subprocess.run(command, check=False, env=build_child_env())
    log_text = ""
    if log_path.is_file():
        log_text = log_path.read_text(encoding="utf-8", errors="replace")
    return completed.returncode, log_text
