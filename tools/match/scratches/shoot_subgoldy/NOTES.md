# Improved — 85.42%, 48/48 insns, loop-layout residual

Same scan-rotation residual class as spawn_salt_hazard (the target's
single-test loop re-spills the index at the top because it later feeds
the fild stagger; our build rotates with a duplicated test). Semantics
complete:

- free scan over the 20-slot pool (state +0x80, stride 0xb0), silent
  return when exhausted
- spawn position staged with the y stagger: y = origin.y + index * -0.01
  (each later slot fires 1cm lower — likely to avoid z-fighting between
  simultaneous shots)
- routes through the matched spawn_sub_lazer_projectile and plays
  positional sound 15 at the ORIGIN (unstaggered) position

2026-06-13 pin audit: focused matcher verified 49.46%, 45/48 insns. The
remaining diff was the free-scan loop layout and stack staging, not the
projectile spawn or audio semantics.

2026-06-15 source-shape note: keep the negative y stagger as a named
`stagger_y` local. Writing the expression inline lets VC6 rewrite it into
`fmul +0.01` plus `fsubr origin.y`; the named local preserves target's
`fmul -0.01` then `fadd origin.y` sequence and clears the masked audit.

2026-06-16 source-shape note: rewriting the free scan as
`while (slots[index].state != 0)` compiled identically to the current pointer
walk, so keep the pointer form because it makes the native state cursor
relationship explicit.

2026-06-20 source-shape update: a scripted sweep showed the native stack frame
is best modeled as one raw `Vector3` copied into the staged vector passed to
`spawn_sub_lazer_projectile`. That recovers the `sub esp, 0x1c` frame and raised
the focused matcher to 78.43% with 2 masked operands ok and no mismatches. Keep
the y stagger split through the named `stagger_y` local; the inline expression
still flips into the misleading positive-constant `fmul` / `fsubr` form.

2026-06-20 sibling loop/call correction: using the same top-test scan shape as
`spawn_salt_hazard` (`while (1)` with an early empty-slot break) recovers the
native `cmp [state], 0` first test and raises the prefix from 2 to 7. Declaring
`play_sound_effect_at_position` as its matched `__stdcall ret 0x8` surface
removes the caller cleanup. Focused Wibo is now 85.42%, 48/48 instructions, and
3 clean masked operands. Spelling the exhaustion branch as `if (index < 20)
continue; return;` and using an explicit `goto found_slot` were codegen-neutral;
the remaining gap is the rotated exhausted-return block plus native's dead
`ecx` load before the positional sound call.

2026-06-20 post-scan exhaustion pass: spelling the free-slot search as
`while (index < 20 && *state != 0)` followed by `if (index >= 20) return`
places the exhausted return before the spawn body, matching the native block
order and improving focused Wibo to 88.66% with a 16/48 prefix. The retained
residual is one extra post-loop `cmp eax, 0x14` before the spawn body, plus the
same missing dead `mov ecx, ADDR` before the positional sound call. Origin
pointer aliases and a `register` hint were codegen-neutral on this shape.
