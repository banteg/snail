// initialize_intro_screen @ 0x4191e0 (thiscall, ret 0x4)

#include "backdrop.h"
#include "bod_types.h"
#include "border_manager.h"
#include "font_system.h"
#include "intro_screen_runtime.h"
#include "landscape_manager.h"
#include "mouse_cursor_state.h"
#include "object_render_types.h"
#include "runtime_config.h"
#include "sprite.h"
#include "star_manager.h"
#include "transform_matrix.h"

extern char* g_game_base; // data_4df904
extern TextureRefList g_texture_refs; // data_4b7790
extern char g_blank_text[]; // data_4dfb08

char cache_music_file(char* path, int unused, char* unused_default_path); // @ 0x432d50
char* load_file_bytes(char* file_name, int* out_size);
char* find_case_insensitive_substring(char* needle, char* haystack);
float parse_next_float32(char** cursor);
int sprintf(char* buffer, const char* format, ...);
void free_tracked_memory(void* ptr);
int report_errorf(char* format, ...);

class LogoLetterVirtualView {
public:
    virtual void update_intro_logo_renderable() = 0;
};

static __forceinline void add_intro_renderable_to_active_list(LogoLetter* bod)
{
    char* node = (char*)bod;
    if ((*(unsigned int*)(node + 4) & 0x200) != 0) {
        report_errorf("List ADD");
        return;
    }

    char* head = g_game_base + 0x5ac;
    char* first = *(char**)head;
    if (first == 0) {
        *(LogoLetter**)head = bod;
        *(int*)(node + 8) = 0;
        *(int*)(*(int*)head + 12) = 0;
    } else {
        *(LogoLetter**)(first + 8) = bod;
        *(char**)(*(char**)(*(char**)head + 8) + 12) = *(char**)head;
        first = *(char**)(*(char**)head + 8);
        *(char**)head = first;
        *(int*)(first + 8) = 0;
    }
    *(unsigned int*)(node + 4) |= 0x200;
}

void Logo::initialize_intro_screen(char* file_name)
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
    ((BorderManager*)(g_game_base + 0xb4c))->set_border_justify_centre(0);
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

    float crawl_y = 0.2f;
    this->renderable_count = 0;
    char* cursor =
        find_case_insensitive_substring((char*)"Text Start:", file_bytes);
    cursor = find_case_insensitive_substring((char*)":", cursor) + 1;
    char* text_end = find_case_insensitive_substring((char*)"Text End:", file_bytes);
    LogoLetter* image_donor = image_donors;

    while (cursor < text_end) {
        char* line = cursor;
        float width = 0.0f;
        int count = 0;
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

            add_intro_renderable_to_active_list(&letters[renderable_count]);
            Object* logo_object = image_donor->object;
            letters[renderable_count].set_bod_object(logo_object);
            letters[renderable_count].object->facequads[0].texture_ref =
                g_texture_refs.get_or_create_texture_ref(path, 0, 0);
            set_matrix_identity(&letters[renderable_count].transform);
            letters[renderable_count].transform.position =
                Vector3(0.0f, -4.0f, 0.0f);
            letters[renderable_count].transform.position.z +=
                crawl_y - image_height * 0.5f;
            letters[renderable_count].color.set_color_white();
            letters[renderable_count].color.a = 0.99900001f;
            letters[renderable_count].glyph = 0xff;

            letters[renderable_count].object->vertices[0].x =
                image_width * 0.5f;
            letters[renderable_count].object->vertices[0].z =
                image_height * 0.5f;
            letters[renderable_count].object->vertices[1].x =
                image_width * -0.5f;
            letters[renderable_count].object->vertices[1].z =
                image_height * 0.5f;
            letters[renderable_count].object->vertices[2].x =
                image_width * -0.5f;
            letters[renderable_count].object->vertices[2].z =
                image_height * -0.5f;
            letters[renderable_count].object->vertices[3].x =
                image_width * 0.5f;
            letters[renderable_count].object->vertices[3].z =
                image_height * -0.5f;

            Vector3* velocity = &letters[renderable_count].velocity;
            velocity->z = 0.0f;
            velocity->y = 0.0f;
            velocity->x = 0.0f;
            LogoLetter* renderable = &letters[renderable_count];
            ((LogoLetterVirtualView*)renderable)
                ->update_intro_logo_renderable();

            ++image_donor;
            ++renderable_count;
            crawl_y -= image_height;

            while (*cursor != 0 && *cursor != 13)
                ++cursor;
        } else if (*cursor != 0) {
            while (*cursor != 0 && *cursor != 13) {
                width += g_font3d_scales[font_slot_index_for_char(*cursor)];
                ++count;
                ++cursor;
            }

            if (0 < count) {
                float x = width * 0.5f;
                x *= 0.80000001f;
                Vector3 initial_position(0.0f, -4.0f, 0.0f);
                char* glyph = line;
                while (count != 0) {
                    add_intro_renderable_to_active_list(
                        &letters[renderable_count]);
                    letters[renderable_count].set_bod_object(
                        g_font3d_bods[font_slot_index_for_char(*glyph)].object);
                    set_matrix_identity(
                        &letters[renderable_count].transform);
                    letters[renderable_count].transform.position =
                        initial_position;
                    letters[renderable_count].transform.position.x += x;
                    letters[renderable_count].transform.position.z += crawl_y;
                    letters[renderable_count].color.set_color_white();
                    letters[renderable_count].color.a = 0.99900001f;
                    Vector3* velocity = &letters[renderable_count].velocity;
                    velocity->z = 0.0f;
                    velocity->y = 0.0f;
                    velocity->x = 0.0f;
                    letters[renderable_count].glyph = *glyph;
                    LogoLetter* renderable =
                        &letters[renderable_count];
                    ((LogoLetterVirtualView*)renderable)
                        ->update_intro_logo_renderable();

                    x -= g_font3d_scales[font_slot_index_for_char(*glyph)]
                        * 0.80000001f;
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
    Vector3 velocity(0.0f, 0.0f, step);
    LogoLetter* renderable = letters;
    for (int i = 0; i < renderable_count; ++i, ++renderable) {
        renderable->velocity = velocity;
    }

    free_tracked_memory(file_bytes);
}
