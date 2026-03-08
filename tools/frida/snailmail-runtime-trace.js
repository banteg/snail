'use strict';

const TARGET_MODULE_NAME = 'SnailMail.RWG';
const PREFERRED_IMAGE_BASE = 0x400000;
const MODULE_POLL_MS = 250;

const HOOKS = {
  level_start: true,
  path_lookup: true,
  attachment_probe: true,
  attachment_begin: true,
  garbage_spawn: true,
  salt_spawn: true,
  salt_deactivate: true,
  slug_spawn: true,
};

const LIMITS = {
  level_start: 128,
  path_lookup: 2048,
  attachment_probe: 4096,
  attachment_begin: 1024,
  garbage_spawn: 4096,
  salt_spawn: 4096,
  salt_deactivate: 4096,
  slug_spawn: 1024,
};

const VA = {
  find_segment_path_index_by_name: 0x429ae0,
  begin_track_attachment_follow_state: 0x420c40,
  try_enter_track_attachment_from_swept_motion: 0x42c770,
  normalize_level_runtime_fields: 0x437eb0,
  spawn_track_garbage_hazard: 0x43da80,
  spawn_salt_runtime_entity: 0x441560,
  deactivate_salt_runtime_entity: 0x441740,
  spawn_slug_runtime_entity: 0x43dc80,
  get_track_cell_row_index: 0x447040,
};

const RUNTIME = {
  selected_track_id: 0x40,
  active_level_ptr: 0xff25d4,
  garbage_scalar: 0x125ffd8,
  salt_scalar: 0x125ffdc,
};

const counters = {};
const floatScratch = Memory.alloc(4);
let hookInstalled = false;

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
    return Memory.readU8(p.add(offset || 0));
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
    return Memory.readU32(p.add(offset || 0));
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
    return roundFloat(Memory.readFloat(p.add(offset || 0)));
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
    return Memory.readPointer(p.add(offset || 0));
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
    return Memory.readCString(p, maxLength || 128);
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
      x: roundFloat(Memory.readFloat(q)),
      y: roundFloat(Memory.readFloat(q.add(4))),
      z: roundFloat(Memory.readFloat(q.add(8))),
    };
  } catch (_) {
    return null;
  }
}

function floatArg(arg) {
  const p = asPtr(arg);
  if (p === null) {
    return null;
  }
  try {
    Memory.writeU32(floatScratch, p.toUInt32());
    return roundFloat(Memory.readFloat(floatScratch));
  } catch (_) {
    return null;
  }
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
      console.log(JSON.stringify(suppressed));
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
    console.log(JSON.stringify(payload));
  }
}

function findTargetModule() {
  const modules = Process.enumerateModules();
  const targetLower = TARGET_MODULE_NAME.toLowerCase();

  for (let i = 0; i < modules.length; i += 1) {
    const module = modules[i];
    if (module.name.toLowerCase() === targetLower) {
      return module;
    }
  }

  for (let i = 0; i < modules.length; i += 1) {
    const module = modules[i];
    const nameLower = module.name.toLowerCase();
    const pathLower = module.path.toLowerCase();
    if (nameLower.indexOf('snailmail') !== -1 && pathLower.indexOf('snailmail.rwg') !== -1) {
      return module;
    }
  }

  return null;
}

function fromVa(module, va) {
  return module.base.add(va - PREFERRED_IMAGE_BASE);
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
    tile_type: safeReadU8(cell, 60),
    world: safeReadVec3(cell, 16),
    attachment: hex(attachment),
    attachment_kind: safeReadU32(attachment, 56),
  };
}

function installHooks(module) {
  if (hookInstalled) {
    return;
  }
  hookInstalled = true;

  const getTrackCellRowIndex = makeTrackCellRowIndex(module);

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
      },
      onLeave(retval) {
        emit('level_start', {
          game: hex(this.game),
          level_descriptor: hex(this.level_descriptor),
          retval: retval.toInt32(),
          selected_track_id: safeReadU32(this.game, RUNTIME.selected_track_id),
          active_level: hex(safeReadPointer(this.game, RUNTIME.active_level_ptr)),
          garbage_scalar: safeReadFloat(this.game, RUNTIME.garbage_scalar),
          salt_scalar: safeReadFloat(this.game, RUNTIME.salt_scalar),
        });
      },
    });
  }

  if (HOOKS.path_lookup) {
    Interceptor.attach(fromVa(module, VA.find_segment_path_index_by_name), {
      onEnter(args) {
        this.path_name = safeReadCString(args[0], 96);
      },
      onLeave(retval) {
        emit('path_lookup', {
          path_name: this.path_name,
          path_index: retval.toInt32(),
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
        emit('attachment_begin', {
          follow_state: hex(this.context.ecx),
          cell: summarizeCell(args[0], getTrackCellRowIndex),
          player_position: safeReadVec3(args[1], 0),
          player: hex(args[2]),
        });
      },
    });
  }

  if (HOOKS.garbage_spawn) {
    Interceptor.attach(fromVa(module, VA.spawn_track_garbage_hazard), {
      onEnter(args) {
        emit('garbage_spawn', {
          game: hex(this.context.ecx),
          cell: summarizeCell(args[0], getTrackCellRowIndex),
          manager: hex(args[1]),
          manager_sprite_bank: safeReadPointer(args[1], 896) !== null ? hex(safeReadPointer(args[1], 896)) : null,
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
    target_module: TARGET_MODULE_NAME,
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
