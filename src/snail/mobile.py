from __future__ import annotations

import difflib
import json
import re
from collections.abc import Iterable
from dataclasses import dataclass
from pathlib import Path
from typing import Any

from .symbols import REPO_ROOT

DEFAULT_VERIFIED_CROSSWALK_PATH = (
    REPO_ROOT / "analysis/symbols/windows-ios-gameplay-crosswalk.json"
)
DEFAULT_MOBILE_CROSSWALK_PATH = (
    REPO_ROOT / "analysis/symbols/windows-mobile-gameplay-crosswalk.json"
)
DEFAULT_ANDROID_CORPUS_ROOT = REPO_ROOT / "analysis/decompile/android"
DEFAULT_IOS_CORPUS_ROOT = REPO_ROOT / "analysis/decompile/ios"

_CAMEL_PART = re.compile(
    r"[A-Z]+(?=[A-Z][a-z]|\d|$)|[A-Z]?[a-z]+|\d+"
)
_WORD = re.compile(r"[A-Za-z0-9]+")
_CANONICAL_TOKEN = {
    "add": "add",
    "ai": "update",
    "allocate": "create",
    "append": "add",
    "build": "build",
    "calc": "calc",
    "calculate": "calc",
    "color": "colour",
    "colour": "colour",
    "compute": "calc",
    "construct": "init",
    "create": "create",
    "deserialize": "load",
    "destroy": "uninit",
    "draw": "render",
    "init": "init",
    "initialize": "init",
    "kill": "remove",
    "new": "create",
    "pos": "position",
    "position": "position",
    "register": "add",
    "release": "uninit",
    "render": "render",
    "reset": "reset",
    "serialize": "save",
    "shutdown": "uninit",
    "uninit": "uninit",
    "uninitialize": "uninit",
    "update": "update",
}
_WINDOWS_BOILERPLATE = frozenset(
    (
        "attachment",
        "from",
        "pair",
        "path",
        "runtime",
        "state",
        "template",
        "track",
    )
)
_MOBILE_METHOD_VERBS = frozenset(
    (
        "add",
        "build",
        "calc",
        "create",
        "init",
        "load",
        "remove",
        "render",
        "reset",
        "save",
        "set",
        "uninit",
        "update",
    )
)


@dataclass(frozen=True)
class MobileCandidate:
    symbol: str
    score: float
    name_score: float
    size_score: float | None


def load_json(path: Path) -> dict[str, Any]:
    return json.loads(path.read_text(encoding="utf-8"))


def signature_base(signature: str) -> str:
    close = signature.rfind(")")
    if close < 0:
        return signature
    depth = 0
    for index in range(close, -1, -1):
        current = signature[index]
        if current == ")":
            depth += 1
        elif current == "(":
            depth -= 1
            if depth == 0:
                return signature[:index]
    return signature


def resolve_corpus_symbols(
    index: dict[str, Any],
    requested: str,
) -> list[dict[str, Any]]:
    functions = [
        function
        for function in index.get("functions", ())
        if function.get("status") == "ok"
    ]
    exact = [
        function
        for function in functions
        if function.get("demangled") == requested
    ]
    if exact:
        return exact
    requested_base = signature_base(requested)
    base_matches = [
        function
        for function in functions
        if signature_base(function.get("demangled", "")) == requested_base
    ]
    return base_matches


def resolve_corpus_symbol(
    index: dict[str, Any],
    requested: str,
) -> dict[str, Any] | None:
    matches = resolve_corpus_symbols(index, requested)
    if len(matches) == 1:
        return matches[0]
    return None


def _identifier_parts(value: str) -> list[str]:
    parts: list[str] = []
    for word in _WORD.findall(value.replace("_", " ")):
        camel = _CAMEL_PART.findall(word)
        parts.extend(part.lower() for part in (camel or [word]))
    return parts


def _canonical(parts: list[str]) -> list[str]:
    return [_CANONICAL_TOKEN.get(part, part) for part in parts]


