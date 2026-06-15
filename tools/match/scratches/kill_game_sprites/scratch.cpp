// kill_game_sprites @ 0x44e3d0 (thiscall, ret)

class Sprite {
public:
    void kill_sprite();

    void* object_ref; // +0x00
    unsigned int flags; // +0x04
    int owner; // +0x08
    Sprite* next; // +0x0c
};

extern Sprite* g_sprite_active_heads[5]; // data_814c94
extern Sprite* g_sprite_free_head; // data_814ca8

class SpriteManager {
public:
    void kill_game_sprites();
};

void SpriteManager::kill_game_sprites()
{
    Sprite** bucket = g_sprite_active_heads;
    unsigned int game_sprite_flag = 0x800;

    do {
        Sprite* sprite = *bucket;
        if (sprite != 0) {
            do {
                unsigned int flags = sprite->flags;
                Sprite* next = sprite->next;
                if ((flags & game_sprite_flag) != 0) {
                    sprite->kill_sprite();
                }
                sprite = next;
            } while (sprite != 0);
        }
        ++bucket;
    } while ((int)bucket < (int)&g_sprite_free_head);
}
