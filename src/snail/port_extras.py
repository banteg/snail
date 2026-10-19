"""Build SnailMailExtras.dat from Android content and matching iPhone HD art."""

from __future__ import annotations

import io
import re
from pathlib import Path

from PIL import Image, ImageMath

from .archive import parse_archive_index, read_archive_entry, write_archive

ANDROID_ROOT = Path("artifacts/android/asm_extracted")
# The APK's loose assets, beside the asm.mp3 archive that asm_extracted unpacks.
APK_ASSETS = Path("artifacts/android/unpacked/com.sandlotgames.snailmail.1/assets")
IOS_ROOT = Path("artifacts/asset-scout/src/ios19/Payload/iSM103010_1.app")
OUTPUT = Path("artifacts/bin/SnailMailExtras.dat")
PC_ARCHIVE = Path("artifacts/bin/SnailMail.dat")
TUTORIAL = "LEVELS/TUTORIAL.TXT"
VOICED_MESSAGE = re.compile(r'Sample="([^"]+)" Message="([^"]*)"(?: SampleB="[^"]*" MessageB="[^"]*")?')

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


def match_surface_palette(high: Image.Image, reference: Image.Image) -> Image.Image:
    """Keep HD detail, transferring the Android tile's low-resolution colours.

    iPhone 1.9's red set is darker and more magenta than Android's. Transfer
    the signed colour difference at Android resolution back onto the HD tile,
    rather than enlarging Android or recolouring the warning arrows by hand.
    Work on each tile separately so adjacent atlas tiles cannot bleed into it.
    """
    reduced = high.resize(reference.size, Image.Resampling.LANCZOS)
    channels = []
    for original, target, source in zip(
        high.split(), reference.split(), reduced.split(), strict=True,
    ):
        delta = ImageMath.lambda_eval(
            lambda images: images["target"] - images["source"],
            target=target.convert("F"),
            source=source.convert("F"),
        ).resize(high.size, Image.Resampling.BILINEAR)
        channels.append(
            ImageMath.lambda_eval(
                lambda images: images["original"] + images["delta"] + 0.5,
                original=original.convert("F"), delta=delta,
            ).convert("L")
        )
    return Image.merge("RGB", channels)


def hd_surface_tiles(
    ios_bytes: bytes, android_bytes: bytes, *, match_palette: bool,
) -> tuple[bytes, bytes]:
    """Decode iPhone 1.9's RGBA-ordered TGA atlas into two 256px PC tiles.

    All seven atlases use OpenGL channel order, including the 24-bit sets 5/6.
    Once R/B are swapped, sets 0-3 reproduce PC Track/Slide0-3 pixel for pixel.
    """
    raw = Image.open(io.BytesIO(ios_bytes)).convert("RGB")
    red, green, blue = raw.split()
    high = Image.merge("RGB", (blue, green, red))
    reference = Image.open(io.BytesIO(android_bytes)).convert("RGB")
    if high.size != (1024, 256) or reference.size != (512, 128):
        raise ValueError(f"unexpected HD/Android surface sizes: {high.size}, {reference.size}")
    tiles = []
    for index in range(2):
        tile = high.crop((index * 256, 0, (index + 1) * 256, 256))
        if match_palette:
            tile = match_surface_palette(
                tile, reference.crop((index * 128, 0, (index + 1) * 128, 128)),
            )
        tiles.append(tga_rgb24(tile))
    return tiles[0], tiles[1]


def tutorial_with_pc_messages(mobile: bytes, pc: bytes) -> bytes:
    """The mobile tutorial course, each line showing the PC text for the voice clip it plays.

    The port plays the PC voice clips, which tell the player to steer with the mouse
    and hold its button to shoot; the mobile text says tilt and touch.
    """
    pc_messages = dict(VOICED_MESSAGE.findall(pc.decode("latin-1")))

    def pc_message(match: re.Match[str]) -> str:
        return f'Sample="{match[1]}" Message="{pc_messages.get(match[1], match[2])}"'

    return VOICED_MESSAGE.sub(pc_message, mobile.decode("latin-1")).encode("latin-1")


def build_extras_files(
    android_root: Path, pc_archive: Path, apk_assets: Path, ios_root: Path,
) -> dict[str, bytes]:
    """Android content with matching HD art, converted to PC conventions."""
    files: dict[str, bytes] = {}
    for index in (4, 5, 6):
        surface_path = android_root / f"OBJECTS/WORLD00/SURFACE{index}.PNG"
        hd_path = ios_root / f"objects_world00_hi_surface{index}.tga"
        track_tga, slide_tga = hd_surface_tiles(
            hd_path.read_bytes(), surface_path.read_bytes(), match_palette=index == 4,
        )
        files[f"OBJECTS/WORLD00/TRACK{index}.TGA"] = track_tga
        files[f"OBJECTS/WORLD00/SLIDE{index}.TGA"] = slide_tga
    fringe_path = android_root / "SPRITES/FRINGECOLOURS.TGA"
    files["SPRITES/FRINGECOLOURS.TGA"] = fringe_path.read_bytes()
    for rel in ("OBJECTS/TRAMPRING/_OBJECT.TXT", "GALAXY/_GALAXYPRO.TXT", "INTRO/CREDITS.TXT", "X/_ANIMATION.TXT"):
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
            # These skies use full-image normalized UVs: keep every source row.
            im = Image.open(io.BytesIO(jpg_p.read_bytes())).convert("RGB")
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
    root: Path, *, out: Path | None = None, android_root: Path | None = None,
    apk_assets: Path | None = None, ios_root: Path | None = None,
) -> Path:
    target = out or (root / OUTPUT)
    source = android_root or (root / ANDROID_ROOT)
    files = build_extras_files(
        source, root / PC_ARCHIVE, apk_assets or (root / APK_ASSETS), ios_root or (root / IOS_ROOT),
    )
    write_archive(target, files)
    return target
