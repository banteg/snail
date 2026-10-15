#ifndef SNAIL_PORT_PROFILE_H
#define SNAIL_PORT_PROFILE_H

// Gameplay profile, chosen once at startup, before snail_start
// (docs/port/README.md#gameplay-profiles).
// Original plays the PC release as shipped, its bugs included; both oracles
// (20/20 replays, 10/10 lockstep sessions) check it bit for bit.
// Ultimate plays the mobile courses and rules (shell/extras*.cpp) with every
// fix for the original's own bugs (shell/fixes.cpp).
extern bool g_port_ultimate;

#endif
