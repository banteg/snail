// Front-end border manager trailing runtime view for menu justify state.
#ifndef BORDER_RUNTIME_H
#define BORDER_RUNTIME_H

class BorderRuntime {
public:
    int set_border_justify_centre(int justify_centre); // @ 0x404730

    char unknown_00000[0x435b0];
    int justify_centre; // +0x435b0, callers pass raw menu offset bits.
};

typedef char BorderRuntime_must_be_0x435b4[
    (sizeof(BorderRuntime) == 0x435b4) ? 1 : -1];

#endif
