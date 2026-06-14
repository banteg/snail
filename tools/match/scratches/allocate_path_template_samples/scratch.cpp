// allocate_path_template_samples @ 0x41b0a0 (thiscall)

void* allocate_tracked_memory(int size, char* name);

struct PathTemplateSample {
    char bytes[0xa8];
};

class PathTemplate {
public:
    void allocate_path_template_samples();

    char unknown_00[0x44];
    unsigned int segment_count; // +0x44
    char unknown_48[0x58 - 0x48];
    PathTemplateSample* primary_samples;   // +0x58
    PathTemplateSample* secondary_samples; // +0x5c
};

void PathTemplate::allocate_path_template_samples()
{
    PathTemplateSample* primary = (PathTemplateSample*)allocate_tracked_memory(
        segment_count * sizeof(PathTemplateSample), "Path Tile Nodes");
    unsigned int count = segment_count;
    primary_samples = primary;
    secondary_samples = (PathTemplateSample*)allocate_tracked_memory(
        count * sizeof(PathTemplateSample), "Path Ball nodes");
}
