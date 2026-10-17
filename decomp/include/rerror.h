#ifndef RERROR_H
#define RERROR_H

// RShell.h's message reporters (mobile RShellError, RShellWarning and
// RShellPrintText), with C++ linkage.
int report_errorf(char* format, ...); // @ 0x431cc0
int report_warningf(char* format, ...); // @ 0x431d10
int report_messagef(char* format, ...); // @ 0x431d60

#endif
