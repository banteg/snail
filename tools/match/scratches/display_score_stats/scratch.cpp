// display_score_stats @ 0x4403c0 (thiscall)
#include "score_stats.h"

int debug_report_stub(char* format, ...); // @ 0x449c00, stripped in release

int RunScoreStats::display_score_stats()
{
    if (total_score != 0) {
        debug_report_stub("\n Score Stats: %i\n", total_score);
        debug_report_stub("Garbage       :%i%%\n", (score_buckets[0] * 100) / total_score);
        debug_report_stub("Slug          :%i%%\n", (score_buckets[1] * 100) / total_score);
        debug_report_stub("Ring          :%i%%\n", (score_buckets[2] * 100) / total_score);
        debug_report_stub("Parcel Collect:%i%%\n", (score_buckets[3] * 100) / total_score);
        debug_report_stub("Parcel Deliver:%i%%\n", (score_buckets[4] * 100) / total_score);
        debug_report_stub("Bonus         :%i%%\n", (score_buckets[5] * 100) / total_score);
        return debug_report_stub("\n");
    }
    return total_score;
}
