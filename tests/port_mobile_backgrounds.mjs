// Capture the vertices, UVs and secondary RNG from a live Pro 1 game.
import { LAYOUT, openMobileGame } from './port_mobile_runtime.mjs';

const expected = JSON.parse(process.argv[3]);
let exports, textureId, vertices = [];
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
    const memory = gameMemory();
    if (memory.readInt32LE(state) !== textureId) return;
    for (let i = 0; i < count; ++i) {
      const p = address + i * 32;
      vertices.push([p, p + 4, p + 20, p + 24].map(offset => memory.readFloatLE(offset)));
    }
  },
});
function gameMemory() { return Buffer.from(exports.memory.buffer); }
const names = {};
for (let slot = 0; slot < 1000; ++slot) {
  const address = exports.snail_sprite_texture_name(slot), memory = game.memory();
  const name = memory.toString('utf8', address, memory.indexOf(0, address));
  for (const key of Object.keys(expected))
    if (name.toLowerCase() === `backgrounds/${key}.tga`.toLowerCase()) names[key] = slot;
}

// Original image globals retain their positions relative to RandTable.bin.
const prefix = Buffer.alloc(16);
[41, 18467, 6334, 26500].forEach((value, i) => prefix.writeInt32LE(value, i * 4));
let table = game.memory().indexOf(prefix);
while (table >= 0 && game.memory().readUInt32LE(table + 0x4f7458 - 0x787f8c + 0xbb98) !== 640)
  table = game.memory().indexOf(prefix, table + 1);
if (table < 0) throw Error('RNG table and display mode not found');
const rng = table + 0x77ff3c - 0x787f8c;
const width = table + 0x4f7458 - 0x787f8c + 0xbb98;
if (game.memory().readUInt32LE(width) !== 640) throw Error('expected a 640px render device');

const backdrop = game.root + LAYOUT.backdrop;
const tick = () => exports.snail_frame(1/60);
const frame = Buffer.from(game.memory());
function probe(name, ultimate, screenWidth, flip, change) {
  const m = game.memory();
  m.set(frame);
  exports.snail_set_profile(ultimate);
  m.writeInt32LE(screenWidth, width);
  m.writeInt32LE(names[name], backdrop + 0x3c);
  m.writeInt32LE(names[name], backdrop + 0x40);
  m[backdrop + 0x38] = 0;
  m[backdrop + 0x39] = 0;
  m[backdrop + 0x4c] = change;
  m.writeFloatLE(10, backdrop + 0x50);
  m[backdrop + 0x54] = flip;
  m[backdrop + 0x55] = flip;
  m.writeInt32LE(1, backdrop + 0x658);
  m.writeFloatLE(0.05, backdrop + 0x6c8);
  m.writeInt32LE(123, rng);
  vertices = []; textureId = ids[name];
  tick();
  if (!vertices.length) throw Error(`no draws for ${name}`);
  const xs = [...new Set(vertices.map(v => v[0]))].sort((a,b) => a-b);
  const ys = [...new Set(vertices.map(v => v[1]))].sort((a,b) => a-b);
  const center = vertices.find(v => v[0] === xs[xs.length >> 1] && v[1] === ys[ys.length >> 1]);
  const left = vertices.find(v => v[0] === xs[0] && v[1] === ys[ys.length-1]);
  const right = vertices.find(v => v[0] === xs.at(-1) && v[1] === ys[0]);
  return {name, ultimate, screenWidth, flip, size:sizes[name], count:vertices.length,
    xCount:xs.length, yCount:ys.length, center:center?.slice(2), left:left?.slice(2), right:right?.slice(2),
    index:game.memory().readInt32LE(rng)};
}
const results = [];
for (const width of [640, 320]) {
  for (const [name, ultimate, flip] of [
    ['SpacePro', 1, 0], ['SpacePro', 1, 1], ['SpacePro2', 1, 0], ['SpacePurple', 1, 0], ['SpacePro', 0, 0],
  ]) {
    const control = probe(name, ultimate, width, flip, 0);
    const sky = probe(name, ultimate, width, flip, 1);
    sky.seedDraws = (sky.index - control.index + 8191) % 8191;
    results.push(sky);
  }
}
// Use the live player and camera updates for both zoom sources.
function zoomTarget(worm) {
  const m = game.memory();
  m.set(frame);
  exports.snail_set_profile(1);
  const player = game.sub + LAYOUT.player, follow = player + LAYOUT.follow;
  const position = player + LAYOUT.player_position;
  m[follow] = 0;
  const z = m.readFloatLE(position + 8);
  if (worm) {
    let path = game.sub + LAYOUT.paths;
    const end = path + 63 * 2 * LAYOUT.path;
    while (path < end && m.readInt32LE(path + LAYOUT.path_kind) !== 0x18) path += LAYOUT.path;
    if (path === end) throw Error('missing WORM');
    const count = m.readInt32LE(path + LAYOUT.path_segment_count), index = count >> 1;
    const cell = game.sub + LAYOUT.runtime_cells + (Math.floor(z) * LAYOUT.lanes + 4) * LAYOUT.cell;
    m.writeFloatLE(z - count * 0.5, cell + LAYOUT.cell_position + 8);
    m[follow] = 1;
    m.writeUInt32LE(path, follow + LAYOUT.follow_template);
    m.writeUInt32LE(cell, follow + LAYOUT.follow_cell);
    m.writeInt32LE(index, follow + LAYOUT.follow_index);
    m.writeFloatLE(0, follow + LAYOUT.follow_progress);
    m.writeFloatLE(0, follow + LAYOUT.follow_vertical);
    const sample = m.readUInt32LE(path + LAYOUT.path_primary_samples) + index * LAYOUT.sample;
    m.writeFloatLE(m.readFloatLE(sample + LAYOUT.sample_center_x), position);
  }
  tick();
  return {target:game.memory().readFloatLE(backdrop + 0x6c8), z};
}
console.log(JSON.stringify({draws:results, course:zoomTarget(false), worm:zoomTarget(true)}));
