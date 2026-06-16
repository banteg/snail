// Track pickup visibility views, partial.
#ifndef TRACK_RUNTIME_H
#define TRACK_RUNTIME_H

// This is not the full 0x54-byte TrackRowCell grid record. It is the small
// visibility gate view reached by TrackHealthPickup::visibility_cell.
struct TrackVisibilityCell {
    char unknown_00[9];
    unsigned char hidden; // +0x09, nonzero suppresses pickup updates
};

#endif
