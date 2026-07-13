#ifndef FONT_SYSTEM_H
#define FONT_SYSTEM_H

#include "main_loop_state.h"
#include "sprite.h"

struct FontSheet {
    int slot_count;             // +0x000
    TextureRef* texture_ref_a;  // +0x004
    TextureRef* texture_ref_b;  // +0x008
    float u0[128];              // +0x00c
    float v0[128];              // +0x20c
    float glyph_width[128];     // +0x40c
    int texture_page[128];      // +0x60c
    float line_marker_y;        // +0x80c
    float line_step;            // +0x810
    float line_marker_fraction; // +0x814
    float spacing_scale;        // +0x818
    float width_scale;          // +0x81c
    float height_scale;         // +0x820
    int font_kind;              // +0x824
};

typedef char FontSheet_must_be_0x828[
    (sizeof(FontSheet) == 0x828) ? 1 : -1];

struct FontQueueEntry {
    unsigned int flags;     // +0x00
    float x0;               // +0x04
    float y0;               // +0x08
    int unknown_0c;         // +0x0c
    float x1;               // +0x10
    float y1;               // +0x14
    int unknown_18;         // +0x18
    float x2;               // +0x1c
    float y2;               // +0x20
    int unknown_24;         // +0x24
    float x3;               // +0x28
    float y3;               // +0x2c
    int unknown_30;         // +0x30
    float text_wave_amplitude; // +0x34
    unsigned char text_wave_enabled; // +0x38
    char pad_39[0x3c - 0x39];
    int font_id;            // +0x3c
    float text_scale;       // +0x40
    char* text;             // +0x44
    int horizontal_align;   // +0x48
    float anchor_x;         // +0x4c
    int texture_id;         // +0x50
    float width;            // +0x54
    float height;           // +0x58
    float u0;               // +0x5c
    float v0;               // +0x60
    float u1;               // +0x64
    float v1;               // +0x68
    Color4f color;          // +0x6c
    int layer;              // +0x7c
    int blend;              // +0x80
};

typedef char FontQueueEntry_must_be_0x84[
    (sizeof(FontQueueEntry) == 0x84) ? 1 : -1];

extern FontSheet g_font_sheets[];        // data_7772f8
extern FontQueueEntry g_font_queue[];    // data_7544e8
extern int g_registered_font_count;       // data_777b20
extern int g_font_queue_count;           // data_777b24
extern char g_font_text_buffer[];         // data_753ce8
extern char* g_font_text_cursor;          // data_7772f0
extern float g_font_wave_phase_a;         // data_7772e8
extern float g_font3d_scales[128];        // data_7770e8

int report_errorf(const char* format, ...);
int font_slot_index_for_char(char value); // @ 0x449d20
float measure_font_text_width(char* text, int font_id, float scale); // @ 0x449e90
int register_font_texture_sheet(char* texture_path, int font_kind,
    float width_scale, float height_scale); // @ 0x449f50
void initialize_font3d_objects(short font_id); // @ 0x44ae10
float sine(float angle); // @ 0x44c9d0
float cosine(float angle); // @ 0x44c980
int draw_textured_quad_immediate(
    TextureRef* texture,
    float x0, float y0,
    float x1, float y1,
    float x2, float y2,
    float x3, float y3,
    float width, float height,
    float u0, float v0,
    float u1, float v1,
    Color4f* color,
    int layer,
    int blend); // @ 0x413030
int draw_font_text_instance(FontQueueEntry* entry); // @ 0x44a360
int draw_queued_font_quad_instance(FontQueueEntry* entry); // @ 0x44a6d0
int queue_axis_aligned_textured_quad(
    int texture_id,
    float x,
    float y,
    float width,
    float height,
    unsigned int flags,
    Color4f* color,
    int layer); // @ 0x44a8b0
void queue_font_text_instance(
    char* text,
    int font_id,
    float text_scale,
    float x,
    float y,
    int horizontal_align,
    float anchor_x,
    unsigned int flags,
    Color4f* color,
    float text_wave_amplitude,
    char text_wave_enabled); // @ 0x44a790
int queue_textured_quad_corners(
    int texture_id,
    float x0, float y0,
    float x1, float y1,
    float x2, float y2,
    float x3, float y3,
    int unused_28,
    int unused_2c,
    unsigned int flags,
    Color4f* color,
    float u0, float v0,
    float u1, float v1,
    int layer,
    int blend); // @ 0x44aac0

#endif
