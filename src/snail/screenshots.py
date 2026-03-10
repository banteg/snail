from __future__ import annotations

import math
import re
from dataclasses import dataclass
from pathlib import Path

from PIL import Image, ImageChops, ImageDraw, ImageFont, ImageStat


DEFAULT_SCREENSHOT_COMPARE_OUTPUT_DIR = Path("artifacts/screenshots/compare")
_LABEL_BAND_HEIGHT = 20
_MONTAGE_GAP = 8
_DEFAULT_BACKGROUND = (0, 0, 0, 255)


@dataclass(frozen=True)
class ScaleSearch:
    start: float
    stop: float
    step: float

    def values(self) -> list[float]:
        values: list[float] = []
        current = self.start
        epsilon = self.step * 0.5
        while current <= self.stop + epsilon:
            values.append(round(current, 6))
            current += self.step
        return values


@dataclass(frozen=True)
class BestAlignment:
    scale: float
    offset_x: int
    offset_y: int
    rmse: float


def compare_screenshots(
    render_path: Path,
    reference_path: Path,
    *,
    compare_size_spec: str = "reference",
    output_dir: Path = DEFAULT_SCREENSHOT_COMPARE_OUTPUT_DIR,
    scale_search: ScaleSearch | None = None,
    offset_search: int = 0,
    prefix: str | None = None,
) -> dict[str, object]:
    render_image = Image.open(render_path).convert("RGBA")
    reference_image = Image.open(reference_path).convert("RGBA")

    compare_size = resolve_compare_size(
        compare_size_spec,
        render_size=render_image.size,
        reference_size=reference_image.size,
    )
    normalized_reference = reference_image.resize(compare_size, Image.Resampling.BICUBIC)
    normalized_render = render_image.resize(compare_size, Image.Resampling.BICUBIC)

    aligned_render, best_alignment = align_render_for_comparison(
        normalized_render,
        normalized_reference,
        scale_search=scale_search,
        offset_search=offset_search,
    )

    signed_diff = make_signed_diff_image(aligned_render, normalized_reference)
    absolute_diff = make_absolute_diff_image(aligned_render, normalized_reference)
    metrics = compute_metrics(aligned_render, normalized_reference)

    output_dir.mkdir(parents=True, exist_ok=True)
    base_name = prefix or default_compare_prefix(render_path, reference_path)
    reference_output = output_dir / f"{base_name}--reference.png"
    render_output = output_dir / f"{base_name}--render.png"
    signed_output = output_dir / f"{base_name}--signed-diff.png"
    absolute_output = output_dir / f"{base_name}--absolute-diff.png"
    montage_output = output_dir / f"{base_name}--montage.png"

    normalized_reference.save(reference_output)
    aligned_render.save(render_output)
    signed_diff.save(signed_output)
    absolute_diff.save(absolute_output)
    make_montage(
        normalized_reference,
        aligned_render,
        signed_diff,
        absolute_diff,
        labels=(
            "Reference",
            "Render",
            "Signed Diff",
            "Absolute Diff",
        ),
    ).save(montage_output)

    return {
        "render": str(render_path),
        "reference": str(reference_path),
        "render_size": {"width": render_image.width, "height": render_image.height},
        "reference_size": {"width": reference_image.width, "height": reference_image.height},
        "compare_size": {"width": compare_size[0], "height": compare_size[1]},
        "alignment": {
            "scale": best_alignment.scale,
            "offset_x": best_alignment.offset_x,
            "offset_y": best_alignment.offset_y,
            "rmse": round(best_alignment.rmse, 6),
        },
        "metrics": metrics,
        "outputs": {
            "reference": str(reference_output),
            "render": str(render_output),
            "signed_diff": str(signed_output),
            "absolute_diff": str(absolute_output),
            "montage": str(montage_output),
        },
    }


def resolve_compare_size(
    spec: str,
    *,
    render_size: tuple[int, int],
    reference_size: tuple[int, int],
) -> tuple[int, int]:
    lowered = spec.lower()
    if lowered == "reference":
        return reference_size
    if lowered == "render":
        return render_size

    match = re.fullmatch(r"(\d+)x(\d+)", lowered)
    if match is None:
        raise ValueError(f"invalid compare size spec: {spec!r}")
    width = int(match.group(1))
    height = int(match.group(2))
    if width <= 0 or height <= 0:
        raise ValueError("compare size must be positive")
    return width, height


