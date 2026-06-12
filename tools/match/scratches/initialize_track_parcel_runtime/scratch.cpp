// initialize_track_parcel_runtime @ 0x408860 (thiscall, ret)

extern void* g_track_parcel_vtable; // off_497364 / data_497364

class BodBase {
public:
    void initialize_bod_base();

    void* vtable; // +0x00
};

class TrackParcelRuntime : public BodBase {
public:
    TrackParcelRuntime* initialize_track_parcel_runtime();
};

TrackParcelRuntime* TrackParcelRuntime::initialize_track_parcel_runtime()
{
    initialize_bod_base();
    vtable = &g_track_parcel_vtable;
    return this;
}
