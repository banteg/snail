// Shared RShell.o functions, partial. Mobile names in comments.
#ifndef RSHELL_H
#define RSHELL_H

struct ArchiveEntry;

// Game data archive and files.
char initialize_game_data_archive(); // @ 0x430e40
int uninitialize_game_data_archive(); // @ 0x430ef0
int set_current_directory_with_drive_fallback(char* path); // @ 0x430f30
// RShellFindFile: a nonzero force_filesystem skips the archive.
char archive_or_file_exists(char* path, char force_filesystem); // @ 0x430fd0
ArchiveEntry* find_archive_entry(char* path); // @ 0x431250
char* load_file_bytes(char* file_name, int* out_size); // @ 0x431520, RShellLoadFile
int delete_file_path_with_directory_walk(char* path); // @ 0x431540
int write_file_bytes(char* path, void* bytes, int byte_count); // @ 0x431650, RShellSaveFile
void enumerate_matching_archive_or_fs_entries(
    char* directory, char* pattern, int* out_count,
    char (*names)[128]); // @ 0x431740, RShellReadDirectory
void xor_archive_bytes_in_place(int start_offset, char* bytes, int count); // @ 0x431980
char load_archive_index(char* path); // @ 0x4319c0
char is_archive_index_loaded(); // @ 0x431a80
void xor_decode_buffer_with_index(void* buffer, int byte_count); // @ 0x433010, RShellScrambleFile

// iOS RShellMemoryScratch / RShellMemoryScratch2: the two 2 MiB halves of the
// transient shell workspace. Mobile callers cast the result to the view they
// need, so it is untyped here too.
void* get_archive_data_base(); // @ 0x431a90
void* get_archive_data_end(); // @ 0x431aa0

// Read a file from the game data archive, or from disk when no archive is
// loaded. A null buffer allocates one; out_size may be null.
char* load_file_bytes_fixed_size_from_archive_or_fs(
    char* file_name, char* buffer, int byte_count); // @ 0x431030
char* load_file_bytes_from_archive_or_fs(
    char* file_name, char* buffer, int* out_size); // @ 0x4312d0

// Text input.
char read_pressed_text_input_key_code(); // @ 0x432440, RShellInkey
char read_repeating_text_input_key_code(); // @ 0x4327e0

// Fonts, music and sound.
int register_font_texture_sheet_wrapper(
    char* texture_path, int shadow_offset_pixels,
    float width_scale, float height_scale); // @ 0x432d20
void reset_registered_sound_sample_count(); // @ 0x432d40
char cache_music_file(char* path, int unused, char* unused_default_path); // @ 0x432d50, RShellMusicPlay
int play_registered_warning_sample(int sample_id); // @ 0x432dd0
int stop_registered_warning_sample(int sample_handle); // @ 0x432de0
void play_sound_effect_backend(int sample_id, float gain, float pitch, float pan); // @ 0x432df0, RShellSoundPlay
void play_voice_backend(int sample_id, float gain, float pitch, float pan); // @ 0x432e80, RShellVoicePlay
int register_sound_sample(char* path, int normalization_class); // @ 0x432f10, RShellSoundRegister
int find_registered_sound_sample_id_by_name(char* sample_name); // @ 0x432fc0

// The authored 640x480 view (authored_view_state.h).
float get_authored_view_width(); // @ 0x433030
float get_authored_view_height(); // @ 0x433040

#endif
