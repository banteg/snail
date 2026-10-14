#ifndef SNAIL_PORT_EXTRAS_H
#define SNAIL_PORT_EXTRAS_H

// Opt-in mobile content (Issue #28), off by default so the original Windows
// game remains the default and both oracles (20/20 replays, 10/10 lockstep
// sessions) match bit for bit.
extern bool g_port_extras;

bool extras_init_archive();
void extras_init_assets();
const char* extras_track_texture_name(int slot);

struct cRSubTracks;
struct PathPair;
void extras_init_paths();
void extras_map_level_paths(cRSubTracks* level_def);
void extras_clear_tramp_rings();
void extras_step_tramp_rings();
const PathPair* extras_get_mobile_path_pair(int extra_index);
int extras_tramp_ring_active_count();

#endif
