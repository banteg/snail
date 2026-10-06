// initialize_global_trivial_object @ 0x406d20 (cdecl)

struct StartupTrivialObject {
    StartupTrivialObject* noop_this_constructor(); // @ 0x44db50
    char unknown_00[0x10];
};
typedef char StartupTrivialObject_must_be_0x10[
    (sizeof(StartupTrivialObject) == 0x10) ? 1 : -1];

extern StartupTrivialObject g_startup_trivial_object; // data_4df848

void initialize_global_trivial_object()
{
    g_startup_trivial_object.noop_this_constructor();
}
