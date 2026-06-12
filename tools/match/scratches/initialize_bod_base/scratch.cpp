// initialize_bod_base @ 0x42f5f0 (thiscall, ret)

extern void* g_bod_base_vtable; // off_4974fc / data_4974fc
extern int g_bod_base_init_count; // data_50331c

class NoopAiCallback {
public:
    NoopAiCallback();
};

class Color4f {
public:
    Color4f* store_color4f(float r, float g, float b, float a);
};

class BodBase {
public:
    BodBase* initialize_bod_base();

    void* vtable; // +0x00
    int flags;    // +0x04
};

BodBase* BodBase::initialize_bod_base()
{
    NoopAiCallback* callback = (NoopAiCallback*)((char*)this + 0x28);

    callback->NoopAiCallback::NoopAiCallback();
    vtable = &g_bod_base_vtable;
    flags = 0x2000020;
    ((Color4f*)callback)->store_color4f(1.0f, 1.0f, 1.0f, 1.0f);
    ++g_bod_base_init_count;
    *(int*)((char*)this + 0x18) = 0;
    *(int*)((char*)this + 0x14) = 0;
    *(int*)((char*)this + 0x10) = 0;
    *(int*)((char*)this + 0x1c) = 0;
    *(int*)((char*)this + 0x20) = 0;
    return this;
}
