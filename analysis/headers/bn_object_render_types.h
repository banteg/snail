typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef int int32_t;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Color4f {
    float r;
    float g;
    float b;
    float a;
} Color4f;

typedef struct TextureRef {
    uint32_t flags;
    uint8_t _pad_04[0x0c - 0x04];
    char name[0x8c - 0x0c];
    int32_t slot_index;
    int32_t frame_count;
    float frame_progress_step;
    void* texture_ref;
    uint8_t _pad_9c[0xa0 - 0x9c];
    int32_t unknown_a0;
} TextureRef;

typedef struct ObjectUv {
    float u;
    float v;
} ObjectUv;

typedef struct ObjectFaceQuad {
    uint8_t flags;
    uint8_t unknown_01;
    uint16_t vertex_0;
    uint16_t vertex_1;
    uint16_t vertex_2;
    uint16_t vertex_3;
    uint8_t _pad_0a[0x0c - 0x0a];
    TextureRef* texture_ref;
    ObjectUv uv[4];
} ObjectFaceQuad;

typedef struct ObjectToonFaceQuadNormal {
    uint8_t raw[0x18];
} ObjectToonFaceQuadNormal;

typedef struct ObjectToonEdge {
    uint32_t flags;
    uint16_t vertex_a;
    uint8_t _pad_06[0x08 - 0x06];
    uint16_t vertex_b;
    uint8_t _pad_0a[0x0c - 0x0a];
    int32_t normal_a;
    int32_t normal_b;
    Vec3 direction;
    float length;
} ObjectToonEdge;

typedef struct ObjectAnimationFrame {
    Vec3* vertices;
    Vec3* facequad_normals;
} ObjectAnimationFrame;

typedef struct ObjectAnimation {
    uint16_t flags;
    uint8_t _pad_02[0x04 - 0x02];
    int32_t generated_frame_count;
    ObjectAnimationFrame** frames;
    float progress;
    float progress_step;
} ObjectAnimation;

typedef struct ObjectVertexBuffer ObjectVertexBuffer;

typedef struct ObjectVertexBufferVtbl {
    uint8_t _pad_00[0x2c];
    int32_t (__stdcall* Lock)(
        ObjectVertexBuffer* self, int32_t offset, int32_t size, void** data, int32_t flags);
    int32_t (__stdcall* Unlock)(ObjectVertexBuffer* self);
} ObjectVertexBufferVtbl;

typedef struct ObjectVertexBuffer {
    ObjectVertexBufferVtbl* vtbl;
} ObjectVertexBuffer;

typedef struct ObjectRenderBuffers {
    uint8_t _pad_00[0x08];
    ObjectVertexBuffer* vertex_buffer;
} ObjectRenderBuffers;

typedef struct ObjectDistort {
    float z_wave;
    float y_squash;
    float xyz_scale;
} ObjectDistort;

typedef struct ObjectIndexBufferResource ObjectIndexBufferResource;

typedef struct ObjectIndexBufferResourceVtbl {
    uint8_t _pad_00[0x2c];
    int32_t (__stdcall* Lock)(
        ObjectIndexBufferResource* self, int32_t offset, int32_t size, void** data, int32_t flags);
    int32_t (__stdcall* Unlock)(ObjectIndexBufferResource* self);
} ObjectIndexBufferResourceVtbl;

typedef struct ObjectIndexBufferResource {
    ObjectIndexBufferResourceVtbl* vtbl;
} ObjectIndexBufferResource;

typedef struct ObjectIndexBuffer {
    ObjectIndexBufferResource* buffer;
} ObjectIndexBuffer;

typedef struct Object {
    uint8_t _pad_00[0x08];
    Vec3* toon_vertices;
    ObjectToonFaceQuadNormal* toon_facequad_normals;
    uint32_t flags;
    int32_t blend_mode;
    TextureRef* override_texture_ref;
    uint8_t _pad_1c[0x2c - 0x1c];
    int32_t vertex_count;
    uint8_t _pad_30[0x38 - 0x30];
    Vec3* vertices;
    Vec3* copied_vertices;
    int32_t field_40;
    Vec3* vertex_normals;
    Color4f* vertex_colours;
    uint8_t _pad_4c[0x54 - 0x4c];
    int32_t facequad_count;
    int32_t facequad_capacity;
    ObjectFaceQuad* facequads;
    Vec3* facequad_normals;
    int32_t texture_group_count;
    int32_t texture_group_capacity;
    int32_t* texture_group_ends;
    int32_t edge_count;
    ObjectToonEdge* edges;
    uint8_t _pad_78[0x80 - 0x78];
    ObjectDistort distort;
    uint8_t _pad_8c[0x94 - 0x8c];
    float bounding_radius;
    uint8_t _pad_98[0xa4 - 0x98];
    Vec3 bounds_min;
    Vec3 bounds_max;
    ObjectAnimation* animation;
    ObjectRenderBuffers* render_buffers;
    int32_t grouped_vertex_count;
    ObjectIndexBuffer* index_buffer;
    int32_t* group_index_starts;
    TextureRef** group_texture_refs;
    int32_t* group_primitive_counts;
    ObjectIndexBuffer* toon_index_buffer;
} Object;

ObjectAnimation* __thiscall request_object_animation(
    Object* object, int32_t keyframe_count, void* keyframes,
    float progress_step, uint16_t flags);
void __cdecl refresh_object_vertex_buffer(Object* object);
