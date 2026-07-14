#ifndef LOGO_TYPES_H
#define LOGO_TYPES_H

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef int int32_t;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Vec4 {
    float x;
    float y;
    float z;
    float w;
} Vec4;

typedef struct Color4f {
    float r;
    float g;
    float b;
    float a;
} Color4f;

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
    void* object;
    Color4f color;
} BodBase;

typedef struct TransformMatrix {
    Vec4 basis_right;
    Vec4 basis_up;
    Vec4 basis_forward;
    Vec4 position;
} TransformMatrix;

typedef struct RenderableBod {
    BodBase bod;
    TransformMatrix transform;
    void* render_animation_manager;
    uint8_t unknown_7c[0x4];
} RenderableBod;

/* Windows cRLogoLetter layout; mobile ports use a smaller BOD prefix. */
typedef struct LogoLetter {
    RenderableBod renderable;
    Vec3 velocity;
    uint8_t glyph;
    uint8_t _pad_8d[0x90 - 0x8d];
} LogoLetter;
typedef LogoLetter IntroLogoRenderable;

/* Exact Windows cRLogo owner at GameRoot +0x4f400. */
typedef struct Logo {
    float progress;
    float progress_step;
    int32_t state;
    int32_t saved_render_flags;
    float duration_seconds;
    int32_t renderable_count;
    LogoLetter letters[0x400];
    LogoLetter image_donors[0x20];
} Logo;
typedef Logo IntroScreenRuntime;

LogoLetter* __thiscall initialize_intro_logo_renderable(LogoLetter* letter);
int32_t __thiscall open_logo(Logo* logo);
void __thiscall initialize_intro_screen(Logo* logo, char* file_name);
int32_t __thiscall destroy_intro_screen(Logo* logo);
void __thiscall update_intro_screen(Logo* logo);
void __thiscall update_intro_logo_renderable(LogoLetter* letter);

#endif
