# Ghidra symbol probe

`decompile_symbol.py` is the bounded second-opinion path for named Android or
Windows functions. It currently defaults to Ghidra 12.1.2 and creates both the
project and Ghidra user home under a temporary directory, so headless analysis
does not mutate the normal GUI profile.

Prefer a unique demangled-name fragment over a raw address. ELF image bases,
Thumb entry bits, and port-specific layouts make raw cross-port addresses easy
to misapply.

```sh
uv run tools/ghidra/decompile_symbol.py \
  artifacts/android/unpacked/com.sandlotgames.snailmail.1/lib/armeabi-v7a/libsnailmail.so \
  SetShootFlags
```

The probe fails closed when the fragment is absent or ambiguous and prints the
Ghidra version, selected fully qualified function, entry point, and decompiled
C on success.
