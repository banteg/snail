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
    OBJECT_FLAG_BUILD_TOON_EDGES = 0x00000001,
    OBJECT_FLAG_DYNAMIC_VERTICES = 0x00000004,
    OBJECT_FLAG_USE_OVERRIDE_TEXTURE = 0x00000008,
    OBJECT_FLAG_REFRESH_TINT_EACH_DRAW = 0x00000010,
    OBJECT_FLAG_TINT_DIRTY = 0x00000040,
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

typedef enum ObjectToonEdgeFlag {
    OBJECT_TOON_EDGE_FLAG_BOUNDARY = 0x1,
    OBJECT_TOON_EDGE_FLAG_SHARED = 0x2,
} ObjectToonEdgeFlag;

typedef struct ObjectToonEdge {
    ObjectToonEdgeFlag flags;
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
    int32_t heightmap_sample_count;
    uint8_t _pad_20[0x24 - 0x20];
    float heightmap_sample_divisor;
    float heightmap_sample_scale;
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

typedef enum FrameSequenceFlag {
    FRAME_SEQUENCE_COMPLETE = 0x01,
    FRAME_SEQUENCE_LOOP = 0x02,
    FRAME_SEQUENCE_PING_PONG = 0x04,
    FRAME_SEQUENCE_REVERSE = 0x08,
    FRAME_SEQUENCE_PAUSED = 0x10,
} FrameSequenceFlag;

/* Authored Object-derived animated texture sequence, exact size 0xf0. */
typedef struct FrameSequence {
    Object object;
    int32_t sequence_flags;
    int32_t current_frame_index;
    float phase;
    float phase_step;
    TextureRef* current_texture_ref;
} FrameSequence;

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

typedef char ObjectList_must_be_0x0c[(sizeof(ObjectList) == 0x0c) ? 1 : -1];

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
typedef struct D3DPresentParameters {
    uint32_t back_buffer_width;
    uint32_t back_buffer_height;
    uint32_t back_buffer_format;
    uint32_t back_buffer_count;
    uint32_t multisample_type;
    uint32_t swap_effect;
    int32_t device_window;
    int32_t windowed;
    int32_t enable_auto_depth_stencil;
    uint32_t auto_depth_stencil_format;
    uint32_t flags;
    uint32_t fullscreen_refresh_rate_hz;
    uint32_t fullscreen_presentation_interval;
} D3DPresentParameters;

typedef struct D3DDeviceCaps8 {
    uint8_t _pad_00[0x58];
    uint32_t max_texture_width;
    uint32_t max_texture_height;
    uint8_t _pad_60[0xd4 - 0x60];
} D3DDeviceCaps8;

typedef struct D3DDisplayMode {
    uint32_t width;
    uint32_t height;
    uint32_t refresh_rate;
    uint32_t format;
} D3DDisplayMode;

typedef struct D3DViewport8 {
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
    float min_z;
    float max_z;
} D3DViewport8;

typedef struct Direct3D8 Direct3D8;
typedef struct Direct3DDevice8 Direct3DDevice8;
typedef struct Direct3DTexture8 Direct3DTexture8;

typedef struct Direct3D8Vtbl {
    uint8_t _pad_000[0x08];
    int32_t (__stdcall* Release)(Direct3D8* self);
    uint8_t _pad_00c[0x20 - 0x0c];
    int32_t (__stdcall* GetAdapterDisplayMode)(
        Direct3D8* self, uint32_t adapter, D3DDisplayMode* mode);
    uint8_t _pad_024[0x34 - 0x24];
    int32_t (__stdcall* GetDeviceCaps)(
        Direct3D8* self, uint32_t adapter, uint32_t device_type,
        D3DDeviceCaps8* caps);
    uint8_t _pad_038[0x3c - 0x38];
    int32_t (__stdcall* CreateDevice)(
        Direct3D8* self, uint32_t adapter, uint32_t device_type,
        int32_t focus_window, uint32_t behavior_flags,
        D3DPresentParameters* parameters, Direct3DDevice8** out_device);
} Direct3D8Vtbl;

struct Direct3D8 {
    Direct3D8Vtbl* vtbl;
};

typedef struct Direct3DTexture8Vtbl {
    uint8_t _pad_000[0x08];
    int32_t (__stdcall* Release)(Direct3DTexture8* self);
} Direct3DTexture8Vtbl;

struct Direct3DTexture8 {
    Direct3DTexture8Vtbl* vtbl;
};

typedef struct Direct3DDevice8Vtbl {
    uint8_t _pad_000[0x08];
    int32_t (__stdcall* Release)(Direct3DDevice8* self);
    uint8_t _pad_00c[0x38 - 0x0c];
    int32_t (__stdcall* Reset)(
        Direct3DDevice8* self, D3DPresentParameters* parameters);
    int32_t (__stdcall* Present)(
        Direct3DDevice8* self, void* source_rect, void* dest_rect,
        int32_t dest_window_override, void* dirty_region);
    uint8_t _pad_040[0x5c - 0x40];
    int32_t (__stdcall* CreateVertexBuffer)(
        Direct3DDevice8* self, uint32_t length, uint32_t usage, uint32_t fvf,
        uint32_t pool, ObjectVertexBuffer** out_buffer);
    int32_t (__stdcall* CreateIndexBuffer)(
        Direct3DDevice8* self, uint32_t length, uint32_t usage, uint32_t format,
        uint32_t pool, ObjectIndexBufferResource** out_buffer);
    uint8_t _pad_064[0x88 - 0x64];
    int32_t (__stdcall* BeginScene)(Direct3DDevice8* self);
    int32_t (__stdcall* EndScene)(Direct3DDevice8* self);
    int32_t (__stdcall* Clear)(
        Direct3DDevice8* self, uint32_t count, void* rects, uint32_t flags,
        uint32_t color, float z, uint32_t stencil);
    int32_t (__stdcall* SetTransform)(
        Direct3DDevice8* self, int32_t state, TransformMatrix* matrix);
    int32_t (__stdcall* GetTransform)(
        Direct3DDevice8* self, int32_t state, TransformMatrix* matrix);
    int32_t (__stdcall* MultiplyTransform)(
        Direct3DDevice8* self, int32_t state, TransformMatrix* matrix);
    int32_t (__stdcall* SetViewport)(
        Direct3DDevice8* self, D3DViewport8* viewport);
    int32_t (__stdcall* GetViewport)(
        Direct3DDevice8* self, D3DViewport8* viewport);
    uint8_t _pad_0a8[0xc8 - 0xa8];
    int32_t (__stdcall* SetRenderState)(
        Direct3DDevice8* self, int32_t state, int32_t value);
    uint8_t _pad_0cc[0xf4 - 0xcc];
    int32_t (__stdcall* SetTexture)(
        Direct3DDevice8* self, uint32_t stage, Direct3DTexture8* texture);
    uint8_t _pad_0f8[0xfc - 0xf8];
    int32_t (__stdcall* SetTextureStageState)(
        Direct3DDevice8* self, uint32_t stage, uint32_t type, uint32_t value);
    uint8_t _pad_100[0x118 - 0x100];
    int32_t (__stdcall* DrawPrimitive)(
        Direct3DDevice8* self, uint32_t primitive_type,
        uint32_t start_vertex, uint32_t primitive_count);
    int32_t (__stdcall* DrawIndexedPrimitive)(
        Direct3DDevice8* self, uint32_t primitive_type,
        uint32_t min_vertex_index, uint32_t vertex_count,
        uint32_t start_index, uint32_t primitive_count);
    uint8_t _pad_120[0x130 - 0x120];
    int32_t (__stdcall* SetVertexShader)(
        Direct3DDevice8* self, uint32_t shader);
    uint8_t _pad_134[0x14c - 0x134];
    int32_t (__stdcall* SetStreamSource)(
        Direct3DDevice8* self, uint32_t stream,
        ObjectVertexBuffer* buffer, uint32_t stride);
    uint8_t _pad_150[0x154 - 0x150];
    int32_t (__stdcall* SetIndices)(
        Direct3DDevice8* self, ObjectIndexBufferResource* index_buffer,
        uint32_t base_vertex_index);
} Direct3DDevice8Vtbl;

struct Direct3DDevice8 {
    Direct3DDevice8Vtbl* vtbl;
};

typedef struct Direct3DRenderer {
    VertexBufferFactory vertex_buffer_factory;
    IndexBufferFactory index_buffer_factory;
    ObjectRenderBuffers* renderer_state;
    uint8_t device_initialized;
    uint8_t _pad_bb8d[0xbb90 - 0xbb8d];
    Direct3D8* d3d;
    Direct3DDevice8* device;
    D3DPresentParameters present;
    D3DDeviceCaps8 device_caps;
    uint32_t display_format;
    uint32_t requested_width;
    uint32_t requested_height;
    uint32_t create_device_flags;
    uint32_t unknown_bcb0;
    uint32_t unknown_bcb4;
    uint32_t depth_stencil_format;
    uint32_t multisample_type;
} Direct3DRenderer;

void __cdecl initialize_textured_backdrop_quad(
    Object* object, char* texture_path, float x_offset);
void __cdecl raise_backdrop_quad_edge_pair(int32_t selector, Object* object);
void __cdecl initialize_backdrop_slice_quad(
    Object* object, char* texture_path, float x_offset);
void __cdecl initialize_backdrop_corner_quad(
    int32_t selector, Object* object, char* texture_path);
void __cdecl initialize_backdrop_tile_quad(
    Object* object, int32_t edge_selector, int32_t orientation,
    int32_t row_selector, int32_t column_selector, char* texture_path);
void __fastcall rotate_object_facequad_uv_pairs(ObjectFaceQuad* quad);

void* __thiscall noop_this_constructor(void* self);
void __thiscall initialize_object(Object* object);
void __thiscall initialize_object_list(ObjectList* object_list, int32_t capacity);
void __thiscall build_all_objects(ObjectList* object_list);
Object* __thiscall add_object_to_list(ObjectList* object_list);
void __thiscall replace_object_list_texture_refs(
    ObjectList* object_list, TextureRef* new_texture, TextureRef* old_texture);
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
void __thiscall advance_frame_sequence(FrameSequence* sequence);
void __cdecl sort_object_faces_by_texture_group(Object* object);
void __cdecl build_object_texture_group_buffers(Object* object);
int32_t __cdecl get_or_append_object_texture_group_vertex(
    Object* object, int32_t vertex_index, float u, float v);
void __cdecl refresh_object_vertex_buffer(Object* object);
tColourSmall* __thiscall pack_color_rgba_u8(
    tColourSmall* out, tColour* color);
void __cdecl set_object_color(Object* object, tColour color);
int32_t __cdecl render_object_toon(
    Object* object, TransformMatrix* matrix);
int32_t __cdecl render_object(
    Object* object, TransformMatrix* matrix, float texture_u,
    float texture_v, tColour* color, char after_sprites);
TransformMatrix* __cdecl render_camera(
    float viewport_x, float viewport_y, float viewport_width,
    float viewport_height, float fov_degrees, TransformMatrix* camera_matrix,
    TransformMatrix* view_matrix, char draw_world, char post_sprite_pass);
TransformMatrix* __stdcall build_perspective_projection_matrix(
    TransformMatrix* matrix, float vertical_fov_radians, float aspect_ratio,
    float near_z, float far_z);
TransformMatrix* __stdcall build_camera_view_matrix(
    TransformMatrix* matrix, const Vec3* eye, const Vec3* target,
    const Vec3* up);
ObjectRenderBuffers* __thiscall create_vertex_buffer(
    VertexBufferFactory* factory, int32_t vertex_count, int32_t fvf);
ObjectIndexBuffer* __thiscall create_index_buffer(
    IndexBufferFactory* factory, int32_t index_count);
void __thiscall initialize_direct3d_renderer_defaults(Direct3DRenderer* renderer);
void __thiscall release_direct3d_renderer_resources(Direct3DRenderer* renderer);
int32_t __thiscall direct3d_renderer_set_cull_mode(
    Direct3DRenderer* renderer, uint8_t cull_front);
void __thiscall initialize_d3d8_device(
    Direct3DRenderer* renderer, uint8_t use_present_interval_one);
void __thiscall reset_direct3d_render_state(Direct3DRenderer* renderer);
void __thiscall release_direct3d_device_interfaces(Direct3DRenderer* renderer);
uint8_t __cdecl initialize_direct3d_renderer(void);
int32_t __cdecl set_cull_mode(int32_t cull_front);
void __cdecl set_blend_mode(int32_t blend_mode);
void __cdecl set_immediate_blend_mode(int32_t blend_mode);
void __cdecl draw_textured_quad_immediate(
    TextureRef* texture, float x0, float y0, float x1, float y1,
    float x2, float y2, float x3, float y3, float width, float height,
    float u0, float v0, float u1, float v1, tColour* color,
    int32_t blend_mode, float rotation);
void __cdecl release_global_direct3d_renderer_resources(void);
int32_t __cdecl present_backbuffer(void);
void __cdecl set_fullscreen_mode(uint8_t enabled);
void __thiscall direct3d_renderer_set_fullscreen_mode(
    Direct3DRenderer* renderer, uint8_t enabled);
void __thiscall restore_texture_ref_stage_states(Direct3DRenderer* renderer);
void __cdecl bind_texture_ref(TextureRef* texture);
void __thiscall query_direct3d_device_caps(Direct3DRenderer* renderer);
int32_t __cdecl reset_render_counters(void);

extern ObjectToonEdge* g_object_edge_build_edges;
extern int32_t g_object_edge_build_count;
extern ObjectList g_object_list;
extern int32_t g_backdrop_raise_first_vertex_index;
extern int32_t g_backdrop_raise_second_vertex_index;
extern int32_t g_backdrop_corner_vertex_indices[4];
extern int32_t g_object_grouped_vertex_cursor;
extern ObjectGroupedVertex* g_object_grouped_vertex_scratch;
extern Direct3DRenderer g_direct3d_renderer;
extern int32_t g_render_triangle_count;
extern int32_t g_render_successful_primitive_count;
extern int32_t g_draw_primitive_call_count;
extern float g_render_projection_param_b;
extern TextureRef* g_current_texture_ref;
extern TransformMatrix* g_render_camera_source_matrix;
extern int32_t g_texture_bind_call_count;
extern Direct3DTexture8** g_d3d_texture_slots;
extern float g_render_projection_near_z;
extern float g_render_projection_far_z;
extern float g_render_projection_param_a;
extern TransformMatrix* g_render_camera_view_matrix;
extern uint8_t g_object_render_pass_filter;
