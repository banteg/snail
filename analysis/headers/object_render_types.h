typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef int int32_t;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct tColour {
    float r;
    float g;
    float b;
    float a;
} tColour;

typedef struct tColourSmall {
    uint8_t b;
    uint8_t g;
    uint8_t r;
    uint8_t a;
} tColourSmall;

typedef enum TextureRefFlags {
    TEXTURE_REF_RETAIN_SOURCE_BYTES = 0x20,
    TEXTURE_REF_REGISTERED = 0x400,
    TEXTURE_REF_DISABLE_PATH_REUSE = 0x800,
    TEXTURE_REF_WRAP_ADDRESSING = 0x1000,
    TEXTURE_REF_ANIMATED = 0x2000,
    TEXTURE_REF_ANIMATION_PING_PONG = 0x4000,
    TEXTURE_REF_SKIP_RUNTIME_LOAD = 0x8000,
    TEXTURE_REF_HAS_ALPHA = 0x10000,
} TextureRefFlags;

typedef struct TextureRef {
    TextureRefFlags flags;
    int32_t loaded_width;
    int32_t loaded_height;
    char name[0x8c - 0x0c];
    int32_t slot_index;
    int32_t frame_count;
    float frame_progress_step;
    void* texture_ref;
    uint8_t unknown_9c[0xa0 - 0x9c];
    int32_t mip_levels;
} TextureRef;

typedef enum ObjectFlag {
    OBJECT_FLAG_DYNAMIC_VERTICES = 0x00000004,
    OBJECT_FLAG_USE_OVERRIDE_TEXTURE = 0x00000008,
    OBJECT_FLAG_TEXTURE_TRANSFORM = 0x00000080,
    OBJECT_FLAG_TOON_ENABLED = 0x00004000,
    OBJECT_FLAG_USE_VERTEX_COLOURS = 0x00010000,
    OBJECT_FLAG_RENDER_DISABLED = 0x00040000,
    OBJECT_FLAG_RENDER_BUFFERS_READY = 0x00080000,
    OBJECT_FLAG_DISABLE_CULLING = 0x00100000,
    OBJECT_FLAG_HAS_ANIMATION = 0x00200000,
    OBJECT_FLAG_DISTORT_ENABLED = 0x00800000,
} ObjectFlag;

typedef struct ObjectUv {
    float u;
    float v;
} ObjectUv;

typedef struct ObjectGroupedVertex {
    float x;
    float y;
    float z;
    uint32_t diffuse;
    float u;
    float v;
    int32_t source_vertex;
} ObjectGroupedVertex;

typedef struct ObjectRenderVertex {
    float x;
    float y;
    float z;
    uint32_t diffuse;
    float u;
    float v;
} ObjectRenderVertex;

typedef struct TransformMatrix {
    Vec3 basis_right;
    float basis_right_w;
    Vec3 basis_up;
    float basis_up_w;
    Vec3 basis_forward;
    float basis_forward_w;
    Vec3 position;
    float position_w;
} TransformMatrix;

typedef enum ObjectFaceQuadFlag {
    OBJECT_FACEQUAD_FLAG_TRIANGLE = 0x80,
} ObjectFaceQuadFlag;

typedef struct ObjectFaceQuad {
    union {
        uint16_t header_word;
        struct {
            uint8_t flags;
            uint8_t secondary_flags;
        };
    };
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
    int32_t vertex_a;
    int32_t vertex_b;
    int32_t normal_a;
    int32_t normal_b;
    Vec3 direction;
    float length;
} ObjectToonEdge;

typedef struct ObjectAnimationFrame {
    Vec3* vertices;
    Vec3* facequad_normals;
} ObjectAnimationFrame;

typedef enum ObjectAnimationFlag {
    OBJECT_ANIMATION_MODE_LOOP = 1,
    OBJECT_ANIMATION_MODE_PING_PONG = 2,
    OBJECT_ANIMATION_MODE_ONCE = 4,
    OBJECT_ANIMATION_MODE_ONCE_REVERSE = 8,
} ObjectAnimationFlag;

typedef enum ObjectAnimationModeOverride {
    OBJECT_ANIMATION_MODE_UNCHANGED = -1,
} ObjectAnimationModeOverride;

typedef uint16_t ObjectAnimationFlags;

typedef struct ObjectAnimation {
    ObjectAnimationFlags flags;
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
    uint32_t fvf;
    int32_t unknown_04;
    ObjectVertexBuffer* vertex_buffer;
} ObjectRenderBuffers;

