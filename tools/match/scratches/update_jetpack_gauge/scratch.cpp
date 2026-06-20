// update_jetpack_gauge @ 0x43a390 (thiscall, ret)
// Jetpack countdown/warning controller used by update_subgoldy.

#include "jetpack_gauge.h"
#include "track_attachment_types.h"
#include "vector3.h"

extern char* g_game_base; // data_4df904

class Game {
public:
    TrackAttachmentRuntimeRow* get_track_runtime_cell_at_world_z(Vector3* position);

    char unknown_00[0x58];
    int completion_row_start; // +0x58
};

class PlayerForJetpackGauge {
public:
    char unknown_00[0x70];
    float position_z; // +0x70
};

class UpdateJetpackPresentationView {
public:
    void set_snail_jetpack(int state);
};

float cosine(float angle);
float sine(float angle);
int debug_report_stub(char* format, ...);

class JetpackGaugeSpeedupCaller : public JetpackGaugeController {
public:
    void spawn_track_speedup(int position, int progress_bits);
};

void JetpackGaugeController::update_jetpack_gauge()
{
    int zero = 0;

    switch (state) {
    case 0:
        return;
    case 1:
        break;
    default:
        return;
    }

    {
        float next_progress = progress + progress_step;
        progress = next_progress;

        Game* live_game = (Game*)game;
        PlayerForJetpackGauge* live_player = (PlayerForJetpackGauge*)player;
        if (next_progress > 1.0f
            || (float)(live_game->completion_row_start - 5) < live_player->position_z) {
            goto finish_hover;
        }

        if (next_progress < 0.100000001f) {
            warning_intensity = next_progress * 10.0f;
        } else if (next_progress > 0.94f) {
            warning_intensity = (1.0f - next_progress) * 16.6666679f;
            if (next_progress - progress_step <= 0.94f) {
                ((UpdateJetpackPresentationView*)(g_game_base + 0x432700))
                    ->set_snail_jetpack(0);
                uninit_jet_particles();
            }
        } else {
            warning_intensity = 1.0f;
            TrackAttachmentRuntimeRow* runtime_cell =
                ((Game*)(g_game_base + 0x74618))
                    ->get_track_runtime_cell_at_world_z((Vector3*)(g_game_base + 0x42fde4));
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
        int live_progress_bits = *(int*)&progress;
        int position = (int)player + 0x68;
        wobble_alpha = 0.0f;
        *(int*)&warning_intensity_latch = intensity_bits;
        wobble_y = (wobble_y_sine * 0.25f + 1.0f) * warning_intensity;
        ((JetpackGaugeSpeedupCaller*)this)->spawn_track_speedup(
            position, live_progress_bits);
        return;
    }

finish_hover:
    end_jetpack_hover();
    if (progress <= 0.94f)
        ((UpdateJetpackPresentationView*)(g_game_base + 0x432700))
            ->set_snail_jetpack(0);
    state = zero;
    wobble_alpha = (float)zero;
    wobble_y = (float)zero;
    wobble_x = (float)zero;
}
