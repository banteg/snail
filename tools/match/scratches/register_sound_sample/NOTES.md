# register_sound_sample @ 0x432f10

First scratch for the registered sound sample entry point.

- Focused Wibo result: 2026-06-18, 93.07%, 50/51 candidate/target
  instructions, prefix 2/51, masked operands 19 ok, no unresolved or
  mismatched operands.
- If the archive index is loaded, reads the sample path into the shared music
  memory buffer and registers from bytes.
- Otherwise registers the sample directly from the filesystem path.
- Stores the original sample path in the 256-entry registered-sample name table
  searched by `find_registered_sound_sample_id_by_name`.
- Increments `g_registered_sound_sample_count` and reports the native
  `RSHELL_SOUND_MAX` error if the table reaches 256 entries.

Current status: proof-grade match, 100.00%, 51/51 target instructions, prefix
51/51, masked operands 19 ok.

Resolved:

- Native reloads the original path into `esi` inside both load branches because
  the archive byte count is a real local, not the caller's `path` stack slot.
  With `int sample_size`, `&sample_size` lands at `[esp+0x8]` after `push esi`
  in the archive arm, and the source no longer aliases the original path value.
- 2026-06-20 rejected probes: branch-local `archive_path`/`filesystem_path`
  aliases and an explicit archive-arm `goto sample_loaded` compiled identically
  to the hoisted near-match. Moving the filesystem `source_path = path` after
  the backend call recovered the late load but regressed the call and count tail
  to 77.67%, so the simpler structured form remains.
- 2026-06-20 global-test retry: removing the `archive_index_records` local and
  testing `g_archive_index_records` directly is codegen-neutral at 93.07%.
  That rules out the saved global alias as the reason for the early `path` load;
  the remaining residual is specifically VC6's branch-invariant path reload
  scheduling.
- 2026-06-20 audio-family retry: forcing `source_path` into a `register` local
  is codegen-neutral at 93.07%. Duplicating the shared store/count/error tail
  inside both backend-load arms regresses to 42.11% by emitting real duplicate
  tail code, so the single shared tail is the durable source shape.
- 2026-06-20 larger-chunk retry: duplicating only the
  `rstrcpy_checked_ascii` path-name copy inside both backend-load arms also
  fails to tail-merge; it emits a 60-instruction 30.63% candidate. Keep the
  single shared copy/count/error tail.
- 2026-06-20 audio-family audit: spelling the archive-arm saved path as
  `&path[0]` is codegen-neutral at 93.07%, so expression spelling is not the
  reason native keeps the `esi = path` reloads branch-local. Rechecking the
  filesystem-arm delayed `source_path = path` shape still regresses to 77.67%:
  it recovers the late reload but moves the backend call and count-tail register
  ownership away from native. Keep the structured shared-tail source.
- 2026-06-20 proof: binding `source_path = path` inside the archive/filesystem
  call arguments is codegen-neutral at 93.07%, confirming the residual was not
  expression spelling. Replacing the `(int*)&path` out parameter with
  `int sample_size` matches 100.00%; the previous scratch had misidentified the
  native `lea [esp+0x8]` as `&path` when it is the local byte-count slot after
  saving `esi`.

## 2026-07-14 registered-sample owner closure

The native exhaustion diagnostic explicitly names `RSHELL_SOUND_MAX` and
`RShell.h`. That evidence now backs a shared 256-slot capacity in
`audio_system.h`, alongside the registered-name table and live count. Reset,
registration, and lookup therefore borrow one owner instead of repeating local
extern declarations, while the overflow clamp derives from the recovered
capacity.

All three normalized listings remain byte-identical and proof-grade:

- reset: `10cc8c23057039806e8185c1f8ac869d1ad353ce65a0c6701136ad931605ae75`
- register: `4c26a7c9c45bbaa1fc167475662dda1dba4e7ff8527e74f64df1dc1a5adcd335`
- lookup: `a5e0964564e48d057ecf9330e790301c5e03bfbb75aae62678151b8bf5cedc7b`
