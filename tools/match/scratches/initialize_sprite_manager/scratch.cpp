// initialize_sprite_manager @ 0x44e160 (thiscall, ret)

class Sprite {
public:
    void initialize_sprite();

    char unknown_00[0x0c];
    Sprite* next; // +0x0c
    Sprite* prev; // +0x10
    char unknown_14[0xb4 - 0x14];
};

class SpriteManager {
public:
    void initialize_sprite_manager();

    unsigned char paused; // +0x00000
    char unknown_00001[0x04 - 0x01];
    Sprite sprites[3000]; // +0x00004
    Sprite* active_heads[5]; // +0x83d64
    Sprite* free_head; // +0x83d78
};

void SpriteManager::initialize_sprite_manager()
{
    char* base = (char*)this;

    int zero = 0;
    *base = (char)zero;
    *(int*)(base + 0x83d64) = zero;
    *(int*)(base + 0x83d68) = zero;
    char* first_sprite = base + 4;
    *(int*)(base + 0x83d6c) = zero;
    *(int*)(base + 0x83d70) = zero;
    *(int*)(base + 0x83d74) = zero;
    *(int*)(base + 0x83d78) = (int)first_sprite;

    int index = zero;
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
