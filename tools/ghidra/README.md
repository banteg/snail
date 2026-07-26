# Ghidra symbol probe

`decompile_symbol.py` is the bounded second-opinion path for Android, iOS, or
Windows functions. It currently defaults to Ghidra 12.1.2 and creates both the
project and Ghidra user home under a temporary directory, so headless analysis
does not mutate the normal GUI profile.

Prefer a unique demangled-name fragment over a raw address. ELF image bases,
Thumb entry bits, and port-specific layouts make raw cross-port addresses easy
to misapply. Use an exact hexadecimal entry address when the loader does not
import a local symbol, as can happen with Mach-O linker symbols:

```sh
uv run tools/ghidra/decompile_symbol.py \
  artifacts/android/unpacked/com.sandlotgames.snailmail.1/lib/armeabi-v7a/libsnailmail.so \
  SetShootFlags

uv run tools/ghidra/decompile_symbol.py \
  "artifacts/ios/unpacked/Snail Mail/Payload/iSM.app/iSM" \
  0x5f620
```

The probe fails closed when a name fragment is absent or ambiguous, or when no
function starts at an exact address. It prints the Ghidra version, selected
fully qualified function, entry point, and clean decompiled C on success. The
Java probe writes that payload to an isolated temporary file, so routine
analyzer startup logs are suppressed; a failed probe prints the script-error
block when available, otherwise only the bounded tail of Ghidra's diagnostics.
This also catches post-script failures because Ghidra may leave the headless
launcher status at zero.
