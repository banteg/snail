// advance_frame_sequence @ 0x430470 (thiscall, ret)
// Advances a frame sequence and publishes the current frame payload.

#include "frame_sequence.h"

void FrameSequence::advance_frame_sequence()
{
    int frame_index = current_frame_index;
    ObjectFaceQuad* frame_records = facequads;
    current_texture_ref = frame_records[frame_index].texture_ref;

    int flags_value = sequence_flags;
    if ((flags_value & 0x11) == 0) {
        float next_phase = phase_step + phase;
        phase = next_phase;
        if (next_phase > 1.0f) {
            phase = next_phase - 1.0f;
            if ((flags_value & 8) != 0) {
                int next_frame_index = frame_index - 1;
                current_frame_index = next_frame_index;
                if (next_frame_index == -1) {
                    if ((flags_value & 4) != 0) {
                        current_frame_index = 1;
                        sequence_flags = flags_value & ~8;
                    } else if ((flags_value & 2) != 0) {
                        current_frame_index = facequad_count - 1;
                    } else {
                        sequence_flags = flags_value | 1;
                        current_frame_index = 0;
                    }
                }
            } else {
                int next_frame_index = frame_index + 1;
                int limit = facequad_count;
                current_frame_index = next_frame_index;
                if (next_frame_index == limit) {
                    if ((flags_value & 4) != 0) {
                        current_frame_index = limit - 2;
                        sequence_flags = flags_value | 8;
                    } else if ((flags_value & 2) != 0) {
                        current_frame_index = 0;
                    } else {
                        sequence_flags = flags_value | 1;
                        current_frame_index = 0;
                    }
                }
            }
        }
        current_texture_ref = frame_records[current_frame_index].texture_ref;
    }
}
