// Exact cRBorderStack embedded in cRBorderManager. Each visibility transition
// records the current generation and borrows the affected BorderRecord; the
// stack never owns or allocates a widget.
#ifndef BORDER_BATCH_STATE_H
#define BORDER_BATCH_STATE_H

#include "border_fwd.h"

enum {
    BORDER_STACK_ENTRY_CAPACITY = 200,
};

struct BorderStackEntry {
    int generation; // +0x00, transition nesting level
    cRBorder* widget; // +0x04, borrowed cRBorderManager pool entry
};

typedef char BorderStackEntry_must_be_0x08[
    (sizeof(BorderStackEntry) == 0x08) ? 1 : -1];

class cRBorderStack {
public:
    // Windows folds this trivial initializer with FrontendFade::initialize.
    void initialize_border_stack(); // @ 0x404350, iOS cRBorderStack::Init()
    void apply_all_border_visibility_mode(int mode); // @ 0x404360,
        // Android cRBorderStack::Perform(int)

    int generation; // +0x00
    int entry_count; // +0x04
    BorderStackEntry entries[BORDER_STACK_ENTRY_CAPACITY]; // +0x08
    cRBorderManager* owner; // +0x648, owns every borrowed entry
};

typedef cRBorderStack BorderStack;
typedef char BorderStack_must_be_0x64c[
    (sizeof(cRBorderStack) == 0x64c) ? 1 : -1];

#endif
