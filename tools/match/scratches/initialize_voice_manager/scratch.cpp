// initialize_voice_manager @ 0x448ee0 (thiscall, ret)

#include "audio_system.h"
#include "voice_manager.h"

#include <string.h>

char* get_archive_data_base();
char* load_file_bytes_from_archive_or_fs(char* path, char* out_buffer, int* out_size);
char* find_case_insensitive_substring(char* needle, char* haystack);
char* advance_to_next_crlf_line(char* cursor);
int parse_next_signed_int(char** cursor);
float parse_next_float32(char** cursor);
void rstrcpy_checked_ascii(char* destination, char* source);
int register_sound_sample(char* path, int normalization_class);
int report_errorf(char* format, ...);

extern char g_tutorial_text[]; // 0x4a38e4

void VoiceManager::initialize_voice_manager()
{
    char set_tag[256];
    char voice_path[256];

    int zero = 0;
    set_tag[0] = (char)zero;

    char* file_text = get_archive_data_base();
    load_file_bytes_from_archive_or_fs("Voice/_Voice.txt", file_text, (int*)zero);

    for (int set_index = zero; set_index < 16; ++set_index) {
        rstrcpy_checked_ascii(set_tag, "Set:");

        char* set_name;
        switch (set_index) {
        case 0:
            set_name = "Damage";
            break;
        case 1:
            set_name = "Dying";
            break;
        case 2:
            set_name = "Enemies";
            break;
        case 3:
            set_name = "Fall";
            break;
        case 4:
            set_name = "Misc";
            break;
        case 5:
            set_name = "PowerUp";
            break;
        case 6:
            set_name = "Slow";
            break;
        case 7:
            set_name = "Start";
            break;
        case 8:
            set_name = "Victory";
            break;
        case 9:
            set_name = "Ouch";
            break;
        case 10:
            set_name = "Package";
            break;
        case 11:
            set_name = "Slugged";
            break;
        case 12:
            set_name = "WormTunnel";
            break;
        case 13:
            set_name = g_tutorial_text;
            break;
        case 14:
            set_name = "Postal";
            break;
        default:
            set_name = "SuperTramp";
            break;
        }
        strcat(set_tag, set_name);

        char* cursor = find_case_insensitive_substring(set_tag, file_text);
        if (cursor == 0) {
            report_errorf("Cannot find %s in _Voice.txt", set_tag);
            return;
        }

        char* open_brace = find_case_insensitive_substring("{", cursor);
        char* close_brace = find_case_insensitive_substring("}", open_brace);
        cursor = advance_to_next_crlf_line(open_brace);

        int entry_count = 0;
        char* count_cursor = cursor;
        while (count_cursor < close_brace) {
            ++entry_count;
            count_cursor = advance_to_next_crlf_line(count_cursor);
        }

        VoiceSet* set = &sets[set_index];
        set->initialize_voice_set(entry_count);

        int entry_index = 0;
        while (entry_index < entry_count) {
            while (*cursor == '\t' || *cursor == ' ') {
                ++cursor;
            }

            rstrcpy_checked_ascii(voice_path, "Voice/");

            char* path_cursor = voice_path + 6;
            while (*cursor != '.') {
                *path_cursor++ = *cursor++;
            }
            *path_cursor++ = '.';
            *path_cursor++ = 'o';
            *path_cursor++ = 'g';
            *path_cursor++ = 'g';
            *path_cursor = 0;

            cursor = advance_to_next_crlf_line(cursor);
            set->bites[entry_index] = register_sound_sample(voice_path, 1);
            ++entry_index;
        }

    }

    char* cursor = find_case_insensitive_substring("NormalizeMusic:", file_text);
    cursor = find_case_insensitive_substring(":", cursor);
    float music_scale = (float)parse_next_signed_int(&cursor) * 0.0099999998f;

    cursor = find_case_insensitive_substring("NormalizeSfx:", file_text);
    cursor = find_case_insensitive_substring(":", cursor);
    float sfx_scale = (float)parse_next_signed_int(&cursor) * 0.0099999998f;

    cursor = find_case_insensitive_substring("NormalizeVoice:", file_text);
    cursor = find_case_insensitive_substring(":", cursor);
    float voice_scale = (float)parse_next_signed_int(&cursor) * 0.0099999998f;

    g_audio_backend.set_audio_normalization_scales(
        music_scale,
        sfx_scale,
        voice_scale);

    cursor = find_case_insensitive_substring("Frequency:", file_text);
    cursor = find_case_insensitive_substring(":", cursor);
    global_frequency_seconds = parse_next_float32(&cursor);

    reset_voice_manager();
}
