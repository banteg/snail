// construct_game_runtime @ 0x407b60

#include "bod_types.h"
#include "border_manager.h"
#include "game_root.h"
#include "render_camera_slot.h"
#include "runtime_slot.h"
#include "sprite.h"

void* operator new(unsigned int size);

int debug_report_stub(char* format, ...); // @ 0x449c00, stripped in release

extern char* g_game_base; // data_4df904
extern int g_bod_base_init_count; // data_50331c
extern int g_bod_count;           // data_4dfadc
extern int g_loc_mirror_count;    // data_4dfae0

extern void* g_root_runtime_callback_table;     // data_4972d8
extern void* g_tip_manager_callback_table;      // data_4972dc
extern void* g_star_field_callback_table;       // data_4972e0
extern void* g_backdrop_callback_table;         // data_4972e4
extern void* g_border_manager_callback_table;   // data_4972e8
extern void* g_overlay_callback_table;          // data_4972ec
extern void* g_game_input_callback_table;       // data_4972f0
extern void* g_noop_runtime_callback_table;     // data_4972b0

#define REPORT_RUNTIME_SIZE_LEDGER() do { \
    debug_report_stub("Size of cRGame %i\n", 0x12e6ff4); \
    debug_report_stub("Size of cRSubGame %i\n", 0x1272838); \
    debug_report_stub("   Size of cRSegmentCache %i\n", 0xa7f8); \
    debug_report_stub("   Size of cRTutorial\t%i\n", 0x1c); \
    debug_report_stub("   Size of cRSubTracks %i\n", 0x1a5978); \
    debug_report_stub("   Size of cRSubSpeedUp %i\n", 0xb4); \
    debug_report_stub("   Size of cRJetPack %i\n", 0x19c); \
    debug_report_stub("   Size of cRSubHealth %i\n", 0x3a0); \
    debug_report_stub("   Size of cRSlug %i\n", 0x760); \
    debug_report_stub("   Size of cRSubLazerManager %i\n", 0xdc0); \
    debug_report_stub("   Size of cRSaltManager %i\n", 0x17c0); \
    debug_report_stub("   Size of cRSubGarbage %i\n", 0x2648); \
    debug_report_stub("   Size of cRSubRing %i\n", 0x3f0); \
    debug_report_stub("   Size of cRFringeManager %i\n", 0x5fb44); \
    debug_report_stub("   Size of cRSubGoldy %i\n", 0x4364); \
    debug_report_stub("   Size of cRSubLoc %i\n", sizeof(SubLoc) * 3200 * 8); \
    debug_report_stub("   Size of cRSubRow %i\n", sizeof(SubRow) * 3200); \
    debug_report_stub("   Size of cRSubHighScore %i\n", 0x947648); \
    debug_report_stub("   Size of cRSubSolution %i\n", 0x1fac0); \
    debug_report_stub("   Size of cRTimeTrial %i\n", 0x330); \
    debug_report_stub("   Size of cRPathManager %i\n", sizeof(PathManager)); \
    debug_report_stub("   Size of cRPath %i\n", 0x52b0); \
    debug_report_stub("   Size of cRLandscapeManager %i\n", 0x97a4); \
    debug_report_stub("   Size of cRSMTracks %i\n", 0x25cfb4); \
    debug_report_stub("   Size of cRParcelManager %i\n", 0x1b58); \
    debug_report_stub("   Size of cRGUI %i\n", 0x28); \
    debug_report_stub("   Size of cRGalaxy %i\n", 0x10fa8); \
    debug_report_stub("   Size of cREnemyManager %i\n", 0x1804); \
    debug_report_stub("   Size of cRCompletion %i\n", 0x50); \
    debug_report_stub("   Size of cRTimesUp %i\n", 0x10); \
    debug_report_stub("Size of cRSubHighScore %i\n", 0x947648); \
    debug_report_stub("Size of cRBod %i\n", 0x38); \
    debug_report_stub("Size of cRSubLoc %i\n", sizeof(SubLoc)); \
    debug_report_stub("Solutions %i\n", 0x947648); \
} while (0)

#define SLOT(offset) ((RuntimeSlot*)(game + (offset)))
#define COLOR(offset) ((Color4f*)(game + (offset)))

class GameRootAllocation {
public:
    // The promoted GameRoot view contains reverse-engineered helper types with
    // synthetic no-op C++ constructors. Raw storage prevents those helpers
    // from running implicitly before the single recovered root constructor.
    char storage[sizeof(GameRoot)];
    __forceinline GameRootAllocation();
};

