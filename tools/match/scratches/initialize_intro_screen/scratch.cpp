// initialize_intro_screen @ 0x4191e0 (thiscall, ret 0x4)

#include "backdrop.h"
#include "bod_types.h"
#include "border_runtime.h"
#include "font_system.h"
#include "intro_screen_runtime.h"
#include "landscape_manager.h"
#include "mouse_cursor_state.h"
#include "runtime_config.h"
#include "sprite.h"
#include "star_manager.h"
#include "transform_matrix.h"

extern char* g_game_base; // data_4df904
extern TextureRefList g_texture_refs; // data_4b7790
extern float g_font_glyph_widths[]; // data_7770e8
extern void* g_font3d_glyph_objects[]; // data_77550c
extern char g_blank_text[]; // data_4dfb08

char cache_music_file(char* path, int unused, char* unused_default_path); // @ 0x432d50
char* load_file_bytes(char* file_name, int* out_size);
char* find_case_insensitive_substring(char* needle, char* haystack);
float parse_next_float32(char** cursor);
int sprintf(char* buffer, const char* format, ...);
int free_tracked_memory(void* ptr);
int report_errorf(char* format, ...);

class IntroLogoRenderableVirtualView {
public:
    virtual void update_intro_logo_renderable() = 0;
};

static __forceinline void add_intro_renderable_to_active_list(IntroLogoRenderable* bod)
{
    char* node = (char*)bod;
    if ((*(unsigned int*)(node + 4) & 0x200) != 0) {
        report_errorf("List ADD");
        return;
    }

    char* head = g_game_base + 0x5ac;
    char* first = *(char**)head;
    if (first != 0) {
        *(IntroLogoRenderable**)(first + 8) = bod;
        *(char**)(*(char**)(*(char**)head + 8) + 12) = *(char**)head;
        first = *(char**)(*(char**)head + 8);
        *(char**)head = first;
        *(int*)(first + 8) = 0;
    } else {
        *(IntroLogoRenderable**)head = bod;
        *(int*)(node + 8) = 0;
        *(int*)(*(int*)head + 12) = 0;
    }
    *(unsigned int*)(node + 4) |= 0x200;
}

static __forceinline void initialize_intro_slot(
    IntroScreenRuntime* owner,
    int slot,
    void* object,
    float x,
    float z,
    char glyph)
{
    IntroLogoRenderable* renderable = &owner->renderables[slot];
    add_intro_renderable_to_active_list(renderable);
    renderable->set_bod_object(object);
    set_matrix_identity(&renderable->transform);
    renderable->transform.position.x = 0.0f;
    renderable->transform.position.y = -4.0f;
    renderable->transform.position.z = 0.0f;
    renderable->transform.position.x += x;
    renderable->transform.position.z += z;
    renderable->color.set_color_white();
    renderable->color.a = 0.99900001f;
    renderable->velocity.x = 0.0f;
    renderable->velocity.y = 0.0f;
    renderable->velocity.z = 0.0f;
    renderable->glyph = glyph;
    ((IntroLogoRenderableVirtualView*)renderable)->update_intro_logo_renderable();
}

