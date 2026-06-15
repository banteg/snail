// Track runtime cell views, partial.
#ifndef TRACK_RUNTIME_H
#define TRACK_RUNTIME_H

struct TrackRuntimeCell {
    char unknown_00[9];
    unsigned char hidden; // +0x09, nonzero suppresses pickup updates
};

#endif
