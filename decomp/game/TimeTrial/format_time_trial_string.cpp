// cRTimeTrial::TimeString / format_time_trial_string @ 0x448960 (ret 0x4)

typedef struct TimeTrialTimeCView {
    float total_seconds;        // +0x00
    int minutes;                // +0x04
    int seconds;                // +0x08, seconds within the current minute
    int display_hundredths;     // +0x0c
    int display_thousandths;    // +0x10
    float second_fraction;      // +0x14
} TimeTrialTimeCView;

int sprintf(char* buffer, char* format, ...);

extern char g_time_trial_string[]; // 0x751478

char* __stdcall format_time_trial_string(TimeTrialTimeCView* timer)
{
    if (timer->total_seconds == 0.0f) {
        sprintf(g_time_trial_string, "-:--:--");
    } else {
        sprintf(
            g_time_trial_string,
            "%1i:%02i:%03i",
            timer->minutes,
            timer->seconds,
            timer->display_thousandths);
        sprintf(
            g_time_trial_string,
            "%1i:%02i:%02i",
            timer->minutes,
            timer->seconds,
            timer->display_hundredths);
    }

    return g_time_trial_string;
}
