// Open the stock route and observe the rows the profile actually built.
import {LAYOUT as L, openGame} from './port_frontend.mjs';

const [wasm, profile, scenario] = process.argv.slice(2);
const game = await openGame(wasm, profile === 'ultimate', 'Probe');
game.mainMenu();
game.press('New Game');
if (scenario === 'tutorial') {
  game.press('Tutorial');
} else {
  game.press('Postal Mode');
  game.press('Deliver');
}
game.press('Click to Start');
game.step(30);

const m = game.memory(), sub = game.sub, player = sub + L.player;
const level = sub + L.level_definition;
const segments = [];
for (let i = 0; i < m.readInt32LE(level); ++i) {
  const slot = level + L.segment_slots + i * L.segment_slot;
  const name = m.readUInt32LE(slot + L.segment_source_name);
  segments.push({
    name: m.toString('ascii', name, m.indexOf(0, name)).toLowerCase(),
    start: m.readInt32LE(slot), rows: m.readInt32LE(slot + L.segment_row_count),
  });
}
const listed = segments.filter(s => s.name !== 'padding.txt');
const result = {first: listed[0].name, count: listed.length, garbage: m.readFloatLE(sub + L.garbage_frequency)};
const flags = row => m.readUInt32LE(sub + L.runtime_rows + row * L.runtime_row + L.row_flags);
if (scenario === 'tutorial') {
  const row = listed.find(s => s.name === 'tutorial 11.txt').start + 27;
  // Let the real track update scan the authored R marker at the leading edge.
  m.writeInt32LE(row, sub + L.runtime_row_scan_end);
  m.writeUInt8(0, player + L.follow_active);
  m.writeFloatLE(5, player + L.player_position + 4);
  m.writeFloatLE(row - 36, player + L.player_z);
  m.writeFloatLE(row - 44, player + L.active_window_min_z);
  game.until(() => m.readInt32LE(sub + L.runtime_row_scan_end) > row, 10);
  result.explosive = Array.from({length: L.ring_slots}, (_, i) => sub + L.rings + i * L.ring)
    .some(ring => m.readInt32LE(ring + L.ring_state) === 1 && m.readInt32LE(ring + L.ring_kind) === 6
      && m.readFloatLE(ring + L.ring_position + 8) === row + 0.5);
} else if (scenario === 'supertramp') {
  const segment = listed.find(s => s.name === 'supertramp2.txt');
  result.noFall = Array.from({length: segment.rows}, (_, i) => flags(segment.start + i))
    .filter(rowFlags => rowFlags & 0x100).length;
  // Coast through an empty, marked row after leaving a path.
  m.writeFloatLE(2, player + L.player_position);
  m.writeFloatLE(5, player + L.player_position + 4);
  m.writeFloatLE(segment.start + 42.1, player + L.player_z);
  m.writeUInt8(1, player + L.player_exit_pending);
  m.writeUInt8(0, player + L.follow_active);
  m.writeFloatLE(0, player + L.player_velocity);
  m.writeFloatLE(-0.2, player + L.player_velocity + 4);
  m.writeFloatLE(0.35, player + L.player_velocity + 8);
  game.step();
  result.speed = m.readFloatLE(player + L.player_velocity + 8);
}
console.log(JSON.stringify(result));
