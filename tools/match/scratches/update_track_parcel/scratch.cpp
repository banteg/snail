// update_track_parcel @ 0x4431d0 (thiscall, ret)

#include "row_event_display.h"
#include "subgame_runtime.h"
#include "track_parcel_runtime.h"

float sine(float radians);
int next_math_random_value();

void Parcel::update_track_parcel()
{
    SubgameRuntime* subgame = owner_subgame;
    Vector3 home_delta;
    Vector3 display_delta;
    if (subgame->subgame_pause_gate)
        return;

    switch (state) {
    case 0:
        break;

    case 1: {
        if (subgame->embedded_player()->interaction_max_z - 10.0f > position.z) {
            sprite->kill_sprite();
            state = 0;
        }

        float advanced_bob = bob_phase_step + bob_phase;
        bob_phase = advanced_bob;
        if (advanced_bob > 1.0f)
            bob_phase = advanced_bob - 1.0f;

        sprite->position = position;
        sprite->position.y =
            sine(bob_phase * 6.2831855f) * 0.30000001f + sprite->position.y;

        Player* owner_view = owner_player;
        sprite->facing_angle = owner_view->heading_roll;
        if (owner_view->follow_active == 1)
            sprite->facing_angle =
                owner_view->follow_orientation_b + sprite->facing_angle;
        return;
    }

    case 2:
    case 3:
        return;

    case 4: {
        float bob_lift = sine(bob_phase * 6.2831855f) * 0.30000001f;
        SubgameRuntime* current_subgame = owner_subgame;
        Vector3* home_anchor = current_subgame->parcel_home_anchor();
        progress = 0.0f;
        progress_step = 0.0416666679f;
        position.y = bob_lift + position.y;

        home_delta.x = home_anchor->x - position.x;
        home_delta.y = home_anchor->y - position.y;
        home_delta.z = home_anchor->z - position.z;
        float distance = home_delta.vector_magnitude();

        Vector3* direction_home_anchor = owner_subgame->parcel_home_anchor();
        state = 5;
        target_distance = distance;
        Vector3 direction;
        direction.x = position.x - direction_home_anchor->x;
        direction.y = position.y - direction_home_anchor->y;
        direction.z = position.z - direction_home_anchor->z;
        travel_dir = direction;
        travel_dir.normalize_vector();
    }
        /* fall through */

    case 5: {
        float remaining = 1.0f - progress;
        SubgameRuntime* current_subgame = owner_subgame;
        Vector3* home_anchor = current_subgame->parcel_home_anchor();
        float scaled_distance = remaining * target_distance;

        Vector3 next_position;
        next_position.x = scaled_distance * travel_dir.x + home_anchor->x;
        next_position.y = scaled_distance * travel_dir.y + home_anchor->y;
        next_position.z = scaled_distance * travel_dir.z + home_anchor->z;
        position = next_position;

        sprite->size_end = remaining * 0.60000002f + 0.40000001f;
        sprite->size_start = sprite->size_end;

        float arc = sine(progress * 3.1415927f) * 0.5f;
        Vector3* basis = current_subgame->parcel_delivery_arc_basis();
        Vector3 sprite_position;
        sprite_position.x = arc * basis->x + position.x;
        sprite_position.y = arc * basis->y + position.y;
        sprite_position.z = arc * basis->z + position.z;
        sprite->position = sprite_position;

        float advanced_progress = progress_step + progress;
        progress = advanced_progress;
        if (advanced_progress > 1.0f) {
            Sprite* dying_sprite = sprite;
            state = 0;
            dying_sprite->kill_sprite();
        }
        return;
    }

    case 6:
        progress = 0.0f;
        progress_step = 0.0166666675f;
        state = 7;
        delivery_offset.x =
            ((float)next_math_random_value() - 16384.0f) * 0.000061035156f;
        {
            int random_y = next_math_random_value();
            delivery_offset.z = 0.0f;
            delivery_offset.y =
                ((float)random_y - 16384.0f) * 0.000091552734f + 1.0f;
        }
        /* fall through */

    case 7: {
        SubgameRuntime* current_subgame = owner_subgame;
        Vector3* home_anchor = current_subgame->parcel_home_anchor();
        display_delta.x =
            current_subgame->row_event_display.widget_world_x -
            home_anchor->x;
        display_delta.y =
            current_subgame->row_event_display.widget_world_y -
            home_anchor->y;
        display_delta.z =
            current_subgame->row_event_display.widget_world_z -
            home_anchor->z;

        sprite->size_end = progress * 0.60000002f + 0.40000001f;
        sprite->size_start = sprite->size_end;

        float current_progress = progress;
        Vector3 display_position;
        display_position.x = display_delta.x * current_progress + home_anchor->x;
        display_position.y = display_delta.y * current_progress + home_anchor->y;
        display_position.z = display_delta.z * current_progress + home_anchor->z;
        sprite->position = display_position;

        float arc = sine(progress * 3.1415927f);
        Vector3 delivery_position;
        delivery_position.x = arc * delivery_offset.x + sprite->position.x;
        delivery_position.y = arc * delivery_offset.y + sprite->position.y;
        delivery_position.z = arc * delivery_offset.z + sprite->position.z;
        sprite->position = delivery_position;

        float advanced_progress = progress_step + progress;
        progress = advanced_progress;
        if (advanced_progress > 1.0f) {
            owner_subgame->row_event_display.register_parcel_delivery();
            Sprite* dying_sprite = sprite;
            state = 0;
            dying_sprite->kill_sprite();
        }
        break;
    }

    default:
        return;
    }
}
