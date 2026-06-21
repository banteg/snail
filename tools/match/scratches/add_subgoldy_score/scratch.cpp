// add_subgoldy_score @ 0x4402c0 (thiscall, ret 8)

#include "player.h"
#include "sound_effect_manager.h"

extern char* g_game_base; // data_4df904

void report_errorf(const char* message, ...);

void Player::add_subgoldy_score(int score_kind, int bonus_score)
{
    int points;

    switch (score_kind) {
    case SUBGOLDY_SCORE_GARBAGE:
        points = 10;
        break;
    case SUBGOLDY_SCORE_SLUG:
        points = 500;
        break;
    case SUBGOLDY_SCORE_RING:
    case SUBGOLDY_SCORE_PARCEL_COLLECT:
    case SUBGOLDY_SCORE_PARCEL_DELIVER:
        points = 100;
        break;
    case SUBGOLDY_SCORE_BONUS:
        points = bonus_score;
        break;
    default:
        report_errorf("Unknown Score Type");
        points = 0;
        break;
    }

    score_buckets[score_kind] += points;

    int old_total = total_score;
    int new_total = old_total + points;
    total_score = new_total;

    if (old_total / 50000 != new_total / 50000) {
        int lives = visible_life_stock;
        if (lives < 9) {
            visible_life_stock = lives + 1;
            char* game = g_game_base;
            if (*(int*)(game + 0x74658) == 0) {
                if (*(int*)(game + 0x24) == 0) {
                    g_sound_effect_manager.play_sound_effect(0x2c);
                }
            }
        }
    }
}
