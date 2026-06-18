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
