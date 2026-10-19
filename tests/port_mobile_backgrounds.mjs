import { LAYOUT, openMobileGame } from './port_mobile_runtime.mjs';

const expected = JSON.parse(process.argv[3]);
let exports, recording = false, textureId, vertices;
const ids = {}, sizes = {};
const game = await openMobileGame(process.argv[2], {
  ready(e) { exports = e; },
  texture_create(id, width, height, pixels) {
    const memory = Buffer.from(exports.memory.buffer);
    const signature = memory.subarray(pixels, pixels + 64).toString('hex');
    for (const [name, reference] of Object.entries(expected))
      if (reference === signature) { ids[name] = id; sizes[name] = [width, height]; }
  },
  draw(primitive, address, count, state) {
    if (!recording) return;
    const memory = Buffer.from(exports.memory.buffer);
    if (memory.readInt32LE(state) !== textureId) return;
    for (let i = 0; i < count; ++i) {
      const vertex = address + i * 32;
      vertices.push({ x: memory.readFloatLE(vertex), u: memory.readFloatLE(vertex + 20), v: memory.readFloatLE(vertex + 24) });
    }
  },
});
const names = {};
for (let slot = 0; slot < 1000; ++slot) {
  const address = exports.snail_sprite_texture_name(slot), memory = game.memory();
  const name = memory.toString('utf8', address, memory.indexOf(0, address));
  for (const key of Object.keys(expected))
    if (name.toLowerCase() === `backgrounds/${key}.tga`.toLowerCase()) names[key] = slot;
}
const results = [];
for (const [name, ultimate, flip] of [
  ['SpacePro', 1, 0], ['SpacePro', 1, 1],
  ['SpacePro2', 1, 0], ['SpacePro2', 1, 1],
  ['SpacePurple', 1, 0], ['SpacePro', 0, 0],
]) {
  if (!(name in names) || !(name in ids)) throw Error(`texture not found: ${name}`);
  const backdrop = game.root + LAYOUT.backdrop, memory = game.memory();
  exports.snail_set_profile(ultimate);
  memory.writeInt32LE(names[name], backdrop + 0x3c);
  memory[backdrop + 0x38] = 0;
  memory[backdrop + 0x4c] = 0;
  memory[backdrop + 0x55] = flip;
  memory.writeInt32LE(1, backdrop + 0x658);
  vertices = []; textureId = ids[name]; recording = true;
  exports.snail_frame(1 / 60);
  recording = false;
  if (!vertices.length) throw Error(`no draws for ${name}`);
  const xs = vertices.map(v => v.x), us = vertices.map(v => v.u), vs = vertices.map(v => v.v);
  const left = Math.min(...xs), right = Math.max(...xs);
  results.push({ name, ultimate, flip, size: sizes[name], count: vertices.length,
    minU: Math.min(...us), maxU: Math.max(...us), minV: Math.min(...vs), maxV: Math.max(...vs),
    leftU: vertices.find(v => v.x === left).u, rightU: vertices.find(v => v.x === right).u });
}
console.log(JSON.stringify(results));
