'use strict';

const TARGET_MODULE_NAMES = ['SnailMail_unwrapped.exe', 'SnailMail.RWG'];
const PREFERRED_IMAGE_BASE = 0x400000;
const MODULE_POLL_MS = 250;
const TRACE_OUTPUT_DIR = 'C:\\share\\snail\\frida';
const TRACE_OUTPUT_PREFIX = 'snailmail-path-oracle';
const ERROR_ALREADY_EXISTS = 183;

const HOOKS = {
  level_start: true,
  path_lookup: true,
  attachment_install: true,
  attachment_projection: true,
  attachment_probe: true,
  attachment_begin: true,
  attachment_update: true,
  attachment_end: true,
  warp_transform: true,
};

const LIMITS = {
  level_start: 128,
  path_lookup: 2048,
  attachment_install_summary: 128,
  attachment_install_cell: 4096,
  attachment_projection: 4096,
  attachment_probe: 4096,
  attachment_begin: 2048,
  attachment_update: 8192,
  attachment_end: 2048,
  warp_transform: 4096,
};

const VA = {
  find_segment_path_index_by_name: 0x429ae0,
  begin_track_attachment_follow_state: 0x420c40,
  update_track_attachment_follow_state: 0x420cb0,
  try_enter_track_attachment_from_swept_motion: 0x42c770,
  compute_warp_attachment_transform: 0x42b920,
  normalize_level_runtime_fields: 0x437eb0,
  populate_runtime_track_cells_from_segments: 0x435eb0,
  end_track_attachment_follow_state: 0x43af60,
  project_position_onto_track_attachment: 0x4444b0,
  get_track_grid_cell_at_world_position: 0x43d410,
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
  build_flags: 0x4c,
  track_row_start: 0x50,
  track_row_end: 0x58,
  level_mode: 0x40,
  level_mode_arg: 0x44,
  replay_active: 0xff25d0,
  replay_track_ptr: 0xff25d4,
  bank_selector_byte: 0x2,
  path_bank_primary: 0xff2914,
  path_bank_secondary: 0xff29bc,
};

const TRACK_LAYOUT = {
  lane_count: 8,
  row_count: 0xc80,
  gameplay_grid_base: 0x3bfac8,
  gameplay_grid_stride: 0x54,
};

const ATTACHMENT = {
  installed_record_stride: 0x150,
  installed_record_count: SEGMENT_PATH_INDEX_NAMES.length,
  gameplay_cell_attachment_offset: 56,
  gameplay_cell_flags_offset: 4,
  gameplay_cell_tile_offset: 60,
  gameplay_cell_world_offset: 16,
  gameplay_cell_row_scalar_a_offset: 0x24,
  gameplay_cell_row_scalar_b_offset: 0x34,
  gameplay_cell_payload_offset: 0x50,
  template_kind_offset: 0x38,
  template_sample_count_offset: 0x44,
  template_width_offset: 0x54,
  template_primary_points_offset: 0x58,
  template_secondary_points_offset: 0x5c,
  template_row_scalar_offset: 0x98,
  template_special_flag_offset: 0x9c,
  sample_stride: 0xa8,
  sample_position_offset: 0x30,
  sample_delta_dir_offset: 0x80,
  sample_delta_length_offset: 0x8c,
  sample_center_x_offset: 0x90,
  sample_scalar_94_offset: 0x94,
  sample_scalar_98_offset: 0x98,
  sample_lateral_scale_offset: 0x9c,
  sample_warp_scalar_offset: 0xa0,
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
      console.log('[snailmail-path-oracle] writing NDJSON to ' + traceFilePath);
    }

    traceFile.write(line + '\n');
    traceFile.flush();
    return true;
  } catch (error) {
    traceFileError = String(error);
    console.error('[snailmail-path-oracle] file output disabled: ' + traceFileError);
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

  const gameplayGridBase = game.add(TRACK_LAYOUT.gameplay_grid_base);
  const gameplayGridBytes = TRACK_LAYOUT.row_count * TRACK_LAYOUT.lane_count * TRACK_LAYOUT.gameplay_grid_stride;
  const cellAddress = cell.toUInt32();
  const baseAddress = gameplayGridBase.toUInt32();

  if (cellAddress < baseAddress || cellAddress >= baseAddress + gameplayGridBytes) {
    return null;
  }

  const offset = cellAddress - baseAddress;
  if (offset % TRACK_LAYOUT.gameplay_grid_stride !== 0) {
    return null;
  }

  const index = Math.floor(offset / TRACK_LAYOUT.gameplay_grid_stride);
  return {
    row: Math.floor(index / TRACK_LAYOUT.lane_count),
    lane: index % TRACK_LAYOUT.lane_count,
  };
}

