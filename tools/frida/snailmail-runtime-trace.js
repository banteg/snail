'use strict';

const TARGET_MODULE_NAMES = ['SnailMail_unwrapped.exe', 'SnailMail.RWG'];
const PREFERRED_IMAGE_BASE = 0x400000;
const MODULE_POLL_MS = 250;
const TRACE_OUTPUT_DIR = 'C:\\share\\snail\\frida';
const TRACE_OUTPUT_PREFIX = 'snailmail-trace';
const ERROR_ALREADY_EXISTS = 183;
const TRACE_PROFILE = 'attachment_survey';

const HOOK_PROFILES = {
  broad_runtime: {
    level_start: true,
    path_lookup: true,
    movement_flags_update: true,
    player_update: true,
    completion_handoff_arm: true,
    completion_screen_init: true,
    complete_subgame_call: true,
    death_handoff_cutscene: false,
    death_handoff_update: false,
    death_select_respawn: true,
    death_select_final_loss: true,
    respawn_enter: true,
    respawn_life_decrement: false,
    respawn_complete_subgame_branch: false,
    track_pair_payload: true,
    attachment_follow_dispatch: true,
    attachment_probe: true,
    attachment_begin: true,
    attachment_update: true,
    attachment_end: true,
    attachment_end_callsite: true,
    floor_sample: true,
    garbage_spawn: true,
    health_pickup: true,
    jetpack_pickup: true,
    ring_effect: true,
    salt_spawn: true,
    salt_update: true,
    salt_deactivate: true,
    slug_spawn: true,
  },
  completion_handoff: {
    level_start: true,
    path_lookup: false,
    movement_flags_update: false,
    player_update: false,
    completion_handoff_arm: true,
    completion_screen_init: true,
    complete_subgame_call: true,
    death_handoff_cutscene: false,
    death_handoff_update: false,
    death_select_respawn: false,
    death_select_final_loss: false,
    respawn_enter: false,
    respawn_life_decrement: false,
    respawn_complete_subgame_branch: false,
    track_pair_payload: false,
    attachment_follow_dispatch: false,
    attachment_probe: false,
    attachment_begin: false,
    attachment_update: false,
    attachment_end: false,
    attachment_end_callsite: false,
    floor_sample: false,
    garbage_spawn: false,
    health_pickup: false,
    jetpack_pickup: false,
    ring_effect: false,
    salt_spawn: false,
    salt_update: false,
    salt_deactivate: false,
    slug_spawn: false,
  },
  failure_handoff: {
    level_start: false,
    path_lookup: false,
    movement_flags_update: false,
    player_update: false,
    completion_handoff_arm: false,
    completion_screen_init: false,
    complete_subgame_call: false,
    death_handoff_cutscene: false,
    death_handoff_update: false,
    death_select_respawn: true,
    death_select_final_loss: true,
    respawn_enter: true,
    respawn_life_decrement: false,
    respawn_complete_subgame_branch: false,
    track_pair_payload: false,
    attachment_follow_dispatch: false,
    attachment_probe: false,
    attachment_begin: false,
    attachment_update: false,
    attachment_end: false,
    attachment_end_callsite: false,
    floor_sample: false,
    garbage_spawn: false,
    health_pickup: false,
    jetpack_pickup: false,
    ring_effect: false,
    salt_spawn: false,
    salt_update: false,
    salt_deactivate: false,
    slug_spawn: false,
  },
  attachment_exit: {
    level_start: false,
    path_lookup: false,
    movement_flags_update: true,
    player_update: true,
    completion_handoff_arm: false,
    completion_screen_init: false,
    complete_subgame_call: false,
    death_handoff_cutscene: false,
    death_handoff_update: false,
    death_select_respawn: false,
    death_select_final_loss: false,
    respawn_enter: false,
    respawn_life_decrement: false,
    respawn_complete_subgame_branch: false,
    track_pair_payload: false,
    attachment_follow_dispatch: false,
    attachment_probe: false,
    attachment_begin: true,
    attachment_update: true,
    attachment_end: true,
    attachment_end_callsite: false,
    floor_sample: false,
    garbage_spawn: false,
    health_pickup: false,
    jetpack_pickup: false,
    ring_effect: false,
    salt_spawn: false,
    salt_update: false,
    salt_deactivate: false,
    slug_spawn: false,
  },
  attachment_survey: {
    level_start: true,
    path_lookup: true,
    movement_flags_update: true,
    player_update: true,
    completion_handoff_arm: false,
    completion_screen_init: false,
    complete_subgame_call: false,
    death_handoff_cutscene: false,
    death_handoff_update: false,
    death_select_respawn: false,
    death_select_final_loss: false,
    respawn_enter: false,
    respawn_life_decrement: false,
    respawn_complete_subgame_branch: false,
    track_pair_payload: true,
    attachment_follow_dispatch: false,
    attachment_probe: false,
    attachment_begin: true,
    attachment_update: true,
    attachment_end: true,
    attachment_end_callsite: false,
    floor_sample: true,
    garbage_spawn: false,
    health_pickup: true,
    jetpack_pickup: true,
    ring_effect: true,
    salt_spawn: true,
    salt_update: true,
    salt_deactivate: true,
    slug_spawn: true,
  },
};

const HOOKS = HOOK_PROFILES[TRACE_PROFILE] || HOOK_PROFILES.broad_runtime;

const LIMITS = {
  level_start: 128,
  path_lookup: 2048,
  movement_flags_update: 2048,
  player_update: 4096,
  completion_handoff_arm: 384,
  completion_screen_init: 256,
  complete_subgame_call: 256,
  death_handoff_cutscene: 256,
  death_handoff_update: 256,
  death_select_respawn: 128,
  death_select_final_loss: 128,
  respawn_enter: 256,
  respawn_life_decrement: 128,
  respawn_complete_subgame_branch: 128,
  track_pair_payload: 2048,
  attachment_follow_dispatch: 2048,
  attachment_probe: 4096,
  attachment_begin: 1024,
  attachment_update: 4096,
  attachment_end: 1024,
  attachment_end_callsite: 1024,
  floor_sample: 4096,
  garbage_spawn: 4096,
  health_pickup: 1024,
  jetpack_pickup: 1024,
  ring_effect: 2048,
  salt_spawn: 4096,
  salt_update: 4096,
  salt_deactivate: 4096,
  slug_spawn: 1024,
};

const VA = {
  app_ptr_global: 0x4df904,
  find_segment_path_index_by_name: 0x429ae0,
  begin_track_attachment_follow_state: 0x420c40,
  update_track_attachment_follow_state: 0x420cb0,
  try_enter_track_attachment_from_swept_motion: 0x42c770,
  update_subgoldy_attachment_probe_flag40: 0x43bdf0,
  update_subgoldy_attachment_probe_flag80: 0x43bec5,
  update_player_movement_flags: 0x43a1a0,
  normalize_level_runtime_fields: 0x437eb0,
  end_track_attachment_follow_state: 0x43af60,
  update_subgoldy: 0x43b120,
  mark_current_track_pair_with_payload: 0x43d3d0,
  get_track_grid_cell_at_world_position: 0x43d410,
  sample_track_floor_height_at_position: 0x43d4d0,
  spawn_track_health_pickup: 0x43d6c0,
  spawn_track_jetpack_pickup: 0x43d890,
  spawn_track_garbage_hazard: 0x43da80,
  spawn_track_ring_or_special_effect: 0x43df10,
  spawn_salt_runtime_entity: 0x441560,
  update_salt_hazard: 0x4417d0,
  deactivate_salt_runtime_entity: 0x441740,
  spawn_slug_runtime_entity: 0x43dc80,
  get_track_cell_row_index: 0x447040,
  completion_handoff_active_arm: 0x43c7b7,
  initialize_completion_screen_entry: 0x404920,
  complete_subgame_entry: 0x438700,
  death_handoff_via_cutscene: 0x446b04,
  death_handoff_via_update_subgoldy: 0x43c093,
  death_select_state_set: 0x441fa0,
  update_subgoldy_resurrect_enter: 0x441fd0,
  respawn_life_decrement: 0x44205b,
  respawn_complete_subgame_branch: 0x442096,
};

const ATTACHMENT_PROBE_SITES = [
  {
    va: VA.update_subgoldy_attachment_probe_flag40,
    callsite: '0x43bdf0',
    return_to: '0x43bdf5',
    lane_flag: '0x40',
  },
  {
    va: VA.update_subgoldy_attachment_probe_flag80,
    callsite: '0x43bec5',
    return_to: '0x43beca',
    lane_flag: '0x80',
  },
];

const ATTACHMENT_END_CALLSITES = [
  {
    va: 0x43b9b8,
    callsite: '0x43b9b8',
  },
  {
    va: 0x43c008,
    callsite: '0x43c008',
  },
  {
    va: 0x43c34b,
    callsite: '0x43c34b',
  },
  {
    va: 0x43c507,
    callsite: '0x43c507',
  },
];

const APP = {
  owner: 0x1b8,
  saved: 0x1bc,
  completion_state: 0x4f3ac,
  replay_return: 0x1066bf0,
};

