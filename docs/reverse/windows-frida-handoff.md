# Windows Frida Handoff

This handoff is for the Windows-side agent that will run the original game under Frida and collect runtime evidence for the remaining RE gaps.

Use this together with:

- [docs/reverse/frida-runtime-trace.md](/Users/banteg/dev/banteg/snail-mail/docs/reverse/frida-runtime-trace.md)
- [docs/reverse/path-system.md](/Users/banteg/dev/banteg/snail-mail/docs/reverse/path-system.md)
- [tools/frida/snailmail-runtime-trace.js](/Users/banteg/dev/banteg/snail-mail/tools/frida/snailmail-runtime-trace.js)

## Goal

Static RE is now strong on:

- `SnailMail.dat`
- `.x2` rendering and animation
- `SEGMENTS/*.TXT` and `LEVELS/*.TXT`
- the hardcoded `Path=` name table
- the main track-build and render-cache pipeline

The remaining gaps are runtime-behavior questions:

- when `P/p` rows become real attachment-follow transitions
- how often `Salt:` spawns without authored `&` rows
- what authored `JetPack=Off` rows do in live play
- what `NoFall` rows actually suppress at runtime
- how often `M` rows turn into slug spawns in real play

## Required Setup

From the Windows machine, have all of these available:

1. A checkout or copy of this repo.
2. The original game files, especially [SnailMail_unwrapped.exe](/Users/banteg/dev/banteg/snail-mail/artifacts/bin/SnailMail_unwrapped.exe).
3. Frida CLI installed and working on Windows.
4. The trace script at [tools/frida/snailmail-runtime-trace.js](/Users/banteg/dev/banteg/snail-mail/tools/frida/snailmail-runtime-trace.js).

Recommended quick checks:

```powershell
frida --version
Get-ChildItem .\tools\frida\snailmail-runtime-trace.js
Get-ChildItem .\artifacts\bin\SnailMail_unwrapped.exe
```

## Important Targeting Rules

- Attach to `SnailMail_unwrapped.exe`, not `SnailMail.exe`.
- The script is written for the 32-bit RWG runtime.
- The script resolves addresses relative to the loaded module base, so ASLR is fine as long as the module is really `SnailMail_unwrapped.exe`.
- Keep captures short and focused. Several short NDJSON files are much better than one giant noisy trace.

## Current Hook Set

The script currently hooks these points:

- `0x437eb0` `normalize_level_runtime_fields`
- `0x429ae0` `find_segment_path_index_by_name`
- `0x42c770` `try_enter_track_attachment_from_swept_motion`
- `0x420c40` `begin_track_attachment_follow_state`
- `0x43da80` `spawn_track_garbage_hazard`
- `0x441560` `spawn_salt_runtime_entity`
- `0x441740` `deactivate_salt_runtime_entity`
- `0x43dc80` `spawn_slug_runtime_entity`
- `0x447040` `get_track_cell_row_index` for row tagging when safe

Expected event names in the NDJSON:

- `module_ready`
- `hooks_installed`
- `level_start`
- `path_lookup`
- `attachment_probe`
- `attachment_begin`
- `garbage_spawn`
- `salt_spawn`
- `salt_deactivate`
- `slug_spawn`

## How To Run

Run the spawn flow from `artifacts\bin` on the Windows machine so the game starts with the expected working directory.

Spawn the gameplay binary under Frida:

```powershell
cd .\artifacts\bin
frida -f .\SnailMail_unwrapped.exe -l ..\..\tools\frida\snailmail-runtime-trace.js
```

If spawn still exits immediately, start the game normally from `artifacts\bin` and attach from the repo root instead:

```powershell
cd C:\path\to\repo
frida -n SnailMail_unwrapped.exe -l .\tools\frida\snailmail-runtime-trace.js
```

