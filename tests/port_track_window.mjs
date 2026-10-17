// Probe the active track window in each profile on Pro 1, whose first
// segment the test turns into a plain platform.
import { LAYOUT, openMobileGame } from './port_mobile_runtime.mjs';

const samples = [];
for (const ultimate of [0, 1]) {
  const { e, sub, memory } = await openMobileGame(process.argv[2]);
  const player = sub + LAYOUT.player;
  const read = () => {
    const m = memory();
    return {
      z: m.readFloatLE(player + LAYOUT.player_z),
      window: m.readFloatLE(player + LAYOUT.active_window_min_z),
      scanEnd: m.readInt32LE(sub + LAYOUT.runtime_row_scan_end),
      finish: m.readInt32LE(sub + LAYOUT.completion_row_start),
    };
  };
  e.snail_set_profile(ultimate);
  // Run far enough that the scan has moved on under this profile's look-ahead.
  for (let i = 0; i < 3; ++i) e.snail_frame(0.4);
  const running = read();

  // The finish banner just under 48 rows ahead, and still over 46 once the snail has moved.
  memory().writeFloatLE(running.z + 47.5, sub + LAYOUT.finish_banner_z);
  e.snail_frame(1 / 60);
  const banner = (memory().readUInt32LE(sub + LAYOUT.finish_banner_flags) & 0x20) !== 0; // BOD_FLAG_RENDER_ENABLED

  // Move the finish line just behind the snail.
  memory().writeInt32LE(Math.floor(read().z) - 1, sub + LAYOUT.completion_row_start);
  e.snail_frame(1 / 60);
  samples.push({ ultimate, running, banner, finished: read() });
}
console.log(JSON.stringify(samples));
