import {LAYOUT as L, openGame} from './port_frontend.mjs';

const [wasm, profile] = process.argv.slice(2);
const game = await openGame(wasm, profile === 'ultimate', 'Probe');
const memory = () => game.memory();
const sub = game.sub, player = sub + L.player;
const ptr = at => memory().readUInt32LE(at);
const float = at => memory().readFloatLE(at);
const blinks = Array.from({length: 24}, (_, i) => float(sub + L.blink_samples + i * 4));
const star = ptr(game.root + L.star_entries) + L.star_entry_size;  // first star with a random alpha
const stars = [0, 1, 2].map(i => {
  const s = star + i * L.star_entry_size;
  return [float(s + L.star_alpha), float(s + L.star_velocity), float(s + L.star_velocity + 4)];
});

game.mainMenu();
game.press('New Game');
game.press('Postal Mode');
game.press('Deliver');
game.press('Click to Start');
game.step(30);

// The two ghost sprites stay in the player's active sprite list throughout a run.
function sprites(texture) {
  let s = ptr(player + L.ghost_sprite);
  while (ptr(s + L.sprite_prev)) s = ptr(s + L.sprite_prev);
  const result = [];
  for (; s; s = ptr(s + L.sprite_next)) {
    if (ptr(s + L.sprite_texture) === texture) result.push(s);
  }
  return result;
}

// Put one authored weapon ring and one slug in the next stretch of Postal I.
// Entering its spawn window runs the normal constructors and actor updates.
const row = Math.max(ptr(sub + L.runtime_row_scan_end), ptr(sub + L.first_block_rows)) + 8;
const cell = sub + L.runtime_cells + row * L.lanes * L.cell;
memory().writeUInt8(L.ring_tile, cell + L.cell_tile);
memory().writeUInt8(L.slug_tile, cell + 7 * L.cell + L.cell_tile);
const flags = sub + L.runtime_rows + row * L.runtime_row + L.row_flags;
memory().writeUInt32LE(ptr(flags) | L.normal_ring, flags);
game.until(() => sprites(0x87).length, 300);
const ringSprites = sprites(0x87);
const ring = ringSprites.map(s => [float(s + L.sprite_size_start), float(s + L.sprite_facing)]);
const ringSlot = Array.from({length: L.ring_slots}, (_, i) => sub + L.rings + i * L.ring)
  .find(s => ptr(s + L.ring_state) === 1 && ptr(s + L.ring_kind) === 5);

// Detonate the nuke while the slug and any of the course's own slugs are in range.
const slugs = sprites(118).length;
memory().writeFloatLE(0.1, player + L.nuke_progress);
game.step();
const debris = sprites(129).length;
memory().writeFloatLE(0, player + L.nuke_progress);

// Fire once with each weapon. Count new trail sprites across the first four
// ticks, including the initial AI call made by the shot's constructor.
function trail(tier, kind, texture) {
  memory().writeInt32LE(tier, player + L.shooting_tier);
  game.step(25);
  let previous = new Set(sprites(texture));
  const counts = [];
  game.e.snail_button(0, 1);
  const shots = Array.from({length: 12}, (_, i) => player + L.golb_shots + i * L.golb_size);
  for (let i = 0; i < 30 && counts.length < 4; ++i) {
    game.step();
    const live = sprites(texture);
    if (shots.some(s => ptr(s + L.golb_state) === 1 && ptr(s + L.golb_kind) === kind)) {
      game.e.snail_button(0, 0);
      counts.push(live.filter(s => !previous.has(s)).length);
    }
    previous = new Set(live);
  }
  return counts;
}

const jets = trail(0, 0, 33), smoke = trail(5, 2, 128);

// Move the ring onto the snail, then change profile during its collection
// animation. Teardown must release precisely the children it allocated.
memory().writeUInt8(0, ringSlot + L.ring_oscillate_x);
memory().copy(memory(), ringSlot + L.ring_position, player + L.camera_target, player + L.camera_target + 12);
game.until(() => ptr(ringSlot + L.ring_state) !== 1, 5);
game.e.snail_set_profile(profile === 'original' ? 1 : 0);
game.until(() => ptr(ringSlot + L.ring_state) === 0, 100);
const ringSurvivors = sprites(0x87).filter(s => ringSprites.includes(s)).length;
console.log(JSON.stringify({blinks, stars, ring, slugs, debris, jets, smoke, ringSurvivors}));