function laneCenterX(lane) {
  if (lane === null || lane === undefined) {
    return null;
  }
  return roundFloat(lane - 3.5);
}

function summarizeAttachmentSample(arrayPtr, sampleIndex) {
  const array = asPtr(arrayPtr);
  if (array === null || array.isNull() || sampleIndex === null || sampleIndex === undefined || sampleIndex < 0) {
    return null;
  }

  const sample = array.add(sampleIndex * ATTACHMENT.sample_stride);
  return {
    ptr: hex(sample),
    position: safeReadVec3(sample, ATTACHMENT.sample_position_offset),
    delta_dir_to_next: safeReadVec3(sample, ATTACHMENT.sample_delta_dir_offset),
    delta_length: safeReadFloat(sample, ATTACHMENT.sample_delta_length_offset),
    center_x: safeReadFloat(sample, ATTACHMENT.sample_center_x_offset),
    scalar_94: safeReadFloat(sample, ATTACHMENT.sample_scalar_94_offset),
    scalar_98: safeReadFloat(sample, ATTACHMENT.sample_scalar_98_offset),
    lateral_scale: safeReadFloat(sample, ATTACHMENT.sample_lateral_scale_offset),
    warp_scalar: safeReadFloat(sample, ATTACHMENT.sample_warp_scalar_offset),
  };
}

function summarizeAttachmentTemplate(templatePtr) {
  const template = asPtr(templatePtr);
  if (template === null || template.isNull()) {
    return null;
  }

  const sampleIndex = safeReadU32(template, ATTACHMENT.template_sample_count_offset);
  return {
    ptr: hex(template),
    kind: safeReadU32(template, ATTACHMENT.template_kind_offset),
    sample_count: sampleIndex,
    width: safeReadFloat(template, ATTACHMENT.template_width_offset),
    primary_points: hex(safeReadPointer(template, ATTACHMENT.template_primary_points_offset)),
    secondary_points: hex(safeReadPointer(template, ATTACHMENT.template_secondary_points_offset)),
    install_row_scalar: safeReadFloat(template, ATTACHMENT.template_row_scalar_offset),
    special_flag: safeReadU32(template, ATTACHMENT.template_special_flag_offset),
  };
}

function summarizeInstalledOwner(ownerPtr, gamePtr) {
  const owner = asPtr(ownerPtr);
  const game = asPtr(gamePtr);
  if (owner === null || owner.isNull() || game === null || game.isNull()) {
    return null;
  }

  const primaryRoot = game.add(RUNTIME.path_bank_primary);
  const secondaryRoot = game.add(RUNTIME.path_bank_secondary);
  const ownerU32 = owner.toUInt32();
  const primaryU32 = primaryRoot.toUInt32();
  const secondaryU32 = secondaryRoot.toUInt32();
  const bankBytes = ATTACHMENT.installed_record_stride * ATTACHMENT.installed_record_count;

  let bankRoot = null;
  let bankLabel = null;
  let pathIndex = null;
  if (ownerU32 >= primaryU32 && ownerU32 < primaryU32 + bankBytes) {
    const offset = ownerU32 - primaryU32;
    if (offset % ATTACHMENT.installed_record_stride === 0) {
      bankRoot = primaryRoot;
      bankLabel = 'ff2914';
      pathIndex = Math.floor(offset / ATTACHMENT.installed_record_stride);
    }
  } else if (ownerU32 >= secondaryU32 && ownerU32 < secondaryU32 + bankBytes) {
    const offset = ownerU32 - secondaryU32;
    if (offset % ATTACHMENT.installed_record_stride === 0) {
      bankRoot = secondaryRoot;
      bankLabel = 'ff29bc';
      pathIndex = Math.floor(offset / ATTACHMENT.installed_record_stride);
    }
  }

  const template = safeReadPointer(owner, ATTACHMENT.gameplay_cell_attachment_offset);
  return {
    ptr: hex(owner),
    bank_root: hex(bankRoot),
    bank_root_label: bankLabel,
    path_index: pathIndex,
    path_name: canonicalPathNameFromIndex(pathIndex),
    template: hex(template),
    template_summary: summarizeAttachmentTemplate(template),
    world_origin: safeReadVec3(owner, 16),
    segment_rows: safeReadU32(owner, 72),
    render_asset_a: hex(safeReadPointer(owner, 36)),
    render_asset_b: hex(safeReadPointer(owner, 132)),
  };
}

