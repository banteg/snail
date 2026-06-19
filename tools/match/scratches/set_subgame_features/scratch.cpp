// set_subgame_features @ 0x435df0 (thiscall, ret)

#include "subgame_runtime.h"

int SubgameRuntime::set_subgame_features()
{
    if (selected_level_record_active != 0) {
        HighScoreRecord* record = selected_level_record;
        runtime_flags = record->runtime_build_flags;
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
