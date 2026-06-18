// find_registered_sound_sample_id_by_name @ 0x432fc0 (cdecl)

extern int g_registered_sound_sample_count; // data_5108b0
extern char g_registered_sound_sample_names[256][0x80]; // data_5088b0

char* find_case_insensitive_substring(char* needle, char* haystack);
int report_errorf(char* format, ...);

int find_registered_sound_sample_id_by_name(char* sample_name)
{
    int sample_id;

    for (sample_id = 0; sample_id < g_registered_sound_sample_count; ++sample_id) {
        char* registered_name = g_registered_sound_sample_names[sample_id];
        if (find_case_insensitive_substring(sample_name, registered_name) != 0)
            return sample_id;
    }

    report_errorf("Cannot Find Sample %s", sample_name);
    return 0;
}
