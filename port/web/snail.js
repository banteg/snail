// Runs snail-web.wasm in the page: loads SnailMail.dat (served packed, see
// fetchArchive) into the in-memory file system, forwards keyboard and mouse input in DirectInput terms, and calls
// snail_frame once per animation frame with the elapsed time.
//
// The game's own loading screen covers the canvas while the page loads and
// starts the game, then waits for a click or key press: browsers allow sound only after a gesture,
// and taking that gesture here keeps it from reaching the game (where it would
// skip the intro).
//
// Files the game writes are kept in IndexedDB (storage.js). The game saved its
// score tables only when quitting, so the page saves when it is hidden.
//
// Enhancements over the original (settings.js) switch on and off in the page:
// rendering at the display's resolution, the game's Fullscreen option filling
// the screen, trapping the mouse (pointer lock: the game's cursor then moves by
// relative motion, at the speed it had), and drawing the track further ahead
// (shell/draw_distance.h; the simulation never sees it).
//
// URL parameters: ?warmup=N fixes the random warmup (the original used
// timeGetTime() % 1000, so by default every start differs); ?reset clears
// saved progress, scores and options; ?mute silences the game and ?mute=0
// brings sound back (both remembered).

import { AudioPresenter } from "./audio.js";
import { Renderer } from "./renderer.js";
import { Settings } from "./settings.js";
import { openSaves } from "./storage.js";
import { createWasi, ExitStatus, MemoryFileSystem } from "./wasi.js";

const canvas = document.getElementById("screen");
const status = document.getElementById("status");
const splash = document.getElementById("splash");
const bar = document.getElementById("bar");

// As cRLoadingBar::AI draws it: 92% of the progress until it is nearly done.
function showProgress(percent) {
  const shown = percent > 98 ? 100 : percent * 0.92;
  bar.style.clipPath = `inset(0 ${100 - shown}% 0 0)`;
}

function show(text, error = false) {
  status.textContent = text;
  status.classList.toggle("error", error);
}

// KeyboardEvent.code -> DirectInput scan code (DIK_*).
const SCAN_CODES = {
  Escape: 0x01, Digit1: 0x02, Digit2: 0x03, Digit3: 0x04, Digit4: 0x05, Digit5: 0x06, Digit6: 0x07,
  Digit7: 0x08, Digit8: 0x09, Digit9: 0x0a, Digit0: 0x0b, Minus: 0x0c, Equal: 0x0d, Backspace: 0x0e,
  Tab: 0x0f, KeyQ: 0x10, KeyW: 0x11, KeyE: 0x12, KeyR: 0x13, KeyT: 0x14, KeyY: 0x15, KeyU: 0x16,
  KeyI: 0x17, KeyO: 0x18, KeyP: 0x19, BracketLeft: 0x1a, BracketRight: 0x1b, Enter: 0x1c,
  ControlLeft: 0x1d, KeyA: 0x1e, KeyS: 0x1f, KeyD: 0x20, KeyF: 0x21, KeyG: 0x22, KeyH: 0x23, KeyJ: 0x24,
  KeyK: 0x25, KeyL: 0x26, Semicolon: 0x27, Quote: 0x28, Backquote: 0x29, ShiftLeft: 0x2a, Backslash: 0x2b,
  KeyZ: 0x2c, KeyX: 0x2d, KeyC: 0x2e, KeyV: 0x2f, KeyB: 0x30, KeyN: 0x31, KeyM: 0x32, Comma: 0x33,
  Period: 0x34, Slash: 0x35, ShiftRight: 0x36, NumpadMultiply: 0x37, AltLeft: 0x38, Space: 0x39,
  CapsLock: 0x3a, F1: 0x3b, F2: 0x3c, F3: 0x3d, F4: 0x3e, F5: 0x3f, F6: 0x40, F7: 0x41, F8: 0x42,
  F9: 0x43, F10: 0x44, Numpad7: 0x47, Numpad8: 0x48, Numpad9: 0x49, NumpadSubtract: 0x4a, Numpad4: 0x4b,
  Numpad5: 0x4c, Numpad6: 0x4d, NumpadAdd: 0x4e, Numpad1: 0x4f, Numpad2: 0x50, Numpad3: 0x51,
  Numpad0: 0x52, NumpadDecimal: 0x53, F11: 0x57, F12: 0x58, NumpadEnter: 0x9c, ControlRight: 0x9d,
  NumpadDivide: 0xb5, AltRight: 0xb8, Home: 0xc7, ArrowUp: 0xc8, PageUp: 0xc9, ArrowLeft: 0xcb,
  ArrowRight: 0xcd, End: 0xcf, ArrowDown: 0xd0, PageDown: 0xd1, Insert: 0xd2, Delete: 0xd3,
};

