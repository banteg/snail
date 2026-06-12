// initialize_salt_hazard_runtime @ 0x408630 (thiscall, ret)

extern void* g_salt_hazard_vtable; // off_497340 / data_497340

class RenderableBod {
public:
    void initialize_renderable_bod();

    void* vtable; // +0x00
};

class SaltHazardRuntime : public RenderableBod {
public:
    SaltHazardRuntime* initialize_salt_hazard_runtime();
};

SaltHazardRuntime* SaltHazardRuntime::initialize_salt_hazard_runtime()
{
    initialize_renderable_bod();
    vtable = &g_salt_hazard_vtable;
    return this;
}
