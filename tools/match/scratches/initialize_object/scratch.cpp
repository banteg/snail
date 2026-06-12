// initialize_object @ 0x42f6f0 (thiscall, ret)

class Object {
public:
    int initialize_object();
};

int Object::initialize_object()
{
    *(int*)((char*)this + 0x10) = 0;
    *(int*)((char*)this + 0x14) = 0;
    *(int*)((char*)this + 0x2c) = 0;
    *(int*)((char*)this + 0x54) = 0;
    *(int*)((char*)this + 0x44) = 0;
    *(int*)((char*)this + 0x40) = 0;
    *(int*)((char*)this + 0x64) = 0;
    return 0;
}