// SnailMail.dat.gz is the archive without its XOR obfuscation, gzipped
// (src/snail/port_serve.py). The game's loader expects the original bytes, so
// the mask goes back on: it follows the file offset and repeats every 256 bytes.
const DRAW_DISTANCE = 3; // the longer view, as a multiple of the original's

const XOR_KEY = Uint8Array.from({ length: 256 }, (_, i) => ((i * i) & 0xff) ^ ((i * 3) & 0xff));

async function fetchArchive(url, onProgress) {
  const response = await fetch(url);
  if (!response.ok) throw new Error(`${url}: ${response.status} ${response.statusText}`);
  const total = Number(response.headers.get("Content-Length"));
  let received = 0;
  const counter = new TransformStream({
    transform(chunk, controller) {
      received += chunk.length;
      onProgress(received, total);
      controller.enqueue(chunk);
    },
  });
  const unpacked = response.body.pipeThrough(counter).pipeThrough(new DecompressionStream("gzip"));
  const data = new Uint8Array(await new Response(unpacked).arrayBuffer());
  for (let i = 0; i < data.length; i++) data[i] ^= XOR_KEY[i & 0xff];
  return data;
}

// Resolves on the first click on the splash or key press, which the game never sees.
function waitForGesture() {
  showProgress(100);
  splash.classList.add("ready");
  return new Promise((resolve) => {
    const start = (event) => {
      event.preventDefault();
      splash.removeEventListener("pointerdown", start);
      window.removeEventListener("keydown", start);
      resolve();
    };
    splash.addEventListener("pointerdown", start);
    window.addEventListener("keydown", start);
  });
}

function clamp(value, low, high) {
  return Math.max(low, Math.min(high, value));
}

function connectInput(exports, settings) {
  // The cursor in game pixels: from the pointer's position, or moved by its
  // motion while the pointer is locked.
  let x = 320, y = 240;
  const locked = () => document.pointerLockElement === canvas;
  const pointer = (event) => {
    const box = canvas.getBoundingClientRect();
    if (locked()) {
      x = clamp(x + (event.movementX * 640) / box.width, 0, 639);
      y = clamp(y + (event.movementY * 480) / box.height, 0, 479);
    } else {
      x = clamp(((event.clientX - box.left) / box.width) * 640, 0, 639);
      y = clamp(((event.clientY - box.top) / box.height) * 480, 0, 479);
    }
    exports.snail_pointer(Math.floor(x), Math.floor(y));
  };
  const button = (event, down) => {
    if (event.button === 0 || event.button === 2) exports.snail_button(event.button === 0 ? 0 : 1, down);
  };
  canvas.addEventListener("pointermove", pointer);
  canvas.addEventListener("pointerdown", (event) => {
    canvas.focus();
    if (settings.get("trapMouse") && !locked()) lockPointer();
    if (!locked()) canvas.setPointerCapture(event.pointerId);
    pointer(event);
    button(event, 1);
  });
  canvas.addEventListener("pointerup", (event) => {
    pointer(event);
    button(event, 0);
  });
  canvas.addEventListener("contextmenu", (event) => event.preventDefault());
  canvas.addEventListener("wheel", (event) => {
    event.preventDefault();
    if (event.deltaY) exports.snail_wheel(event.deltaY < 0 ? 1 : -1);
  }, { passive: false });
  const key = (event, down) => {
    const code = SCAN_CODES[event.code];
    if (code === undefined || event.metaKey || settings.open) return;
    event.preventDefault();
    exports.snail_key(code, down);
  };
  window.addEventListener("keydown", (event) => key(event, 1));
  window.addEventListener("keyup", (event) => key(event, 0));
  // Keys held while the page loses focus would otherwise stay down.
  window.addEventListener("blur", () => {
    for (const code of Object.values(SCAN_CODES)) exports.snail_key(code, 0);
  });
}

function lockPointer() {
  // Safari returns nothing; others a promise that rejects when the page may not lock yet.
  canvas.requestPointerLock()?.catch?.(() => {});
}

// The game's Fullscreen option (set_fullscreen_mode) with the page as the
// screen. Browsers enter fullscreen only after a gesture: a request without
// one waits for the click that starts the game. Leaving fullscreen through the
// browser turns the game's option off, so its Options menu stays truthful.
class Fullscreen {
  constructor(settings) {
    this.settings = settings;
    this.wanted = false;
    this.exports = null;
    document.addEventListener("fullscreenchange", () => {
      const full = document.fullscreenElement !== null;
      if (full && this.settings.get("trapMouse")) lockPointer();
      if (full !== this.wanted && this.settings.get("fullscreen") && this.exports) {
        this.wanted = full;
        this.exports.snail_fullscreen_changed(full ? 1 : 0);
      }
    });
  }

  request(enabled) {
    this.wanted = enabled;
    this.apply();
  }

