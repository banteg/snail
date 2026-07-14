// Authored cRCompletion owner embedded in SubgameRuntime. The same 0x50-byte
// object drives both the parcel-delivery display and the final result screen.
#ifndef COMPLETION_H
#define COMPLETION_H

#include "frontend_widget.h"
#include "vector3.h"

class Completion {
public:
    void flush_row_event_display(); // @ 0x404830, cRCompletion::UnInit
    void initialize_completion_screen(
        int delivered_count,
        unsigned char perfect_delivery); // @ 0x404920, cRCompletion::Init
    void update_row_event_display(); // @ 0x404cf0, cRCompletion::AI
    void register_parcel_delivery(); // @ 0x405040, cRCompletion::RegisterParcel

    FrontendWidget* title_widget; // +0x00, "Delivery Complete!" heading
    FrontendWidget* delivered_count_widget; // +0x04
    FrontendWidget* bonus_summary_widget; // +0x08, blinking bonus text
    FrontendWidget* bonus_icon_widget; // +0x0c, sprite id 122
    FrontendWidget* continue_widget; // +0x10
    union {
        int state;
        int continue_state;
    }; // +0x14
    union {
        unsigned char gate_18;
        unsigned char continue_visible;
    }; // +0x18
    char unknown_19[0x1c - 0x19];
    union {
        int parcel_target_count;
        int delivered_count;
    }; // +0x1c
    union {
        int bonus_enabled;
        int perfect_delivery;
    }; // +0x20
    union {
        int staged_parcel_count;
        int delivered_count_progress;
    }; // +0x24
    union {
        int delivered_parcel_count;
        int delivered_count_display;
    }; // +0x28
    union {
        float progress;
        float delivered_count_progress_limit;
    }; // +0x2c
    union {
        float progress_step;
        float delivered_count_progress_step;
    }; // +0x30
    Vector3 widget_world; // +0x34, authored parcel-delivery destination
    union {
        float bonus_blink_progress;
        float bonus_progress;
    }; // +0x40
    union {
        float bonus_blink_step;
        float bonus_progress_step;
    }; // +0x44
    int bonus_score; // +0x48
    union {
        int display_token;
        int total_score;
    }; // +0x4c
};

typedef char Completion_must_be_0x50[
    (sizeof(Completion) == 0x50) ? 1 : -1];

enum {
    COMPLETION_BONUS_TABLE_CAPACITY = 6,
};

// cRCompletion-owned reference tables and prompt text used by Init.
extern int g_completion_bonus_y_table[COMPLETION_BONUS_TABLE_CAPACITY]; // data_4a1194
extern int g_completion_bonus_x_table[COMPLETION_BONUS_TABLE_CAPACITY]; // data_4a11ac
extern char g_click_to_continue_text[]; // aClickToContinu

#endif
