"""Windows-first build identities and evidence from reference ports."""

from __future__ import annotations

import hashlib
import json
import zipfile
from pathlib import Path

from .mobile import resolve_corpus_symbols
from .symbols import REPO_ROOT, load_function_symbol_manifest

DEFAULT_BUILDS = REPO_ROOT / "analysis/ports/builds.json"
DEFAULT_RELATIONSHIPS = REPO_ROOT / "analysis/ports/functions.json"


def read_json(path: Path) -> dict:
    return json.loads(path.read_text(encoding="utf-8"))


def repo_path(root: Path, value: str) -> Path:
    path = (root / value).resolve()
    if not path.is_relative_to(root.resolve()):
        raise ValueError(f"path escapes repository: {value}")
    return path


def load_builds(path: Path = DEFAULT_BUILDS) -> dict:
    registry = read_json(path)
    if registry.get("schema") != 1:
        raise ValueError("unsupported build registry schema")
    builds = registry["builds"]
    ids = [build["id"] for build in builds]
    if len(set(ids)) != len(ids):
        raise ValueError("duplicate build identity")
    primary = [build["id"] for build in builds if build["role"] == "primary"]
    if primary != [registry["primary_build"]]:
        raise ValueError("exactly one registered primary build is required")
    if any(build["role"] not in {"primary", "lead", "deferred"} for build in builds):
        raise ValueError("unknown build role")
    return registry


def read_build_binary(build: dict, root: Path = REPO_ROOT) -> bytes:
    source = build["binary"]
    path = repo_path(root, source["path"])
    if "archive_member" in source:
        with zipfile.ZipFile(path) as archive:
            data = archive.read(source["archive_member"])
    else:
        data = path.read_bytes()
    if "offset" in source or "size" in source:
        offset, size = source["offset"], source["size"]
        if offset < 0 or size <= 0 or offset + size > len(data):
            raise ValueError(f"{build['id']}: binary slice is outside the source")
        data = data[offset : offset + size]
    if hashlib.sha256(data).hexdigest() != source["sha256"]:
        raise ValueError(f"{build['id']}: binary SHA-256 mismatch")
    return data


def check_registry(
    registry: dict,
    relationships: dict,
    *,
    root: Path = REPO_ROOT,
    binaries: bool = True,
) -> list[str]:
    """Check evidence identities; no progress credit is inferred here."""
    errors = []
    builds = {build["id"]: build for build in registry["builds"]}
    manifest = load_function_symbol_manifest(
        repo_path(root, relationships["windows_manifest"])
    )
    functions = {function.name for function in manifest.functions}
    primary = builds[registry["primary_build"]]
    if primary.get("function_manifest") != relationships["windows_manifest"]:
        errors.append(
            "primary build and relationships use different function manifests"
        )
    if primary["binary"]["path"] != manifest.primary_target:
        errors.append("primary build differs from the Windows matching image")
    for build in builds.values():
        try:
            if binaries:
                read_build_binary(build, root)
            for field in ("symbol_index", "corpus"):
                if field not in build:
                    continue
                index_path = (
                    build[field] if field == "symbol_index" else build[field]["index"]
                )
                index = read_json(repo_path(root, index_path))
                expected = index.get("binary_sha256", index.get("executable_sha256"))
                if expected != build["binary"]["sha256"]:
                    raise ValueError(
                        f"{build['id']}: {field} belongs to a different binary"
                    )
                if field == "symbol_index" and index.get("build_id") != build["id"]:
                    raise ValueError(
                        f"{build['id']}: symbol index has wrong build identity"
                    )
        except (OSError, ValueError, KeyError, zipfile.BadZipFile) as error:
            errors.append(str(error))
    seen = set()
    for entry in relationships["functions"]:
        name = entry["windows_id"]
        if name not in functions or name in seen:
            errors.append(f"unknown or duplicate Windows function: {name}")
        seen.add(name)
        for relation in entry.get("relationships", ()):
            if relation["build_id"] not in builds:
                errors.append(f"{name}: unknown reference build")
            if relation["kind"] not in {
                "same-algorithm",
                "split",
                "inlined",
                "candidate",
            }:
                errors.append(f"{name}: unsupported relationship kind")
            if not relation.get("evidence"):
                errors.append(f"{name}: relationship has no evidence")
        for item in [*entry.get("relationships", ()), *entry.get("constraints", ())]:
            for evidence in item.get("evidence", ()):
                if not repo_path(root, evidence).is_file():
                    errors.append(f"{name}: missing evidence {evidence}")
    return errors


