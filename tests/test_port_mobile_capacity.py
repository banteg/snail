"""Long mobile courses must fit before track condensation runs."""

import re
import shutil
import struct
import subprocess

import pytest

from snail.archive import parse_archive_index, read_archive_entry, write_archive
from snail.symbols import REPO_ROOT

WASM = REPO_ROOT / "port/zig-out/bin/snail.wasm"
BASE = REPO_ROOT / "artifacts/bin/SnailMail.dat"
EXTRAS = REPO_ROOT / "artifacts/bin/SnailMailExtras.dat"


@pytest.mark.skipif(
    shutil.which("node") is None or not all(p.exists() for p in (WASM, BASE, EXTRAS)),
    reason="needs node, snail.wasm, and both game archives",
)
# ArcadePro010, the longest mobile course, has 3407 rows as Android lays it.
@pytest.mark.parametrize("rows,ultimate,accepted", [(3407, True, True), (3499, True, True), (3500, True, False), (3407, False, False)])
def test_mobile_course_capacity_before_condensation(tmp_path, rows, ultimate, accepted):
    def segment_rows(data):
        return sum(line.startswith(b"@") for line in data.splitlines()) - 2

    index = parse_archive_index(EXTRAS)
    files = {entry.path.upper(): read_archive_entry(EXTRAS, entry) for entry in index.entries}
    # Keep the entry/exit definitions independent of later mobile asset changes.
    base_index = parse_archive_index(BASE)
    entry_rows = 0
    for kind, source in (("Start", "START.TXT"), ("Finish", "FINISH.TXT")):
        data = read_archive_entry(BASE, base_index.entry_by_path("Segments/" + source))
        files[f"SEGMENTS/CAPACITY{kind.upper()}.TXT"] = data
        entry_rows += segment_rows(data)
    # Ultimate lays Padding before each listed segment, as Android does.
    padding_rows = segment_rows(files["SEGMENTS/PADDING.TXT"]) if ultimate else 0
    remaining = rows - entry_rows
    # A segment owns at most 256 rows, so split the course into smaller pieces.
    names = []
    while remaining > 0:
        name = f"CapacityProbe{len(names)}.txt"
        names.append(name)
        count = min(240, remaining - padding_rows)
        files[f"SEGMENTS/{name.upper()}"] = (
            "ID:0\r\nName:'CapacityProbe'\r\nData:\r\n@@@@@@@@@@\r\n"
            + "@________@\r\n" * count + "@@@@@@@@@@\r\n"
        ).encode()
        remaining -= padding_rows + count
    level = files["LEVELS/ARCADEPRO010.TXT"]
    level = re.sub(
        rb"(Segments Begin:[^\r\n]*\r?\n).*?(Segments End:)",
        lambda match: match[1] + ("\r\n".join(names) + "\r\n").encode() + match[2],
        level, flags=re.DOTALL,
    )
    level = re.sub(rb"(First:[^\r\n]*\s*)Start.txt", rb"\g<1>CapacityStart.txt", level)
    level = re.sub(rb"(Last:[^\r\n]*\s*)Finish.txt", rb"\g<1>CapacityFinish.txt", level)
    files["LEVELS/ARCADEPRO010.TXT"] = level
    if ultimate:
        (tmp_path / "SnailMail.dat").symlink_to(BASE)
        write_archive(tmp_path / "SnailMailExtras.dat", files)
    else:
        base_files = {entry.path.upper(): read_archive_entry(BASE, entry) for entry in base_index.entries}
        base_files.update({name: data for name, data in files.items() if "CAPACITY" in name})
        base_files["LEVELS/ARCADE001.TXT"] = level
        write_archive(tmp_path / "SnailMail.dat", base_files)
    config = bytearray(196)
    struct.pack_into("<ff", config, 0, 1.0, 1.0)
    config[0x60:0x69] = b"Fluctuosa"
    struct.pack_into("<ifi", config, 0x40, 50, 0.5, 50)
    struct.pack_into("<ii", config, 0xA0, 1, 1)
    config[0xC0] = 1
    (tmp_path / "SnailMail.cfg").write_bytes(config)
    (tmp_path / "SnailMailMobile.cfg").write_bytes(config)
    (tmp_path / "SnailMailPro.cfg").write_bytes(struct.pack("<ii", 10, 10))
    keys = tmp_path / "pro10.keys"
    menu_y = 240 if ultimate else 172
    menu = (
        "600 escape\n700 mouse 345 112\n720 click 3\n"
        f"800 mouse 345 {menu_y}\n820 click 3\n"
    )
    keys.write_text(menu)
    args = ["node", str(REPO_ROOT / "port/shell/run.mjs"), str(WASM)]
    if ultimate:
        args += ["--profile", "ultimate"]
    args.extend(["--trace", "--keys", str(keys)])
    preview = subprocess.run(
        [*args, "--ticks", "900"], cwd=tmp_path,
        capture_output=True, text=True, check=True,
    )
    button = re.findall(r'widget \d+ at \(([-\d]+), ([-\d]+)\) size ([-\d]+) x ([-\d]+).*"Deliver!"', preview.stderr)
    assert button, preview.stderr
    x, y, width, height = map(int, button[-1])
    keys.write_text(menu + f"920 mouse {x + width // 2} {y + height // 2}\n940 click 3\n")
    process = subprocess.run(
        [*args, "--ticks", "1050"], cwd=tmp_path,
        capture_output=True, text=True, check=False,
    )
    # Both originals only report a track that is too long, and build it.
    assert process.returncode == 0, process.stderr
    assert 'level "Eximius Ferreus"' in process.stderr
    limit = 3500 if ultimate else 3100
    report = f"Track (Eximius Ferreus) too long, Maximum Length {limit}"
    assert (report not in process.stderr) == accepted, process.stderr
