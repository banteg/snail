#ifndef ACTIVE_BOD_H
#define ACTIVE_BOD_H

class ActiveBod {
public:
    virtual void update_active_bod(); // vtable slot 0, default @ 0x433e80

    unsigned int list_flags; // +0x04
    ActiveBod* list_prev;    // +0x08
    ActiveBod* list_next;    // +0x0c
    char unknown_10[0x38 - 0x10];
    float world_z;           // +0x38
};

typedef char ActiveBod_must_be_0x3c[
    (sizeof(ActiveBod) == 0x3c) ? 1 : -1];

#endif
