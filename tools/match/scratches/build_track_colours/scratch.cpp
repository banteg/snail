// build_track_colours @ 0x435d40 (thiscall, ret)

#include "sprite.h"

extern Color4f g_track_colour_bank_a[51]; // data_74e7e8
extern Color4f g_track_colour_bank_b[51]; // data_6437f8
extern Color4f g_track_colour_bank_c[51]; // data_643b28
extern Color4f g_track_colour_bank_d[51]; // data_53cb30
extern Color4f g_track_colour_bank_e[51]; // data_53ce60
extern Color4f g_track_colour_bank_f[51]; // data_6434c8
extern Color4f g_track_colour_bank_g[51]; // data_6444b8
extern Color4f g_track_colour_bank_h[51]; // data_644188
extern Color4f g_track_colour_bank_i[51]; // data_643e58
extern Color4f g_track_colour_bank_j[51]; // data_53c800
extern Color4f g_track_colour_bank_k[51]; // data_643198

class Game {
public:
    void build_track_colours();
};

void Game::build_track_colours()
{
    for (int offset = 0; offset < 0x330; offset += 0x10) {
        ((Color4f*)((char*)g_track_colour_bank_a + offset))->set_color_white();
        ((Color4f*)((char*)g_track_colour_bank_b + offset))->set_color_white();
        ((Color4f*)((char*)g_track_colour_bank_c + offset))->set_color_white();
        ((Color4f*)((char*)g_track_colour_bank_d + offset))->set_color_white();
        ((Color4f*)((char*)g_track_colour_bank_e + offset))->set_color_white();
        ((Color4f*)((char*)g_track_colour_bank_f + offset))->set_color_white();
        ((Color4f*)((char*)g_track_colour_bank_g + offset))->set_color_white();
        ((Color4f*)((char*)g_track_colour_bank_h + offset))->set_color_white();
        ((Color4f*)((char*)g_track_colour_bank_i + offset))->set_color_white();
        ((Color4f*)((char*)g_track_colour_bank_j + offset))->set_color_white();
        ((Color4f*)((char*)g_track_colour_bank_j + offset))->set_color_white();
        ((Color4f*)((char*)g_track_colour_bank_k + offset))->set_color_white();
        ((Color4f*)((char*)g_track_colour_bank_k + offset))->set_color_white();
    }
}
