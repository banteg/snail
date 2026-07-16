// update_track_parcel @ 0x4431d0 (thiscall, ret)

#include "subgame_runtime.h"
#include "track_parcel_runtime.h"

float sine(float radians);
int next_math_random_value();

void Parcel::update_track_parcel()
{
    SubgameRuntime* subgame = owner_subgame;
    Vector3 delta;
    if (subgame->subgame_pause_gate)
        return;

    switch (state) {
    case PARCEL_STATE_INACTIVE:
        break;

    case PARCEL_STATE_TRACK_ACTIVE: {
        if (subgame->embedded_player()->interaction_max_z - 10.0f > position.z) {
            sprite->kill_sprite();
            state = PARCEL_STATE_INACTIVE;
        }

        float advanced_bob = bob_phase_step + bob_phase;
        bob_phase = advanced_bob;
        if (advanced_bob > 1.0f)
            bob_phase = advanced_bob - 1.0f;

        sprite->position = position;
        sprite->position.y =
            sine(bob_phase * 6.2831855f) * 0.30000001f + sprite->position.y;

        sprite->facing_angle = owner_player->heading_roll;
        if (owner_player->follow_state.active == 1)
            sprite->facing_angle =
                owner_player->follow_state.orientation_b + sprite->facing_angle;
        return;
    }

    case PARCEL_STATE_UNKNOWN_2:
    case PARCEL_STATE_UNKNOWN_3:
        return;

    case PARCEL_STATE_COLLECT_PENDING: {
        float bob_lift = sine(bob_phase * 6.2831855f) * 0.30000001f;
        SubgameRuntime* current_subgame = owner_subgame;
        Vector3* home_anchor = current_subgame->parcel_home_anchor();
        progress = 0.0f;
        progress_step = 0.0416666679f;
        position.y = bob_lift + position.y;

        delta = *home_anchor - position;
        float distance = delta.vector_magnitude();

        Vector3* direction_home_anchor = owner_subgame->parcel_home_anchor();
        state = PARCEL_STATE_COLLECTING;
        target_distance = distance;
        travel_dir = position - *direction_home_anchor;
        travel_dir.normalize_vector();
    }
        /* fall through */

    case PARCEL_STATE_COLLECTING: {
        float remaining = 1.0f - progress;
        Vector3* home_anchor = owner_subgame->parcel_home_anchor();
        position = travel_dir * (remaining * target_distance) + *home_anchor;

        sprite->size_end = remaining * 0.60000002f + 0.40000001f;
        sprite->size_start = sprite->size_end;

        float arc = sine(progress * 3.1415927f) * 0.5f;
        Vector3* basis = owner_subgame->parcel_delivery_arc_basis();
        sprite->position = *basis * arc + position;

        float advanced_progress = progress_step + progress;
        progress = advanced_progress;
        if (advanced_progress > 1.0f) {
            Sprite* dying_sprite = sprite;
            state = PARCEL_STATE_INACTIVE;
            dying_sprite->kill_sprite();
        }
        return;
    }

    case PARCEL_STATE_DELIVERY_PENDING:
        progress = 0.0f;
        progress_step = 0.0166666675f;
        state = PARCEL_STATE_DELIVERING;
        delivery_offset.x =
            ((float)next_math_random_value() - 16384.0f) * 0.000061035156f;
        {
            int random_y = next_math_random_value();
            delivery_offset.z = 0.0f;
            delivery_offset.y =
                ((float)random_y - 16384.0f) * 0.000091552734f + 1.0f;
        }
        /* fall through */

    case PARCEL_STATE_DELIVERING: {
        SubgameRuntime* current_subgame = owner_subgame;
        Vector3* home_anchor = current_subgame->parcel_home_anchor();
        delta = current_subgame->completion.widget_world - *home_anchor;

        float delivery_scale = progress;
        delivery_scale *= 0.60000002f;
        delivery_scale += 0.40000001f;
        sprite->size_end = delivery_scale;
        sprite->size_start = sprite->size_end;

        sprite->position =
            delta * progress + *owner_subgame->parcel_home_anchor();

        sprite->position += delivery_offset * sine(progress * 3.1415927f);

        float advanced_progress = progress_step + progress;
        progress = advanced_progress;
        if (advanced_progress > 1.0f) {
            owner_subgame->completion.register_parcel_delivery();
            Sprite* dying_sprite = sprite;
            state = PARCEL_STATE_INACTIVE;
            dying_sprite->kill_sprite();
        }
        break;
    }

    default:
        return;
    }
}
