// get_path_nodes @ 0x41b0a0 (cRPath::GetNodes, thiscall)
#include "track_attachment.h"

#include "tracked_allocation_stack.h"

void cRPath::GetNodes()
{
    AttachmentSample* primary = (AttachmentSample*)allocate_tracked_memory(
        segment_count * sizeof(AttachmentSample), "Path Tile Nodes");
    unsigned int count = segment_count;
    primary_samples = primary;
    secondary_samples = (AttachmentSample*)allocate_tracked_memory(
        count * sizeof(AttachmentSample), "Path Ball nodes");
}
