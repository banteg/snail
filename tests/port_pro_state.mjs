// Leave a Pro game and play High Scores replays the ways Android allows, and
// report what each screen holds: the records under the Postal title, the course
// each replay loads and the saved Pro progress.
import { readFileSync } from 'node:fs';
import { LAYOUT, openMobileGame } from './port_mobile_runtime.mjs';

const { e, root, sub, memory, step, click } = await openMobileGame(process.argv[2]);
const state = () => memory().readInt32LE(root + LAYOUT.frontend_state);
const text = (address) => { const m = memory(); return m.toString('latin1', address, m.indexOf(0, address)); };
const postalName = () => text(sub + LAYOUT.postal_records + LAYOUT.record_name);
const proProgress = () => { const b = readFileSync('SnailMailPro.cfg'); return [b.readInt32LE(0), b.readInt32LE(4)]; };
const wait = (what, done, escape = false) => {
  for (let i = 0; i < 100 && !done(); ++i) {
    if (escape) { e.snail_key(1, 1); e.snail_frame(1 / 60); e.snail_key(1, 0); }
    step(1);
  }
  if (!done()) throw Error(`never reached ${what}`);
};
const highScores = () => { click(345, 180); wait('High Scores', () => state() === 19); };
const toggle = () => click(420, 400);
// A level completes as update_subgoldy ends it; destroy_subgame sends a replay
// back to High Scores.
const endLevel = (saved) => {
  const m = memory();
  m.writeInt32LE(2, sub + LAYOUT.subgame_rebuild_selector);
  if (saved !== undefined) m.writeInt32LE(saved, root + LAYOUT.saved_frontend_state);
  m.writeInt32LE(26, root + LAYOUT.frontend_state);
};
// Press a row's Replay button, which the PC hides and Android shows.
const replay = (row) => {
  const m = memory();
  const widget = m.readUInt32LE(root + LAYOUT.high_score + LAYOUT.replay_row_widgets + 4 * row);
  m.writeUInt32LE(m.readUInt32LE(widget + LAYOUT.widget_flags) | LAYOUT.primary_action_triggered, widget + LAYOUT.widget_flags);
  wait('the replay', () => state() === 11 && memory().readInt32LE(sub + LAYOUT.subgame_state) === 2);
  return text(sub + LAYOUT.level_definition + LAYOUT.level_display_name);
};

const report = {};
// The last Pro level ends without a new high score: thanks, credits, main menu.
endLevel(29);
wait('the main menu', () => state() === 5, true);
highScores();
report.afterCredits = postalName();
toggle();
toggle();
report.proView = postalName();
report.proReplay = replay(0);
report.proProgressDuringReplay = proProgress();
endLevel();
wait('High Scores', () => state() === 19);
report.afterProReplay = postalName();
click(210, 400);  // Back
wait('the main menu', () => state() === 5);
highScores();
// High Scores reopens on the Pro table it last showed, as on Android; the
// toggle leads on to Postal.
toggle();
report.afterBack = postalName();
toggle();
toggle();
replay(0);
endLevel();
wait('High Scores', () => state() === 19);
toggle();
report.postalView = postalName();
report.postalReplay = replay(0);
report.proProgress = proProgress();
console.log(JSON.stringify(report));
