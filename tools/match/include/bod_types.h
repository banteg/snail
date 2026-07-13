// Shared BodBase/RenderableBod initializer-family views.
// iOS RObject.o names these owners cRBod and cRBodPos.
// More runtime-specific object geometry and AI fields stay scratch-local.
#ifndef BOD_TYPES_H
#define BOD_TYPES_H

#include "bod_list.h"
#include "sprite.h"
#include "transform_matrix.h"

struct ObjectGeometry;
struct Object;

class BodBase : public BodNode {
public:
    BodBase* initialize_bod_base();       // @ 0x42f5f0
    bool is_bod_after_sprites();          // @ 0x42f5c0
    int set_bod_object(void* object);     // @ 0x42f5d0
    ObjectGeometry* apply_bod_position(TransformMatrix* matrix); // @ 0x42f680

    Vector3 position;   // +0x10, copied into temporary render matrices
    float render_arg_1c; // +0x1c, forwarded to render_object texture-u offset
    float render_arg_20; // +0x20, forwarded to render_object texture-v offset
    union {
        Object* object;     // +0x24, borrowed render-object slot
        Object* strip_mesh; // cRPath provenance alias for the same render body
    };
    Color4f color;      // +0x28
};

typedef char BodBase_must_be_0x38[(sizeof(BodBase) == 0x38) ? 1 : -1];

class RenderableBod : public BodBase {
public:
    RenderableBod* initialize_renderable_bod(); // @ 0x42f650
    RenderableBod* initialize_noop_renderable_bod(); // @ 0x408040

    TransformMatrix transform; // +0x38
};

typedef char RenderableBod_must_be_0x78[(sizeof(RenderableBod) == 0x78) ? 1 : -1];

extern BodBase g_font3d_bods[128]; // data_7754e8

#endif
