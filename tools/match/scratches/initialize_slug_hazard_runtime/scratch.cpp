// initialize_slug_hazard_runtime @ 0x408530 (thiscall, ret)

extern void* g_slug_hazard_vtable; // off_497324 / data_497324

class RenderableBod {
public:
    void initialize_renderable_bod();

    void* vtable; // +0x00
};

class SlugHazardRuntime : public RenderableBod {
public:
    SlugHazardRuntime* initialize_slug_hazard_runtime();
};

SlugHazardRuntime* SlugHazardRuntime::initialize_slug_hazard_runtime()
{
    initialize_renderable_bod();
    vtable = &g_slug_hazard_vtable;
    return this;
}
