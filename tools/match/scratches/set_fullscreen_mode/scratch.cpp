// set_fullscreen_mode @ 0x414260 (cdecl)

class Direct3DRenderer {
public:
    int direct3d_renderer_set_fullscreen_mode(int enabled);
};

extern Direct3DRenderer g_direct3d_renderer; // data_4f7458

int set_fullscreen_mode(int enabled)
{
    return g_direct3d_renderer.direct3d_renderer_set_fullscreen_mode(enabled);
}
