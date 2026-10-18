// Path and camera rules, one tick at a time in each profile: the snail rides a
// turnover or an S-bend, leaves a path sideways while hovering, coasts off a lift
// path, or lands on a trampoline (port/patches/12-path-camera.patch,
// 13-trampoline-ring.patch). Also reads the mobile path templates the shell
// builds (port/shell/extras_paths.cpp).
import { LAYOUT as L, openMobileGame } from './port_mobile_runtime.mjs';

// Shell extra path pairs, in snail_extra_path_pair order.
const EXTRA_PATHS = ['LOOPTHELOOP1', 'SBEND1', 'SBEND2', 'SBEND4', 'DETOUR2', 'DETOUR3', 'DETOUR',
  'SUPERTRAMPLEFT', 'TURNOVER2', 'TURNOVER3', 'SHIMMY1', 'SHIMMY2', 'SHIMMY4', 'SHIMMY',
  'INVERT1', 'HALFPOLE', 'TRANS_LOOPTHELOOP1', 'TRANS_INVERT1', 'CAGE2', 'TWISTER2A', 'TWISTER2B'];
const PC_SBEND_SLOT = 14;

const game = await openMobileGame(process.argv[2]);
const { e, sub } = game;
const player = sub + L.player;
const follow = player + L.follow;
// Every case starts from this tick of Pro 1, the snail on open track.
const start = Buffer.from(game.memory());

const extraPath = (name) => e.snail_extra_path_pair(EXTRA_PATHS.indexOf(name));
const samples = (path, bank, field) => {
  const m = game.memory();
  const base = m.readUInt32LE(path + bank);
  return Array.from({length: m.readInt32LE(path + L.path_segment_count)},
    (_, i) => m.readFloatLE(base + i * L.sample + field));
};
const cellAt = (row, lane) => sub + L.runtime_cells + (row * L.lanes + lane) * L.cell;
const position = (m, axis) => m.readFloatLE(player + L.player_position + 4 * axis);

function tick(ultimate, setup) {
  game.memory().set(start);
  e.snail_set_profile(ultimate);
  setup(game.memory());
  e.snail_frame(1 / 60);
  return game.memory();
}

// Puts the snail on `path` at sample `index`, centred on it, with the path's
// source cell half its length behind the snail.
function ride(m, path, index) {
  const count = m.readInt32LE(path + L.path_segment_count);
  m[follow] = 1;
  m.writeUInt32LE(path, follow + L.follow_template);
  m.writeUInt32LE(cellAt(Math.floor(position(m, 2) - count / 2), 4), follow + L.follow_cell);
  m.writeInt32LE(index, follow + L.follow_index);
  m.writeFloatLE(0, follow + L.follow_progress);
  m.writeFloatLE(0, follow + L.follow_vertical);
  m.writeFloatLE(samples(path, L.path_primary_samples, L.sample_center_x)[index], player + L.player_position);
  m.writeFloatLE(0, player + L.player_velocity + 4);
}

const followState = (m) => ({
  active: m[follow],
  index: m.readInt32LE(follow + L.follow_index),
  progress: m.readFloatLE(follow + L.follow_progress),
  roll: m.readFloatLE(follow + L.follow_roll),
});

const out = {kinds: {}, lateralScales: {}, profiles: {}};
for (const name of EXTRA_PATHS) {
  const path = extraPath(name);
  out.kinds[name] = game.memory().readInt32LE(path + L.path_kind);
  out.lateralScales[name] = [...new Set([path, path + L.path].flatMap(
    side => samples(side, L.path_primary_samples, L.sample_lateral_scale)))];
}
out.kinds.SBEND = game.memory().readInt32LE(sub + L.paths + PC_SBEND_SLOT * 2 * L.path + L.path_kind);

const turnover = extraPath('TURNOVER2');
out.turnover = {
  count: game.memory().readInt32LE(turnover + L.path_segment_count),
  roll: samples(turnover, L.path_primary_samples, L.sample_roll),
  deltaLength: samples(turnover, L.path_secondary_samples, L.sample_delta_length),
};
const sbend = extraPath('SBEND1');

