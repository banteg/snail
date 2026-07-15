#ifndef BN_LOADING_BAR_TYPES_H
#define BN_LOADING_BAR_TYPES_H

typedef int int32_t;

/* Exact 0x0c-byte global cRLoadingBar lifecycle owner. */
typedef struct LoadingBar {
    int32_t active;
    int32_t previous_percent;
    int32_t last_loading_budget;
} LoadingBar;

#endif
