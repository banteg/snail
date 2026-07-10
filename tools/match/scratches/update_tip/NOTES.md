# Exact match

`update_tip` now matches at 100.00%, 51/51 instructions, with nine clean masked
operands.

The scratch covers the full recovered behavior:

- hide the main tip widget while `Game::pause_gate` is set;
- unhide it otherwise;
- consume either OK or Disable button click by clearing widget flag `0x20`;
- restore the previous frontend outer owner, kill the tip widgets, unhide all
  borders, and clear `active`;
- advance auto-dismiss progress for timed tips and kill the slot after it
  passes `1.0f`.

The exact source shape duplicates the clicked-tip teardown block for the OK and
Disable buttons. That keeps each candidate button pointer in `ecx` through the
flag clear and matches the native `[ecx+0x1a0]` store. A shared `||` condition
or source `goto` tail is semantically equivalent, but makes VC6 materialize
`&button->widget_flags` and adds two `lea` instructions.

Rejected source-shaped probes:

- preserving and returning call results for the helper and widget methods added
  extra `eax` save/restore moves;
- a `_DWORD*`/word-index view of the button widgets emitted the same code as the
  named `FrontendWidget::widget_flags` field, so the named field is kept;
- direct `button->widget_flags &= ~0x20`, explicit label/goto button checks,
  and a `flags_ptr` helper all compile back to the old 73.08% shared-tail
  shape;
- a shared `widget_main` local made the pause gate use a shorter prefix; using
  branch-local `slot->widget_main` is the accepted source shape.

Keep pinned unless a new source idiom explains the button pointer ownership.

2026-06-16 type consolidation: the local `FrontendWidget` view was replaced by
`frontend_widget.h`. The matcher remained at 73.08% until the clicked-tip body
was duplicated.

2026-06-16 type consolidation: the local `TipSlot` and
`TipMessageDefinition` views were replaced by shared `tip_manager.h`. The
matcher still reported 73.08%, 51 target instructions versus 53 candidate
instructions, preserving the same button-pointer residual.

2026-06-21 clicked-button split: duplicating the OK and Disable clicked-teardown
body exactly matches native. Focused Wibo reports 100.00%, 51/51 instructions,
51/51 prefix, and nine clean masked operands.

2026-07-10 root-owner promotion: the exact source now restores
`GamePlayer[0].frontend_state` and calls the owned
`GameRoot::border_manager`, replacing raw root offsets without changing a byte.
