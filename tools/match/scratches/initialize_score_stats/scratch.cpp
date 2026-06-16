// initialize_score_stats @ 0x444960 (thiscall, ret)

class ScoreStats {
public:
    int initialize_score_stats();

    int field_00; // +0x00
    int field_04; // +0x04
    int field_08; // +0x08
    int field_0c; // +0x0c
    int field_10; // +0x10
    int field_14; // +0x14
};

int ScoreStats::initialize_score_stats()
{
    field_04 = 0;
    field_08 = 0;
    field_00 = 0;
    field_10 = 0;
    field_14 = 0;
    field_0c = 0;
    return 0;
}
