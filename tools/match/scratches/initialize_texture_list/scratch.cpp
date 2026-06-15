// initialize_texture_list @ 0x44e800 (thiscall, ret 0x4)

class TextureList {
public:
    int initialize_texture_list(int capacity);

    void* head;   // +0x00
    int capacity; // +0x04
};

int TextureList::initialize_texture_list(int capacity_)
{
    head = 0;
    capacity = capacity_;
    return capacity_;
}
