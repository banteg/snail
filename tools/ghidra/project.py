from __future__ import annotations

import fcntl
import hashlib
import json
import os
import re
import tempfile
from collections.abc import Iterator
from contextlib import contextmanager
from dataclasses import dataclass
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[2]
USER_GHIDRA_DIR = Path.home() / ".local/opt/ghidra_12.1.3_PUBLIC"
DEFAULT_GHIDRA_DIR = Path(
    os.environ.get("GHIDRA_INSTALL_DIR")
    or (
        str(USER_GHIDRA_DIR)
        if USER_GHIDRA_DIR.is_dir()
        else "/Applications/ghidra_12.1.3_PUBLIC"
    )
).expanduser()
DEFAULT_PROJECT_ROOT = REPO_ROOT / "artifacts/ghidra"
PROJECT_NAME = "SnailMailAnalysis"
METADATA_SCHEMA = 1
HASH_CHUNK_SIZE = 1024 * 1024
SAFE_KEY = re.compile(r"[^A-Za-z0-9._-]+")


@dataclass(frozen=True)
class GhidraBuild:
    version: str
    revision: str


@dataclass(frozen=True)
class Project:
    root: Path
    location: Path
    home: Path
    metadata_path: Path
    lock_path: Path
    name: str
    program_name: str
    key: str
    persistent: bool
    exists: bool
    expected_metadata: dict[str, object]

    @property
    def project_file(self) -> Path:
        return self.location / f"{self.name}.gpr"

    def command_prefix(self, headless: Path, binary: Path) -> list[str]:
        command = [str(headless), str(self.location), self.name]
        if self.exists:
            command.extend(("-process", self.program_name))
        else:
            command.extend(("-import", str(binary)))
        return command

    def command_suffix(self) -> list[str]:
        return [] if self.persistent else ["-deleteProject"]

    def provenance(self) -> dict[str, object]:
        binary = self.expected_metadata["binary"]
        ghidra = self.expected_metadata["ghidra"]
        assert isinstance(binary, dict)
        assert isinstance(ghidra, dict)
        return {
            "mode": "persistent" if self.persistent else "fresh",
            "project_key": self.key if self.persistent else None,
            "source_sha256": binary["sha256"],
            "ghidra_version": ghidra["version"],
            "ghidra_revision": ghidra["revision"],
        }


class ProjectMetadataError(RuntimeError):
    pass


class ProjectLockError(RuntimeError):
    pass


