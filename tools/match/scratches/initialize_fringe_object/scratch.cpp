// initialize_fringe_object @ 0x408650 (thiscall, ret)

extern void* g_fringe_object_vtable; // off_497344 / data_497344

class BodBase {
public:
    void initialize_bod_base();

    void* vtable; // +0x00
};

class FringeObject : public BodBase {
public:
    FringeObject* initialize_fringe_object();
};

FringeObject* FringeObject::initialize_fringe_object()
{
    initialize_bod_base();
    vtable = &g_fringe_object_vtable;
    return this;
}
