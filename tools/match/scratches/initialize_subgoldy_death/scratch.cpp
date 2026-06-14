// initialize_subgoldy_death @ 0x446e30 (thiscall, ret)

class Game {
public:
    char unknown_00[0x40];
    int level_mode; // +0x40
};

class Player {
public:
    void initialize_subgoldy_death();
    int initialize_subgoldy_resurrect(int final_loss);

    char unknown_0000[0x408];
    Game* game; // +0x408
    char unknown_040c[0x4340 - 0x40c];
    int visible_life_stock; // +0x4340
};

void Player::initialize_subgoldy_death()
{
    switch (game->level_mode) {
    case 0:
        if (visible_life_stock <= 0)
            initialize_subgoldy_resurrect(1);
        else
            initialize_subgoldy_resurrect(0);
        break;
    case 1:
    case 4:
        initialize_subgoldy_resurrect(1);
        break;
    case 7:
        initialize_subgoldy_resurrect(0);
        break;
    }
}
