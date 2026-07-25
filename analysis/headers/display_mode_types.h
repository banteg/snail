#ifndef SNAIL_DISPLAY_MODE_TYPES_H
#define SNAIL_DISPLAY_MODE_TYPES_H

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef int int32_t;

/*
 * Minimum display-mode/view-sample owner recovered from the exact helper
 * chain at 0x407910..0x4079d5 and 0x412940..0x4129b8.
 *
 * The first three fields and one 0x10-byte sample are directly addressed.
 * The sample tail's capacity is not recoverable from the surviving code:
 * storage after this 0x1c-byte prefix deliberately remains unclaimed.
 */
typedef struct DisplayModeRecord {
    uint8_t unknown_00[12];
    uint16_t width;
    uint16_t height;
} DisplayModeRecord;

typedef struct DisplayModeViewSample {
    float x;
    float y;
    float width;
    float height;
} DisplayModeViewSample;

typedef struct DisplayModeState {
    int32_t queued_view_sample_count;
    int32_t probe_count;
    DisplayModeRecord* current_mode;
    DisplayModeViewSample view_samples[1];
} DisplayModeState;

extern DisplayModeState g_display_mode_state;

typedef char DisplayModeRecord_must_be_0x10[
    (sizeof(DisplayModeRecord) == 0x10) ? 1 : -1];
typedef char DisplayModeViewSample_must_be_0x10[
    (sizeof(DisplayModeViewSample) == 0x10) ? 1 : -1];
typedef char DisplayModeState_minimum_prefix_must_be_0x1c[
    (sizeof(DisplayModeState) == 0x1c) ? 1 : -1];

#endif
