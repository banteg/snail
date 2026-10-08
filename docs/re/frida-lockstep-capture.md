# Lockstep capture

[`tools/frida/snailmail-lockstep.js`](../../tools/frida/snailmail-lockstep.js)
records a session of the original Windows game so the port can replay it
tick for tick and compare. Unlike the replay oracle, which only has what
high-score recordings store (lateral path, flags, z), a lockstep tape covers
everything a player does: menus, every mode, deaths, pickups, and frames to
compare renders against.

## What it records

One directory per session, `C:\share\snail\lockstep\<time>-<pid>\`:

- `tape.ndjson`
  - `session`: the module, script version, Frida version.
  - `files`: which of `SnailMail.cfg` and `ScoreA/B/C.dat` were copied to
    `start/` (the game reads them at startup, so the port must start from the
    same ones).
  - `startup`: the random warmup (the original draws `timeGetTime() % 1000`
    random numbers before constructing the game; this count is the only
    wall-clock input to the simulation), the RNG state after it, and the
    runtime config bytes.
  - `tick`, once per `cRGame::AI` call:
    - at entry, the input state the game logic reads, as the main loop left
      it after polling: held keys (DirectInput scan codes) this poll and the
      last, both input-controller slots, mouse position, button state and
      latch, wheel, and `g_render_queue_active`;
    - at exit, a snapshot: front-end and subgame state, level mode, the
      snail's position and velocity, score, lives, shooting tier, track
      offsets, RNG state, and `AI`'s return value.
  - `render`: a frame was rendered after `after` ticks. The original renders
    on its own cadence (several ticks per frame, or none), and the port
    replays that cadence too.
  - `frame`: a capture in `frames/`.
  - `fpu`: the x87 control word of the game thread (precision and rounding
    control), at startup, when the path template bank is built, and whenever
    it changes between ticks (script version 3; version 2's reader faulted).
- `frames/present-NNNNNN.bmp`: the game window, every 120th present and the
  first. Change `CAPTURE_EVERY` at the top of the script; 0 turns captures
  off.
- `start/`: the save files as they were at launch.

Addresses and field offsets in the script are generated from the symbol
manifests and the recovered headers (`uv run snail port lockstep-script
--write`), so they match what the port compiles.

## Setup (Windows)

1. Install Frida: `pip install frida-tools` (Frida 16.2 or newer).
2. Use the unwrapped gameplay image. In a checkout of this repo on the
   Windows machine, with the game's files in `artifacts\bin`:

   ```
   uv run snail unwrap
   ```

   or copy `artifacts/bin/SnailMail_unwrapped.exe` from the Mac into the
   game's directory, next to `SnailMail.dat`.
3. Optional but recommended: set the game to windowed mode in its Options
   once, before capturing. Frame captures read the screen, and a window is the
   most reliable case.

## Capturing

Spawn the game under Frida from its directory. Spawning matters: the warmup
happens before the first frame, so attaching to a running game misses it.

```
cd <game directory>
frida -f .\SnailMail_unwrapped.exe -l <repo>\tools\frida\snailmail-lockstep.js
```

The console prints the session directory. After the intro starts, check that
`frames\present-000001.bmp` exists and shows the game (not black). If it is
black, set `CAPTURE_EVERY = 0`; the tape is still useful without frames.

Always quit through the game's own Exit menu, so the last rows are written.

## Sessions to record

Short sessions are better than one long one; each is a separate replay.

1. **Menus** (about 1 minute): let the intro run a few seconds, skip it with
   Escape, visit New Game, High Scores (both banks), Options (change and
   restore a setting), Credits, then Exit.
2. **Tutorial**: New Game, Tutorial, play through, fall off at least once.
3. **Postal**: a postal level you have unlocked, with shooting, pickups, a
   death, and the level completion screen if you can.
4. **Challenge**: a challenge run to game over.
5. **Time Trial** and **Galaxy map**, if unlocked.
6. **Long run** (optional): a full postal level from start to finish; the
   longer the run, the stricter the comparison.

Each tape grows by about 3 MB per minute of play; frames add about 1.2 MB
each.

## Sending captures back

Zip `C:\share\snail\lockstep` (or the session folders you want compared) and
put the archive somewhere the Mac can read. Note next to each session what
you did in it.

## Comparing (Mac)

```
uv run snail port lockstep <session dir> [<session dir> ...]
```

For each session: convert the tape for the headless port, stage a game
directory with the session's `start/` files and the archive, replay every
tick with the recorded inputs and render cadence
(`port/shell/lockstep_tape.cpp`), and compare the port's snapshot, RNG state
and `cRGame::AI` result with the original's after every tick. The report
lists the first divergent tick with its fields, the largest float errors, and
any integer field that ever diverges.
