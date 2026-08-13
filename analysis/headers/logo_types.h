#ifndef LOGO_TYPES_H
#define LOGO_TYPES_H

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef int int32_t;

typedef struct Object Object;
typedef struct AnimManager AnimManager;

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

typedef struct BodNode {
    void* vtable;
    uint32_t list_flags;
    struct BodNode* list_prev;
    struct BodNode* list_next;
} BodNode;

typedef struct BodBase {
    BodNode bod;
    Vec3 position;
    float render_arg_1c;
    float render_arg_20;
    Object* object;
    tColour color;
} BodBase;

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

typedef struct RenderableBod {
    BodBase bod;
    TransformMatrix transform;
    AnimManager* render_animation_manager;
    int32_t frame_number;
} RenderableBod;

/* Windows cRLogoLetter layout; mobile ports use a smaller BOD prefix. */
typedef struct cRLogoLetter {
    RenderableBod renderable;
    Vec3 velocity;
    uint8_t glyph;
    uint8_t _pad_8d[0x90 - 0x8d];
} cRLogoLetter;

/* Exact Windows cRLogo owner at GameRoot +0x4f400. */
typedef struct cRLogo {
    float progress;
    float progress_step;
    int32_t state;
    int32_t saved_render_flags;
    float duration_seconds;
    int32_t renderable_count;
    cRLogoLetter letters[0x400];
    cRLogoLetter image_donors[0x20];
} cRLogo;

cRLogoLetter* __thiscall initialize_intro_logo_renderable(cRLogoLetter* letter);
void __thiscall open_logo(cRLogo* logo);
void __thiscall initialize_intro_screen(cRLogo* logo, char* file_name);
void __thiscall destroy_intro_screen(cRLogo* logo);
void __thiscall update_intro_screen(cRLogo* logo);
void __thiscall update_intro_logo_renderable(cRLogoLetter* letter);

#endif
