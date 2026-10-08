"""The layout block of the lockstep capture script (tools/frida/snailmail-lockstep.js).

The script records a session of the original Windows game for the port to
replay tick for tick: the startup random warmup, the input state the game
logic reads before every cRGame::AI call, when frames render and present, a
state snapshot after every tick, and periodic frames. It reads the game's
memory, so it needs addresses and field offsets. Those come from here, not
from hand-copied numbers: offsets are compiled from the recovered headers for
wasm32 (the original's 32-bit x86 layout), and addresses come from the
symbol manifests.
"""

import json
import re
import subprocess
import tempfile
from pathlib import Path

SCRIPT = Path("tools/frida/snailmail-lockstep.js")
FUNCTIONS = Path("analysis/symbols/gameplay-functions.json")
REFERENCES = Path("analysis/symbols/gameplay-references.json")
INCLUDE = Path("tools/match/include")
RUNNER = Path("port/shell/run.mjs")
BLOCK = re.compile(r"(// @layout-begin[^\n]*\n).*?(\n// @layout-end)", re.DOTALL)

# Hooked functions, by manifest name.
FUNCTIONS_USED = {
    "main_loop": "game_startup_and_main_loop",
    "random_float": "random_float_below",  # RAND, which the startup warmup calls
    "construct_game_runtime": "construct_game_runtime",
    "game_ai": "cRGame_AI",
    "render_scene": "render_game_frame_scene",
    "present": "present_backbuffer",
}

# Globals read, by reference-manifest name, with the bytes to read.
GLOBALS_USED = {
    "game": ("g_game", 4),
    "keyboard_current": ("g_keyboard_current_state", 0x100),
    "keyboard_previous": ("g_keyboard_previous_state", 0x100),
    "controller_slot0": ("g_input_controller_slot0", 0x38),
    "controller_slot1": ("g_input_controller_slot1", 0x38),
    "mouse_live_x": ("g_mouse_live_x", 4),
    "mouse_live_y": ("g_mouse_live_y", 4),
    "left_button_state": ("g_left_mouse_button_state", 1),
    "left_button_latch": ("g_left_mouse_button_latch", 1),
    "right_button_state": ("g_right_mouse_button_state", 1),
    "right_button_latch": ("g_right_mouse_button_latch", 1),
    "mouse_wheel_delta": ("g_mouse_wheel_delta", 4),
    "render_queue_active": ("g_render_queue_active", 1),
    "runtime_config": ("g_runtime_config", 0xC4),
    "math_random_index": ("g_math_random_index", 4),
    "d3d_device": ("g_d3d_device", 4),
    "main_window": ("g_main_window", 4),
}

# The CRT's rand() seed: `mov eax, [0x4b1f40]` at the head of rand (0x48bfe5),
# which RAND reaches through j_rand (0x44c920). Not in the reference manifest.
CRT_RAND_SEED = 0x4B1F40

# Per-tick snapshot fields: offsetof(GameRoot, <path>) and how to read them.
SNAPSHOT = {
    "frontend_state": ("players[0].frontend_state", "i32"),
    "saved_frontend_state": ("players[0].saved_frontend_state", "i32"),
    "fade_state": ("fade.state", "i32"),
    "frame_counter": ("frame_counter", "i32"),
    "fixed_update_count": ("fixed_update_count", "i32"),
    "fixed_update_accumulator": ("fixed_update_accumulator", "f32"),
    "subgame_state": ("subgame.subgame_state", "i32"),
    "level_mode": ("subgame.level_mode", "i32"),
    "level_mode_arg": ("subgame.level_mode_arg", "i32"),
    "subgame_rate": ("subgame.subgame_rate", "f32"),
    "replay_cursor": ("subgame.replay_update_cursor", "i32"),
    "x": ("subgame.player.transform.position.x", "f32"),
    "y": ("subgame.player.transform.position.y", "f32"),
    "z": ("subgame.player.transform.position.z", "f32"),
    "vx": ("subgame.player.velocity.x", "f32"),
    "vy": ("subgame.player.velocity.y", "f32"),
    "vz": ("subgame.player.velocity.z", "f32"),
    "score": ("subgame.player.total_score", "i32"),
    "lives": ("subgame.player.lives", "i32"),
    "life_stock": ("subgame.player.visible_life_stock", "i32"),
    "shooting_tier": ("subgame.player.shooting_tier", "i32"),
    "track_z_offset": ("subgame.player.track_z_offset", "f32"),
    "track_z_anchor": ("subgame.player.track_z_anchor", "f32"),
    # The snail's orientation and path-follow state, which set its position while it follows a path.
    "right_x": ("subgame.player.transform.basis_right.x", "f32"),
    "right_y": ("subgame.player.transform.basis_right.y", "f32"),
    "right_z": ("subgame.player.transform.basis_right.z", "f32"),
    "up_x": ("subgame.player.transform.basis_up.x", "f32"),
    "up_y": ("subgame.player.transform.basis_up.y", "f32"),
    "up_z": ("subgame.player.transform.basis_up.z", "f32"),
    "forward_x": ("subgame.player.transform.basis_forward.x", "f32"),
    "forward_y": ("subgame.player.transform.basis_forward.y", "f32"),
    "forward_z": ("subgame.player.transform.basis_forward.z", "f32"),
    "follow_active": ("subgame.player.follow_state.active", "u8"),
    "follow_sample": ("subgame.player.follow_state.sample_index", "i32"),
    "follow_progress": ("subgame.player.follow_state.progress", "f32"),
    "follow_vertical": ("subgame.player.follow_state.vertical_offset", "f32"),
    "follow_up_x": ("subgame.player.follow_state.orientation_up.x", "f32"),
    "follow_up_y": ("subgame.player.follow_state.orientation_up.y", "f32"),
    "follow_up_z": ("subgame.player.follow_state.orientation_up.z", "f32"),
}


