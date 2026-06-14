// add_time_trial_high_score @ 0x4178b0 (thiscall, ret 0xc)

struct TimeTrialRecord {
    int active;                  // +0x00
    int score;                   // +0x04
    float total_seconds;         // +0x08
    char unknown_0c[0x3c - 0x0c];
    int mode_tag;                // +0x3c
    int route_index;             // +0x40
    int replay_cursor;           // +0x44
    char payload[0x1fac0 - 0x48];
};

class HighScoreBank {
public:
    void add_time_trial_high_score(
        TimeTrialRecord* record,
        int route_index,
        unsigned char route_active);

    char unknown_000000[0x2b8c88];
    TimeTrialRecord route_records[51]; // +0x2b8c88
    TimeTrialRecord scratch_record;    // +0x9080c8
};

void HighScoreBank::add_time_trial_high_score(
    TimeTrialRecord* record,
    int route_index,
    unsigned char route_active)
{
    record->mode_tag = 2;
    record->route_index = route_index;
    record->replay_cursor = 0;
    if (!route_active) {
        record->total_seconds = 0.0f;
    }

    scratch_record = *record;

    if (route_active) {
        TimeTrialRecord* route_record = &route_records[route_index];
        if (record->total_seconds < route_record->total_seconds
            || route_record->total_seconds == 0.0f) {
            *route_record = *record;
            route_record->route_index = route_index;
        }
    }
}
