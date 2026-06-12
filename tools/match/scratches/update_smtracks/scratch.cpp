// update_smtracks @ 0x441f60 (thiscall, ret)

struct TextureSlot {
    char unknown_00[0x0c];
    int replacement_scalar;    // +0x0c
};

struct SourceTexture {
    char unknown_00[0x5c];
    TextureSlot* texture_slot; // +0x5c
};

void __cdecl sample_smtrack_heightmap(SourceTexture* source, float base, float scale, int replacement, char cubic);

class FrameSequence {
public:
    int advance_frame_sequence();
};

class SMTracks {
public:
    void update_smtracks();

    char unknown_00[0x24];
    SourceTexture* source;     // +0x24
    char unknown_28[0x38 - 0x28];
    FrameSequence frame_sequence; // +0x38
    char unknown_39[0x124 - 0x39];
    int replacement_scalar;    // +0x124
};

void SMTracks::update_smtracks()
{
    frame_sequence.advance_frame_sequence();
    source->texture_slot->replacement_scalar = replacement_scalar;
    sample_smtrack_heightmap(source, 0.0f, 5.0f, replacement_scalar, 0);
}
