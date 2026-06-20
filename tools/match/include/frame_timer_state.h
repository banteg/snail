// Shared frame timer state used by the window proc and main loop startup.
#ifndef FRAME_TIMER_STATE_H
#define FRAME_TIMER_STATE_H

struct FrameTimerState {
    int primary_timestamp;   // +0x00
    int secondary_timestamp; // +0x04
    int elapsed_ticks;       // +0x08

    void clear_frame_timer_state(); // @ 0x407910
    void reset_frame_timer_state(); // @ 0x407920
};

typedef char FrameTimerState_must_be_0x0c[(sizeof(FrameTimerState) == 0x0c) ? 1 : -1];

#endif
