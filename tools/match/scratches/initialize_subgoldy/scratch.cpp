// initialize_subgoldy @ 0x43a9c0 (thiscall, ret 0x4)

#include "anim_manager.h"
#include "cameraman_state.h"
#include "click_start.h"
#include "damage_guage.h"
#include "invincible_shell.h"
#include "jetpack_gauge.h"
#include "player.h"
#include "score_stats.h"
#include "snail_skin.h"
#include "spring_float.h"
#include "transform_matrix.h"

class CutsceneAIState {
public:
    int initialize_cutscene_ai();
};

extern char* g_game_base; // data_4df904

int Player::initialize_subgoldy(int player_slot)
{
    char* self = (char*)this;
    int zero = 0;

    this->player_slot = player_slot;
    this->game = (SubgameRuntime*)(g_game_base + 0x74618);
    *(int*)(self + 0x370) = zero;
    *(int*)(self + 0x1e8) = zero;
    *(unsigned char*)(self + 0x2d8) = (unsigned char)zero;
    this->nuke.owner_player = this;
    this->nuke.state = zero;
    *(unsigned char*)(self + 0x14c) = (unsigned char)zero;
    *(int*)(self + 0x8c) = zero;
    *(int*)(self + 0x444) = zero;
    *(int*)(self + 0x338) = zero;
    *(int*)(self + 0x33c) = -1;
    *(unsigned char*)(self + 0x1e4) = (unsigned char)zero;
    *(unsigned char*)(self + 0x42b8) = (unsigned char)zero;
    *(int*)(*(char**)(self + 0x408) + 0x12727ec) = zero;
    *(int*)(self + 0x3c68) = zero;
    *(int*)(self + 0x30d4) = zero;
    *(int*)(self + 0x34b0) = zero;
    *(int*)(self + 0x388c) = zero;
    *(int*)(self + 0x2dc) = zero;
    *(int*)(self + 0x2e0) = zero;

    ((SpringFloat*)(*(char**)(self + 0x29a8) + 0x80))->reset_spring_float();
    *(int*)(self + 0x2980) = 0xc1980000;
    *(int*)(self + 0x1cc) = zero;
    *(int*)(self + 0x42b0) = zero;
    *(int*)(self + 0x42b4) = 0x3c888889;
    *(int*)(self + 0x435c) = zero;
    *(int*)(self + 0x4360) = 0x3c888889;
    ((ScoreStats*)(self + 0x4344))->initialize_score_stats();
    ((InvincibleShellController*)(self + 0x4218))->initialize_invincible_shell();
    *(int*)(self + 0x334) = 0x3d638e38;
    *(int*)(self + 0x330) = 0x3d638e38;
    *(int*)(self + 0x434) = zero;
    *(int*)(self + 0x438) = 0x3c888889;

    if ((*(int*)(*(char**)(self + 0x29a8) + 0x10) & 0x200000) != 0) {
        *(int*)(self + 0x2988) |= 0x800;
        *(char**)(self + 0x29fc) = self + 0x2a88;
        ((AnimManager*)(self + 0x2a88))->initialize_anim_manager();
        *(int*)(self + 0x2a88) = 1;
        *(char**)(self + 0x2ac8) = self + 0x2984;
        *(char**)(self + 0x2acc) = self + 0x2ad0;
        *(int*)(self + 0x2ac4) = zero;
    } else {
        ((AnimManager*)(self + 0x2a88))->initialize_anim_manager();
        *(int*)(self + 0x2a88) = zero;
    }

    if ((*(int*)(*(char**)(self + 0x3b88) + 0x10) & 0x200000) != 0) {
        *(int*)(self + 0x3b68) = (*(int*)(self + 0x3b68) & 0xffffffdf) | 0x800;
        *(int*)(self + 0x3c68) = zero;
        *(char**)(self + 0x3bdc) = self + 0x3c6c;
        ((AnimManager*)(self + 0x3c6c))->initialize_anim_manager();
        *(int*)(self + 0x3c6c) = 1;
        *(char**)(self + 0x3cac) = self + 0x3b64;
        *(char**)(self + 0x3cb0) = self + 0x3cb4;
        *(int*)(self + 0x3ca8) = zero;
    } else {
        ((AnimManager*)(self + 0x3c6c))->initialize_anim_manager();
        *(int*)(self + 0x3c6c) = zero;
    }

    if ((*(int*)(*(char**)(self + 0x2ff4) + 0x10) & 0x200000) != 0) {
        *(int*)(self + 0x2fd4) = (*(int*)(self + 0x2fd4) & 0xffffffdf) | 0x800;
        *(int*)(self + 0x30d4) = zero;
        *(char**)(self + 0x3048) = self + 0x30d8;
        ((AnimManager*)(self + 0x30d8))->initialize_anim_manager();
        *(int*)(self + 0x30d8) = 1;
        *(char**)(self + 0x3118) = self + 0x2fd0;
        *(char**)(self + 0x311c) = self + 0x3120;
        *(int*)(self + 0x3114) = zero;
    } else {
        ((AnimManager*)(self + 0x30d8))->initialize_anim_manager();
        *(int*)(self + 0x30d8) = zero;
    }

    if ((*(int*)(*(char**)(self + 0x33d0) + 0x10) & 0x200000) != 0) {
        *(int*)(self + 0x33b0) = (*(int*)(self + 0x33b0) & 0xffffffdf) | 0x800;
        *(int*)(self + 0x34b0) = zero;
        *(char**)(self + 0x3424) = self + 0x34b4;
        ((AnimManager*)(self + 0x34b4))->initialize_anim_manager();
        *(int*)(self + 0x34b4) = 1;
        *(char**)(self + 0x34f4) = self + 0x33ac;
        *(char**)(self + 0x34f8) = self + 0x34fc;
        *(int*)(self + 0x34f0) = zero;
    } else {
        ((AnimManager*)(self + 0x34b4))->initialize_anim_manager();
        *(int*)(self + 0x34b4) = zero;
    }

    if ((*(int*)(*(char**)(self + 0x37ac) + 0x10) & 0x200000) != 0) {
        *(int*)(self + 0x378c) = (*(int*)(self + 0x378c) & 0xffffffdf) | 0x800;
        *(int*)(self + 0x388c) = zero;
        *(char**)(self + 0x3800) = self + 0x3890;
        ((AnimManager*)(self + 0x3890))->initialize_anim_manager();
        *(int*)(self + 0x3890) = 1;
        *(char**)(self + 0x38d0) = self + 0x3788;
        *(char**)(self + 0x38d4) = self + 0x38d8;
        *(int*)(self + 0x38cc) = zero;
    } else {
        ((AnimManager*)(self + 0x3890))->initialize_anim_manager();
        *(int*)(self + 0x3890) = zero;
    }

    ((SnailSkinTransition*)(self + 0x42bc))->initialize_snail_skin();
    ((CutsceneAIState*)(self + 0x42dc))->initialize_cutscene_ai();
    if (*(unsigned char*)(*(char**)(self + 0x408) + 0xff25d0) == 0)
        *(int*)(self + 0x42e8) = 1;
    this->presentation.owner_player = this;
    set_matrix_identity((TransformMatrix*)(self + 0x29bc));
    set_matrix_identity((TransformMatrix*)(self + 0x2a44));
    set_matrix_identity((TransformMatrix*)(self + 0x2a04));
    *(int*)(self + 0x4338) = zero;
    click_start_controller()->initialize_click_start((ClickStartPlayer*)this);
    ((CameramanState*)(self + 0x200))->initialize_cameraman();
    initialize_subgoldy_ghost(*(int*)(self + 0x380));

    *(int*)(self + 0x1d8) = 0x3d4ede62;
    *(int*)(self + 0x1e0) = 0x3d4ede62;
    position.x = 0.0f;
    position.y = 0.0f;
    position.z = 4.0f;
    *(int*)(self + 0x37c) = zero;
    *(int*)(self + 0x328) = zero;
    *(int*)(self + 0x32c) = 0x3c888889;
    *(int*)(self + 0x1d4) = zero;
    *(int*)(self + 0x1dc) = zero;
    *(int*)(self + 0x3f40) = zero;
    *(int*)(self + 0x3f44) = 0x3bbc5264;
    *(int*)(self + 0x3f48) = zero;
    *(int*)(self + 0x3f4c) = 0x3bde0163;
    *(unsigned char*)(self + 0x84) = (unsigned char)zero;
    cached_camera_target_world = position;
    int* velocity_lanes = (int*)(self + 0x410);
    velocity_lanes[2] = zero;
    velocity_lanes[1] = zero;
    velocity_lanes[0] = zero;

    int active_slot = *(int*)(self + 0x380);
    char* control_source;
    if (active_slot == 1) {
        char* app = g_game_base;
        char* control_check = app + 0x44;
        if (control_check != 0)
            control_source = app + 0x7c;
        else
            control_source = 0;
    } else {
        char* app = g_game_base;
        char* control_check = app + 0xb4;
        if (control_check != 0)
            control_source = app + 0xec;
        else
            control_source = 0;
    }
    this->control_source = (PlayerControlSource*)control_source;
    *(int*)(self + 0x2730) = zero;
    *(unsigned char*)(self + 0x440) = (unsigned char)zero;
    *(int*)(self + 0x2738) = zero;
    ((DamageGuage*)(self + 0x3c4))->initialize_damage_gauge();
    progress_bar.noop_runtime_ai();
    this->follow_active = (unsigned char)zero;

    char* transform = self + 0x614;
    int transform_count = 12;
    do {
        *(int*)(transform + 0x80) = zero;
        set_matrix_identity((TransformMatrix*)transform);
        *(char**)(transform + 0xac) = *(char**)(self + 0x408);
        transform += 0x2e8;
        --transform_count;
    } while (transform_count);

    int player_flags = *(int*)(self + 4);
    int gauge_slot = *(int*)(self + 0x380);
    player_flags |= 0x20;
    *(int*)(self + 4) = player_flags;
    *(int*)(self + 0x2744) = zero;
    *(int*)(self + 0x2748) = 0x3e555556;
    *(int*)(self + 0x274c) = zero;
    int result =
        ((JetpackGaugeController*)(self + 0x2750))->initialize_jetpack_gauge(gauge_slot);
    *(int*)(self + 0x350) = zero;
    *(int*)(self + 0x354) = zero;
    *(int*)(self + 0x358) = zero;
    *(int*)(self + 0x35c) = zero;
    *(int*)(self + 0x360) = zero;
    *(int*)(self + 0x364) = zero;
    *(int*)(self + 0x368) = zero;
    *(int*)(self + 0x36c) = zero;
    *(int*)(self + 0x374) = zero;
    *(int*)(self + 0x378) = zero;
    *(unsigned char*)(self + 0x41d) = (unsigned char)zero;
    *(unsigned char*)(self + 0x41c) = (unsigned char)zero;
    *(int*)(self + 0x404) = zero;
    (*(char**)(self + 0x408))[1] = 1;
    return result;
}
