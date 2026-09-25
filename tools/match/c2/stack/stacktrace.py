"""Dump VC6 C2 stack-packing (stack.c) variables and slots after sub_1074b617."""
import struct, sys, tempfile, re
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import trace as t
from snail import match as m
c2 = t.c2

PACK_HOOK = {"site": 0x33CDE, "target": 0x4B617, "return": True}
PRIO_HOOK = {"site": 0x33607, "target": 0x31D21, "return": False}
PRIO2_HOOK = {"site": 0x215BB, "target": 0x31D21, "return": False}
MAXV = 400
RECORDER = r"""
static HANDLE stk_file;
static void stk_write(void *data, unsigned long size)
{
    DWORD written;
    if (!WriteFile(stk_file, data, size, &written, 0) || written != size) ExitProcess(79);
}
static void stk_observe(unsigned long phase, unsigned long *registers)
{
    unsigned char *base = (unsigned char *)targets[STK_HOOK] - 0x4B617;
    unsigned long *v, *sym, rec[12], n = 0, i, cnt;
    unsigned char *tab;
    if (phase < 100 && phase != STK_HOOK) {
        unsigned long *j = (unsigned long *)registers[6], w[32], q;
        unsigned long *sy = (unsigned long *)j[0];
        w[0] = 0xEEEE0005; w[1] = phase;
        for (q = 0; q < 18; ++q) w[2 + q] = j[q];
        for (q = 0; q < 8; ++q) w[20 + q] = sy ? sy[q] : 0;
        stk_write(w, 28 * 4);
        return;
    }
    if (phase < 100) return;
    rec[0] = 0xAAAA0001; rec[1] = saved_function; stk_write(rec, 8);
    v = *(unsigned long **)(base + 0x9F220);
    while (v && n < 4000) {
        sym = (unsigned long *)v[0];
        rec[0] = 0xBBBB0002; rec[1] = (unsigned long)v; rec[2] = *((unsigned char *)v + 4);
        rec[3] = v[0x20/4]; rec[4] = v[0x34/4]; rec[5] = v[0x38/4]; rec[6] = v[0x28/4];
        rec[7] = sym ? sym[3] : 0; rec[8] = sym ? sym[4] : 0; rec[9] = *((unsigned char *)v + 6);
        rec[10] = *((unsigned char *)v + 5); rec[11] = v[0];
        stk_write(rec, 48);
        v = (unsigned long *)v[0x2c/4]; ++n;
    }
    cnt = *(unsigned long *)(base + 0x9F224);
    tab = *(unsigned char **)(base + 0x9F228);
    for (i = 0; i < cnt; ++i) {
        unsigned long *s = (unsigned long *)(tab + i * 0x14);
        rec[0] = 0xCCCC0003; rec[1] = i; rec[2] = s[2]; rec[3] = s[3]; rec[4] = s[4];
        stk_write(rec, 20);
    }
    rec[0] = 0xDDDD0004; rec[1] = *(unsigned long *)(base + 0x9F21C); stk_write(rec, 8);
}
"""

def observer(profile, stock_source):
    hook = len(profile["hooks"]) - 1
    source = stock_source(profile)
    a1 = "    unsigned long first, node, count = 0, record[742], op, side, j, k, at;\n"
    a2 = "    trace_file = CreateFileA("
    a3 = "    CloseHandle(trace_file);"
    source = source.replace("static void __cdecl observe(", f"#define STK_HOOK {hook}\n" + RECORDER + "static void __cdecl observe(")
    source = source.replace(a1, a1 + "    { stk_observe(phase, registers); return; }\n")
    source = source.replace(a2, '    stk_file = CreateFileA("stack.bin", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);\n    if (stk_file == INVALID_HANDLE_VALUE) ExitProcess(78);\n' + a2)
    return source.replace(a3, "    CloseHandle(stk_file);\n" + a3)

def run(scratch_dir, source, out):
    work = out.parent / (out.name + "-input")
    work.mkdir(parents=True)
    conf = (scratch_dir / "scratch.conf").read_text()
    conf = re.sub(r"^COMPILER=.*\n", "", conf, flags=re.M)
    (work / "scratch.conf").write_text(conf)
    (work / "scratch.cpp").write_bytes(Path(source).read_bytes())
    sp, ss = c2.load_profile, c2.observer_source
    profile = sp()
    from rotation import FUNCTION_ENTRY_HOOK, FINAL_HOOK
    profile = dict(profile, name=profile["name"] + "-stack", hooks=[PRIO_HOOK, PRIO2_HOOK, PACK_HOOK])
    c2.load_profile = lambda: profile
    c2.observer_source = lambda p: observer(p, ss)
    try:
        try:
            t.trace(work, out)
        except ValueError as e:
            if "Empty C2 trace" not in str(e): raise
    finally:
        c2.load_profile, c2.observer_source = sp, ss
    return (out / "observed/stack.bin").read_bytes()

def decode(data):
    at = 0; out = []
    while at < len(data):
        (k,) = struct.unpack_from("<I", data, at)
        if k == 0xAAAA0001:
            _, f = struct.unpack_from("<2I", data, at); at += 8; out.append(("F", f))
        elif k == 0xBBBB0002:
            w = struct.unpack_from("<12I", data, at); at += 48; out.append(("V",) + w[1:])
        elif k == 0xCCCC0003:
            w = struct.unpack_from("<5I", data, at); at += 20; out.append(("S",) + w[1:])
        elif k == 0xEEEE0005:
            w = struct.unpack_from("<28I", data, at); at += 112; out.append(("P",) + w[1:])
        elif k == 0xDDDD0004:
            w = struct.unpack_from("<2I", data, at); at += 8; out.append(("E", w[1]))
        else:
            raise ValueError(hex(k))
    return out

if __name__ == "__main__":
    scratch = Path(sys.argv[1]); src = sys.argv[2]
    out = Path(tempfile.mkdtemp(prefix="stk-", dir=tempfile.gettempdir())) / "trace"
    data = run(scratch, src, out)
    def s32(x): return x - (1 << 32) if x & 0x80000000 else x
    for r in decode(data):
        if r[0] == "F": print(f"== function {r[1]:#x}")
        elif r[0] == "V":
            _, v, typ, size, weight, idx, off28, symoff, symsize, f6, f5, v1 = r
            print(f"sym={v1:#x} var idx={idx:3d} type={typ} size={size:3d} weight={weight:6d} off28={s32(off28):5d} symoff={s32(symoff):5d} symsize={symsize} f5={f5:#x} f6={f6:#x}")
        elif r[0] == "S":
            _, i, size, weight, x = r
            print(f"slot {i:2d} size={size:3d} weight={weight:6d} density={weight*1000//max(size,1)} f10={s32(x)}")
        elif r[0] == "P":
            ebx = r[1]; j = r[2:20]; sy = r[20:28]
            print(f"prio hook={ebx} pr={s32(j[3]):6d} id40={j[16]:#x} id1c={j[7]} sym={j[0]:#x} f5={(j[1]>>8)&0xff:#x} j={[hex(x) for x in j[1:]]} sym={[hex(x) for x in sy[:6]]}")
        else: print(f"fixed_count={r[1]}")
