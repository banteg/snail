#ifndef BN_OVERLAY_TYPES_H
#define BN_OVERLAY_TYPES_H

/*
 * Narrow Binary Ninja overlay/camera ownership slice.
 *
 * RenderableBod and TransformMatrix are intentionally referenced from the
 * existing presentation type lane instead of being redeclared here. Run
 * sync_path_template_types.py before this sync on a fresh database.
 */

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

typedef union RenderCameraTail {
    float overlay_rotation_angle;
    uint32_t render_mask;
} RenderCameraTail;

typedef struct RenderCamera {
    struct RenderableBod bod;
    uint8_t unknown_78[0x80 - 0x78];
    struct TransformMatrix view_matrix;
    float fov_degrees;
    RenderCameraTail tail;
} RenderCamera;

typedef struct Overlay {
    struct RenderableBod bod;
    uint8_t unknown_78[0x80 - 0x78];
    RenderCamera camera;
    float rotation_step;
} Overlay;

typedef struct SubgameOwnerLink {
    struct SubgameRuntime* game;
} SubgameOwnerLink;

#endif
