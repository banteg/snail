// initialize_track_jetpack_pickup_runtime @ 0x4084d0 (thiscall, ret)

extern void* g_track_jetpack_pickup_vtable; // off_497318 / data_497318
extern void* g_track_jetpack_body_vtable;   // off_49731c / data_49731c

class BodBase {
public:
    void initialize_bod_base();
};

class RenderableBod : public BodBase {
public:
    void initialize_renderable_bod();

    void* vtable; // +0x00
};

class TrackJetpackPickupRuntime : public BodBase {
public:
    TrackJetpackPickupRuntime* initialize_track_jetpack_pickup_runtime();

    void* vtable; // +0x00
    char unknown_04[0x74 - 0x04];
    RenderableBod body_a; // +0x74
    char unknown_78[0x108 - 0x78];
    RenderableBod body_b; // +0x108
};

TrackJetpackPickupRuntime* TrackJetpackPickupRuntime::initialize_track_jetpack_pickup_runtime()
{
    initialize_bod_base();
    body_a.initialize_renderable_bod();
    body_a.vtable = &g_track_jetpack_body_vtable;
    body_b.initialize_renderable_bod();
    body_b.vtable = &g_track_jetpack_body_vtable;
    vtable = &g_track_jetpack_pickup_vtable;
    return this;
}
