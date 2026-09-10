# cRBorderStack::Perform @ 0x404360

## 2026-09-11 inline-table certification

The unchanged source now compares at **100%**, 138/138 code
instructions plus 16 bytes of explicitly compared jump-table data. All
1 reference audits are clean and positional. Encoded-body proof is
**exact**.
This is corrected table-data accounting, not newly reconstructed source code.

The [proof report](../../inline-jump-table-proof-20260911.md) and
[receipt](../../inline-jump-table-proof-20260911.json) preserve the full source,
compiled-object identity, data entries, reference audits, comparison ranges, and
encoded-body evidence. Earlier measurements below are historical.

Exact match: 100.00%, 137/137 instructions, with its masked jump-table
operand clean.

Modes 0 and 3 push hidden or disabled transitions over the manager's fixed
150-record pool. Modes 1 and 2 unwind only the newest generation; mode 1 also
restores idle padding and hover state. The stack borrows `cRBorder` handles and
does not allocate or own them.

Android `Border.o` independently exports `cRBorderStack::Perform(int)` with
the same four-mode behavior. Live Windows analysis confirms a void thiscall
receiver and exactly two callers, the BorderManager hide and unhide wrappers.
No exact iOS body is claimed.

The stable matcher identity remains `apply_all_border_visibility_mode`; source
and relocations now use the authored member name.
