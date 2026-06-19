#ifndef RECT_H
#define RECT_H

struct Rect {
    int left;   // +0x00
    int top;    // +0x04
    int right;  // +0x08
    int bottom; // +0x0c
};

typedef char Rect_must_be_0x10[(sizeof(Rect) == 0x10) ? 1 : -1];

#endif
