"""Mobile road surfaces must use the same tiling contract as the PC road."""

import json
import shutil
import subprocess

import pytest

from snail.symbols import REPO_ROOT


@pytest.mark.skipif(
    shutil.which("node") is None
    or not (REPO_ROOT / "port/zig-out/bin/snail.wasm").exists()
    or not (REPO_ROOT / "artifacts/bin/SnailMail.dat").exists()
    or not (REPO_ROOT / "artifacts/bin/SnailMailExtras.dat").exists(),
    reason="needs node, snail.wasm, and both game archives",
)
def test_mobile_road_textures_repeat_like_pc_surfaces(tmp_path):
    for name in ("SnailMail.dat", "SnailMailExtras.dat"):
        (tmp_path / name).symlink_to(REPO_ROOT / "artifacts/bin" / name)
    probe = tmp_path / "texture_sampling.mjs"
    probe.write_text(
        """
import { readFile } from 'node:fs/promises';
import { WASI } from 'node:wasi';
const wasi = new WASI({
  version: 'preview1', args: ['snail.wasm', '--extras', '--ticks', '1'],
  env: { ...process.env, PWD: process.cwd() }, preopens: { '/': '/' },
  returnOnExit: true,
});
const module = await WebAssembly.compile(await readFile(process.argv[2]));
const instance = await WebAssembly.instantiate(module, wasi.getImportObject());
wasi.start(instance);
const memory = Buffer.from(instance.exports.memory.buffer);
const result = {};
for (const kind of ['Track', 'Slide']) for (const index of [0, 4, 5, 6]) {
  const name = `Objects/World00/${kind}${index}.tga`;
  const needle = Buffer.from(name + '\\0');
  const dimension = index === 0 ? 256 : 128;
  // Read the registered cRTexture record, excluding identical path literals.
  // sprite.h fixes flags/width/height/name/mip_levels at 0/4/8/12/160.
  for (let p = memory.indexOf(needle); p >= 0; p = memory.indexOf(needle, p + 1)) {
    const base = p - 12;
    if (base >= 0 && memory.readInt32LE(base + 4) === dimension
        && memory.readInt32LE(base + 8) === dimension) {
      result[name] = {
        repeat: !!(memory.readUInt32LE(base) & 0x1000),
        mipLevels: memory.readInt32LE(base + 160),
      };
    }
  }
}
console.log(JSON.stringify(result));
"""
    )
    process = subprocess.run(
        ["node", str(probe), str(REPO_ROOT / "port/zig-out/bin/snail.wasm")],
        cwd=tmp_path, capture_output=True, text=True, check=True,
    )
    textures = json.loads(process.stdout.splitlines()[-1])
    for kind in ("Track", "Slide"):
        reference = textures[f"Objects/World00/{kind}0.tga"]
        assert reference == {"repeat": True, "mipLevels": 2}
        for index in (4, 5, 6):
            assert textures[f"Objects/World00/{kind}{index}.tga"] == reference
