// update_tutorial @ 0x448de0 (fastcall, ret)
#include "golb.h"
#include "new_game_menu.h"

class Game {
public:
    void* get_track_grid_cell_at_world_position(Vector3* position);
};

void* TutorialController::update_tutorial()
{
    Game* owner = game;
    return owner->get_track_grid_cell_at_world_position((Vector3*)((char*)owner + 0x3bb7cc));
}
