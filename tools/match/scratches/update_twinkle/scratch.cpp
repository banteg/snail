// update_twinkle @ 0x404080 (thiscall, void)

#include "frontend_widget.h"

int next_math_random_value();

void Twinkle::update_twinkle()
{
    float wrapped_angle = angle + angle_step;
    angle = wrapped_angle;
    if (wrapped_angle > 6.2831855f) {
        angle = wrapped_angle - 6.2831855f;
    } else if (wrapped_angle < 0.0f) {
        angle = wrapped_angle + 6.2831855f;
    }

    switch (state) {
    case 1: {
        int flags = owner_widget->widget_flags;
        if ((flags & 2) != 0
            && (flags & FRONTEND_WIDGET_FLAG_DISABLED) == 0) {
            float next_delay = delay_progress;
            next_delay += delay_step;
            delay_progress = next_delay;
            if (next_delay > 1.0f) {
                state = 2;
                alpha = 0.0f;
                target_alpha = 0.89999998f;
                angle =
                    ((float)next_math_random_value() - 16384.0f) *
                    0.0001917476f;

                int spin_direction;
                if (((float)next_math_random_value() - 16384.0f) *
                        0.000061035156f <
                    0.0f) {
                    spin_direction = -1;
                } else {
                    spin_direction =
                        (((float)next_math_random_value() - 16384.0f) *
                             0.000061035156f ==
                         0.0f)
                            ? 0
                            : 1;
                }

                int step_random = next_math_random_value();
                delay_progress = 0.0f;
                FrontendWidget* active_owner = owner_widget;
                delay_step = 1.0f;
                angle_step =
                    1.0f /
                    ((((float)step_random - 16384.0f) * 0.000061035156f +
                         5.0f) *
                        60.0f) *
                    spin_direction * 6.2831855f;

                x = ((float)next_math_random_value() *
                         (active_owner->layout_width * 0.80000001f) *
                         0.000030517578f +
                     active_owner->layout_x) +
                    active_owner->layout_width * 0.100000001f;

                active_owner = owner_widget;
                y = ((float)next_math_random_value() *
                         (active_owner->layout_height * 0.80000001f) *
                         0.000030517578f +
                     active_owner->layout_height * 0.100000001f) +
                    active_owner->layout_y;

                size =
                    ((float)next_math_random_value() - 16384.0f) *
                        0.00073242188f +
                    25.0f;
            }
        }
        break;
    }

    case 2: {
        float next_alpha = (target_alpha - alpha) * 0.100000001f + alpha;
        alpha = next_alpha;
        float remaining = target_alpha - next_alpha;
        if (remaining < 0.0f) {
            remaining = -remaining;
        }
        if (remaining < 0.0099999998f) {
            target_alpha = 0.0f;
            state = 4;
        }
        draw_twinkle();
        break;
    }

    case 4: {
        alpha = (target_alpha - alpha) * 0.100000001f + alpha;
        draw_twinkle();
        float remaining = target_alpha - alpha;
        if (remaining < 0.0f) {
            remaining = -remaining;
        }
        if (remaining < 0.0099999998f) {
            state = 1;
            alpha = 0.0f;
            delay_progress = 0.0f;
            delay_step =
                1.0f /
                (((float)next_math_random_value() * 0.000030517578f +
                     0.0099999998f) *
                    60.0f);
        }
        break;
    }
    }
}
