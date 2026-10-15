import { openMobileGame } from './port_mobile_runtime.mjs';

const game = await openMobileGame(process.argv[2]);
const { e, sub } = game;
const rates = [];
for (const extras of [0, 1]) {
  for (const mode of [0, 1, 3, 4, 7]) {
    for (const fill of [0.5, 0.1]) {
      for (const hover of [0, 1]) {
        e.snail_set_extras(extras);
        let memory = game.memory();
        const player = sub + 0x3bb764;
        memory.writeInt32LE(2, sub + 0x3c);
        memory.writeInt32LE(mode, sub + 0x40);
        memory.writeFloatLE(1, sub + 0x30);
        memory.writeFloatLE(20, player + 0x70);
        memory.writeInt32LE(40, sub + 0x58);
        memory.writeInt32LE(2, player + 0x3c4);
        memory.writeFloatLE(fill, player + 0x3c4 + 0x20);
        memory.writeFloatLE(fill, player + 0x3c4 + 0x1c);
        memory.writeInt32LE(hover, player + 0x275c);
        memory.writeFloatLE(0.6, player + 0x2750 + 0x20c);
        e.snail_frame(1 / 60);
        memory = game.memory();
        rates.push({
          extras, mode, fill, hover,
          rate: memory.readFloatLE(sub + 0x38),
          z: memory.readFloatLE(player + 0x70),
          end: memory.readInt32LE(sub + 0x58),
          boost: memory.readInt32LE(player + 0x3c4),
          display: memory.readFloatLE(player + 0x3c4 + 0x20),
          hoverState: memory.readInt32LE(player + 0x275c),
          intensity: memory.readFloatLE(player + 0x2750 + 0x20c),
        });
      }
    }
  }
}
const memory = game.memory();
// Windows field offsets plus the port's extra 400 cell/row records.
const catalog = sub + 0x10014cc + 400 * (8 * 84 + 244);
const count = memory.readInt32LE(catalog);
const segments = {};
for (let i = 0; i < count; ++i) {
  const entry = catalog + 4 + i * 0x4088;
  const name = memory.toString('utf8', entry + 0x40, memory.indexOf(0, entry + 0x40)).toUpperCase();
  if (['CAGE2.TXT', 'FINISH.TXT', 'TWISTER2.TXT'].includes(name))
    segments[name] = memory.readInt32LE(entry + 0x84);
}
e.snail_save();

const swingGame = await openMobileGame(process.argv[2]);
const swing = [];
for (let frame = 0; frame < 600; ++frame) {
  const player = swingGame.sub + 0x3bb764;
  const memory = swingGame.memory();
  memory.writeInt32LE(2, player + 0x308);
  memory.writeInt32LE(2, player + 0x3c4);
  memory.writeFloatLE(0.5, player + 0x3c4 + 0x1c);
  swingGame.e.snail_frame(0.1);
  if (swingGame.e.snail_swaying_ring_count() > 0)
    swing.push(swingGame.e.snail_swaying_ring_x());
  if (swing.length >= 15) break;
}
console.log(JSON.stringify({ rates, catalogCount: count, segments, swing }));
