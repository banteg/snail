'use strict';

// Lockstep capture: records a session of the original game so the port can
// replay it tick for tick and compare (docs/re/frida-lockstep-capture.md).
//
//   frida -f .\SnailMail_unwrapped.exe -l <repo>\tools\frida\snailmail-lockstep.js
//
// Spawn the game with -f: the startup warmup happens before the first frame,
// and a late attach misses it.
//
// Output, one directory per session under OUTPUT_ROOT:
//   tape.ndjson   session, startup (warmup count, RNG, config), one `tick` row
//                 per cRGame::AI call (inputs at entry, state at exit),
//                 `render` rows between ticks, `frame` rows for captures,
//                 `fpu` rows with the x87 control word (at startup, the path
//                 template build, and whenever it changes between ticks)
//   frames/       BMP captures of the game window every CAPTURE_EVERY presents
//   start/        SnailMail.cfg and Score?.dat as they were at launch

const OUTPUT_ROOT = 'C:\\share\\snail\\lockstep';
const CAPTURE_EVERY = 120; // presents between frame captures; 0 turns captures off
const FLUSH_EVERY = 30; // rows between flushes
const TARGET_MODULE_NAMES = ['SnailMail_unwrapped.exe', 'SnailMail.RWG'];
const PREFERRED_IMAGE_BASE = 0x400000;
const SCRIPT_VERSION = 3;

// Addresses and field offsets, generated from the symbol manifests and the
// recovered headers: `uv run snail port lockstep-script --write`.
// @layout-begin (generated; do not edit)
const LAYOUT = {
  "functions": {"main_loop": "0x406dc0", "random_float": "0x44dc90", "construct_game_runtime": "0x407b60", "game_ai": "0x40a2a0", "render_scene": "0x4134c0", "present": "0x413520", "template_bank": "0x408060"},
  "main_loop_end": "0x4072f0",
  "globals": {"game": ["0x4df904", 4], "keyboard_current": ["0x777c4c", 256], "keyboard_previous": ["0x777b4c", 256], "controller_slot0": ["0x50333c", 56], "controller_slot1": ["0x503374", 56], "mouse_live_x": ["0x777d58", 4], "mouse_live_y": ["0x777d60", 4], "left_button_state": ["0x4b7234", 1], "left_button_latch": ["0x4b7764", 1], "right_button_state": ["0x4b7640", 1], "right_button_latch": ["0x4b7230", 1], "mouse_wheel_delta": ["0x4dfad0", 4], "render_queue_active": ["0x4b7236", 1], "runtime_config": ["0x4df918", 196], "math_random_index": ["0x77ff3c", 4], "d3d_device": ["0x502fec", 4], "main_window": ["0x4dfaf0", 4], "crt_rand_seed": ["0x4b1f40", 4]},
  "snapshot": {"frontend_state": ["0x1b8", "i32"], "saved_frontend_state": ["0x1bc", "i32"], "fade_state": ["0x24", "i32"], "frame_counter": ["0x51c", "i32"], "fixed_update_count": ["0x3c", "i32"], "fixed_update_accumulator": ["0x518", "f32"], "subgame_state": ["0x74654", "i32"], "level_mode": ["0x74658", "i32"], "level_mode_arg": ["0x7465c", "i32"], "subgame_rate": ["0x74650", "f32"], "replay_cursor": ["0x1066bf4", "i32"], "x": ["0x42fde4", "f32"], "y": ["0x42fde8", "f32"], "z": ["0x42fdec", "f32"], "vx": ["0x43018c", "f32"], "vy": ["0x430190", "f32"], "vz": ["0x430194", "f32"], "score": ["0x430060", "i32"], "lives": ["0x430180", "i32"], "life_stock": ["0x4340bc", "i32"], "shooting_tier": ["0x430084", "i32"], "track_z_offset": ["0x4324b8", "f32"], "track_z_anchor": ["0x4324bc", "f32"], "right_x": ["0x42fdb4", "f32"], "right_y": ["0x42fdb8", "f32"], "right_z": ["0x42fdbc", "f32"], "up_x": ["0x42fdc4", "f32"], "up_y": ["0x42fdc8", "f32"], "up_z": ["0x42fdcc", "f32"], "forward_x": ["0x42fdd4", "f32"], "forward_y": ["0x42fdd8", "f32"], "forward_z": ["0x42fddc", "f32"], "follow_active": ["0x430100", "u8"], "follow_sample": ["0x43010c", "i32"], "follow_progress": ["0x430110", "f32"], "follow_vertical": ["0x430114", "f32"], "follow_up_x": ["0x430120", "f32"], "follow_up_y": ["0x430124", "f32"], "follow_up_z": ["0x430128", "f32"]},
};
// @layout-end

