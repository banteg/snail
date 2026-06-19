// initialize_intro_screen @ 0x4191e0 (thiscall, ret 0x4)

#include "backdrop.h"
#include "bod_types.h"
#include "font_system.h"
#include "landscape_script_bank.h"
#include "mouse_cursor_state.h"
#include "sprite.h"
#include "star_field.h"
#include "transform_matrix.h"

extern char* g_game_base; // data_4df904
extern unsigned int g_render_flags; // data_4df934
extern TextureRefList g_texture_refs; // data_4b7790
extern float g_font_glyph_widths[]; // data_7770e8
extern void* g_font3d_glyph_objects[]; // data_77550c

char cache_music_file(char* path, int unused, char* unused_default_path); // @ 0x432d50
char* load_file_bytes(char* file_name, int* out_size);
char* find_case_insensitive_substring(char* needle, char* haystack);
float parse_next_float32(char** cursor);
int sprintf(char* buffer, const char* format, ...);
int free_tracked_memory(void* ptr);
int report_errorf(char* format, ...);

class IntroRenderable {
public:
    int set_bod_object(void* object);

    char unknown_000[0x38];
    TransformMatrix transform; // +0x38
    char unknown_078[0x90 - 0x78];
};

class IntroScreen {
public:
    int initialize_intro_screen(char* file_name);
};

class IntroBorderManager {
public:
    int set_border_justify_centre(int justify_centre);
};

static void add_intro_renderable_to_active_list(IntroRenderable* bod)
{
    char* node = (char*)bod;
    if ((*(unsigned int*)(node + 4) & 0x200) != 0) {
        report_errorf("List ADD");
        return;
    }

    char* head = g_game_base + 0x5ac;
    char* first = *(char**)head;
    if (first != 0) {
        *(IntroRenderable**)(first + 8) = bod;
        *(char**)(*(char**)(*(char**)head + 8) + 12) = *(char**)head;
        first = *(char**)(*(char**)head + 8);
        *(char**)head = first;
        *(int*)(first + 8) = 0;
    } else {
        *(IntroRenderable**)head = bod;
        *(int*)(node + 8) = 0;
        *(int*)(*(int*)head + 12) = 0;
    }
    *(unsigned int*)(node + 4) |= 0x200;
}

static void initialize_intro_slot(IntroScreen* owner, int slot, void* object, float x, float z, char glyph)
{
    char* self = (char*)owner;
    IntroRenderable* renderable = (IntroRenderable*)(self + 0x18 + slot * 0x90);
    add_intro_renderable_to_active_list(renderable);
    renderable->set_bod_object(object);
    set_matrix_identity(&renderable->transform);
    *(float*)((char*)renderable + 0x80) = x;
    *(float*)((char*)renderable + 0x84) = -4.0f;
    *(float*)((char*)renderable + 0x88) = z;
    ((Color4f*)((char*)renderable + 0x40))->set_color_white();
    *(float*)((char*)renderable + 0x4c) = 0.99900001f;
    *(char*)((char*)renderable + 0x8c) = glyph;
}

int IntroScreen::initialize_intro_screen(char* file_name)
{
    char* self = (char*)this;
    int renderable_count = 0;

    cache_music_file((char*)"music/introtext.ogg", 0, (char*)"");
    int script_index =
        ((LandscapeScriptBank*)(g_game_base + 0x106c218))
            ->load_landscape_script_by_name((char*)"SpaceRed.txt");
    ((Backdrop*)(g_game_base + 0x4ec10))
        ->change_backdrop(
            (LandscapeScriptRecord*)(g_game_base + 0x106c7bc +
                script_index * sizeof(LandscapeScriptRecord)),
            0);
    ((IntroBorderManager*)(g_game_base + 0xb4c))->set_border_justify_centre(0);
    ((StarField*)(g_game_base + 0x4f33c))->unhide_star_field();

    char* file_bytes = load_file_bytes(file_name, 0);
    *(unsigned int*)(self + 0x0c) = g_render_flags;

    TransformMatrix matrix;
    *(TransformMatrix*)(g_game_base + 0x15c) =
        *matrix.initialize_matrix_from_values(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.63439298f, 0.77301002f, 0.0f,
            0.0f, -0.77301002f, 0.63439298f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);
    *(float*)(g_game_base + 0x284) = 100.0f;
    *(int*)(self + 0x00) = 0;
    *(float*)(self + 0x04) = 0.0016638901f;
    ((MouseCursorState*)(g_game_base + 0x290))->release_mouse_cursor();
    *(int*)(self + 0x08) = 0;
    *(int*)(self + 0x14) = 0;

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
            while (*cursor != '.' && *cursor != 0)
                *out++ = *cursor++;
            *out++ = '.';
            *out++ = 't';
            *out++ = 'g';
            *out++ = 'a';
            *out = 0;
            if (*cursor == '.')
                ++cursor;

            float image_width = parse_next_float32(&cursor);
            float image_height = parse_next_float32(&cursor);
            sprintf(path, "Intro/%s", image_name);

            initialize_intro_slot(
                this,
                renderable_count,
                *(void**)(self + 0x2403c + renderable_count * 4),
                0.0f,
                crawl_y - image_height * 0.5f,
                (char)0xff);

            IntroRenderable* renderable =
                (IntroRenderable*)(self + 0x18 + renderable_count * 0x90);
            TextureRef* texture = g_texture_refs.get_or_create_texture_ref(path, 0, 0);
            *(TextureRef**)(*(int*)(*(int*)((char*)renderable + 0x3c) + 0x5c) + 0x0c) = texture;
            float* verts = *(float**)(*(int*)((char*)renderable + 0x3c) + 0x38);
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

            if (count > 0) {
                float x = width * 0.5f * 0.80000001f;
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
    *(float*)(self + 0x10) = duration;
    *(int*)(self + 0x14) = renderable_count;

    float step = (1.0f / (duration * 60.0f)) * (3.0f - crawl_y);
    for (int i = 0; i < renderable_count; ++i) {
        IntroRenderable* renderable = (IntroRenderable*)(self + 0x18 + i * 0x90);
        *(float*)((char*)renderable + 0x98) = 0.0f;
        *(float*)((char*)renderable + 0x9c) = 0.0f;
        *(float*)((char*)renderable + 0xa0) = step;
    }

    return free_tracked_memory(file_bytes);
}