  apply() {
    const want = this.wanted && this.settings.get("fullscreen");
    if (want && !document.fullscreenElement && (navigator.userActivation?.isActive ?? true)) {
      document.documentElement
        .requestFullscreen({ navigationUI: "hide" })
        // Escape belongs to the game; holding it still leaves fullscreen.
        .then(() => navigator.keyboard?.lock?.(["Escape"]))
        .catch(() => {});
    } else if (!want && document.fullscreenElement) {
      document.exitFullscreen().catch(() => {});
    }
  }
}

// Sharp rendering draws at the canvas's size in device pixels; otherwise at
// 640x480, scaled up by the page as before.
function connectResolution(renderer, settings) {
  let devicePixels = 640;
  const update = () => renderer.setResolution(settings.get("hidpi") ? Math.max(640, devicePixels) : 640);
  const observer = new ResizeObserver(([entry]) => {
    devicePixels = Math.round(entry.devicePixelContentBoxSize?.[0].inlineSize ?? entry.contentRect.width * devicePixelRatio);
    update();
  });
  try {
    observer.observe(canvas, { box: "device-pixel-content-box" });
  } catch {
    observer.observe(canvas);
  }
  return update;
}

async function main() {
  const renderer = new Renderer(canvas);
  const params = new URLSearchParams(location.search);
  if (params.has("mute")) {
    try {
      localStorage.setItem("snail-mail-mute", params.get("mute") === "0" ? "0" : "1");
    } catch {}
  }
  let muted = false;
  try {
    muted = localStorage.getItem("snail-mail-mute") === "1";
  } catch {}
  const audio = new AudioPresenter({ muted });
  const settings = new Settings((changes) => {
    if ("hidpi" in changes) updateResolution();
    if ("fullscreen" in changes) fullscreen.apply();
    if (changes.trapMouse === false && document.pointerLockElement) document.exitPointerLock();
    if ("drawDistance" in changes) applyDrawDistance();
  });
  let applyDrawDistance = () => {};
  const fullscreen = new Fullscreen(settings);
  const updateResolution = connectResolution(renderer, settings);
  const fs = new MemoryFileSystem();
  const [archive, module] = await Promise.all([
    fetchArchive("SnailMail.dat.gz", (received, total) => showProgress(Math.min(98, (100 * received) / total))),
    WebAssembly.compileStreaming(fetch("snail-web.wasm")),
  ]);
  fs.write("SnailMail.dat", archive);
  const saves = await openSaves();
  if (new URLSearchParams(location.search).has("reset")) await saves.clear();
  for (const [name, bytes] of await saves.load()) fs.write(name, bytes);

  const wasi = createWasi(fs, {
    log: (line, fd) => (fd === 2 ? console.warn : console.log)(line),
    onClose: (path, data) => {
      // The extracted BASS library is a temporary file, deleted on a clean quit.
      if (!/(^|\/)tbass\.dll$/i.test(path)) saves.save(path, data.slice());
    },
  });
  const instance = await WebAssembly.instantiate(module, {
    wasi_snapshot_preview1: wasi.imports,
    snail: { ...renderer.imports(), ...audio.imports(), set_fullscreen: (enabled) => fullscreen.request(enabled !== 0) },
  });
  const exports = instance.exports;
  wasi.bind(exports.memory);
  renderer.bind(exports.memory);
  audio.bind(exports.memory);

  exports._initialize();
  const warmup = new URLSearchParams(location.search).get("warmup");
  if (!exports.snail_start(warmup === null ? Date.now() % 1000 : Number(warmup))) {
    throw new Error("startup failed (see the console)");
  }
  fullscreen.exports = exports;
  applyDrawDistance = () => exports.snail_set_draw_distance(settings.get("drawDistance") ? DRAW_DISTANCE : 1);
  applyDrawDistance();
  await waitForGesture();
  audio.unlock();
  fullscreen.apply(); // a fullscreen request at startup waited for this gesture
  splash.classList.add("gone");
  connectInput(exports, settings);
  const save = () => exports.snail_save();
  document.addEventListener("visibilitychange", () => {
    if (document.visibilityState === "hidden") save();
  });
  window.addEventListener("pagehide", save);
  window.snail = { exports, renderer, audio, fs, settings }; // for the console
  canvas.focus();

  let last = performance.now();
  const frame = (now) => {
    const elapsed = Math.min(1, (now - last) / 1000);
    last = now;
    let quit;
    try {
      quit = exports.snail_frame(elapsed);
    } catch (error) {
      console.error(error);
      show(`Snail Mail stopped: ${error.stack || error}`, true);
      return;
    }
    if (quit) {
      save();
      show(`The game quit (code ${quit}). Reload to play again.`);
      return;
    }
    requestAnimationFrame(frame);
  };
  requestAnimationFrame(frame);
}

main().catch((error) => {
  console.error(error);
  const detail = error instanceof ExitStatus ? `exited with status ${error.code}` : error.stack || String(error);
  show(`Snail Mail stopped: ${detail}`, true);
});
