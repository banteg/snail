// Fire real weapons on Postal I, then position their next tick relative to four live asteroids.
import { LAYOUT as L, openGame } from './port_frontend.mjs';

const [wasm, profile] = process.argv.slice(2);
async function weapon(tier) {
  const game = await openGame(wasm, profile === '1', 'Probe');
  game.mainMenu();
  game.press('New Game');
  game.press('Postal Mode');
  game.press('Deliver');
  game.press('Click to Start');
  game.step(30);
  const m = game.memory(), player = game.sub + L.player;
  const word = at => m.readUInt32LE(at);
  function vector(at, x, y, z) {
    m.writeFloatLE(x, at); m.writeFloatLE(y, at + 4); m.writeFloatLE(z, at + 8);
  }
  function asteroids() {
    const active = [];
    for (let a = word(game.sub + L.asteroid_head); a; a = word(a + L.asteroid_next)) {
      if (word(a + L.asteroid_state) === 1) active.push(a);
    }
    return active;
  }
  const row = Math.max(word(game.sub + L.runtime_row_scan_end), word(game.sub + L.first_block_rows)) + 8;
  const cells = game.sub + L.runtime_cells + row * L.lanes * L.cell;
  for (let lane = 0; lane < 4; ++lane) m.writeUInt8(L.asteroid_tile, cells + lane * L.cell + L.cell_tile);
  m.writeInt32LE(tier, player + L.shooting_tier);
  game.until(() => asteroids().length >= 4);
  game.e.snail_button(0, 1);
  const slots = Array.from({length: 12}, (_, i) => player + L.golb_shots + i * L.golb_size);
  const shot = game.until(() => slots.find(s => word(s + L.golb_state) === 1 && word(s + L.golb_kind) === (tier === 3 ? 1 : 2)));
  game.e.snail_button(0, 0);

  const targets = asteroids();
  const z = m.readFloatLE(player + L.player_z) + 12;
  const speed = tier === 3 ? 3 : 0.8;
  m.writeUInt8(0, shot + L.shot_follow); // Start can launch the shot on an attachment.
  vector(shot + L.shot_pos, 0, 2, z);
  vector(shot + L.shot_prev, 0, 2, z);
  vector(shot + L.shot_velocity, 0, 0, speed);
  for (const a of targets) {
    vector(a + L.asteroid_pos, 20, 2, z);
    m.writeFloatLE(0.64, a + L.asteroid_radius);
  }
  const score = word(player + L.total_score);
  function sample(positions) {
    for (let i = 0; i < positions.length; ++i) {
      const [x, dz] = positions[i];
      vector(targets[i] + L.asteroid_pos, x, 2, z + dz);
    }
    game.step();
    return {
      hits: targets.slice(0, 4).map(a => word(a + L.asteroid_state) !== 1),
      score: word(player + L.total_score) - score,
      live: word(shot + L.golb_state) === 1,
    };
  }
  if (tier === 3) return {laser: sample([[0, 1.5], [0, 2.8], [1.3, 1.5], [0, 4.3]])};

  // Rewind to the same fired rocket for each distance. A stale lock keeps its
  // original coordinates even when the registered object has since moved away.
  const saved = Buffer.from(m), result = {};
  for (const [name, gap] of [['pointBlank', 1.1], ['ordinary', 1.3], ['stale', 1.1]]) {
    saved.copy(m);
    m.writeUInt32LE(targets[0], shot + L.shot_target_object);
    vector(shot + L.shot_target, 0, 2, z + gap);
    result[name] = sample(name === 'stale' ? [] : [[0, gap], [2, gap], [3.5, gap]]);
  }
  return result;
}
console.log(JSON.stringify({...await weapon(3), ...await weapon(5)}));
