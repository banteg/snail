// update_jetpack_gauge @ 0x43a390 (thiscall, ret)
// Jetpack countdown/warning controller used by update_subgoldy.

#include "game_root.h"
#include "sub_hover.h"
#include "player.h"
#include "subgame_runtime.h"
#include "track_attachment_types.h"
#include "vector3.h"

extern GameRoot* g_game; // data_4df904

float cosine(float angle);
float sine(float angle);
int debug_report_stub(char* format, ...);

void SubHover::update_jetpack_gauge()
{
    int zero = 0;

    int live_state = state;
    live_state -= zero;
    if (live_state == 0)
        return;
    --live_state;
    if (live_state != 0)
        return;

    {
        float next_progress = progress + progress_step;
        progress = next_progress;

        SubgameRuntime* live_game = game;
        Player* live_player = player;
        if (next_progress > 1.0f
            || (float)(live_game->completion_row_start - 5) < live_player->transform.position.z) {
            goto finish_hover;
        }

        if (next_progress < 0.100000001f) {
            warning_intensity = next_progress * 10.0f;
        } else if (next_progress > 0.94f) {
            warning_intensity = (1.0f - next_progress) * 16.6666679f;
            if (next_progress - progress_step <= 0.94f) {
                g_game->subgame.embedded_player()->presentation.set_snail_jetpack(0);
                uninit_jet_particles();
            }
        } else {
            warning_intensity = 1.0f;
            SubRow* runtime_cell =
                g_game->subgame.get_track_runtime_cell_at_world_z(
                    &g_game->subgame.embedded_player()->transform.position);
            if ((runtime_cell->flags & 0x8000) != 0) {
                progress = 0.94f;
                debug_report_stub("Auto Shutoff Jetpack\n");
            }
        }

        warning_intensity =
            1.0f - (cosine(warning_intensity * 3.1415927f) + 1.0f) * 0.5f;
        wobble_x = sine(progress * 25.132742f) * warning_intensity * 0.25f;
        float wobble_y_sine = sine(progress * 37.699112f);
        int intensity_bits = *(int*)&warning_intensity;
        wobble_alpha = 0.0f;
        *(int*)&warning_intensity_latch = intensity_bits;
        wobble_y = (wobble_y_sine * 0.25f + 1.0f) * warning_intensity;
        spawn_track_speedup(&player->transform.position, progress);
        return;
    }

finish_hover:
    end_jetpack_hover();
    if (progress <= 0.94f)
        g_game->subgame.embedded_player()->presentation.set_snail_jetpack(0);
    state = zero;
    wobble_alpha = (float)zero;
    wobble_y = (float)zero;
    wobble_x = (float)zero;
}
