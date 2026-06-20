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

Current status: near-match. The operands and backend method calls are resolved,
but VC6 hoists the saved path load above the archive-index branch. Native keeps
that `esi = path` setup inside each branch.

Residual:

- Native reloads the original path into `esi` inside both load branches.
  Structured `if/else` source with a local `archive_index_records` gives the
  right branch layout and operands, but VC6 hoists `source_path = path` before
  the branch and reuses it in the filesystem path arm.
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
