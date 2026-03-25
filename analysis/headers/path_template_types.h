#ifndef PATH_TEMPLATE_TYPES_H
#define PATH_TEMPLATE_TYPES_H

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef short int16_t;
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
    uint8_t _pad_04[0x25];
} TextureRef;

typedef enum PathTemplateStripMeshFlags {
    PATH_TEMPLATE_STRIP_MESH_FLAG_HAS_VERTEX_COLOURS = 0x10000,
} PathTemplateStripMeshFlags;

typedef struct ObjectFaceQuad {
    uint16_t flags;
    uint16_t vertex_index_a;
    uint16_t vertex_index_b;
    uint16_t vertex_index_c;
    uint16_t vertex_index_d;
    uint16_t _pad_0a;
    TextureRef* texture_ref;
    float u0;
    float v0;
    float u1;
    float v1;
    float u2;
    float v2;
    float u3;
    float v3;
} ObjectFaceQuad;

typedef struct PathTemplateStripMesh {
    uint8_t _pad_00[0x10];
    PathTemplateStripMeshFlags flags;
    uint8_t _pad_14[0x18];
    uint32_t vertex_count;
    uint8_t _pad_30[0x8];
    Vec3* vertices;
    uint8_t _pad_3c[0xc];
    Color4f* vertex_colours;
    uint8_t _pad_4c[0x8];
    uint32_t facequad_count;
    uint32_t facequad_capacity;
    ObjectFaceQuad* facequads;
} PathTemplateStripMesh;

typedef struct PathTemplateSample {
    Vec3 basis_right;
    float _pad_0c;
    Vec3 basis_up;
    float _pad_1c;
    Vec3 basis_forward;
    float _pad_2c;
    Vec3 position;
    uint8_t _pad_3c[0x44];
    Vec3 delta_dir_to_next;
    float delta_length;
    float center_x;
    float rotation_scalar_94;
    float rotation_scalar_98;
    float lateral_scale;
    float special_scalar;
    uint8_t _pad_a4[0x4];
} PathTemplateSample;

typedef struct PathTemplate {
    uint8_t _pad_00[0x24];
    PathTemplateStripMesh* strip_mesh;
    uint8_t _pad_28[0x8];
    float header_30;
    float header_34;
    uint32_t kind;
    uint8_t is_mirrored_x;
    uint8_t _pad_3d[0x3];
    uint32_t side_exit_mode;
    uint32_t segment_count;
    uint32_t _pad_48;
    float segment_count_f;
    float width_or_scale;
    uint32_t width_cells;
    PathTemplateSample* primary_samples;
    PathTemplateSample* secondary_samples;
    uint8_t _pad_60[0x38];
    float installed_heading_delta;
    uint8_t special_runtime_flag_9c;
    uint8_t _pad_9d[0x3];
    float header_a0;
    float header_a4;
} PathTemplate;

TextureRef* __thiscall get_or_create_texture_ref(int32_t* texture_list, char* texture_path, int32_t arg3, int16_t arg4);
void* __fastcall allocate_path_nodes(PathTemplate* self);
int32_t __fastcall finalize_path_template_record(PathTemplate* self);
int32_t __thiscall mirror_path_template_pair_x(PathTemplate* self, PathTemplate* source);
int32_t* __thiscall request_object_vertices(PathTemplateStripMesh* mesh, int32_t vertex_count);
int32_t* __fastcall request_object_vertex_colours(PathTemplateStripMesh* mesh);
void __thiscall request_object_facequads(PathTemplateStripMesh* mesh, int32_t facequad_count);

int32_t __thiscall initialize_looptheloop_path_template_pair(
    PathTemplate* self,
    float arg2,
    int32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_loopout_path_template_pair(
    PathTemplate* self,
    float arg2,
    int32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_detour_path_template_pair(
    PathTemplate* self,
    int32_t arg2,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_supertramp_path_template_pair(
    PathTemplate* self,
    float arg2,
    int32_t arg3,
    char* texture_a,
    char* texture_b,
    char* texture_c
);

int32_t __thiscall initialize_kind42_path_template_pair(
    PathTemplate* self,
    int32_t arg2,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_halfpipe_path_template_pair(
    PathTemplate* self,
    float arg2,
    float arg3,
    int32_t arg4,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_looptheloopw_path_template_pair(
    PathTemplate* self,
    float arg2,
    int32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_halfpole_path_template_pair(
    PathTemplate* self,
    float arg2,
    float arg3,
    int32_t arg4,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_cage2_path_template_pair(
    PathTemplate* self,
    float arg2,
    int32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_screw_path_template_pair(
    PathTemplate* self,
    int32_t arg2,
    int32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_slalom_path_template_pair(
    PathTemplate* self,
    int32_t arg2,
    uint32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_worm_path_template_pair(
    PathTemplate* self,
    char* texture_path
);

int32_t __thiscall initialize_slalombig_path_template_pair(
    PathTemplate* self,
    int32_t arg2,
    uint32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_sweep_path_template_pair(
    PathTemplate* self,
    int32_t arg2,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_snake_path_template_pair(
    PathTemplate* self,
    int32_t arg2,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_dip_path_template_pair(
    PathTemplate* self,
    int32_t arg2,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_p_path_template_pair(
    PathTemplate* self,
    int32_t arg2,
    uint32_t arg3,
    float arg4,
    float arg5,
    int32_t arg6,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_start_path_template_pair(
    PathTemplate* self,
    float arg2,
    int32_t arg3,
    char* texture_path
);

int32_t __thiscall initialize_turnover_path_template_pair(
    PathTemplate* self,
    float arg2,
    int32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_turnoverdouble_path_template_pair(
    PathTemplate* self,
    float arg2,
    int32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_turnunder_path_template_pair(
    PathTemplate* self,
    float arg2,
    int32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_wibble_path_template_pair(
    PathTemplate* self,
    int32_t arg2,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_invert_path_template_pair(
    PathTemplate* self,
    int32_t arg2,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_twister_path_template_pair(
    PathTemplate* self,
    float arg2,
    int32_t arg3,
    char arg4,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_twister2_path_template_pair(
    PathTemplate* self,
    float arg2,
    int32_t arg3,
    char arg4,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_loopbow_path_template_pair(
    PathTemplate* self,
    float arg2,
    uint32_t arg3,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_toad_path_template_pair(
    PathTemplate* self,
    char arg2,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_hill_valley_path_template_pair(
    PathTemplate* self,
    int32_t arg2,
    float arg3,
    float arg4,
    char arg5,
    char* texture_a,
    char* texture_b
);

int32_t __thiscall initialize_sbend_path_template_pair(
    PathTemplate* self,
    uint32_t arg2,
    float arg3,
    float arg4,
    char arg5,
    char* texture_a,
    char* texture_b
);

#endif
