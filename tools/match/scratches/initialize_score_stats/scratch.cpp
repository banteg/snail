// initialize_score_stats @ 0x444960 (thiscall, ret)

class ScoreStats {
public:
    int initialize_score_stats();
};

int ScoreStats::initialize_score_stats()
{
    *(int*)((char*)this + 0x04) = 0;
    *(int*)((char*)this + 0x08) = 0;
    *(int*)((char*)this + 0x00) = 0;
    *(int*)((char*)this + 0x10) = 0;
    *(int*)((char*)this + 0x14) = 0;
    *(int*)((char*)this + 0x0c) = 0;
    return 0;
}
