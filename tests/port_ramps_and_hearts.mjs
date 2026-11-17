// The probe course has a '[' at lane 0, ']' at lane 3 and a heart at lane 4.
import { openGame, LAYOUT as L } from './port_frontend.mjs';

const [wasm, profile] = process.argv.slice(2);
const A = JSON.parse(process.env.RAMP_HEART_LAYOUT);
const game = await openGame(wasm, Number(profile), 'Probe');
game.mainMenu();
game.press('New Game');
game.press('Postal Mode');
game.press('Deliver');
game.press('Click to Start');

const mem = game.memory();
const sub = game.sub, player = sub + L.player, position = player + L.position;
const tile = (row, lane) => mem.readUInt8(sub + L.runtime_cells + (row * L.lanes + lane) * L.cell + L.cell_tile);
function approach(x, y, z) {
  game.e.snail_pointer(320, 240);
  mem.writeFloatLE(320, player + A.anchor);
  mem.writeFloatLE(320 - x * 80, player + A.offset);
  mem.writeUInt8(0, player + L.follow_active);
  mem.writeUInt8(0, player + L.player_exit_pending);
  mem.writeFloatLE(x, position);
  mem.writeFloatLE(y, position + 4);
  mem.writeFloatLE(z, position + 8);
  mem.writeFloatLE(0, player + L.player_velocity);
  mem.writeFloatLE(0, player + L.player_velocity + 4);
  mem.writeFloatLE(0.2, player + L.player_velocity + 8);
}

const result = {}, ramps = {};
for (let row = 0; row < mem.readInt32LE(sub + L.completion_row_start); ++row) {
  const mirrored = Boolean(mem.readUInt32LE(sub + L.runtime_rows + row * L.runtime_row + L.row_flags) & A.mirrored);
  const lane = n => mirrored ? L.lanes - 1 - n : n;
  const side = mirrored ? 'mirrored' : 'plain';
  if (tile(row, lane(4)) === 23 && !ramps[side]) {
    ramps[side] = {row, lanes: [lane(0), lane(3)]};
  }
}

// Take one tick past a live, fully raised heart at each height. Keep the
// ground approach used by the Windows courses alongside the two airborne cases.
const slots = Array.from({length: 8}, (_, i) => sub + A.hearts + i * A.heart_size);
let last = -1;
result.heart = {};
for (const [label, y] of [['above', 1.8], ['raised', 1.19], ['ground', 0.49]]) {
  const heart = game.until(() => slots.find(h => mem.readInt32LE(h + A.heart_state) === 1
    && mem.readFloatLE(h + A.heart_position + 8) > last), 1200);
  const x = mem.readFloatLE(heart + A.heart_position);
  const z = mem.readFloatLE(heart + A.heart_position + 8);
  const base = mem.readFloatLE(heart + A.heart_position + 4);
  const sprite = mem.readUInt32LE(heart + A.heart_sprite);
  mem.writeFloatLE(0.25, heart + A.heart_phase);
  mem.writeFloatLE(base + 0.6, sprite + A.sprite_position + 4);
  approach(x, y, z - 0.2);
  mem.writeFloatLE(0.75, player + L.gauge_fill);
  game.step();
  result.heart[label] = mem.readFloatLE(player + L.gauge_fill) === 0.25;
  last = z;
}
for (const [side, {row, lanes}] of Object.entries(ramps)) {
  result[side] = lanes.map(lane => tile(row, lane));
  result[side + 'Roll'] = lanes.map(lane => {
    approach(lane - 3.5, 0.49, row + 0.1);
    mem.writeInt32LE(0, player + A.lean);
    mem.writeFloatLE(0, player + A.amplitude);
    game.step();
    return mem.readFloatLE(player + A.amplitude);
  });
}
console.log(JSON.stringify(result));
