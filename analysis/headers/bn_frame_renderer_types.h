#ifndef BN_FRAME_RENDERER_TYPES_H
#define BN_FRAME_RENDERER_TYPES_H

/*
 * Narrow Binary Ninja ownership slice for the root frame renderer.
 *
 * Vec3 and Sprite are imported by the existing object/sprite lanes. Keeping
 * them as named dependencies here avoids replacing their complete layouts.
 */

typedef struct GameRoot GameRoot;

typedef struct SpriteDepthNode {
    struct SpriteDepthNode* next;
    struct Vec3 position;
    float depth_key;
    struct Sprite* sprite;
} SpriteDepthNode;

#endif
