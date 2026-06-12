// initialize_garbage_hazard @ 0x408550 (thiscall, ret)

extern void* g_garbage_hazard_vtable; // off_497328 / data_497328

class RenderableBod {
public:
    void initialize_renderable_bod();

    void* vtable; // +0x00
};

class GarbageHazardRuntime : public RenderableBod {
public:
    GarbageHazardRuntime* initialize_garbage_hazard();
};

GarbageHazardRuntime* GarbageHazardRuntime::initialize_garbage_hazard()
{
    initialize_renderable_bod();
    vtable = &g_garbage_hazard_vtable;
    return this;
}
