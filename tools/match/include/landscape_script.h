// Parsed landscape/background script record, shared by the landscape manager
// and backdrop renderer.
#ifndef LANDSCAPE_SCRIPT_H
#define LANDSCAPE_SCRIPT_H

#include "sprite.h"

struct LandscapeScriptRecord {
    LandscapeScriptRecord* initialize_landscape_script_record(); // @ 0x408840

    int id; // +0x00, parsed from "ID:"
    char name[0x84 - 0x04]; // +0x04
    int backdrop_texture_id; // +0x84, base sprite texture id from "Picture:"
    unsigned char split_backdrop_texture_pair; // +0x88, single vs _A/_B textures
    char backdrop_texture_path[0x10c - 0x89]; // +0x89
    int object_index; // +0x10c, parsed from "Landscape:" or -1
    Color4f fog_color; // +0x110, RGB parsed from "Fog:"; copied as 16 bytes
    float distort; // +0x120, parsed from "Distort:"
};
typedef char LandscapeScriptRecord_must_be_0x124[
    (sizeof(LandscapeScriptRecord) == 0x124) ? 1 : -1];

struct LandscapeScriptWindow {
    char unknown_000[0x5a4];
    LandscapeScriptRecord record; // +0x5a4
};

#endif
