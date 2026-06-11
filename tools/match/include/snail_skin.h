// SnailSkinTransition @ player presentation controller
// Layouts recovered in analysis/decompile/{binja,ida}/functions/00445f*.c
#ifndef SNAIL_SKIN_H
#define SNAIL_SKIN_H

struct PlayerRenderModel {
    int unknown_00[4];
    unsigned int flags;      // +0x10, |= 8 marks material dirty
    int unknown_14;
    int material_index;      // +0x18
};

struct PlayerRenderOwner {
    int unknown_00[9];
    PlayerRenderModel* model; // +0x24
};

class SnailSkinTransition {
public:
    void update_snail_skin_transition();             // @ 0x445f80
    void change_snail_skin(int slot_id, float duration_seconds); // @ 0x445fd0

    int selected_slot;             // +0x00
    int slot_ids[3];               // +0x04 (0=default, 1=damage-red, 2=invincible)
    PlayerRenderOwner* owner_render_state; // +0x10
    int active;                    // +0x14
    float progress;                // +0x18
    float progress_step;           // +0x1c
};

#endif