__forceinline GameRootAllocation::GameRootAllocation()
{
    char* game = (char*)this;
    {
        COLOR(0x14)->noop_this_constructor();

        GameRoot* root = (GameRoot*)game;
        GameInput* game_input = &root->game_inputs[0];
        int game_input_count = 2;
        do {
            game_input->initialize_bod_base();
            game_input->vtable = &g_game_input_callback_table;
            ++game_input;
            --game_input_count;
        } while (game_input_count);

        GamePlayer* player = &root->players[0];
        int player_count = 2;
        do {
            player->initialize_game_player();
            ++player;
            --player_count;
        } while (player_count);

        root->inactive_bod_sentinel.initialize_bod_base();

        RenderCameraSlot* camera = &root->render_camera_slots[0];
        int camera_count = 5;
        do {
            camera->initialize_render_camera_slot();
            camera = (RenderCameraSlot*)((char*)camera + 0x28);
            --camera_count;
        } while (camera_count);

        Overlay* overlay = &root->overlay_0;
        overlay->initialize_renderable_bod();
        overlay->camera.initialize_noop_renderable_bod();
        overlay->vtable = &g_overlay_callback_table;

        overlay = &root->overlay_1;
        overlay->initialize_renderable_bod();
        overlay->camera.initialize_noop_renderable_bod();
        overlay->vtable = &g_overlay_callback_table;

        overlay = &root->overlay_2;
        overlay->initialize_renderable_bod();
        overlay->camera.initialize_noop_renderable_bod();
        overlay->vtable = &g_overlay_callback_table;

        RuntimeSlot* passive_renderable = SLOT(0xa60);
        passive_renderable->initialize_renderable_bod();
        ((RuntimeSlot*)((char*)passive_renderable + 0x80))->noop_runtime_slot_constructor();
        passive_renderable->vtable = &g_noop_runtime_callback_table;

        BorderManager* border_manager = &root->border_manager;
        border_manager->initialize_bod_base();
        initialize_array_with_constructor(
            (RuntimeSlot*)&border_manager->borders[0],
            0x724,
            0x96,
            &RuntimeSlot::initialize_border_record);
        border_manager->vtable = &g_border_manager_callback_table;

        BodBase* bod = &root->root_bods[0];
        int bod_count = GAME_ROOT_BOD_COUNT;
        do {
            bod->initialize_bod_base();
            ++bod;
            --bod_count;
        } while (bod_count);

        initialize_array_with_constructor(
            (RuntimeSlot*)&root->directx_loader.cached_x_mesh_slots[0],
            sizeof(CachedXMeshSlot),
            DIRECTX_LOADER_CACHED_X_MESH_SLOT_COUNT,
            &RuntimeSlot::initialize_cached_x_mesh_slot);

        Backdrop* backdrop = &root->backdrop;
        backdrop->initialize_bod_base();
        ((Color4f*)((char*)backdrop + 0x67c))->noop_this_constructor();
        ((Color4f*)((char*)backdrop + 0x69c))->noop_this_constructor();
        backdrop->vtable = &g_backdrop_callback_table;

        StarField* star_field = &root->star_field;
        ((BodBase*)star_field)->initialize_bod_base();
        ((BodBase*)star_field)->vtable = &g_star_field_callback_table;

        root->root_bod_4f3c8.initialize_bod_base();

        initialize_array_with_constructor(
            (RuntimeSlot*)&root->intro_screen.renderables[0],
            sizeof(IntroLogoRenderable),
            INTRO_SCREEN_RENDERABLE_COUNT,
            &RuntimeSlot::initialize_intro_logo_renderable);
        initialize_array_with_constructor(
            (RuntimeSlot*)&root->intro_screen.logo_renderables[0],
            sizeof(IntroLogoRenderable),
            INTRO_SCREEN_LOGO_RENDERABLE_COUNT,
            &RuntimeSlot::initialize_intro_logo_renderable);

        root->subgame.initialize_runtime_pools_and_path_template_bank();

        TipManager* tip_manager = &root->tip_manager;
        tip_manager->initialize_bod_base();
        tip_manager->vtable = &g_tip_manager_callback_table;

        SLOT(0)->vtable = &g_root_runtime_callback_table;
    }
}

int construct_game_runtime()
{
    REPORT_RUNTIME_SIZE_LEDGER();

    GameRoot* game = (GameRoot*)new GameRootAllocation;

    g_game_base = (char*)game;
    debug_report_stub("BodCount=%i  Memory=%i\n", g_bod_base_init_count, g_bod_base_init_count * 0x38);
    debug_report_stub("LocCount=%i Memory=%i\n", g_bod_count, g_bod_count * 0x54);
    return debug_report_stub("LocMirrorCount=%i Memory=%i\n", g_loc_mirror_count, g_loc_mirror_count * 0x15c);
}

#undef SLOT
#undef COLOR
