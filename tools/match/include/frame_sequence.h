// Shared animation/frame-sequence view. The current payload at +0xec is used
// by SMTracks as the texture replacement scalar after advancing.
#ifndef FRAME_SEQUENCE_H
#define FRAME_SEQUENCE_H

struct FrameSequenceFrame {
    char unknown_00[0x0c];
    int payload; // +0x0c
    char unknown_10[0x30 - 0x10];
};

typedef char FrameSequenceFrame_must_be_0x30[
    (sizeof(FrameSequenceFrame) == 0x30) ? 1 : -1];

class FrameSequence {
public:
    void advance_frame_sequence(); // @ 0x430470

    char unknown_00[0x54];
    int frame_count; // +0x54
    char unknown_58[0x5c - 0x58];
    FrameSequenceFrame* frames; // +0x5c
    char unknown_60[0xdc - 0x60];
    int flags; // +0xdc
    int current_frame_index; // +0xe0
    float phase; // +0xe4
    float phase_step; // +0xe8
    int current_frame_payload; // +0xec
};

typedef char FrameSequence_must_be_0xf0[
    (sizeof(FrameSequence) == 0xf0) ? 1 : -1];

#endif
