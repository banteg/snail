// Shared border batch-state view, cross-checked by hide_all_borders and
// unhide_all_borders.
#ifndef BORDER_BATCH_STATE_H
#define BORDER_BATCH_STATE_H

class BorderBatchState {
public:
    int apply_all_border_visibility_mode(int mode);
};

#endif
