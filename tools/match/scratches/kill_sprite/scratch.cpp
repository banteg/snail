// kill_sprite @ 0x44e200 (thiscall, ret)

int report_errorf(char* format, ...);

class Sprite {
public:
    void kill_sprite();

    char unknown_00[0x04];
    int flags; // +0x04
    int owner; // +0x08
    Sprite* next; // +0x0c
    Sprite* prev; // +0x10
    char unknown_14[0x1c - 0x14];
    int texture_ref; // +0x1c
};

class SpriteManager {
public:
    char unknown_00000[0x83d64];
    Sprite* active_heads[5]; // +0x83d64
    Sprite* free_head; // +0x83d78
};

extern SpriteManager g_sprite_manager; // data_790f30
extern Sprite g_sprite_sentinel; // data_814cb0

void Sprite::kill_sprite()
{
    if ((flags & 1) == 0) {
        report_errorf("Sprite kill error, already dead (%s)", texture_ref + 0xc);
    }
    if (this != &g_sprite_sentinel) {
        flags &= ~1;
        if (this == g_sprite_manager.active_heads[owner]) {
            Sprite* next_sprite = next;
            if (next_sprite != 0) {
                next_sprite->prev = 0;
            }
            g_sprite_manager.active_heads[owner] = next;
            next = g_sprite_manager.free_head;
            g_sprite_manager.free_head = this;
        } else {
            Sprite* previous_sprite = prev;
            if (previous_sprite != 0) {
                previous_sprite->next = next;
            }
            Sprite* next_sprite = next;
            if (next_sprite != 0) {
                next_sprite->prev = prev;
            }
            next = g_sprite_manager.free_head;
            g_sprite_manager.free_head = this;
        }
    }
}
