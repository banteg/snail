// Narrow root-view slice for callsites that only need the global gameplay
// pause gate while still using raw game-base offsets for unrelated fields.
#ifndef GAME_PAUSE_VIEW_H
#define GAME_PAUSE_VIEW_H

struct GamePauseView {
    char unknown_000000[0x74621];
    unsigned char pause_gate; // +0x74621
};

#endif
