# VC6 stack-slot packing (research tooling)

Diagnostic scripts from the 2026-09-25 intro-screen investigation. They trace
C2's stack packer (`stack.c`, `C2+0x4b617`, hooked at `+0x33cde`) through the
preserving observer (`../trace.py`, which needs `../crimson`).

Observed rule:

- each spilled variable gets a weight equal to its reference count;
- variables are sorted by size ascending, weight descending, then packed
  greedily into the most recent non-interfering slot;
- when the frame exceeds 0x80 bytes, slots are reordered by
  `weight * 1000 / size` using C2's unstable quicksort (`C2+0x61bf0`,
  mirrored by `qs.py`);
- declaration order and names have no effect.

So a single extra reference to a spilled local (e.g. a reload before a final
call) can reorder every stack offset in a large function. See
`../../scratches/initialize_intro_screen/NOTES.md` for the worked example.

- `stacktrace.py <scratch-dir> <source.cpp>` prints traced variables, slots,
  weights and register-allocator priority records.
- `pipe.py <this-dir>` simulates the packing and sort for a hand-entered
  variable list (currently the intro-screen frame).
- `qs.py` reproduces C2's quicksort order.

These are research scripts, not part of the matcher; they carry no matching
credit.
