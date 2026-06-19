# initialize_voice_manager

`VoiceManager::initialize_voice_manager` parses `Voice/_Voice.txt`, builds the
16 named `VoiceSet` buckets, registers each listed `.ogg`, applies music/SFX/
voice normalization scales, reads the global voice frequency, and then resets
the manager cooldown state.

The native function is a `void` thiscall despite decompiler return noise. The
fall-through return leaves whatever helper result is in `eax`; the only real
API behavior is field initialization plus the final `reset_voice_manager()`.

Source-shape details retained:

- The `Voice/_Voice.txt` load keeps the `get_archive_data_base()` buffer as the
  text cursor and ignores the loader return, matching the native pre-call store.
- Set tag construction uses `rstrcpy_checked_ascii(set_tag, "Set:")` followed by
  CRT `strcat`, which VC6 expands into the observed `rep movsd`/`rep movsb`
  append block.
- Case 13 reuses the existing `g_tutorial_text` data string at `0x4a38e4`;
  emitting a fresh `"Tutorial"` literal creates a real masked operand mismatch.
- The scratch avoids register-forcing tricks. The main retained differences are
  register allocation around `ebx`/`ebp` and the line cursor, plus the placement
  of the missing-set error tail.
