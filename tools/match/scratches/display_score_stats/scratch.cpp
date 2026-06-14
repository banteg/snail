// display_score_stats @ 0x4403c0 (thiscall)

int debug_report_stub(char* format, ...); // @ 0x449c00, stripped in release

class ScoreStats {
public:
    int display_score_stats();

    char unknown_000[0x2e4];
    int total_score;       // +0x2e4
    char unknown_2e8[0x28];
    int garbage_score;     // +0x310
    int slug_score;        // +0x314
    int ring_score;        // +0x318
    int parcel_collected;  // +0x31c
    int parcel_delivered;  // +0x320
    int bonus_score;       // +0x324
};

int ScoreStats::display_score_stats()
{
    if (total_score != 0) {
        debug_report_stub("\n Score Stats: %i\n", total_score);
        debug_report_stub("Garbage       :%i%%\n", (garbage_score * 100) / total_score);
        debug_report_stub("Slug          :%i%%\n", (slug_score * 100) / total_score);
        debug_report_stub("Ring          :%i%%\n", (ring_score * 100) / total_score);
        debug_report_stub("Parcel Collect:%i%%\n", (parcel_collected * 100) / total_score);
        debug_report_stub("Parcel Deliver:%i%%\n", (parcel_delivered * 100) / total_score);
        debug_report_stub("Bonus         :%i%%\n", (bonus_score * 100) / total_score);
        return debug_report_stub("\n");
    }
    return total_score;
}
