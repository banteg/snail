#ifndef SNAIL_PORT_LOCKSTEP_TAPE_H
#define SNAIL_PORT_LOCKSTEP_TAPE_H

#include <stdio.h>

// Replays a lockstep tape and writes the port's per-tick state (shell/lockstep_tape.cpp).
int run_tape(const char* tape_path, const char* out_path);

// Step by step, for hosts that render: tape_open starts the game as the
// recording did; tape_step runs the next recorded tick (writing its state to
// `states` when given) and the frames rendered after it, and returns how many
// it rendered, or -1 after the last tick.
bool tape_open(const char* tape_path);
int tape_step(FILE* states);

#endif
