#ifndef RERROR_H
#define RERROR_H

// The recovered error formatter uses C linkage in its canonical /TC profile.
#ifdef __cplusplus
extern "C" {
#endif
int report_errorf(char* format, ...);
#ifdef __cplusplus
}
#endif

#endif
