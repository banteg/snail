#ifndef DUPLICATE_VERTICES_H
#define DUPLICATE_VERTICES_H

struct DuplicateVertexRecord {
    unsigned short source_vertex; // +0x00
    unsigned short compare_vertex; // +0x02
    char unknown_04[0x08 - 0x04];
    unsigned short live_flag; // +0x08
};

class DuplicateVertexBuffer {
public:
    void* initialize_duplicate_vertices(int count); // @ 0x419f50
    int clean_duplicate_vertices(int unused); // @ 0x419f80

    int active_count; // +0x00
    DuplicateVertexRecord* records; // +0x04
};

#endif
