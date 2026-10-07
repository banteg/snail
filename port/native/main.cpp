// Native Snail Mail: snail-web.wasm translated by wasm2c, run in an SDL3
// window. Usage: snail-native [--mute] [--warmup N] [--frames N --screenshot FILE] [data directory]
// The data directory holds SnailMail.dat (default: the current directory);
// saves land beside it, as with the original. --frames runs N fixed 1/60 s
// frames without input in a hidden window, then saves the last one as a PNG.

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdlib.h>
#include <string.h>

#include "host.h"

namespace {

const int kWidth = 640, kHeight = 480;

// SDL scancode -> DirectInput scan code (DIK_*).
int dik(SDL_Scancode scancode)
{
    if (scancode >= SDL_SCANCODE_A && scancode <= SDL_SCANCODE_Z) {
        static const unsigned char letters[26] = {0x1e, 0x30, 0x2e, 0x20, 0x12, 0x21, 0x22, 0x23, 0x17, 0x24, 0x25,
            0x26, 0x32, 0x31, 0x18, 0x19, 0x10, 0x13, 0x1f, 0x14, 0x16, 0x2f, 0x11, 0x2d, 0x15, 0x2c};
        return letters[scancode - SDL_SCANCODE_A];
    }
    if (scancode >= SDL_SCANCODE_1 && scancode <= SDL_SCANCODE_0)
        return 0x02 + (scancode - SDL_SCANCODE_1);
    if (scancode >= SDL_SCANCODE_F1 && scancode <= SDL_SCANCODE_F10)
        return 0x3b + (scancode - SDL_SCANCODE_F1);
    switch (scancode) {
    case SDL_SCANCODE_ESCAPE: return 0x01;
    case SDL_SCANCODE_MINUS: return 0x0c;
    case SDL_SCANCODE_EQUALS: return 0x0d;
    case SDL_SCANCODE_BACKSPACE: return 0x0e;
    case SDL_SCANCODE_TAB: return 0x0f;
    case SDL_SCANCODE_LEFTBRACKET: return 0x1a;
    case SDL_SCANCODE_RIGHTBRACKET: return 0x1b;
    case SDL_SCANCODE_RETURN: return 0x1c;
    case SDL_SCANCODE_LCTRL: return 0x1d;
    case SDL_SCANCODE_SEMICOLON: return 0x27;
    case SDL_SCANCODE_APOSTROPHE: return 0x28;
    case SDL_SCANCODE_GRAVE: return 0x29;
    case SDL_SCANCODE_LSHIFT: return 0x2a;
    case SDL_SCANCODE_BACKSLASH: return 0x2b;
    case SDL_SCANCODE_COMMA: return 0x33;
    case SDL_SCANCODE_PERIOD: return 0x34;
    case SDL_SCANCODE_SLASH: return 0x35;
    case SDL_SCANCODE_RSHIFT: return 0x36;
    case SDL_SCANCODE_LALT: return 0x38;
    case SDL_SCANCODE_SPACE: return 0x39;
    case SDL_SCANCODE_CAPSLOCK: return 0x3a;
    case SDL_SCANCODE_F11: return 0x57;
    case SDL_SCANCODE_F12: return 0x58;
    case SDL_SCANCODE_KP_ENTER: return 0x9c;
    case SDL_SCANCODE_RCTRL: return 0x9d;
    case SDL_SCANCODE_RALT: return 0xb8;
    case SDL_SCANCODE_HOME: return 0xc7;
    case SDL_SCANCODE_UP: return 0xc8;
    case SDL_SCANCODE_PAGEUP: return 0xc9;
    case SDL_SCANCODE_LEFT: return 0xcb;
    case SDL_SCANCODE_RIGHT: return 0xcd;
    case SDL_SCANCODE_END: return 0xcf;
    case SDL_SCANCODE_DOWN: return 0xd0;
    case SDL_SCANCODE_PAGEDOWN: return 0xd1;
    case SDL_SCANCODE_INSERT: return 0xd2;
    case SDL_SCANCODE_DELETE: return 0xd3;
    default: return -1;
    }
}

// Window coordinates -> the 640x480 frame, letterboxed as gpu.cpp draws it.
void pointer(w2c_game* game, SDL_Window* window, float x, float y)
{
    int width, height;
    SDL_GetWindowSize(window, &width, &height);
    float scale = SDL_min((float)width / kWidth, (float)height / kHeight);
    float left = (width - kWidth * scale) / 2, top = (height - kHeight * scale) / 2;
    int px = (int)SDL_floorf((x - left) / scale), py = (int)SDL_floorf((y - top) / scale);
    w2c_game_snail_pointer(game, (uint32_t)SDL_clamp(px, 0, kWidth - 1), (uint32_t)SDL_clamp(py, 0, kHeight - 1));
}

}  // namespace

