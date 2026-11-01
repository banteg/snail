import assert from 'node:assert/strict';
import { LAYOUT, openGame } from './port_frontend.mjs';

const [wasm, profile, name] = process.argv.slice(2);
const ultimate = profile === '1';
const game = await openGame(wasm, ultimate, name);
const { e } = game;
game.mainMenu();
game.press('New Game');
game.press('Postal Mode');
game.press('Deliver');
game.find('Click to Start');
game.step(2);

const left = 0x4000, right = 0x8000;
const clickState = () => game.memory().readInt32LE(game.sub + LAYOUT.click_state);
function poll() {
  game.step();
  const m = game.memory();
  return [m.readInt32LE(game.root + LAYOUT.pressed), m.readInt32LE(game.root + LAYOUT.held)]
    .map(bits => bits & (left | right));
}

assert.equal(clickState(), 2);
// Losing focus discards both a queued tap and an unconsumed hold.
e.snail_button(0, 1); e.snail_button(0, 0); e.snail_button(1, 1);
e.snail_window_state(0, 0); e.snail_window_state(1, 1);
assert.deepEqual(poll(), [0, 0]);
assert.equal(clickState(), 2);

// Two left clicks during one held right click, including redundant reports.
e.snail_button(1, 1);
for (let i = 0; i < 2; ++i) {
  e.snail_button(0, 1); e.snail_button(0, 1); e.snail_button(0, 0);
}
assert.deepEqual(poll(), ultimate ? [left | right, left | right] : [right, right]);
assert.deepEqual(poll(), [0, right]);
// The click-start actor sees the game-input owner's sampled edge on its next update.
assert.equal(clickState(), ultimate ? 3 : 2);
e.snail_button(1, 0);
assert.deepEqual(poll(), ultimate ? [left, left] : [0, 0]);
assert.deepEqual(poll(), [0, 0]);
assert.deepEqual(poll(), [0, 0]);

// A second pointer holds the same logical button after the first releases.
e.snail_button(1, 1, 7); e.snail_button(1, 1, 9); e.snail_button(1, 0, 7);
assert.deepEqual(poll(), ultimate ? [right, right] : [0, 0]);
e.snail_button(1, 0, 9);
assert.deepEqual(poll(), [0, 0]);

// A cancelled gesture does not synthesize a press. If another pointer already
// completed its click, cancelling the last pointer must still deliver that click.
e.snail_button(1, 1, 7); e.snail_button(1, -1, 7);
assert.deepEqual(poll(), [0, 0]);
e.snail_button(1, 1, 7); e.snail_button(1, 1, 9);
e.snail_button(1, 0, 9); e.snail_button(1, -1, 7);
assert.deepEqual(poll(), ultimate ? [right, right] : [0, 0]);
assert.deepEqual(poll(), [0, 0]);

e.snail_button(1, 1, 7);
assert.deepEqual(poll(), [right, right]);
e.snail_window_state(0, 0); e.snail_window_state(1, 1);
e.snail_button(1, 1, 7); e.snail_button(1, 0, 7);
assert.deepEqual(poll(), [0, 0]);
assert.deepEqual(poll(), ultimate ? [right, right] : [0, 0]);
assert.deepEqual(poll(), [0, 0]);
