from __future__ import annotations

from dataclasses import dataclass
import json
from pathlib import Path
import re
from typing import Any


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_FUNCTION_SYMBOL_MANIFEST_PATH = (
    REPO_ROOT / "docs/reverse/symbols/gameplay-functions.json"
)
AUTO_FUNCTION_NAME_RE = re.compile(
    r"^(?:sub|j_sub|nullsub|j_nullsub|thunk|j_thunk)_[0-9a-fA-F]+$"
)
FUNCTION_NAME_RE = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
HEX_VALUE_RE = re.compile(r"^0x[0-9a-fA-F]+$")
SHA256_RE = re.compile(r"^[0-9a-f]{64}$")


@dataclass(frozen=True, slots=True)
class FunctionSymbol:
    address: int
    name: str
    description: str | None = None

    @property
    def address_hex(self) -> str:
        return f"0x{self.address:x}"


@dataclass(frozen=True, slots=True)
class FunctionSymbolManifest:
    name: str
    primary_target: str
    reference_target: str
    image_base: int
    unwrapped_sha256: str
    source_database: str | None
    functions: tuple[FunctionSymbol, ...]


def is_auto_function_name(name: str) -> bool:
    return bool(AUTO_FUNCTION_NAME_RE.fullmatch(name))


def is_curated_function_name(name: str) -> bool:
    return bool(FUNCTION_NAME_RE.fullmatch(name)) and not is_auto_function_name(name)


def _require_string(raw: dict[str, Any], key: str) -> str:
    value = raw.get(key)
    if not isinstance(value, str) or not value:
        raise ValueError(f"manifest field {key!r} must be a non-empty string")
    return value


def _parse_hex_int(value: object, *, field_name: str) -> int:
    if isinstance(value, int):
        return value
    if isinstance(value, str) and HEX_VALUE_RE.fullmatch(value):
        return int(value, 16)
    raise ValueError(f"{field_name} must be an integer or hex string")


def _load_function_symbols(raw_symbols: object) -> tuple[FunctionSymbol, ...]:
    if not isinstance(raw_symbols, list) or not raw_symbols:
        raise ValueError("manifest field 'functions' must be a non-empty list")

    symbols: list[FunctionSymbol] = []
    seen_addresses: set[int] = set()
    seen_names: set[str] = set()
    previous_address = -1

    for index, raw_symbol in enumerate(raw_symbols):
        if not isinstance(raw_symbol, dict):
            raise ValueError(f"function entry {index} must be an object")

        address = _parse_hex_int(
            raw_symbol.get("address"),
            field_name=f"functions[{index}].address",
        )
        name = raw_symbol.get("name")
        if not isinstance(name, str) or not is_curated_function_name(name):
            raise ValueError(
                f"functions[{index}].name must be a curated identifier-like symbol name"
            )
        description = raw_symbol.get("description")
        if description is not None:
            if not isinstance(description, str) or not description.strip():
                raise ValueError(
                    f"functions[{index}].description must be a non-empty string when present"
                )
            description = description.strip()
        if address in seen_addresses:
            raise ValueError(f"duplicate function address: 0x{address:x}")
        if name in seen_names:
            raise ValueError(f"duplicate function name: {name}")
        if address <= previous_address:
            raise ValueError("function addresses must be strictly increasing")

        symbols.append(
            FunctionSymbol(address=address, name=name, description=description)
        )
        seen_addresses.add(address)
        seen_names.add(name)
        previous_address = address

    return tuple(symbols)


def validate_function_symbol_manifest(
    manifest: FunctionSymbolManifest,
) -> FunctionSymbolManifest:
    if manifest.image_base <= 0:
        raise ValueError("image_base must be positive")
    if not SHA256_RE.fullmatch(manifest.unwrapped_sha256):
        raise ValueError("unwrapped_sha256 must be a lowercase SHA-256 hex digest")
    if not manifest.functions:
        raise ValueError("manifest must contain at least one function symbol")
    if manifest.functions[0].address < manifest.image_base:
        raise ValueError("function addresses must be within the image address space")
    return manifest


def load_function_symbol_manifest(path: Path) -> FunctionSymbolManifest:
    raw = json.loads(path.read_text(encoding="utf-8"))
    if not isinstance(raw, dict):
        raise ValueError("symbol manifest must be a JSON object")

    source_database = raw.get("source_database")
    if source_database is not None and not isinstance(source_database, str):
        raise ValueError("manifest field 'source_database' must be a string when present")

    manifest = FunctionSymbolManifest(
        name=_require_string(raw, "name"),
        primary_target=_require_string(raw, "primary_target"),
        reference_target=_require_string(raw, "reference_target"),
        image_base=_parse_hex_int(raw.get("image_base"), field_name="image_base"),
        unwrapped_sha256=_require_string(raw, "unwrapped_sha256"),
        source_database=source_database,
        functions=_load_function_symbols(raw.get("functions")),
    )
    return validate_function_symbol_manifest(manifest)


def build_function_symbol_manifest(
    template: FunctionSymbolManifest,
    functions: list[FunctionSymbol] | tuple[FunctionSymbol, ...],
) -> FunctionSymbolManifest:
    ordered = tuple(sorted(functions, key=lambda symbol: symbol.address))
    return validate_function_symbol_manifest(
        FunctionSymbolManifest(
            name=template.name,
            primary_target=template.primary_target,
            reference_target=template.reference_target,
            image_base=template.image_base,
            unwrapped_sha256=template.unwrapped_sha256,
            source_database=template.source_database,
            functions=ordered,
        )
    )


def normalize_function_symbol_manifest(
    manifest: FunctionSymbolManifest,
) -> dict[str, object]:
    normalized: dict[str, object] = {
        "name": manifest.name,
        "primary_target": manifest.primary_target,
        "reference_target": manifest.reference_target,
        "image_base": f"0x{manifest.image_base:x}",
        "unwrapped_sha256": manifest.unwrapped_sha256,
        "functions": [
            {
                **{"address": function.address_hex, "name": function.name},
                **(
                    {"description": function.description}
                    if function.description is not None
                    else {}
                ),
            }
            for function in manifest.functions
        ],
    }
    if manifest.source_database is not None:
        normalized["source_database"] = manifest.source_database
    return normalized


def write_function_symbol_manifest(
    manifest: FunctionSymbolManifest,
    path: Path,
) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(
        json.dumps(normalize_function_symbol_manifest(manifest), indent=2) + "\n",
        encoding="utf-8",
    )


def summarize_function_symbol_manifest(
    manifest: FunctionSymbolManifest,
    *,
    path: Path | None = None,
) -> dict[str, object]:
    first = manifest.functions[0]
    last = manifest.functions[-1]
    summary: dict[str, object] = {
        "name": manifest.name,
        "function_count": len(manifest.functions),
        "described_function_count": sum(
            1 for function in manifest.functions if function.description is not None
        ),
        "image_base": f"0x{manifest.image_base:x}",
        "address_range": {
            "start": first.address_hex,
            "end": last.address_hex,
        },
        "primary_target": manifest.primary_target,
        "reference_target": manifest.reference_target,
        "unwrapped_sha256": manifest.unwrapped_sha256,
        "preview": [
            {
                **{"address": symbol.address_hex, "name": symbol.name},
                **(
                    {"description": symbol.description}
                    if symbol.description is not None
                    else {}
                ),
            }
            for symbol in manifest.functions[:8]
        ],
    }
    if manifest.source_database is not None:
        summary["source_database"] = manifest.source_database
    if path is not None:
        summary["manifest"] = str(path)
    return summary