def function_leads(
    name: str,
    registry: dict,
    relationships: dict,
    *,
    root: Path = REPO_ROOT,
) -> dict:
    manifest = load_function_symbol_manifest(
        repo_path(root, relationships["windows_manifest"])
    )
    function = next(
        (f for f in manifest.functions if name == f.name or name in f.aliases), None
    )
    if function is None:
        raise ValueError(f"unknown curated function or alias: {name}")
    crosswalk = read_json(repo_path(root, relationships["mobile_crosswalk"]))
    mapping = next(
        (e for e in crosswalk["entries"] if e["windows_name"] == function.name), {}
    )
    authored = next(
        (e for e in relationships["functions"] if e["windows_id"] == function.name), {}
    )
    # Transfer only actual verified spellings. Fuzzy candidate scores do not
    # establish a relation to another version of the game.
    names = set()
    if mapping.get("status") == "verified":
        names = {mapping[k] for k in ("android_symbol", "ios_symbol") if mapping.get(k)}
    leads = []
    for build in registry["builds"]:
        if build["role"] != "lead":
            continue
        if "symbol_index" not in build:
            continue
        index = read_json(repo_path(root, build["symbol_index"]))
        if index["binary_sha256"] != build["binary"]["sha256"]:
            raise ValueError(f"{build['id']}: stale symbol index")
        corpus = None
        if "corpus" in build:
            corpus = read_json(repo_path(root, build["corpus"]["index"]))
            if corpus["executable_sha256"] != build["binary"]["sha256"]:
                raise ValueError(f"{build['id']}: stale corpus")
        for symbol in index["functions"]:
            if symbol["demangled"] not in names:
                continue
            lead = {
                "build_id": build["id"],
                "binary_sha256": build["binary"]["sha256"],
                **symbol,
                "address_space": "link-time-va",
                "association": "same-symbol-only",
                "body_parity": "not-reviewed-for-this-build",
                "analysis_cautions": build.get("analysis_cautions", []),
            }
            if corpus is not None:
                port = build["corpus"]["crosswalk_port"]
                if mapping.get(f"{port}_symbol") == symbol["demangled"]:
                    lead["association"] = "curated-windows-correspondence"
                    lead["body_parity"] = "see-existing-crosswalk-evidence"
                exports = [
                    f
                    for f in resolve_corpus_symbols(corpus, symbol["demangled"])
                    if f.get("mangled") == symbol["mangled"]
                ]
                for exported in exports:
                    address = int(exported["address"], 16)
                    bias = int(build["corpus"]["address_bias"], 16)
                    if address - bias != int(symbol["address"], 16):
                        raise ValueError(
                            f"{build['id']}: corpus address does not resolve to symbol"
                        )
                    lead["analysis_address"] = hex(address)
                    lead["decompile"] = str(
                        Path(build["corpus"]["index"]).parent / exported["path"]
                    )
            leads.append(lead)
    return {
        "function": function.name,
        "primary_build": registry["primary_build"],
        "windows_address": function.address_hex,
        "source_object": mapping.get("source_object"),
        "scratch": f"tools/match/scratches/{function.name}/scratch.cpp",
        "mobile_crosswalk": relationships["mobile_crosswalk"],
        "leads": leads,
        "relationships": authored.get("relationships", []),
        "constraints": authored.get("constraints", []),
        "acceptance": "Windows native instructions, positional references, and complete byte accounting.",
    }
