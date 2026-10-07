// The replay oracle (headless --replay): plays a high-score replay recorded by
// the original Windows game and compares the port's simulation against it,
// tick by tick.
//
// A replay record stores, per tick, the snail's lateral position and input
// flags (which playback feeds back in) and the z the original's physics
// produced (which playback does not touch). update_subgoldy re-simulates z
// from the fed lateral path, so the recorded z is the original's own answer
// for each tick, and any difference is a divergence in the port's simulation.
//
// The replay starts the way the High Scores screen's Replay button would: the
// shipped game hides those buttons (HideInit, never revealed), but their
// handler is in update_high_score_screen (0x4170b0). Once the screen shows the
// chosen bank, the oracle performs that handler's effects for the chosen row.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "game_root.h"
#include "replay_oracle.h"
#include "rmath_random.h"
#include "runtime_config.h"
#include "sub_solution.h"

namespace {

const float kZTolerance = 1.0f / 32.0f;  // the recording's own quantum

struct Oracle {
    bool enabled = false;
    int bank = 0;  // 0 postal (ScoreA.dat), 1 challenge (ScoreB.dat)
    int rank = 0;
    bool launched = false;
    bool finished = false;
    SubSolution* record = nullptr;
    float* recorded_z = nullptr;  // the original's z after each sample
    int compared = 0;
    int first_divergence = -1;
    float max_error = 0;
    int max_error_sample = -1;
    int last_cursor = -1;
};

Oracle g_oracle;

void launch()
{
    // update_high_score_screen's Replay-button handler, for row `rank`.
    cRSubHighScore& scores = g_game->subgame.sub_high_score;
    SubSolution* record = (SubSolution*)((char*)scores.active_record_bank + g_oracle.rank * SUB_SOLUTION_STRIDE);
    g_game->players[0].frontend_state = 10;
    g_game->players[0].redispatch_requested = 1;
    g_game->high_score.UnInit();
    g_game->subgame.replay_launch_record = record;
    g_game->subgame.replay_launch_active = 1;
    g_game->subgame.replay_launch_from_frontend = 1;
    g_game->subgame.replay_launch_return_state = 18;
    g_game->subgame.level_mode = record->replay_mode_id;

    g_oracle.record = record;
    g_oracle.launched = true;
    // The recording accumulated quantized deltas (update_subgoldy).
    int count = record->replay_sample_count;
    g_oracle.recorded_z = (float*)malloc((count > 0 ? count : 1) * sizeof(float));
    float accumulated = 0;
    for (int i = 0; i < count; ++i) {
        float delta = MathType16to32(record->run_records[i].delta_z, 32.0f);
        accumulated = i == 0 ? delta : accumulated + delta;
        g_oracle.recorded_z[i] = accumulated;
    }
    fprintf(stderr, "oracle: replaying %s #%d: score %d, level %d, mode %d, %d samples\n",
        g_oracle.bank ? "challenge" : "postal", g_oracle.rank + 1, record->score, record->replay_level_index,
        record->replay_mode_id, count);
}

}  // namespace

bool replay_oracle_configure(const char* spec)
{
    // "A3" or "B10": the bank file letter and the 1-based row.
    if ((spec[0] != 'A' && spec[0] != 'B') || atoi(spec + 1) < 1 || atoi(spec + 1) > 10)
        return false;
    g_oracle.enabled = true;
    g_oracle.bank = spec[0] == 'A' ? 0 : 1;
    g_oracle.rank = atoi(spec + 1) - 1;
    return true;
}

bool replay_oracle_enabled() { return g_oracle.enabled; }

void replay_oracle_started()
{
    // The High Scores screen opens on the configured bank.
    g_runtime_config.high_score_selected_bank = g_oracle.bank;
}

bool replay_oracle_tick(int tick)
{
    if (!g_oracle.launched) {
        if (g_game->players[0].frontend_state == 19 && g_game->fade.state == 0)
            launch();
        return false;
    }
    cRSubGame& subgame = g_game->subgame;
    int cursor = subgame.replay_update_cursor;
    if (!subgame.selected_level_record_active || cursor == g_oracle.last_cursor)
        return g_oracle.last_cursor >= 0 && g_game->players[0].frontend_state != 11;
    // After a tick the cursor names the sample that tick's z became in the
    // recording (playback reads the lateral sample one behind it).
    int sample = cursor;
    g_oracle.last_cursor = cursor;
    if (sample < 0 || sample >= g_oracle.record->replay_sample_count)
        return sample >= g_oracle.record->replay_sample_count;
    float error = fabsf(subgame.player.transform.position.z - g_oracle.recorded_z[sample]);
    ++g_oracle.compared;
    if (error > g_oracle.max_error) {
        g_oracle.max_error = error;
        g_oracle.max_error_sample = sample;
    }
    if (error > kZTolerance && g_oracle.first_divergence < 0) {
        g_oracle.first_divergence = sample;
        fprintf(stderr, "oracle: first divergence at sample %d (tick %d): port z %.4f, original z %.4f\n", sample,
            tick, subgame.player.transform.position.z, g_oracle.recorded_z[sample]);
    }
    return false;
}

int replay_oracle_report()
{
    if (!g_oracle.launched) {
        fprintf(stderr, "oracle: the replay never started\n");
        return 1;
    }
    int count = g_oracle.record->replay_sample_count;
    // Playback stops at the run's end marker (flag 8); the recording goes on
    // past it, so the samples after it are never played.
    int end = count;
    for (int i = 0; i < count; ++i)
        if (g_oracle.record->run_records[i].flags & 8) {
            end = i + 1;
            break;
        }
    fprintf(stderr,
        "oracle: compared %d of %d samples up to the run's end (%d recorded); max |dz| %.4f at sample %d; %s\n",
        g_oracle.compared, end, count, g_oracle.max_error, g_oracle.max_error_sample,
        g_oracle.first_divergence < 0 ? "matches the original" : "diverges");
    return g_oracle.first_divergence < 0 && g_oracle.compared == end ? 0 : 3;
}
