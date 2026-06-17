// update_smtracks @ 0x441f60 (thiscall, ret)

#include "frame_sequence.h"

struct TextureSlot {
    char unknown_00[0x0c];
    int replacement_scalar;    // +0x0c
};

struct SourceTexture {
    char unknown_00[0x5c];
    TextureSlot* texture_slot; // +0x5c
};

void __cdecl sample_smtrack_heightmap(SourceTexture* source, float base, float scale, int replacement, char cubic);

class SMTracks {
public:
    void update_smtracks();

    char unknown_00[0x24];
    SourceTexture* source;     // +0x24
    char unknown_28[0x38 - 0x28];
    FrameSequence frame_sequence; // +0x38
};

void SMTracks::update_smtracks()
{
    frame_sequence.advance_frame_sequence();
    source->texture_slot->replacement_scalar = frame_sequence.current_frame_payload;
    sample_smtrack_heightmap(
        source,
        0.0f,
        5.0f,
        frame_sequence.current_frame_payload,
        0);
}
