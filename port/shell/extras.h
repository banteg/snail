#ifndef SNAIL_PORT_EXTRAS_H
#define SNAIL_PORT_EXTRAS_H

// Mobile content (Issue #28) for the Ultimate profile (profile.h).
#include "profile.h"

const char* extras_save_path(const char* name);
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
int extras_swaying_ring_count();

struct ArchiveIndex;
ArchiveIndex* extras_get_archive_index();
void extras_init_pro();
bool extras_is_pro_mode();
void extras_set_pro_mode(bool active);

#endif
