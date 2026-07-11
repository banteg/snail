#ifndef FRAME_RENDERER_TYPES_H
#define FRAME_RENDERER_TYPES_H

/* Narrow IDA import slice for the root frame renderer and its sprite sort workspace. */

typedef struct GameRoot GameRoot;

typedef struct FrameRendererVec3 {
    float x;
    float y;
    float z;
} FrameRendererVec3;

typedef struct SpriteDepthNode {
    struct SpriteDepthNode* next;
    FrameRendererVec3 position;
    float depth_key;
    void* sprite;
} SpriteDepthNode;

#endif
