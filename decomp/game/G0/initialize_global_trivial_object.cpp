// initialize_global_trivial_object @ 0x406d20 (compiler-generated initializer)

struct StartupTrivialObject {
    StartupTrivialObject(); // @ 0x44db50
    char unknown_00[0x10];
};
typedef char StartupTrivialObject_must_be_0x10[
    (sizeof(StartupTrivialObject) == 0x10) ? 1 : -1];

StartupTrivialObject g_startup_trivial_object; // 0x4df848
