'use strict';

const TARGET_MODULE_NAMES = ['SnailMail_unwrapped.exe', 'SnailMail.RWG'];
const PREFERRED_IMAGE_BASE = 0x400000;
const MODULE_POLL_MS = 250;
const TRACE_OUTPUT_DIR = 'C:\\share\\snail\\frida';
const TRACE_OUTPUT_PREFIX = 'snailmail-trace';
const ERROR_ALREADY_EXISTS = 183;

const HOOKS = {
  level_start: true,
  path_lookup: true,
  player_update: true,
  attachment_probe: true,
  attachment_begin: true,
  attachment_update: true,
  attachment_end: true,
  floor_sample: true,
  garbage_spawn: true,
  health_pickup: true,
  jetpack_pickup: true,
  ring_effect: true,
  salt_spawn: true,
  salt_update: true,
  salt_deactivate: true,
  slug_spawn: true,
};

const LIMITS = {
  level_start: 128,
  path_lookup: 2048,
  player_update: 4096,
  attachment_probe: 4096,
  attachment_begin: 1024,
  attachment_update: 4096,
  attachment_end: 1024,
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
  find_segment_path_index_by_name: 0x429ae0,
  begin_track_attachment_follow_state: 0x420c40,
  update_track_attachment_follow_state: 0x420cb0,
  try_enter_track_attachment_from_swept_motion: 0x42c770,
  normalize_level_runtime_fields: 0x437eb0,
  end_track_attachment_follow_state: 0x43af60,
  update_player_track_movement_and_triggers: 0x43b120,
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
  mode_or_track: 0x40,
  build_flags: 0x4c,
  track_row_start: 0x50,
  track_row_end: 0x58,
  active_level_flag_0: 0xff25d0,
  active_level_flag_1: 0xff25d1,
  active_level_ptr: 0xff25d4,
  garbage_scalar: 0x125ffd8,
  salt_scalar: 0x125ffdc,
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
    return new NativeFunction(fromVa(module, VA.get_track_grid_cell_at_world_position), 'pointer', ['pointer', 'pointer'], 'fastcall');
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

function summarizeCell(cellPtr, getTrackCellRowIndex) {
  const cell = asPtr(cellPtr);
  if (cell === null || cell.isNull()) {
    return null;
  }

  let row = null;
  if (getTrackCellRowIndex !== null) {
    try {
      row = getTrackCellRowIndex(cell);
    } catch (_) {
      row = null;
    }
  }

  const attachment = safeReadPointer(cell, 56);
  return {
    ptr: hex(cell),
    row: row,
    flags: safeReadU32(cell, 4),
    tile_type: safeReadU8(cell, 60),
    world: safeReadVec3(cell, 16),
    attachment: hex(attachment),
    attachment_kind: safeReadU32(attachment, 56),
  };
}

function summarizeFollowState(followStatePtr, getTrackCellRowIndex) {
  const followState = asPtr(followStatePtr);
  if (followState === null || followState.isNull()) {
    return null;
  }

  return {
    ptr: hex(followState),
    active: boolFlag(safeReadU32(followState, 0)),
    template: hex(safeReadPointer(followState, 4)),
    cell: summarizeCell(safeReadPointer(followState, 8), getTrackCellRowIndex),
    sample_index: safeReadU32(followState, 0xc),
    progress: safeReadFloat(followState, 0x10),
    player: hex(safeReadPointer(followState, 0x38)),
  };
}

function summarizePlayer(playerPtr, getTrackCellRowIndex) {
  const player = asPtr(playerPtr);
  if (player === null || player.isNull()) {
    return null;
  }

  return {
    ptr: hex(player),
    game: hex(safeReadPointer(player, 0x408)),
    build_flags: safeReadU32(safeReadPointer(player, 0x408), RUNTIME.build_flags),
    position: safeReadVec3(player, 0x68),
    velocity: safeReadVec3(player, 0x410),
    cell: summarizeCell(safeReadPointer(player, 0x43c), getTrackCellRowIndex),
    attachment_active: boolFlag(safeReadU32(player, 0x384)),
    follow_state: hex(player.add(0x384)),
    follow_sample_index: safeReadU32(player, 0x390),
    follow_progress: safeReadFloat(player, 0x394),
    movement_state: safeReadU32(player, 0x120),
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

function installHooks(module) {
  if (hookInstalled) {
    return;
  }
  hookInstalled = true;

  const getTrackCellRowIndex = makeTrackCellRowIndex(module);
  const getTrackGridCellAtWorldPosition = makeTrackGridCellLocator(module);

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

  if (HOOKS.player_update) {
    Interceptor.attach(fromVa(module, VA.update_player_track_movement_and_triggers), {
      onEnter(args) {
        this.player = asPtr(this.context.ecx);
        this.before = summarizePlayer(this.player, getTrackCellRowIndex);
      },
      onLeave() {
        const after = summarizePlayer(this.player, getTrackCellRowIndex);
        if (after === null) {
          return;
        }

        const digest = JSON.stringify({
          row: after.cell ? after.cell.row : null,
          tile: after.cell ? after.cell.tile_type : null,
          attachment_active: after.attachment_active,
          sample_index: after.follow_sample_index,
          movement_state: after.movement_state,
        });

        maybeEmitSampled('player_update', after.ptr || 'player', digest, 8, {
          player: after.ptr,
          game: after.game,
          build_flags: after.build_flags,
          player_position: after.position,
          before_position: this.before ? this.before.position : null,
          cell: after.cell,
          before_cell: this.before ? this.before.cell : null,
          velocity: after.velocity,
          attachment_active: after.attachment_active,
          attachment_active_before: this.before ? this.before.attachment_active : null,
          follow_state: after.follow_state,
          follow_sample_index: after.follow_sample_index,
          follow_progress: after.follow_progress,
          movement_state: after.movement_state,
        });
      },
    });
  }

  if (HOOKS.attachment_probe) {
    Interceptor.attach(fromVa(module, VA.try_enter_track_attachment_from_swept_motion), {
      onEnter(args) {
        const cell = args[6];
        emit('attachment_probe', {
          template: hex(this.context.ecx),
          build_flags: safeReadU32(safeReadPointer(this.context.ecx, 0x408), RUNTIME.build_flags),
          cell: summarizeCell(cell, getTrackCellRowIndex),
          position: {
            x: floatArg(args[0]),
            y: floatArg(args[1]),
            z: floatArg(args[2]),
          },
          velocity: {
            x: floatArg(args[3]),
            y: floatArg(args[4]),
            z: floatArg(args[5]),
          },
        });
      },
    });
  }

  if (HOOKS.attachment_begin) {
    Interceptor.attach(fromVa(module, VA.begin_track_attachment_follow_state), {
      onEnter(args) {
        const follow = summarizeFollowState(this.context.ecx, getTrackCellRowIndex);
        emit('attachment_begin', {
          follow_state: follow !== null ? follow.ptr : hex(this.context.ecx),
          build_flags: safeReadU32(safeReadPointer(args[2], 0x408), RUNTIME.build_flags),
          cell: summarizeCell(args[0], getTrackCellRowIndex),
          player_position: safeReadVec3(args[1], 0),
          player: hex(args[2]),
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
        const player = asPtr(this.context.ecx);
        const before = summarizePlayer(player, getTrackCellRowIndex);
        const follow = summarizeFollowState(player !== null ? player.add(0x384) : null, getTrackCellRowIndex);
        emit('attachment_end', {
          player: before !== null ? before.ptr : hex(player),
          build_flags: before !== null ? before.build_flags : safeReadU32(safeReadPointer(player, 0x408), RUNTIME.build_flags),
          player_position: before !== null ? before.position : null,
          cell: follow !== null && follow.cell !== null ? follow.cell : before !== null ? before.cell : null,
          attachment_active: follow !== null ? follow.active : before !== null ? before.attachment_active : null,
          follow_state: follow !== null ? follow.ptr : before !== null ? before.follow_state : null,
          follow_sample_index: follow !== null ? follow.sample_index : before !== null ? before.follow_sample_index : null,
          follow_progress: follow !== null ? follow.progress : before !== null ? before.follow_progress : null,
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
            ? summarizeCell(getTrackGridCellAtWorldPosition(this.game, this.positionPtr), getTrackCellRowIndex)
            : null;
        const digest = JSON.stringify({
          row: cell ? cell.row : null,
          tile: cell ? cell.tile_type : null,
          z: position ? position.z : null,
        });
        maybeEmitSampled('floor_sample', hex(this.positionPtr), digest, 16, {
          game: hex(this.game),
          build_flags: safeReadU32(this.game, RUNTIME.build_flags),
          position: position,
          cell: cell,
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
          cell: summarizeCell(args[0], getTrackCellRowIndex),
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
          cell: summarizeCell(args[0], getTrackCellRowIndex),
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
          cell: summarizeCell(args[0], getTrackCellRowIndex),
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
          cell: summarizeCell(args[0], getTrackCellRowIndex),
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
          cell: summarizeCell(args[0], getTrackCellRowIndex),
          manager: hex(args[1]),
          sprite_id: 0x76,
        });
      },
    });
  }

  emit('hooks_installed', {
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
