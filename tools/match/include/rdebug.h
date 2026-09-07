#ifndef RDEBUG_H
#define RDEBUG_H

// Shared C ABI: report_errorf is compiled as C in the recovered native profile.
#ifdef __cplusplus
extern "C" {
#endif
int report_errorf(char* format, ...);
int debug_report_stub(char* format, ...);
#ifdef __cplusplus
}
#endif

#endif
