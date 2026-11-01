// Probe the path built at startup and enter Challenge through its normal Play button.
import {LAYOUT, openGame} from './port_frontend.mjs';

const [, , wasm, profile] = process.argv;
const game = await openGame(wasm, profile === 'ultimate', 'Probe');
const slalomSlot = 22;
const path = game.sub + LAYOUT.paths + 2 * slalomSlot * LAYOUT.path;
const samples = game.memory().readUInt32LE(path + LAYOUT.path_primary_samples);
const slalomCenter = game.memory().readFloatLE(samples + 19 * LAYOUT.sample + LAYOUT.sample_center_x);

game.mainMenu();
game.press('New Game');
game.press('Challenge Mode');
game.press('Play');
// Isolate the build from how many draws the menu and its fade consume.
// The second draw in the build tick selects the seed, RandTable[1748] = 318.
game.until(() => {
  if (game.memory().readInt32LE(game.sub + LAYOUT.completion_row_start)) return true;
  game.e.snail_rand_seed(1746);
});
game.find('Click to Start');
const finishRow = game.memory().readInt32LE(game.sub + LAYOUT.completion_row_start);
const seed = game.memory().readInt32LE(game.sub + LAYOUT.runtime_build_seed);
console.log(JSON.stringify({seed, finishRow, slalomCenter}));
