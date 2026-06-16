# Source-shaped pinned match

`update_tip` currently matches at 73.08%, 51 target instructions versus 53
candidate instructions, with an 11/51 exact prefix.

The scratch covers the full recovered behavior:

- hide the main tip widget while the gameplay presentation gate is suspended;
- unhide it otherwise;
- consume either OK or Disable button click by clearing widget flag `0x20`;
- restore the previous frontend outer owner, kill the tip widgets, unhide all
  borders, and clear `active`;
- advance auto-dismiss progress for timed tips and kill the slot after it
  passes `1.0f`.

The remaining localized residual is codegen shape, not a known semantic gap.
Native keeps the candidate button pointer in `ecx` and stores to
`[ecx+0x1a0]`; the best typed source found so far keeps the pointer in `eax`,
materializes `&button->widget_flags` in `ecx`, and stores to `[ecx]`. This adds
two `lea` instructions and shifts branch labels, which makes the percentage look
worse than the semantic gap.

Rejected source-shaped probes:

- preserving and returning call results for the helper and widget methods added
  extra `eax` save/restore moves;
- a `_DWORD*`/word-index view of the button widgets emitted the same code as the
  named `FrontendWidget::widget_flags` field, so the named field is kept;
- explicit label/goto button checks moved the clicked teardown block after the
  timed-tip block and regressed the score;
- a shared `widget_main` local made the suspend gate use a shorter prefix; using
  branch-local `slot->widget_main` is the accepted source shape.

Keep pinned unless a new source idiom explains the button pointer ownership.

2026-06-16 type consolidation: the local `FrontendWidget` view was replaced by
`frontend_widget.h`. The matcher remains at 73.08%, preserving the known
button-pointer residual described above.

2026-06-16 type consolidation: the local `TipSlot` and
`TipMessageDefinition` views were replaced by shared `tip_manager.h`. The
matcher still reports 73.08%, 51 target instructions versus 53 candidate
instructions, preserving the same button-pointer residual.
