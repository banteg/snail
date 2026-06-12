# Pinned — 41.46%, 39/43 insns, layout-only residual

Small function, so the two layout deltas weigh heavily on the score:
the original duplicates both error blocks in full (our build cross-jumps
the shared `report_errorf` tail), and registers shuffle (flags in eax vs
ecx, anchor via lea vs add). Same residual class as switch_track_mirror.
Block ORDER is confirmed early-return style: not-linked error first,
iteration-guard (0x40) error second, unlink last.

Semantics fully pinned:

- guard bits on +0x04: 0x200 = linked (error "List REMOVE" when clear),
  0x40 = iteration guard (error "List REMOVEnext" when set); both error
  paths still clear state (+0x80)
- unlink: next->prev = prev; prev ? prev->next = next : anchor->first
  (+0x04 of the anchor at game+0x5a8) = next
- freed slot pushes onto the free stack: this->next = anchor->free_top
  (+0x08), anchor->free_top = this
- exit writes: state = 0 interleaved between the flags reload and the
  `&= ~0x200` clear
