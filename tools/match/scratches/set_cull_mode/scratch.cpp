// set_cull_mode @ 0x4129f0 (cdecl)

class Direct3DRenderer {
public:
    int direct3d_renderer_set_cull_mode(char cull_front);
};

extern Direct3DRenderer g_direct3d_renderer; // data_4f7458

int set_cull_mode(int cull_front)
{
    return g_direct3d_renderer.direct3d_renderer_set_cull_mode((char)cull_front);
}
