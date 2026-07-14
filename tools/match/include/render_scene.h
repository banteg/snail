// High-byte scene-selection contract shared by viewports and render queues.
#ifndef RENDER_SCENE_H
#define RENDER_SCENE_H

enum RenderSceneFlag {
    RENDER_SCENE_OVERLAY_0 = 0x01000000,
    RENDER_SCENE_PLAYER_0 = 0x02000000,
    RENDER_SCENE_OVERLAY_1 = 0x04000000,
    RENDER_SCENE_OVERLAY_2 = 0x08000000,
    RENDER_SCENE_PLAYER_1 = 0x10000000,
};

const unsigned int RENDER_SCENE_MASK = 0xff000000u;

#endif
