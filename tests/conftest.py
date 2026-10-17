import itertools
import json
import os
import re
import struct
import subprocess

import pytest

from snail.archive import parse_archive_index, read_archive_entry, write_archive
from snail.port_lockstep import layout_offsets
from snail.symbols import REPO_ROOT

# Fields the JavaScript harnesses reach in the port's memory, in the layout the port compiles.
PORT_LAYOUT = (
    ("subgame", "offsetof(cRGame, subgame)"),
    ("backdrop", "offsetof(cRGame, backdrop)"),
    ("level_definition", "offsetof(cRSubGame, level_definition)"),
    ("level_display_name", "offsetof(SubTracks, level_display_name)"),
    ("player", "offsetof(cRSubGame, player)"),
    ("sm_tracks", "offsetof(cRSubGame, sm_tracks)"),
    ("segment_entry", "sizeof(SegmentCatalogEntry)"),
    ("completion_row_start", "offsetof(cRSubGame, completion_row_start)"),
    ("runtime_row_scan_end", "offsetof(cRSubGame, runtime_row_scan_end)"),
    ("finish_banner_z", "offsetof(cRSubGame, banners.slots[1].position.z)"),
    ("finish_banner_flags", "offsetof(cRSubGame, banners.slots[1].list_flags)"),
    ("player_z", "offsetof(cRSubGoldy, transform.position.z)"),
    ("active_window_min_z", "offsetof(cRSubGoldy, active_window_min_z)"),
)


@pytest.fixture(scope="session")
def port_layout_env() -> dict[str, str]:
    """The environment for a harness that reads `SNAIL_LAYOUT` (tests/port_mobile_runtime.mjs)."""
    return {**os.environ, "SNAIL_LAYOUT": json.dumps(layout_offsets(REPO_ROOT, PORT_LAYOUT, port=True))}


@pytest.fixture
def probe_course(tmp_path):
    """Play a course of the PC Start, the given segment rows and the PC Finish on the headless
    build (Pro 10 in Ultimate, Postal 1 in Original) and return its `--trace`. The snail waits for
    its start click at z = 4 unless `start`."""
    runs = itertools.count()

    def play(rows, ultimate, start=False):
        directory = tmp_path / f"course{next(runs)}"
        directory.mkdir()
        extras = REPO_ROOT / "artifacts/bin/SnailMailExtras.dat"
        files = {entry.path.upper(): read_archive_entry(extras, entry) for entry in parse_archive_index(extras).entries}
        base = REPO_ROOT / "artifacts/bin/SnailMail.dat"
        base_index = parse_archive_index(base)
        for kind in ("START", "FINISH"):
            files[f"SEGMENTS/PROBE{kind}.TXT"] = read_archive_entry(base, base_index.entry_by_path(f"Segments/{kind}.TXT"))
        files["SEGMENTS/PROBE.TXT"] = (
            "ID:0\r\nName:'Probe'\r\nData:\r\n@@@@@@@@@@\r\n"
            + "".join(f"{row}\r\n" for row in rows) + "@________@\r\n" * 40 + "@@@@@@@@@@\r\n"
        ).encode()
        level = files["LEVELS/ARCADEPRO010.TXT"]
        level = re.sub(
            rb"(Segments Begin:[^\r\n]*\r?\n).*?(Segments End:)",
            lambda match: match[1] + b"Probe.txt\r\n" + match[2],
            level, flags=re.DOTALL,
        )  # fmt: skip
        level = re.sub(rb"(First:[^\r\n]*\s*)Start.txt", rb"\g<1>ProbeStart.txt", level)
        level = re.sub(rb"(Last:[^\r\n]*\s*)Finish.txt", rb"\g<1>ProbeFinish.txt", level)
        files["LEVELS/ARCADEPRO010.TXT"] = level
        if ultimate:
            (directory / "SnailMail.dat").symlink_to(base)
            write_archive(directory / "SnailMailExtras.dat", files)
        else:
            base_files = {entry.path.upper(): read_archive_entry(base, entry) for entry in base_index.entries}
            base_files.update({name: data for name, data in files.items() if "PROBE" in name})
            base_files["LEVELS/ARCADE001.TXT"] = level
            write_archive(directory / "SnailMail.dat", base_files)
        config = bytearray(196)
        struct.pack_into("<ff", config, 0, 1.0, 1.0)
        config[0x60:0x69] = b"Fluctuosa"
        struct.pack_into("<ifi", config, 0x40, 50, 0.5, 50)
        struct.pack_into("<ii", config, 0xA0, 1, 1)
        config[0xC0] = 1
        (directory / "SnailMail.cfg").write_bytes(config)
        (directory / "SnailMailMobile.cfg").write_bytes(config)
        (directory / "SnailMailPro.cfg").write_bytes(struct.pack("<ii", 10, 10))
        keys = directory / "probe.keys"
        menu = f"600 escape\n700 mouse 345 112\n720 click 3\n800 mouse 345 {383 if ultimate else 172}\n820 click 3\n"
        keys.write_text(menu)
        args = ["node", str(REPO_ROOT / "port/shell/run.mjs"), str(REPO_ROOT / "port/zig-out/bin/snail.wasm")]
        args += ["--trace", "--keys", str(keys), *(["--profile", "ultimate"] if ultimate else [])]
        preview = subprocess.run([*args, "--ticks", "900"], cwd=directory, capture_output=True, text=True, check=True)
        button = re.findall(r'widget \d+ at \(([-\d]+), ([-\d]+)\) size ([-\d]+) x ([-\d]+).*"Deliver!"', preview.stderr)
        assert button, preview.stderr
        x, y, width, height = map(int, button[-1])
        menu += f"920 mouse {x + width // 2} {y + height // 2}\n940 click 3\n"
        keys.write_text(menu + ("1100 click 3\n" if start else ""))
        run = subprocess.run(
            [*args, "--ticks", "1400" if start else "1050"], cwd=directory, capture_output=True, text=True, check=True
        )
        assert 'level "Eximius Ferreus"' in run.stderr
        return run.stderr

    return play
