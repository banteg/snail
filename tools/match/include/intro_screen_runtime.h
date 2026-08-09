// Root-owned cRLogo runtime at GameRoot +0x4f400. The two fixed renderable
// banks close exactly on cRSubGame +0x74618.
#ifndef INTRO_SCREEN_RUNTIME_H
#define INTRO_SCREEN_RUNTIME_H

#include "bod_types.h"

enum {
    LOGO_LETTER_CAPACITY = 0x400,
    LOGO_IMAGE_DONOR_CAPACITY = 0x20,
};

class cRLogoLetter : public RenderableBod {
public:
    cRLogoLetter(); // @ 0x408490
    void AI(); // @ 0x419a90

    Vector3 velocity; // +0x80
    unsigned char glyph; // +0x8c, 0xff for image records
    char unknown_08d[0x90 - 0x8d];
};
typedef cRLogoLetter LogoLetter;
typedef cRLogoLetter IntroLogoRenderable;
typedef char cRLogoLetter_must_be_0x90[
    (sizeof(cRLogoLetter) == 0x90) ? 1 : -1];
typedef char LogoLetter_must_be_0x90[
    (sizeof(LogoLetter) == 0x90) ? 1 : -1];

class cRLogo {
public:
    void Open(); // @ 0x419110
    void Init(char* file_name); // @ 0x4191e0
    void AI(); // @ 0x4199e0
    void UnInit(); // @ 0x419920

    float progress;                 // +0x00
    float progress_step;            // +0x04
    int state;                      // +0x08
    int saved_render_flags;         // +0x0c
    float duration_seconds;         // +0x10
    int renderable_count;           // +0x14
    cRLogoLetter letters[LOGO_LETTER_CAPACITY]; // +0x18, text and image crawl entries
    cRLogoLetter image_donors[LOGO_IMAGE_DONOR_CAPACITY]; // +0x24018, sequential preloaded image-object donors
};

typedef cRLogo Logo;
typedef cRLogo IntroScreenRuntime;
typedef char cRLogo_must_be_0x25218[
    (sizeof(cRLogo) == 0x25218) ? 1 : -1];
typedef char Logo_must_be_0x25218[(sizeof(Logo) == 0x25218) ? 1 : -1];

#endif
