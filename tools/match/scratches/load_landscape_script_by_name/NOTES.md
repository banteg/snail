# load_landscape_script_by_name @ 0x4182f0

Structure-first recovery for the landscape script cache loader.

- `this+0x5a0` is the signed loaded-script count.
- Records start at `this+0x5a4` and are 0x124-byte `LandscapeScriptRecord`
  entries: id, name, texture id/path/split flag, object index, fog color, and
  distort.
- The two calls to `0x449c00` are the release-stripped debug-report stub:
  `"Loading backdrop texture %s"` and `"Landscape: %s imported\n"`.
- Missing `Picture:` intentionally skips only the texture block, then still
  parses `Landscape:` and `Distort:` before adding the script.

2026-06-20 exact match: the cache scan now keeps an explicit empty-count
precheck, then uses a `while (index < script_count)` loop. That preserves the
native `edi` index / `ebp` name-cursor ownership and avoids VC6's earlier
duplicated compare-call layout. Focused Wibo now reports 100.00%, 386/386
instructions, full prefix, and 63 clean masked operands.
