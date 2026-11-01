// Read the initialized objects before any course replaces Track0/Slide0 with its palette.
import assert from 'node:assert/strict';
import {LAYOUT, openGame} from './port_frontend.mjs';

for (const ultimate of [false, true]) {
  const {e, sub, memory} = await openGame(process.argv[2], ultimate, 'MeshProbe');
  const m = memory();
  const pair = slot => sub + LAYOUT.paths + 2 * slot * LAYOUT.path;
  const strip = (path, hand) => m.readUInt32LE(path + hand * LAYOUT.path + 0x24);

  // WORM has no seam vertex at the end of a row. Both profiles allocate only
  // the 400 real vertices. Original reflects X, Ultimate builds the hands alike.
  const worm = [0, 1].map(hand => strip(pair(24), hand));
  for (const obj of worm) assert.equal(m.readUInt32LE(obj + 0x2c), 400);
  assert.equal(m[pair(24) + LAYOUT.path + 0x3c], ultimate ? 0 : 1);
  const wormFace = m.readUInt32LE(worm[0] + 0x5c), wormTexture = m.readUInt32LE(wormFace + 0xc);
  assert.deepEqual([m.readUInt32LE(wormTexture + 4), m.readUInt32LE(wormTexture + 8)],
    ultimate ? [16, 64] : [32, 32]);
  const vertices = worm.map(obj => m.readUInt32LE(obj + 0x38));
  for (let i = 0; i < 400; ++i) {
    const [x0, x1] = vertices.map(p => m.readFloatLE(p + 12 * i));
    assert.equal(x1, ultimate ? x0 : -x0);
  }

  // Each object retains its authored quads and their textures after grouping.
  function faceMaterials(obj) {
    const textures = new Set(), warningU = new Set(), entryFaces = {};
    const count = m.readUInt32LE(obj + 0x54), faces = m.readUInt32LE(obj + 0x5c);
    for (let i = 0; i < count; ++i) {
      const face = faces + i * 0x30, name = m.readUInt32LE(face + 0xc) + 0xc;
      const texture = m.toString('ascii', name, m.indexOf(0, name)).split('/').at(-1);
      textures.add(texture);
      const first = m.readUInt16LE(face + 2), second = m.readUInt16LE(face + 4);
      if (first + second === 1) entryFaces[first] = texture;
      if (texture === 'TrackWarn.tga') {
        for (let j = 0; j < 4; ++j) warningU.add(m.readFloatLE(face + 0x10 + 8 * j));
      }
    }
    return {textures: [...textures].sort(), warningU: [...warningU].sort((a, b) => a - b), entryFaces};
  }
  for (const hand of [0, 1]) {
    for (const tramp of ultimate ? [pair(31), e.snail_extra_path_pair(7)] : [pair(31)]) {
      assert.deepEqual(faceMaterials(strip(tramp, hand)).warningU,
        ultimate ? [0.375, 0.5, 0.625] : [0, 0.125, 0.25]);
    }
    if (ultimate) {
      // Shared HILL, VALLEY, SBEND, CAGE2, SCREW, SNAKE, START, TWISTER2,
      // TOAD variants, followed by the three mobile-only narrow S-bends.
      const strips = [8, 11, 12, 13, 14, 15, 21, 29, 36, 45, 46, 47, 48, 49, 50].map(pair);
      strips.push(...[1, 2, 3].map(i => e.snail_extra_path_pair(i)));
      for (const path of strips) {
        const {textures, entryFaces} = faceMaterials(strip(path, hand));
        const mirrored = m[path + hand * LAYOUT.path + 0x3c];
        assert.deepEqual(textures, ['Back.tga', 'Slide0.tga']);
        assert.equal(entryFaces[mirrored], 'Slide0.tga');
        assert.equal(entryFaces[1 - mirrored], 'Back.tga');
      }
    }
  }
}
