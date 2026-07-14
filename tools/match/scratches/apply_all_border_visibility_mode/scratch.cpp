// apply_all_border_visibility_mode @ 0x404360 (thiscall, ret 4)

#include "border_manager.h"

void BorderStack::apply_all_border_visibility_mode(int mode)
{
    switch (mode) {
    case 0: {
        for (int i = 0; i < BORDER_RECORD_COUNT; ++i) {
            int flags = owner->borders[i].flags;
            if (flags != 0
                && (flags
                        & (0x10000000 | FRONTEND_WIDGET_FLAG_TEARDOWN_ACTIVE
                            | FRONTEND_WIDGET_FLAG_HIDDEN))
                    == 0) {
                owner->borders[i].flags = flags | FRONTEND_WIDGET_FLAG_HIDDEN;
                entries[entry_count].widget =
                    (FrontendWidget*)&owner->borders[i];
                entries[entry_count].generation = generation;
                ++entry_count;
            }
        }
        ++generation;
        return;
    }

    case 1:
        if (generation <= 0) {
            return;
        }
        --generation;
        if (entry_count <= 0) {
            return;
        }
        --entry_count;
        while (entry_count >= 0) {
            if (entries[entry_count].generation != generation) {
                break;
            }
            entries[entry_count].widget->widget_flags &= ~FRONTEND_WIDGET_FLAG_HIDDEN;
            entries[entry_count].widget->target_padding =
                entries[entry_count].widget->idle_padding;
            entries[entry_count].widget->current_padding =
                entries[entry_count].widget->idle_padding;
            entries[entry_count].widget->hover_blend_target = 0.0f;
            entries[entry_count].widget->hover_blend_current = 0.0f;
            --entry_count;
        }
        ++entry_count;
        return;

    case 3: {
        for (int i = 0; i < BORDER_RECORD_COUNT; ++i) {
            int flags = owner->borders[i].flags;
            if (flags != 0
                && (flags
                        & (0x10000000 | FRONTEND_WIDGET_FLAG_TEARDOWN_ACTIVE
                            | FRONTEND_WIDGET_FLAG_HIDDEN
                            | FRONTEND_WIDGET_FLAG_DISABLED))
                    == 0) {
                owner->borders[i].flags = flags | FRONTEND_WIDGET_FLAG_DISABLED;
                entries[entry_count].widget =
                    (FrontendWidget*)&owner->borders[i];
                entries[entry_count].generation = generation;
                ++entry_count;
            }
        }
        ++generation;
        return;
    }

    case 2:
        if (generation <= 0) {
            return;
        }
        --generation;
        if (entry_count <= 0) {
            return;
        }
        --entry_count;
        while (entry_count >= 0) {
            if (entries[entry_count].generation != generation) {
                break;
            }
            entries[entry_count].widget->widget_flags &= ~FRONTEND_WIDGET_FLAG_DISABLED;
            --entry_count;
        }
        ++entry_count;
        return;
    }
}
