// The WASI preview1 calls snail-web.wasm imports, over the host file system.
// The program sees one preopened root, the directory holding SnailMail.dat;
// paths resolve case-insensitively within it, as on the Windows file system
// the game was written for. Writes (SnailMail.cfg, ScoreA/B/C.dat) land there.

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <unistd.h>

#include <string>
#include <unordered_map>
#include <vector>

#include "host.h"

namespace {

enum : uint32_t {
    ERRNO_SUCCESS = 0, ERRNO_ACCES = 2, ERRNO_BADF = 8, ERRNO_EXIST = 20, ERRNO_INVAL = 28, ERRNO_IO = 29,
    ERRNO_ISDIR = 31, ERRNO_NOENT = 44, ERRNO_NOTDIR = 54,
};
enum : uint8_t { FILETYPE_CHARACTER_DEVICE = 2, FILETYPE_DIRECTORY = 3, FILETYPE_REGULAR_FILE = 4 };
enum : uint32_t { OFLAGS_CREAT = 1, OFLAGS_DIRECTORY = 2, OFLAGS_EXCL = 4, OFLAGS_TRUNC = 8 };
const uint64_t RIGHT_FD_WRITE = 1u << 6;
const uint32_t FDFLAGS_APPEND = 1;
const uint32_t ROOT_FD = 3;

uint32_t wasi_errno(int error)
{
    switch (error) {
    case ENOENT: return ERRNO_NOENT;
    case EACCES: case EPERM: return ERRNO_ACCES;
    case EEXIST: return ERRNO_EXIST;
    case EISDIR: return ERRNO_ISDIR;
    case ENOTDIR: return ERRNO_NOTDIR;
    case EBADF: return ERRNO_BADF;
    case EINVAL: return ERRNO_INVAL;
    default: return ERRNO_IO;
    }
}

struct Descriptor {
    int fd;            // host descriptor
    std::string path;  // host path
    bool directory;
};

}  // namespace

struct WasiState {
    std::string root;
    std::unordered_map<uint32_t, Descriptor> descriptors;
    uint32_t next = ROOT_FD + 1;
};

namespace {

uint8_t* memory(w2c_wasi__snapshot__preview1* wasi) { return linear_memory(wasi->game); }

template <typename T>
T load(w2c_wasi__snapshot__preview1* wasi, uint32_t pointer)
{
    T value;
    memcpy(&value, memory(wasi) + pointer, sizeof(T));
    return value;
}

template <typename T>
void store(w2c_wasi__snapshot__preview1* wasi, uint32_t pointer, T value)
{
    memcpy(memory(wasi) + pointer, &value, sizeof(T));
}

// The host path for a guest path under a directory descriptor: `.` and `..`
// stay inside the root, and each component matches case-insensitively.
bool resolve(WasiState* state, uint32_t fd, const std::string& guest, std::string* out)
{
    std::string base;
    if (fd == ROOT_FD) {
        base = state->root;
    } else {
        auto it = state->descriptors.find(fd);
        if (it == state->descriptors.end() || !it->second.directory)
            return false;
        base = it->second.path;
    }
    std::vector<std::string> parts;
    std::string relative = base.substr(state->root.size());
    std::string combined = relative + "/" + guest;
    size_t start = 0;
    while (start <= combined.size()) {
        size_t end = combined.find_first_of("/\\", start);
        if (end == std::string::npos)
            end = combined.size();
        std::string part = combined.substr(start, end - start);
        if (part == "..") {
            if (!parts.empty())
                parts.pop_back();
        } else if (!part.empty() && part != ".") {
            parts.push_back(part);
        }
        start = end + 1;
    }
    std::string path = state->root;
    for (const std::string& part : parts) {
        std::string candidate = path + "/" + part;
        struct stat info;
        if (lstat(candidate.c_str(), &info) != 0) {
            if (DIR* directory = opendir(path.c_str())) {
                while (dirent* entry = readdir(directory)) {
                    if (strcasecmp(entry->d_name, part.c_str()) == 0) {
                        candidate = path + "/" + entry->d_name;
                        break;
                    }
                }
                closedir(directory);
            }
        }
        path = candidate;
    }
    *out = path;
    return true;
}

std::string guest_string(w2c_wasi__snapshot__preview1* wasi, uint32_t pointer, uint32_t length)
{
    return std::string((const char*)memory(wasi) + pointer, length);
}

uint8_t filetype(mode_t mode)
{
    return S_ISDIR(mode) ? FILETYPE_DIRECTORY : FILETYPE_REGULAR_FILE;
}

int host_fd(WasiState* state, uint32_t fd)
{
    if (fd <= 2)
        return (int)fd;
    auto it = state->descriptors.find(fd);
    return it == state->descriptors.end() ? -1 : it->second.fd;
}

std::vector<iovec> iovecs(w2c_wasi__snapshot__preview1* wasi, uint32_t pointer, uint32_t count)
{
    std::vector<iovec> list(count);
    for (uint32_t i = 0; i < count; ++i) {
        list[i].iov_base = memory(wasi) + load<uint32_t>(wasi, pointer + i * 8);
        list[i].iov_len = load<uint32_t>(wasi, pointer + i * 8 + 4);
    }
    return list;
}

}  // namespace

