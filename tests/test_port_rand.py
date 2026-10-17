"""RAND's stream: Original keeps the C runtime's rand, Ultimate steps Android's RandTable.bin."""

import json
import shutil
import struct
import subprocess

import pytest

from snail.symbols import REPO_ROOT

WASM = REPO_ROOT / "port/zig-out/bin/snail-web.wasm"
RAND_TABLE = REPO_ROOT / "artifacts/android/asm_extracted/RANDTABLE.BIN"
SEEDS = (0, 1, 8190, 8191, 32767)


def msvc_rand(seed: int, count: int) -> list[int]:
    values = []
    for _ in range(count):
        seed = (seed * 214013 + 2531011) & 0xFFFFFFFF
        values.append(seed >> 16 & 0x7FFF)
    return values


# What gRMathRand2Init puts in g_math_random_table: rand() from its initial seed.
TABLE = msvc_rand(1, 8191)


@pytest.mark.skipif(
    not RAND_TABLE.exists(), reason="needs the extracted Android assets"
)
def test_android_rand_table_is_msvc_rand_from_seed_1():
    data = RAND_TABLE.read_bytes()
    assert list(struct.unpack(f"<{len(data) // 2}H", data)) == TABLE


@pytest.mark.skipif(
    shutil.which("node") is None
    or not WASM.exists()
    or not (REPO_ROOT / "artifacts/bin/SnailMail.dat").exists()
    or not (REPO_ROOT / "artifacts/bin/SnailMailExtras.dat").exists(),
    reason="needs node, the browser port build, and both game archives",
)
@pytest.mark.parametrize("ultimate", [False, True])
def test_rand_after_rand_seed(tmp_path, ultimate):
    probe = tmp_path / "rand.mjs"
    probe.write_text("""
import { readFile } from 'node:fs/promises';
import { pathToFileURL } from 'node:url';
const [root, ultimate, seeds] = process.argv.slice(2);
const { MemoryFileSystem, createWasi } = await import(pathToFileURL(root + '/port/web/wasi.js'));
const fs = new MemoryFileSystem();
for (const name of ['SnailMail.dat', 'SnailMailExtras.dat'])
  fs.write(name, new Uint8Array(await readFile(root + '/artifacts/bin/' + name)));
const wasi = createWasi(fs, { log() {} });
const module = await WebAssembly.compile(await readFile(root + '/port/zig-out/bin/snail-web.wasm'));
const snail = Object.fromEntries(WebAssembly.Module.imports(module)
  .filter(i => i.module === 'snail').map(i => [i.name, () => 0]));
const { exports: e } = await WebAssembly.instantiate(module, { wasi_snapshot_preview1: wasi.imports, snail });
wasi.bind(e.memory);
e._initialize();
e.snail_set_profile(Number(ultimate));
if (!e.snail_start(0)) throw new Error('startup failed');
const draws = {};
for (const seed of JSON.parse(seeds)) {
  e.snail_rand_seed(seed);
  draws[seed] = [e.snail_rand(), e.snail_rand(), e.snail_rand()];
}
const first = [];
for (let seed = 0; seed < 8191; ++seed) {
  e.snail_rand_seed(seed);
  first.push(e.snail_rand());
}
console.log(JSON.stringify({ draws, first }));
""")
    result = subprocess.run(
        ["node", str(probe), str(REPO_ROOT), str(int(ultimate)), json.dumps(SEEDS)],
        capture_output=True, text=True, check=True,
    )  # fmt: skip
    data = json.loads(result.stdout.splitlines()[-1])
    draws = {int(seed): values for seed, values in data["draws"].items()}
    if ultimate:
        # Android's RandSeed sets the index to seed % 8191 and Rand() steps it
        # before reading, so seed 0 draws from entry 1 on and 8190 wraps to 0.
        assert draws[0] == [18467, 6334, 26500]
        assert draws == {
            seed: [TABLE[(seed + k) % 8191] for k in (1, 2, 3)] for seed in SEEDS
        }
        assert data["first"] == TABLE[1:] + TABLE[:1]
    else:
        assert draws[0] == [38, 7719, 21238]
        assert draws == {seed: msvc_rand(seed, 3) for seed in SEEDS}
        assert data["first"] == [msvc_rand(seed, 1)[0] for seed in range(8191)]
