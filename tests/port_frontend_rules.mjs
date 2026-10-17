// Front-end rules each profile plays (tests/test_port_frontend_rules.py).
// Usage: node port_frontend_rules.mjs WASM SCENARIO ULTIMATE PLAYER [ARG]
import { ESCAPE, FADE_BEFORE_ACTION, LAYOUT, openGame } from './port_frontend.mjs';

const [wasm, scenario, ultimate, player, arg] = process.argv.slice(2);
const game = await openGame(wasm, ultimate === '1', player);
const memory = () => game.memory();
const SCAN = {A: 0x1e, E: 0x12, M: 0x32, N: 0x31, O: 0x18, T: 0x14, U: 0x16, W: 0x11};
const TOGGLES = ['Postal Scores', 'Challenge Scores', 'Pro Scores'];

// From the main menu into the galaxy, or the setup, of a New Game mode.
function newGame(mode) {
  game.press('New Game');
  game.press(mode);
  return game.find(mode === 'Postal Mode' || mode === 'Pro-Challenge' ? 'Deliver' : 'Play');
}

function startRun(mode) {
  game.press(newGame(mode).text);
  game.press('Click to Start');
  game.step(60);
}

// Pause > End Game > Yes, with the run scoring `score`; returns the front-end
// state it settles in.
function quitRun(score) {
  memory().writeInt32LE(score, game.sub + LAYOUT.sub_total_score);
  game.key(ESCAPE);
  game.press('End Game');
  game.press('Yes');
  game.step(120);
  return game.state();
}

function title() {
  return game.until(() => game.widgets().find(w => w.text.endsWith(' High Scores'))).text;
}

const scenarios = {
  // NEWTON turns off score records and AUTUMN falling, typed anywhere.
  cheats() {
    game.mainMenu();
    for (const letter of 'NEWTONAUTUMN') game.key(SCAN[letter]);
    startRun('Postal Mode');
    return {state: quitRun(4321)};
  },

  // Ending a run of mode `arg` from the pause menu.
  quit() {
    game.mainMenu();
    startRun(arg);
    const state = quitRun(4321);
    return {state, survival: game.scores(LAYOUT.survival_records)};
  },

  // Cancelling the name for a new score in the `arg` galaxy, then reading that
  // galaxy's table back.
  cancel() {
    game.mainMenu();
    newGame(arg);
    // Pro-Challenge has swapped its own table into postal_records.
    game.seed(LAYOUT.hs_postal_records, [30000, 20000, 10000, ...Array(8).fill(null)]);
    game.seed(LAYOUT.survival_records, [...Array(10).keys()].map(row => 9000 - 100 * row).concat([null]));
    game.press('Deliver');
    game.press('Click to Start');
    game.step(60);
    const state = quitRun(25000);
    game.press('Cancel');
    // Back on the New Game menu.
    game.press(arg);
    game.find('Deliver');
    game.e.snail_save();
    return {state, postal: game.scores(LAYOUT.hs_postal_records)};
  },

  // Entering the `arg` galaxy, then saving.
  galaxy() {
    game.mainMenu();
    newGame(arg);
    game.e.snail_save();
    return {};
  },

  // High Scores from the main menu, toggled twice and left, then reopened.
  scores() {
    game.mainMenu();
    game.seed(LAYOUT.survival_records, [3000, 2000, 1000, ...Array(8).fill(null)]);
    game.press('High Scores');
    const titles = [title()];
    let replays;
    for (let i = 0; i < 2; ++i) {
      game.press(game.widgets().find(w => TOGGLES.includes(w.text)).text);
      game.until(() => title() !== titles.at(-1));
      titles.push(title());
      if (titles.at(-1) === 'Challenge High Scores')
        replays = game.widgets().filter(w => w.text === 'Replay').map(w => (w.flags & FADE_BEFORE_ACTION) !== 0);
    }
    game.press('Back');
    game.press('High Scores');
    titles.push(title());
    game.e.snail_save();
    return {titles, replays};
  },

  // A Time Trial finish, with the route's best time `arg` (0 for none) and a
  // bonus left over from an earlier postal finish.
  'time-trial'() {
    game.mainMenu();
    startRun('Time Trial');
    const m = memory();
    const route = m.readInt32LE(game.sub + LAYOUT.level_mode_arg);
    const record = game.record(LAYOUT.time_trial_records, route);
    m.writeFloatLE(Number(arg), record + LAYOUT.solution_seconds);
    m.writeInt32LE(50000, game.sub + LAYOUT.bonus_score);
    // The finish line, just ahead.
    m.writeInt32LE(Math.ceil(m.readFloatLE(game.sub + LAYOUT.sub_player_z)) + 1, game.sub + LAYOUT.completion_row_start);
    const shown = new Set();
    game.until(() => {
      for (const widget of game.widgets()) shown.add(widget.text);
      return game.widgets().some(w => w.text === 'Play');
    }, 1200);
    const saved = memory();
    return {
      shown: [...shown],
      seconds: saved.readFloatLE(record + LAYOUT.solution_seconds),
      score: saved.readInt32LE(record + LAYOUT.solution_score),
    };
  },
};

console.log(JSON.stringify(scenarios[scenario]()));
