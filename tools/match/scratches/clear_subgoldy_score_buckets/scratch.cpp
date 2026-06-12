// clear_subgoldy_score_buckets @ 0x4403a0 (thiscall, ret)

class Player {
public:
    int clear_subgoldy_score_buckets();

    char unknown_00[0x310];
    int score_buckets[6]; // +0x310
};

int Player::clear_subgoldy_score_buckets()
{
    for (int i = 0; i < 6; ++i) {
        score_buckets[i] = 0;
    }
    return 0;
}
