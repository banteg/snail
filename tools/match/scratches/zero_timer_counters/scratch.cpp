// zero_timer_counters @ 0x441b70 (thiscall, ret)

class TimerCounters {
public:
    int zero_timer_counters();

    int fields[6]; // +0x00
};

int TimerCounters::zero_timer_counters()
{
    fields[0] = 0;
    fields[1] = 0;
    fields[2] = 0;
    fields[3] = 0;
    fields[4] = 0;
    fields[5] = 0;
    return 0;
}
