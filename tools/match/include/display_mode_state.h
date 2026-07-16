// Shared display-mode/view-sample state used by startup and frame rendering.
#ifndef DISPLAY_MODE_STATE_H
#define DISPLAY_MODE_STATE_H

struct DisplayModeRecord {
    char unknown_00[0x0c];
    unsigned short width;  // +0x0c
    unsigned short height; // +0x0e
};

struct DisplayModeViewSample {
    float x;      // +0x00
    float y;      // +0x04
    float width;  // +0x08
    float height; // +0x0c
};

struct DisplayModeState {
    int queued_view_sample_count; // +0x00
    int probe_count;              // +0x04
    DisplayModeRecord* current_mode; // +0x08
    DisplayModeViewSample view_samples[1]; // +0x0c, variable-capacity tail

    void clear_display_mode_state(); // @ 0x407910
    void reset_display_mode_probe_count(); // @ 0x407920
    char read_next_display_mode_view_sample(
        float* x, float* y, float* width, float* height); // @ 0x407930
    char update_display_mode_view_state(); // @ 0x412940
};

extern DisplayModeState g_display_mode_state; // data_4df9e0

// Process-owned display dimensions sampled before the authored 640x480 view
// is installed during startup.
extern int g_current_display_width;  // data_4df858
extern int g_current_display_height; // data_4b775c

typedef char DisplayModeRecord_must_be_0x10[
    (sizeof(DisplayModeRecord) == 0x10) ? 1 : -1];
typedef char DisplayModeViewSample_must_be_0x10[
    (sizeof(DisplayModeViewSample) == 0x10) ? 1 : -1];

#endif
