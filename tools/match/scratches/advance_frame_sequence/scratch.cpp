// advance_frame_sequence @ 0x430470 (thiscall, ret)
// Advances a frame sequence and publishes the current frame payload.

#include "frame_sequence.h"

void FrameSequence::advance_frame_sequence()
{
    int frame_index = current_frame_index;
    FrameSequenceFrame* frame_records = frames;
    current_frame_payload = frame_records[frame_index].payload;

    int flags_value = flags;
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
                        flags = flags_value & ~8;
                    } else if ((flags_value & 2) != 0) {
                        current_frame_index = frame_count - 1;
                    } else {
                        flags = flags_value | 1;
                        current_frame_index = 0;
                    }
                }
            } else {
                int next_frame_index = frame_index + 1;
                int limit = frame_count;
                current_frame_index = next_frame_index;
                if (next_frame_index == limit) {
                    if ((flags_value & 4) != 0) {
                        current_frame_index = limit - 2;
                        flags = flags_value | 8;
                    } else if ((flags_value & 2) != 0) {
                        current_frame_index = 0;
                    } else {
                        flags = flags_value | 1;
                        current_frame_index = 0;
                    }
                }
            }
        }
        current_frame_payload = frame_records[current_frame_index].payload;
    }
}
