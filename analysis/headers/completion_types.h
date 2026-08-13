#ifndef COMPLETION_TYPES_H
#define COMPLETION_TYPES_H

typedef unsigned char uint8_t;
typedef int int32_t;

typedef struct FrontendWidget FrontendWidget;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef enum CompletionState {
    COMPLETION_STATE_INACTIVE = 0,
    COMPLETION_STATE_STAGING_PARCELS = 1,
    COMPLETION_STATE_WAITING_FOR_DELIVERIES = 2,
    COMPLETION_STATE_SUMMARY_PENDING = 3,
    COMPLETION_STATE_SUMMARY_ACTIVE = 4,
    COMPLETION_STATE_CONTINUE_ACCEPTED = 5,
    COMPLETION_STATE_EMPTY_DELIVERY_DELAY = 6,
} CompletionState;

/* Exact Windows cRCompletion child embedded at cRSubGame +0x12727d8. */
typedef struct cRCompletion {
    FrontendWidget* title_widget;
    FrontendWidget* delivered_count_widget;
    FrontendWidget* bonus_summary_widget;
    FrontendWidget* bonus_icon_widget;
    FrontendWidget* continue_widget;
    CompletionState state;
    uint8_t fast_forward_enabled;
    uint8_t _pad_19[0x3];
    int32_t parcel_target_count;
    int32_t bonus_enabled;
    int32_t staged_parcel_count;
    int32_t delivered_parcel_count;
    float progress;
    float progress_step;
    Vec3 widget_world;
    float bonus_blink_progress;
    float bonus_blink_step;
    int32_t bonus_score;
    int32_t display_token;
} cRCompletion;

typedef char cRCompletion_must_be_0x50[
    (sizeof(cRCompletion) == 0x50) ? 1 : -1];

#endif