let image = null; // the game module
let tape = null;
let rows = 0;
let sessionDir = null;
let ticks = 0;
let presents = 0;
let warmup = 0;
let constructed = false;
let lastControlWord = null;

// The x87 control word of the calling thread (precision and rounding control),
// which decides how the original rounds its float arithmetic. Read by a few
// bytes of x86 rather than a CModule: Frida's TinyCC inline assembly faulted.
let readControlWord = null;
try {
  const code = Memory.alloc(Process.pageSize);
  Memory.patchCode(code, 16, (writable) => {
    writable.writeByteArray([
      0x83, 0xec, 0x04, //       sub esp, 4
      0xd9, 0x3c, 0x24, //       fnstcw [esp]
      0x0f, 0xb7, 0x04, 0x24, // movzx eax, word [esp]
      0x83, 0xc4, 0x04, //       add esp, 4
      0xc3, //                   ret
    ]);
  });
  readControlWord = new NativeFunction(code, 'uint16', []);
} catch (error) {
  console.error('[snailmail-lockstep] cannot read the FPU control word: ' + error);
}

function recordControlWord(where) {
  if (readControlWord === null) return;
  let cw;
  try {
    cw = readControlWord();
  } catch (error) {
    // An optional reading must not cost the tick rows.
    console.error('[snailmail-lockstep] FPU control word read failed, no more fpu rows: ' + error);
    readControlWord = null;
    return;
  }
  if (cw === lastControlWord && where === 'tick') return;
  lastControlWord = cw;
  write({ t: 'fpu', where, after: ticks, cw: '0x' + cw.toString(16) });
}

// --- frame captures ------------------------------------------------------------

function comMethod(object, index, returns, args) {
  const vtable = object.readPointer();
  return new NativeFunction(vtable.add(index * 4).readPointer(), returns, ['pointer'].concat(args), 'stdcall');
}

const D3D = {
  device_GetDisplayMode: 8,
  device_CreateImageSurface: 27,
  device_GetFrontBuffer: 30,
  surface_Release: 2,
  surface_LockRect: 9,
  surface_UnlockRect: 10,
  FMT_A8R8G8B8: 21,
  LOCK_READONLY: 0x10,
};

function writeBmp(path, width, height, pixels) {
  // 32-bit top-down BMP from BGRA rows.
  const header = new ArrayBuffer(54);
  const v = new DataView(header);
  v.setUint8(0, 0x42); v.setUint8(1, 0x4d);
  v.setUint32(2, 54 + pixels.byteLength, true);
  v.setUint32(10, 54, true);
  v.setUint32(14, 40, true);
  v.setInt32(18, width, true);
  v.setInt32(22, -height, true);
  v.setUint16(26, 1, true);
  v.setUint16(28, 32, true);
  v.setUint32(34, pixels.byteLength, true);
  const file = new File(path, 'wb');
  file.write(header);
  file.write(pixels.buffer);
  file.close();
}

// The game window's client area from the front buffer, which in windowed
// mode covers the whole screen.
function captureFrame(name) {
  const device = globalAt('d3d_device').readPointer();
  if (device.isNull()) return null;
  const mode = Memory.alloc(16);
  if (comMethod(device, D3D.device_GetDisplayMode, 'int', ['pointer'])(device, mode) < 0) return null;
  const screenWidth = mode.readU32();
  const screenHeight = mode.add(4).readU32();
  const surfaceOut = Memory.alloc(4);
  if (comMethod(device, D3D.device_CreateImageSurface, 'int', ['uint', 'uint', 'uint', 'pointer'])(
    device, screenWidth, screenHeight, D3D.FMT_A8R8G8B8, surfaceOut) < 0) return null;
  const surface = surfaceOut.readPointer();
  try {
    if (comMethod(device, D3D.device_GetFrontBuffer, 'int', ['pointer'])(device, surface) < 0) return null;
    const window = globalAt('main_window').readPointer();
    const rect = Memory.alloc(16);
    user32.GetClientRect(window, rect);
    const width = rect.add(8).readS32();
    const height = rect.add(12).readS32();
    const origin = Memory.alloc(8);
    user32.ClientToScreen(window, origin);
    const left = Math.max(0, origin.readS32());
    const top = Math.max(0, origin.add(4).readS32());
    const w = Math.min(width, screenWidth - left);
    const h = Math.min(height, screenHeight - top);
    if (w <= 0 || h <= 0) return null;
    const locked = Memory.alloc(8);
    if (comMethod(surface, D3D.surface_LockRect, 'int', ['pointer', 'pointer', 'uint'])(surface, locked, NULL, D3D.LOCK_READONLY) < 0) return null;
    const pitch = locked.readS32();
    const bits = locked.add(4).readPointer();
    const pixels = new Uint8Array(w * h * 4);
    for (let y = 0; y < h; ++y) {
      const row = new Uint8Array(bits.add((top + y) * pitch + left * 4).readByteArray(w * 4));
      pixels.set(row, y * w * 4);
    }
    comMethod(surface, D3D.surface_UnlockRect, 'int', [])(surface);
    writeBmp(sessionDir + '\\frames\\' + name, w, h, pixels);
    return { width: w, height: h };
  } finally {
    comMethod(surface, D3D.surface_Release, 'uint', [])(surface);
  }
}

