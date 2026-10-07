// The WASI preview1 calls snail-web.wasm imports, over an in-memory file
// system with one preopened root. Paths are case-insensitive, as on the
// Windows file system the game was written for. Files the game writes
// (configuration, scores) live in memory for the session.

const ERRNO = { SUCCESS: 0, BADF: 8, EXIST: 20, INVAL: 28, ISDIR: 31, NOENT: 44, NOTDIR: 54, NOSYS: 52 };
const FILETYPE = { CHARACTER_DEVICE: 2, DIRECTORY: 3, REGULAR_FILE: 4 };
const OFLAGS = { CREAT: 1, DIRECTORY: 2, EXCL: 4, TRUNC: 8 };
const ROOT_FD = 3;

export class ExitStatus extends Error {
  constructor(code) {
    super(`exit ${code}`);
    this.code = code;
  }
}

export class MemoryFileSystem {
  constructor() {
    this.files = new Map(); // lower-case path -> { name, data: Uint8Array }
  }

  static key(path) {
    return path.replace(/\\/g, "/").replace(/^\/+|\/+$/g, "").replace(/\/+/g, "/").toLowerCase();
  }

  write(path, data) {
    const name = path.replace(/\\/g, "/").replace(/^\/+/, "");
    this.files.set(MemoryFileSystem.key(path), { name, data });
  }

  file(path) {
    return this.files.get(MemoryFileSystem.key(path));
  }

  isDirectory(path) {
    const key = MemoryFileSystem.key(path);
    if (key === "") return true;
    for (const other of this.files.keys()) if (other.startsWith(key + "/")) return true;
    return false;
  }

  // Immediate children as [name, filetype], names in their stored case.
  list(path) {
    const key = MemoryFileSystem.key(path);
    const prefix = key === "" ? "" : key + "/";
    const entries = new Map();
    for (const [other, { name }] of this.files) {
      if (!other.startsWith(prefix)) continue;
      const rest = name.split("/").slice(prefix === "" ? 0 : key.split("/").length);
      const child = rest[0];
      entries.set(child.toLowerCase(), [child, rest.length > 1 ? FILETYPE.DIRECTORY : FILETYPE.REGULAR_FILE]);
    }
    return [...entries.values()];
  }
}

