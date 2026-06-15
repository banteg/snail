// initialize_duplicate_vertices @ 0x419f50 (thiscall, ret 0x4)

void* allocate_tracked_memory(int size, char* label);
extern char g_duplicate_vertices_alloc_label[]; // "Duplicate vertices"

class DuplicateVertexBuffer {
public:
    void* initialize_duplicate_vertices(int count);

    int active_count; // +0x00
    void* entries;   // +0x04
};

void* DuplicateVertexBuffer::initialize_duplicate_vertices(int count)
{
    active_count = 0;
    void* result = allocate_tracked_memory(count * 10, g_duplicate_vertices_alloc_label);
    entries = result;
    return result;
}