def parse_scale_search(spec: str) -> ScaleSearch:
    match = re.fullmatch(
        r"\s*([-+]?\d+(?:\.\d+)?)\s*:\s*([-+]?\d+(?:\.\d+)?)\s*:\s*([-+]?\d+(?:\.\d+)?)\s*",
        spec,
    )
    if match is None:
        raise ValueError(f"invalid scale search spec: {spec!r}")

    start = float(match.group(1))
    stop = float(match.group(2))
    step = float(match.group(3))
    if step <= 0:
        raise ValueError("scale search step must be positive")
    if stop < start:
        raise ValueError("scale search stop must be >= start")
    if start <= 0:
        raise ValueError("scale search start must be positive")
    return ScaleSearch(start=start, stop=stop, step=step)


def default_compare_prefix(render_path: Path, reference_path: Path) -> str:
    return f"{slugify_stem(render_path.stem)}--vs--{slugify_stem(reference_path.stem)}"


def slugify_stem(value: str) -> str:
    lowered = value.strip().lower()
    collapsed = re.sub(r"[^a-z0-9]+", "-", lowered)
    return collapsed.strip("-") or "image"


def align_render_for_comparison(
    render_image: Image.Image,
    reference_image: Image.Image,
    *,
    scale_search: ScaleSearch | None,
    offset_search: int,
) -> tuple[Image.Image, BestAlignment]:
    scales = scale_search.values() if scale_search is not None else [1.0]
    best_image = render_image
    best_alignment = BestAlignment(scale=1.0, offset_x=0, offset_y=0, rmse=float("inf"))

    for scale in scales:
        for offset_x in range(-offset_search, offset_search + 1):
            for offset_y in range(-offset_search, offset_search + 1):
                candidate = transform_render_image(render_image, scale=scale, offset_x=offset_x, offset_y=offset_y)
                rmse = compute_rmse(candidate, reference_image)
                if rmse < best_alignment.rmse:
                    best_image = candidate
                    best_alignment = BestAlignment(scale=scale, offset_x=offset_x, offset_y=offset_y, rmse=rmse)

    return best_image, best_alignment


def transform_render_image(
    image: Image.Image,
    *,
    scale: float,
    offset_x: int,
    offset_y: int,
) -> Image.Image:
    if scale <= 0:
        raise ValueError("scale must be positive")

    width, height = image.size
    scaled_width = max(1, int(round(width * scale)))
    scaled_height = max(1, int(round(height * scale)))
    scaled = image.resize((scaled_width, scaled_height), Image.Resampling.BICUBIC)
    canvas = Image.new("RGBA", image.size, _DEFAULT_BACKGROUND)
    paste_x = (width - scaled_width) // 2 + offset_x
    paste_y = (height - scaled_height) // 2 + offset_y
    canvas.paste(scaled, (paste_x, paste_y))
    return canvas


def compute_rmse(candidate: Image.Image, reference: Image.Image) -> float:
    difference = ImageChops.difference(candidate.convert("RGB"), reference.convert("RGB"))
    rms = ImageStat.Stat(difference).rms
    return math.sqrt(sum(channel * channel for channel in rms) / len(rms))


