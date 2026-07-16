// construct_game_runtime @ 0x407b60

#include "bod_types.h"
#include "border_manager.h"
#include "game_root.h"
#include "render_camera_slot.h"
#include "runtime_slot.h"
#include "sprite.h"

void* operator new(unsigned int size);

int debug_report_stub(char* format, ...); // @ 0x449c00, stripped in release

extern GameRoot* g_game; // data_4df904
extern int g_sub_loc_count;       // data_4dfadc
extern int g_loc_mirror_count;    // data_4dfae0

extern void* g_root_runtime_callback_table;     // data_4972d8
extern void* g_tip_manager_callback_table;      // data_4972dc
extern void* g_star_field_callback_table;       // data_4972e0
extern void* g_backdrop_callback_table;         // data_4972e4
extern void* g_border_manager_callback_table;   // data_4972e8
extern void* g_overlay_callback_table;          // data_4972ec
extern void* g_game_input_callback_table;       // data_4972f0

#define REPORT_RUNTIME_SIZE_LEDGER() do { \
    debug_report_stub("Size of cRGame %i\n", sizeof(GameRoot)); \
    debug_report_stub("Size of cRSubGame %i\n", sizeof(SubgameRuntime)); \
    debug_report_stub("   Size of cRSegmentCache %i\n", sizeof(SegmentCache)); \
    debug_report_stub("   Size of cRTutorial\t%i\n", sizeof(Tutorial)); \
    debug_report_stub("   Size of cRSubTracks %i\n", sizeof(SubTracks)); \
    debug_report_stub("   Size of cRSubSpeedUp %i\n", sizeof(SubSpeedUp)); \
    debug_report_stub("   Size of cRJetPack %i\n", sizeof(JetPack)); \
    debug_report_stub("   Size of cRSubHealth %i\n", sizeof(((SubgameRuntime*)0)->health_pickups)); \
    debug_report_stub("   Size of cRSlug %i\n", sizeof(((SubgameRuntime*)0)->slug_hazards.slots)); \
    debug_report_stub("   Size of cRSubLazerManager %i\n", sizeof(SubLazerManager)); \
    debug_report_stub("   Size of cRSaltManager %i\n", sizeof(SaltManager)); \
    debug_report_stub("   Size of cRSubGarbage %i\n", sizeof(((SubgameRuntime*)0)->garbage_hazards.slots)); \
    debug_report_stub("   Size of cRSubRing %i\n", sizeof(SubRingPool)); \
    debug_report_stub("   Size of cRFringeManager %i\n", sizeof(FringeManager)); \
    debug_report_stub("   Size of cRSubGoldy %i\n", sizeof(Player)); \
    debug_report_stub("   Size of cRSubLoc %i\n", sizeof(((SubgameRuntime*)0)->runtime_cells)); \
    debug_report_stub("   Size of cRSubRow %i\n", sizeof(((SubgameRuntime*)0)->runtime_rows)); \
    debug_report_stub("   Size of cRSubHighScore %i\n", sizeof(SubHighScore)); \
    debug_report_stub("   Size of cRSubSolution %i\n", sizeof(SubSolution)); \
    debug_report_stub("   Size of cRTimeTrial %i\n", sizeof(TimeTrial)); \
    debug_report_stub("   Size of cRPathManager %i\n", sizeof(PathManager)); \
    debug_report_stub("   Size of cRPath %i\n", sizeof(((SubgameRuntime*)0)->path_pairs)); \
    debug_report_stub("   Size of cRLandscapeManager %i\n", sizeof(LandscapeManager)); \
    debug_report_stub("   Size of cRSMTracks %i\n", sizeof(SMTracks)); \
    debug_report_stub("   Size of cRParcelManager %i\n", sizeof(ParcelManager)); \
    debug_report_stub("   Size of cRGUI %i\n", sizeof(GUI)); \
    debug_report_stub("   Size of cRGalaxy %i\n", sizeof(Galaxy)); \
    debug_report_stub("   Size of cREnemyManager %i\n", sizeof(EnemyManager)); \
    debug_report_stub("   Size of cRCompletion %i\n", sizeof(Completion)); \
    debug_report_stub("   Size of cRTimesUp %i\n", sizeof(TimesUp)); \
    debug_report_stub("Size of cRSubHighScore %i\n", sizeof(SubHighScore)); \
    debug_report_stub("Size of cRBod %i\n", sizeof(BodBase)); \
    debug_report_stub("Size of cRSubLoc %i\n", sizeof(SubLoc)); \
    debug_report_stub("Solutions %i\n", sizeof(SubHighScore)); \
} while (0)

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
    {
        GameRoot* root = (GameRoot*)this;
        root->fog_color.noop_this_constructor();
        GameInput* game_input = &root->game_inputs[0];
        int game_input_count =
            sizeof(root->game_inputs) / sizeof(root->game_inputs[0]);
        do {
            game_input->initialize_bod_base();
            game_input->vtable = &g_game_input_callback_table;
            ++game_input;
            --game_input_count;
        } while (game_input_count);

        GamePlayer* player = &root->players[0];
        int player_count = sizeof(root->players) / sizeof(root->players[0]);
        do {
            player->initialize_game_player();
            ++player;
            --player_count;
        } while (player_count);

        root->inactive_bod_sentinel.initialize_bod_base();

        RenderCameraSlot* camera = &root->render_camera_slots[0];
        int camera_count =
            sizeof(root->render_camera_slots) / sizeof(root->render_camera_slots[0]);
        do {
            camera->initialize_render_camera_slot();
            ++camera;
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

        RenderableBod* passive_renderable = &root->root_noop_renderable;
        passive_renderable->initialize_renderable_bod();
        ((RuntimeSlot*)((char*)passive_renderable + sizeof(RenderableBod)))
            ->noop_runtime_slot_constructor();
        passive_renderable->vtable = &g_noop_runtime_callback_table;

        BorderManager* border_manager = &root->border_manager;
        border_manager->initialize_bod_base();
        initialize_array_with_constructor(
            (RuntimeSlot*)&border_manager->borders[0],
            sizeof(border_manager->borders[0]),
            BORDER_RECORD_COUNT,
            &RuntimeSlot::initialize_border_record);
        border_manager->vtable = &g_border_manager_callback_table;

        BodBase* bod = &root->root_bod_catalog.universe_hole;
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
        backdrop->primary_world_blend.color.noop_this_constructor();
        backdrop->secondary_world_blend.color.noop_this_constructor();
        backdrop->vtable = &g_backdrop_callback_table;

        StarManager* star_manager = &root->star_manager;
        ((BodBase*)star_manager)->initialize_bod_base();
        ((BodBase*)star_manager)->vtable = &g_star_field_callback_table;

        root->root_bod_4f3c8.initialize_bod_base();

        initialize_array_with_constructor(
            (RuntimeSlot*)&root->logo.letters[0],
            sizeof(LogoLetter),
            LOGO_LETTER_CAPACITY,
            &RuntimeSlot::initialize_intro_logo_renderable);
        initialize_array_with_constructor(
            (RuntimeSlot*)&root->logo.image_donors[0],
            sizeof(LogoLetter),
            LOGO_IMAGE_DONOR_CAPACITY,
            &RuntimeSlot::initialize_intro_logo_renderable);

        root->subgame.initialize_runtime_pools_and_path_template_bank();

        TipManager* tip_manager = &root->tip_manager;
        tip_manager->initialize_bod_base();
        tip_manager->vtable = &g_tip_manager_callback_table;

        root->vtable = &g_root_runtime_callback_table;
    }
}

int construct_game_runtime()
{
    REPORT_RUNTIME_SIZE_LEDGER();

    GameRoot* game = (GameRoot*)new GameRootAllocation;

    g_game = game;
    debug_report_stub("BodCount=%i  Memory=%i\n", g_bod_base_init_count, g_bod_base_init_count * 0x38);
    debug_report_stub("LocCount=%i Memory=%i\n", g_sub_loc_count, g_sub_loc_count * sizeof(SubLoc));
    return debug_report_stub("LocMirrorCount=%i Memory=%i\n", g_loc_mirror_count, g_loc_mirror_count * 0x15c);
}
