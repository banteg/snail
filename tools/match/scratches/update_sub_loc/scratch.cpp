// update_sub_loc @ 0x439d50 (thiscall, ret)
// Runtime-cell update: wall2 (tile 14) fires at the player through the
// 4% gate once the first authored block passes the player z; tiles 22/29/30
// and the default lane cull or sync the attachment skirt color.

#include "game_root.h"
#include "track_attachment_types.h"
#include "vector3.h"

float random_float_below(float maximum, const char* tag);
float random_signed_float_below(float maximum, const char* tag);

extern GameRoot* g_game; // data_4df904 (this TU caches the base, reloading after calls)

inline Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
    Vector3 result;
    result.x = lhs.x - rhs.x;
    result.y = lhs.y - rhs.y;
    result.z = lhs.z - rhs.z;
    return result;
}

void SubLoc::update_sub_loc()
{
    if ((lane_and_flags & SUBLOC_FLAG_AI_ENABLED) == 0)
        return;
    if (g_game->subgame.subgame_pause_gate)
        return;
    if (tile_id == 14) {
        if ((float)g_game->subgame.first_block_row_count
            >= g_game->subgame.embedded_player()->transform.position.z)
            goto cull_check;
        if (random_float_below(100.0f, "W") < 4.0f) {
            Vector3 spawn = position;
            spawn.y += 8.0f;
            unsigned int merged_run_width =
                (lane_and_flags >> SUBLOC_MERGED_RUN_WIDTH_SHIFT)
                & SUBLOC_MERGED_RUN_WIDTH_VALUE_MASK;
            spawn.x = (float)merged_run_width * 0.5f + spawn.x;
            float jitter = random_signed_float_below(3.0f, "Wall2");
            Vector3 target = g_game->subgame.embedded_player()->transform.position;
            target.z = jitter + 8.0f + target.z;
            Vector3 direction;
            direction = target - spawn;
            if (direction.z >= -4.0f)
                goto cull_check;
            direction.normalize_vector();
            direction.x *= 0.40000001f;
            direction.y *= 0.40000001f;
            direction.z *= 0.40000001f;
            g_game->subgame.sub_lazers.shoot_subgoldy(&spawn, &direction);
        }
cull_check:
        if (position.z < g_game->subgame.embedded_player()->interaction_max_z)
            remove_sub_loc();
        return;
    }

    if (tile_id == 22) {
        if (position.z >= g_game->subgame.embedded_player()->interaction_max_z)
            return;
        goto destroy;
    }

    if (tile_id == 29 || tile_id == 30) {
        if (attachment_template_record->kind == 24) {
            render_arg_20 =
                render_arg_20 - g_game->subgame.subgame_rate * 0.033333335f;
            color.set_color_alpha(0.800000012f);
        }
        tColour scratch;
        tColour* skirt = g_game->subgame.get_track_skirt_color(&scratch);
        g_game->subgame.runtime_rows[get_track_cell_row_index()]
            .attachment_body.color = *skirt;
        if (g_game->subgame.embedded_player()->interaction_max_z
                - ((float)attachment_template_record->row_span_count + 5.0f)
            > position.z)
            remove_sub_loc();
        return;
    }

    if (position.z < g_game->subgame.embedded_player()->interaction_max_z
        && (float)(g_game->subgame.completion_row_start - 5) > position.z) {
destroy:
        remove_sub_loc();
    }
}
