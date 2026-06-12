// update_tutorial @ 0x448de0 (fastcall, ret)
#include "golb.h"

class Game {
public:
    void* get_track_grid_cell_at_world_position(Vector3* position);
};

class TutorialController {
public:
    void* update_tutorial();

    char unknown_00[0x0c];
    Game* game;
};

void* TutorialController::update_tutorial()
{
    Game* owner = game;
    return owner->get_track_grid_cell_at_world_position((Vector3*)((char*)owner + 0x3bb7cc));
}