int IntroScreenRuntime::initialize_intro_screen(char* file_name)
{
    cache_music_file((char*)"music/introtext.ogg", 0, g_blank_text);
    int script_index =
        ((LandscapeManager*)(g_game_base + 0x106c218))
            ->load_landscape_script_by_name((char*)"SpaceRed.txt");
    ((Backdrop*)(g_game_base + 0x4ec10))
        ->change_backdrop(
            &((LandscapeManager*)(g_game_base + 0x106c218))
                ->scripts[script_index],
            0);
    ((BorderRuntime*)(g_game_base + 0xb4c))->set_border_justify_centre(0);
    ((StarManager*)(g_game_base + 0x4f33c))->unhide_star_field();

    char* file_bytes = load_file_bytes(file_name, 0);
    saved_render_flags = g_runtime_config.render_flags;

    TransformMatrix matrix;
    *(TransformMatrix*)(g_game_base + 0x15c) =
        *matrix.initialize_matrix_from_values(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.63439298f, 0.77301002f, 0.0f,
            0.0f, -0.77301002f, 0.63439298f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);
    *(float*)(g_game_base + 0x284) = 100.0f;
    progress = 0.0f;
    progress_step = 1.0f / 600.0f;
    ((MouseCursorState*)(g_game_base + 0x290))->release_mouse_cursor();
    state = 0;
    this->renderable_count = 0;

    float crawl_y = 0.2f;
    char* text_start = find_case_insensitive_substring((char*)"Text Start:", file_bytes);
    char* cursor = find_case_insensitive_substring((char*)":", text_start) + 1;
    char* text_end = find_case_insensitive_substring((char*)"Text End:", file_bytes);

    while (cursor < text_end) {
        char* line = cursor;
        if (*cursor == '*') {
            char image_name[128];
            char path[128];
            char* out = image_name;
            ++cursor;
            while (*cursor != '.')
                *out++ = *cursor++;
            *out++ = '.';
            *out++ = 't';
            *out++ = 'g';
            *out++ = 'a';
            *out = 0;
            ++cursor;

            float image_width = parse_next_float32(&cursor);
            float image_height = parse_next_float32(&cursor);
            sprintf(path, "Intro/%s", image_name);

            initialize_intro_slot(
                this,
                renderable_count,
                logo_renderables[renderable_count].object,
                0.0f,
                crawl_y - image_height * 0.5f,
                (char)0xff);

            IntroLogoRenderable* renderable = &renderables[renderable_count];
            TextureRef* texture = g_texture_refs.get_or_create_texture_ref(path, 0, 0);
            char* render_object = (char*)renderable->object;
            *(TextureRef**)(*(int*)(render_object + 0x5c) + 0x0c) = texture;
            float* verts = *(float**)(render_object + 0x38);
            if (verts != 0) {
                float half_w = image_width * 0.5f;
                float half_h = image_height * 0.5f;
                verts[0] = half_w;
                verts[2] = half_h;
                verts[3] = -half_w;
                verts[5] = half_h;
                verts[8] = -half_w;
                verts[9] = -half_h;
                verts[11] = half_w;
            }
            ++renderable_count;
            crawl_y -= image_height;

            while (*cursor != 0 && *cursor != 13)
                ++cursor;
        } else if (*cursor != 0) {
            float width = 0.0f;
            int count = 0;
            while (*cursor != 0 && *cursor != 13) {
                width += g_font_glyph_widths[font_slot_index_for_char(*cursor)];
                ++count;
                ++cursor;
            }

            if (0 < count) {
                float x = width * 0.5f;
                x *= 0.80000001f;
                char* glyph = line;
                while (count != 0) {
                    int slot = font_slot_index_for_char(*glyph);
                    initialize_intro_slot(
                        this,
                        renderable_count,
                        g_font3d_glyph_objects[slot * 14],
                        x,
                        crawl_y,
                        *glyph);
                    x -= g_font_glyph_widths[slot] * 0.80000001f;
                    ++glyph;
                    ++renderable_count;
                    --count;
                }
            }
        }

        if (*cursor == 13) {
            cursor += 2;
            crawl_y -= 1.0f;
        }
    }

    cursor = find_case_insensitive_substring((char*)"Duration:", file_bytes);
    cursor = find_case_insensitive_substring((char*)":", cursor);
    float duration = parse_next_float32(&cursor);
    duration_seconds = duration;

    float step = (1.0f / (duration * 60.0f)) * (3.0f - crawl_y);
    for (int i = 0; i < renderable_count; ++i) {
        IntroLogoRenderable* renderable = &renderables[i];
        renderable->velocity.x = 0.0f;
        renderable->velocity.y = 0.0f;
        renderable->velocity.z = step;
    }

    return free_tracked_memory(file_bytes);
}