for (const ultimate of [0, 1]) {
  const result = out.profiles[ultimate ? 'ultimate' : 'original'] = {};
  for (const pitch of [0, 0.5]) {
    const m = tick(ultimate, m => {
      m[follow] = 0;
      m.writeFloatLE(pitch, player + L.player_pitch_cycle);
      m.writeFloatLE(0.5, player + L.player_lift);
    });
    result[pitch ? 'liftDuringPitch' : 'liftOffPath'] = m.readFloatLE(player + L.player_lift);
  }

  let m = tick(ultimate, m => ride(m, sbend, 13));
  result.sbend = {
    ...followState(m),
    lift: m.readFloatLE(player + L.player_lift),
    z: position(m, 2),
    cellZ: m.readFloatLE(m.readUInt32LE(follow + L.follow_cell) + L.cell_position + 8),
    count: m.readInt32LE(sbend + L.path_segment_count),
  };

  for (const heading of [0, 1]) {
    m = tick(ultimate, m => {
      ride(m, turnover, 20);
      m.writeFloatLE(heading, turnover + L.path_heading);
    });
    result[heading ? 'turnoverWithHeading' : 'turnover'] = followState(m);
  }

  m = tick(ultimate, m => {
    ride(m, turnover, 20);
    m.writeInt32LE(L.hover_active, player + L.player_hover_state);
    m.writeFloatLE(position(m, 0) + 3, player + L.player_position);
  });
  result.hoverSideExit = followState(m);

  for (const falling of [1, 0]) {
    m = tick(ultimate, m => {
      // Two trampoline rows: the snail may cross into the next one this tick.
      for (const row of [0, 1]) {
        const cell = cellAt(Math.floor(position(m, 2)) + row, Math.floor(position(m, 0) + 4));
        m[cell + L.cell_tile] = L.trampoline;
        m.writeFloatLE(-3, cell + L.cell_position + 4);
      }
      m[follow] = 0;
      m[player + L.player_exit_pending] = 1;
      m.writeFloatLE(-3, player + L.player_position + 4);
      m.writeFloatLE(-0.1, player + L.player_velocity + 4);
      const flags = m.readUInt32LE(sub + L.runtime_flags);
      m.writeUInt32LE(falling ? flags | L.allow_falling : flags & ~L.allow_falling, sub + L.runtime_flags);
    });
    result[falling ? 'trampolineBounce' : 'noFallClamp'] = {
      rings: e.snail_tramp_ring_active_count(),
      y: position(m, 1),
    };
  }

  const setupReentry = (m, x, y, zOff, vy, vz, width = 2) => {
    const baseRow = Math.floor(position(m, 2));
    const pCell = cellAt(baseRow, 4);
    const s0 = m.readUInt32LE(turnover + L.path_secondary_samples);
    const s0x = m.readFloatLE(s0 + 0x30);
    const s0y = m.readFloatLE(s0 + 0x34);
    m.writeFloatLE(-s0x, pCell + L.cell_position);
    m.writeFloatLE(2.0 - s0y, pCell + L.cell_position + 4);
    m.writeFloatLE(baseRow, pCell + L.cell_position + 8);
    m.writeUInt32LE(turnover, pCell + L.cell_attachment);
    m.writeInt32LE(width, turnover + L.path_width_cells);
    for (const r of [baseRow, baseRow + 1]) {
      const rowAddr = sub + L.runtime_rows + r * L.runtime_row;
      m.writeUInt32LE(
        m.readUInt32LE(rowAddr + L.row_flags) | L.primary_attachment_flag,
        rowAddr + L.row_flags,
      );
      m.writeUInt32LE(pCell, rowAddr + L.row_primary_cell);
    }
    m[follow] = 0;
    m[player + L.player_exit_pending] = 1;
    m.writeFloatLE(x, player + L.player_position);
    m.writeFloatLE(y, player + L.player_position + 4);
    m.writeFloatLE(baseRow + zOff, player + L.player_position + 8);
    m.writeFloatLE(0, player + L.player_velocity);
    m.writeFloatLE(vy, player + L.player_velocity + 4);
    m.writeFloatLE(vz, player + L.player_velocity + 8);
  };

  m = tick(ultimate, m => setupReentry(m, 0, 2.25, 0.3, -0.2, 0.2));
  result.reentryBeforeCrossing = followState(m);

  m = tick(ultimate, m => setupReentry(m, 0, 2.05, 0.3, -0.1, 0.2));
  result.reentryAfterCrossing = followState(m);

  m = tick(ultimate, m => setupReentry(m, 1.45, 2.05, 0.3, -0.1, 0.2, 2));
  result.reentryOutsideHalfWidth = followState(m);
}
console.log(JSON.stringify(out));
