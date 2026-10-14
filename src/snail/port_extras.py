"""Build SnailMailExtras.dat from the extracted Android release assets."""

from __future__ import annotations

import io
from pathlib import Path

from PIL import Image

from .archive import write_archive

ANDROID_ROOT = Path("artifacts/android/asm_extracted")
OUTPUT = Path("artifacts/bin/SnailMailExtras.dat")


def tga_rgb24(image: Image.Image) -> bytes:
    """Encode an image as a 24-bit uncompressed bottom-up TGA matching PC Track0-3.tga."""
    rgb = image.convert("RGB")
    out = io.BytesIO()
    rgb.save(out, format="TGA", compression=None)
    raw = bytearray(out.getvalue())
    raw[17] = 8  # match PC Track0-3.tga descriptor byte
    return bytes(raw)


def split_surface_strip(strip_bytes: bytes) -> tuple[bytes, bytes]:
    """Split a 4:1 mobile SurfaceN strip into PC-layout (TrackN.tga, SlideN.tga)."""
    strip = Image.open(io.BytesIO(strip_bytes)).convert("RGB")
    tile = strip.height
    if strip.width < tile * 2:
        raise ValueError(f"surface strip too narrow: {strip.size}")
    track = strip.crop((0, 0, tile, tile))
    slide = strip.crop((tile, 0, tile * 2, tile))
    return tga_rgb24(track), tga_rgb24(slide)


def build_extras_files(android_root: Path) -> dict[str, bytes]:
    """Mobile-only assets converted to PC archive conventions."""
    files: dict[str, bytes] = {}
    for index in (4, 5, 6):
        surface_path = android_root / f"OBJECTS/WORLD00/SURFACE{index}.PNG"
        track_tga, slide_tga = split_surface_strip(surface_path.read_bytes())
        files[f"OBJECTS/WORLD00/TRACK{index}.TGA"] = track_tga
        files[f"OBJECTS/WORLD00/SLIDE{index}.TGA"] = slide_tga
    fringe_path = android_root / "SPRITES/FRINGECOLOURS.TGA"
    files["SPRITES/FRINGECOLOURS.TGA"] = fringe_path.read_bytes()
    files["OBJECTS/TRAMPRING/_OBJECT.TXT"] = (android_root / "OBJECTS/TRAMPRING/_OBJECT.TXT").read_bytes()
    files["OBJECTS/TRAMPRING/TRAMPRING.TGA"] = (android_root / "OBJECTS/TRAMPRING/TRAMPRING.TGA").read_bytes()
    return files


def generate(root: Path, *, out: Path | None = None, android_root: Path | None = None) -> Path:
    target = out or (root / OUTPUT)
    source = android_root or (root / ANDROID_ROOT)
    files = build_extras_files(source)
    write_archive(target, files)
    return target
