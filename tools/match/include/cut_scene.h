// Authored cRCutScene, exact 0x5c-byte intro/completion/death camera owner.
#ifndef CUT_SCENE_H
#define CUT_SCENE_H

#include "transform_matrix.h"

class Player;
class Snail;

enum CutSceneState {
    CUT_SCENE_STATE_INACTIVE = 0,
    CUT_SCENE_STATE_INTRO_PENDING = 1,
    CUT_SCENE_STATE_INTRO_ACTIVE = 2,
    // States 3 and 4 have no producer or handler in the Windows image.
    CUT_SCENE_STATE_COMPLETION_PENDING = 5,
    CUT_SCENE_STATE_COMPLETION_BLEND = 6,
    CUT_SCENE_STATE_COMPLETION_HOLD = 7,
    CUT_SCENE_STATE_INTRO_RETURN_BLEND = 8,
    CUT_SCENE_STATE_INTRO_FINISH = 9,
    CUT_SCENE_STATE_DEATH_PENDING = 10,
    CUT_SCENE_STATE_DEATH_BLEND = 11,
    CUT_SCENE_STATE_DEATH_HOLD = 12,
};

class CutScene {
public:
    void initialize_cutscene_ai(); // @ 0x446130, cRCutScene::Init
    void update_cutscene(); // @ 0x4466d0, cRCutScene::AI

    Snail* presentation; // +0x00, non-owning parent cRSnail
    Player* player; // +0x04, non-owning Goldy owner
    int camera_mode; // +0x08
    CutSceneState state; // +0x0c
    TransformMatrix live_matrix; // +0x10
    float progress; // +0x50
    float progress_step; // +0x54
    unsigned char force_camera_update; // +0x58
    char unknown_59[0x5c - 0x59];
};

typedef char CutScene_must_be_0x5c[(sizeof(CutScene) == 0x5c) ? 1 : -1];

#endif