int main(int argc, char** argv)
{
    bool muted = false;
    int warmup = -1;
    const char* root = ".";
    int frames = 0;
    const char* screenshot = nullptr;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--mute") == 0)
            muted = true;
        else if (strcmp(argv[i], "--warmup") == 0 && i + 1 < argc)
            warmup = atoi(argv[++i]);
        else if (strcmp(argv[i], "--frames") == 0 && i + 1 < argc)
            frames = atoi(argv[++i]);
        else if (strcmp(argv[i], "--screenshot") == 0 && i + 1 < argc)
            screenshot = argv[++i];
        else if (argv[i][0] != '-')
            root = argv[i];
        else {
            SDL_Log("usage: snail-native [--mute] [--warmup N] [--frames N --screenshot FILE] [data directory]");
            return 2;
        }
    }

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_Log("snail: %s", SDL_GetError());
        return 1;
    }
    SDL_WindowFlags flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY | (frames ? SDL_WINDOW_HIDDEN : 0);
    SDL_Window* window = SDL_CreateWindow("Snail Mail", kWidth * 2, kHeight * 2, flags);
    if (!window) {
        SDL_Log("snail: %s", SDL_GetError());
        return 1;
    }
    SDL_HideCursor();  // the game draws its own

    static w2c_game game;
    static w2c_snail host;
    static w2c_wasi__snapshot__preview1 wasi;
    host.game = &game;
    host.gpu = gpu_create(window);
    host.mixer = mixer_create(muted);
    wasi.game = &game;
    wasi.state = wasi_create(root);
    if (!host.gpu)
        return 1;

    wasm_rt_init();
    wasm2c_game_instantiate(&game, &host, &wasi);
    w2c_game_0x5Finitialize(&game);
    // The original drew timeGetTime() % 1000 random numbers before construction.
    if (!w2c_game_snail_start(&game, (uint32_t)(warmup >= 0 ? warmup : SDL_GetTicks() % 1000))) {
        SDL_Log("snail: startup failed; is SnailMail.dat in %s?", root);
        return 1;
    }

    if (frames) {
        for (int frame = 0; frame < frames; ++frame) {
            if (w2c_game_snail_frame(&game, 1.0f / 60.0f) != 0)
                break;
            if (gpu_frame_pending(host.gpu))
                gpu_end_frame(host.gpu, false);
        }
        bool saved = !screenshot || gpu_save_frame(host.gpu, screenshot);
        if (!saved)
            SDL_Log("snail: %s: %s", screenshot, SDL_GetError());
        SDL_Quit();
        return saved ? 0 : 1;
    }

    Uint64 last = SDL_GetTicksNS();
    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_EVENT_QUIT:
                running = false;
                break;
            case SDL_EVENT_KEY_DOWN:
            case SDL_EVENT_KEY_UP:
                if (int code = dik(event.key.scancode); code >= 0 && !event.key.repeat)
                    w2c_game_snail_key(&game, (uint32_t)code, event.type == SDL_EVENT_KEY_DOWN);
                break;
            case SDL_EVENT_MOUSE_MOTION:
                pointer(&game, window, event.motion.x, event.motion.y);
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
            case SDL_EVENT_MOUSE_BUTTON_UP:
                pointer(&game, window, event.button.x, event.button.y);
                if (event.button.button == SDL_BUTTON_LEFT || event.button.button == SDL_BUTTON_RIGHT)
                    w2c_game_snail_button(&game, event.button.button == SDL_BUTTON_LEFT ? 0 : 1,
                        event.type == SDL_EVENT_MOUSE_BUTTON_DOWN);
                break;
            case SDL_EVENT_MOUSE_WHEEL:
                if (event.wheel.y != 0)
                    w2c_game_snail_wheel(&game, event.wheel.y > 0 ? 1u : (uint32_t)-1);
                break;
            case SDL_EVENT_WINDOW_FOCUS_LOST:
                // Keys held while the window loses focus would otherwise stay down.
                for (int code = 0; code < 256; ++code)
                    w2c_game_snail_key(&game, (uint32_t)code, 0);
                break;
            default:
                break;
            }
        }
        Uint64 now = SDL_GetTicksNS();
        float elapsed = SDL_min((float)(now - last) / 1e9f, 1.0f);
        last = now;
        if (w2c_game_snail_frame(&game, elapsed) != 0)
            running = false;
        if (gpu_frame_pending(host.gpu))
            gpu_end_frame(host.gpu, true);
        else
            SDL_Delay(1);
    }

    // The game saved its score tables on the way out.
    w2c_game_snail_save(&game);
    SDL_Quit();
    return 0;
}
