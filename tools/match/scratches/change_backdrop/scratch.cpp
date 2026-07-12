// change_backdrop @ 0x410d50 (thiscall, ret 0x8)
// Stages one parsed landscape script record for the backdrop renderer.

#include "backdrop.h"

void Backdrop::change_backdrop(LandscapeScriptRecord* record, char flip)
{
    int render_enabled = 0;
    unsigned char split_pair = record->split_backdrop_texture_pair;

    if (split_pair != render_enabled) {
        if (record->backdrop_texture_id != render_enabled) {
            render_enabled = 1;
            pending_split_backdrop_pair = (unsigned char)render_enabled;
            backdrop_change_queued = (unsigned char)render_enabled;
            pending_primary_texture_id = record->backdrop_texture_id;
            pending_secondary_texture_id = record->backdrop_texture_id + 1;
            pending_distort = record->distort;
            pending_flip = flip;
        }
    } else {
        if (record->backdrop_texture_id != render_enabled) {
            pending_split_backdrop_pair = (unsigned char)render_enabled;
            render_enabled = 1;
            backdrop_change_queued = (unsigned char)render_enabled;
            pending_primary_texture_id = record->backdrop_texture_id;
            pending_distort = record->distort;
            pending_flip = flip;
        }
    }

    backdrop_render_enabled = render_enabled;
}
