// Drive the browser reactor to a galaxy map, count the PC galaxy sprites it
// draws on screen, then open the thanks-for-playing screen that follows the
// galaxy's last route and report each of its texts.
// Usage: node port_frontend_content.mjs WASM PROFILE MENU_Y FIRST_GALAXY SPRITE_HASHES
import { createHash } from 'node:crypto';
import { readFile } from 'node:fs/promises';
import { WASI } from 'node:wasi';

// Field offsets in the port's layout, from the test (tests/conftest.py).
const LAYOUT = JSON.parse(process.env.SNAIL_LAYOUT);
const [wasm, profile, menuY, firstGalaxy, spriteHashes] = process.argv.slice(2);
const spriteHashSet = new Set(JSON.parse(spriteHashes));
const galaxyTextures = new Set();
let e, recording = false, visible = 0, hidden = 0;

const presenter = {
  texture_create(id, width, height, pixels) {
    const rgba = Buffer.from(e.memory.buffer, pixels, width * height * 4);
    if (spriteHashSet.has(createHash('sha1').update(rgba).digest('hex'))) galaxyTextures.add(id);
  },
  draw(primitive, address, count, state) {
    if (!recording) return;
    const memory = Buffer.from(e.memory.buffer);
    if (!galaxyTextures.has(memory.readInt32LE(state))) return;
    for (let triangle = 0; triangle + 3 <= count; triangle += 3) {
      const xs = [], ys = [];
      for (let i = triangle; i < triangle + 3; ++i) {
        const vertex = address + i * 32, w = memory.readFloatLE(vertex + 12);
        xs.push(memory.readFloatLE(vertex) / w);
        ys.push(memory.readFloatLE(vertex + 4) / w);
      }
      const onScreen = Math.max(...xs) > -1 && Math.min(...xs) < 1 && Math.max(...ys) > -1 && Math.min(...ys) < 1;
      if (onScreen) ++visible; else ++hidden;
    }
  },
};

const wasi = new WASI({version: 'preview1', args: [], env: {...process.env, PWD: process.cwd()}, preopens: {'/': process.cwd()}});
const module = await WebAssembly.compile(await readFile(wasm));
const imports = wasi.getImportObject();
imports.snail = Object.fromEntries(WebAssembly.Module.imports(module)
  .filter(i => i.module === 'snail').map(i => [i.name, presenter[i.name] ?? (() => 0)]));
const instance = await WebAssembly.instantiate(module, imports);
wasi.initialize(instance);
e = instance.exports;
e.snail_set_profile(Number(profile));
if (!e.snail_start(0)) throw Error('game startup failed');

const step = (n = 5) => { for (let i = 0; i < n; ++i) e.snail_frame(0.4); };
const click = (x, y) => {
  e.snail_pointer(x, y); e.snail_frame(1 / 60);
  e.snail_button(0, 1); e.snail_frame(1 / 60); e.snail_button(0, 0); step();
};
step(25); e.snail_key(1, 1); e.snail_frame(1 / 60); e.snail_key(1, 0); step();
click(345, 112); click(345, Number(menuY)); step();

// The galaxy map is up (frontend state 11) with this galaxy's names.
let memory = Buffer.from(e.memory.buffer), root;
const needle = Buffer.from(`${firstGalaxy}\0`);
for (let p = memory.indexOf(needle); p >= 0; p = memory.indexOf(needle, p + 1)) {
  const candidate = p - LAYOUT.galaxy_name;
  if (candidate > 0 && memory.readInt32LE(candidate + LAYOUT.frontend_state) === 11) root = candidate;
}
if (!root) throw Error(`the ${firstGalaxy} map did not open`);
recording = true;
e.snail_frame(1 / 60);
recording = false;

// What finishing the galaxy's last route opens (update_subgoldy.cpp: state 29).
Buffer.from(e.memory.buffer).writeInt32LE(29, root + LAYOUT.frontend_state);
const texts = {};
for (let tick = 0; tick < 1200 && !('4' in texts); ++tick) {
  e.snail_frame(1 / 60);
  memory = Buffer.from(e.memory.buffer);
  const state = memory.readInt32LE(root + LAYOUT.splash_state);
  const text = memory.readUInt32LE(root + LAYOUT.splash_message) + LAYOUT.border_text;
  if (!(state in texts)) texts[state] = memory.toString('latin1', text, memory.indexOf(0, text));
}
console.log(JSON.stringify({ visible, hidden, texts }));
