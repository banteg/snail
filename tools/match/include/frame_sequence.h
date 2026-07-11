// Shared animated-object frame sequence. Its Object base owns the 0x30-byte
// face records; the tail advances across their TextureRef payloads.
#ifndef FRAME_SEQUENCE_H
#define FRAME_SEQUENCE_H

#include "object_render_types.h"

class FrameSequence : public Object {
public:
    void advance_frame_sequence(); // @ 0x430470

    int sequence_flags; // +0xdc
    int current_frame_index; // +0xe0
    float phase; // +0xe4
    float phase_step; // +0xe8
    TextureRef* current_texture_ref; // +0xec
};

typedef char FrameSequence_must_be_0xf0[
    (sizeof(FrameSequence) == 0xf0) ? 1 : -1];

#endif
