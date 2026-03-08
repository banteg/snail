from __future__ import annotations

from pathlib import Path
import struct

import pefile


REFLEXIVE_WRAPPER_ASSETS = (
    Path("ReflexiveArcade/RAW_003.wdt"),
    Path("ReflexiveArcade/button_pressed.jpg"),
    Path("ReflexiveArcade/button_hover.jpg"),
    Path("ReflexiveArcade/button_normal.jpg"),
    Path("ReflexiveArcade/Background.jpg"),
)
REFLEXIVE_SHORT_ENCRYPTION_KEY = "Game Needs Short Fixed Encryption="


def _resolve_wrapper_asset_paths(
    wrapped_path: Path,
    asset_paths: tuple[Path, ...] | None = None,
) -> tuple[Path, ...]:
    base_dir = wrapped_path.resolve().parent
    paths = asset_paths or REFLEXIVE_WRAPPER_ASSETS
    return tuple(
        path if path.is_absolute() else (base_dir / path).resolve()
        for path in paths
    )


def _reflexive_rng_state(seed: int) -> dict[str, int | list[int]]:
    state = [0] * 250
    current = seed & 0xFFFFFFFF
    for index in range(249, -1, -1):
        current = (current * 0x41C64E6D + 0x3039) & 0xFFFFFFFF
        state[index] = current >> 16

    mask = 0xFFFFFFFF
    bit = 0x80000000
    state_index = 3
    while bit != 0:
        state[state_index] = (state[state_index] & mask) | bit
        bit >>= 1
        mask >>= 1
        state_index += 7

    return {"index_a": 0, "index_b": 0x67, "state": state}


def _reflexive_rng_next_byte(rng: dict[str, int | list[int]]) -> int:
    state = rng["state"]
    assert isinstance(state, list)

    index_a = int(rng["index_a"])
    index_b = int(rng["index_b"])

    rng["index_a"] = (index_a + 1) % 250
    rng["index_b"] = (index_b + 1) % 250

    state[index_a] ^= state[index_b]
    return state[index_a] & 0xFF


def decrypt_reflexive_buffer(data: bytes, seed: int) -> bytes:
    rng = _reflexive_rng_state(seed)
    decrypted = bytearray(data)
    for index in range(len(decrypted)):
        decrypted[index] = (decrypted[index] - _reflexive_rng_next_byte(rng)) & 0xFF
    return bytes(decrypted)


def _reflexive_config_seed(wrapped_path: Path, asset_paths: tuple[Path, ...]) -> int:
    return (
        wrapped_path.stat().st_size
        + sum(path.stat().st_size for path in asset_paths)
    ) & 0xFFFFFFFF


def _reflexive_image_seed(raw_config: bytes) -> int:
    seed = 0
    for index in range(len(raw_config) & 3):
        seed = (
            seed + struct.unpack_from("<I", raw_config, index * 4)[0]
        ) & 0xFFFFFFFF
    return seed


def decrypt_reflexive_wrapper_config(
    wrapped_path: Path,
    raw_config_path: Path,
    asset_paths: tuple[Path, ...] | None = None,
) -> str:
    wrapped_path = wrapped_path.resolve()
    raw_config_path = raw_config_path.resolve()
    resolved_assets = _resolve_wrapper_asset_paths(wrapped_path, asset_paths)
    decrypted = decrypt_reflexive_buffer(
        raw_config_path.read_bytes(),
        _reflexive_config_seed(wrapped_path, resolved_assets),
    )
    return decrypted.decode("ascii", errors="strict")


def _reflexive_short_encryption_enabled(config_text: str) -> bool:
    for line in config_text.splitlines():
        if line.startswith(REFLEXIVE_SHORT_ENCRYPTION_KEY):
            value = line.split("=", 1)[1].strip().lower()
            return value not in {"", "0", "false", "no"}
    return False


def _reflexive_encrypted_region(
    wrapped_path: Path,
    config_text: str,
) -> tuple[int, int]:
    pe = pefile.PE(str(wrapped_path), fast_load=True)
    entry_rva = pe.OPTIONAL_HEADER.AddressOfEntryPoint
    short_encryption = _reflexive_short_encryption_enabled(config_text)

    for section in pe.sections:
        section_start = section.VirtualAddress
        section_size = min(section.Misc_VirtualSize, section.SizeOfRawData)
        if section_size == 0:
            section_size = max(section.Misc_VirtualSize, section.SizeOfRawData)
        if section_start <= entry_rva < section_start + section_size:
            raw_start = section.PointerToRawData + (entry_rva - section_start)
            length = section_size - (entry_rva - section_start)
            if short_encryption:
                if length < 0x80:
                    raise ValueError("short encryption region is smaller than 0x80 bytes")
                length = 0x80
            return raw_start, length

    raise ValueError("could not locate the encrypted entrypoint section")


def unwrap_reflexive_executable(
    wrapped_path: Path,
    raw_config_path: Path,
    asset_paths: tuple[Path, ...] | None = None,
) -> bytes:
    wrapped_path = wrapped_path.resolve()
    raw_config_path = raw_config_path.resolve()
    config_text = decrypt_reflexive_wrapper_config(
        wrapped_path,
        raw_config_path,
        asset_paths=asset_paths,
    )
    raw_start, length = _reflexive_encrypted_region(wrapped_path, config_text)
    image = bytearray(wrapped_path.read_bytes())
    image[raw_start : raw_start + length] = decrypt_reflexive_buffer(
        image[raw_start : raw_start + length],
        _reflexive_image_seed(raw_config_path.read_bytes()),
    )
    return bytes(image)
