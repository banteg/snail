// initialize_active_landscape_entry @ 0x408820 (thiscall, ret)

extern void* g_active_landscape_entry_vtable; // off_497360 / data_497360

class RenderableBod {
public:
    void initialize_renderable_bod();

    void* vtable; // +0x00
};

class ActiveLandscapeEntry : public RenderableBod {
public:
    ActiveLandscapeEntry* initialize_active_landscape_entry();
};

ActiveLandscapeEntry* ActiveLandscapeEntry::initialize_active_landscape_entry()
{
    initialize_renderable_bod();
    vtable = &g_active_landscape_entry_vtable;
    return this;
}