def _symbol_shape(symbol: str) -> tuple[list[str], list[str]]:
    base = signature_base(symbol)
    if "::" in base:
        owner, method = base.rsplit("::", 1)
    else:
        owner, method = "", base
    owner_parts = _identifier_parts(owner)
    if owner_parts[:2] == ["c", "r"]:
        owner_parts = owner_parts[2:]
    method_parts = _identifier_parts(method)
    return _canonical(owner_parts), _canonical(method_parts)


def _compact(parts: list[str]) -> str:
    return "".join(parts)


def _similarity(left: str, right: str) -> float:
    if not left or not right:
        return 0.0
    return difflib.SequenceMatcher(a=left, b=right, autojunk=False).ratio()


def score_mobile_symbol(
    windows_name: str,
    description: str | None,
    symbol: str,
) -> float:
    if description and symbol in description:
        return 1.0

    windows_parts = _canonical(_identifier_parts(windows_name))
    windows_core = [
        part
        for part in windows_parts
        if part not in _WINDOWS_BOILERPLATE
    ]
    owner_parts, method_parts = _symbol_shape(symbol)
    method_core = [
        part
        for part in method_parts
        if part not in _MOBILE_METHOD_VERBS
    ]

    windows_compact = _compact(windows_core)
    method_owner_compact = _compact(method_parts + owner_parts)
    if windows_compact == method_owner_compact:
        # Windows recovery names conventionally put the action before the
        # owner (`reset_subgame`), while mobile C++ symbols put the owner
        # first (`cRSubGame::ReSet`). Preserve the method verb for this exact
        # identity check before dropping lifecycle boilerplate below.
        return 1.0

    owner_compact = _compact(owner_parts)
    method_compact = _compact(method_core)
    combined_compact = _compact(owner_parts + method_core)
    windows_tokens = set(windows_core)
    mobile_tokens = set(owner_parts + method_core)
    union = windows_tokens | mobile_tokens
    token_overlap = (
        len(windows_tokens & mobile_tokens) / len(union)
        if union
        else 0.0
    )
    score = max(
        _similarity(windows_compact, owner_compact) * 0.94,
        _similarity(windows_compact, method_compact),
        _similarity(windows_compact, combined_compact) * 0.96,
        token_overlap,
    )

    if description:
        description_parts = set(
            _canonical(_identifier_parts(description))
        )
        symbol_parts = set(owner_parts + method_parts)
        if symbol_parts:
            description_overlap = len(
                description_parts & symbol_parts
            ) / len(symbol_parts)
            score = max(score, description_overlap * 0.9)
    return round(min(score, 1.0), 4)


def rank_mobile_symbols(
    windows_name: str,
    description: str | None,
    index: dict[str, Any],
    *,
    windows_aliases: Iterable[str] = (),
    rejected_symbols: Iterable[str] = (),
    limit: int = 5,
    minimum_score: float = 0.35,
    windows_size: int | None = None,
) -> list[MobileCandidate]:
    aliases = tuple(windows_aliases)
    rejected = frozenset(rejected_symbols)
    candidates = []
    for function in index.get("functions", ()):
        if function.get("status") != "ok" or not function.get("demangled"):
            continue
        symbol = function["demangled"]
        if symbol in rejected:
            continue
        name_score = score_mobile_symbol(
            windows_name,
            description,
            symbol,
        )
        symbol_base = signature_base(symbol)
        exact_alias_match = any(
            signature_base(alias) == symbol_base for alias in aliases
        )
        if exact_alias_match:
            name_score = 1.0
        mobile_size = function.get("size")
        size_score = None
        if (
            windows_size
            and isinstance(mobile_size, int)
            and mobile_size > 0
        ):
            size_score = min(windows_size, mobile_size) / max(
                windows_size,
                mobile_size,
            )
        if exact_alias_match:
            # A curated authored alias is stronger evidence than body size:
            # platform ports routinely replace desktop-only implementations
            # with one-instruction stubs.
            score = 1.0
        else:
            score = (
                name_score
                if size_score is None
                else name_score * 0.6 + size_score * 0.4
            )
        candidates.append(
            MobileCandidate(
                symbol=symbol,
                score=round(score, 4),
                name_score=name_score,
                size_score=(
                    round(size_score, 4)
                    if size_score is not None
                    else None
                ),
            )
        )
    candidates.sort(key=lambda candidate: (-candidate.score, candidate.symbol))
    return [
        candidate
        for candidate in candidates
        if candidate.score >= minimum_score
    ][:limit]


