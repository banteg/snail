// Run real gameplay frames for live input and selected replay samples.
import {LAYOUT as L, openGame} from './port_frontend.mjs';

const [wasm, profile] = process.argv.slice(2);
const game = await openGame(wasm, profile === 'ultimate', 'Probe');
game.mainMenu();
game.press('New Game');
game.press('Postal Mode');
game.press('Deliver');
game.press('Click to Start');
game.step(30);
const m = game.memory(), sub = game.sub, player = sub + L.player;
m.writeUInt32LE(m.readUInt32LE(sub + L.runtime_flags) | L.enable_shooting, sub + L.runtime_flags);

const cursor = () => m.readInt32LE(sub + L.replay_update_cursor);
const flagsAt = (record, tick) => record + L.solution_first_flags + L.replay_sample_size * tick;
const shots = () => Array.from({length: 12}, (_, i) =>
  m.readInt32LE(player + L.golb_shots + i * L.golb_size + L.golb_state) !== 0);
function fired() {
  const prev = shots();
  game.step();
  return shots().some((active, i) => active && !prev[i]);
}

const live = [];
const recording = sub + L.replay_sample_count - L.solution_sample_count;
m.writeFloatLE(0, player + L.shoot_cooldown);
game.e.snail_button(0, 1);
for (let frame = 0; frame < 28; ++frame) {
  const tick = cursor();
  const shot = fired();
  live.push({flags: m.readUInt16LE(flagsAt(recording, tick)), shot});
}
game.e.snail_button(0, 0);
game.step();

// Stage a selected record in the otherwise unused last Postal score slot.
const replay = game.record(L.hs_postal_records, 10);
m.writeUInt32LE(replay, sub + L.selected_replay);
m[sub + L.replay_active] = 1;
function playback(flags, cooldown = 0, inRange = true) {
  const tick = cursor();
  m.writeUInt16LE(flags, flagsAt(replay, tick));
  m.writeInt32LE(tick + (inRange ? 1 : 0), replay + L.solution_sample_count);
  m.writeFloatLE(cooldown, player + L.shoot_cooldown);
  return fired();
}
const played = [playback(0x05), playback(0x45), playback(0x44, 0.5), playback(0x45, 0, false)];
console.log(JSON.stringify({live, played}));
