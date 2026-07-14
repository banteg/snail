// set_subgame_features @ 0x435df0 (thiscall, ret)

#include "subgame_runtime.h"

int SubgameRuntime::set_subgame_features()
{
    if (selected_level_record_active != 0) {
        SubSolution* record = selected_level_record;
        runtime_flags = record->runtime_build_flags;
        return (int)record;
    }

    int mode = level_mode;
    runtime_flags = SUBGAME_RUNTIME_FLAGS_SWITCH_SEED;
    if ((unsigned int)mode <= 7) {
        runtime_flags = SUBGAME_RUNTIME_FLAGS_ENGINE_DEFAULT;
        switch (mode) {
        case 0:
        case 1:
            runtime_flags = SUBGAME_RUNTIME_FLAGS_POSTAL_CHALLENGE;
            break;
        case 4:
            runtime_flags = SUBGAME_RUNTIME_FLAGS_TIME_TRIAL;
            break;
        case 7:
            runtime_flags = SUBGAME_RUNTIME_FLAGS_TUTORIAL;
            break;
        }
    } else {
        runtime_flags = SUBGAME_RUNTIME_FLAGS_ENGINE_DEFAULT;
    }
    return mode;
}
