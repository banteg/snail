// Level definition loader interface. The full storage layout is still
// scratch-local to load_level_definition_file until more users agree on it.
#ifndef LEVEL_DEFINITION_LOADER_H
#define LEVEL_DEFINITION_LOADER_H

class LevelDefinitionLoader {
public:
    int* load_frontend_level_by_mode_and_index(int mode, int level_index); // @ 0x443650
    int* load_level_definition_file(char* path); // @ 0x447480
};

#endif
