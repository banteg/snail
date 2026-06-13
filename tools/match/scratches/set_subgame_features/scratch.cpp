// set_subgame_features @ 0x435df0 (thiscall, ret)

struct SelectedLevelRecord {
    char unknown_00[0x38];
    unsigned int runtime_flags; // +0x38
};

class Game {
public:
    int set_subgame_features();

    char unknown_00[0x40];
    int level_mode;            // +0x40
    int level_mode_arg;        // +0x44
    int unknown_48;
    unsigned int runtime_flags; // +0x4c
    char unknown_50[0xff25d0 - 0x50];
    unsigned char selected_level_record_active; // +0xff25d0
    char unknown_ff25d1[0xff25d4 - 0xff25d1];
    SelectedLevelRecord* selected_level_record; // +0xff25d4
};

int Game::set_subgame_features()
{
    if (selected_level_record_active != 0) {
        SelectedLevelRecord* record = selected_level_record;
        runtime_flags = record->runtime_flags;
        return (int)record;
    }

    int mode = level_mode;
    runtime_flags = 0x484;
    if ((unsigned int)mode <= 7) {
        runtime_flags = 0x600484;
        switch (mode) {
        case 0:
        case 1:
            runtime_flags = 0xf5cfff;
            break;
        case 4:
            runtime_flags = 0x75cfff;
            break;
        case 7:
            runtime_flags = 0xe4cfff;
            break;
        }
    } else {
        runtime_flags = 0x600484;
    }
    return mode;
}