def snapshot_offsets(root: Path) -> dict[str, int]:
    """offsetof each snapshot field, compiled from the recovered headers for wasm32."""
    with tempfile.TemporaryDirectory(prefix="snail-lockstep-") as temp:
        source = Path(temp) / "offsets.cpp"
        lines = ["#include <stddef.h>", "#include <stdio.h>", '#include "game_root.h"', "int main() {"]
        lines += [f'    printf("%d\\n", (int)offsetof(GameRoot, {path}));' for path, _ in SNAPSHOT.values()]
        lines += ["    return 0;", "}"]
        source.write_text("\n".join(lines) + "\n")
        program = Path(temp) / "offsets.wasm"
        subprocess.run(
            ["zig", "c++", "-target", "wasm32-wasi", "-std=c++17", "-fms-extensions", "-fdeclspec", "-fno-exceptions",
             "-fno-rtti", "-DSNAIL_PORT", "-Wno-everything", f"-I{(root / INCLUDE).resolve()}", str(source),
             "-o", str(program)],
            check=True, capture_output=True, text=True,
        )  # fmt: skip
        output = subprocess.run(
            ["node", str(root / RUNNER), str(program)], check=True, capture_output=True, text=True, cwd=temp
        ).stdout
    return dict(zip(SNAPSHOT, (int(value) for value in output.split()), strict=True))


def manifest_addresses(root: Path) -> tuple[dict[str, str], dict[str, list]]:
    functions = {}
    for function in json.loads((root / FUNCTIONS).read_text())["functions"]:
        for name in (function["name"], *function.get("aliases", ())):
            functions.setdefault(name, function["address"])
    references = {}
    for symbol in json.loads((root / REFERENCES).read_text())["symbols"]:
        for name in (symbol["name"], *symbol.get("aliases", ())):
            references.setdefault(name, symbol["address"])
    resolved_functions = {key: functions[name] for key, name in FUNCTIONS_USED.items()}
    resolved_globals = {key: [references[name], size] for key, (name, size) in GLOBALS_USED.items()}
    resolved_globals["crt_rand_seed"] = [f"0x{CRT_RAND_SEED:x}", 4]
    return resolved_functions, resolved_globals


def main_loop_end(root: Path, start: str) -> str:
    """The first function after the main loop: the warmup's return addresses lie before it."""
    starts = sorted(int(f["address"], 16) for f in json.loads((root / FUNCTIONS).read_text())["functions"])
    return f"0x{next(a for a in starts if a > int(start, 16)):x}"


def layout(root: Path) -> dict:
    functions, globals_ = manifest_addresses(root)
    offsets = snapshot_offsets(root)
    return {
        "functions": functions,
        "main_loop_end": main_loop_end(root, functions["main_loop"]),
        "globals": globals_,
        "snapshot": {key: [f"0x{offsets[key]:x}", kind] for key, (_, kind) in SNAPSHOT.items()},
    }


def script_text(root: Path) -> str:
    text = (root / SCRIPT).read_text()
    entries = ",\n".join(f"  {json.dumps(key)}: {json.dumps(value)}" for key, value in layout(root).items())
    block = "const LAYOUT = {\n" + entries + ",\n};"
    if not BLOCK.search(text):
        raise ValueError(f"{SCRIPT} has no // @layout-begin ... // @layout-end block")
    return BLOCK.sub(lambda match: match.group(1) + block + match.group(2), text)
