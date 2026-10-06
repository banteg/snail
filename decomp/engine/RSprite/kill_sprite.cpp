// kill_sprite @ 0x44e200 (thiscall)

#include "sprite.h"

int report_errorf(char* format, ...);

void cRSprite::Kill()
{
    if ((flags & SPRITE_FLAG_ACTIVE) == 0) {
        report_errorf("Sprite kill error, already dead (%s)", texture_ref->name);
    }
    if (this != &g_sprite_sentinel) {
        flags &= ~SPRITE_FLAG_ACTIVE;
        if (this == g_sprite_manager.active_heads[owner]) {
            cRSprite* next_sprite = next;
            if (next_sprite != 0) {
                next_sprite->prev = 0;
            }
            g_sprite_manager.active_heads[owner] = next;
            next = g_sprite_manager.free_head;
            g_sprite_manager.free_head = this;
        } else {
            cRSprite* previous_sprite = prev;
            if (previous_sprite != 0) {
                previous_sprite->next = next;
            }
            cRSprite* next_sprite = next;
            if (next_sprite != 0) {
                next_sprite->prev = prev;
            }
            next = g_sprite_manager.free_head;
            g_sprite_manager.free_head = this;
        }
    }
}
