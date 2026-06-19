#ifndef BLINK_RANDOM_TABLE_H
#define BLINK_RANDOM_TABLE_H

class BlinkRandomTable {
public:
    double advance_blink_random(); // @ 0x4408a0
    int initialize_blink_random(); // @ 0x4408c0

    char unknown_000000[0x3bb700];
    int index;         // +0x3bb700
    float samples[24]; // +0x3bb704
};

typedef char BlinkRandomTable_must_be_0x3bb764[
    (sizeof(BlinkRandomTable) == 0x3bb764) ? 1 : -1];

#endif
