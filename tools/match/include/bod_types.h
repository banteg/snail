// Shared BodBase/RenderableBod initializer-family views.
// More runtime-specific object geometry and AI fields stay scratch-local.
#ifndef BOD_TYPES_H
#define BOD_TYPES_H

#include "sprite.h"
#include "transform_matrix.h"

struct ObjectGeometry;

class BodBase {
public:
    BodBase* initialize_bod_base();       // @ 0x42f5f0
    bool is_bod_after_sprites();          // @ 0x42f5c0
    int set_bod_object(void* object);     // @ 0x42f5d0
    ObjectGeometry* apply_bod_position(TransformMatrix* matrix); // @ 0x42f680

    void* vtable;       // +0x00
    int flags;          // +0x04
    char unknown_08[0x10 - 0x08];
    int unknown_10;     // +0x10, cleared by initialize_bod_base
    int unknown_14;     // +0x14, cleared by initialize_bod_base
    int unknown_18;     // +0x18, cleared by initialize_bod_base
    int unknown_1c;     // +0x1c, cleared by initialize_bod_base
    int unknown_20;     // +0x20, cleared by initialize_bod_base
    void* object;       // +0x24
    Color4f color;      // +0x28
};

typedef char BodBase_must_be_0x38[(sizeof(BodBase) == 0x38) ? 1 : -1];

class RenderableBod : public BodBase {
public:
    RenderableBod* initialize_renderable_bod(); // @ 0x42f650

    TransformMatrix transform; // +0x38
};

typedef char RenderableBod_must_be_0x78[(sizeof(RenderableBod) == 0x78) ? 1 : -1];

#endif
