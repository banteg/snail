// request_object_edges @ 0x430570 (thiscall, ret)

void* allocate_tracked_memory(int size, char* name);

class Object {
public:
    void* request_object_edges(int edge_count);

    char unknown_00[0x70];
    int allocated_edge_count;
    void* edges;
};

void* Object::request_object_edges(int edge_count)
{
    void* result = (void*)allocated_edge_count;
    if (result == 0) {
        allocated_edge_count = edge_count;
        result = allocate_tracked_memory(edge_count * 0x24, "Object Edges");
        edges = result;
    }
    return result;
}