function summarizeCell(cellPtr, getTrackCellRowIndex, gamePtr) {
  const cell = asPtr(cellPtr);
  const game = asPtr(gamePtr);
  if (cell === null || cell.isNull()) {
    return null;
  }

  const derived = deriveTrackGridAddressInfo(game, cell);
  let row = derived !== null ? derived.row : null;
  if (row === null && getTrackCellRowIndex !== null) {
    try {
      row = getTrackCellRowIndex(cell);
    } catch (_) {
      row = null;
    }
  }

  const attachment = safeReadPointer(cell, ATTACHMENT.gameplay_cell_attachment_offset);
  return {
    ptr: hex(cell),
    row: row,
    lane: derived !== null ? derived.lane : null,
    lane_center_x: derived !== null ? laneCenterX(derived.lane) : null,
    flags: safeReadU32(cell, ATTACHMENT.gameplay_cell_flags_offset),
    tile_type: safeReadU8(cell, ATTACHMENT.gameplay_cell_tile_offset),
    world: safeReadVec3(cell, ATTACHMENT.gameplay_cell_world_offset),
    row_scalar_a: safeReadFloat(cell, ATTACHMENT.gameplay_cell_row_scalar_a_offset),
    row_scalar_b: safeReadFloat(cell, ATTACHMENT.gameplay_cell_row_scalar_b_offset),
    payload: safeReadU32(cell, ATTACHMENT.gameplay_cell_payload_offset),
    attachment: hex(attachment),
    owner_summary: summarizeInstalledOwner(attachment, game),
  };
}

function summarizeFollowState(followStatePtr, getTrackCellRowIndex) {
  const follow = asPtr(followStatePtr);
  if (follow === null || follow.isNull()) {
    return null;
  }

  const playerPtr = safeReadPointer(follow, 0x38);
  const gamePtr = safeReadPointer(playerPtr, 0x408);
  const templatePtr = safeReadPointer(follow, 4);
  const sampleIndex = safeReadU32(follow, 0xc);
  const primaryPtr = safeReadPointer(templatePtr, ATTACHMENT.template_primary_points_offset);
  const secondaryPtr = safeReadPointer(templatePtr, ATTACHMENT.template_secondary_points_offset);
  const outputPosition = safeReadVec3(follow, 0x2c);
  const primarySample = summarizeAttachmentSample(primaryPtr, sampleIndex);
  return {
    ptr: hex(follow),
    active: boolFlag(safeReadU32(follow, 0)),
    template: hex(templatePtr),
    template_summary: summarizeAttachmentTemplate(templatePtr),
    owner_cell: summarizeCell(safeReadPointer(follow, 8), getTrackCellRowIndex, gamePtr),
    sample_index: sampleIndex,
    progress: safeReadFloat(follow, 0x10),
    vertical_offset: safeReadFloat(follow, 0x14),
    output_position: outputPosition,
    current_primary_sample: primarySample,
    current_secondary_sample: summarizeAttachmentSample(secondaryPtr, sampleIndex),
    next_primary_sample: summarizeAttachmentSample(primaryPtr, sampleIndex !== null ? sampleIndex + 1 : null),
    next_secondary_sample: summarizeAttachmentSample(secondaryPtr, sampleIndex !== null ? sampleIndex + 1 : null),
    lateral_offset_from_center:
      outputPosition !== null && primarySample !== null && primarySample.center_x !== null
        ? roundFloat(outputPosition.x - primarySample.center_x)
        : null,
    player: hex(playerPtr),
    player_position: safeReadVec3(playerPtr, 0x68),
    player_velocity: safeReadVec3(playerPtr, 0x410),
  };
}

