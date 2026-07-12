// Authored cRSnailSkin, exact 0x20-byte skin/material selection owner.
#ifndef SNAIL_SKIN_H
#define SNAIL_SKIN_H

class Snail;
struct TextureRef;

class SnailSkin {
public:
    void initialize_snail_skin(); // @ 0x445f60, cRSnailSkin::Init
    void update_snail_skin_transition(); // @ 0x445f80, cRSnailSkin::AI
    void change_snail_skin(int slot_id, float duration_seconds); // @ 0x445fd0, Change

    int selected_slot;             // +0x00
    TextureRef* material_overrides[3]; // +0x04 (default, damage-red, invincible)
    Snail* owner_snail;            // +0x10, non-owning parent backlink
    int active;                    // +0x14
    float progress;                // +0x18
    float progress_step;           // +0x1c
};

typedef char SnailSkin_must_be_0x20[(sizeof(SnailSkin) == 0x20) ? 1 : -1];

#endif
