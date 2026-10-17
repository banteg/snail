// Drive the browser reactor through the front end by widget text, reading and
// writing game state in the port's layout (tests/conftest.py PORT_LAYOUT).
import { readFile } from 'node:fs/promises';
import { WASI } from 'node:wasi';

export const LAYOUT = JSON.parse(process.env.SNAIL_LAYOUT);

const HIDDEN = 0x1000, KILL_PENDING = 0x200, TEARDOWN_ACTIVE = 0x400;
export const FADE_BEFORE_ACTION = 0x40000000;
export const ESCAPE = 0x01;

// Starts the game in the working directory, which holds the archives (copies:
// WASI follows no link out of it) and saves. The saved config's last high-score
// name, which startup copies to players[0].player_name beside front-end state
// 12, locates the game root that g_game points at.
export async function openGame(wasm, ultimate, playerName) {
  const wasi = new WASI({version: 'preview1', args: [], env: {...process.env, PWD: process.cwd()}, preopens: {'/': process.cwd()}});
  const module = await WebAssembly.compile(await readFile(wasm));
  const imports = wasi.getImportObject();
  imports.snail = Object.fromEntries(WebAssembly.Module.imports(module)
    .filter(i => i.module === 'snail').map(i => [i.name, () => 0]));
  const instance = await WebAssembly.instantiate(module, imports);
  wasi.initialize(instance);
  const e = instance.exports;
  e.snail_set_profile(ultimate ? 1 : 0);
  if (!e.snail_start(0)) throw Error('game startup failed');
  const memory = () => Buffer.from(e.memory.buffer);
  const m = memory();
  const name = Buffer.from(playerName + '\0');
  let root;
  for (let hit = m.indexOf(name); hit >= 0 && !root; hit = m.indexOf(name, hit + 1)) {
    const candidate = hit - LAYOUT.player_name;
    const pointer = Buffer.alloc(4);
    pointer.writeInt32LE(candidate);
    if (candidate > 0 && m.readInt32LE(candidate + LAYOUT.frontend_state) === 12 && m.indexOf(pointer) >= 0)
      root = candidate;
  }
  if (!root) throw Error('game root not found');
  return new Game(e, memory, root);
}

class Game {
  constructor(e, memory, root) {
    this.e = e;
    this.memory = memory;
    this.root = root;
    this.sub = root + LAYOUT.subgame;
  }

  step(ticks = 1) {
    for (let i = 0; i < ticks; ++i) this.e.snail_frame(1 / 60);
  }

  key(code) {
    this.e.snail_key(code, 1); this.step();
    this.e.snail_key(code, 0); this.step();
  }

  click(x, y) {
    this.e.snail_pointer(x, y); this.step();
    this.e.snail_button(0, 1); this.step();
    this.e.snail_button(0, 0); this.step();
  }

  state() {
    return this.memory().readInt32LE(this.root + LAYOUT.frontend_state);
  }

  // Visible front-end widgets, as the headless --trace lists them.
  widgets() {
    const m = this.memory();
    const result = [];
    for (let i = 0; i < LAYOUT.border_count; ++i) {
      const border = this.root + LAYOUT.borders + i * LAYOUT.border_size;
      const flags = m.readUInt32LE(border + LAYOUT.border_widget_flags);
      if (!flags || (flags & (HIDDEN | KILL_PENDING | TEARDOWN_ACTIVE))) continue;
      const text = border + LAYOUT.text_buffer;
      result.push({
        text: m.toString('latin1', text, m.indexOf(0, text)),
        flags,
        x: m.readFloatLE(border + LAYOUT.layout_x), y: m.readFloatLE(border + LAYOUT.layout_y),
        width: m.readFloatLE(border + LAYOUT.layout_width), height: m.readFloatLE(border + LAYOUT.layout_height),
      });
    }
    return result;
  }

  // Waits until a widget whose text starts with `text` shows on a settled
  // screen (no fade running), as the headless --trace lists them.
  find(text, ticks = 600) {
    return this.until(() => this.memory().readInt32LE(this.root + LAYOUT.fade_state) === 0
      && this.widgets().find(w => w.text.startsWith(text)), ticks);
  }

  // Steps until `test` returns something truthy, and returns it.
  until(test, ticks = 600) {
    for (let i = 0; i < ticks; ++i) {
      const result = test();
      if (result) return result;
      this.step();
    }
    throw Error(`timed out; showing ${JSON.stringify(this.widgets().map(w => w.text))}`);
  }

  press(text) {
    const widget = this.find(text);
    this.click(Math.round(widget.x + widget.width / 2), Math.round(widget.y + widget.height / 2));
    return widget;
  }

  // Past the intro to the main menu.
  mainMenu() {
    this.step(600);
    this.key(ESCAPE);
    this.find('New Game');
  }

  // A row of a high-score bank (LAYOUT.hs_postal_records, survival_records or
  // time_trial_records).
  record(bank, row) {
    return this.sub + LAYOUT.sub_high_score + bank + row * LAYOUT.solution_size;
  }

  // Each row's score, null where the row is inactive.
  scores(bank, rows = 11) {
    const m = this.memory();
    return Array.from({length: rows}, (_, row) => {
      const record = this.record(bank, row);
      return m.readInt32LE(record + LAYOUT.solution_active) === 1
        ? m.readInt32LE(record + LAYOUT.solution_score) : null;
    });
  }

  seed(bank, scores) {
    const m = this.memory();
    scores.forEach((score, row) => {
      const record = this.record(bank, row);
      m.writeInt32LE(score === null ? 0 : 1, record + LAYOUT.solution_active);
      m.writeInt32LE(score ?? 0, record + LAYOUT.solution_score);
    });
  }
}
