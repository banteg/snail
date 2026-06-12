// initialize_track_speedup_runtime @ 0x4084b0 (thiscall, ret)

extern void* g_track_speedup_vtable; // off_497314 / data_497314

class RenderableBod {
public:
    void initialize_renderable_bod();
};

class TrackSpeedupRuntime : public RenderableBod {
public:
    TrackSpeedupRuntime* initialize_track_speedup_runtime();

    void* vtable; // +0x00
};

TrackSpeedupRuntime* TrackSpeedupRuntime::initialize_track_speedup_runtime()
{
    initialize_renderable_bod();
    vtable = &g_track_speedup_vtable;
    return this;
}
