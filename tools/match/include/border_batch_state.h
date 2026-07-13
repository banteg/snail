// Exact cRBorderStack embedded in BorderManager. Each visibility transition
// records the current generation and borrows the affected BorderRecord; the
// stack never owns or allocates a widget.
#ifndef BORDER_BATCH_STATE_H
#define BORDER_BATCH_STATE_H

class BorderManager;
class FrontendWidget;

enum {
    BORDER_STACK_ENTRY_CAPACITY = 200,
};

struct BorderStackEntry {
    int generation; // +0x00, transition nesting level
    FrontendWidget* widget; // +0x04, borrowed BorderManager pool entry
};

typedef char BorderStackEntry_must_be_0x08[
    (sizeof(BorderStackEntry) == 0x08) ? 1 : -1];

class BorderStack {
public:
    // Windows folds this trivial initializer with FrontendFade::initialize.
    void initialize_border_stack(); // @ 0x404350, iOS cRBorderStack::Init()
    int apply_all_border_visibility_mode(int mode);

    int generation; // +0x00
    int entry_count; // +0x04
    BorderStackEntry entries[BORDER_STACK_ENTRY_CAPACITY]; // +0x08
    BorderManager* owner; // +0x648, owns every borrowed entry
};

typedef char BorderStack_must_be_0x64c[
    (sizeof(BorderStack) == 0x64c) ? 1 : -1];

#endif