// `onClose(path, data)` sees every file the program wrote, when it closes.
export function createWasi(fs, { log = console.log, onClose = () => {} } = {}) {
  let memory = null;
  const descriptors = new Map(); // fd -> { path, directory, data?, position }
  let nextFd = ROOT_FD + 1;
  const pending = { 1: "", 2: "" };
  const decoder = new TextDecoder();
  const encoder = new TextEncoder();

  const view = () => new DataView(memory.buffer);
  const bytes = () => new Uint8Array(memory.buffer);
  const string = (pointer, length) => decoder.decode(bytes().slice(pointer, pointer + length));

  function resolve(fd, pointer, length) {
    const base = fd === ROOT_FD ? "" : descriptors.get(fd)?.path;
    if (base === undefined) return null;
    const parts = [];
    for (const part of `${base}/${string(pointer, length)}`.split("/")) {
      if (part === "" || part === ".") continue;
      if (part === "..") parts.pop();
      else parts.push(part);
    }
    return parts.join("/");
  }

  function iovecs(pointer, count) {
    const v = view();
    const list = [];
    for (let i = 0; i < count; ++i) list.push([v.getUint32(pointer + i * 8, true), v.getUint32(pointer + i * 8 + 4, true)]);
    return list;
  }

  function writeStat(pointer, type, size) {
    const v = view();
    for (let i = 0; i < 64; i += 4) v.setUint32(pointer + i, 0, true);
    v.setUint8(pointer + 16, type);
    v.setBigUint64(pointer + 24, 1n, true);
    v.setBigUint64(pointer + 32, BigInt(size), true);
  }

  const imports = {
    fd_write(fd, iovs, count, written) {
      let total = 0;
      for (const [pointer, length] of iovecs(iovs, count)) {
        const chunk = bytes().slice(pointer, pointer + length);
        total += length;
        if (fd === 1 || fd === 2) {
          pending[fd] += decoder.decode(chunk, { stream: true });
          let newline;
          while ((newline = pending[fd].indexOf("\n")) >= 0) {
            log(pending[fd].slice(0, newline), fd);
            pending[fd] = pending[fd].slice(newline + 1);
          }
          continue;
        }
        const descriptor = descriptors.get(fd);
        if (!descriptor || descriptor.directory) return ERRNO.BADF;
        const file = fs.file(descriptor.path);
        const end = descriptor.position + length;
        if (end > file.data.length) {
          const grown = new Uint8Array(end);
          grown.set(file.data);
          file.data = grown;
        }
        file.data.set(chunk, descriptor.position);
        descriptor.position = end;
        descriptor.written = true;
      }
      view().setUint32(written, total, true);
      return ERRNO.SUCCESS;
    },
    fd_read(fd, iovs, count, read) {
      const descriptor = descriptors.get(fd);
      if (!descriptor || descriptor.directory) return ERRNO.BADF;
      const data = fs.file(descriptor.path).data;
      let total = 0;
      for (const [pointer, length] of iovecs(iovs, count)) {
        const chunk = data.subarray(descriptor.position, Math.min(data.length, descriptor.position + length));
        bytes().set(chunk, pointer);
        descriptor.position += chunk.length;
        total += chunk.length;
        if (chunk.length < length) break;
      }
      view().setUint32(read, total, true);
      return ERRNO.SUCCESS;
    },
    fd_seek(fd, offset, whence, result) {
      const descriptor = descriptors.get(fd);
      if (!descriptor || descriptor.directory) return ERRNO.BADF;
      const size = fs.file(descriptor.path).data.length;
      const base = [0, descriptor.position, size][whence];
      const position = base + Number(offset);
      if (base === undefined || position < 0) return ERRNO.INVAL;
      descriptor.position = position;
      view().setBigUint64(result, BigInt(position), true);
      return ERRNO.SUCCESS;
    },
    fd_close(fd) {
      const descriptor = descriptors.get(fd);
      if (!descriptor) return ERRNO.BADF;
      descriptors.delete(fd);
      if (descriptor.written) onClose(descriptor.path, fs.file(descriptor.path).data);
      return ERRNO.SUCCESS;
    },
    fd_fdstat_get(fd, pointer) {
      const v = view();
      let type;
      if (fd <= 2) type = FILETYPE.CHARACTER_DEVICE;
      else if (fd === ROOT_FD) type = FILETYPE.DIRECTORY;
      else if (descriptors.has(fd)) type = descriptors.get(fd).directory ? FILETYPE.DIRECTORY : FILETYPE.REGULAR_FILE;
      else return ERRNO.BADF;
      v.setUint8(pointer, type);
      v.setUint16(pointer + 2, 0, true);
      v.setBigUint64(pointer + 8, 0xffffffffffffffffn, true);
      v.setBigUint64(pointer + 16, 0xffffffffffffffffn, true);
      return ERRNO.SUCCESS;
    },
    fd_fdstat_set_flags() {
      return ERRNO.SUCCESS;
    },
    fd_prestat_get(fd, pointer) {
      if (fd !== ROOT_FD) return ERRNO.BADF;
      view().setUint8(pointer, 0);
      view().setUint32(pointer + 4, 1, true);
      return ERRNO.SUCCESS;
    },
    fd_prestat_dir_name(fd, pointer, length) {
      if (fd !== ROOT_FD) return ERRNO.BADF;
      bytes().set(encoder.encode("/").subarray(0, length), pointer);
      return ERRNO.SUCCESS;
    },
    path_open(fd, _lookup, pathPointer, pathLength, oflags, _base, _inheriting, _fdflags, result) {
      const path = resolve(fd, pathPointer, pathLength);
      if (path === null) return ERRNO.BADF;
      let file = fs.file(path);
      const directory = !file && fs.isDirectory(path);
      if (oflags & OFLAGS.DIRECTORY && !directory) return file ? ERRNO.NOTDIR : ERRNO.NOENT;
      if (!directory) {
        if (file && oflags & OFLAGS.CREAT && oflags & OFLAGS.EXCL) return ERRNO.EXIST;
        if (!file) {
          if (!(oflags & OFLAGS.CREAT)) return ERRNO.NOENT;
          fs.write(path, new Uint8Array(0));
          file = fs.file(path);
        } else if (oflags & OFLAGS.TRUNC) {
          file.data = new Uint8Array(0);
        }
      }
      const opened = nextFd++;
      // A created or truncated file counts as written even if nothing follows.
      const written = !directory && (oflags & (OFLAGS.CREAT | OFLAGS.TRUNC)) !== 0;
      descriptors.set(opened, { path, directory, position: 0, written });
      view().setUint32(result, opened, true);
      return ERRNO.SUCCESS;
    },
    path_filestat_get(fd, _flags, pathPointer, pathLength, pointer) {
      const path = resolve(fd, pathPointer, pathLength);
      if (path === null) return ERRNO.BADF;
      const file = fs.file(path);
      if (file) writeStat(pointer, FILETYPE.REGULAR_FILE, file.data.length);
      else if (fs.isDirectory(path)) writeStat(pointer, FILETYPE.DIRECTORY, 0);
      else return ERRNO.NOENT;
      return ERRNO.SUCCESS;
    },
    fd_readdir(fd, buffer, length, cookie, used) {
      const descriptor = fd === ROOT_FD ? { path: "", directory: true } : descriptors.get(fd);
      if (!descriptor || !descriptor.directory) return ERRNO.BADF;
      const entries = [[".", FILETYPE.DIRECTORY], ["..", FILETYPE.DIRECTORY], ...fs.list(descriptor.path)];
      const out = new Uint8Array(length);
      let offset = 0;
      for (let index = Number(cookie); index < entries.length && offset < length; ++index) {
        const [name, type] = entries[index];
        const encoded = encoder.encode(name);
        const record = new Uint8Array(24 + encoded.length);
        const fields = new DataView(record.buffer);
        fields.setBigUint64(0, BigInt(index + 1), true);
        fields.setBigUint64(8, BigInt(index + 1), true);
        fields.setUint32(16, encoded.length, true);
        fields.setUint8(20, type);
        record.set(encoded, 24);
        const take = Math.min(record.length, length - offset);
        out.set(record.subarray(0, take), offset);
        offset += take;
      }
      bytes().set(out.subarray(0, offset), buffer);
      view().setUint32(used, offset, true);
      return ERRNO.SUCCESS;
    },
    random_get(pointer, length) {
      crypto.getRandomValues(bytes().subarray(pointer, pointer + length));
      return ERRNO.SUCCESS;
    },
    proc_exit(code) {
      throw new ExitStatus(code);
    },
  };

  return {
    imports,
    bind(instanceMemory) {
      memory = instanceMemory;
    },
  };
}
