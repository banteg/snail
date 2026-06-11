// change_snail_skin @ 0x445fd0 (thiscall, ret 0x8)
// Layout from analysis/decompile/{binja,ida}/functions/00445fd0-change_snail_skin.c

class SnailSkinTransition {
public:
    void change_snail_skin(int slot_id, float duration_seconds);

    int selected_slot;   // +0x00
    int unknown_04;      // +0x04
    int unknown_08;      // +0x08
    int unknown_0c;      // +0x0c
    int unknown_10;      // +0x10
    int active;          // +0x14
    float progress;      // +0x18
    float progress_step; // +0x1c
};

void SnailSkinTransition::change_snail_skin(int slot_id, float duration_seconds)
{
    active = 1;
    progress = 0.0f;
    if (duration_seconds == 0.0f) {
        progress_step = 0.0f;
        selected_slot = slot_id;
    } else {
        selected_slot = slot_id;
        progress_step = 1.0f / (duration_seconds * 60.0f);
    }
}
