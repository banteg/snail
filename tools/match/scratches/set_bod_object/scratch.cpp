// set_bod_object @ 0x42f5d0 (thiscall, ret 4)

class BodBase {
public:
    int set_bod_object(void* object);

    void* vtable; // +0x00
    int flags;    // +0x04
    char unknown_08[0x1c];
    void* object; // +0x24
};

int BodBase::set_bod_object(void* object_)
{
    object = object_;
    flags |= 2;
    return flags;
}