The script now creates `C:\share\snail\frida\` itself and writes NDJSON there with a generated filename like `snailmail-trace-20260308-153000-1234.ndjson`.
Keep the first console line from each run because it prints the exact file path that was opened.

## Capture Matrix

Run these captures in roughly this order.

### 1. Path Attachment Capture

Purpose:

- prove the full chain from `Path=<name>` lookup to `attachment_probe` to `attachment_begin`

Best target:

- `LEVELS/ARCADE028.TXT`

Why:

- strongest current path-heavy arcade target
- many repeated public path families

Output location:

- generated under `C:\share\snail\frida\`
- copy or rename the resulting file to `arcade028-path.ndjson` before handing it back

What to do in-game:

1. Start `Twisterific`.
2. Play until at least one obvious path-follow section is entered.
3. Quit once `attachment_begin` has clearly fired.

Success criteria:

- at least one `path_lookup`
- at least one `attachment_probe`
- at least one `attachment_begin`

### 2. Scalar Salt Capture

Purpose:

- confirm salt spawning when `Salt:` is high but authored `&` rows are absent

Best target:

- `LEVELS/ARCADE039.TXT`

Why:

- current top scalar-salt level
- static corpus has `Salt:100` and `0` explicit `&` rows

Output location:

- generated under `C:\share\snail\frida\`
- copy or rename the resulting file to `arcade039-salt.ndjson` before handing it back

What to do in-game:

1. Start `Sodium Squared`.
2. Play long enough for ambient hazard spawning to occur.
3. Quit after multiple `salt_spawn` or after a few minutes if nothing fires.

Success criteria:

- one `level_start` showing the normalized salt scalar
- at least one `salt_spawn` or a clean negative result after a reasonable play window

### 3. Authored Salt And Ring Capture

Purpose:

- separate authored `&` behavior from scalar salt
- observe ring effect rows in a controlled tutorial flow

Best target:

- `LEVELS/TUTORIAL.TXT`

Why:

- strongest combined authored-salt and ring tutorial target
- static clue: `Salt:0`, so any `salt_spawn` should correlate with authored rows rather than the scalar fallback

Output location:

- generated under `C:\share\snail\frida\`
- copy or rename the resulting file to `tutorial-salt-ring.ndjson` before handing it back

Success criteria:

- `level_start`
- ring-heavy progression in a low-noise level
- any `salt_spawn` behavior with `Salt:0`

### 4. JetPack-Off Capture

Purpose:

- observe live response on authored `JetPack=Off` rows

Best target:

- `LEVELS/ARCADE025.TXT`

Why:

- currently the cleanest level for explicit `JetPack=Off`

Output location:

- generated under `C:\share\snail\frida\`
- copy or rename the resulting file to `arcade025-jetpackoff.ndjson` before handing it back

Success criteria:

- `level_start`
- clear passage through the `JetPackOff` segment
- useful correlation between authored rows and observed movement or timer behavior

### 5. No-Fall Capture

Purpose:

- observe how trampoline-heavy `NoFall` content behaves in live play

Best target:

- `LEVELS/ARCADE047.TXT`

Why:

- strongest repeated `NoFall` exposure in the current corpus

Output location:

- generated under `C:\share\snail\frida\`
- copy or rename the resulting file to `arcade047-nofall.ndjson` before handing it back

### 6. Slug Capture

Purpose:

- confirm whether dense `M` rows really drive slug spawns in the expected way

Best target:

- `LEVELS/ARCADE029.TXT`

Why:

- best current slug-like level from the local planner

Output location:

- generated under `C:\share\snail\frida\`
- copy or rename the resulting file to `arcade029-slugs.ndjson` before handing it back

## What To Hand Back

After each run, keep:

- the raw NDJSON file
- the in-game level name
- a short human note with what you actually did
- whether the run ended normally, crashed, or got stuck

Good note format:

```text
arcade028-path.ndjson
Level: Twisterific
Actions: started level, stayed center lane, entered first visible path section, quit after first attachment follow
Notes: saw one obvious path transition near TwisterA/TwisterB segment
```

## How To Summarize After Copying Back

Once the NDJSON files are back in this repo on macOS or Linux, summarize them from the repo root:

```bash
uv run snail trace summary /path/to/arcade028-path.ndjson
uv run snail trace summary /path/to/arcade039-salt.ndjson
uv run snail trace summary /path/to/tutorial-salt-ring.ndjson
uv run snail trace plan --limit 5
```

## Known Static Context

The Windows agent should assume all of these are already established statically:

- `Path=<name>` resolves through a `51`-entry hardcoded table in RWG.
- Most public path names now map to concrete constructor families in the world-init block.
- `WARP` is the only public path slot still missing from that aligned constructor table.
- `P/p` cells install runtime attachment pointers on neighboring cells.
- the main player update can enter a dedicated attachment-follow state from those attachments.
- `Salt:` and authored `&` are not the same system.
- `JetPack=Off` seeds runtime `0x8000`, but `0x8000` is later reused by edge-variant logic too.
- `NoFall` is live runtime state and already affects glyph normalization.

## Open Questions To Prioritize

- Which named `Path=` families actually produce `attachment_begin` events in live play?
- Do high `Salt:` levels spawn salt hazards without any authored `&` rows?
- Does `Salt:0` plus authored `&` still produce `salt_spawn` in the expected rows?
- What concrete gameplay effect shows up on authored `JetPack=Off` rows?
- How often do `M`-heavy levels actually call `spawn_slug_runtime_entity`?

## If Something Goes Wrong

- If no `module_ready` or `hooks_installed` event appears, you are probably attached to the wrong process.
- If the game launches but no events appear, attach to `SnailMail_unwrapped.exe` directly instead of the wrapper.
- If output is too noisy, stop the run and switch to a shorter target level instead of letting one huge trace grow.
- If the game crashes immediately under Frida, keep the failing NDJSON or console output anyway. Even a failed launch is useful if it happens consistently.
