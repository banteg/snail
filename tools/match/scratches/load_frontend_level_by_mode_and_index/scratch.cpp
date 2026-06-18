// load_frontend_level_by_mode_and_index @ 0x443650 (thiscall, ret 0x8)

int sprintf(char* buffer, char* format, ...);

class FrontendLevelLoader {
public:
    void* load_frontend_level_by_mode_and_index(int mode, int level_index);
    void* load_level_definition_file(char* path); // @ 0x447480
};

void* FrontendLevelLoader::load_frontend_level_by_mode_and_index(
    int mode,
    int level_index)
{
    char path[128];

    switch (mode) {
    case 0:
        if (level_index <= 50) {
            sprintf(path, "Arcade%03i.txt", level_index);
        } else {
            if (level_index == 51)
                sprintf(path, "ArcadeExtra000.txt");
        }
        break;

    case 4:
        if (level_index <= 50)
            sprintf(path, "Arcade%03i.txt", level_index);
        else
            sprintf(path, "TimeTrialExtra%03i.txt", level_index - 50);
        break;

    case 1:
        sprintf(path, "Challenge000.txt");
        break;

    case 7:
        sprintf(path, "Tutorial.txt");
        break;

    case 2:
    case 3:
        sprintf(path, "Arcade000.txt");
        break;

    default:
        break;
    }

    return load_level_definition_file(path);
}
