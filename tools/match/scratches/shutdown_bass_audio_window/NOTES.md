# shutdown_bass_audio_window @ 0x407b00

Owns the hidden BASS window/class shutdown path.

- The caller-side `ECX = 0x753c58` load proves
  `uninitialize_bass_audio_backend @ 0x4496d0` is an `AudioBackend` member even
  though its body does not read `this`.
- Destroys `g_bass_window` when present, then unregisters the `"BASS"` class
  with the WinMain-owned `g_application_instance`. Native jumps directly to
  unregistration after a successful destroy; the handle-zeroing store exists
  only after the fatal-error call on the destroy-failure path.
- Both Win32 failures dispatch the existing startup-fatal error helper; the
  unregister failure is emitted as the native tail return.
