#ifndef PATH_TEMPLATE_TYPES_H
#define PATH_TEMPLATE_TYPES_H

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef int int32_t;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

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
    uint8_t _pad_00[0x30];
    float header_30;
    float header_34;
    uint32_t kind;
    uint32_t is_mirrored_x;
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
    float special_runtime_flag_9c;
    float header_a0;
    float header_a4;
} PathTemplate;

void* __fastcall allocate_path_nodes(PathTemplate* self);
int32_t __fastcall finalize_path_template_record(PathTemplate* self);
int32_t __thiscall mirror_path_template_pair_x(PathTemplate* self, PathTemplate* source);

int32_t __thiscall initialize_looptheloop_path_template_pair(
    PathTemplate* self,
    float arg2,
    int32_t arg3,
    char* arg4,
    char* arg5
);

int32_t __thiscall initialize_loopout_path_template_pair(
    PathTemplate* self,
    float arg2,
    int32_t arg3,
    char* arg4,
    char* arg5
);

int32_t __thiscall initialize_detour_path_template_pair(
    PathTemplate* self,
    int32_t arg2,
    char* arg3,
    char* arg4
);

int32_t __thiscall initialize_supertramp_path_template_pair(
    PathTemplate* self,
    float arg2,
    int32_t arg3,
    char* arg4,
    char* arg5,
    char* arg6
);

int32_t __thiscall initialize_kind42_path_template_pair(
    PathTemplate* self,
    int32_t arg2,
    char* arg3,
    char* arg4
);

int32_t __thiscall initialize_halfpipe_path_template_pair(
    PathTemplate* self,
    float arg2,
    float arg3,
    int32_t arg4,
    char* arg5,
    char* arg6
);

#endif