const SEGMENT_PATH_INDEX_NAMES = [
  'LOOPTHELOOP',
  'LOOPTHELOOP2',
  'LOOPTHELOOP4',
  'LOOPTHELOOPT2',
  'LOOPTHELOOPT3',
  'LOOPTHELOOPT4',
  'LOOPTHELOOPW',
  'LOOPBOW',
  'HILL',
  'HILL4C',
  'HILL4',
  'VALLEY',
  'VALLEY4C',
  'VALLEY4',
  'SBEND',
  'CAGE2',
  'HUMP',
  'DUMP',
  'HUMPSMALL',
  'DUMPSMALL',
  'DIP',
  'SCREW',
  'SLALOM',
  'SLALOMBIG',
  'WORM',
  'LOOPOUT',
  'LOOPOUT3',
  'LOOPOUTBIG',
  'SWEEP',
  'SNAKE',
  'WARP',
  'SUPERTRAMP',
  'SLALOMDOUBLE',
  'P0',
  'P1',
  'P2',
  'START',
  'TURNOVER',
  'TURNOVERDOUBLE',
  'TURNUNDER',
  'WIBBLE',
  'INVERT',
  'HALFPIPE',
  'TWISTERA',
  'TWISTERB',
  'TWISTER2A',
  'TWISTER2B',
  'TOAD0',
  'TOAD1',
  'TOADPAIR0',
  'TOADPAIR1',
];

const RUNTIME = {
  track_center_x: 0x38,
  level_mode: 0x40,
  level_mode_arg: 0x44,
  mode_or_track: 0x40,
  build_flags: 0x4c,
  track_row_start: 0x50,
  track_row_end: 0x58,
  track_state_latch: 0xa854,
  active_level_flag_0: 0xff25d0,
  active_level_flag_1: 0xff25d1,
  active_level_ptr: 0xff25d4,
  replay_track_index: 0xff25d8,
  garbage_scalar: 0x125ffd8,
  salt_scalar: 0x125ffdc,
};

const TRACK_LAYOUT = {
  lane_count: 8,
  row_count: 0xc80,
  gameplay_grid_base: 0x3bfac8,
  gameplay_grid_stride: 0x54,
  row_cell_base: 0x5ccac8,
  row_cell_stride: 0xf4,
};

const counters = {};
const sampledState = {};
const floatScratch = Memory.alloc(4);
let hookInstalled = false;
let traceFile = null;
let traceFilePath = null;
let traceFileError = null;

const createDirectoryW = new SystemFunction(
  Process.getModuleByName('kernel32.dll').getExportByName('CreateDirectoryW'),
  'bool',
  ['pointer', 'pointer']
);

function pad2(value) {
  return value < 10 ? '0' + value : String(value);
}

function formatTimestamp(date) {
  return [
    date.getFullYear(),
    pad2(date.getMonth() + 1),
    pad2(date.getDate()),
    '-',
    pad2(date.getHours()),
    pad2(date.getMinutes()),
    pad2(date.getSeconds()),
  ].join('');
}

