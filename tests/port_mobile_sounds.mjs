// Start each profile and list the samples it registers, then play Pro 1 in
// each and record, tick by tick, the sounds Android changed: the damage
// warning's postalloop, the invincibility start and upramp.
import { createHash } from 'node:crypto';
import { LAYOUT, openMobileGame, startGame } from './port_mobile_runtime.mjs';

const [wasm, soundsJson] = process.argv.slice(2);
const named = JSON.parse(soundsJson);  // md5 of a sample's file -> name

function md5(e, bytes, size) {
  return createHash('md5').update(new Uint8Array(e.memory.buffer, bytes, size)).digest('hex');
}

// Every sample a start registers, in order, by name or md5.
async function registered(ultimate) {
  let e;
  const samples = [];
  await startGame(wasm, {
    ready: exports => { e = exports; },
    sound_create: (sound, bytes, size) => {
      const hash = md5(e, bytes, size);
      samples.push(named[hash] ?? hash);
    },
  }, ultimate);
  return samples;
}

async function record(ultimate) {
  let e, game, tick = 0, riding = 0;
  const sounds = {}, channels = {}, events = [];
  const presenter = {
    ready: exports => { e = exports; },
    sound_create: (sound, bytes, size) => {
      const name = named[md5(e, bytes, size)];
      if (name) sounds[sound] = name;
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
  let vy = 0, launch;
  for (; tick < 1200; ++tick) {
    const memory = game.memory();
    if (tick === 0)
      memory.writeFloatLE(1, player + LAYOUT.gauge_fill);  // the warning starts
    if (tick === 170)
      memory.writeFloatLE(0.001, player + LAYOUT.gauge_fill);  // and stops as the gauge empties
    if (tick === 200)
      memory.writeInt32LE(7, player + LAYOUT.shooting_tier);  // invincible, firing pw7
    if (launch && !launch.rewound && launch.falling && Math.abs(vy) < 0.01) {
      // Landed past the first ramp: back 3 rows before it, as a new level or
      // life puts the snail back at its start.
      memory.writeFloatLE(launch.z - 3, player + LAYOUT.player_z);
      launch.rewound = true;
    }
    riding = memory.readUInt8(player + LAYOUT.follow_active);  // on a path as the tick starts
    e.snail_frame(1 / 60);
    // A ramp or the SuperTramp sets the snail rising.
    const rising = game.memory().readFloatLE(player + LAYOUT.player_vy);
    if (rising > 0 && vy <= 0) {
      const z = game.memory().readFloatLE(player + LAYOUT.player_z);
      events.push({ tick, launch: z, riding });
      launch ??= { tick, z };
    }
    vy = rising;
    if (launch && vy < -0.05) launch.falling = true;
  }
  return events;
}

console.log(JSON.stringify({
  registered: { original: await registered(0), ultimate: await registered(1) },
  original: await record(0),
  ultimate: await record(1),
}));
