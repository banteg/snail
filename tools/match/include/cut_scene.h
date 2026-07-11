// Authored cRCutScene, exact 0x5c-byte intro/completion/death camera owner.
#ifndef CUT_SCENE_H
#define CUT_SCENE_H

#include "transform_matrix.h"

class Player;
class PlayerPresentationController;

class CutScene {
public:
    void initialize_cutscene_ai(); // @ 0x446130, cRCutScene::Init
    void update_cutscene(); // @ 0x4466d0, cRCutScene::AI

    PlayerPresentationController* presentation; // +0x00, non-owning parent
    Player* player; // +0x04, non-owning Goldy owner
    int camera_mode; // +0x08
    int state; // +0x0c
    TransformMatrix live_matrix; // +0x10
    float progress; // +0x50
    float progress_step; // +0x54
    unsigned char force_camera_update; // +0x58
    char unknown_59[0x5c - 0x59];
};

typedef char CutScene_must_be_0x5c[(sizeof(CutScene) == 0x5c) ? 1 : -1];

#endif
