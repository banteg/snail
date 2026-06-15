// allocate_path_template_samples @ 0x41b0a0 (thiscall)
#include "track_attachment.h"

void* allocate_tracked_memory(int size, char* name);

void AttachmentPathTemplate::allocate_path_template_samples()
{
    AttachmentSample* primary = (AttachmentSample*)allocate_tracked_memory(
        segment_count * sizeof(AttachmentSample), "Path Tile Nodes");
    unsigned int count = segment_count;
    primary_samples = primary;
    secondary_samples = (AttachmentSample*)allocate_tracked_memory(
        count * sizeof(AttachmentSample), "Path Ball nodes");
}
