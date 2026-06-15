// initialize_sprite_manager @ 0x44e160 (thiscall, ret)

class Sprite {
public:
    void initialize_sprite();
};

class SpriteManager {
public:
    void initialize_sprite_manager();
};

void SpriteManager::initialize_sprite_manager()
{
    char* base = (char*)this;

    *base = 0;
    *(int*)(base + 0x83d64) = 0;
    *(int*)(base + 0x83d68) = 0;
    *(int*)(base + 0x83d6c) = 0;
    *(int*)(base + 0x83d70) = 0;
    *(int*)(base + 0x83d74) = 0;
    *(int*)(base + 0x83d78) = (int)(base + 4);

    int index = 0;
    do {
        char* slot = base + index * 0xb4;
        ((Sprite*)(slot + 4))->initialize_sprite();

        if (index == 0) {
            *(int*)(base + 0x14) = 0;
            *(int*)(base + 0x10) = (int)(base + 0xb8);
        } else if (index == 0xbb7) {
            *(int*)(base + 0x83cc0) = (int)(base + 0x83bfc);
            *(int*)(base + 0x83cbc) = 0;
        } else {
            *(int*)(slot + 0x14) = (int)(slot - 0xb0);
            *(int*)(slot + 0x10) = (int)(slot + 0xb8);
        }
        ++index;
    } while (index < 0xbb8);
}
