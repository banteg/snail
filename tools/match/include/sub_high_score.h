// Authored cRSubHighScore owner embedded in SubgameRuntime. Its 8-byte active
// window prefix borrows one of the three owned SubSolution arrays; all 75
// solutions remain value-owned by this 0x947648-byte object.
#ifndef SUB_HIGH_SCORE_H
#define SUB_HIGH_SCORE_H

#include "sub_solution.h"

const int SUB_HIGH_SCORE_TOP_TEN_COUNT = 10;
const int SUB_HIGH_SCORE_TOP_TEN_STORAGE_COUNT =
    SUB_HIGH_SCORE_TOP_TEN_COUNT + 1;
const int SUB_HIGH_SCORE_TIME_TRIAL_ROUTE_COUNT = 51;

class SubHighScore {
public:
    void initialize_high_score_tables(); // @ 0x417540
    void load_high_scores_from_file(char* file_name); // @ 0x4175e0
    void add_arcade_high_score(
        SubSolution* record,
        int level_arg); // @ 0x4176a0, cRSubHighScore::AddArcade
    void add_survival_high_score(
        SubSolution* record); // @ 0x417780, cRSubHighScore::AddSurvival
    void add_time_trial_high_score(
        SubSolution* record,
        int route_index,
        unsigned char route_active); // @ 0x4178b0, cRSubHighScore::AddTimeTrial
    void mini_delete_high_score_entry(int rank); // @ 0x417af0, cRSubHighScore::MiniDelete
    void save_high_scores_and_config(unsigned char save_mask); // @ 0x417940
    void noop_runtime_ai(); // shared empty lifecycle hook @ 0x407b50

    // The add helpers borrow their caller-owned record for the duration of the
    // call. They normalize it in place, then copy the value into this bank's
    // embedded result/ranking storage; none of them retain the input pointer.

    // Borrowed view of whichever embedded record bank the front end exposes.
    // initialize_subgame selects one of the three arrays below; it never
    // allocates or transfers ownership through this pointer.
    SubSolution* active_record_bank; // +0x00
    int active_record_count;             // +0x04
    union {
        struct {
            SubSolution postal_records[SUB_HIGH_SCORE_TOP_TEN_STORAGE_COUNT]; // +0x08
            SubSolution survival_records[SUB_HIGH_SCORE_TOP_TEN_STORAGE_COUNT]; // +0x15c648
            SubSolution time_trial_route_records[SUB_HIGH_SCORE_TIME_TRIAL_ROUTE_COUNT]; // +0x2b8c88
        };
        struct {
            char unknown_before_mini_delete_source[0x17c100];
            // cRSubHighScore::MiniDelete shifts from the row after the
            // canceled rank. This aliases survival_records[1] at +0x17c108;
            // it is a view into the same owned arrays, not separate storage.
            SubSolution mini_delete_source_records[SUB_HIGH_SCORE_TOP_TEN_COUNT];
        };
    };
    SubSolution current_result_record; // +0x9080c8
    SubSolution survival_pending_record; // +0x927b88
};

typedef char SubHighScore_must_be_0x947648[
    (sizeof(SubHighScore) == 0x947648) ? 1 : -1];

#endif
