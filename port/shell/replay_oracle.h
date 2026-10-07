#ifndef SNAIL_PORT_REPLAY_ORACLE_H
#define SNAIL_PORT_REPLAY_ORACLE_H

// The replay oracle for headless runs (shell/replay_oracle.cpp).
bool replay_oracle_configure(const char* spec);  // "A3": ScoreA.dat, row 3
bool replay_oracle_enabled();
void replay_oracle_started();      // after start_game
bool replay_oracle_tick(int tick);  // after each tick; true once the replay is over
int replay_oracle_report();         // prints the summary; 0 when the port matches

#endif
