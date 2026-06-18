// update_track_parcel @ 0x4431d0 (thiscall, ret)

#include "row_event_display.h"
#include "track_parcel_runtime.h"

float sine(float radians);
int next_math_random_value();

struct ParcelOwnerView {
    char unknown_000[0x370];
    float facing_angle; // +0x370
    char unknown_374[0x384 - 0x374];
    unsigned char facing_angle_extra_enabled; // +0x384
    char unknown_385[0x3a0 - 0x385];
    float facing_angle_extra; // +0x3a0
};

class ParcelSubgameView {
public:
    char unknown_000000[0x09];
    unsigned char subgame_pause_gate; // +0x09
    char unknown_00000a[0x3be0e4 - 0x0a];
    float parcel_kill_plane_z; // +0x3be0e4
    char unknown_3be0e8[0x3be130 - 0x3be0e8];
    Vector3 delivery_arc_basis; // +0x3be130
    char unknown_3be13c[0x3bf91c - 0x3be13c];
    Vector3 parcel_home_anchor; // +0x3bf91c
    char unknown_3bf928[0x12727d8 - 0x3bf928];
    RowEventDisplayController row_event_display; // +0x12727d8
};

void TrackParcelRuntime::update_track_parcel()
{
    ParcelSubgameView* subgame = (ParcelSubgameView*)game;
    if (subgame->subgame_pause_gate)
        return;

    switch (state) {
    case 0:
        return;

    case 1: {
        if (subgame->parcel_kill_plane_z - 10.0f > world_position.z) {
            sprite->kill_sprite();
            state = 0;
        }

        float advanced_bob = bob_phase_step + bob_phase;
        bob_phase = advanced_bob;
        if (advanced_bob > 1.0f)
            bob_phase = advanced_bob - 1.0f;

        sprite->position = world_position;
        sprite->position.y =
            sine(bob_phase * 6.2831855f) * 0.30000001f + sprite->position.y;

        ParcelOwnerView* owner_view = (ParcelOwnerView*)owner;
        sprite->facing_angle = owner_view->facing_angle;
        if (owner_view->facing_angle_extra_enabled == 1)
            sprite->facing_angle =
                owner_view->facing_angle_extra + sprite->facing_angle;
        return;
    }

    case 2:
    case 3:
        return;

    case 4: {
        float bob_lift = sine(bob_phase * 6.2831855f) * 0.30000001f;
        ParcelSubgameView* current_subgame = (ParcelSubgameView*)game;
        progress = 0.0f;
        progress_step = 0.0416666679f;
        world_position.y = bob_lift + world_position.y;

        Vector3 home_delta;
        home_delta.x = current_subgame->parcel_home_anchor.x - world_position.x;
        home_delta.y = current_subgame->parcel_home_anchor.y - world_position.y;
        home_delta.z = current_subgame->parcel_home_anchor.z - world_position.z;
        float distance = home_delta.vector_magnitude();

        ParcelSubgameView* direction_subgame = (ParcelSubgameView*)game;
        state = 5;
        target_distance = distance;
        travel_dir.x = world_position.x - direction_subgame->parcel_home_anchor.x;
        travel_dir.y = world_position.y - direction_subgame->parcel_home_anchor.y;
        travel_dir.z = world_position.z - direction_subgame->parcel_home_anchor.z;
        travel_dir.normalize_vector();
    }
        /* fall through */

    case 5: {
        float remaining = 1.0f - progress;
        ParcelSubgameView* current_subgame = (ParcelSubgameView*)game;
        Vector3* home_anchor = &current_subgame->parcel_home_anchor;
        float scaled_distance = remaining * target_distance;

        world_position.x = scaled_distance * travel_dir.x + home_anchor->x;
        world_position.y = scaled_distance * travel_dir.y + home_anchor->y;
        world_position.z = scaled_distance * travel_dir.z + home_anchor->z;

        sprite->size_end = remaining * 0.60000002f + 0.40000001f;
        sprite->size_start = sprite->size_end;

        float arc = sine(progress * 3.1415927f) * 0.5f;
        Vector3* basis = &((ParcelSubgameView*)game)->delivery_arc_basis;
        sprite->position.x = arc * basis->x + world_position.x;
        sprite->position.y = arc * basis->y + world_position.y;
        sprite->position.z = arc * basis->z + world_position.z;

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
        ParcelSubgameView* current_subgame = (ParcelSubgameView*)game;
        Vector3 display_delta;
        display_delta.x =
            current_subgame->row_event_display.widget_world_x -
            current_subgame->parcel_home_anchor.x;
        display_delta.y =
            current_subgame->row_event_display.widget_world_y -
            current_subgame->parcel_home_anchor.y;
        display_delta.z =
            current_subgame->row_event_display.widget_world_z -
            current_subgame->parcel_home_anchor.z;

        sprite->size_end = progress * 0.60000002f + 0.40000001f;
        sprite->size_start = sprite->size_end;

        float current_progress = progress;
        Vector3* home_anchor = &((ParcelSubgameView*)game)->parcel_home_anchor;
        sprite->position.x = display_delta.x * current_progress + home_anchor->x;
        sprite->position.y = display_delta.y * current_progress + home_anchor->y;
        sprite->position.z = display_delta.z * current_progress + home_anchor->z;

        float arc = sine(progress * 3.1415927f);
        sprite->position.x = arc * delivery_offset.x + sprite->position.x;
        sprite->position.y = arc * delivery_offset.y + sprite->position.y;
        sprite->position.z = arc * delivery_offset.z + sprite->position.z;

        float advanced_progress = progress_step + progress;
        progress = advanced_progress;
        if (advanced_progress > 1.0f) {
            ((ParcelSubgameView*)game)->row_event_display.register_parcel_delivery();
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
