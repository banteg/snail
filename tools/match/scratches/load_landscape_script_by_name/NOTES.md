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

Current focused result is 88.95%, with 392/386 instructions, 63 masked operands
ok, and no unresolved or mismatched operands. Remaining expected gaps are mostly
the cache-scan register/loop layout, VC6 local-buffer placement, stack cleanup
scheduling around varargs/helper calls, and label layout around the
split-texture path.