def exact_cross_port_backfills(
    crosswalk: dict[str, Any],
    android_index: dict[str, Any],
    ios_index: dict[str, Any],
) -> list[tuple[str, str, str]]:
    android_symbols = {
        function["demangled"]
        for function in android_index.get("functions", ())
        if function.get("status") == "ok"
    }
    ios_symbols = {
        function["demangled"]
        for function in ios_index.get("functions", ())
        if function.get("status") == "ok"
    }
    changes: list[tuple[str, str, str]] = []
    for entry in crosswalk["entries"]:
        if (
            not entry.get("android_symbol")
            and entry.get("ios_symbol") in android_symbols
        ):
            symbol = entry["ios_symbol"]
            entry["android_symbol"] = symbol
            entry["android_symbol_evidence"] = "exact-demangled-symbol"
            changes.append((entry["windows_name"], "android", symbol))
        if (
            not entry.get("ios_symbol")
            and entry.get("android_symbol") in ios_symbols
        ):
            symbol = entry["android_symbol"]
            entry["ios_symbol"] = symbol
            entry["ios_symbol_evidence"] = "exact-demangled-symbol"
            changes.append((entry["windows_name"], "ios", symbol))
    return changes


def build_complete_mobile_crosswalk(
    manifest: dict[str, Any],
    verified_crosswalk: dict[str, Any],
    android_index: dict[str, Any],
    ios_index: dict[str, Any],
    *,
    candidate_limit: int = 5,
) -> dict[str, Any]:
    verified_by_name = {
        entry["windows_name"]: entry
        for entry in verified_crosswalk["entries"]
    }
    entries = []
    manifest_functions = manifest["functions"]
    for function_index, function in enumerate(manifest_functions):
        windows_name = function["name"]
        next_function = (
            manifest_functions[function_index + 1]
            if function_index + 1 < len(manifest_functions)
            else None
        )
        windows_size = (
            int(next_function["address"], 0)
            - int(function["address"], 0)
            if next_function is not None
            else None
        )
        verified = verified_by_name.get(windows_name)
        entry: dict[str, Any] = {
            "address": function["address"],
            "windows_name": windows_name,
            "windows_size": windows_size,
            "status": "verified" if verified else "unverified",
        }
        for key in ("source_object", "source_object_evidence"):
            if key in function:
                entry[key] = function[key]
        if verified:
            for key in (
                "android_symbol",
                "android_symbol_evidence",
                "ios_symbol",
                "ios_symbol_evidence",
                "source_object",
                "source_object_evidence",
                "confidence",
            ):
                if key in verified:
                    entry[key] = verified[key]
        description = function.get("description")
        mobile_candidate_rejections = function.get(
            "mobile_candidate_rejections",
            [],
        )
        rejected_symbols = {
            rejection["symbol"]
            for rejection in mobile_candidate_rejections
        }
        if mobile_candidate_rejections:
            entry["mobile_candidate_rejections"] = (
                mobile_candidate_rejections
            )
        for port, index in (
            ("android", android_index),
            ("ios", ios_index),
        ):
            symbol = entry.get(f"{port}_symbol")
            if symbol:
                if symbol in rejected_symbols:
                    raise ValueError(
                        f"{windows_name} both verifies and rejects {symbol}"
                    )
                entry[f"{port}_body_count"] = len(
                    resolve_corpus_symbols(index, symbol)
                )
                continue
            candidates = rank_mobile_symbols(
                windows_name,
                description,
                index,
                windows_aliases=function.get("aliases", ()),
                rejected_symbols=rejected_symbols,
                limit=candidate_limit,
                windows_size=windows_size,
            )
            entry[f"{port}_candidates"] = [
                {
                    "symbol": candidate.symbol,
                    "score": candidate.score,
                    "name_score": candidate.name_score,
                    "size_score": candidate.size_score,
                }
                for candidate in candidates
            ]
        entries.append(entry)

    verified_count = len(verified_by_name)
    return {
        "name": "Complete Windows/mobile gameplay crosswalk",
        "windows_manifest": "analysis/symbols/gameplay-functions.json",
        "verified_source": (
            "analysis/symbols/windows-ios-gameplay-crosswalk.json"
        ),
        "android_index": "analysis/decompile/android/index.json",
        "ios_index": "analysis/decompile/ios/index.json",
        "notes": [
            "Every Windows manifest function has exactly one entry.",
            "verified entries come from the hand-audited source crosswalk.",
            "body_count records how many matching exports exist in this corpus version.",
            "windows_size is the distance to the next curated manifest start and can include gaps.",
            "unverified candidate scores blend curated names and aliases with size similarity; an exact curated alias outranks platform-stub size drift, but candidates are not mappings.",
            "source_object on an unverified entry is independent Windows compilation-unit provenance and does not turn a candidate into a mobile mapping.",
            "source_object_evidence set to windows-contiguous-source-run means the function is physically bounded by verified Windows functions from the same source object and its recovered owner agrees with that unit.",
            "source_object_evidence set to windows-constructor-support-run means a compiler-emitted helper belongs to a bounded constructor support block with a direct source-object anchor and a closed native caller graph; shared folded and cross-cutting helpers are excluded.",
            "source_object_evidence set to dual-mobile-inline-source-object means Android and iOS inline the complete Windows operation inside the same authored enclosing method, both ports independently assign that method to the named source unit, and the Windows call graph agrees; this is source provenance, not a whole-function mobile mapping.",
            "source_object_evidence set to ios-enclosing-function-source-object means iOS inlines the complete Windows operation inside a function with a direct STABS source-object record and the bounded Windows unit plus call graph agree; this recovers Windows source provenance without claiming a standalone iOS mapping.",
            "source_object_evidence set to windows-source-unit-tail means an exact Windows helper follows a verified same-object lifecycle family, its recovered owner belongs to that family, and the next verified function begins a different source unit.",
            "source_object_evidence set to windows-isolated-class-source-run means a closed Windows method family forms its own linker run between independently identified source units, and the exact native class name fixes that run's object filename.",
            "source_object_evidence set to ios-global-source-object means the Windows function initializes, or is the direct CRT thunk for, a cross-port global whose exact iOS symbol is assigned to that source object.",
            "source_object_evidence set to android-global-constructor-source-file means an exact Android `_GLOBAL__I_<source>.cpp` symbol constructs the corresponding cross-port globals, and the canonical iOS source catalog assigns that source file to the named object unit.",
            "mobile_candidate_rejections preserve audited negative evidence and exclude only the exact demangled symbols listed by the Windows manifest.",
        ],
        "counts": {
            "manifest_functions": len(manifest["functions"]),
            "verified_entries": verified_count,
            "unverified_entries": len(manifest["functions"]) - verified_count,
            "verified_android_symbols": sum(
                bool(entry.get("android_symbol")) for entry in entries
            ),
            "verified_ios_symbols": sum(
                bool(entry.get("ios_symbol")) for entry in entries
            ),
            "available_android_mappings": sum(
                bool(entry.get("android_body_count")) for entry in entries
            ),
            "available_ios_mappings": sum(
                bool(entry.get("ios_body_count")) for entry in entries
            ),
        },
        "entries": entries,
    }


def corpus_function_path(
    corpus_root: Path,
    function: dict[str, Any],
) -> Path:
    return corpus_root / function["path"]


def windows_decompile_path(
    *,
    tool: str,
    address: int,
    windows_name: str,
) -> Path:
    return (
        REPO_ROOT
        / "analysis/decompile"
        / tool
        / "functions"
        / f"{address:08x}-{windows_name}.c"
    )
