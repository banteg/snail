// initialize_sprite_manager @ 0x44e160 (thiscall, ret)

#include "sprite.h"

extern "C" void* memset(void* destination, int value, unsigned int count);

void SpriteManager::initialize_sprite_manager()
{
    char* base = (char*)this;

    int zero = 0;
    *base = (char)zero;
    memset(base + 0x83d64, zero, 0x14);
    char* first_sprite = base + 4;
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