def sha256_file(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        while chunk := stream.read(HASH_CHUNK_SIZE):
            digest.update(chunk)
    return digest.hexdigest()


def binary_identity(binary: Path) -> str:
    try:
        return binary.relative_to(REPO_ROOT).as_posix()
    except ValueError:
        return str(binary)


def project_key(binary: Path) -> str:
    identity = binary_identity(binary)
    basename = SAFE_KEY.sub("-", binary.name).strip("-") or "binary"
    suffix = hashlib.sha256(identity.encode()).hexdigest()[:12]
    return f"{basename}-{suffix}"


def read_ghidra_build(ghidra_dir: Path) -> GhidraBuild:
    properties_path = ghidra_dir / "Ghidra/application.properties"
    try:
        lines = properties_path.read_text(encoding="utf-8").splitlines()
    except FileNotFoundError as error:
        raise ProjectMetadataError(
            f"missing Ghidra build metadata: {properties_path}"
        ) from error
    properties = {}
    for line in lines:
        if not line or line.startswith("#") or "=" not in line:
            continue
        key, value = line.split("=", 1)
        properties[key] = value
    version = properties.get("application.version")
    revision = properties.get("application.revision.ghidra")
    if not version or not revision:
        raise ProjectMetadataError(
            f"incomplete Ghidra build metadata: {properties_path}"
        )
    return GhidraBuild(version=version, revision=revision)


def expected_metadata(binary: Path, ghidra_dir: Path) -> dict[str, object]:
    build = read_ghidra_build(ghidra_dir)
    return {
        "schema": METADATA_SCHEMA,
        "binary": {
            "identity": binary_identity(binary),
            "sha256": sha256_file(binary),
            "size": binary.stat().st_size,
        },
        "ghidra": {
            "version": build.version,
            "revision": build.revision,
        },
        "project": {
            "name": PROJECT_NAME,
            "program_name": binary.name,
        },
    }


def persistent_project(
    binary: Path,
    ghidra_dir: Path,
    project_root: Path = DEFAULT_PROJECT_ROOT,
) -> Project:
    key = project_key(binary)
    root = project_root.resolve() / key
    location = root / "project"
    metadata_path = root / "metadata.json"
    project_file = location / f"{PROJECT_NAME}.gpr"
    metadata_exists = metadata_path.is_file()
    project_exists = project_file.is_file()
    if metadata_exists != project_exists:
        raise ProjectMetadataError(
            f"incomplete persistent Ghidra project at {root}; metadata and "
            "project database must either both exist or both be absent"
        )
    expected = expected_metadata(binary, ghidra_dir)
    if project_exists:
        try:
            observed = json.loads(metadata_path.read_text(encoding="utf-8"))
        except (OSError, json.JSONDecodeError) as error:
            raise ProjectMetadataError(
                f"invalid persistent Ghidra project metadata: {metadata_path}"
            ) from error
        if observed != expected:
            raise ProjectMetadataError(
                f"persistent Ghidra project provenance mismatch at {root}; "
                "use --fresh for a clean-room run or move the stale project "
                "aside before rebuilding it"
            )
    return Project(
        root=root,
        location=location,
        home=root / "home",
        metadata_path=metadata_path,
        lock_path=project_root.resolve() / f".{key}.lock",
        name=PROJECT_NAME,
        program_name=binary.name,
        key=key,
        persistent=True,
        exists=project_exists,
        expected_metadata=expected,
    )


def fresh_project(binary: Path, ghidra_dir: Path, root: Path) -> Project:
    expected = expected_metadata(binary, ghidra_dir)
    return Project(
        root=root,
        location=root / "project",
        home=root / "home",
        metadata_path=root / "metadata.json",
        lock_path=root / ".lock",
        name=PROJECT_NAME,
        program_name=binary.name,
        key="fresh",
        persistent=False,
        exists=False,
        expected_metadata=expected,
    )


def prepare_project(project: Project) -> None:
    project.location.mkdir(parents=True, exist_ok=True)
    project.home.mkdir(parents=True, exist_ok=True)


def record_initialized_project(project: Project) -> None:
    if not project.persistent or project.exists:
        return
    temporary = project.metadata_path.with_suffix(".json.tmp")
    temporary.write_text(
        json.dumps(project.expected_metadata, indent=2, sort_keys=True) + "\n",
        encoding="utf-8",
    )
    temporary.replace(project.metadata_path)


@contextmanager
def locked_persistent_project(
    binary: Path,
    ghidra_dir: Path,
    project_root: Path = DEFAULT_PROJECT_ROOT,
) -> Iterator[Project]:
    key = project_key(binary)
    resolved_root = project_root.resolve()
    lock_path = resolved_root / f".{key}.lock"
    project_root_path = resolved_root / key
    lock_path.parent.mkdir(parents=True, exist_ok=True)
    with lock_path.open("a+", encoding="utf-8") as stream:
        try:
            fcntl.flock(stream.fileno(), fcntl.LOCK_EX | fcntl.LOCK_NB)
        except BlockingIOError as error:
            raise ProjectLockError(
                f"persistent Ghidra project is already in use: {project_root_path}"
            ) from error
        try:
            yield persistent_project(binary, ghidra_dir, resolved_root)
        finally:
            fcntl.flock(stream.fileno(), fcntl.LOCK_UN)


@contextmanager
def temporary_fresh_project(
    binary: Path,
    ghidra_dir: Path,
    *,
    prefix: str,
    parent: Path | None = None,
) -> Iterator[Project]:
    with tempfile.TemporaryDirectory(prefix=prefix, dir=parent) as temporary:
        project = fresh_project(binary, ghidra_dir, Path(temporary))
        prepare_project(project)
        yield project
