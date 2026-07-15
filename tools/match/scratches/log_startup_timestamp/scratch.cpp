// log_startup_timestamp @ 0x406d30 (cdecl)

#include <sys/timeb.h>
#include <time.h>

int debug_report_stub(char* format, ...); // @ 0x449c00, stripped in release

int log_startup_timestamp()
{
    struct _timeb time_buffer;
    char* time_text;

    _ftime(&time_buffer);
    time_text = ctime(&time_buffer.time);
    return debug_report_stub(
        "The time is %.19s.%hu %s = %x\n",
        time_text,
        time_buffer.millitm,
        time_text + 20,
        time_buffer.time);
}
