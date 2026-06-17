#ifndef OBJECT_RENDER_TYPES_H
#define OBJECT_RENDER_TYPES_H

struct TextureRef;
struct TransformMatrix;
struct RenderObjectDevice;
struct ObjectVertexBufferVtbl;

struct ObjectVertexBuffer {
    ObjectVertexBufferVtbl* vtbl;
};

struct ObjectRenderBuffers {
    char unknown_00[0x08];
    ObjectVertexBuffer* vertex_buffer; // +0x08
};

struct ObjectRenderVertex {
    float x;
    float y;
    float z;
    unsigned int diffuse;
    float u;
    float v;
};

struct ObjectGroupedVertex {
    float x;              // +0x00
    float y;              // +0x04
    float z;              // +0x08
    unsigned int diffuse; // +0x0c
    float u;              // +0x10
    float v;              // +0x14, stored as 1.0 - source v
    int source_vertex;    // +0x18
};

struct ObjectUv {
    float u;
    float v;
};

struct ObjectFaceQuad {
    unsigned char flags; // +0x00; 0x80 marks three-index form, 0x10 starts a texture group
    char unknown_01;
    unsigned short vertex_0; // +0x02
    unsigned short vertex_1; // +0x04
    unsigned short vertex_2; // +0x06
    unsigned short vertex_3; // +0x08
    char unknown_0a[0x0c - 0x0a];
    TextureRef* texture_ref; // +0x0c
    ObjectUv uv[4]; // +0x10
};

typedef char ObjectFaceQuad_must_be_0x30[
    (sizeof(ObjectFaceQuad) == 0x30) ? 1 : -1];

struct ObjectIndexBufferResource;
struct Object;

struct ObjectIndexBufferResourceVtbl {
    char unknown_00[0x2c];
    int (__stdcall* Lock)(ObjectIndexBufferResource* self, int offset, int size,
        void** data, int flags);
    int (__stdcall* Unlock)(ObjectIndexBufferResource* self);
};

struct ObjectIndexBufferResource {
    ObjectIndexBufferResourceVtbl* vtbl;
};

struct ObjectIndexBuffer {
    ObjectIndexBufferResource* buffer; // +0x00
};

struct RenderObjectDeviceVtbl {
    char unknown_000[0x94];
    int (__stdcall* SetTransform)(RenderObjectDevice* self, int state, TransformMatrix* matrix);
    char unknown_098[0xc8 - 0x98];
    int (__stdcall* SetRenderState)(RenderObjectDevice* self, int state, int value);
    char unknown_0cc[0xfc - 0xcc];
    int (__stdcall* SetTextureStageState)(RenderObjectDevice* self, int stage, int type, int value);
    char unknown_100[0x11c - 0x100];
    int (__stdcall* DrawIndexedPrimitive)(RenderObjectDevice* self, int primitive_type,
        int min_vertex_index, int vertex_count, int start_index, int primitive_count);
    char unknown_120[0x130 - 0x120];
    int (__stdcall* SetVertexShader)(RenderObjectDevice* self, int shader);
    char unknown_134[0x14c - 0x134];
    int (__stdcall* SetStreamSource)(RenderObjectDevice* self, int stream,
        ObjectVertexBuffer* vertex_buffer, int stride);
    char unknown_150[0x154 - 0x150];
    int (__stdcall* SetIndices)(RenderObjectDevice* self,
        ObjectIndexBufferResource* index_buffer, int base_vertex_index);
};

struct RenderObjectDevice {
    RenderObjectDeviceVtbl* vtbl;
};

struct Object {
    int initialize_object(); // @ 0x42f6f0
    void* request_object_texture_groups(int group_count); // @ 0x42f930
    void calc_object_bounding_box(); // @ 0x42fb10
    void calc_object_facequad_normals(); // @ 0x42fcb0
    void calc_object_texture_groups(); // @ 0x4303f0
    void calc_object_edges(); // @ 0x4308b0

    char unknown_00[0x10];
    unsigned int flags; // +0x10
    int field_14; // +0x14
    TextureRef* override_texture_ref; // +0x18
    char unknown_1c[0x2c - 0x1c];
    int vertex_count; // +0x2c
    char unknown_30[0x40 - 0x30];
    int field_40; // +0x40
    void* vertex_normals; // +0x44
    char unknown_48[0x54 - 0x48];
    int facequad_count; // +0x54
    int facequad_capacity; // +0x58
    ObjectFaceQuad* facequads; // +0x5c
    char unknown_60[0x64 - 0x60];
    int texture_group_count; // +0x64
    int texture_group_capacity; // +0x68
    int* texture_group_ends; // +0x6c, cumulative facequad ends
    char unknown_70[0xc0 - 0x70];
    ObjectRenderBuffers* render_buffers; // +0xc0
    int grouped_vertex_count; // +0xc4
    ObjectIndexBuffer* index_buffer; // +0xc8
    int* group_index_starts; // +0xcc
    TextureRef** group_texture_refs; // +0xd0
    int* group_primitive_counts; // +0xd4
    ObjectIndexBuffer* toon_index_buffer; // +0xd8
};

typedef char Object_must_be_0xdc[(sizeof(Object) == 0xdc) ? 1 : -1];

struct ObjectList {
    void initialize_object_list(int capacity); // @ 0x42f990
    void build_all_objects(); // @ 0x42f9e0
    Object* add_object_to_list(); // @ 0x42fad0
    void replace_object_list_texture_refs(TextureRef* new_texture, TextureRef* old_texture);

    int count; // +0x00
    int capacity; // +0x04
    Object* objects; // +0x08
};

void replace_object_group_texture_refs(Object* object, TextureRef* new_texture,
    TextureRef* old_texture); // @ 0x4145c0

extern ObjectList g_object_list; // data_4b7648

#endif
