# Pinned — 49.46%, 45/48 insns, loop-layout residual

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

2026-06-13 pin audit: focused matcher still verifies 49.46%, 45/48 insns.
Keep pinned; the remaining diff is the free-scan loop layout and stack
staging, not the projectile spawn or audio semantics.

2026-06-15 source-shape note: keep the negative y stagger as a named
`stagger_y` local. Writing the expression inline lets VC6 rewrite it into
`fmul +0.01` plus `fsubr origin.y`; the named local preserves target's
`fmul -0.01` then `fadd origin.y` sequence and clears the masked audit.
