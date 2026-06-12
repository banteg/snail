// initialize_active_bod @ 0x4085e0 (thiscall, ret)

extern void* g_active_bod_vtable; // off_497338 / data_497338

class BodBase {
public:
    void initialize_bod_base();

    void* vtable; // +0x00
};

class ActiveBod : public BodBase {
public:
    ActiveBod* initialize_active_bod();
};

ActiveBod* ActiveBod::initialize_active_bod()
{
    initialize_bod_base();
    vtable = &g_active_bod_vtable;
    return this;
}