function makeLevelRuntimeSnapshot(gamePtr) {
  const game = asPtr(gamePtr);
  if (game === null || game.isNull()) {
    return null;
  }

  return {
    build_flags: safeReadU32(game, RUNTIME.build_flags),
    level_mode: safeReadU32(game, RUNTIME.level_mode),
    level_mode_arg: safeReadU32(game, RUNTIME.level_mode_arg),
    track_row_start: safeReadU32(game, RUNTIME.track_row_start),
    track_row_end: safeReadU32(game, RUNTIME.track_row_end),
    replay_active: boolFlag(safeReadU8(game, RUNTIME.replay_active)),
    replay_track_ptr: hex(safeReadPointer(game, RUNTIME.replay_track_ptr)),
    bank_selector_byte: safeReadU8(game, RUNTIME.bank_selector_byte),
  };
}

function scanInstalledAttachmentCells(gamePtr, getTrackCellRowIndex) {
  const game = asPtr(gamePtr);
  if (game === null || game.isNull()) {
    return [];
  }

  const cells = [];
  for (let row = 0; row < TRACK_LAYOUT.row_count; row += 1) {
    for (let lane = 0; lane < TRACK_LAYOUT.lane_count; lane += 1) {
      const cell = game
        .add(TRACK_LAYOUT.gameplay_grid_base)
        .add((lane + row * TRACK_LAYOUT.lane_count) * TRACK_LAYOUT.gameplay_grid_stride);
      const tileType = safeReadU8(cell, ATTACHMENT.gameplay_cell_tile_offset);
      const flags = safeReadU32(cell, ATTACHMENT.gameplay_cell_flags_offset);
      const attachment = safeReadPointer(cell, ATTACHMENT.gameplay_cell_attachment_offset);
      if (attachment === null || attachment.isNull()) {
        continue;
      }
      if (tileType !== 29 && tileType !== 30 && (flags === null || (flags & 0xc0) === 0)) {
        continue;
      }

      cells.push(summarizeCell(cell, getTrackCellRowIndex, game));
    }
  }

  return cells;
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
    module_base: hex(module.base),
    module_path: module.path,
  });

  if (HOOKS.level_start) {
    Interceptor.attach(fromVa(module, VA.normalize_level_runtime_fields), {
      onEnter(args) {
        this.game = this.context.ecx;
        this.level_descriptor = args[0];
      },
      onLeave(retval) {
        emit('level_start', {
          game: hex(this.game),
          level_descriptor: hex(this.level_descriptor),
          retval: retval.toInt32(),
          runtime: makeLevelRuntimeSnapshot(this.game),
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
        emit('path_lookup', {
          path_name:
            canonicalPathNameFromIndex(pathIndex) !== null
              ? canonicalPathNameFromIndex(pathIndex)
              : this.path_name_sanitized !== null
                ? this.path_name_sanitized
                : this.path_name_raw,
          path_name_raw: this.path_name_raw,
          path_name_sanitized: this.path_name_sanitized,
          path_name_from_index: canonicalPathNameFromIndex(pathIndex),
          path_index: pathIndex,
        });
      },
    });
  }

  if (HOOKS.attachment_install) {
    Interceptor.attach(fromVa(module, VA.populate_runtime_track_cells_from_segments), {
      onEnter() {
        this.game = this.context.ecx;
        this.runtimeBefore = makeLevelRuntimeSnapshot(this.game);
      },
      onLeave(retval) {
        const installed = scanInstalledAttachmentCells(this.game, getTrackCellRowIndex);
        const byKind = {};
        const byPath = {};
        const byRoot = {};

        installed.forEach(function (cell) {
          const owner = cell.owner_summary;
          const kind = owner !== null && owner.template_summary !== null ? owner.template_summary.kind : null;
          const path = owner !== null ? owner.path_name : null;
          const root = owner !== null ? owner.bank_root_label : null;
          const kindKey = kind === null ? 'null' : String(kind);
          const pathKey = path === null ? 'null' : path;
          const rootKey = root === null ? 'null' : root;
          byKind[kindKey] = (byKind[kindKey] || 0) + 1;
          byPath[pathKey] = (byPath[pathKey] || 0) + 1;
          byRoot[rootKey] = (byRoot[rootKey] || 0) + 1;
        });

        emit('attachment_install_summary', {
          game: hex(this.game),
          retval: retval.toInt32(),
          runtime_before: this.runtimeBefore,
          runtime_after: makeLevelRuntimeSnapshot(this.game),
          attachment_cell_count: installed.length,
          by_kind: byKind,
          by_path: byPath,
          by_bank_root: byRoot,
        });

        installed.forEach(function (cell, index) {
          emit('attachment_install_cell', {
            index: index,
            game: hex(this.game),
            runtime: makeLevelRuntimeSnapshot(this.game),
            cell: cell,
          });
        }, this);
      },
    });
  }

  if (HOOKS.attachment_projection) {
    Interceptor.attach(fromVa(module, VA.project_position_onto_track_attachment), {
      onEnter(args) {
        this.game = this.context.ecx;
        this.positionPtr = args[0];
        this.outScalarPtr = args[1];
        this.beforePosition = safeReadVec3(this.positionPtr, 0);
        this.beforeCell =
          getTrackGridCellAtWorldPosition !== null
            ? summarizeCell(getTrackGridCellAtWorldPosition(this.game, this.positionPtr), getTrackCellRowIndex, this.game)
            : null;
      },
      onLeave(retval) {
        const afterPosition = safeReadVec3(this.positionPtr, 0);
        const afterCell =
          getTrackGridCellAtWorldPosition !== null
            ? summarizeCell(getTrackGridCellAtWorldPosition(this.game, this.positionPtr), getTrackCellRowIndex, this.game)
            : null;
        const digest = JSON.stringify({
          row: afterCell !== null ? afterCell.row : null,
          lane: afterCell !== null ? afterCell.lane : null,
          tile: afterCell !== null ? afterCell.tile_type : null,
          x: afterPosition !== null ? afterPosition.x : null,
          y: afterPosition !== null ? afterPosition.y : null,
          z: afterPosition !== null ? afterPosition.z : null,
        });

        maybeEmitSampled('attachment_projection', hex(this.positionPtr), digest, 4, {
          game: hex(this.game),
          runtime: makeLevelRuntimeSnapshot(this.game),
          retval: retval.toInt32(),
          before_position: this.beforePosition,
          after_position: afterPosition,
          projected_value: safeReadFloat(this.outScalarPtr, 0),
          before_cell: this.beforeCell,
          after_cell: afterCell,
        });
      },
    });
  }

  if (HOOKS.attachment_probe) {
    Interceptor.attach(fromVa(module, VA.try_enter_track_attachment_from_swept_motion), {
      onEnter(args) {
        const template = this.context.ecx;
        const cell = args[6];
        emit('attachment_probe', {
          template: hex(template),
          template_summary: summarizeAttachmentTemplate(template),
          cell: summarizeCell(cell, getTrackCellRowIndex, null),
          sweep_start: {
            x: floatArg(args[0]),
            y: floatArg(args[1]),
            z: floatArg(args[2]),
          },
          sweep_delta: {
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
          follow_state_summary: follow,
          source_cell: summarizeCell(args[0], getTrackCellRowIndex, safeReadPointer(args[2], 0x408)),
          projected_player_position: safeReadVec3(args[1], 0),
          player: hex(args[2]),
          runtime: makeLevelRuntimeSnapshot(safeReadPointer(args[2], 0x408)),
        });
      },
    });
  }

  if (HOOKS.attachment_update) {
    Interceptor.attach(fromVa(module, VA.update_track_attachment_follow_state), {
      onEnter(args) {
        this.followState = this.context.ecx;
        this.pathFactor = args[0];
        this.positionPtr = args[1];
        this.motionPtr = args[2];
      },
      onLeave(retval) {
        const follow = summarizeFollowState(this.followState, getTrackCellRowIndex);
        const digest = JSON.stringify({
          sample_index: follow !== null ? follow.sample_index : null,
          progress: follow !== null ? follow.progress : null,
          lateral_offset: follow !== null ? follow.lateral_offset_from_center : null,
          x: follow !== null && follow.output_position !== null ? follow.output_position.x : null,
          z: follow !== null && follow.output_position !== null ? follow.output_position.z : null,
          retval: retval.toInt32(),
        });

        maybeEmitSampled('attachment_update', follow !== null ? follow.ptr : hex(this.followState), digest, 2, {
          follow_state: follow !== null ? follow.ptr : hex(this.followState),
          follow_state_summary: follow,
          runtime: makeLevelRuntimeSnapshot(safeReadPointer(follow !== null ? follow.player : null, 0x408)),
          projected_player_position: safeReadVec3(this.positionPtr, 0),
          motion: safeReadVec3(this.motionPtr, 0),
          path_factor: floatArg(this.pathFactor),
          retval: retval.toInt32(),
        });
      },
    });
  }

  if (HOOKS.attachment_end) {
    Interceptor.attach(fromVa(module, VA.end_track_attachment_follow_state), {
      onEnter() {
        this.player = asPtr(this.context.ecx);
        this.beforeFollow = summarizeFollowState(this.player !== null ? this.player.add(0x384) : null, getTrackCellRowIndex);
      },
      onLeave(retval) {
        const afterFollow = summarizeFollowState(this.player !== null ? this.player.add(0x384) : null, getTrackCellRowIndex);
        emit('attachment_end', {
          retval: retval.toInt32(),
          player: hex(this.player),
          runtime: makeLevelRuntimeSnapshot(safeReadPointer(this.player, 0x408)),
          before_follow_state_summary: this.beforeFollow,
          after_follow_state_summary: afterFollow,
          player_position: safeReadVec3(this.player, 0x68),
          player_velocity: safeReadVec3(this.player, 0x410),
        });
      },
    });
  }

  if (HOOKS.warp_transform) {
    Interceptor.attach(fromVa(module, VA.compute_warp_attachment_transform), {
      onEnter(args) {
        this.scalar = floatArg(args[0]);
        this.x = floatArg(args[1]);
        this.y = floatArg(args[2]);
        this.matrixPtr = args[3];
        this.outScalarPtr = args[4];
      },
      onLeave(retval) {
        const digest = JSON.stringify({
          scalar: this.scalar,
          x: this.x,
          y: this.y,
          out: safeReadFloat(this.outScalarPtr, 0),
        });
        maybeEmitSampled('warp_transform', hex(this.matrixPtr), digest, 4, {
          retval: retval.toInt32(),
          warp_scalar: this.scalar,
          input_x: this.x,
          input_y: this.y,
          output_scalar: safeReadFloat(this.outScalarPtr, 0),
          matrix_translation: {
            x: safeReadFloat(this.matrixPtr, 0x30),
            y: safeReadFloat(this.matrixPtr, 0x34),
            z: safeReadFloat(this.matrixPtr, 0x38),
          },
        });
      },
    });
  }

  emit('hooks_installed', {
    module: module.name,
    script: TRACE_OUTPUT_PREFIX,
  });
}

function waitForTargetModule() {
  const timer = setInterval(function () {
    if (hookInstalled) {
      clearInterval(timer);
      return;
    }

    const module = findTargetModule();
    if (module !== null) {
      clearInterval(timer);
      try {
        installHooks(module);
      } catch (error) {
        console.error('[snailmail-path-oracle] install failed: ' + error.stack);
      }
    }
  }, MODULE_POLL_MS);
}

waitForTargetModule();
