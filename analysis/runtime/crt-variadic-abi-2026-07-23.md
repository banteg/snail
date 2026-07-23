# Binary Ninja CRT variadic ABI recovery — 2026-07-23

The live Windows database had `sprintf` at `0x48b32c` pinned to
`int32_t(char*, char*)`. The function is the native cdecl CRT formatter: its
body seeds the argument cursor from the first stack slot after `format`, and 31
direct callsites across 18 functions push format-dependent values after the two
fixed parameters.

The recovered analysis contract is:

```c
int32_t __cdecl sprintf(char* buffer, const char* format, ...);
```

This is an ABI correction, not a source match guess. The matching scratches
already declare and call the same variadic function, and the restored arguments
are independently visible in native pushes. Representative recovered callers
now show:

- `initialize_intro_screen`: the image name passed to `"Intro/%s"`;
- `build_subgame_level`: `level_definition.parcel_count` passed to `"0/%i"`;
- `load_galaxy_layout`: the galaxy index and missing-record count;
- `format_time_trial_string`: the owned minute, second, and fractional fields;
- `load_object_definition`: the source path passed to `"%s/_Object.txt"`.

The last function also materializes as full HLIL again instead of the previous
empty `int32_t load_object_definition()` shell.

Applying the prototype exposed a replay defect: Binary Ninja can keep an
already-materialized function type until that function is explicitly queued for
reanalysis. `update_analysis_and_wait()` alone let the variadic type appear
during preview and then fall back to the stale fixed prototype. The shared
narrow-sync transaction now reanalyzes every changed prototype both after apply
and after rollback, and the CRT replay explicitly reanalyzes the complete
`sprintf` caller set so tracked caller HLIL cannot remain stale.

Replay with:

```sh
UV_CACHE_DIR=/tmp/snail-mail-uv-cache uv run python \
  tools/binja/sync_crt_variadic_prototypes.py \
  --target SnailMail_unwrapped.exe.bndb
```
