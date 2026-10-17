"""Build SnailMailExtras.dat from the extracted Android release assets."""

from __future__ import annotations

import io
import re
from pathlib import Path

from PIL import Image

from .archive import parse_archive_index, read_archive_entry, write_archive

ANDROID_ROOT = Path("artifacts/android/asm_extracted")
# The APK's loose assets, beside the asm.mp3 archive that asm_extracted unpacks.
APK_ASSETS = Path("artifacts/android/unpacked/com.sandlotgames.snailmail.1/assets")
OUTPUT = Path("artifacts/bin/SnailMailExtras.dat")
PC_ARCHIVE = Path("artifacts/bin/SnailMail.dat")
TUTORIAL = "LEVELS/TUTORIAL.TXT"
VOICED_MESSAGE = re.compile(r'Sample="([^"]+)" Message="([^"]*)"')

def swap_tga32_rb(raw: bytes) -> bytes:
    """Swap OpenGL ES RGBA 32-bit TGA pixels to PC D3D BGRA layout."""
    width = int.from_bytes(raw[12:14], "little")
    height = int.from_bytes(raw[14:16], "little")
    n = width * height * 4
    out = bytearray(raw[: 18 + n] + b"\x00\x00")
    out[18 : 18 + n : 4], out[20 : 18 + n : 4] = raw[20 : 18 + n : 4], raw[18 : 18 + n : 4]
    return bytes(out)

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


def tutorial_with_pc_messages(mobile: bytes, pc: bytes) -> bytes:
    """The mobile tutorial course, each line showing the PC text for the voice clip it plays.

    The port plays the PC voice clips, which tell the player to steer with the mouse
    and hold its button to shoot; the mobile text says tilt and touch.
    """
    pc_messages = dict(VOICED_MESSAGE.findall(pc.decode("latin-1")))

    def pc_message(match: re.Match[str]) -> str:
        return f'Sample="{match[1]}" Message="{pc_messages.get(match[1], match[2])}"'

    return VOICED_MESSAGE.sub(pc_message, mobile.decode("latin-1")).encode("latin-1")


def build_extras_files(android_root: Path, pc_archive: Path, apk_assets: Path) -> dict[str, bytes]:
    """Mobile-only assets converted to PC archive conventions."""
    files: dict[str, bytes] = {}
    for index in (4, 5, 6):
        surface_path = android_root / f"OBJECTS/WORLD00/SURFACE{index}.PNG"
        track_tga, slide_tga = split_surface_strip(surface_path.read_bytes())
        files[f"OBJECTS/WORLD00/TRACK{index}.TGA"] = track_tga
        files[f"OBJECTS/WORLD00/SLIDE{index}.TGA"] = slide_tga
    fringe_path = android_root / "SPRITES/FRINGECOLOURS.TGA"
    files["SPRITES/FRINGECOLOURS.TGA"] = fringe_path.read_bytes()
    for rel in ("OBJECTS/TRAMPRING/_OBJECT.TXT", "GALAXY/_GALAXYPRO.TXT"):
        p = android_root / rel
        if p.exists():
            files[rel] = p.read_bytes()
    for rel in (
        "OBJECTS/TRAMPRING/TRAMPRING.TGA",
        "GALAXY/BORDERSPACEMAPPRO.TGA",
        "GALAXY/LEVELSELECTPRO.TGA",
        "GALAXY/LINEPRO.TGA",
    ):
        p = android_root / rel
        if p.exists():
            files[rel] = swap_tga32_rb(p.read_bytes())
    for folder in ("LEVELS", "SEGMENTS"):
        for path in sorted((android_root / folder).glob("*.TXT")):
            files[f"{folder}/{path.name}"] = path.read_bytes()
    pc_index = parse_archive_index(pc_archive)
    pc_tutorial = read_archive_entry(pc_archive, pc_index.entry_by_path(TUTORIAL))
    files[TUTORIAL] = tutorial_with_pc_messages(files[TUTORIAL], pc_tutorial)
    for stem in ("SPACEPRO", "SPACEPRO2"):
        txt_p = android_root / f"BACKGROUNDS/{stem}.TXT"
        jpg_p = android_root / f"BACKGROUNDS/{stem}.JPG"
        if txt_p.exists() and jpg_p.exists():
            files[f"BACKGROUNDS/{stem}.TXT"] = txt_p.read_bytes()
            im = Image.open(io.BytesIO(jpg_p.read_bytes())).convert("RGB").resize((512, 256), Image.Resampling.BILINEAR)
            files[f"BACKGROUNDS/{stem}.TGA"] = tga_rgb24(im)
    starmap_txt = android_root / "BACKGROUNDS/STARMAPPRO.TXT"
    starmap_jpg = android_root / "BACKGROUNDS/STARMAPPROBG.JPG"
    if starmap_txt.exists() and starmap_jpg.exists():
        files["BACKGROUNDS/STARMAPPRO.TXT"] = starmap_txt.read_bytes()
        src = Image.open(io.BytesIO(starmap_jpg.read_bytes())).convert("RGB").crop((0, 0, 480, 320))
        tile = src.resize((320, 240), Image.Resampling.BILINEAR)
        canvas = src.resize((512, 256), Image.Resampling.BILINEAR)
        canvas.paste(tile, (0, 0))
        files["BACKGROUNDS/STARMAPPROBG.TGA"] = tga_rgb24(canvas)
    splash_txt = android_root / "BACKGROUNDS/SPLASHPRO.TXT"
    splash_png = android_root / "BACKGROUNDS/SPLASHPRO.PNG"
    if splash_txt.exists() and splash_png.exists():
        files["BACKGROUNDS/SPLASHPRO.TXT"] = splash_txt.read_bytes()
        src = Image.open(io.BytesIO(splash_png.read_bytes())).convert("RGB").crop((0, 0, 480, 320))
        scaled = src.resize((640, 480), Image.Resampling.BILINEAR)
        canvas = Image.new("RGB", (640, 512))
        canvas.paste(scaled, (0, 0))
        files["BACKGROUNDS/SPLASHPRO_A.TGA"] = tga_rgb24(canvas.crop((0, 0, 512, 512)))
        files["BACKGROUNDS/SPLASHPRO_B.TGA"] = tga_rgb24(canvas.crop((512, 0, 640, 512)))
    # Android's ramp sound (gSFXBank 42), a mono Vorbis file like the PC SFX2 ones.
    files["SFX2/UPRAMP.OGG"] = (apk_assets / "upramp.ogg").read_bytes()
    return files


def generate(
    root: Path, *, out: Path | None = None, android_root: Path | None = None, apk_assets: Path | None = None
) -> Path:
    target = out or (root / OUTPUT)
    source = android_root or (root / ANDROID_ROOT)
    files = build_extras_files(source, root / PC_ARCHIVE, apk_assets or (root / APK_ASSETS))
    write_archive(target, files)
    return target
