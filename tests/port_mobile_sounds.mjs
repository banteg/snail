// Play Pro 1 in each profile and record, tick by tick, the sounds Android
// changed: the damage warning's postalloop, the invincibility start and upramp.
import { createHash } from 'node:crypto';
import { LAYOUT, openMobileGame } from './port_mobile_runtime.mjs';

const [wasm, soundsJson] = process.argv.slice(2);
const named = JSON.parse(soundsJson);  // md5 of a sample's file -> name

async function record(ultimate) {
  let e, game, tick = 0, riding = 0;
  const sounds = {}, channels = {}, events = [];
  const presenter = {
    ready: exports => { e = exports; },
    sound_create: (sound, bytes, size) => {
      const md5 = createHash('md5').update(new Uint8Array(e.memory.buffer, bytes, size)).digest('hex');
      if (named[md5]) sounds[sound] = named[md5];
    },
    channel_play: (channel, sound, bus, volume, pan, frequency, loop) => {
      if (!sounds[sound]) return;
      channels[channel] = sounds[sound];
      const z = game.memory().readFloatLE(game.sub + LAYOUT.player + LAYOUT.player_z);
      events.push({ tick, play: sounds[sound], loop, z, riding });
    },
    channel_stop: channel => {
      if (channels[channel]) events.push({ tick, stop: channels[channel] });
    },
  };
  game = await openMobileGame(wasm, presenter);
  e.snail_set_profile(ultimate);
  const player = game.sub + LAYOUT.player;
  for (; tick < 1200; ++tick) {
    const memory = game.memory();
    if (tick === 0)
      memory.writeFloatLE(1, player + LAYOUT.gauge_fill);  // the warning starts
    if (tick === 170)
      memory.writeFloatLE(0.001, player + LAYOUT.gauge_fill);  // and stops as the gauge empties
    if (tick === 200)
      memory.writeInt32LE(7, player + LAYOUT.shooting_tier);  // invincible, firing pw7
    riding = memory.readUInt8(player + LAYOUT.follow_active);  // on a path as the tick starts
    e.snail_frame(1 / 60);
  }
  return events;
}

console.log(JSON.stringify({ original: await record(0), ultimate: await record(1) }));