// --- hooks ---------------------------------------------------------------------

function hook(name, callbacks) {
  return Interceptor.attach(va(LAYOUT.functions[name]), callbacks);
}

function start() {
  bindWin32();
  sessionDir = OUTPUT_ROOT + '\\' + timestamp() + '-' + Process.id;
  makeDirectory(sessionDir + '\\frames');
  tape = new File(sessionDir + '\\tape.ndjson', 'wb');
  console.log('[snailmail-lockstep] writing ' + sessionDir);
  write({
    t: 'session', version: SCRIPT_VERSION, module: image.name, module_base: image.base.toString(),
    module_path: image.path, capture_every: CAPTURE_EVERY, frida: Frida.version,
  });
  write(Object.assign({ t: 'files' }, copyStartFiles()));

  const mainLoopStart = va(LAYOUT.functions.main_loop);
  const mainLoopEnd = va(LAYOUT.main_loop_end);
  const warmupHook = hook('random_float', {
    onEnter() {
      // The warmup loop: RAND calls straight from game_startup_and_main_loop
      // before the runtime is constructed, timeGetTime() % 1000 of them.
      if (!constructed && this.returnAddress.compare(mainLoopStart) >= 0 && this.returnAddress.compare(mainLoopEnd) < 0) {
        ++warmup;
      }
    },
  });
  hook('construct_game_runtime', {
    onEnter() {
      constructed = true;
      warmupHook.detach(); // RAND runs constantly from here on
      const [seed, index] = rng();
      write({
        t: 'startup', warmup, crt_rand_seed: seed, math_random_index: index,
        config: hexBytes(globalAt('runtime_config'), LAYOUT.globals.runtime_config[1]),
      });
      recordControlWord('startup');
      tape.flush();
    },
  });
  hook('template_bank', {
    onEnter() {
      recordControlWord('template_bank');
    },
  });
  hook('game_ai', {
    onEnter() {
      recordControlWord('tick');
      this.game = this.context.ecx;
      this.inputs = inputs();
    },
    onLeave(retval) {
      const row = Object.assign({ t: 'tick', n: ticks }, this.inputs);
      row.s = snapshot(this.game);
      row.rng = rng();
      row.r = retval.toInt32();
      write(row);
      ++ticks;
      if (row.r >= 1 && row.r <= 3) tape.flush(); // the game is quitting
    },
  });
  hook('render_scene', {
    onEnter() {
      write({ t: 'render', after: ticks });
    },
  });
  hook('present', {
    onLeave() {
      ++presents;
      if (CAPTURE_EVERY > 0 && (presents === 1 || presents % CAPTURE_EVERY === 0)) {
        const name = 'present-' + String(presents).padStart(6, '0') + '.bmp';
        let result = null;
        try {
          result = captureFrame(name);
        } catch (error) {
          console.error('[snailmail-lockstep] frame capture failed: ' + error);
        }
        if (result) write({ t: 'frame', present: presents, after: ticks, file: 'frames/' + name, width: result.width, height: result.height });
        tape.flush();
      }
    },
  });
  console.log('[snailmail-lockstep] hooks installed; play, then quit the game from its menu');
}

function waitForImage() {
  for (const name of TARGET_MODULE_NAMES) {
    const module = Process.findModuleByName(name);
    if (module) {
      image = module;
      start();
      return;
    }
  }
  setTimeout(waitForImage, 50);
}

if (LAYOUT === null) {
  throw new Error('generate the layout first: uv run snail port lockstep-script --write');
}
waitForImage();
