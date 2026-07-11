// Windows cRSubTracks owner. The tail layout is recovered from
// load_level_definition_file and shared with frontend level selection users.
#ifndef SUB_TRACKS_H
#define SUB_TRACKS_H

#include "segment_catalog_types.h"
#include "sprite.h"

class SubTracks {
public:
    void load_frontend_level_by_mode_and_index(int mode, int level_index); // @ 0x443650
    void load_level_definition_file(char* path); // @ 0x447480
    void copy_segment_definition_to_level_slot(char* segment_name, SubSegment* segment);
    void load_builtin_segment_definitions(SubSegmentRaw** raw_segments); // @ 0x448060

    int segment_count;                   // +0x000000
    SubSegment segment_slots[100];       // +0x000004
    SubSegment first_segment;            // +0x19d484
    SubSegment last_segment;             // +0x1a16a4
    int random_length;                   // +0x1a58c4
    unsigned char random_enabled;        // +0x1a58c8
    char unknown_1a58c9[0x1a58cc - 0x1a58c9];
    Color4f fringe_color;                // +0x1a58cc
    char level_display_name[0x80];       // +0x1a58dc
    float selected_speed;                // +0x1a595c
    float garbage_frequency;             // +0x1a5960
    float salt_frequency;                // +0x1a5964
    int landscape_script_index;          // +0x1a5968
    int parcel_count;                    // +0x1a596c
    int track_texture_set;               // +0x1a5970
    int parcel_quota;                    // +0x1a5974
};

typedef char SubTracks_must_be_0x1a5978[
    (sizeof(SubTracks) == 0x1a5978) ? 1 : -1];

#endif
