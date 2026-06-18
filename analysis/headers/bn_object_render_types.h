typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef int int32_t;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

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

typedef struct ObjectRenderBuffers {
    uint8_t _pad_00[0x08];
    void* vertex_buffer;
} ObjectRenderBuffers;

typedef struct Object {
    uint8_t _pad_00[0xdc];
} Object;

ObjectAnimation* __thiscall request_object_animation(
    Object* object, int32_t keyframe_count, void* keyframes,
    float progress_step, uint16_t flags);
void __cdecl refresh_object_vertex_buffer(Object* object);
