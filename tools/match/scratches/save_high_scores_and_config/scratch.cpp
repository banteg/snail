// save_high_scores_and_config @ 0x417940 (thiscall, ret 0x4)

#include "high_score_bank.h"
#include "runtime_config.h"

const int HIGH_SCORE_SAVE_BUFFER_SIZE = 0x4c4b40;

extern char* allocate_tracked_memory(int size, char* name);
extern void free_tracked_memory(void* memory);
extern char* xor_decode_buffer_with_index(char* bytes, int byte_count);
extern int write_file_bytes(char* file_name, void* bytes, int byte_count);
extern char* save_config_file(char* file_name, void* bytes, int byte_count);

char* HighScoreBank::save_high_scores_and_config(unsigned char save_mask)
{
    char* bytes = allocate_tracked_memory(
        HIGH_SCORE_SAVE_BUFFER_SIZE,
        "High Score Table");

    if ((save_mask & 1) != 0) {
        char* out = bytes;
        int bytes_used = 0;
        SubSolution* record = postal_records;
        int count = HIGH_SCORE_TOP_TEN_STORAGE_COUNT;
        do {
            if (record->active == 1) {
                bytes_used += record->serialize_compact_high_score_record(
                    (SubSolutionHeader*)out);
                out = bytes + bytes_used;
            }
            ++record;
            --count;
        } while (count != 0);
        xor_decode_buffer_with_index(bytes, bytes_used);
        write_file_bytes("ScoreA.dat", bytes, bytes_used);
    }

    if ((save_mask & 2) != 0) {
        char* out = bytes;
        int bytes_used = 0;
        SubSolution* record = survival_records;
        int count = HIGH_SCORE_TOP_TEN_STORAGE_COUNT;
        do {
            if (record->active == 1) {
                bytes_used += record->serialize_compact_high_score_record(
                    (SubSolutionHeader*)out);
                out = bytes + bytes_used;
            }
            ++record;
            --count;
        } while (count != 0);
        xor_decode_buffer_with_index(bytes, bytes_used);
        write_file_bytes("ScoreB.dat", bytes, bytes_used);
    }

    if ((save_mask & 8) != 0) {
        char* out = bytes;
        int bytes_used = 0;
        SubSolution* record = time_trial_route_records;
        int count = HIGH_SCORE_TIME_TRIAL_ROUTE_COUNT;
        do {
            if (record->active == 1) {
                bytes_used += record->serialize_compact_high_score_record(
                    (SubSolutionHeader*)out);
                out = bytes + bytes_used;
            }
            ++record;
            --count;
        } while (count != 0);
        xor_decode_buffer_with_index(bytes, bytes_used);
        write_file_bytes("ScoreC.dat", bytes, bytes_used);
    }

    free_tracked_memory(bytes);
    return save_config_file("SnailMail.cfg", &g_runtime_config, sizeof(g_runtime_config));
}
