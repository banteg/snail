// Windows layout of the authored cross-port cRMovie animated-object owner.
// Its Object base owns the 0x30-byte face records; the tail advances across
// their cRTexture payloads.
#ifndef MOVIE_H
#define MOVIE_H

#include "object_render_types.h"

enum MovieFlag {
    MOVIE_COMPLETE = 0x01,
    MOVIE_LOOP = 0x02,
    MOVIE_PING_PONG = 0x04,
    MOVIE_REVERSE = 0x08,
    MOVIE_PAUSED = 0x10,
};

class Movie : public Object {
public:
    void advance_frame_sequence(); // @ 0x430470

    int sequence_flags; // +0xdc
    int current_frame_index; // +0xe0
    float phase; // +0xe4
    float phase_step; // +0xe8
    cRTexture* current_texture_ref; // +0xec
};

typedef char Movie_must_be_0xf0[
    (sizeof(Movie) == 0xf0) ? 1 : -1];

#endif