function ensureDirectory(path) {
  const normalized = path.replace(/\//g, '\\');
  const parts = normalized.split('\\');
  if (parts.length === 0) {
    return;
  }

  let current = '';
  let index = 0;
  if (/^[A-Za-z]:$/.test(parts[0])) {
    current = parts[0] + '\\';
    index = 1;
  }

  for (; index < parts.length; index += 1) {
    const part = parts[index];
    if (part.length === 0) {
      continue;
    }

    current = current.length === 0 ? part : current + '\\' + part;
    const result = createDirectoryW(Memory.allocUtf16String(current), NULL);
    if (!result.value && result.lastError !== ERROR_ALREADY_EXISTS) {
      throw new Error('CreateDirectoryW failed for ' + current + ' (lastError=' + result.lastError + ')');
    }
  }
}

function getTraceFilePath() {
  if (traceFilePath === null) {
    traceFilePath =
      TRACE_OUTPUT_DIR +
      '\\' +
      TRACE_OUTPUT_PREFIX +
      '-' +
      formatTimestamp(new Date()) +
      '-' +
      Process.id +
      '.ndjson';
  }
  return traceFilePath;
}

function appendTraceLine(line) {
  if (traceFileError !== null) {
    return false;
  }

  try {
    if (traceFile === null) {
      ensureDirectory(TRACE_OUTPUT_DIR);
      traceFile = new File(getTraceFilePath(), 'ab');
      console.log('[snailmail-trace] writing NDJSON to ' + traceFilePath);
    }

    traceFile.write(line + '\n');
    traceFile.flush();
    return true;
  } catch (error) {
    traceFileError = String(error);
    console.error('[snailmail-trace] file output disabled: ' + traceFileError);
    return false;
  }
}

function roundFloat(value) {
  if (value === null || value === undefined) {
    return null;
  }
  return Math.round(value * 1000) / 1000;
}

function asPtr(value) {
  if (value === null || value === undefined) {
    return null;
  }
  try {
    return ptr(value);
  } catch (_) {
    return null;
  }
}

function hex(value) {
  const p = asPtr(value);
  return p === null ? null : p.toString();
}

function safeReadU8(base, offset) {
  const p = asPtr(base);
  if (p === null || p.isNull()) {
    return null;
  }
  try {
    return p.add(offset || 0).readU8();
  } catch (_) {
    return null;
  }
}

function safeReadU32(base, offset) {
  const p = asPtr(base);
  if (p === null || p.isNull()) {
    return null;
  }
  try {
    return p.add(offset || 0).readU32();
  } catch (_) {
    return null;
  }
}

function safeReadFloat(base, offset) {
  const p = asPtr(base);
  if (p === null || p.isNull()) {
    return null;
  }
  try {
    return roundFloat(p.add(offset || 0).readFloat());
  } catch (_) {
    return null;
  }
}

function safeReadPointer(base, offset) {
  const p = asPtr(base);
  if (p === null || p.isNull()) {
    return null;
  }
  try {
    return p.add(offset || 0).readPointer();
  } catch (_) {
    return null;
  }
}

function safeReadCString(base, maxLength) {
  const p = asPtr(base);
  if (p === null || p.isNull()) {
    return null;
  }
  try {
    return p.readCString(maxLength || 128);
  } catch (_) {
    return null;
  }
}

function safeReadAsciiToken(base, maxLength) {
  const p = asPtr(base);
  if (p === null || p.isNull()) {
    return null;
  }

  try {
    const bytes = p.readByteArray(maxLength || 64);
    if (bytes === null) {
      return null;
    }

    const view = new Uint8Array(bytes);
    let token = '';
    for (let index = 0; index < view.length; index += 1) {
      const byte = view[index];
      if (byte === 0) {
        break;
      }

      const isDigit = byte >= 0x30 && byte <= 0x39;
      const isUpper = byte >= 0x41 && byte <= 0x5a;
      const isLower = byte >= 0x61 && byte <= 0x7a;
      if (!isDigit && !isUpper && !isLower) {
        break;
      }

      token += String.fromCharCode(byte);
    }

    return token.length === 0 ? null : token;
  } catch (_) {
    return null;
  }
}

function safeReadVec3(base, offset) {
  const p = asPtr(base);
  if (p === null || p.isNull()) {
    return null;
  }
  const q = p.add(offset || 0);
  try {
    return {
      x: roundFloat(q.readFloat()),
      y: roundFloat(q.add(4).readFloat()),
      z: roundFloat(q.add(8).readFloat()),
    };
  } catch (_) {
    return null;
  }
}

function boolFlag(value) {
  if (value === null || value === undefined) {
    return null;
  }
  return value !== 0;
}

function fastcallArg0(args, context) {
  const fromArgs = asPtr(args[0]);
  if (fromArgs !== null) {
    return fromArgs;
  }
  return asPtr(context.ecx);
}

function floatArg(arg) {
  const p = asPtr(arg);
  if (p === null) {
    return null;
  }
  try {
    floatScratch.writeU32(p.toUInt32());
    return roundFloat(floatScratch.readFloat());
  } catch (_) {
    return null;
  }
}

function canonicalPathNameFromIndex(pathIndex) {
  if (pathIndex === null || pathIndex === undefined) {
    return null;
  }
  if (pathIndex < 0 || pathIndex >= SEGMENT_PATH_INDEX_NAMES.length) {
    return null;
  }
  return SEGMENT_PATH_INDEX_NAMES[pathIndex];
}

function makeLevelRuntimeSnapshot(game) {
  const gamePtr = asPtr(game);
  const flag0 = safeReadU8(gamePtr, RUNTIME.active_level_flag_0);
  const flag1 = safeReadU8(gamePtr, RUNTIME.active_level_flag_1);
  const hasActiveLevel = (flag0 !== null && flag0 !== 0) || (flag1 !== null && flag1 !== 0);
  const activeLevelPtr = hasActiveLevel ? safeReadPointer(gamePtr, RUNTIME.active_level_ptr) : null;

  return {
    active_level_flag_0: flag0,
    active_level_flag_1: flag1,
    active_level_present: hasActiveLevel,
    active_level: hex(activeLevelPtr),
    selected_track_id: activeLevelPtr !== null ? safeReadU32(activeLevelPtr, 0x2c) : null,
    build_flags: safeReadU32(gamePtr, RUNTIME.build_flags),
    track_row_start: safeReadU32(gamePtr, RUNTIME.track_row_start),
    track_row_end: safeReadU32(gamePtr, RUNTIME.track_row_end),
    garbage_scalar: safeReadFloat(gamePtr, RUNTIME.garbage_scalar),
    salt_scalar: safeReadFloat(gamePtr, RUNTIME.salt_scalar),
  };
}

function eventPayload(event, extra) {
  const seq = (counters[event] || 0) + 1;
  counters[event] = seq;

  const limit = LIMITS[event];
  if (limit !== undefined && seq > limit) {
    if (seq === limit + 1) {
      const suppressed = {
        ts_ms: Date.now(),
        pid: Process.id,
        tid: Process.getCurrentThreadId(),
        event: event + '_suppressed',
        limit: limit,
      };
      const line = JSON.stringify(suppressed);
      appendTraceLine(line);
      console.log(line);
    }
    return null;
  }

  const payload = {
    ts_ms: Date.now(),
    pid: Process.id,
    tid: Process.getCurrentThreadId(),
    event: event,
    seq: seq,
  };

  if (extra) {
    Object.keys(extra).forEach(function (key) {
      payload[key] = extra[key];
    });
  }

  return payload;
}

function emit(event, extra) {
  const payload = eventPayload(event, extra);
  if (payload !== null) {
    const line = JSON.stringify(payload);
    appendTraceLine(line);
    console.log(line);
  }
}

function findTargetModule() {
  const modules = Process.enumerateModules();
  const targetLower = TARGET_MODULE_NAMES.map(function (name) {
    return name.toLowerCase();
  });

  for (let i = 0; i < modules.length; i += 1) {
    const module = modules[i];
    if (targetLower.indexOf(module.name.toLowerCase()) !== -1) {
      return module;
    }
  }

  for (let i = 0; i < modules.length; i += 1) {
    const module = modules[i];
    const nameLower = module.name.toLowerCase();
    const pathLower = module.path.toLowerCase();
    if (
      nameLower.indexOf('snailmail') !== -1 &&
      targetLower.some(function (target) {
        return pathLower.indexOf(target) !== -1;
      })
    ) {
      return module;
    }
  }

  return null;
}

function fromVa(module, va) {
  return module.base.add(va - PREFERRED_IMAGE_BASE);
}

function makeTrackGridCellLocator(module) {
  try {
    return new NativeFunction(fromVa(module, VA.get_track_grid_cell_at_world_position), 'pointer', ['pointer', 'pointer'], 'thiscall');
  } catch (_) {
    return null;
  }
}

function makeTrackCellRowIndex(module) {
  try {
    return new NativeFunction(fromVa(module, VA.get_track_cell_row_index), 'int', ['pointer'], 'thiscall');
  } catch (_) {
    return null;
  }
}

function deriveTrackGridAddressInfo(gamePtr, cellPtr) {
  const game = asPtr(gamePtr);
  const cell = asPtr(cellPtr);
  if (game === null || game.isNull() || cell === null || cell.isNull()) {
    return null;
  }

  const cellAddress = cell.toUInt32();
  const gameplayGridBase = game.add(TRACK_LAYOUT.gameplay_grid_base).toUInt32();
  const gameplayGridSize = TRACK_LAYOUT.row_count * TRACK_LAYOUT.lane_count * TRACK_LAYOUT.gameplay_grid_stride;
  if (cellAddress >= gameplayGridBase && cellAddress < gameplayGridBase + gameplayGridSize) {
    const offset = cellAddress - gameplayGridBase;
    if (offset % TRACK_LAYOUT.gameplay_grid_stride === 0) {
      const index = Math.floor(offset / TRACK_LAYOUT.gameplay_grid_stride);
      return {
        storage: 'grid',
        row: Math.floor(index / TRACK_LAYOUT.lane_count),
        lane: index % TRACK_LAYOUT.lane_count,
      };
    }
  }

  const rowCellBase = game.add(TRACK_LAYOUT.row_cell_base).toUInt32();
  const rowCellSize = TRACK_LAYOUT.row_count * TRACK_LAYOUT.row_cell_stride;
  if (cellAddress >= rowCellBase && cellAddress < rowCellBase + rowCellSize) {
    const offset = cellAddress - rowCellBase;
    if (offset % TRACK_LAYOUT.row_cell_stride === 0) {
      return {
        storage: 'row',
        row: Math.floor(offset / TRACK_LAYOUT.row_cell_stride),
        lane: null,
      };
    }
  }

  return null;
}

function laneCenterX(lane) {
  if (lane === null || lane === undefined) {
    return null;
  }
  return roundFloat(lane - 3.5);
}

function deriveGridWorld(row, lane, floorHeight) {
  if (row === null || row === undefined || lane === null || lane === undefined) {
    return null;
  }
  return {
    x: laneCenterX(lane),
    y: floorHeight,
    z: roundFloat(row + 0.5),
  };
}

function summarizeCell(cellPtr, getTrackCellRowIndex, gamePtr) {
  const cell = asPtr(cellPtr);
  if (cell === null || cell.isNull()) {
    return null;
  }

  const derived = deriveTrackGridAddressInfo(gamePtr, cell);
  let row = derived !== null ? derived.row : null;
  if (row === null && getTrackCellRowIndex !== null) {
    try {
      row = getTrackCellRowIndex(cell);
    } catch (_) {
      row = null;
    }
  }

  const floorHeight = safeReadFloat(cell, 0x14);
  if (derived !== null && derived.storage === 'grid') {
    return {
      ptr: hex(cell),
      storage: 'grid',
      row: row,
      lane: derived.lane,
      flags: safeReadU32(cell, 4),
      tile_type: safeReadU8(cell, 60),
      floor_height: floorHeight,
      row_scalar_a: safeReadFloat(cell, 0x24),
      row_scalar_b: safeReadFloat(cell, 0x34),
      payload: safeReadU32(cell, 0x50),
      world: deriveGridWorld(row, derived.lane, floorHeight),
      attachment: null,
      attachment_kind: null,
    };
  }

  const attachment = safeReadPointer(cell, 56);
  return {
    ptr: hex(cell),
    storage: derived !== null ? derived.storage : null,
    row: row,
    lane: derived !== null ? derived.lane : null,
    flags: safeReadU32(cell, 4),
    tile_type: safeReadU8(cell, 60),
    floor_height: floorHeight,
    row_scalar_a: safeReadFloat(cell, 0x24),
    row_scalar_b: safeReadFloat(cell, 0x34),
    payload: safeReadU32(cell, 0x50),
    world: safeReadVec3(cell, 16),
    attachment: hex(attachment),
    attachment_kind: safeReadU32(attachment, 56),
  };
}

function summarizeAttachmentTemplate(templatePtr) {
  const template = asPtr(templatePtr);
  if (template === null || template.isNull()) {
    return null;
  }

  return {
    ptr: hex(template),
    header_30: safeReadFloat(template, 0x30),
    header_34: safeReadFloat(template, 0x34),
    kind: safeReadU32(template, 0x38),
    mirror_or_variant: safeReadU32(template, 0x3c),
    terminal_flag: safeReadU32(template, 0x40),
    sample_count: safeReadU32(template, 0x44),
    sample_count_f32: safeReadFloat(template, 0x4c),
    width_or_scale: safeReadFloat(template, 0x50),
    subdivision_count: safeReadU32(template, 0x54),
    primary_points: hex(safeReadPointer(template, 0x58)),
    secondary_points: hex(safeReadPointer(template, 0x5c)),
    sample_delta: safeReadVec3(template, 0x80),
    sample_length: safeReadFloat(template, 0x8c),
    row_scalar_a: safeReadFloat(template, 0x98),
    row_scalar_b: safeReadFloat(template, 0x9c),
    row_scalar_c: safeReadFloat(template, 0xa0),
    row_scalar_d: safeReadFloat(template, 0xa4),
  };
}

function summarizeFollowState(followStatePtr, getTrackCellRowIndex) {
  const followState = asPtr(followStatePtr);
  if (followState === null || followState.isNull()) {
    return null;
  }

  const playerPtr = safeReadPointer(followState, 0x38);
  const gamePtr = safeReadPointer(playerPtr, 0x408);
  const templatePtr = safeReadPointer(followState, 4);

  return {
    ptr: hex(followState),
    active: boolFlag(safeReadU32(followState, 0)),
    template: hex(templatePtr),
    template_summary: summarizeAttachmentTemplate(templatePtr),
    cell: summarizeCell(safeReadPointer(followState, 8), getTrackCellRowIndex, gamePtr),
    sample_index: safeReadU32(followState, 0xc),
    progress: safeReadFloat(followState, 0x10),
    offset_y: safeReadFloat(followState, 0x14),
    orientation: safeReadVec3(followState, 0x18),
    output_position: safeReadVec3(followState, 0x2c),
    player: hex(playerPtr),
  };
}

function computeSampledFloorHeight(cell, position) {
  if (cell === null || position === null || cell.tile_type === null || position.z === null) {
    return null;
  }

  const rowFraction = position.z - Math.floor(position.z);
  switch (cell.tile_type) {
    case 0x01:
    case 0x0e:
    case 0x0f:
      return 0.0;
    case 0x02:
    case 0x03:
    case 0x04:
    case 0x05:
    case 0x06:
    case 0x07:
    case 0x0b:
    case 0x0c:
    case 0x0d:
      return rowFraction * 0.400000006;
    case 0x08:
    case 0x09:
    case 0x0a:
      return rowFraction * 0.400000006 + 0.5;
    case 0x16:
      return cell.floor_height;
    default:
      return -100.0;
  }
}

function summarizePlayer(playerPtr, getTrackCellRowIndex) {
  const player = asPtr(playerPtr);
  if (player === null || player.isNull()) {
    return null;
  }

  const gamePtr = safeReadPointer(player, 0x408);
  return {
    ptr: hex(player),
    game: hex(gamePtr),
    build_flags: safeReadU32(gamePtr, RUNTIME.build_flags),
    level_mode: safeReadU32(gamePtr, RUNTIME.level_mode),
    level_mode_arg: safeReadU32(gamePtr, RUNTIME.level_mode_arg),
    track_center_x: safeReadFloat(gamePtr, RUNTIME.track_center_x),
    track_state_latch: safeReadU8(gamePtr, RUNTIME.track_state_latch),
    replay_active: boolFlag(safeReadU8(gamePtr, RUNTIME.active_level_flag_0)),
    replay_track_index: safeReadU32(gamePtr, RUNTIME.replay_track_index),
    position: safeReadVec3(player, 0x68),
    velocity: safeReadVec3(player, 0x410),
    cached_track_pair_cell_a: summarizeCell(safeReadPointer(player, 0x98), getTrackCellRowIndex, gamePtr),
    cached_track_pair_cell_b: summarizeCell(safeReadPointer(player, 0x9c), getTrackCellRowIndex, gamePtr),
    cell: summarizeCell(safeReadPointer(player, 0x43c), getTrackCellRowIndex, gamePtr),
    attachment_active: boolFlag(safeReadU32(player, 0x384)),
    follow_state: hex(player.add(0x384)),
    follow_sample_index: safeReadU32(player, 0x390),
    follow_progress: safeReadFloat(player, 0x394),
    movement_state: safeReadU32(player, 0x120),
    movement_flag_selector: safeReadU32(player, 0x308),
    movement_flags: safeReadU32(player, 0x338),
    previous_movement_flags: safeReadU32(player, 0x33c),
    movement_progress: safeReadFloat(player, 0x2730),
    movement_rate_scalar: safeReadFloat(player, 0x2734),
    track_z_offset: safeReadFloat(player, 0x273c),
    track_z_anchor: safeReadFloat(player, 0x2740),
    movement_mode_selector: safeReadU32(player, 0x40c),
    row_event_id: safeReadU32(player, 0x1e8),
    row_event_state: safeReadU32(player, 0x1ec),
    row_event_timer: safeReadFloat(player, 0x1f0),
    row_event_data_a: safeReadU32(player, 0x1f8),
    row_event_data_b: safeReadU32(player, 0x1fc),
    attachment_exit_pending: boolFlag(safeReadU8(player, 0x41d)),
    attachment_exit_anchor_z: safeReadFloat(player, 0x424),
    post_follow_value_a: safeReadFloat(player, 0x42c),
    post_follow_value_b: safeReadFloat(player, 0x430),
    attachment_exit_progress: safeReadFloat(player, 0x434),
    attachment_exit_progress_step: safeReadFloat(player, 0x438),
    follow_effect_gate_a: boolFlag(safeReadU8(player, 0x44c)),
    follow_effect_gate_b: boolFlag(safeReadU8(player, 0x44d)),
  };
}

function getAppPtr(module) {
  return safeReadPointer(fromVa(module, VA.app_ptr_global), 0);
}

function summarizeAppState(appPtr) {
  const app = asPtr(appPtr);
  if (app === null || app.isNull()) {
    return null;
  }

  return {
    ptr: hex(app),
    owner: safeReadU32(app, APP.owner),
    saved: safeReadU32(app, APP.saved),
    completion_state: safeReadU32(app, APP.completion_state),
    replay_return: safeReadU32(app, APP.replay_return),
  };
}

function summarizeCompletionHandoff(playerPtr) {
  const player = asPtr(playerPtr);
  if (player === null || player.isNull()) {
    return null;
  }

  return {
    active: boolFlag(safeReadU32(player, 0x440)),
    timer: safeReadFloat(player, 0x444),
    step: safeReadFloat(player, 0x448),
    voice_gate: boolFlag(safeReadU8(player, 0x44e)),
    exit_pending: boolFlag(safeReadU8(player, 0x41d)),
    gate_a: boolFlag(safeReadU8(player, 0x44c)),
    gate_b: boolFlag(safeReadU8(player, 0x44d)),
  };
}

function maybeEmitSampled(event, key, digest, stride, extra) {
  if (!sampledState[event]) {
    sampledState[event] = new Map();
  }

  const stateKey = String(key);
  const state = sampledState[event].get(stateKey) || { count: 0, digest: null };
  state.count += 1;
  const changed = state.digest !== digest;
  const periodic = stride <= 1 || state.count === 1 || state.count % stride === 0;
  state.digest = digest;
  sampledState[event].set(stateKey, state);

  if (changed || periodic) {
    emit(event, extra);
  }
}

let nextUpdateSubgoldySeq = 1;
const updateSubgoldyStateByThread = Object.create(null);
const recentAttachmentProbesByPlayer = Object.create(null);

function setCurrentUpdateSubgoldyState(playerPtr) {
  const tid = Process.getCurrentThreadId();
  const state = {
    seq: nextUpdateSubgoldySeq,
    player: hex(playerPtr),
  };
  nextUpdateSubgoldySeq += 1;
  updateSubgoldyStateByThread[tid] = state;
  return state;
}

function clearCurrentUpdateSubgoldyState() {
  const tid = Process.getCurrentThreadId();
  delete updateSubgoldyStateByThread[tid];
}

function getCurrentUpdateSubgoldyState() {
  const tid = Process.getCurrentThreadId();
  return updateSubgoldyStateByThread[tid] || null;
}

function rememberAttachmentProbe(playerPtr, probe) {
  const key = hex(playerPtr);
  if (key === null || probe === null) {
    return;
  }

  const existing = recentAttachmentProbesByPlayer[key] || [];
  existing.push(probe);

  const filtered = existing.filter(function (item) {
    if (probe.update_seq === null || item.update_seq === null) {
      return true;
    }
    return probe.update_seq >= item.update_seq && probe.update_seq - item.update_seq <= 2;
  });

  recentAttachmentProbesByPlayer[key] = filtered.slice(-8);
}

function getRecentAttachmentProbes(playerPtr, updateSeq) {
  const key = hex(playerPtr);
  if (key === null) {
    return null;
  }

  const probes = recentAttachmentProbesByPlayer[key] || [];
  const filtered = probes.filter(function (item) {
    if (updateSeq === null || item.update_seq === null) {
      return true;
    }
    return Math.abs(item.update_seq - updateSeq) <= 1;
  });

  return filtered.length > 0 ? filtered : null;
}

function installHooks(module) {
  if (hookInstalled) {
    return;
  }
  hookInstalled = true;

  const getTrackCellRowIndex = makeTrackCellRowIndex(module);
  const getTrackGridCellAtWorldPosition = makeTrackGridCellLocator(module);

  if (HOOKS.attachment_probe || HOOKS.attachment_begin || HOOKS.attachment_follow_dispatch || HOOKS.attachment_end_callsite) {
    Interceptor.attach(fromVa(module, VA.update_subgoldy), {
      onEnter() {
        setCurrentUpdateSubgoldyState(this.context.ecx);
      },
      onLeave() {
        clearCurrentUpdateSubgoldyState();
      },
    });
  }

  emit('module_ready', {
    module: module.name,
    module_base: module.base.toString(),
    module_path: module.path,
  });

  if (HOOKS.level_start) {
    Interceptor.attach(fromVa(module, VA.normalize_level_runtime_fields), {
      onEnter(args) {
        this.game = this.context.ecx;
        this.level_descriptor = args[0];
        this.mode_before = safeReadU32(this.game, RUNTIME.mode_or_track);
      },
      onLeave(retval) {
        const snapshot = makeLevelRuntimeSnapshot(this.game);
        emit('level_start', {
          game: hex(this.game),
          level_descriptor: hex(this.level_descriptor),
          retval: retval.toInt32(),
          mode_before: this.mode_before,
          mode_after: safeReadU32(this.game, RUNTIME.mode_or_track),
          active_level_flag_0: snapshot.active_level_flag_0,
          active_level_flag_1: snapshot.active_level_flag_1,
          active_level_present: snapshot.active_level_present,
          selected_track_id: snapshot.selected_track_id,
          active_level: snapshot.active_level,
          build_flags: snapshot.build_flags,
          track_row_start: snapshot.track_row_start,
          track_row_end: snapshot.track_row_end,
          garbage_scalar: snapshot.garbage_scalar,
          salt_scalar: snapshot.salt_scalar,
        });
      },
    });
  }

  if (HOOKS.path_lookup) {
    Interceptor.attach(fromVa(module, VA.find_segment_path_index_by_name), {
      onEnter(args) {
        this.path_name_raw = safeReadCString(args[0], 96);
        this.path_name_sanitized = safeReadAsciiToken(args[0], 64);
      },
      onLeave(retval) {
        const pathIndex = retval.toInt32();
        const canonicalPathName = canonicalPathNameFromIndex(pathIndex);
        emit('path_lookup', {
          path_name:
            canonicalPathName !== null
              ? canonicalPathName
              : this.path_name_sanitized !== null
                ? this.path_name_sanitized
                : this.path_name_raw,
          path_name_raw: this.path_name_raw,
          path_name_sanitized: this.path_name_sanitized,
          path_name_from_index: canonicalPathName,
          path_index: pathIndex,
        });
      },
    });
  }

  if (HOOKS.movement_flags_update) {
    Interceptor.attach(fromVa(module, VA.update_player_movement_flags), {
      onEnter() {
        this.player = asPtr(this.context.ecx);
        this.before = summarizePlayer(this.player, getTrackCellRowIndex);
      },
      onLeave(retval) {
        const after = summarizePlayer(this.player, getTrackCellRowIndex);
        if (after === null) {
          return;
        }

        const digest = JSON.stringify({
          selector: after.movement_flag_selector,
          flags: after.movement_flags,
          previous: after.previous_movement_flags,
          rate: after.movement_rate_scalar,
        });

        maybeEmitSampled('movement_flags_update', after.ptr || 'player', digest, 8, {
          retval: retval.toInt32(),
          player: after.ptr,
          game: after.game,
          level_mode: after.level_mode,
          level_mode_arg: after.level_mode_arg,
          track_center_x: after.track_center_x,
          track_state_latch: after.track_state_latch,
          replay_active: after.replay_active,
          replay_track_index: after.replay_track_index,
          player_position: after.position,
          movement_state: after.movement_state,
          movement_flag_selector: after.movement_flag_selector,
          movement_flags: after.movement_flags,
          previous_movement_flags: after.previous_movement_flags,
          movement_progress: after.movement_progress,
          movement_rate_scalar: after.movement_rate_scalar,
          track_z_offset: after.track_z_offset,
          track_z_anchor: after.track_z_anchor,
          movement_mode_selector: after.movement_mode_selector,
          row_event_id: after.row_event_id,
          row_event_state: after.row_event_state,
          row_event_timer: after.row_event_timer,
          row_event_data_a: after.row_event_data_a,
          row_event_data_b: after.row_event_data_b,
          before_cell: this.before !== null ? this.before.cell : null,
          cell: after.cell,
        });
      },
    });
  }

  if (HOOKS.player_update) {
    Interceptor.attach(fromVa(module, VA.update_subgoldy), {
      onEnter(args) {
        this.player = asPtr(this.context.ecx);
        this.before = summarizePlayer(this.player, getTrackCellRowIndex);
        this.beforeSampledCell =
          getTrackGridCellAtWorldPosition !== null && this.before !== null && this.before.game !== null
            ? summarizeCell(getTrackGridCellAtWorldPosition(asPtr(this.before.game), this.player.add(0x68)), getTrackCellRowIndex, asPtr(this.before.game))
            : null;
      },
      onLeave() {
        const after = summarizePlayer(this.player, getTrackCellRowIndex);
        if (after === null) {
          return;
        }

        const currentSampledCell =
          getTrackGridCellAtWorldPosition !== null && after.game !== null
            ? summarizeCell(getTrackGridCellAtWorldPosition(asPtr(after.game), this.player.add(0x68)), getTrackCellRowIndex, asPtr(after.game))
            : null;

        const digest = JSON.stringify({
          row: currentSampledCell ? currentSampledCell.row : after.cell ? after.cell.row : null,
          tile: currentSampledCell ? currentSampledCell.tile_type : after.cell ? after.cell.tile_type : null,
          attachment_active: after.attachment_active,
          sample_index: after.follow_sample_index,
          movement_state: after.movement_state,
          movement_flags: after.movement_flags,
        });

        maybeEmitSampled('player_update', after.ptr || 'player', digest, 8, {
          player: after.ptr,
          game: after.game,
          build_flags: after.build_flags,
          level_mode: after.level_mode,
          level_mode_arg: after.level_mode_arg,
          track_center_x: after.track_center_x,
          track_state_latch: after.track_state_latch,
          replay_active: after.replay_active,
          replay_track_index: after.replay_track_index,
          player_position: after.position,
          before_position: this.before ? this.before.position : null,
          cell: currentSampledCell !== null ? currentSampledCell : after.cell,
          before_cell: this.beforeSampledCell !== null ? this.beforeSampledCell : this.before ? this.before.cell : null,
          raw_cell: after.cell,
          before_raw_cell: this.before ? this.before.cell : null,
          velocity: after.velocity,
          cached_track_pair_cell_a: after.cached_track_pair_cell_a,
          cached_track_pair_cell_b: after.cached_track_pair_cell_b,
          attachment_active: after.attachment_active,
          attachment_active_before: this.before ? this.before.attachment_active : null,
          follow_state: after.follow_state,
          follow_state_summary: summarizeFollowState(this.player !== null ? this.player.add(0x384) : null, getTrackCellRowIndex),
          follow_sample_index: after.follow_sample_index,
          follow_progress: after.follow_progress,
          movement_state: after.movement_state,
          movement_flag_selector: after.movement_flag_selector,
          movement_flags: after.movement_flags,
          previous_movement_flags: after.previous_movement_flags,
          movement_progress: after.movement_progress,
          movement_rate_scalar: after.movement_rate_scalar,
          track_z_offset: after.track_z_offset,
          track_z_anchor: after.track_z_anchor,
          movement_mode_selector: after.movement_mode_selector,
          row_event_id: after.row_event_id,
          row_event_state: after.row_event_state,
          row_event_timer: after.row_event_timer,
          row_event_data_a: after.row_event_data_a,
          row_event_data_b: after.row_event_data_b,
          attachment_exit_pending: after.attachment_exit_pending,
          attachment_exit_anchor_z: after.attachment_exit_anchor_z,
          post_follow_value_a: after.post_follow_value_a,
          post_follow_value_b: after.post_follow_value_b,
          attachment_exit_progress: after.attachment_exit_progress,
          attachment_exit_progress_step: after.attachment_exit_progress_step,
          follow_effect_gate_a: after.follow_effect_gate_a,
          follow_effect_gate_b: after.follow_effect_gate_b,
        });
      },
    });
  }

  if (HOOKS.completion_handoff_arm) {
    Interceptor.attach(fromVa(module, VA.completion_handoff_active_arm), {
      onEnter() {
        const player = asPtr(this.context.ebp);
        emit('completion_handoff_arm', {
          player: hex(player),
          game: hex(safeReadPointer(player, 0x408)),
          mode: safeReadU32(player, 0x2970),
          lives: safeReadU32(player, 0x4340),
          completion_handoff: summarizeCompletionHandoff(player),
          app: summarizeAppState(getAppPtr(module)),
        });
      },
    });
  }

  if (HOOKS.completion_screen_init) {
    const completionInitReturn = fromVa(module, 0x446c03);
    Interceptor.attach(fromVa(module, VA.initialize_completion_screen_entry), {
      onEnter(args) {
        const returnAddress = safeReadPointer(this.context.esp, 0);
        if (returnAddress === null || !returnAddress.equals(completionInitReturn)) {
          return;
        }

        const completionPayload = asPtr(args[0]);
        const player =
          completionPayload !== null && !completionPayload.isNull() ? completionPayload.sub(0x4338) : null;
        emit('completion_screen_init', {
          return_to: '0x446c03',
          init_owner: hex(this.context.ecx),
          completion_payload: hex(completionPayload),
          completion_flag: args[1].toInt32(),
          player: hex(player),
          game: hex(safeReadPointer(player, 0x408)),
          mode: safeReadU32(player, 0x2970),
          lives: safeReadU32(player, 0x4340),
          completion_handoff: summarizeCompletionHandoff(player),
          app: summarizeAppState(getAppPtr(module)),
        });
      },
    });
  }

  if (HOOKS.complete_subgame_call) {
    const completeSubgameReturns = {
      [fromVa(module, 0x43c986).toString()]: '0x43c981',
      [fromVa(module, 0x43c9b4).toString()]: '0x43c9af',
      [fromVa(module, 0x43c9cd).toString()]: '0x43c9c8',
    };

    Interceptor.attach(fromVa(module, VA.complete_subgame_entry), {
      onEnter(args) {
        const returnAddress = safeReadPointer(this.context.esp, 0);
        const callsite = returnAddress !== null ? completeSubgameReturns[returnAddress.toString()] : null;
        if (!callsite) {
          return;
        }

        emit('complete_subgame_call', {
          callsite: callsite,
          return_to: hex(returnAddress),
          game: hex(this.context.ecx),
          arg0: args[0].toInt32(),
          app: summarizeAppState(getAppPtr(module)),
        });
      },
    });
  }

  if (HOOKS.death_handoff_cutscene) {
    Interceptor.attach(fromVa(module, VA.death_handoff_via_cutscene), {
      onEnter() {
        const player = asPtr(this.context.ecx);
        emit('death_handoff_cutscene', {
          source: 'update_cutscene',
          player: hex(player),
          game: hex(safeReadPointer(player, 0x408)),
          mode: safeReadU32(player, 0x2970),
          lives: safeReadU32(player, 0x4340),
          world_y: safeReadFloat(player, 0x6c),
          world_z: safeReadFloat(player, 0x70),
          death_flag84: boolFlag(safeReadU8(player, 0x84)),
          exit_pending: boolFlag(safeReadU8(player, 0x41d)),
          gate_a: boolFlag(safeReadU8(player, 0x44c)),
          gate_b: boolFlag(safeReadU8(player, 0x44d)),
          app: summarizeAppState(getAppPtr(module)),
        });
      },
    });
  }

  if (HOOKS.death_handoff_update) {
    Interceptor.attach(fromVa(module, VA.death_handoff_via_update_subgoldy), {
      onEnter() {
        const player = asPtr(this.context.ebp);
        emit('death_handoff_update', {
          player: hex(player),
          game: hex(safeReadPointer(player, 0x408)),
          mode: safeReadU32(player, 0x2970),
          lives: safeReadU32(player, 0x4340),
          world_y: safeReadFloat(player, 0x6c),
          world_z: safeReadFloat(player, 0x70),
          movement_state: safeReadU32(player, 0x2984),
          death_flag84: boolFlag(safeReadU8(player, 0x84)),
          exit_pending: boolFlag(safeReadU8(player, 0x41d)),
          gate_a: boolFlag(safeReadU8(player, 0x44c)),
          gate_b: boolFlag(safeReadU8(player, 0x44d)),
          app: summarizeAppState(getAppPtr(module)),
        });
      },
    });
  }

  if (HOOKS.death_select_respawn || HOOKS.death_select_final_loss) {
    Interceptor.attach(fromVa(module, VA.death_select_state_set), {
      onEnter(args) {
        const player = asPtr(this.context.ecx);
        const finalLoss = args[0].toInt32();
        const payload = {
          player: hex(player),
          game: hex(safeReadPointer(player, 0x408)),
          mode: safeReadU32(player, 0x2970),
          lives: safeReadU32(player, 0x4340),
          world_y: safeReadFloat(player, 0x6c),
          world_z: safeReadFloat(player, 0x70),
          final_loss: finalLoss,
          app: summarizeAppState(getAppPtr(module)),
        };

        if (finalLoss === 0) {
          if (HOOKS.death_select_respawn) {
            emit('death_select_respawn', payload);
          }
          return;
        }

        if (finalLoss === 1 && HOOKS.death_select_final_loss) {
          emit('death_select_final_loss', payload);
        }
      },
    });
  }

  if (HOOKS.respawn_enter) {
    Interceptor.attach(fromVa(module, VA.update_subgoldy_resurrect_enter), {
      onEnter() {
        const player = asPtr(this.context.ecx);
        emit('respawn_enter', {
          player: hex(player),
          game: hex(safeReadPointer(player, 0x408)),
          mode: safeReadU32(player, 0x2970),
          lives: safeReadU32(player, 0x4340),
          final_loss: safeReadU32(player, 0x80),
          death_flag84: boolFlag(safeReadU8(player, 0x84)),
          respawn_progress: safeReadFloat(player, 0x8c),
          respawn_progress_step: safeReadFloat(player, 0x90),
          game_fade: safeReadU32(safeReadPointer(player, 0x408), 0xc),
          app: summarizeAppState(getAppPtr(module)),
        });
      },
    });
  }

  if (HOOKS.respawn_life_decrement) {
    Interceptor.attach(fromVa(module, VA.respawn_life_decrement), {
      onEnter() {
        const player = asPtr(this.context.esi);
        emit('respawn_life_decrement', {
          player: hex(player),
          game: hex(safeReadPointer(player, 0x408)),
          mode: safeReadU32(player, 0x2970),
          lives_before: safeReadU32(player, 0x4340),
          respawn_progress: safeReadFloat(player, 0x8c),
          game_fade: safeReadU32(safeReadPointer(player, 0x408), 0x24),
          final_loss: safeReadU32(player, 0x80),
          app: summarizeAppState(getAppPtr(module)),
        });
      },
    });
  }

  if (HOOKS.respawn_complete_subgame_branch) {
    Interceptor.attach(fromVa(module, VA.respawn_complete_subgame_branch), {
      onEnter() {
        const player = asPtr(this.context.esi);
        emit('respawn_complete_subgame_branch', {
          player: hex(player),
          game: hex(safeReadPointer(player, 0x408)),
          mode: safeReadU32(player, 0x2970),
          lives: safeReadU32(player, 0x4340),
          respawn_progress: safeReadFloat(player, 0x8c),
          game_fade: safeReadU32(safeReadPointer(player, 0x408), 0x24),
          final_loss: safeReadU32(player, 0x80),
          app: summarizeAppState(getAppPtr(module)),
        });
      },
    });
  }

  if (HOOKS.track_pair_payload) {
    Interceptor.attach(fromVa(module, VA.mark_current_track_pair_with_payload), {
      onEnter(args) {
        const player = asPtr(this.context.ecx);
        const playerSummary = summarizePlayer(player, getTrackCellRowIndex);
        const payload = floatArg(args[0]);
        const digest = JSON.stringify({
          payload: payload,
          row_a:
            playerSummary !== null && playerSummary.cached_track_pair_cell_a !== null
              ? playerSummary.cached_track_pair_cell_a.row
              : null,
          row_b:
            playerSummary !== null && playerSummary.cached_track_pair_cell_b !== null
              ? playerSummary.cached_track_pair_cell_b.row
              : null,
        });

        maybeEmitSampled('track_pair_payload', playerSummary !== null ? playerSummary.ptr : hex(player), digest, 4, {
          player: playerSummary !== null ? playerSummary.ptr : hex(player),
          player_position: playerSummary !== null ? playerSummary.position : null,
          movement_state: playerSummary !== null ? playerSummary.movement_state : null,
          movement_flag_selector: playerSummary !== null ? playerSummary.movement_flag_selector : null,
          movement_flags: playerSummary !== null ? playerSummary.movement_flags : null,
          movement_progress: playerSummary !== null ? playerSummary.movement_progress : null,
          track_z_offset: playerSummary !== null ? playerSummary.track_z_offset : null,
          track_z_anchor: playerSummary !== null ? playerSummary.track_z_anchor : null,
          track_state_latch: playerSummary !== null ? playerSummary.track_state_latch : null,
          pair_payload: payload,
          pair_cell_a: playerSummary !== null ? playerSummary.cached_track_pair_cell_a : null,
          pair_cell_b: playerSummary !== null ? playerSummary.cached_track_pair_cell_b : null,
        });
      },
    });
  }

  if (HOOKS.attachment_probe) {
    ATTACHMENT_PROBE_SITES.forEach(function (site) {
      Interceptor.attach(fromVa(module, site.va), {
        onEnter() {
          const player = asPtr(this.context.ebp);
          const playerSummary = summarizePlayer(player, getTrackCellRowIndex);
          const updateState = getCurrentUpdateSubgoldyState();
          const probe = {
            callsite: site.callsite,
            return_to: site.return_to,
            lane_flag: site.lane_flag,
            update_seq: updateState !== null ? updateState.seq : null,
            player: playerSummary !== null ? playerSummary.ptr : hex(player),
            game: playerSummary !== null ? playerSummary.game : hex(safeReadPointer(player, 0x408)),
            build_flags: playerSummary !== null ? playerSummary.build_flags : null,
            template: hex(this.context.ecx),
            template_summary: summarizeAttachmentTemplate(this.context.ecx),
            player_position: playerSummary !== null ? playerSummary.position : safeReadVec3(player, 0x68),
            cell: playerSummary !== null ? playerSummary.cell : null,
            attachment_active: playerSummary !== null ? playerSummary.attachment_active : null,
            attachment_exit_pending: playerSummary !== null ? playerSummary.attachment_exit_pending : null,
            attachment_exit_progress: playerSummary !== null ? playerSummary.attachment_exit_progress : null,
            post_follow_value_a: playerSummary !== null ? playerSummary.post_follow_value_a : null,
            post_follow_value_b: playerSummary !== null ? playerSummary.post_follow_value_b : null,
            follow_effect_gate_a: playerSummary !== null ? playerSummary.follow_effect_gate_a : null,
            follow_effect_gate_b: playerSummary !== null ? playerSummary.follow_effect_gate_b : null,
            movement_flags: playerSummary !== null ? playerSummary.movement_flags : null,
            movement_progress: playerSummary !== null ? playerSummary.movement_progress : null,
          };

          rememberAttachmentProbe(player, {
            callsite: probe.callsite,
            return_to: probe.return_to,
            lane_flag: probe.lane_flag,
            update_seq: probe.update_seq,
          });
          emit('attachment_probe', probe);
        },
      });
    });
  }

  if (HOOKS.attachment_follow_dispatch) {
    Interceptor.attach(fromVa(module, 0x43b99d), {
      onEnter() {
        const player = asPtr(this.context.ebp);
        const playerSummary = summarizePlayer(player, getTrackCellRowIndex);
        const updateState = getCurrentUpdateSubgoldyState();
        emit('attachment_follow_dispatch', {
          callsite: '0x43b99d',
          update_seq: updateState !== null ? updateState.seq : null,
          retval: this.context.eax.toInt32(),
          player: playerSummary !== null ? playerSummary.ptr : hex(player),
          game: playerSummary !== null ? playerSummary.game : hex(safeReadPointer(player, 0x408)),
          build_flags: playerSummary !== null ? playerSummary.build_flags : null,
          player_position: playerSummary !== null ? playerSummary.position : safeReadVec3(player, 0x68),
          cell: playerSummary !== null ? playerSummary.cell : null,
          attachment_active: playerSummary !== null ? playerSummary.attachment_active : null,
          attachment_exit_pending: playerSummary !== null ? playerSummary.attachment_exit_pending : null,
          attachment_exit_progress: playerSummary !== null ? playerSummary.attachment_exit_progress : null,
          post_follow_value_a: playerSummary !== null ? playerSummary.post_follow_value_a : null,
          post_follow_value_b: playerSummary !== null ? playerSummary.post_follow_value_b : null,
          follow_effect_gate_a: playerSummary !== null ? playerSummary.follow_effect_gate_a : null,
          follow_effect_gate_b: playerSummary !== null ? playerSummary.follow_effect_gate_b : null,
        });
      },
    });
  }

  if (HOOKS.attachment_end_callsite) {
    ATTACHMENT_END_CALLSITES.forEach(function (site) {
      Interceptor.attach(fromVa(module, site.va), {
        onEnter() {
          const player = asPtr(this.context.ebp);
          const playerSummary = summarizePlayer(player, getTrackCellRowIndex);
          const updateState = getCurrentUpdateSubgoldyState();
          emit('attachment_end_callsite', {
            callsite: site.callsite,
            update_seq: updateState !== null ? updateState.seq : null,
            player: playerSummary !== null ? playerSummary.ptr : hex(player),
            player_position: playerSummary !== null ? playerSummary.position : safeReadVec3(player, 0x68),
            cell: playerSummary !== null ? playerSummary.cell : null,
            attachment_active: playerSummary !== null ? playerSummary.attachment_active : null,
            attachment_exit_pending: playerSummary !== null ? playerSummary.attachment_exit_pending : null,
            attachment_exit_progress: playerSummary !== null ? playerSummary.attachment_exit_progress : null,
            post_follow_value_a: playerSummary !== null ? playerSummary.post_follow_value_a : null,
            post_follow_value_b: playerSummary !== null ? playerSummary.post_follow_value_b : null,
            follow_effect_gate_a: playerSummary !== null ? playerSummary.follow_effect_gate_a : null,
            follow_effect_gate_b: playerSummary !== null ? playerSummary.follow_effect_gate_b : null,
          });
        },
      });
    });
  }

  if (HOOKS.attachment_begin) {
    Interceptor.attach(fromVa(module, VA.begin_track_attachment_follow_state), {
      onEnter(args) {
        const updateState = getCurrentUpdateSubgoldyState();
        const recentProbes = getRecentAttachmentProbes(args[2], updateState !== null ? updateState.seq : null);
        const follow = summarizeFollowState(this.context.ecx, getTrackCellRowIndex);
        emit('attachment_begin', {
          update_seq: updateState !== null ? updateState.seq : null,
          follow_state: follow !== null ? follow.ptr : hex(this.context.ecx),
          follow_state_summary: follow,
          template: follow !== null ? follow.template : null,
          template_summary: follow !== null ? follow.template_summary : null,
          build_flags: safeReadU32(safeReadPointer(args[2], 0x408), RUNTIME.build_flags),
          cell: summarizeCell(args[0], getTrackCellRowIndex, safeReadPointer(args[2], 0x408)),
          player_position: safeReadVec3(args[1], 0),
          player: hex(args[2]),
          recent_attachment_probes: recentProbes,
          attachment_active: follow !== null ? follow.active : null,
          follow_sample_index: follow !== null ? follow.sample_index : null,
          follow_progress: follow !== null ? follow.progress : null,
        });
      },
    });
  }

  if (HOOKS.attachment_update) {
    Interceptor.attach(fromVa(module, VA.update_track_attachment_follow_state), {
      onEnter(args) {
        this.followState = this.context.ecx;
        this.playerPositionPtr = args[1];
        this.motionPtr = args[2];
        this.pathFactor = args[0];
      },
      onLeave(retval) {
        const follow = summarizeFollowState(this.followState, getTrackCellRowIndex);
        const digest = JSON.stringify({
          row: follow && follow.cell ? follow.cell.row : null,
          tile: follow && follow.cell ? follow.cell.tile_type : null,
          sample_index: follow ? follow.sample_index : null,
          progress: follow ? follow.progress : null,
          retval: retval.toInt32(),
        });

        maybeEmitSampled('attachment_update', follow !== null ? follow.ptr : hex(this.followState), digest, 2, {
          follow_state: follow !== null ? follow.ptr : hex(this.followState),
          follow_state_summary: follow,
          template: follow !== null ? follow.template : null,
          template_summary: follow !== null ? follow.template_summary : null,
          build_flags: safeReadU32(safeReadPointer(follow !== null ? follow.player : null, 0x408), RUNTIME.build_flags),
          cell: follow !== null ? follow.cell : null,
          player: follow !== null ? follow.player : null,
          player_position: safeReadVec3(this.playerPositionPtr, 0),
          velocity: safeReadVec3(this.motionPtr, 0),
          attachment_active: follow !== null ? follow.active : null,
          follow_sample_index: follow !== null ? follow.sample_index : null,
          follow_progress: follow !== null ? follow.progress : null,
          effect_scale: floatArg(this.pathFactor),
          retval: retval.toInt32(),
        });
      },
    });
  }

  if (HOOKS.attachment_end) {
    Interceptor.attach(fromVa(module, VA.end_track_attachment_follow_state), {
      onEnter() {
        this.player = asPtr(this.context.ecx);
        this.before = summarizePlayer(this.player, getTrackCellRowIndex);
        this.beforeSampledCell =
          getTrackGridCellAtWorldPosition !== null && this.before !== null && this.before.game !== null
            ? summarizeCell(getTrackGridCellAtWorldPosition(asPtr(this.before.game), this.player.add(0x68)), getTrackCellRowIndex, asPtr(this.before.game))
            : null;
        this.beforeFollow = summarizeFollowState(this.player !== null ? this.player.add(0x384) : null, getTrackCellRowIndex);
      },
      onLeave(retval) {
        const after = summarizePlayer(this.player, getTrackCellRowIndex);
        const afterFollow = summarizeFollowState(this.player !== null ? this.player.add(0x384) : null, getTrackCellRowIndex);
        const afterSampledCell =
          getTrackGridCellAtWorldPosition !== null && after !== null && after.game !== null
            ? summarizeCell(getTrackGridCellAtWorldPosition(asPtr(after.game), this.player.add(0x68)), getTrackCellRowIndex, asPtr(after.game))
            : null;

        emit('attachment_end', {
          retval: retval.toInt32(),
          player: after !== null ? after.ptr : this.before !== null ? this.before.ptr : hex(this.player),
          build_flags:
            after !== null
              ? after.build_flags
              : this.before !== null
                ? this.before.build_flags
                : safeReadU32(safeReadPointer(this.player, 0x408), RUNTIME.build_flags),
          player_position: after !== null ? after.position : null,
          before_position: this.before !== null ? this.before.position : null,
          cell: afterSampledCell !== null ? afterSampledCell : after !== null ? after.cell : null,
          before_cell: this.beforeSampledCell !== null ? this.beforeSampledCell : this.before !== null ? this.before.cell : null,
          raw_cell: after !== null ? after.cell : null,
          before_raw_cell: this.before !== null ? this.before.cell : null,
          attachment_active: after !== null ? after.attachment_active : null,
          attachment_active_before: this.before !== null ? this.before.attachment_active : null,
          follow_state: afterFollow !== null ? afterFollow.ptr : after !== null ? after.follow_state : null,
          follow_state_summary: afterFollow,
          before_follow_state: this.beforeFollow !== null ? this.beforeFollow.ptr : this.before !== null ? this.before.follow_state : null,
          before_follow_state_summary: this.beforeFollow,
          template: afterFollow !== null ? afterFollow.template : null,
          template_summary: afterFollow !== null ? afterFollow.template_summary : null,
          before_template: this.beforeFollow !== null ? this.beforeFollow.template : null,
          before_template_summary: this.beforeFollow !== null ? this.beforeFollow.template_summary : null,
          follow_sample_index: afterFollow !== null ? afterFollow.sample_index : after !== null ? after.follow_sample_index : null,
          before_follow_sample_index:
            this.beforeFollow !== null ? this.beforeFollow.sample_index : this.before !== null ? this.before.follow_sample_index : null,
          follow_progress: afterFollow !== null ? afterFollow.progress : after !== null ? after.follow_progress : null,
          before_follow_progress:
            this.beforeFollow !== null ? this.beforeFollow.progress : this.before !== null ? this.before.follow_progress : null,
          movement_state: after !== null ? after.movement_state : this.before !== null ? this.before.movement_state : null,
          movement_flag_selector: after !== null ? after.movement_flag_selector : this.before !== null ? this.before.movement_flag_selector : null,
          movement_flags: after !== null ? after.movement_flags : this.before !== null ? this.before.movement_flags : null,
          previous_movement_flags: after !== null ? after.previous_movement_flags : this.before !== null ? this.before.previous_movement_flags : null,
          movement_progress: after !== null ? after.movement_progress : this.before !== null ? this.before.movement_progress : null,
          movement_rate_scalar: after !== null ? after.movement_rate_scalar : this.before !== null ? this.before.movement_rate_scalar : null,
          track_z_offset: after !== null ? after.track_z_offset : this.before !== null ? this.before.track_z_offset : null,
          track_z_anchor: after !== null ? after.track_z_anchor : this.before !== null ? this.before.track_z_anchor : null,
          movement_mode_selector: after !== null ? after.movement_mode_selector : this.before !== null ? this.before.movement_mode_selector : null,
          level_mode: after !== null ? after.level_mode : this.before !== null ? this.before.level_mode : null,
          level_mode_arg: after !== null ? after.level_mode_arg : this.before !== null ? this.before.level_mode_arg : null,
          track_center_x: after !== null ? after.track_center_x : this.before !== null ? this.before.track_center_x : null,
          track_state_latch: after !== null ? after.track_state_latch : this.before !== null ? this.before.track_state_latch : null,
          replay_active: after !== null ? after.replay_active : this.before !== null ? this.before.replay_active : null,
          replay_track_index: after !== null ? after.replay_track_index : this.before !== null ? this.before.replay_track_index : null,
          row_event_id: after !== null ? after.row_event_id : this.before !== null ? this.before.row_event_id : null,
          row_event_state: after !== null ? after.row_event_state : this.before !== null ? this.before.row_event_state : null,
          row_event_timer: after !== null ? after.row_event_timer : this.before !== null ? this.before.row_event_timer : null,
          row_event_data_a: after !== null ? after.row_event_data_a : this.before !== null ? this.before.row_event_data_a : null,
          row_event_data_b: after !== null ? after.row_event_data_b : this.before !== null ? this.before.row_event_data_b : null,
          attachment_exit_pending: after !== null ? after.attachment_exit_pending : null,
          attachment_exit_anchor_z: after !== null ? after.attachment_exit_anchor_z : null,
          post_follow_value_a: after !== null ? after.post_follow_value_a : null,
          post_follow_value_b: after !== null ? after.post_follow_value_b : null,
          attachment_exit_progress: after !== null ? after.attachment_exit_progress : null,
          attachment_exit_progress_step: after !== null ? after.attachment_exit_progress_step : null,
          follow_effect_gate_a: after !== null ? after.follow_effect_gate_a : null,
          follow_effect_gate_b: after !== null ? after.follow_effect_gate_b : null,
        });
      },
    });
  }

  if (HOOKS.floor_sample) {
    Interceptor.attach(fromVa(module, VA.sample_track_floor_height_at_position), {
      onEnter(args) {
        this.game = this.context.ecx;
        this.positionPtr = args[0];
      },
      onLeave() {
        const position = safeReadVec3(this.positionPtr, 0);
        const cell =
          getTrackGridCellAtWorldPosition !== null && this.game !== null
            ? summarizeCell(getTrackGridCellAtWorldPosition(this.game, this.positionPtr), getTrackCellRowIndex, this.game)
            : null;
        const digest = JSON.stringify({
          row: cell ? cell.row : null,
          tile: cell ? cell.tile_type : null,
          z: position ? position.z : null,
        });
        maybeEmitSampled('floor_sample', hex(this.positionPtr), digest, 16, {
          game: hex(this.game),
          build_flags: safeReadU32(this.game, RUNTIME.build_flags),
          level_mode: safeReadU32(this.game, RUNTIME.level_mode),
          level_mode_arg: safeReadU32(this.game, RUNTIME.level_mode_arg),
          track_center_x: safeReadFloat(this.game, RUNTIME.track_center_x),
          track_state_latch: safeReadU8(this.game, RUNTIME.track_state_latch),
          replay_active: boolFlag(safeReadU8(this.game, RUNTIME.active_level_flag_0)),
          replay_track_index: safeReadU32(this.game, RUNTIME.replay_track_index),
          position: position,
          cell: cell,
          sampled_floor_height: computeSampledFloorHeight(cell, position),
        });
      },
    });
  }

  if (HOOKS.garbage_spawn) {
    Interceptor.attach(fromVa(module, VA.spawn_track_garbage_hazard), {
      onEnter(args) {
        emit('garbage_spawn', {
          game: hex(this.context.ecx),
          build_flags: safeReadU32(this.context.ecx, RUNTIME.build_flags),
          cell: summarizeCell(args[0], getTrackCellRowIndex, this.context.ecx),
          manager: hex(args[1]),
          manager_sprite_bank: safeReadPointer(args[1], 896) !== null ? hex(safeReadPointer(args[1], 896)) : null,
        });
      },
    });
  }

  if (HOOKS.health_pickup) {
    Interceptor.attach(fromVa(module, VA.spawn_track_health_pickup), {
      onEnter(args) {
        emit('health_pickup', {
          game: hex(this.context.ecx),
          build_flags: safeReadU32(this.context.ecx, RUNTIME.build_flags),
          cell: summarizeCell(args[0], getTrackCellRowIndex, this.context.ecx),
          manager: hex(args[1]),
        });
      },
    });
  }

  if (HOOKS.jetpack_pickup) {
    Interceptor.attach(fromVa(module, VA.spawn_track_jetpack_pickup), {
      onEnter(args) {
        emit('jetpack_pickup', {
          game: hex(this.context.ecx),
          build_flags: safeReadU32(this.context.ecx, RUNTIME.build_flags),
          cell: summarizeCell(args[0], getTrackCellRowIndex, this.context.ecx),
          manager: hex(args[1]),
        });
      },
    });
  }

  if (HOOKS.ring_effect) {
    Interceptor.attach(fromVa(module, VA.spawn_track_ring_or_special_effect), {
      onEnter(args) {
        emit('ring_effect', {
          game: hex(this.context.ecx),
          build_flags: safeReadU32(this.context.ecx, RUNTIME.build_flags),
          cell: summarizeCell(args[0], getTrackCellRowIndex, this.context.ecx),
          effect_kind: args[1].toInt32(),
          manager: hex(args[2]),
          effect_scale: floatArg(args[3]),
        });
      },
    });
  }

  if (HOOKS.salt_spawn) {
    Interceptor.attach(fromVa(module, VA.spawn_salt_runtime_entity), {
      onEnter(args) {
        this.slot_manager = this.context.ecx;
        this.position = safeReadVec3(args[0], 0);
      },
      onLeave(retval) {
        emit('salt_spawn', {
          slot_manager: hex(this.slot_manager),
          position: this.position,
          slot_result: retval.toInt32(),
        });
      },
    });
  }

  if (HOOKS.salt_update) {
    Interceptor.attach(fromVa(module, VA.update_salt_hazard), {
      onEnter(args) {
        const slot = fastcallArg0(args, this.context);
        const position = safeReadVec3(slot, 104);
        const state = safeReadU32(slot, 128);
        const digest = JSON.stringify({
          state: state,
          x: position !== null ? position.x : null,
          y: position !== null ? position.y : null,
          z: position !== null ? position.z : null,
        });

        maybeEmitSampled('salt_update', hex(slot), digest, 8, {
          slot: hex(slot),
          state: state,
          position: position,
          velocity: safeReadVec3(slot, 140),
        });
      },
    });
  }

  if (HOOKS.salt_deactivate) {
    Interceptor.attach(fromVa(module, VA.deactivate_salt_runtime_entity), {
      onEnter(args) {
        const slot = this.context.ecx;
        emit('salt_deactivate', {
          slot: hex(slot),
          state: safeReadU32(slot, 128),
          position: safeReadVec3(slot, 104),
          velocity: safeReadVec3(slot, 140),
        });
      },
    });
  }

  if (HOOKS.slug_spawn) {
    Interceptor.attach(fromVa(module, VA.spawn_slug_runtime_entity), {
      onEnter(args) {
        emit('slug_spawn', {
          game: hex(this.context.ecx),
          build_flags: safeReadU32(this.context.ecx, RUNTIME.build_flags),
          cell: summarizeCell(args[0], getTrackCellRowIndex, this.context.ecx),
          manager: hex(args[1]),
          sprite_id: 0x76,
        });
      },
    });
  }

  emit('hooks_installed', {
    profile: TRACE_PROFILE,
    hooks: HOOKS,
  });
}

function waitForTargetModule() {
  const initial = findTargetModule();
  if (initial !== null) {
    installHooks(initial);
    return;
  }

  emit('waiting_for_module', {
    target_modules: TARGET_MODULE_NAMES,
  });

  const timer = setInterval(function () {
    const module = findTargetModule();
    if (module !== null) {
      clearInterval(timer);
      installHooks(module);
    }
  }, MODULE_POLL_MS);
}

waitForTargetModule();
