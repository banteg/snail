"""Background star streaks occlude the world in the original; Ultimate fixes it."""

import json
import shutil
import subprocess

import pytest

from snail.symbols import REPO_ROOT


@pytest.mark.skipif(
    shutil.which("node") is None
    or not (REPO_ROOT / "port/zig-out/bin/snail-web.wasm").exists()
    or not (REPO_ROOT / "artifacts/bin/SnailMail.dat").exists()
    or not (REPO_ROOT / "artifacts/bin/SnailMailExtras.dat").exists(),
    reason="needs node, the browser port build, and both game archives",
)
@pytest.mark.parametrize("ultimate", [False, True])
def test_starfield_depth_writes_leak_only_in_the_original(tmp_path, ultimate):
    probe = tmp_path / "starfield.mjs"
    probe.write_text("""
import { readFile } from 'node:fs/promises';
import { pathToFileURL } from 'node:url';
const root = process.argv[2];
const { MemoryFileSystem, createWasi } = await import(pathToFileURL(root + '/port/web/wasi.js'));
const fs = new MemoryFileSystem();
for (const name of ['SnailMail.dat', 'SnailMailExtras.dat'])
  fs.write(name, new Uint8Array(await readFile(root + '/artifacts/bin/' + name)));
const wasi = createWasi(fs, { log() {} });
const module = await WebAssembly.compile(await readFile(root + '/port/zig-out/bin/snail-web.wasm'));
const snail = Object.fromEntries(WebAssembly.Module.imports(module)
  .filter(i => i.module === 'snail').map(i => [i.name, () => 0]));
let memory, collect = false;
const stars = [], world = [], foreground = [];
snail.draw = (primitive, pointer, count, state) => {
  if (!collect) return;
  const s = new Int32Array(memory.buffer, state, 28);
  const v = new Float32Array(memory.buffer, pointer, count * 8);
  if (!s[16]) return;
  const draw = { write: s[17], func: s[18], count, texture: s[0] };
  const atStarDepth = count === 6 && [3, 11, 19, 27, 35, 43].every(i => v[i] === 50);
  if (atStarDepth && !s[20] && s[10]) stars.push(draw);
  else {
    world.push(draw);
    if (s[10]) foreground.push(draw);
  }
};
const { exports: e } = await WebAssembly.instantiate(module, { wasi_snapshot_preview1: wasi.imports, snail });
memory = e.memory;
wasi.bind(memory);
e._initialize();
e.snail_set_profile(Number(process.argv[3]));
if (!e.snail_start(0)) throw new Error('startup failed');
const step = n => { for (let i = 0; i < n; i++) e.snail_frame(1 / 60); };
const click = (x,y) => {
  e.snail_pointer(x,y); step(3); e.snail_button(0,1); step(3); e.snail_button(0,0); step(3);
};
step(600); e.snail_key(1,1); step(3); e.snail_key(1,0); step(100);
click(345,112); step(100); click(344,102); step(200);
collect = true;
step(1);
console.log(JSON.stringify({ stars, world, foreground }));
""")
    result = subprocess.run(
        ["node", str(probe), str(REPO_ROOT), str(int(ultimate))],
        capture_output=True, text=True, check=True,
    )
    draws = json.loads(result.stdout.splitlines()[-1])
    assert len(draws["stars"]) == 36
    assert {d["write"] for d in draws["stars"]} == {0 if ultimate else 1}
    assert {d["func"] for d in draws["stars"]} == {4}  # LEQUAL, still depth tested
    assert draws["world"] and draws["foreground"]
    assert {d["write"] for d in draws["world"]} == {1}