WasiState* wasi_create(const char* root)
{
    WasiState* state = new WasiState;
    char absolute[4096];
    state->root = realpath(root, absolute) ? absolute : root;
    return state;
}

extern "C" {

uint32_t w2c_wasi__snapshot__preview1_fd_write(w2c_wasi__snapshot__preview1* wasi, uint32_t fd, uint32_t iovs,
    uint32_t count, uint32_t written)
{
    int host = host_fd(wasi->state, fd);
    if (host < 0)
        return ERRNO_BADF;
    std::vector<iovec> list = iovecs(wasi, iovs, count);
    ssize_t result = writev(host, list.data(), (int)list.size());
    if (result < 0)
        return wasi_errno(errno);
    store<uint32_t>(wasi, written, (uint32_t)result);
    return ERRNO_SUCCESS;
}

uint32_t w2c_wasi__snapshot__preview1_fd_read(w2c_wasi__snapshot__preview1* wasi, uint32_t fd, uint32_t iovs,
    uint32_t count, uint32_t read)
{
    int host = host_fd(wasi->state, fd);
    if (host < 0)
        return ERRNO_BADF;
    std::vector<iovec> list = iovecs(wasi, iovs, count);
    ssize_t result = readv(host, list.data(), (int)list.size());
    if (result < 0)
        return wasi_errno(errno);
    store<uint32_t>(wasi, read, (uint32_t)result);
    return ERRNO_SUCCESS;
}

uint32_t w2c_wasi__snapshot__preview1_fd_seek(w2c_wasi__snapshot__preview1* wasi, uint32_t fd, uint64_t offset,
    uint32_t whence, uint32_t result)
{
    int host = host_fd(wasi->state, fd);
    if (host < 0)
        return ERRNO_BADF;
    static const int kWhence[] = {SEEK_SET, SEEK_CUR, SEEK_END};
    if (whence > 2)
        return ERRNO_INVAL;
    off_t position = lseek(host, (off_t)(int64_t)offset, kWhence[whence]);
    if (position < 0)
        return wasi_errno(errno);
    store<uint64_t>(wasi, result, (uint64_t)position);
    return ERRNO_SUCCESS;
}

uint32_t w2c_wasi__snapshot__preview1_fd_close(w2c_wasi__snapshot__preview1* wasi, uint32_t fd)
{
    auto it = wasi->state->descriptors.find(fd);
    if (it == wasi->state->descriptors.end())
        return ERRNO_BADF;
    close(it->second.fd);
    wasi->state->descriptors.erase(it);
    return ERRNO_SUCCESS;
}

uint32_t w2c_wasi__snapshot__preview1_fd_fdstat_get(w2c_wasi__snapshot__preview1* wasi, uint32_t fd, uint32_t pointer)
{
    uint8_t type;
    if (fd <= 2) {
        type = FILETYPE_CHARACTER_DEVICE;
    } else if (fd == ROOT_FD) {
        type = FILETYPE_DIRECTORY;
    } else {
        auto it = wasi->state->descriptors.find(fd);
        if (it == wasi->state->descriptors.end())
            return ERRNO_BADF;
        type = it->second.directory ? FILETYPE_DIRECTORY : FILETYPE_REGULAR_FILE;
    }
    memset(memory(wasi) + pointer, 0, 24);
    store<uint8_t>(wasi, pointer, type);
    store<uint64_t>(wasi, pointer + 8, ~0ull);
    store<uint64_t>(wasi, pointer + 16, ~0ull);
    return ERRNO_SUCCESS;
}

uint32_t w2c_wasi__snapshot__preview1_fd_fdstat_set_flags(w2c_wasi__snapshot__preview1*, uint32_t, uint32_t)
{
    return ERRNO_SUCCESS;
}

uint32_t w2c_wasi__snapshot__preview1_fd_prestat_get(w2c_wasi__snapshot__preview1* wasi, uint32_t fd, uint32_t pointer)
{
    if (fd != ROOT_FD)
        return ERRNO_BADF;
    store<uint8_t>(wasi, pointer, 0);
    store<uint32_t>(wasi, pointer + 4, 1);
    return ERRNO_SUCCESS;
}

uint32_t w2c_wasi__snapshot__preview1_fd_prestat_dir_name(w2c_wasi__snapshot__preview1* wasi, uint32_t fd,
    uint32_t pointer, uint32_t length)
{
    if (fd != ROOT_FD || length < 1)
        return ERRNO_BADF;
    store<char>(wasi, pointer, '/');
    return ERRNO_SUCCESS;
}

uint32_t w2c_wasi__snapshot__preview1_path_open(w2c_wasi__snapshot__preview1* wasi, uint32_t fd, uint32_t,
    uint32_t path_pointer, uint32_t path_length, uint32_t oflags, uint64_t rights, uint64_t, uint32_t fdflags,
    uint32_t result)
{
    std::string path;
    if (!resolve(wasi->state, fd, guest_string(wasi, path_pointer, path_length), &path))
        return ERRNO_BADF;
    struct stat info;
    bool exists = stat(path.c_str(), &info) == 0;
    bool directory = exists && S_ISDIR(info.st_mode);
    if ((oflags & OFLAGS_DIRECTORY) && !directory)
        return exists ? ERRNO_NOTDIR : ERRNO_NOENT;
    int flags;
    if (directory) {
        flags = O_RDONLY | O_DIRECTORY;
    } else {
        bool write = (rights & RIGHT_FD_WRITE) || (oflags & (OFLAGS_CREAT | OFLAGS_TRUNC));
        flags = write ? O_RDWR : O_RDONLY;
        if (oflags & OFLAGS_CREAT) flags |= O_CREAT;
        if (oflags & OFLAGS_EXCL) flags |= O_EXCL;
        if (oflags & OFLAGS_TRUNC) flags |= O_TRUNC;
        if (fdflags & FDFLAGS_APPEND) flags |= O_APPEND;
    }
    int host = open(path.c_str(), flags, 0644);
    if (host < 0)
        return wasi_errno(errno);
    uint32_t opened = wasi->state->next++;
    wasi->state->descriptors[opened] = Descriptor{host, path, directory};
    store<uint32_t>(wasi, result, opened);
    return ERRNO_SUCCESS;
}

uint32_t w2c_wasi__snapshot__preview1_path_filestat_get(w2c_wasi__snapshot__preview1* wasi, uint32_t fd, uint32_t,
    uint32_t path_pointer, uint32_t path_length, uint32_t pointer)
{
    std::string path;
    if (!resolve(wasi->state, fd, guest_string(wasi, path_pointer, path_length), &path))
        return ERRNO_BADF;
    struct stat info;
    if (stat(path.c_str(), &info) != 0)
        return wasi_errno(errno);
    memset(memory(wasi) + pointer, 0, 64);
    store<uint8_t>(wasi, pointer + 16, filetype(info.st_mode));
    store<uint64_t>(wasi, pointer + 24, 1);
    store<uint64_t>(wasi, pointer + 32, (uint64_t)info.st_size);
    return ERRNO_SUCCESS;
}

uint32_t w2c_wasi__snapshot__preview1_fd_readdir(w2c_wasi__snapshot__preview1* wasi, uint32_t fd, uint32_t buffer,
    uint32_t length, uint64_t cookie, uint32_t used)
{
    std::string path;
    if (fd == ROOT_FD) {
        path = wasi->state->root;
    } else {
        auto it = wasi->state->descriptors.find(fd);
        if (it == wasi->state->descriptors.end() || !it->second.directory)
            return ERRNO_BADF;
        path = it->second.path;
    }
    DIR* directory = opendir(path.c_str());
    if (!directory)
        return wasi_errno(errno);
    std::vector<uint8_t> out;
    uint64_t index = 0;
    while (dirent* entry = readdir(directory)) {
        if (index++ < cookie)
            continue;
        size_t name_length = strlen(entry->d_name);
        uint8_t record[24] = {0};
        uint64_t next = index;
        uint32_t namlen = (uint32_t)name_length;
        memcpy(record, &next, 8);
        memcpy(record + 8, &next, 8);
        memcpy(record + 16, &namlen, 4);
        record[20] = entry->d_type == DT_DIR ? FILETYPE_DIRECTORY : FILETYPE_REGULAR_FILE;
        out.insert(out.end(), record, record + 24);
        out.insert(out.end(), entry->d_name, entry->d_name + name_length);
        if (out.size() >= length)
            break;
    }
    closedir(directory);
    uint32_t count = out.size() < length ? (uint32_t)out.size() : length;
    memcpy(memory(wasi) + buffer, out.data(), count);
    store<uint32_t>(wasi, used, count);
    return ERRNO_SUCCESS;
}

uint32_t w2c_wasi__snapshot__preview1_random_get(w2c_wasi__snapshot__preview1* wasi, uint32_t pointer, uint32_t length)
{
    arc4random_buf(memory(wasi) + pointer, length);
    return ERRNO_SUCCESS;
}

void w2c_wasi__snapshot__preview1_proc_exit(w2c_wasi__snapshot__preview1*, uint32_t code)
{
    exit((int)code);
}

}  // extern "C"
