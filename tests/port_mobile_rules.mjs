// Drive the probe course (tests/test_port_mobile_rules.py) through to its
// delivery tally in one profile, and report what the snail scored and saw.
// Usage: node port_mobile_rules.mjs WASM ULTIMATE(0|1) watch|skip
import { LAYOUT, openMobileGame } from './port_mobile_runtime.mjs';

const [wasm, ultimate, tally] = process.argv.slice(2);
const game = await openMobileGame(wasm, {}, 6);
const { e, sub } = game;
e.snail_set_profile(Number(ultimate));
const player = sub + LAYOUT.player;
const completion = sub + LAYOUT.completion;
const i32 = (address) => game.memory().readInt32LE(address);
const timer = () => game.memory().readFloatLE(player + LAYOUT.handoff_timer);
const state = () => ({
  z: game.memory().readFloatLE(player + LAYOUT.position + 8),
  score: i32(player + LAYOUT.total_score),
  buckets: Array.from({ length: LAYOUT.score_bucket_count }, (_, i) => i32(player + LAYOUT.score_buckets + 4 * i)),
  lives: i32(player + LAYOUT.lives),
  ringCounter: i32(player + LAYOUT.ring_counter),
  cursor: i32(sub + LAYOUT.replay_update_cursor),
  samples: i32(sub + LAYOUT.replay_sample_count),
  tips: Array.from({ length: LAYOUT.tip_slots }, (_, i) => i32(game.root + LAYOUT.tips + i * LAYOUT.tip)).filter(Boolean).length,
});
const click = () => { e.snail_button(0, 1); e.snail_frame(1 / 60); e.snail_button(0, 0); };

const report = { rings: 0, messages: [] };
let message = i32(player + LAYOUT.row_event), previous = 0, clicked = false;
for (let frame = 0; frame < 20000 && !report.after; ++frame) {
  // The authored rings sit beside the snail's line; bring each active one
  // (state 1, kind 5) to it.
  for (let i = 0; i < LAYOUT.ring_slots; ++i) {
    const ring = sub + LAYOUT.rings + i * LAYOUT.ring;
    if (i32(ring + LAYOUT.ring_state) !== 1 || i32(ring + LAYOUT.ring_kind) !== 5) continue;
    const memory = game.memory();
    memory.writeUInt8(0, ring + LAYOUT.ring_oscillate_x);
    for (let k = 0; k < 3; ++k)
      memory.writeFloatLE(memory.readFloatLE(player + LAYOUT.camera_target + 4 * k), ring + LAYOUT.ring_position + 4 * k);
    ++report.rings;
  }
  e.snail_frame(1 / 60);
  if (i32(player + LAYOUT.row_event) !== message) {
    message = i32(player + LAYOUT.row_event);
    // Segments without a message (the rings, any Padding) raise row events
    // too; keep those whose segment carries one.
    const slot = sub + LAYOUT.level_definition + LAYOUT.segment_slots + (message - 1) * LAYOUT.segment_slot;
    if (message > 0 && game.memory().readUInt8(slot + LAYOUT.segment_message) !== 0) report.messages.push(state());
  }
  const current = i32(completion + LAYOUT.completion_state);
  if (current && !previous) {
    report.before = state();
    if (tally === 'skip') {
      // Three parcels collected: the tally owes 300 points before its bonus.
      const memory = game.memory();
      memory.writeInt32LE(3, completion + LAYOUT.completion_target);
      const token = completion + LAYOUT.completion_display_token;
      memory.writeInt32LE(memory.readInt32LE(token) + 300, token);
    }
  }
  // A click 2 s into the hand-off skips the tally while parcels still fly.
  if (tally === 'skip' && !clicked && (current === 1 || current === 2) && timer() > 2.5) {
    report.skipped = state();
    click();
    clicked = true;
  }
  // The summary waits for a click; hold it for two seconds first.
  if (tally === 'watch' && !clicked && current === 4) {
    report.summary = state();
    for (let i = 0; i < 120; ++i) e.snail_frame(1 / 60);
    report.held = state();
    click();
    clicked = true;
  }
  if (!current && previous) report.after = state();
  previous = current;
}
console.log(JSON.stringify(report));
