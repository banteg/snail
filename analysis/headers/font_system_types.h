#ifndef FONT_SYSTEM_TYPES_H
#define FONT_SYSTEM_TYPES_H

/*
 * Narrow cross-decompiler owner slice for the Windows font runtime.
 *
 * The global layout is contiguous and independently bounded:
 *
 *   0x4b7236  uint8_t render_queue_active
 *   0x753ce8  char text_buffer[0x800]
 *   0x7544e8  cFontPrintBuffer queue[0x400]
 *   0x7754e8  BodBase font3d_bods[0x80]
 *   0x7770e8  float font3d_scales[0x80]
 *   0x7772f8  FontSheet font_sheets[1]
 *   0x777b20  int32_t registered_font_count
 *
 * Android symbols preserve cFontPrintBuffer and its 0x84-byte stride. The
 * Windows atlas registrar, width calculator, text renderer, and 3D-font
 * materializer agree on the complete 0x828-byte FontSheet layout.
 */

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef int int32_t;
typedef short int16_t;

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
    char name[0x80];
    int32_t slot_index;
    int32_t frame_count;
    float frame_progress_step;
    void* texture_ref;
    uint8_t unknown_9c[0x4];
    int32_t mip_levels;
} TextureRef;

typedef struct tColour {
    float r;
    float g;
    float b;
    float a;
} tColour;

typedef struct FontSheet {
    int32_t slot_count;
    TextureRef* texture_ref_a;
    TextureRef* texture_ref_b;
    float u0[0x80];
    float v0[0x80];
    float glyph_width[0x80];
    int32_t texture_page[0x80];
    float line_marker_y;
    float line_step;
    float line_marker_fraction;
    float spacing_scale;
    float width_scale;
    float height_scale;
    int32_t font_kind;
} FontSheet;

typedef struct cFontPrintBuffer {
    uint32_t flags;
    float x0;
    float y0;
    int32_t unknown_0c;
    float x1;
    float y1;
    int32_t unknown_18;
    float x2;
    float y2;
    int32_t unknown_24;
    float x3;
    float y3;
    int32_t unknown_30;
    float text_wave_amplitude;
    uint8_t text_wave_enabled;
    char pad_39[3];
    int32_t font_id;
    float text_scale;
    char* text;
    int32_t horizontal_align;
    float anchor_x;
    int32_t texture_id;
    float width;
    float height;
    float u0;
    float v0;
    float u1;
    float v1;
    tColour color;
    int32_t blend_mode;
    float rotation;
} cFontPrintBuffer;

void __cdecl initialize_global_font3d_bods_thunk(void);
void __cdecl initialize_global_font3d_bods(void);
void __cdecl initialize_global_font_queue_colors_thunk(void);
void __cdecl initialize_global_font_queue_colors(void);
float __cdecl measure_font_text_width(char* text, int32_t font_id, float scale);
int32_t __cdecl register_font_texture_sheet(
    char* texture_path,
    int32_t font_kind,
    float width_scale,
    float height_scale);
void __cdecl draw_font_text_instance(cFontPrintBuffer* entry);
void __cdecl draw_queued_font_quad_instance(cFontPrintBuffer* entry);
void __cdecl draw_font_text_queue(uint32_t render_mask);
void __cdecl queue_font_text_instance(
    char* text,
    int32_t font_id,
    float text_scale,
    float x,
    float y,
    int32_t horizontal_align,
    float anchor_x,
    uint32_t flags,
    tColour* color,
    float text_wave_amplitude,
    uint8_t text_wave_enabled);
int32_t __cdecl queue_axis_aligned_textured_quad(
    int32_t texture_id,
    float x,
    float y,
    float width,
    float height,
    uint32_t flags,
    tColour* color,
    int32_t blend_mode);
int32_t __cdecl queue_axis_aligned_textured_quad_uv(
    int32_t texture_id,
    float x,
    float y,
    float width,
    float height,
    uint32_t flags,
    tColour* color,
    float u0,
    float v0,
    float u1,
    float v1,
    int32_t blend_mode,
    float rotation);
int32_t __cdecl queue_textured_quad_corners(
    int32_t texture_id,
    float x0,
    float y0,
    float x1,
    float y1,
    float x2,
    float y2,
    float x3,
    float y3,
    int32_t unused_28,
    int32_t unused_2c,
    uint32_t flags,
    tColour* color,
    float u0,
    float v0,
    float u1,
    float v1,
    int32_t blend_mode,
    float rotation);
float* __cdecl layout_and_queue_wrapped_font_text(
    char* text,
    int32_t font_id,
    float text_scale,
    float x,
    float y,
    float* out_x,
    float* out_y,
    float* out_width,
    float* out_height,
    float text_wave_amplitude,
    uint8_t text_wave_enabled,
    int32_t horizontal_align,
    float anchor_x,
    uint32_t flags,
    tColour* color,
    uint8_t measure_only,
    uint8_t pulse_alpha);
void __cdecl initialize_font3d_objects(int16_t font_id);

#endif
