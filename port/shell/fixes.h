#ifndef SNAIL_PORT_FIXES_H
#define SNAIL_PORT_FIXES_H

// Fixes for the original's own bugs, in the Ultimate profile only
// (profile.h, docs/port/original-bugs.md). The Original profile keeps the bugs.

// Active slugs and garbage drawn upright on a cell the track tilts: what the
// original shows on their spawn tick, and what the spawn fix leaves none of
// (--trace).
int fixes_upright_hazard_count();

#endif
