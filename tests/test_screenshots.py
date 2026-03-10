from __future__ import annotations

from pathlib import Path

from PIL import Image

from snail.screenshots import compare_screenshots, parse_scale_search, resolve_compare_size


def test_resolve_compare_size_accepts_named_and_explicit_sizes() -> None:
    assert resolve_compare_size("reference", render_size=(1024, 768), reference_size=(640, 480)) == (640, 480)
    assert resolve_compare_size("render", render_size=(1024, 768), reference_size=(640, 480)) == (1024, 768)
    assert resolve_compare_size("800x600", render_size=(1024, 768), reference_size=(640, 480)) == (800, 600)


def test_parse_scale_search() -> None:
    search = parse_scale_search("0.95:1.05:0.05")
    assert search.values() == [0.95, 1.0, 1.05]


def test_compare_screenshots_writes_outputs_and_metrics(tmp_path: Path) -> None:
    reference_path = tmp_path / "reference.png"
    render_path = tmp_path / "render.png"
    output_dir = tmp_path / "compare"

    reference = Image.new("RGBA", (8, 8), (0, 0, 0, 255))
    for x in range(2, 6):
        for y in range(2, 6):
            reference.putpixel((x, y), (255, 255, 255, 255))
    reference.save(reference_path)

    render = Image.new("RGBA", (8, 8), (0, 0, 0, 255))
    for x in range(3, 7):
        for y in range(2, 6):
            render.putpixel((x, y), (255, 255, 255, 255))
    render.save(render_path)

    summary = compare_screenshots(
        render_path,
        reference_path,
        output_dir=output_dir,
        offset_search=2,
        compare_size_spec="reference",
    )

    assert summary["compare_size"] == {"width": 8, "height": 8}
    assert summary["alignment"]["offset_x"] == -1
    assert summary["alignment"]["offset_y"] == 0
    assert summary["metrics"]["mean_absolute_rgb"]["r"] == 0.0

    outputs = summary["outputs"]
    for key in ("reference", "render", "signed_diff", "absolute_diff", "montage"):
        assert Path(outputs[key]).is_file()
