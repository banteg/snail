#ifndef SNAIL_PORT_LOCKSTEP_TAPE_H
#define SNAIL_PORT_LOCKSTEP_TAPE_H

// Replays a lockstep tape and writes the port's per-tick state (shell/lockstep_tape.cpp).
int run_tape(const char* tape_path, const char* out_path);

#endif
