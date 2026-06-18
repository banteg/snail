// kill_sprite @ 0x44e200 (thiscall)

#include "sprite.h"

int report_errorf(char* format, ...);

void Sprite::kill_sprite()
{
    if ((flags & 1) == 0) {
        report_errorf("Sprite kill error, already dead (%s)", texture_ref->name);
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
