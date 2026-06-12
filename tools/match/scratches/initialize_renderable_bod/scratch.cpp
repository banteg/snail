// initialize_renderable_bod @ 0x42f650 (thiscall, ret)

extern void* g_renderable_bod_vtable; // off_497500 / data_497500

struct TransformMatrix;
void __fastcall set_matrix_identity(TransformMatrix* transform);

class BodBase {
public:
    void initialize_bod_base();

    void* vtable; // +0x00
    int flags;    // +0x04
};

class RenderableBod : public BodBase {
public:
    RenderableBod* initialize_renderable_bod();

    char unknown_08[0x30];
    TransformMatrix* transform; // +0x38 placeholder for offset typing
};

RenderableBod* RenderableBod::initialize_renderable_bod()
{
    initialize_bod_base();
    vtable = &g_renderable_bod_vtable;
    flags = 0x2000420;
    set_matrix_identity((TransformMatrix*)((char*)this + 0x38));
    return this;
}
