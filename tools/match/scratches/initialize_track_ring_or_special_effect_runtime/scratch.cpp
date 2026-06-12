// initialize_track_ring_or_special_effect_runtime @ 0x408570 (thiscall, ret)

extern void* g_track_ring_or_special_effect_vtable; // off_49732c / data_49732c

class RenderableBod {
public:
    void initialize_renderable_bod();

    void* vtable; // +0x00
};

class TrackRingOrSpecialEffectRuntime : public RenderableBod {
public:
    TrackRingOrSpecialEffectRuntime* initialize_track_ring_or_special_effect_runtime();
};

TrackRingOrSpecialEffectRuntime*
TrackRingOrSpecialEffectRuntime::initialize_track_ring_or_special_effect_runtime()
{
    initialize_renderable_bod();
    vtable = &g_track_ring_or_special_effect_vtable;
    return this;
}
