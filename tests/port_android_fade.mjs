// A centered run on Time Trial I hits the first slug without firing.
import {LAYOUT as L, openGame} from './port_frontend.mjs';

const [wasm, particles, cadence] = process.argv.slice(2);
const game = await openGame(wasm, true, 'Probe');
game.mainMenu();
game.press('New Game');
game.press('Time Trial');
game.press('Play');
game.find('Click to Start');
game.e.snail_pointer(320, 240);
game.e.snail_button(0, 1);
game.step(1);
game.e.snail_button(0, 0);

const forwardVelocity = game.sub + L.player + L.player_velocity + 8;
game.until(() => game.memory().readFloatLE(forwardVelocity) < -0.05, 1000);
// Android's 80 fireworks take three primary draws each. Skip the same
// number on the effects-off run and compare the next three table values.
if (particles === 'off')
  for (let i = 0; i < 80 * 3; ++i) game.e.snail_rand();
const draws = Array.from({length: 3}, () => game.e.snail_rand());

const fade = game.root + L.fade_state;
const transitions = [];
let previous = 0;
for (let tick = 1; tick <= 285; ++tick) {
  // One browser frame simulates ticks 259-261. Only the final tick
  // presents, so the screen must stay in the outgoing fade until then.
  if (cadence === 'catch-up' && tick === 259) {
    game.e.snail_frame(3 / 60);
    tick += 2;
  } else {
    game.step();
  }
  const state = game.memory().readInt32LE(fade);
  if (state !== previous) transitions.push([tick, state]);
  previous = state;
}
console.log(JSON.stringify({draws, transitions}));