def compute_metrics(candidate: Image.Image, reference: Image.Image) -> dict[str, object]:
    candidate_bytes = candidate.convert("RGB").tobytes()
    reference_bytes = reference.convert("RGB").tobytes()
    pixel_count = candidate.width * candidate.height

    signed_sums = [0, 0, 0]
    abs_sums = [0, 0, 0]
    squared_sums = [0, 0, 0]
    max_abs = [0, 0, 0]

    for channel_index, (candidate_channel, reference_channel) in enumerate(
        zip(candidate_bytes, reference_bytes, strict=True)
    ):
        channel = channel_index % 3
        delta = candidate_channel - reference_channel
        signed_sums[channel] += delta
        abs_delta = abs(delta)
        abs_sums[channel] += abs_delta
        squared_sums[channel] += delta * delta
        if abs_delta > max_abs[channel]:
            max_abs[channel] = abs_delta

    def mean(values: list[int]) -> dict[str, float]:
        return {
            "r": round(values[0] / pixel_count, 6),
            "g": round(values[1] / pixel_count, 6),
            "b": round(values[2] / pixel_count, 6),
        }

    def root_mean_square(values: list[int]) -> dict[str, float]:
        return {
            "r": round(math.sqrt(values[0] / pixel_count), 6),
            "g": round(math.sqrt(values[1] / pixel_count), 6),
            "b": round(math.sqrt(values[2] / pixel_count), 6),
        }

    return {
        "mean_signed_rgb": mean(signed_sums),
        "mean_absolute_rgb": mean(abs_sums),
        "rmse_rgb": root_mean_square(squared_sums),
        "max_absolute_rgb": {
            "r": max_abs[0],
            "g": max_abs[1],
            "b": max_abs[2],
        },
    }


def make_signed_diff_image(candidate: Image.Image, reference: Image.Image) -> Image.Image:
    candidate_bytes = candidate.convert("RGB").tobytes()
    reference_bytes = reference.convert("RGB").tobytes()
    out = bytearray(candidate.width * candidate.height * 3)

    for index in range(0, len(candidate_bytes), 3):
        candidate_r, candidate_g, candidate_b = candidate_bytes[index : index + 3]
        reference_r, reference_g, reference_b = reference_bytes[index : index + 3]
        candidate_luma = (candidate_r + candidate_g + candidate_b) / 3.0
        reference_luma = (reference_r + reference_g + reference_b) / 3.0
        delta = int(round(candidate_luma - reference_luma))
        if delta >= 0:
            strength = min(delta * 2, 255)
            out[index : index + 3] = bytes((strength, 0, 0))
        else:
            strength = min((-delta) * 2, 255)
            out[index : index + 3] = bytes((0, 80, strength))

    return Image.frombytes("RGB", candidate.size, bytes(out))


def make_absolute_diff_image(candidate: Image.Image, reference: Image.Image) -> Image.Image:
    candidate_bytes = candidate.convert("RGB").tobytes()
    reference_bytes = reference.convert("RGB").tobytes()
    out = bytearray(candidate.width * candidate.height)

    for pixel_index, index in enumerate(range(0, len(candidate_bytes), 3)):
        candidate_r, candidate_g, candidate_b = candidate_bytes[index : index + 3]
        reference_r, reference_g, reference_b = reference_bytes[index : index + 3]
        delta = (
            abs(candidate_r - reference_r)
            + abs(candidate_g - reference_g)
            + abs(candidate_b - reference_b)
        ) // 3
        out[pixel_index] = delta

    grayscale = Image.frombytes("L", candidate.size, bytes(out))
    return grayscale.convert("RGB")


def make_montage(
    top_left: Image.Image,
    top_right: Image.Image,
    bottom_left: Image.Image,
    bottom_right: Image.Image,
    *,
    labels: tuple[str, str, str, str],
) -> Image.Image:
    width, height = top_left.size
    font = ImageFont.load_default()

    tile_height = height + _LABEL_BAND_HEIGHT
    montage_width = width * 2 + _MONTAGE_GAP * 3
    montage_height = tile_height * 2 + _MONTAGE_GAP * 3
    montage = Image.new("RGBA", (montage_width, montage_height), (24, 24, 28, 255))
    draw = ImageDraw.Draw(montage)

    tiles = (
        (top_left, labels[0], _MONTAGE_GAP, _MONTAGE_GAP),
        (top_right, labels[1], width + _MONTAGE_GAP * 2, _MONTAGE_GAP),
        (bottom_left, labels[2], _MONTAGE_GAP, tile_height + _MONTAGE_GAP * 2),
        (bottom_right, labels[3], width + _MONTAGE_GAP * 2, tile_height + _MONTAGE_GAP * 2),
    )

    for image, label, left, top in tiles:
        draw.text((left, top), label, fill=(240, 240, 240, 255), font=font)
        montage.paste(image.convert("RGBA"), (left, top + _LABEL_BAND_HEIGHT))

    return montage
