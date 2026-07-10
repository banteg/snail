// begin_track_attachment_follow_state @ 0x420c40 (thiscall, ret 0xc)
#include "track_attachment.h"

extern char* g_game_base;

AttachmentPathTemplate* FollowState::begin_track_attachment_follow_state(
    TrackRowCell* cell, const Vector3* world_position, Player* owning_player)
{
    active = 1;
    template_record = cell->attachment_template_record;
    source_cell = cell;
    sample_index = 0;
    progress = world_position->z - cell->anchor_position.z;
    float height = world_position->y - 0.49f;
    player = owning_player;
    vertical_offset = height;
    int table_index = 61 * cell->get_track_cell_row_index();
    float* runtime_row_installed_heading_fields =
        (float*)(g_runtime_row_installed_heading_fields + (int)g_game_base);
    AttachmentPathTemplate* record = template_record;
    record->installed_heading_delta = runtime_row_installed_heading_fields[table_index];
    return record;
}
