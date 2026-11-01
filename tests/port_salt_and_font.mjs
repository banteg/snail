// Inspect the mesh and text vertices submitted to the normal browser presenter.
import {createHash} from 'node:crypto';
import {LAYOUT as L, openGame} from './port_frontend.mjs';

const [wasm, profile] = process.argv.slice(2);
const ultimate = profile === 'ultimate';
let memory, saltTexture, fontTexture, collecting = false;
const saltAlphas = [], glyphStarts = [];
const game = await openGame(wasm, ultimate, 'Probe', {
  ready(e) { memory = () => Buffer.from(e.memory.buffer); },
  texture_create(id, width, height, pixels) {
    if (!((width === 128 && height === 128) || (width === 1024 && height === 64))) return;
    const rgba = memory().subarray(pixels, pixels + width * height * 4);
    const hash = createHash('sha1').update(rgba).digest('hex');
    // Decoded stock X/SALT.TGA and the second page of FONT-MENU-HOVER.
    if (hash === '92318cc6f6cc5926fcb8a9298fca03300fd04eb5') saltTexture = id;
    if (hash === 'c94ffd7a4d1d629e5a7ef4f77ac35e6543511c95') fontTexture = id;
  },
  draw(primitive, vertices, count, state) {
    if (!collecting) return;
    const m = memory(), texture = m.readInt32LE(state);
    if (texture === saltTexture) saltAlphas.push(m.readUInt8(vertices + 19));
    if (texture === fontTexture && count === 6) {
      // FontLoad samples half a texel inside the glyph's left edge.
      glyphStarts.push(m.readFloatLE(vertices + 20) * 1024 - 0.5);
    }
  },
});
if (!saltTexture || !fontTexture) throw Error('target textures missing');

game.mainMenu();
const m = memory();
const label = game.find('New Game').text;
let button;
for (let i = 0; i < L.border_count; ++i) {
  const text = game.root + L.borders + i * L.border_size + L.text_buffer;
  if (m.toString('latin1', text, m.indexOf(0, text)) === label) {
    button = text;
    break;
  }
}
if (!button) throw Error('menu label missing');

function glyphCounts(text) {
  m.write(text + '\0', button, 'latin1');
  glyphStarts.length = 0;
  collecting = true;
  game.step();
  collecting = false;
  // Atlas slots 64 (double quote), 84 (apostrophe) and 53 (space).
  return [261, 638, 4].map(x => glyphStarts.filter(left => left === x).length);
}
const baseline = glyphCounts('   ');
const glyphs = glyphCounts('"\' ').map((n, i) => n - baseline[i]);
m.write(label + '\0', button, 'latin1');

game.press('New Game');
game.press('Postal Mode');
game.press('Deliver');
game.press('Click to Start');
game.step(15);
// Place two salt crystals on the same row of Postal I. Both draw the same mesh.
const flags = game.sub + L.runtime_flags;
m.writeUInt32LE(m.readUInt32LE(flags) & ~0x10000, flags);
const row = Math.max(m.readInt32LE(game.sub + L.runtime_row_scan_end), m.readInt32LE(game.sub + L.first_block_rows)) + 3;
const cell = game.sub + L.runtime_cells + (row * L.lanes + 1) * L.cell;
m.writeUInt8(0x22, cell + L.cell_tile);
m.writeUInt8(0x22, cell + L.cell + L.cell_tile);
const salt = game.sub + L.salt_slots;
const playerZ = game.sub + L.sub_player_z;
const sample = () => ({
  distance: m.readFloatLE(salt + L.salt_z) - m.readFloatLE(playerZ),
  tint: m.readFloatLE(salt + L.salt_alpha),
  drawn: [...new Set(saltAlphas)],
});
collecting = true;
game.until(() => {
  if (m.readInt32LE(salt + L.salt_state) === 1) return true;
  saltAlphas.length = 0;
}, 300);
const spawn = sample();
const samples = [];
for (const distance of [52, 24, -1]) {
  for (const slot of [salt, salt + L.salt_size])
    m.writeFloatLE(m.readFloatLE(playerZ) + distance, slot + L.salt_z);
  saltAlphas.length = 0;
  game.step();
  samples.push(sample());
}
// Draw one near crystal and one distant crystal in the same frame.
m.writeFloatLE(m.readFloatLE(playerZ) + 52, salt + L.salt_z);
saltAlphas.length = 0;
game.step();
const pair = [...new Set(saltAlphas)].sort((a, b) => a - b);
console.log(JSON.stringify({glyphs, spawn, samples, pair}));
