// Shared cRBod/cRBodPos initializer-family owners.
// More runtime-specific AI fields stay scratch-local.
#ifndef BOD_TYPES_H
#define BOD_TYPES_H

#include "bod_fwd.h"
#include "bod_list.h"
#include "object_fwd.h"
#include "sprite.h"
#include "transform_matrix.h"

class AnimManager;

// Shared lifecycle state for the cRBod/cRBodPos family. The callback table is
// installed on renderable bodies whose AI entry is the native no-op stub.
extern void* g_noop_runtime_callback_table; // data_4972b0
extern void* g_bod_base_vtable;              // data_4974fc
extern void* g_renderable_bod_vtable;        // data_497500
extern int g_bod_base_init_count;            // data_50331c

class cRBod : public BodNode {
public:
    cRBod* initialize_bod_base();         // @ 0x42f5f0
    void noop_runtime_ai();               // folded @ 0x407b50; cRBod::AI()
    bool IsAfterSprites();                // @ 0x42f5c0
    int SetObject(Object* object);        // @ 0x42f5d0
    Object* apply_bod_position(TransformMatrix* matrix); // @ 0x42f680

    Vector3 position;   // +0x10, copied into temporary render matrices
    float render_arg_1c; // +0x1c, forwarded to render_object texture-u offset
    float render_arg_20; // +0x20, forwarded to render_object texture-v offset
    union {
        Object* object;     // +0x24, borrowed render-object slot
        Object* strip_mesh; // cRPath provenance alias for the same render body
    };
    tColour color;      // +0x28
};

typedef char cRBod_must_be_0x38[(sizeof(cRBod) == 0x38) ? 1 : -1];
typedef char BodBase_must_be_0x38[(sizeof(BodBase) == 0x38) ? 1 : -1];

class cRBodPos : public cRBod {
public:
    cRBodPos* initialize_renderable_bod(); // @ 0x42f650
    cRBodPos* initialize_noop_renderable_bod(); // @ 0x408040

    TransformMatrix transform; // +0x38
    // Only valid with BOD_FLAG_SYNC_ANIMATION: cRGame::Render borrows this
    // manager's progress for Object::animation immediately before drawing.
    AnimManager* render_animation_manager; // +0x78
    // LoadAnim reuses raw cRBodPos records as animation keyframes and stores
    // their authored frame number in the final positioned-body lane.
    int frame_number; // +0x7c
};

typedef char cRBodPos_must_be_0x80[(sizeof(cRBodPos) == 0x80) ? 1 : -1];
typedef char RenderableBod_must_be_0x80[
    (sizeof(RenderableBod) == 0x80) ? 1 : -1];

#endif
