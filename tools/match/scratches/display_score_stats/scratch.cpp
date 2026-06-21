// display_score_stats @ 0x4403c0 (thiscall)
#include "score_stats.h"

int debug_report_stub(char* format, int value); // @ 0x449c00, stripped in release
typedef int (__cdecl *DebugReportOneArg)(char* format);

int RunScoreStats::display_score_stats()
{
    if (total_score != 0) {
        debug_report_stub("\n Score Stats: %i\n", total_score);
        debug_report_stub("Garbage       :%i%%\n", (score_buckets[SUBGOLDY_SCORE_GARBAGE] * 100) / total_score);
        debug_report_stub("Slug          :%i%%\n", (score_buckets[SUBGOLDY_SCORE_SLUG] * 100) / total_score);
        debug_report_stub("Ring          :%i%%\n", (score_buckets[SUBGOLDY_SCORE_RING] * 100) / total_score);
        debug_report_stub("Parcel Collect:%i%%\n", (score_buckets[SUBGOLDY_SCORE_PARCEL_COLLECT] * 100) / total_score);
        debug_report_stub("Parcel Deliver:%i%%\n", (score_buckets[SUBGOLDY_SCORE_PARCEL_DELIVER] * 100) / total_score);
        debug_report_stub("Bonus         :%i%%\n", (score_buckets[SUBGOLDY_SCORE_BONUS] * 100) / total_score);
        return ((DebugReportOneArg)debug_report_stub)("\n");
    }
    return total_score;
}
