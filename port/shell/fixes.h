#ifndef SNAIL_PORT_FIXES_H
#define SNAIL_PORT_FIXES_H

// Fixes for the original's own bugs, always on (docs/port/original-bugs.md).
// So far they change only what is drawn, so both oracles still match.

// Active slugs and garbage drawn upright on a cell the track tilts: what the
// original shows on their spawn tick, and what the spawn fix leaves none of
// (--trace).
int fixes_upright_hazard_count();

#endif
