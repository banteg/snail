// kill_subgoldy @ 0x445840 (thiscall, ret)

#include "vector3.h"

class Player {
public:
    int kill_subgoldy();
    int begin_post_follow_carryover();

    char unknown_00[0x68];
    Vector3 position; // +0x68
};

int Player::kill_subgoldy()
{
    int result = begin_post_follow_carryover();
    position.y = -8.0f;
    return result;
}
