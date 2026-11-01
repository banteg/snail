// Inspect the requests consumed by the track scanner after normal course construction.
import {LAYOUT as L, openGame} from './port_frontend.mjs';

const [wasm, profile, scenario] = process.argv.slice(2);
const game = await openGame(wasm, profile === 'ultimate', 'Probe');
game.mainMenu();
game.press('New Game');
const challenge = scenario === 'fresh' || scenario === 'stale';
game.press(challenge ? 'Challenge Mode' : 'Postal Mode');
const m = game.memory();
const cells = game.sub + L.runtime_cells;
if (scenario === 'stale') {
  // The previous track can leave a trampoline at -3 in any of these slots.
  for (let i = 0; i < L.row_capacity * L.lanes; ++i)
    m.writeFloatLE(-3, cells + i * L.cell + L.cell_position + 4);
}
if (scenario === 'loopsville') {
  game.find('Deliver');
  game.step(2);  // both original RNGs selected a short pattern on this build tick
}
game.press(challenge ? 'Play' : 'Deliver');
game.find('Click to Start');

const level = game.sub + L.level_definition;
const finish = m.readInt32LE(game.sub + L.completion_row_start);
const parcels = [];
for (let row = 0; row < finish; ++row) {
  const entry = game.sub + L.runtime_rows + row * L.runtime_row;
  const flags = m.readUInt32LE(entry + L.row_flags);
  if (!(flags & L.parcel_requested)) continue;
  // Only flat digit markers have neither an authored nor a projected height.
  if (challenge && (flags & (L.parcel_local | L.attachment_mask))) continue;
  if (scenario === 'loopsville') {
    parcels.push(row);
    continue;
  }
  const pos = entry + L.parcel_spawn_position;
  const x = m.readFloatLE(pos), y = m.readFloatLE(pos + 4), z = m.readFloatLE(pos + 8);
  const lane = Math.floor(x + L.lanes / 2);
  const cell = cells + (row * L.lanes + lane) * L.cell;
  parcels.push({row, x, y, z, road: m.readFloatLE(cell + L.cell_position + 4)});
}
console.log(JSON.stringify({
  parcels, seed: m.readInt32LE(game.sub + L.runtime_build_seed), count: m.readInt32LE(level + L.parcel_count), quota: m.readInt32LE(level + L.parcel_quota),
}));