typedef struct ObjectDistort {
    float z_wave;
    float y_squash;
    float xyz_scale;
    float unknown_0c;
    float unknown_10;
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

typedef struct VertexBufferFactory {
    int32_t count;
    ObjectRenderBuffers buffers[0xbb8];
} VertexBufferFactory;

typedef struct IndexBufferFactory {
    int32_t count;
    ObjectIndexBuffer buffers[0xbb8];
} IndexBufferFactory;

typedef struct Object {
    uint8_t _pad_00[0x08];
    Vec3* toon_vertices;
    ObjectToonFaceQuadNormal* toon_facequad_normals;
    ObjectFlag flags;
    int32_t blend_mode;
    TextureRef* override_texture_ref;
    uint8_t _pad_1c[0x2c - 0x1c];
    int32_t vertex_count;
    uint8_t _pad_30[0x38 - 0x30];
    Vec3* vertices;
    Vec3* copied_vertices;
    int32_t field_40;
    Vec3* vertex_normals;
    tColour* vertex_colours;
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

typedef struct XAnimationKeyframe {
    uint8_t _pad_00[0x24];
    Object* object;
    uint8_t _pad_28[0x7c - 0x28];
    int32_t frame_number;
} XAnimationKeyframe;

typedef struct ObjectList {
    int32_t count;
    int32_t capacity;
    Object* objects;
} ObjectList;

typedef struct DuplicateVertexRecord {
    uint16_t source_vertex;
    uint16_t compare_vertex;
    uint8_t _pad_04[0x08 - 0x04];
    uint16_t live_flag;
} DuplicateVertexRecord;

typedef struct DuplicateVertices {
    int32_t active_count;
    DuplicateVertexRecord* records;
} DuplicateVertices;

typedef struct CachedXMeshSlot {
    uint8_t _pad_00[0x24];
    Object* object;
    uint8_t _pad_28[0x3c - 0x28];
    char name[0x80];
} CachedXMeshSlot;

typedef struct DirectXLoader {
    char* animation_bytes;
    int32_t cached_x_mesh_count;
    CachedXMeshSlot cached_x_mesh_slots[0x80];
    DuplicateVertices duplicate_vertices;
} DirectXLoader;

void* __thiscall noop_this_constructor(void* self);
void __thiscall initialize_object(Object* object);
void __thiscall initialize_object_list(ObjectList* object_list, int32_t capacity);
void __thiscall build_all_objects(ObjectList* object_list);
Object* __thiscall add_object_to_list(ObjectList* object_list);
void __thiscall apply_object_toon(Object* object, int32_t toon_flags);
void __thiscall request_object_vertices(Object* object, int32_t vertex_count);
void __thiscall copy_object_vertices(Object* object);
void __thiscall request_object_vertices_copy(Object* object);
void __fastcall request_object_vertex_colours(Object* object);
Vec3* __thiscall request_object_facequad_normals(Object* object);
void __thiscall request_object_facequads(Object* object, int32_t facequad_count);
void __thiscall request_object_texture_groups(Object* object, int32_t group_count);
void __thiscall request_object_edges(Object* object, int32_t edge_count);
void __cdecl load_object_definition(char* path, Object* object);

void __thiscall initialize_directx_loader(DirectXLoader* loader);
void __thiscall load_x_mesh(
    DirectXLoader* loader, char* mesh_path, Object* object, int32_t options_flags);
int32_t __thiscall load_or_reuse_cached_x_mesh(DirectXLoader* loader, char* mesh_name);
void __thiscall load_x_animation_clip(
    DirectXLoader* loader, char* mesh_name, Object* object);
void* __thiscall initialize_duplicate_vertices(
    DuplicateVertices* duplicate_vertices, int32_t count);
int32_t __thiscall clean_duplicate_vertices(
    DuplicateVertices* duplicate_vertices, int32_t unused);

void __thiscall calc_object_bounding_box(Object* object);
void __thiscall calc_object_facequad_normals(Object* object);
void __thiscall calc_object_texture_groups(Object* object);
void __thiscall add_object_edge(
    Object* object, int32_t vertex_a, int32_t vertex_b, int32_t normal_index);
void __thiscall calc_object_edges(Object* object);
void __thiscall apply_distort_to_object(ObjectDistort* distort, Object* object);

void __thiscall request_object_animation(
    Object* object, int32_t keyframe_count, XAnimationKeyframe* keyframes,
    float progress_step, int32_t flags);
void __cdecl build_object_texture_group_buffers(Object* object);
int32_t __cdecl get_or_append_object_texture_group_vertex(
    Object* object, int32_t vertex_index, float u, float v);
void __cdecl refresh_object_vertex_buffer(Object* object);
tColourSmall* __thiscall pack_color_rgba_u8(
    tColourSmall* out, tColour* color);
void __cdecl set_object_color(Object* object, tColour color);
int32_t __cdecl render_object(
    Object* object, TransformMatrix* matrix, float texture_u,
    float texture_v, tColour* color, char after_sprites);
ObjectRenderBuffers* __thiscall create_object_vertex_buffer_resource(
    VertexBufferFactory* factory, int32_t vertex_count, int32_t fvf);
ObjectIndexBuffer* __thiscall create_object_index_buffer_resource(
    IndexBufferFactory* factory, int32_t index_count);

extern ObjectToonEdge* g_object_edge_build_edges;
extern int32_t g_object_edge_build_count;
extern int32_t g_object_grouped_vertex_cursor;
extern ObjectGroupedVertex* g_object_grouped_vertex_scratch;
