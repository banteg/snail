// initialize_game_assets_and_world @ 0x40acf0 (thiscall)

#include <string.h>
#include <stddef.h>

#include "backdrop.h"
#include "bod_types.h"
#include "cameraman.h"
#include "cheat_state.h"
#include "directx_loader.h"
#include "game_root.h"
#include "galaxy_route_types.h"
#include "landscape_manager.h"
#include "object_render_types.h"
#include "rstring.h"
#include "runtime_config.h"
#include "segment_catalog_types.h"
#include "sound_effect_manager.h"
#include "sprite.h"
#include "thanks_screen.h"
#include "transform_matrix.h"
#include "voice_manager.h"

extern char g_directx_loader_scratch[]; // 0x74eb18, cleared before DirectX loader init
extern char g_help_script_path[]; // 0x4a3488
extern char g_menu_background_script_path[]; // 0x4a347c
extern SubSegmentRaw* g_builtin_segment_definitions[]; // 0x4a63d0

int report_errorf(char* format, ...); // @ 0x431cc0
int debug_report_stub(char* format, ...); // @ 0x449c00
void initialize_font_wave_state(); // @ 0x449c70
void initialize_font3d_objects(short font_id); // @ 0x44ae10
void register_font_texture_sheet_wrapper(
    char* font_path,
    int shadow_offset_pixels,
    float width_scale,
    float height_scale); // @ 0x432d20
void initialize_backdrop_slice_quad(Object* object, char* texture_path, float x_offset); // @ 0x41a1c0, ObjectProcTileFloorFast
void initialize_textured_backdrop_quad(Object* object, char* texture_path, float x_offset); // @ 0x41a0b0, ObjectProcTileFast
void raise_backdrop_quad_edge_pair(int edge_pair, Object* object); // @ 0x41a170, ObjectProcTileFastRamp
void initialize_backdrop_corner_quad(int corner, Object* object, char* texture_path); // @ 0x41a290, ObjectProcTileFloorCornerFast
void initialize_backdrop_tile_quad(
    Object* object,
    int edge_selector,
    int orientation,
    int row_selector,
    int column_selector,
    char* texture_path); // @ 0x41a4d0, ObjectProcFringe
void set_object_color(Object* object, tColour color); // @ 0x4141d0
void set_input_controller_pointer_authored_xy(
    int controller,
    float authored_x,
    float authored_y); // @ 0x4323a0
static __forceinline void link_root_bod(BodBase* bod)
{
    char* node = (char*)bod;
    unsigned int* flags = (unsigned int*)(node + 4);
    if ((*flags & BOD_FLAG_LINKED) != 0) {
        report_errorf((char*)"List ADD");
        return;
    }

    char* head = (char*)&g_game->active_bod_list.first;
    char* first = *(char**)head;
    if (first != 0) {
        *(char**)(first + 8) = node;
        *(char**)(*(char**)(*(char**)head + 8) + 12) = *(char**)head;
        first = *(char**)(*(char**)head + 8);
        *(char**)head = first;
        *(int*)(first + 8) = 0;
    } else {
        *(char**)head = node;
        *(int*)(node + 8) = 0;
        *(int*)(*(char**)head + 12) = 0;
    }
    *flags |= BOD_FLAG_LINKED;
}

static __forceinline void initialize_overlay_slot(cROverlay* overlay)
{
    link_root_bod(overlay);
    overlay->Init();
}

char cRGame::initialize_game_assets_and_world()
{
    char* game = (char*)this;
    tColour asset_color;
    asset_color.noop_this_constructor();

    fog_color.store_color4f(1.0f, 1.0f, 1.0f, 1.0f);
    fog_density = 1.0f;
    fog_start = 30.0f;
    fog_end = 50.0f;
    fog_enabled = 1;
    player_count = GAME_ROOT_PLAYER_SLOT_COUNT;
    fade.Init();
    frontend_link_latch = 0;
    subgame.subgame_pause_gate = 0;

    g_cheat_state.Init();
    intro.hide_for_replay_latch = 0;
    subgame.BlinkRandInit();
    subgame.SetRate(1.1f);
    render_skip_count = 2;
    fixed_update_count = 1;

    g_texture_refs.Init(500);
    g_object_list.Init(3000);
    unknown_000514 = 0;
    fixed_update_accumulator = 0.0f;
    frame_counter = 0;
    inactive_bod_sentinel.list_next = 0;
    active_bod_list.free_top = &inactive_bod_sentinel;
    active_bod_list.first = 0;
    unknown_000b48 = 0;
    memset(g_sprite_depth_buckets, 0, sizeof(g_sprite_depth_buckets));

    viewports[0].sort_key = 0;
    viewports[0].flags = RENDER_SCENE_OVERLAY_0 | 3;
    viewports[0].camera = &overlay_0.camera;
    viewports[0].viewport_x = 0.0f;
    viewports[0].viewport_y = 0.0f;
    viewports[0].viewport_width = 1.0f;
    viewports[0].viewport_height = 1.0f;
    viewports[2].draw_world = 0;
    initialize_overlay_slot(&overlay_0);

    memset(g_directx_loader_scratch, 0, 0x15c);
    DirectXLoader* loader = &directx_loader;
    loader->initialize_directx_loader();
    cRLandscapeManager* landscape = &subgame.landscape_manager;
    landscape->Open();
    cRSMTracks* sm_tracks = &subgame.sm_tracks;
    sm_tracks->Import();
    landscape->Import((char*)"Starmap.txt");
    landscape->Import((char*)"Splash.txt");
    landscape->Import(g_help_script_path);

    subgame.level_mode_arg = g_runtime_config.landscape_backdrop_variant_selector;
    ((SubgameOwnerLink*)&subgame.gui)->bind_subgame_owner();
    ((SubgameOwnerLink*)&subgame.splash)->bind_subgame_owner();
    subgame.galaxy.Open();
    subgame.player.cameraman.initialize_cameraman();
    logo.Open();
    g_sound_effect_manager.Init(g_sound_bank_entries);
    g_voice_manager.Init();
    options.apply_audio_config_volumes();
    sm_tracks->OpenLevels();
    g_game->subgame.landscape_manager
        .Import(g_menu_background_script_path);
    subgame.level_definition_scratch.load_builtin_segment_definitions(
        g_builtin_segment_definitions);

    viewports[1].sort_key = 1;
    viewports[1].flags = RENDER_SCENE_PLAYER_0 | 1;
    viewports[1].SetCamera(&players[0].camera);
    players[0].camera.render_mask = RENDER_SCENE_PLAYER_0;

    viewports[4].sort_key = 1;
    viewports[4].flags = RENDER_SCENE_PLAYER_1 | 3;
    viewports[4].SetCamera(&players[1].camera);
    players[1].camera.render_mask = RENDER_SCENE_PLAYER_1;

    viewports[3].sort_key = 3;
    viewports[3].flags = RENDER_SCENE_OVERLAY_2 | 3;
    viewports[3].camera = &overlay_2.camera;
    viewports[3].viewport_x = 0.0f;
    viewports[3].viewport_y = 0.0f;
    viewports[3].viewport_width = 1.0f;
    viewports[3].viewport_height = 1.0f;
    initialize_overlay_slot(&overlay_2);

    viewports[2].sort_key = 2;
    viewports[2].flags = RENDER_SCENE_OVERLAY_1 | 3;
    viewports[2].camera = &overlay_1.camera;
    viewports[2].viewport_x = 0.0f;
    viewports[2].viewport_y = 0.0f;
    viewports[2].viewport_width = 1.0f;
    viewports[2].viewport_height = 1.0f;
    initialize_overlay_slot(&overlay_1);

    register_font_texture_sheet_wrapper((char*)"Objects/Font/Font-menu-hover.tga", 2, 0.75f, 1.0f);
    initialize_font3d_objects(0);
    initialize_font_wave_state();
    g_sprite_manager.Init();
    g_sprite_manager.Load((char*)"Sprites/Debug.tga", 1, 0);
    g_sprite_manager.Load((char*)"Sprites/Overlay.tga", 2, 0);
    g_sprite_manager.Load((char*)"Sprites/Border.tga", 5, 0x400);
    g_sprite_manager.Load((char*)"Sprites/Mouse.tga", 22, 0x400);
    g_sprite_manager.Load((char*)"Sprites/Warning.tga", 94, 0x400);
    g_sprite_manager.Load((char*)"Sprites/Play.tga", 27, 0x400);
    g_sprite_manager.Load((char*)"Sprites/StarTail.tga", 32, 0x400);
    g_sprite_manager.Load((char*)"Sprites/Jet.tga", 33, 0x400);
    g_sprite_manager.Load((char*)"Sprites/Health.tga", 57, 0x400);
    g_sprite_manager.Load((char*)"Sprites/DamageGuage.tga", 89, 0x400);
    g_sprite_manager.Load((char*)"Sprites/DamageGuageFull.tga", 90, 0x400);
    g_sprite_manager.Load((char*)"Sprites/DamageGuageBright.tga", 91, 0x400);
    g_sprite_manager.Load((char*)"Sprites/Spark.tga", 92, 0x400);
    g_sprite_manager.Load((char*)"Sprites/Black.tga", 93, 0x400);
    g_sprite_manager.Load((char*)"Sprites/BorderGlow.tga", 99, 0x400);
    g_sprite_manager.Load((char*)"Sprites/Slug000.tga", 118, 0x400);
    g_sprite_manager.Load((char*)"Sprites/Slug001.tga", 119, 0x400);
    g_sprite_manager.Load((char*)"Sprites/SlugMask.tga", 120, 0x400);
    g_sprite_manager.Load((char*)"Sprites/Parcel000.tga", 121, 0x400);
    g_sprite_manager.Load((char*)"Sprites/ParcelIcon.tga", 122, 0x400);
    g_sprite_manager.Load((char*)"Sprites/GarbageA.tga", 114, 0x400);
    g_sprite_manager.Load((char*)"Sprites/GarbageB.tga", 115, 0x400);
    g_sprite_manager.Load((char*)"Sprites/GarbageC.tga", 116, 0x400);
    g_sprite_manager.Load((char*)"Sprites/GarbageD.tga", 117, 0x400);
    g_sprite_manager.Load((char*)"Sprites/Life.tga", 123, 0x400);
    g_sprite_manager.Load((char*)"Sprites/JetPack000.tga", 124, 0x400);
    g_sprite_manager.Load((char*)"Sprites/Smoke.tga", 128, 0x400);
    g_sprite_manager.Load((char*)"Sprites/SlugGoo.tga", 129, 0x400);
    g_sprite_manager.Load((char*)"Sprites/SliderBar.tga", 36, 0x400);
    g_sprite_manager.Load((char*)"Sprites/SliderBarFull.tga", 37, 0x400);
    g_sprite_manager.Load((char*)"Sprites/Less.tga", 38, 0x400);
    g_sprite_manager.Load((char*)"Sprites/LessHover.tga", 40, 0x400);
    g_sprite_manager.Load((char*)"Sprites/LessMask.tga", 41, 0x420);
    g_sprite_manager.Load((char*)"Sprites/More.tga", 42, 0x400);
    g_sprite_manager.Load((char*)"Sprites/MoreHover.tga", 44, 0x400);
    g_sprite_manager.Load((char*)"Sprites/MoreMask.tga", 45, 0x420);
    g_sprite_manager.Load((char*)"Sprites/ParticleBlasters.tga", 130, 0x400);
    g_sprite_manager.Load((char*)"Sprites/ParticleExplode-big.tga", 131, 0x400);
    g_sprite_manager.Load((char*)"Sprites/ParticleExplode-small.tga", 132, 0x400);
    g_sprite_manager.Load((char*)"Sprites/ParticleSlow-big.tga", 133, 0x400);
    g_sprite_manager.Load((char*)"Sprites/ParticleSlow-small.tga", 134, 0x400);
    g_sprite_manager.Load((char*)"Sprites/ParticleRing-big.tga", 135, 0x400);
    g_sprite_manager.Load((char*)"Sprites/ParticleRing-small.tga", 136, 0x400);
    g_sprite_manager.Load((char*)"Sprites/Collision.tga", 137, 0x400);
    g_sprite_manager.Load((char*)"Galaxy/SpaceMapLogo.tga", 138, 0x400);
    g_sprite_manager.Load((char*)"Galaxy/Galaxy000.tga", 139, 0x400);
    g_sprite_manager.Load((char*)"Galaxy/Galaxy001.tga", 140, 0x400);
    g_sprite_manager.Load((char*)"Galaxy/Galaxy002.tga", 141, 0x400);
    g_sprite_manager.Load((char*)"Galaxy/Galaxy003.tga", 142, 0x400);
    g_sprite_manager.Load((char*)"Galaxy/Galaxy004.tga", 143, 0x400);
    g_sprite_manager.Load((char*)"Galaxy/Galaxy005.tga", 144, 0x400);
    g_sprite_manager.Load((char*)"Galaxy/Galaxy006.tga", 145, 0x400);
    g_sprite_manager.Load((char*)"Galaxy/Galaxy007.tga", 146, 0x400);
    g_sprite_manager.Load((char*)"Galaxy/Galaxy008.tga", 147, 0x400);
    g_sprite_manager.Load((char*)"Galaxy/Galaxy009.tga", 148, 0x400);
    g_sprite_manager.Load((char*)"Galaxy/GalaxySelect.tga", 149, 0x400);
    g_sprite_manager.Load((char*)"Galaxy/LevelSelect.tga", 150, 0x400);
    g_sprite_manager.Load((char*)"Galaxy/LevelStar.tga", 151, 0x400);
    g_sprite_manager.Load((char*)"Galaxy/BorderSpacemap.tga", 152, 0x400);
    g_sprite_manager.Load((char*)"Galaxy/Line.tga", 153, 0x400);
    g_sprite_manager.Load((char*)"Galaxy/LineStar.tga", 154, 0x400);
    g_sprite_manager.Load((char*)"Sprites/Progress-Bar.tga", 155, 0x400);
    g_sprite_manager.Load((char*)"Sprites/Progress-Bar-lit.tga", 156, 0x400);
    g_sprite_manager.Load((char*)"Sprites/Progress-Cursor.tga", 157, 0x400);
    g_sprite_manager.Load((char*)"Sprites/JetPackThrust.tga", 158, 0x400);
    g_sprite_manager.Load((char*)"Sprites/Ghost.tga", 159, 0x400);

    float slice_index = 0.0f;
    do {
        int storage_index = (int)slice_index;
        BodBase* floor_slice = &root_bod_catalog.floor_slices.storage[storage_index];
        floor_slice->SetObject(g_object_list.Add());
        initialize_backdrop_slice_quad(
            floor_slice->object, (char*)"Objects/World00/Track0.tga", slice_index);

        BodBase* warning_slice = &root_bod_catalog.warning_slices.storage[storage_index];
        warning_slice->SetObject(g_object_list.Add());
        initialize_backdrop_slice_quad(
            warning_slice->object, (char*)"Objects/World00/TrackWarn.tga", slice_index);

        BodBase* slide_slice = &root_bod_catalog.slide_slices.storage[storage_index];
        slide_slice->SetObject(g_object_list.Add());
        initialize_backdrop_slice_quad(
            slide_slice->object, (char*)"Objects/World00/Slide0.tga", slice_index);
        slice_index += 1.0f;
    } while (slice_index < 8.0f);

    TransformMatrix transform;
    set_matrix_identity(&transform);

    BodBase* pillar = &root_bod_catalog.pillars[0];
    pillar->SetObject(g_object_list.Add());
    loader->load_x_mesh((char*)"pillar1.x", pillar->object, 1);
    transform.position.x = 0.0f;
    pillar->ApplyPos(&transform);

    pillar = &root_bod_catalog.pillars[1];
    pillar->SetObject(g_object_list.Add());
    loader->load_x_mesh((char*)"pillar2.x", pillar->object, 1);
    transform.position.x = 0.5f;
    pillar->ApplyPos(&transform);

    pillar = &root_bod_catalog.pillars[2];
    pillar->SetObject(g_object_list.Add());
    loader->load_x_mesh((char*)"pillar3.x", pillar->object, 1);
    transform.position.x = 1.0f;
    pillar->ApplyPos(&transform);

    pillar = &root_bod_catalog.pillars[3];
    pillar->SetObject(g_object_list.Add());
    loader->load_x_mesh((char*)"pillar4.x", pillar->object, 1);
    transform.position.x = 1.5f;
    pillar->ApplyPos(&transform);

    pillar = &root_bod_catalog.pillars[4];
    pillar->SetObject(g_object_list.Add());
    loader->load_x_mesh((char*)"pillar5.x", pillar->object, 1);
    transform.position.x = 2.0f;
    pillar->ApplyPos(&transform);

    pillar = &root_bod_catalog.pillars[5];
    pillar->SetObject(g_object_list.Add());
    loader->load_x_mesh((char*)"pillar6.x", pillar->object, 1);
    transform.position.x = 2.5f;
    pillar->ApplyPos(&transform);

    pillar = &root_bod_catalog.pillars[6];
    pillar->SetObject(g_object_list.Add());
    loader->load_x_mesh((char*)"pillar7.x", pillar->object, 1);
    transform.position.x = 3.0f;
    pillar->ApplyPos(&transform);

    pillar = &root_bod_catalog.pillars[7];
    pillar->SetObject(g_object_list.Add());
    loader->load_x_mesh((char*)"pillar8.x", pillar->object, 1);
    transform.position.x = 3.5f;
    pillar->ApplyPos(&transform);

    BodBase* ramp_edge = &root_bod_catalog.ramp_edges[0];
    ramp_edge->SetObject(g_object_list.Add());
    initialize_textured_backdrop_quad(
        ramp_edge->object, (char*)"Objects/Universe/Ramp.tga", 0.0f);
    raise_backdrop_quad_edge_pair(-1, ramp_edge->object);

    ramp_edge = &root_bod_catalog.ramp_edges[1];
    ramp_edge->SetObject(g_object_list.Add());
    initialize_textured_backdrop_quad(
        ramp_edge->object, (char*)"Objects/Universe/Ramp.tga", 0.0f);
    raise_backdrop_quad_edge_pair(0, ramp_edge->object);

    ramp_edge = &root_bod_catalog.ramp_edges[2];
    ramp_edge->SetObject(g_object_list.Add());
    initialize_textured_backdrop_quad(
        ramp_edge->object, (char*)"Objects/Universe/Ramp.tga", 0.0f);
    raise_backdrop_quad_edge_pair(1, ramp_edge->object);

    BodBase* corner = &root_bod_catalog.floor_corners.storage[TRACK_CORNER_0_STORAGE_INDEX];
    corner->SetObject(g_object_list.Add());
    initialize_backdrop_corner_quad(
        0, corner->object, (char*)"Objects/World00/Track0.tga");
    corner = &root_bod_catalog.floor_corners.storage[TRACK_CORNER_1_STORAGE_INDEX];
    corner->SetObject(g_object_list.Add());
    initialize_backdrop_corner_quad(
        1, corner->object, (char*)"Objects/World00/Track0.tga");
    corner = &root_bod_catalog.floor_corners.storage[TRACK_CORNER_2_STORAGE_INDEX];
    corner->SetObject(g_object_list.Add());
    initialize_backdrop_corner_quad(
        2, corner->object, (char*)"Objects/World00/Track0.tga");
    corner = &root_bod_catalog.floor_corners.storage[TRACK_CORNER_3_STORAGE_INDEX];
    corner->SetObject(g_object_list.Add());
    initialize_backdrop_corner_quad(
        3, corner->object, (char*)"Objects/World00/Track0.tga");

    corner = &root_bod_catalog.warning_corners.storage[TRACK_CORNER_0_STORAGE_INDEX];
    corner->SetObject(g_object_list.Add());
    initialize_backdrop_corner_quad(
        0, corner->object, (char*)"Objects/World00/TrackWarn.tga");
    corner = &root_bod_catalog.warning_corners.storage[TRACK_CORNER_1_STORAGE_INDEX];
    corner->SetObject(g_object_list.Add());
    initialize_backdrop_corner_quad(
        1, corner->object, (char*)"Objects/World00/TrackWarn.tga");
    corner = &root_bod_catalog.warning_corners.storage[TRACK_CORNER_2_STORAGE_INDEX];
    corner->SetObject(g_object_list.Add());
    initialize_backdrop_corner_quad(
        2, corner->object, (char*)"Objects/World00/TrackWarn.tga");
    corner = &root_bod_catalog.warning_corners.storage[TRACK_CORNER_3_STORAGE_INDEX];
    corner->SetObject(g_object_list.Add());
    initialize_backdrop_corner_quad(
        3, corner->object, (char*)"Objects/World00/TrackWarn.tga");

    corner = &root_bod_catalog.slide_corners.storage[TRACK_CORNER_0_STORAGE_INDEX];
    corner->SetObject(g_object_list.Add());
    initialize_backdrop_corner_quad(
        0, corner->object, (char*)"Objects/World00/Slide0.tga");
    corner = &root_bod_catalog.slide_corners.storage[TRACK_CORNER_1_STORAGE_INDEX];
    corner->SetObject(g_object_list.Add());
    initialize_backdrop_corner_quad(
        1, corner->object, (char*)"Objects/World00/Slide0.tga");
    corner = &root_bod_catalog.slide_corners.storage[TRACK_CORNER_2_STORAGE_INDEX];
    corner->SetObject(g_object_list.Add());
    initialize_backdrop_corner_quad(
        2, corner->object, (char*)"Objects/World00/Slide0.tga");
    corner = &root_bod_catalog.slide_corners.storage[TRACK_CORNER_3_STORAGE_INDEX];
    corner->SetObject(g_object_list.Add());
    initialize_backdrop_corner_quad(
        3, corner->object, (char*)"Objects/World00/Slide0.tga");

    BodBase* trampoline = &root_bod_catalog.trampoline;
    trampoline->SetObject(g_object_list.Add());
    loader->load_x_mesh((char*)"Tramp.x", trampoline->object, 1);
    trampoline->object->blend_mode = 6;
    trampoline->object->facequads[0].texture_ref->flags |= TEXTURE_REF_REGISTERED;

    BodBase* universe_hole = &root_bod_catalog.universe_hole;
    universe_hole->SetObject(g_object_list.Add());
    initialize_textured_backdrop_quad(
        universe_hole->object, (char*)"Objects/Universe/Hole.tga", 0.0f);
    universe_hole->object->blend_mode = 5;
    universe_hole->object->facequads[0].texture_ref->flags |= 4;

    BodBase* lazer = &root_bod_catalog.lazer_model;
    lazer->SetObject(g_object_list.Add());
    load_object_definition((char*)"Objects/Lazer", lazer->object);

    enum {
        BOD_OBJECT_OFFSET = offsetof(BodBase, object),
        SUB_LAZER_OWNER_FROM_OBJECT =
            offsetof(cRSubLazer, owner_game) - offsetof(BodBase, object),
        SUB_LAZER_SLOT_COUNT =
            sizeof(((cRSubLazerManager*)0)->slots)
            / sizeof(((cRSubLazerManager*)0)->slots[0]),
        BANNER_POOL_FROM_ROOT =
            offsetof(GameRoot, subgame) + offsetof(cRSubGame, banners),
        BANNER_SLOT_COUNT =
            sizeof(((BannerPool*)0)->slots) / sizeof(((BannerPool*)0)->slots[0])
    };
    Object** sub_lazer_object = &subgame.sub_lazers.slots[0].object;
    int sub_lazer_count = SUB_LAZER_SLOT_COUNT;
    do {
        ((BodBase*)((char*)sub_lazer_object - BOD_OBJECT_OFFSET))
            ->SetObject(lazer->object);
        (*sub_lazer_object)->facequads[0].texture_ref->flags |= TEXTURE_REF_REGISTERED;
        *(cRSubGame**)(
            (char*)sub_lazer_object + SUB_LAZER_OWNER_FROM_OBJECT) = &subgame;
        ((tColour*)(sub_lazer_object + 1))
            ->store_color4f(1.0f, 1.0f, 1.0f, 0.7f);
        (*sub_lazer_object)->blend_mode = 9;
        sub_lazer_object = (Object**)((char*)sub_lazer_object + sizeof(cRSubLazer));
        --sub_lazer_count;
    } while (sub_lazer_count != 0);

    BodBase* salt_model = &root_bod_catalog.salt_model;
    salt_model->SetObject(g_object_list.Add());
    loader->load_x_mesh((char*)"salt.x", salt_model->object, 1);

    cRSubGame** salt_owner = &subgame.salt_hazards.slots[0].owner_game;
    int salt_count = 40;
    do {
        cRSalt* salt = (cRSalt*)((char*)salt_owner - 0x88);
        salt->SetObject(salt_model->object);
        *salt_owner = &subgame;
        salt->color.store_color4f(1.0f, 1.0f, 1.0f, 0.9f);
        salt->object->blend_mode = 12;
        set_matrix_identity(&salt->transform);
        salt_owner = (cRSubGame**)((char*)salt_owner + sizeof(cRSalt));
        --salt_count;
    } while (salt_count != 0);

    int banner_index = 0;
    do {
        char* banner_cursor = game + banner_index * sizeof(Banner);
        ((Banner*)(banner_cursor + BANNER_POOL_FROM_ROOT))
            ->SetObject(g_object_list.Add());
        if (banner_index == 0) {
            loader->load_x_mesh(
                (char*)"postofficestop.x",
                subgame.banners.slots[0].object,
                1);
        }
        if (banner_index == 1) {
            loader->load_x_mesh(
                (char*)"postofficestop.x",
                subgame.banners.slots[1].object,
                banner_index);
        }
        ((Banner*)(banner_cursor + BANNER_POOL_FROM_ROOT))->position.z = 0.0f;
        ((Banner*)(banner_cursor + BANNER_POOL_FROM_ROOT))->position.y = 0.0f;
        ((Banner*)(banner_cursor + BANNER_POOL_FROM_ROOT))->position.x = 0.0f;
        subgame.banners.slots[banner_index].owner_game = &subgame;
        ((Banner*)(banner_cursor + BANNER_POOL_FROM_ROOT))->visibility_mode = banner_index;
        ++banner_index;
        ((Banner*)(banner_cursor + BANNER_POOL_FROM_ROOT))->phase = 0.0f;
        ((Banner*)(banner_cursor + BANNER_POOL_FROM_ROOT))->phase_step = 0.006944444f;
    } while (banner_index < BANNER_SLOT_COUNT);

    BodNode* track_bod_list = &subgame.track_body_list_head;
    active_bod_list.add_bod(track_bod_list);
    subgame.barrier_sub_lazer_list_head.add_bod_after(track_bod_list);
    subgame.salt_hazard_list_head.add_bod_after(track_bod_list);
    subgame.golb_vapour_list_head.add_bod_after(track_bod_list);
    subgame.fringe_attachment_list_head.add_bod_after(track_bod_list);
    subgame.special_track_cell_list_head.add_bod_after(track_bod_list);
    subgame.unknown_bod_355cec.add_bod_after(track_bod_list);
    subgame.landscape_slice_list_head.add_bod_after(track_bod_list);
    subgame.unknown_bod_355c7c.add_bod_after(track_bod_list);

    debug_report_stub((char*)"path generation start\n");

    Path* path = &subgame.path_pairs[0].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_looptheloop_path_template_pair(
        6.0f,
        3,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[0].primary.position.z = 0.0f;
    subgame.path_pairs[0].primary.position.y = 0.0f;
    subgame.path_pairs[0].primary.position.x = 0.0f;

    subgame.path_pairs[0].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[0].secondary.Mirror(path);
    subgame.path_pairs[0].secondary.position.z = 0.0f;
    subgame.path_pairs[0].secondary.position.y = 0.0f;
    subgame.path_pairs[0].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[0].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[0].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[0].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[0].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[0].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[0].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[0].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[1].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_looptheloop_path_template_pair(
        6.0f,
        2,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[1].primary.position.z = 0.0f;
    subgame.path_pairs[1].primary.position.y = 0.0f;
    subgame.path_pairs[1].primary.position.x = 0.0f;

    subgame.path_pairs[1].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[1].secondary.Mirror(path);
    subgame.path_pairs[1].secondary.position.z = 0.0f;
    subgame.path_pairs[1].secondary.position.y = 0.0f;
    subgame.path_pairs[1].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[1].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[1].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[1].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[1].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[1].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[1].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[1].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[2].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_looptheloop_path_template_pair(
        8.0f,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[2].primary.position.z = 0.0f;
    subgame.path_pairs[2].primary.position.y = 0.0f;
    subgame.path_pairs[2].primary.position.x = 0.0f;

    subgame.path_pairs[2].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[2].secondary.Mirror(path);
    subgame.path_pairs[2].secondary.position.z = 0.0f;
    subgame.path_pairs[2].secondary.position.y = 0.0f;
    subgame.path_pairs[2].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[2].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[2].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[2].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[2].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[2].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[2].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[2].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[6].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_looptheloopw_path_template_pair(
        8.0f,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[6].primary.position.z = 0.0f;
    subgame.path_pairs[6].primary.position.y = 0.0f;
    subgame.path_pairs[6].primary.position.x = 0.0f;

    subgame.path_pairs[6].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[6].secondary.Mirror(path);
    subgame.path_pairs[6].secondary.position.z = 0.0f;
    subgame.path_pairs[6].secondary.position.y = 0.0f;
    subgame.path_pairs[6].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[6].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[6].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[6].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[6].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[6].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[6].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[6].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[3].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_looptheloop_path_template_pair(
        3.0f,
        2,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[3].primary.position.z = 0.0f;
    subgame.path_pairs[3].primary.position.y = 0.0f;
    subgame.path_pairs[3].primary.position.x = 0.0f;

    subgame.path_pairs[3].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[3].secondary.Mirror(path);
    subgame.path_pairs[3].secondary.position.z = 0.0f;
    subgame.path_pairs[3].secondary.position.y = 0.0f;
    subgame.path_pairs[3].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[3].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[3].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[3].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[3].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[3].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[3].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[3].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[4].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_looptheloop_path_template_pair(
        3.0f,
        3,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[4].primary.position.z = 0.0f;
    subgame.path_pairs[4].primary.position.y = 0.0f;
    subgame.path_pairs[4].primary.position.x = 0.0f;

    subgame.path_pairs[4].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[4].secondary.Mirror(path);
    subgame.path_pairs[4].secondary.position.z = 0.0f;
    subgame.path_pairs[4].secondary.position.y = 0.0f;
    subgame.path_pairs[4].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[4].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[4].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[4].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[4].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[4].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[4].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[4].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[5].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_looptheloop_path_template_pair(
        3.0f,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[5].primary.position.z = 0.0f;
    subgame.path_pairs[5].primary.position.y = 0.0f;
    subgame.path_pairs[5].primary.position.x = 0.0f;

    subgame.path_pairs[5].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[5].secondary.Mirror(path);
    subgame.path_pairs[5].secondary.position.z = 0.0f;
    subgame.path_pairs[5].secondary.position.y = 0.0f;
    subgame.path_pairs[5].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[5].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[5].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[5].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[5].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[5].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[5].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[5].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[7].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_loopbow_path_template_pair(
        6.0f,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[7].primary.position.z = 0.0f;
    subgame.path_pairs[7].primary.position.y = 0.0f;
    subgame.path_pairs[7].primary.position.x = 0.0f;

    subgame.path_pairs[7].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[7].secondary.Mirror(path);
    subgame.path_pairs[7].secondary.position.z = 0.0f;
    subgame.path_pairs[7].secondary.position.y = 0.0f;
    subgame.path_pairs[7].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[7].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[7].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[7].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[7].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[7].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[7].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[7].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[37].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_turnover_path_template_pair(
        6.0f,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[37].primary.position.z = 0.0f;
    subgame.path_pairs[37].primary.position.y = 0.0f;
    subgame.path_pairs[37].primary.position.x = 0.0f;

    subgame.path_pairs[37].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[37].secondary.Mirror(path);
    subgame.path_pairs[37].secondary.position.z = 0.0f;
    subgame.path_pairs[37].secondary.position.y = 0.0f;
    subgame.path_pairs[37].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[37].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[37].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[37].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[37].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[37].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[37].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[37].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[38].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_turnoverdouble_path_template_pair(
        6.0f,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[38].primary.position.z = 0.0f;
    subgame.path_pairs[38].primary.position.y = 0.0f;
    subgame.path_pairs[38].primary.position.x = 0.0f;

    subgame.path_pairs[38].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[38].secondary.Mirror(path);
    subgame.path_pairs[38].secondary.position.z = 0.0f;
    subgame.path_pairs[38].secondary.position.y = 0.0f;
    subgame.path_pairs[38].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[38].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[38].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[38].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[38].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[38].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[38].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[38].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[43].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_twister_path_template_pair(
        2.5f,
        3,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[43].primary.position.z = 0.0f;
    subgame.path_pairs[43].primary.position.y = 0.0f;
    subgame.path_pairs[43].primary.position.x = 0.0f;

    subgame.path_pairs[43].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[43].secondary.Mirror(path);
    subgame.path_pairs[43].secondary.position.z = 0.0f;
    subgame.path_pairs[43].secondary.position.y = 0.0f;
    subgame.path_pairs[43].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[43].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[43].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[43].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[43].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[43].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[43].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[43].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[44].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_twister_path_template_pair(
        2.5f,
        3,
        0,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[44].primary.position.z = 0.0f;
    subgame.path_pairs[44].primary.position.y = 0.0f;
    subgame.path_pairs[44].primary.position.x = 0.0f;

    subgame.path_pairs[44].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[44].secondary.Mirror(path);
    subgame.path_pairs[44].secondary.position.z = 0.0f;
    subgame.path_pairs[44].secondary.position.y = 0.0f;
    subgame.path_pairs[44].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[44].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[44].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[44].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[44].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[44].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[44].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[44].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[45].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_twister2_path_template_pair(
        2.5f,
        3,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[45].primary.position.z = 0.0f;
    subgame.path_pairs[45].primary.position.y = 0.0f;
    subgame.path_pairs[45].primary.position.x = 0.0f;

    subgame.path_pairs[45].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[45].secondary.Mirror(path);
    subgame.path_pairs[45].secondary.position.z = 0.0f;
    subgame.path_pairs[45].secondary.position.y = 0.0f;
    subgame.path_pairs[45].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[45].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[45].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[45].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[45].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[45].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[45].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[45].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[46].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_twister2_path_template_pair(
        2.5f,
        3,
        0,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[46].primary.position.z = 0.0f;
    subgame.path_pairs[46].primary.position.y = 0.0f;
    subgame.path_pairs[46].primary.position.x = 0.0f;

    subgame.path_pairs[46].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[46].secondary.Mirror(path);
    subgame.path_pairs[46].secondary.position.z = 0.0f;
    subgame.path_pairs[46].secondary.position.y = 0.0f;
    subgame.path_pairs[46].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[46].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[46].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[46].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[46].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[46].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[46].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[46].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[39].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_turnunder_path_template_pair(
        6.0f,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[39].primary.position.z = 0.0f;
    subgame.path_pairs[39].primary.position.y = 0.0f;
    subgame.path_pairs[39].primary.position.x = 0.0f;

    subgame.path_pairs[39].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[39].secondary.Mirror(path);
    subgame.path_pairs[39].secondary.position.z = 0.0f;
    subgame.path_pairs[39].secondary.position.y = 0.0f;
    subgame.path_pairs[39].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[39].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[39].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[39].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[39].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[39].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[39].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[39].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[41].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_invert_path_template_pair(
        6.0f,
        8,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[41].primary.position.z = 0.0f;
    subgame.path_pairs[41].primary.position.y = 0.0f;
    subgame.path_pairs[41].primary.position.x = 0.0f;

    subgame.path_pairs[41].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[41].secondary.Mirror(path);
    subgame.path_pairs[41].secondary.position.z = 0.0f;
    subgame.path_pairs[41].secondary.position.y = 0.0f;
    subgame.path_pairs[41].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[41].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[41].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[41].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[41].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[41].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[41].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[41].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[42].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_halfpipe_path_template_pair(
        6.0f,
        8,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[42].primary.position.z = 0.0f;
    subgame.path_pairs[42].primary.position.y = 0.0f;
    subgame.path_pairs[42].primary.position.x = 0.0f;

    subgame.path_pairs[42].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[42].secondary.Mirror(path);
    subgame.path_pairs[42].secondary.position.z = 0.0f;
    subgame.path_pairs[42].secondary.position.y = 0.0f;
    subgame.path_pairs[42].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[42].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[42].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[42].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[42].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[42].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[42].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[42].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[40].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_wibble_path_template_pair(
        6.0f,
        8,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[40].primary.position.z = 0.0f;
    subgame.path_pairs[40].primary.position.y = 0.0f;
    subgame.path_pairs[40].primary.position.x = 0.0f;

    subgame.path_pairs[40].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[40].secondary.Mirror(path);
    subgame.path_pairs[40].secondary.position.z = 0.0f;
    subgame.path_pairs[40].secondary.position.y = 0.0f;
    subgame.path_pairs[40].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[40].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[40].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[40].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[40].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[40].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[40].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[40].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[31].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_supertramp_path_template_pair(
        6.0f,
        2,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga",
        (char*)"Objects/World00/TrackWarn.tga");
    subgame.path_pairs[31].primary.position.z = 0.0f;
    subgame.path_pairs[31].primary.position.y = 0.0f;
    subgame.path_pairs[31].primary.position.x = 0.0f;
    path->build_track_fringe_supertramp_mesh(
        (char*)"Objects/Universe/Fringe.tga");
    subgame.path_pairs[31].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[31].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[31].primary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[31].secondary;
    path->SetObject(g_object_list.Add());
    path->initialize_supertramp_path_template_pair(
        6.0f,
        2,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga",
        (char*)"Objects/World00/TrackWarn.tga");
    subgame.path_pairs[31].secondary.position.z = 0.0f;
    subgame.path_pairs[31].secondary.position.y = 0.0f;
    subgame.path_pairs[31].secondary.position.x = 0.0f;
    path->build_track_fringe_supertramp_mesh(
        (char*)"Objects/Universe/Fringe.tga");
    subgame.path_pairs[31].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[31].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[31].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[36].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_start_path_template_pair(
        4.0f,
        8,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[36].primary.position.z = 0.0f;
    subgame.path_pairs[36].primary.position.y = 0.0f;
    subgame.path_pairs[36].primary.position.x = 0.0f;
    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[36].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[36].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[36].primary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[36].secondary;
    path->SetObject(g_object_list.Add());
    path->initialize_start_path_template_pair(
        4.0f,
        8,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Slidex.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[36].secondary.position.z = 0.0f;
    subgame.path_pairs[36].secondary.position.y = 0.0f;
    subgame.path_pairs[36].secondary.position.x = 0.0f;
    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[36].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[36].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[36].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[25].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_loopout_path_template_pair(
        3.0f,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[25].primary.position.z = 0.0f;
    subgame.path_pairs[25].primary.position.y = 0.0f;
    subgame.path_pairs[25].primary.position.x = 0.0f;

    subgame.path_pairs[25].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[25].secondary.Mirror(path);
    subgame.path_pairs[25].secondary.position.z = 0.0f;
    subgame.path_pairs[25].secondary.position.y = 0.0f;
    subgame.path_pairs[25].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[25].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[25].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[25].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[25].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[25].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[25].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[25].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[27].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_loopout_path_template_pair(
        5.0f,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[27].primary.position.z = 0.0f;
    subgame.path_pairs[27].primary.position.y = 0.0f;
    subgame.path_pairs[27].primary.position.x = 0.0f;

    subgame.path_pairs[27].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[27].secondary.Mirror(path);
    subgame.path_pairs[27].secondary.position.z = 0.0f;
    subgame.path_pairs[27].secondary.position.y = 0.0f;
    subgame.path_pairs[27].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[27].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[27].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[27].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[27].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[27].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[27].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[27].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[26].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_loopout_path_template_pair(
        3.0f,
        3,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[26].primary.position.z = 0.0f;
    subgame.path_pairs[26].primary.position.y = 0.0f;
    subgame.path_pairs[26].primary.position.x = 0.0f;

    subgame.path_pairs[26].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[26].secondary.Mirror(path);
    subgame.path_pairs[26].secondary.position.z = 0.0f;
    subgame.path_pairs[26].secondary.position.y = 0.0f;
    subgame.path_pairs[26].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[26].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[26].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[26].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[26].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[26].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[26].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[26].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[16].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_hump_path_template_pair(
        4.0f,
        1.0f,
        3,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[16].primary.position.z = 0.0f;
    subgame.path_pairs[16].primary.position.y = 0.0f;
    subgame.path_pairs[16].primary.position.x = 0.0f;

    subgame.path_pairs[16].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[16].secondary.Mirror(path);
    subgame.path_pairs[16].secondary.position.z = 0.0f;
    subgame.path_pairs[16].secondary.position.y = 0.0f;
    subgame.path_pairs[16].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[16].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[16].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[16].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[16].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[16].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[16].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[16].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[17].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_dump_path_template_pair(
        4.0f,
        1.0f,
        3,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[17].primary.position.z = 0.0f;
    subgame.path_pairs[17].primary.position.y = 0.0f;
    subgame.path_pairs[17].primary.position.x = 0.0f;

    subgame.path_pairs[17].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[17].secondary.Mirror(path);
    subgame.path_pairs[17].secondary.position.z = 0.0f;
    subgame.path_pairs[17].secondary.position.y = 0.0f;
    subgame.path_pairs[17].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[17].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[17].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[17].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[17].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[17].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[17].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[17].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[18].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_hump_path_template_pair(
        4.0f,
        0.300000012f,
        3,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[18].primary.position.z = 0.0f;
    subgame.path_pairs[18].primary.position.y = 0.0f;
    subgame.path_pairs[18].primary.position.x = 0.0f;

    subgame.path_pairs[18].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[18].secondary.Mirror(path);
    subgame.path_pairs[18].secondary.position.z = 0.0f;
    subgame.path_pairs[18].secondary.position.y = 0.0f;
    subgame.path_pairs[18].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[18].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[18].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[18].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[18].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[18].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[18].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[18].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[19].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_dump_path_template_pair(
        4.0f,
        0.300000012f,
        3,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[19].primary.position.z = 0.0f;
    subgame.path_pairs[19].primary.position.y = 0.0f;
    subgame.path_pairs[19].primary.position.x = 0.0f;

    subgame.path_pairs[19].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[19].secondary.Mirror(path);
    subgame.path_pairs[19].secondary.position.z = 0.0f;
    subgame.path_pairs[19].secondary.position.y = 0.0f;
    subgame.path_pairs[19].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[19].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[19].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[19].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[19].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[19].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[19].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[19].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[8].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_hill_valley_path_template_pair(
        8,
        4.0f,
        20.0f,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[8].primary.position.z = 0.0f;
    subgame.path_pairs[8].primary.position.y = 0.0f;
    subgame.path_pairs[8].primary.position.x = 0.0f;

    subgame.path_pairs[8].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[8].secondary.Mirror(path);
    subgame.path_pairs[8].secondary.position.z = 0.0f;
    subgame.path_pairs[8].secondary.position.y = 0.0f;
    subgame.path_pairs[8].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[8].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[8].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[8].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[8].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[8].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[8].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[8].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[10].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_hill_valley_path_template_pair(
        4,
        4.0f,
        20.0f,
        0,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[10].primary.position.z = 0.0f;
    subgame.path_pairs[10].primary.position.y = 0.0f;
    subgame.path_pairs[10].primary.position.x = 0.0f;

    subgame.path_pairs[10].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[10].secondary.Mirror(path);
    subgame.path_pairs[10].secondary.position.z = 0.0f;
    subgame.path_pairs[10].secondary.position.y = 0.0f;
    subgame.path_pairs[10].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[10].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[10].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[10].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[10].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[10].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[10].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[10].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[9].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_hill_valley_path_template_pair(
        4,
        4.0f,
        20.0f,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[9].primary.position.z = 0.0f;
    subgame.path_pairs[9].primary.position.y = 0.0f;
    subgame.path_pairs[9].primary.position.x = 0.0f;

    subgame.path_pairs[9].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[9].secondary.Mirror(path);
    subgame.path_pairs[9].secondary.position.z = 0.0f;
    subgame.path_pairs[9].secondary.position.y = 0.0f;
    subgame.path_pairs[9].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[9].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[9].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[9].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[9].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[9].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[9].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[9].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[14].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_sbend_path_template_pair(
        8,
        8.0f,
        14.0f,
        1,
        (char*)"Objects/World00/Track0.tga",
        (char*)"Objects/World00/Track0.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[14].primary.position.z = 0.0f;
    subgame.path_pairs[14].primary.position.y = 0.0f;
    subgame.path_pairs[14].primary.position.x = 0.0f;

    subgame.path_pairs[14].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[14].secondary.Mirror(path);
    subgame.path_pairs[14].secondary.position.z = 0.0f;
    subgame.path_pairs[14].secondary.position.y = 0.0f;
    subgame.path_pairs[14].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[14].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[14].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[14].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[14].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[14].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[14].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[14].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[11].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_hill_valley_path_template_pair(
        8,
        -4.0f,
        20.0f,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[11].primary.position.z = 0.0f;
    subgame.path_pairs[11].primary.position.y = 0.0f;
    subgame.path_pairs[11].primary.position.x = 0.0f;

    subgame.path_pairs[11].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[11].secondary.Mirror(path);
    subgame.path_pairs[11].secondary.position.z = 0.0f;
    subgame.path_pairs[11].secondary.position.y = 0.0f;
    subgame.path_pairs[11].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[11].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[11].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[11].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[11].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[11].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[11].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[11].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[13].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_hill_valley_path_template_pair(
        4,
        -4.0f,
        20.0f,
        0,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[13].primary.position.z = 0.0f;
    subgame.path_pairs[13].primary.position.y = 0.0f;
    subgame.path_pairs[13].primary.position.x = 0.0f;

    subgame.path_pairs[13].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[13].secondary.Mirror(path);
    subgame.path_pairs[13].secondary.position.z = 0.0f;
    subgame.path_pairs[13].secondary.position.y = 0.0f;
    subgame.path_pairs[13].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[13].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[13].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[13].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[13].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[13].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[13].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[13].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[12].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_hill_valley_path_template_pair(
        4,
        -4.0f,
        20.0f,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[12].primary.position.z = 0.0f;
    subgame.path_pairs[12].primary.position.y = 0.0f;
    subgame.path_pairs[12].primary.position.x = 0.0f;

    subgame.path_pairs[12].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[12].secondary.Mirror(path);
    subgame.path_pairs[12].secondary.position.z = 0.0f;
    subgame.path_pairs[12].secondary.position.y = 0.0f;
    subgame.path_pairs[12].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[12].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[12].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[12].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[12].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[12].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[12].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[12].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[20].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_dip_path_template_pair(
        4.0f,
        2,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[20].primary.position.z = 0.0f;
    subgame.path_pairs[20].primary.position.y = 0.0f;
    subgame.path_pairs[20].primary.position.x = 0.0f;

    subgame.path_pairs[20].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[20].secondary.Mirror(path);
    subgame.path_pairs[20].secondary.position.z = 0.0f;
    subgame.path_pairs[20].secondary.position.y = 0.0f;
    subgame.path_pairs[20].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[20].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[20].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[20].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[20].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[20].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[20].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[20].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[21].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_screw_path_template_pair(
        0x18,
        3,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[21].primary.position.z = 0.0f;
    subgame.path_pairs[21].primary.position.y = 0.0f;
    subgame.path_pairs[21].primary.position.x = 0.0f;

    subgame.path_pairs[21].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[21].secondary.Mirror(path);
    subgame.path_pairs[21].secondary.position.z = 0.0f;
    subgame.path_pairs[21].secondary.position.y = 0.0f;
    subgame.path_pairs[21].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[21].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[21].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[21].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[21].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[21].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[21].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[21].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[22].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_slalom_path_template_pair(
        0x20,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[22].primary.position.z = 0.0f;
    subgame.path_pairs[22].primary.position.y = 0.0f;
    subgame.path_pairs[22].primary.position.x = 0.0f;

    subgame.path_pairs[22].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[22].secondary.Mirror(path);
    subgame.path_pairs[22].secondary.position.z = 0.0f;
    subgame.path_pairs[22].secondary.position.y = 0.0f;
    subgame.path_pairs[22].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[22].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[22].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[22].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[22].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[22].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[22].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[22].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[23].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_slalombig_path_template_pair(
        0x20,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[23].primary.position.z = 0.0f;
    subgame.path_pairs[23].primary.position.y = 0.0f;
    subgame.path_pairs[23].primary.position.x = 0.0f;

    subgame.path_pairs[23].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[23].secondary.Mirror(path);
    subgame.path_pairs[23].secondary.position.z = 0.0f;
    subgame.path_pairs[23].secondary.position.y = 0.0f;
    subgame.path_pairs[23].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[23].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[23].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[23].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[23].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[23].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[23].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[23].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[32].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_slalomdouble_path_template_pair(
        0x20,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[32].primary.position.z = 0.0f;
    subgame.path_pairs[32].primary.position.y = 0.0f;
    subgame.path_pairs[32].primary.position.x = 0.0f;

    subgame.path_pairs[32].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[32].secondary.Mirror(path);
    subgame.path_pairs[32].secondary.position.z = 0.0f;
    subgame.path_pairs[32].secondary.position.y = 0.0f;
    subgame.path_pairs[32].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[32].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[32].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[32].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[32].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[32].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[32].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[32].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[24].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_worm_path_template_pair(
        (char*)"Objects/World00/Worm.tga");
    subgame.path_pairs[24].primary.position.z = 0.0f;
    subgame.path_pairs[24].primary.position.y = 0.0f;
    subgame.path_pairs[24].primary.position.x = 0.0f;

    subgame.path_pairs[24].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[24].secondary.Mirror(path);
    subgame.path_pairs[24].secondary.position.z = 0.0f;
    subgame.path_pairs[24].secondary.position.y = 0.0f;
    subgame.path_pairs[24].secondary.position.x = 0.0f;

    subgame.path_pairs[24].primary.fringe_mesh_bod.SetObject(
        g_object_list.Add());
    disable_object_rendering(
        subgame.path_pairs[24].primary.fringe_mesh_bod.object);
    subgame.path_pairs[24].secondary.fringe_mesh_bod.SetObject(
        g_object_list.Add());
    disable_object_rendering(
        subgame.path_pairs[24].secondary.fringe_mesh_bod.object);
    subgame.path_pairs[24].primary.object->blend_mode = 8;
    subgame.path_pairs[24].secondary.object->blend_mode = 8;

    path = &subgame.path_pairs[28].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_sweep_path_template_pair(
        4.0f,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[28].primary.position.z = 0.0f;
    subgame.path_pairs[28].primary.position.y = 0.0f;
    subgame.path_pairs[28].primary.position.x = 0.0f;

    subgame.path_pairs[28].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[28].secondary.Mirror(path);
    subgame.path_pairs[28].secondary.position.z = 0.0f;
    subgame.path_pairs[28].secondary.position.y = 0.0f;
    subgame.path_pairs[28].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[28].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[28].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[28].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[28].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[28].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[28].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[28].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[15].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_cage2_path_template_pair(
        3,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[15].primary.position.z = 0.0f;
    subgame.path_pairs[15].primary.position.y = 0.0f;
    subgame.path_pairs[15].primary.position.x = 0.0f;

    subgame.path_pairs[15].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[15].secondary.Mirror(path);
    subgame.path_pairs[15].secondary.position.z = 0.0f;
    subgame.path_pairs[15].secondary.position.y = 0.0f;
    subgame.path_pairs[15].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[15].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[15].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[15].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[15].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[15].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[15].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[15].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[33].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_p_path_template_pair(
        0,
        4.0f,
        3,
        0.5f,
        -2.5f,
        14,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[33].primary.position.z = 0.0f;
    subgame.path_pairs[33].primary.position.y = 0.0f;
    subgame.path_pairs[33].primary.position.x = 0.0f;

    subgame.path_pairs[33].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[33].secondary.Mirror(path);
    subgame.path_pairs[33].secondary.position.z = 0.0f;
    subgame.path_pairs[33].secondary.position.y = 0.0f;
    subgame.path_pairs[33].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[33].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[33].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[33].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[33].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[33].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[33].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[33].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[34].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_p_path_template_pair(
        1,
        4.0f,
        3,
        -2.5f,
        2.5f,
        14,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[34].primary.position.z = 0.0f;
    subgame.path_pairs[34].primary.position.y = 0.0f;
    subgame.path_pairs[34].primary.position.x = 0.0f;

    subgame.path_pairs[34].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[34].secondary.Mirror(path);
    subgame.path_pairs[34].secondary.position.z = 0.0f;
    subgame.path_pairs[34].secondary.position.y = 0.0f;
    subgame.path_pairs[34].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[34].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[34].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[34].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[34].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[34].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[34].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[34].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[35].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_p_path_template_pair(
        2,
        4.0f,
        3,
        2.5f,
        0.5f,
        14,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[35].primary.position.z = 0.0f;
    subgame.path_pairs[35].primary.position.y = 0.0f;
    subgame.path_pairs[35].primary.position.x = 0.0f;

    subgame.path_pairs[35].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[35].secondary.Mirror(path);
    subgame.path_pairs[35].secondary.position.z = 0.0f;
    subgame.path_pairs[35].secondary.position.y = 0.0f;
    subgame.path_pairs[35].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[35].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[35].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[35].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[35].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[35].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[35].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[35].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[29].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_snake_path_template_pair(
        2.0f,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Track0.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[29].primary.position.z = 0.0f;
    subgame.path_pairs[29].primary.position.y = 0.0f;
    subgame.path_pairs[29].primary.position.x = 0.0f;

    subgame.path_pairs[29].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[29].secondary.Mirror(path);
    subgame.path_pairs[29].secondary.position.z = 0.0f;
    subgame.path_pairs[29].secondary.position.y = 0.0f;
    subgame.path_pairs[29].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[29].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[29].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[29].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[29].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[29].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[29].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[29].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[47].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_toad_path_template_pair(
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Track0.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[47].primary.position.z = 0.0f;
    subgame.path_pairs[47].primary.position.y = 0.0f;
    subgame.path_pairs[47].primary.position.x = 0.0f;

    subgame.path_pairs[47].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[47].secondary.Mirror(path);
    subgame.path_pairs[47].secondary.position.z = 0.0f;
    subgame.path_pairs[47].secondary.position.y = 0.0f;
    subgame.path_pairs[47].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[47].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[47].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[47].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[47].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[47].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[47].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[47].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[48].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_toad_path_template_pair(
        0,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Track0.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[48].primary.position.z = 0.0f;
    subgame.path_pairs[48].primary.position.y = 0.0f;
    subgame.path_pairs[48].primary.position.x = 0.0f;

    subgame.path_pairs[48].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[48].secondary.Mirror(path);
    subgame.path_pairs[48].secondary.position.z = 0.0f;
    subgame.path_pairs[48].secondary.position.y = 0.0f;
    subgame.path_pairs[48].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[48].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[48].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[48].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[48].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[48].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[48].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[48].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[49].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_toad_path_template_pair(
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Track0.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[49].primary.position.z = 0.0f;
    subgame.path_pairs[49].primary.position.y = 0.0f;
    subgame.path_pairs[49].primary.position.x = 0.0f;

    subgame.path_pairs[49].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[49].secondary.Mirror(path);
    subgame.path_pairs[49].secondary.position.z = 0.0f;
    subgame.path_pairs[49].secondary.position.y = 0.0f;
    subgame.path_pairs[49].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", -1.0f);
    subgame.path_pairs[49].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[49].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[49].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[49].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 1.0f);
    subgame.path_pairs[49].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[49].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[49].secondary.fringe_mesh_bod.position.x = 0.0f;

    path = &subgame.path_pairs[50].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_toad_path_template_pair(
        0,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Track0.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[50].primary.position.z = 0.0f;
    subgame.path_pairs[50].primary.position.y = 0.0f;
    subgame.path_pairs[50].primary.position.x = 0.0f;

    subgame.path_pairs[50].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[50].secondary.Mirror(path);
    subgame.path_pairs[50].secondary.position.z = 0.0f;
    subgame.path_pairs[50].secondary.position.y = 0.0f;
    subgame.path_pairs[50].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 1.0f);
    subgame.path_pairs[50].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[50].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[50].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[50].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", -1.0f);
    subgame.path_pairs[50].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[50].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[50].secondary.fringe_mesh_bod.position.x = 0.0f;

    tColour path_transition_color;
    path_transition_color.noop_this_constructor();
    path_transition_color.store_color4f(1.0f, 1.0f, 1.0f, 0.60000002f);

    path = &subgame.path_pairs[51].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_looptheloop_path_template_pair(
        6.0f,
        3,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[51].primary.position.z = 0.0f;
    subgame.path_pairs[51].primary.position.y = 0.0f;
    subgame.path_pairs[51].primary.position.x = 0.0f;

    subgame.path_pairs[51].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[51].secondary.Mirror(path);
    subgame.path_pairs[51].secondary.position.z = 0.0f;
    subgame.path_pairs[51].secondary.position.y = 0.0f;
    subgame.path_pairs[51].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[51].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[51].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[51].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[51].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[51].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[51].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[51].secondary.fringe_mesh_bod.position.x = 0.0f;

    subgame.path_pairs[0].primary.entry_transition_strip_mesh =
        subgame.path_pairs[51].primary.object;
    subgame.path_pairs[0].primary.entry_base_strip_mesh =
        subgame.path_pairs[0].primary.object;
    subgame.path_pairs[0].secondary.entry_transition_strip_mesh =
        subgame.path_pairs[51].secondary.object;
    subgame.path_pairs[0].secondary.entry_base_strip_mesh =
        subgame.path_pairs[0].secondary.object;

    path = &subgame.path_pairs[52].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_looptheloop_path_template_pair(
        6.0f,
        2,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[52].primary.position.z = 0.0f;
    subgame.path_pairs[52].primary.position.y = 0.0f;
    subgame.path_pairs[52].primary.position.x = 0.0f;

    subgame.path_pairs[52].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[52].secondary.Mirror(path);
    subgame.path_pairs[52].secondary.position.z = 0.0f;
    subgame.path_pairs[52].secondary.position.y = 0.0f;
    subgame.path_pairs[52].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[52].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[52].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[52].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[52].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[52].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[52].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[52].secondary.fringe_mesh_bod.position.x = 0.0f;

    subgame.path_pairs[1].primary.entry_transition_strip_mesh =
        subgame.path_pairs[52].primary.object;
    subgame.path_pairs[1].secondary.entry_base_strip_mesh =
        subgame.path_pairs[1].secondary.object;
    subgame.path_pairs[1].primary.entry_base_strip_mesh =
        subgame.path_pairs[1].primary.object;
    subgame.path_pairs[1].secondary.entry_transition_strip_mesh =
        subgame.path_pairs[52].secondary.object;

    path = &subgame.path_pairs[53].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_looptheloop_path_template_pair(
        8.0f,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[53].primary.position.z = 0.0f;
    subgame.path_pairs[53].primary.position.y = 0.0f;
    subgame.path_pairs[53].primary.position.x = 0.0f;

    subgame.path_pairs[53].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[53].secondary.Mirror(path);
    subgame.path_pairs[53].secondary.position.z = 0.0f;
    subgame.path_pairs[53].secondary.position.y = 0.0f;
    subgame.path_pairs[53].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[53].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[53].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[53].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[53].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[53].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[53].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[53].secondary.fringe_mesh_bod.position.x = 0.0f;

    subgame.path_pairs[2].primary.entry_transition_strip_mesh =
        subgame.path_pairs[53].primary.object;
    subgame.path_pairs[2].primary.entry_base_strip_mesh =
        subgame.path_pairs[2].primary.object;
    subgame.path_pairs[2].secondary.entry_transition_strip_mesh =
        subgame.path_pairs[53].secondary.object;
    subgame.path_pairs[2].secondary.entry_base_strip_mesh =
        subgame.path_pairs[2].secondary.object;

    path = &subgame.path_pairs[57].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_looptheloopw_path_template_pair(
        8.0f,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[57].primary.position.z = 0.0f;
    subgame.path_pairs[57].primary.position.y = 0.0f;
    subgame.path_pairs[57].primary.position.x = 0.0f;

    subgame.path_pairs[57].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[57].secondary.Mirror(path);
    subgame.path_pairs[57].secondary.position.z = 0.0f;
    subgame.path_pairs[57].secondary.position.y = 0.0f;
    subgame.path_pairs[57].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[57].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[57].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[57].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[57].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[57].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[57].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[57].secondary.fringe_mesh_bod.position.x = 0.0f;

    subgame.path_pairs[6].primary.entry_transition_strip_mesh =
        subgame.path_pairs[57].primary.object;
    subgame.path_pairs[6].primary.entry_base_strip_mesh =
        subgame.path_pairs[6].primary.object;
    subgame.path_pairs[6].secondary.entry_transition_strip_mesh =
        subgame.path_pairs[57].secondary.object;
    subgame.path_pairs[6].secondary.entry_base_strip_mesh =
        subgame.path_pairs[6].secondary.object;

    path = &subgame.path_pairs[54].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_looptheloop_path_template_pair(
        3.0f,
        2,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[54].primary.position.z = 0.0f;
    subgame.path_pairs[54].primary.position.y = 0.0f;
    subgame.path_pairs[54].primary.position.x = 0.0f;

    subgame.path_pairs[54].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[54].secondary.Mirror(path);
    subgame.path_pairs[54].secondary.position.z = 0.0f;
    subgame.path_pairs[54].secondary.position.y = 0.0f;
    subgame.path_pairs[54].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[54].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[54].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[54].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[54].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[54].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[54].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[54].secondary.fringe_mesh_bod.position.x = 0.0f;

    subgame.path_pairs[3].primary.entry_transition_strip_mesh =
        subgame.path_pairs[54].primary.object;
    subgame.path_pairs[3].primary.entry_base_strip_mesh =
        subgame.path_pairs[3].primary.object;
    subgame.path_pairs[3].secondary.entry_transition_strip_mesh =
        subgame.path_pairs[54].secondary.object;
    subgame.path_pairs[3].secondary.entry_base_strip_mesh =
        subgame.path_pairs[3].secondary.object;

    path = &subgame.path_pairs[55].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_looptheloop_path_template_pair(
        3.0f,
        3,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[55].primary.position.z = 0.0f;
    subgame.path_pairs[55].primary.position.y = 0.0f;
    subgame.path_pairs[55].primary.position.x = 0.0f;

    subgame.path_pairs[55].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[55].secondary.Mirror(path);
    subgame.path_pairs[55].secondary.position.z = 0.0f;
    subgame.path_pairs[55].secondary.position.y = 0.0f;
    subgame.path_pairs[55].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[55].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[55].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[55].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[55].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[55].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[55].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[55].secondary.fringe_mesh_bod.position.x = 0.0f;

    subgame.path_pairs[4].primary.entry_transition_strip_mesh =
        subgame.path_pairs[55].primary.object;
    subgame.path_pairs[4].primary.entry_base_strip_mesh =
        subgame.path_pairs[4].primary.object;
    subgame.path_pairs[4].secondary.entry_transition_strip_mesh =
        subgame.path_pairs[55].secondary.object;
    subgame.path_pairs[4].secondary.entry_base_strip_mesh =
        subgame.path_pairs[4].secondary.object;

    path = &subgame.path_pairs[56].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_looptheloop_path_template_pair(
        3.0f,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[56].primary.position.z = 0.0f;
    subgame.path_pairs[56].primary.position.y = 0.0f;
    subgame.path_pairs[56].primary.position.x = 0.0f;

    subgame.path_pairs[56].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[56].secondary.Mirror(path);
    subgame.path_pairs[56].secondary.position.z = 0.0f;
    subgame.path_pairs[56].secondary.position.y = 0.0f;
    subgame.path_pairs[56].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[56].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[56].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[56].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[56].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[56].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[56].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[56].secondary.fringe_mesh_bod.position.x = 0.0f;

    subgame.path_pairs[5].primary.entry_transition_strip_mesh =
        subgame.path_pairs[56].primary.object;
    subgame.path_pairs[5].primary.entry_base_strip_mesh =
        subgame.path_pairs[5].primary.object;
    subgame.path_pairs[5].secondary.entry_transition_strip_mesh =
        subgame.path_pairs[56].secondary.object;
    subgame.path_pairs[5].secondary.entry_base_strip_mesh =
        subgame.path_pairs[5].secondary.object;

    path = &subgame.path_pairs[58].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_loopbow_path_template_pair(
        6.0f,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[58].primary.position.z = 0.0f;
    subgame.path_pairs[58].primary.position.y = 0.0f;
    subgame.path_pairs[58].primary.position.x = 0.0f;

    subgame.path_pairs[58].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[58].secondary.Mirror(path);
    subgame.path_pairs[58].secondary.position.z = 0.0f;
    subgame.path_pairs[58].secondary.position.y = 0.0f;
    subgame.path_pairs[58].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[58].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[58].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[58].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[58].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[58].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[58].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[58].secondary.fringe_mesh_bod.position.x = 0.0f;

    subgame.path_pairs[7].primary.entry_transition_strip_mesh =
        subgame.path_pairs[58].primary.object;
    subgame.path_pairs[7].primary.entry_base_strip_mesh =
        subgame.path_pairs[7].primary.object;
    subgame.path_pairs[7].secondary.entry_transition_strip_mesh =
        subgame.path_pairs[58].secondary.object;
    subgame.path_pairs[7].secondary.entry_base_strip_mesh =
        subgame.path_pairs[7].secondary.object;

    path = &subgame.path_pairs[62].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_invert_path_template_pair(
        6.0f,
        8,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[62].primary.position.z = 0.0f;
    subgame.path_pairs[62].primary.position.y = 0.0f;
    subgame.path_pairs[62].primary.position.x = 0.0f;

    subgame.path_pairs[62].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[62].secondary.Mirror(path);
    subgame.path_pairs[62].secondary.position.z = 0.0f;
    subgame.path_pairs[62].secondary.position.y = 0.0f;
    subgame.path_pairs[62].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[62].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[62].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[62].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[62].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[62].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[62].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[62].secondary.fringe_mesh_bod.position.x = 0.0f;

    subgame.path_pairs[41].primary.entry_transition_strip_mesh =
        subgame.path_pairs[62].primary.object;
    subgame.path_pairs[41].primary.entry_base_strip_mesh =
        subgame.path_pairs[41].primary.object;
    subgame.path_pairs[41].secondary.entry_transition_strip_mesh =
        subgame.path_pairs[62].secondary.object;
    subgame.path_pairs[41].secondary.entry_base_strip_mesh =
        subgame.path_pairs[41].secondary.object;

    path = &subgame.path_pairs[59].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_loopout_path_template_pair(
        3.0f,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[59].primary.position.z = 0.0f;
    subgame.path_pairs[59].primary.position.y = 0.0f;
    subgame.path_pairs[59].primary.position.x = 0.0f;

    subgame.path_pairs[59].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[59].secondary.Mirror(path);
    subgame.path_pairs[59].secondary.position.z = 0.0f;
    subgame.path_pairs[59].secondary.position.y = 0.0f;
    subgame.path_pairs[59].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[59].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[59].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[59].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[59].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[59].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[59].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[59].secondary.fringe_mesh_bod.position.x = 0.0f;

    subgame.path_pairs[25].primary.entry_transition_strip_mesh =
        subgame.path_pairs[59].primary.object;
    subgame.path_pairs[25].primary.entry_base_strip_mesh =
        subgame.path_pairs[25].primary.object;
    subgame.path_pairs[25].secondary.entry_transition_strip_mesh =
        subgame.path_pairs[59].secondary.object;
    subgame.path_pairs[25].secondary.entry_base_strip_mesh =
        subgame.path_pairs[25].secondary.object;

    path = &subgame.path_pairs[61].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_loopout_path_template_pair(
        5.0f,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[61].primary.position.z = 0.0f;
    subgame.path_pairs[61].primary.position.y = 0.0f;
    subgame.path_pairs[61].primary.position.x = 0.0f;

    subgame.path_pairs[61].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[61].secondary.Mirror(path);
    subgame.path_pairs[61].secondary.position.z = 0.0f;
    subgame.path_pairs[61].secondary.position.y = 0.0f;
    subgame.path_pairs[61].secondary.position.x = 0.0f;

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[61].primary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[61].primary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[61].primary.fringe_mesh_bod.position.x = 0.0f;
    subgame.path_pairs[61].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[61].secondary.fringe_mesh_bod.position.z = 0.0f;
    subgame.path_pairs[61].secondary.fringe_mesh_bod.position.y = 0.0f;
    subgame.path_pairs[61].secondary.fringe_mesh_bod.position.x = 0.0f;

    subgame.path_pairs[27].primary.entry_transition_strip_mesh =
        subgame.path_pairs[61].primary.object;
    subgame.path_pairs[27].primary.entry_base_strip_mesh =
        subgame.path_pairs[27].primary.object;
    subgame.path_pairs[27].secondary.entry_transition_strip_mesh =
        subgame.path_pairs[61].secondary.object;
    subgame.path_pairs[27].secondary.entry_base_strip_mesh =
        subgame.path_pairs[27].secondary.object;

    path = &subgame.path_pairs[60].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_loopout_path_template_pair(
        3.0f,
        3,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[60].primary.position.zero_vector3();

    subgame.path_pairs[60].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[60].secondary.Mirror(path);
    subgame.path_pairs[60].secondary.position.zero_vector3();

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[60].primary.fringe_mesh_bod.position.zero_vector3();
    subgame.path_pairs[60].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    subgame.path_pairs[60].secondary.fringe_mesh_bod.position.zero_vector3();

    subgame.path_pairs[26].primary.entry_transition_strip_mesh =
        subgame.path_pairs[60].primary.object;
    subgame.path_pairs[26].primary.entry_base_strip_mesh =
        subgame.path_pairs[26].primary.object;
    subgame.path_pairs[26].secondary.entry_transition_strip_mesh =
        subgame.path_pairs[60].secondary.object;
    subgame.path_pairs[26].secondary.entry_base_strip_mesh =
        subgame.path_pairs[26].secondary.object;

    debug_report_stub((char*)"path generation end\n");

    subgame.player.presentation.cutscene_animation_slots[0].body.SetObject(
        g_object_list.Add());

    char base_animation_name[0x80];
    char* test_line = find_case_insensitive_substring(
        (char*)"Test:", loader->animation_bytes);
    if (test_line != 0) {
        char* source = find_case_insensitive_substring((char*)":", test_line) + 1;
        char* destination = base_animation_name;
        while (*source != '.')
            *destination++ = *source++;
        *destination++ = '.';
        *destination++ = 'x';
        *destination = 0;
    } else {
        rstrcpy_checked_ascii(
            base_animation_name, (char*)"turbo-base-000.x");
    }

    loader->load_x_animation_clip(
        base_animation_name,
        subgame.player.presentation.cutscene_animation_slots[0].body.object);
    subgame.player.presentation.SetObject(g_object_list.Add());
    loader->load_x_animation_clip(
        base_animation_name, subgame.player.presentation.object);

    subgame.player.presentation.cutscene_animation_slots[1].body.SetObject(
        g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"turbo-move-000.x",
        subgame.player.presentation.cutscene_animation_slots[1].body.object);
    subgame.player.presentation.cutscene_animation_slots[2].body.SetObject(
        g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"turbo-bobalong-000.x",
        subgame.player.presentation.cutscene_animation_slots[2].body.object);
    subgame.player.presentation.cutscene_animation_slots[3].body.SetObject(
        g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"turbo-lookbackleft-000.x",
        subgame.player.presentation.cutscene_animation_slots[3].body.object);
    subgame.player.presentation.cutscene_animation_slots[4].body.SetObject(
        g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"turbo-lookbackright-000.x",
        subgame.player.presentation.cutscene_animation_slots[4].body.object);
    subgame.player.presentation.cutscene_animation_slots[5].body.SetObject(
        g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"turbo-fall-000.x",
        subgame.player.presentation.cutscene_animation_slots[5].body.object);
    subgame.player.presentation.cutscene_animation_slots[6].body.SetObject(
        g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"turbo-damaged-000.x",
        subgame.player.presentation.cutscene_animation_slots[6].body.object);
    subgame.player.presentation.cutscene_animation_slots[7].body.SetObject(
        g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"turbo-intoshell-000.x",
        subgame.player.presentation.cutscene_animation_slots[7].body.object);
    subgame.player.presentation.cutscene_animation_slots[8].body.SetObject(
        g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"turbo-skidstop-000.x",
        subgame.player.presentation.cutscene_animation_slots[8].body.object);
    subgame.player.presentation.cutscene_animation_slots[9].body.SetObject(
        g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"turbo-talk-000.x",
        subgame.player.presentation.cutscene_animation_slots[9].body.object);

    subgame.player.presentation.snail_hotspot_body.SetObject(
        g_object_list.Add());
    loader->load_x_mesh(
        (char*)"TurboHotSpots.x",
        subgame.player.presentation.snail_hotspot_body.object,
        2);
    subgame.player.presentation.extract_snail_local_hotspots();

    int animation_count =
        sizeof(subgame.player.presentation.cutscene_animation_slots)
        / sizeof(subgame.player.presentation.cutscene_animation_slots[0]);
    PresentationAnimationSlot* animation_slot;
    int cutscene_animation_index = 0;
    do {
        Object* animation_object =
            subgame.player.presentation
                .cutscene_animation_slots[cutscene_animation_index]
                .body.object;
        animation_object->flags |= OBJECT_FLAG_DYNAMIC_VERTICES;
        animation_object->ApplyToon(0);
        animation_object->distort.z_wave = 0.0f;
        animation_object->distort.y_squash = 0.0f;
        animation_object->distort.xyz_scale = 0.0f;
        ++cutscene_animation_index;
    } while (--animation_count != 0);

    subgame.player.presentation.object->flags |= OBJECT_FLAG_DYNAMIC_VERTICES;
    subgame.player.presentation.object->ApplyToon(0);
    subgame.player.presentation.object->distort.z_wave = 0.0f;
    subgame.player.presentation.object->distort.y_squash = 0.0f;
    subgame.player.presentation.object->distort.xyz_scale = 0.0f;

    subgame.player.presentation.jetpack_channel.SetObject(
        g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"jetpack-base-000.x",
        subgame.player.presentation.jetpack_channel.object);
    subgame.player.presentation.jetpack_channel.animation_slots[0]
        .body.SetObject(
        g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"jetpack-base-000.x",
        subgame.player.presentation.jetpack_channel.animation_slots[0]
            .body.object);
    subgame.player.presentation.jetpack_channel.animation_slots[1]
        .body.SetObject(
        g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"jetpack-draw-000.x",
        subgame.player.presentation.jetpack_channel.animation_slots[1]
            .body.object);

    animation_count = 2;
    animation_slot =
        &subgame.player.presentation.jetpack_channel.animation_slots[0];
    do {
        Object* animation_object = animation_slot->body.object;
        animation_object->flags |= OBJECT_FLAG_DYNAMIC_VERTICES;
        animation_object->ApplyToon(0);
        animation_object->distort.z_wave = 0.0f;
        animation_object->distort.y_squash = 0.0f;
        animation_object->distort.xyz_scale = 0.0f;
        ++animation_slot;
    } while (--animation_count != 0);

    subgame.player.presentation.jetpack_channel.object->flags |=
        OBJECT_FLAG_DYNAMIC_VERTICES;
    subgame.player.presentation.jetpack_channel.object->ApplyToon(0);
    subgame.player.presentation.jetpack_channel.object->distort.z_wave = 0.0f;
    subgame.player.presentation.jetpack_channel.object->distort.y_squash = 0.0f;
    subgame.player.presentation.jetpack_channel.object->distort.xyz_scale = 0.0f;

    subgame.player.presentation.weapon_channels[0].SetObject(
        g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"blasterleft-base-000.x",
        subgame.player.presentation.weapon_channels[0].object);
    subgame.player.presentation.weapon_channels[0].animation_slots[0]
        .body.SetObject(g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"blasterleft-base-000.x",
        subgame.player.presentation.weapon_channels[0].animation_slots[0]
            .body.object);
    subgame.player.presentation.weapon_channels[0].animation_slots[1]
        .body.SetObject(g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"blasterleft-draw-000.x",
        subgame.player.presentation.weapon_channels[0].animation_slots[1]
            .body.object);
    subgame.player.presentation.weapon_channels[0].animation_slots[2]
        .body.SetObject(g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"blasterleft-fire-000.x",
        subgame.player.presentation.weapon_channels[0].animation_slots[2]
            .body.object);
    subgame.player.presentation.weapon_channels[0].animation_slots[3]
        .body.SetObject(g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"Laserleft-base-000.x",
        subgame.player.presentation.weapon_channels[0].animation_slots[3]
            .body.object);
    subgame.player.presentation.weapon_channels[0].animation_slots[4]
        .body.SetObject(g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"Laserleft-draw-000.x",
        subgame.player.presentation.weapon_channels[0].animation_slots[4]
            .body.object);

    animation_count =
        sizeof(subgame.player.presentation.weapon_channels[0].animation_slots)
        / sizeof(subgame.player.presentation.weapon_channels[0].animation_slots[0]);
    animation_slot =
        &subgame.player.presentation.weapon_channels[0].animation_slots[0];
    do {
        Object* animation_object = animation_slot->body.object;
        animation_object->flags |= OBJECT_FLAG_DYNAMIC_VERTICES;
        animation_object->ApplyToon(0);
        animation_object->distort.z_wave = 0.0f;
        animation_object->distort.y_squash = 0.0f;
        animation_object->distort.xyz_scale = 0.0f;
        ++animation_slot;
    } while (--animation_count != 0);

    subgame.player.presentation.weapon_channels[0].object->flags |=
        OBJECT_FLAG_DYNAMIC_VERTICES;
    subgame.player.presentation.weapon_channels[0].object->ApplyToon(0);
    subgame.player.presentation.weapon_channels[0].object->distort.z_wave = 0.0f;
    subgame.player.presentation.weapon_channels[0].object->distort.y_squash = 0.0f;
    subgame.player.presentation.weapon_channels[0].object->distort.xyz_scale = 0.0f;

    subgame.player.presentation.weapon_channels[1].SetObject(
        g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"blasterRight-base-000.x",
        subgame.player.presentation.weapon_channels[1].object);
    subgame.player.presentation.weapon_channels[1].animation_slots[0]
        .body.SetObject(g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"blasterRight-base-000.x",
        subgame.player.presentation.weapon_channels[1].animation_slots[0]
            .body.object);
    subgame.player.presentation.weapon_channels[1].animation_slots[1]
        .body.SetObject(g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"blasterRight-draw-000.x",
        subgame.player.presentation.weapon_channels[1].animation_slots[1]
            .body.object);
    subgame.player.presentation.weapon_channels[1].animation_slots[2]
        .body.SetObject(g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"blasterRight-fire-000.x",
        subgame.player.presentation.weapon_channels[1].animation_slots[2]
            .body.object);
    subgame.player.presentation.weapon_channels[1].animation_slots[3]
        .body.SetObject(g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"Laserright-base-000.x",
        subgame.player.presentation.weapon_channels[1].animation_slots[3]
            .body.object);
    subgame.player.presentation.weapon_channels[1].animation_slots[4]
        .body.SetObject(g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"Laserright-draw-000.x",
        subgame.player.presentation.weapon_channels[1].animation_slots[4]
            .body.object);

    animation_count =
        sizeof(subgame.player.presentation.weapon_channels[1].animation_slots)
        / sizeof(subgame.player.presentation.weapon_channels[1].animation_slots[0]);
    animation_slot =
        &subgame.player.presentation.weapon_channels[1].animation_slots[0];
    do {
        Object* animation_object = animation_slot->body.object;
        animation_object->flags |= OBJECT_FLAG_DYNAMIC_VERTICES;
        animation_object->ApplyToon(0);
        animation_object->distort.z_wave = 0.0f;
        animation_object->distort.y_squash = 0.0f;
        animation_object->distort.xyz_scale = 0.0f;
        ++animation_slot;
    } while (--animation_count != 0);

    subgame.player.presentation.weapon_channels[1].object->flags |=
        OBJECT_FLAG_DYNAMIC_VERTICES;
    subgame.player.presentation.weapon_channels[1].object->ApplyToon(0);
    subgame.player.presentation.weapon_channels[1].object->distort.z_wave = 0.0f;
    subgame.player.presentation.weapon_channels[1].object->distort.y_squash = 0.0f;
    subgame.player.presentation.weapon_channels[1].object->distort.xyz_scale = 0.0f;

    subgame.player.presentation.weapon_channels[2].SetObject(
        g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"blasterTop-base-000.x",
        subgame.player.presentation.weapon_channels[2].object);
    subgame.player.presentation.weapon_channels[2].animation_slots[0]
        .body.SetObject(g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"blasterTop-base-000.x",
        subgame.player.presentation.weapon_channels[2].animation_slots[0]
            .body.object);
    subgame.player.presentation.weapon_channels[2].animation_slots[1]
        .body.SetObject(g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"blasterTop-draw-000.x",
        subgame.player.presentation.weapon_channels[2].animation_slots[1]
            .body.object);
    subgame.player.presentation.weapon_channels[2].animation_slots[2]
        .body.SetObject(g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"blasterTop-fire-000.x",
        subgame.player.presentation.weapon_channels[2].animation_slots[2]
            .body.object);
    subgame.player.presentation.weapon_channels[2].animation_slots[3]
        .body.SetObject(g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"rocketlauncher-base-000.x",
        subgame.player.presentation.weapon_channels[2].animation_slots[3]
            .body.object);
    subgame.player.presentation.weapon_channels[2].animation_slots[4]
        .body.SetObject(g_object_list.Add());
    loader->load_x_animation_clip(
        (char*)"rocketlauncher-draw-000.x",
        subgame.player.presentation.weapon_channels[2].animation_slots[4]
            .body.object);

    animation_count =
        sizeof(subgame.player.presentation.weapon_channels[2].animation_slots)
        / sizeof(subgame.player.presentation.weapon_channels[2].animation_slots[0]);
    animation_slot =
        &subgame.player.presentation.weapon_channels[2].animation_slots[0];
    do {
        Object* animation_object = animation_slot->body.object;
        animation_object->flags |= OBJECT_FLAG_DYNAMIC_VERTICES;
        animation_object->ApplyToon(0);
        animation_object->distort.z_wave = 0.0f;
        animation_object->distort.y_squash = 0.0f;
        animation_object->distort.xyz_scale = 0.0f;
        ++animation_slot;
    } while (--animation_count != 0);

    subgame.player.presentation.weapon_channels[2].object->flags |=
        OBJECT_FLAG_DYNAMIC_VERTICES;
    subgame.player.presentation.weapon_channels[2].object->ApplyToon(0);
    subgame.player.presentation.weapon_channels[2].object->distort.z_wave = 0.0f;
    subgame.player.presentation.weapon_channels[2].object->distort.y_squash = 0.0f;
    subgame.player.presentation.weapon_channels[2].object->distort.xyz_scale = 0.0f;

    subgame.player.presentation.snail_skin
        .material_overrides[SNAIL_SKIN_SLOT_DEFAULT] =
        g_texture_refs.Add(
            (char*)"x/snail-turbo.tga", 0, 0);
    subgame.player.presentation.snail_skin
        .material_overrides[SNAIL_SKIN_SLOT_DAMAGE] =
        g_texture_refs.Add(
            (char*)"x/snail-turbo-damage.tga", 0, 0);
    subgame.player.presentation.snail_skin
        .material_overrides[SNAIL_SKIN_SLOT_INVINCIBLE] =
        g_texture_refs.Add(
            (char*)"x/snail-turbo-invincible.tga", 0, 0);

    subgame.player.presentation.invincible_shell.SetObject(
        g_object_list.Add());
    loader->load_x_mesh(
        (char*)"invincible-base-000.x",
        subgame.player.presentation.invincible_shell.object,
        1);
    subgame.player.presentation.invincible_shell.object->flags &=
        ~OBJECT_FLAG_DISABLE_CULLING;

    cRSubGolb* golb_shot = &subgame.player.golb_shots[0];
    golb_shot->tertiary_body.SetObject(
        g_object_list.Add());
    loader->load_x_mesh(
        (char*)"rocket-base-000.x", golb_shot->tertiary_body.object, 1);
    Object* rocket_object = golb_shot->tertiary_body.object;
    int golb_shot_count = 12;
    do {
        golb_shot->vapour.SetObject(
            g_object_list.Add());
        Object* vapour_object = golb_shot->vapour.object;
        vapour_object->flags |=
            OBJECT_FLAG_DISABLE_CULLING | OBJECT_FLAG_DYNAMIC_VERTICES;
        vapour_object->blend_mode = 9;
        load_object_definition((char*)"Objects/VapourLazer", vapour_object);
        golb_shot->vapour.Init(vapour_object, 0.159999996f);
        golb_shot->tertiary_body.SetObject(rocket_object);
        ++golb_shot;
    } while (--golb_shot_count != 0);

    cRTexture* texture_ref = g_texture_refs.Add(
        (char*)"Objects/VapourLazer/Lazer.tga", 0, 0);
    texture_ref->flags |= TEXTURE_REF_REGISTERED;
    texture_ref = g_texture_refs.Add(
        (char*)"Objects/World00/Worm.tga", 0, 0);
    texture_ref->flags |= 0x1403;
    texture_ref = g_texture_refs.Add(
        (char*)"Objects/World00/Back.tga", 0, 0);
    texture_ref->flags |= 0x1402;
    texture_ref = g_texture_refs.Add(
        (char*)"Objects/World00/TrackWarn.tga", 0, 0);
    texture_ref->flags = TEXTURE_REF_WRAP_ADDRESSING;
    texture_ref = g_texture_refs.Add(
        (char*)"Objects/Universe/Ramp.tga", 0, 0);
    texture_ref->flags |= TEXTURE_REF_WRAP_ADDRESSING;
    texture_ref = g_texture_refs.Add(
        (char*)"Objects/World00/Track0.tga", 0, 0);
    texture_ref->flags |= 0x1002;
    texture_ref = g_texture_refs.Add(
        (char*)"Objects/World00/Slide0.tga", 0, 0);
    texture_ref->flags |= 0x1002;
    texture_ref = g_texture_refs.Add(
        (char*)"Objects/World00/Track1.tga", 0, 0);
    texture_ref->flags |= 0x1002;
    texture_ref = g_texture_refs.Add(
        (char*)"Objects/World00/Slide1.tga", 0, 0);
    texture_ref->flags |= 0x1002;
    texture_ref = g_texture_refs.Add(
        (char*)"Objects/World00/Track2.tga", 0, 0);
    texture_ref->flags |= 0x1002;
    texture_ref = g_texture_refs.Add(
        (char*)"Objects/World00/Slide2.tga", 0, 0);
    texture_ref->flags |= 0x1002;
    texture_ref = g_texture_refs.Add(
        (char*)"Objects/World00/Track3.tga", 0, 0);
    texture_ref->flags |= 0x1002;
    texture_ref = g_texture_refs.Add(
        (char*)"Objects/World00/Slide3.tga", 0, 0);
    texture_ref->flags |= 0x1002;

    track.track_textures[0] =
        g_texture_refs.Add(
            (char*)"Objects/World00/Track0.tga", 0, 0);
    track.slide_textures[0] =
        g_texture_refs.Add(
            (char*)"Objects/World00/Slide0.tga", 0, 0);
    track.track_textures[1] =
        g_texture_refs.Add(
            (char*)"Objects/World00/Track1.tga", 0, 0);
    track.slide_textures[1] =
        g_texture_refs.Add(
            (char*)"Objects/World00/Slide1.tga", 0, 0);
    track.track_textures[2] =
        g_texture_refs.Add(
            (char*)"Objects/World00/Track2.tga", 0, 0);
    track.slide_textures[2] =
        g_texture_refs.Add(
            (char*)"Objects/World00/Slide2.tga", 0, 0);
    track.track_textures[3] =
        g_texture_refs.Add(
            (char*)"Objects/World00/Track3.tga", 0, 0);
    track.slide_textures[3] =
        g_texture_refs.Add(
            (char*)"Objects/World00/Slide3.tga", 0, 0);
    track.current_texture_set = 0;

    g_texture_refs.Add(
        (char*)"Objects/World00/Back.tga", 0, 0)->mip_levels = 2;
    g_texture_refs.Add(
        (char*)"Objects/World00/TrackWarn.tga", 0, 0)->mip_levels = 2;
    g_texture_refs.Add(
        (char*)"Objects/Universe/Ramp.tga", 0, 0)->mip_levels = 2;
    g_texture_refs.Add(
        (char*)"Objects/World00/Track0.tga", 0, 0)->mip_levels = 2;
    g_texture_refs.Add(
        (char*)"Objects/World00/Slide0.tga", 0, 0)->mip_levels = 2;
    g_texture_refs.Add(
        (char*)"Objects/World00/Track1.tga", 0, 0)->mip_levels = 2;
    g_texture_refs.Add(
        (char*)"Objects/World00/Slide1.tga", 0, 0)->mip_levels = 2;
    g_texture_refs.Add(
        (char*)"Objects/World00/Track2.tga", 0, 0)->mip_levels = 2;
    g_texture_refs.Add(
        (char*)"Objects/World00/Slide2.tga", 0, 0)->mip_levels = 2;
    g_texture_refs.Add(
        (char*)"Objects/World00/Track3.tga", 0, 0)->mip_levels = 2;
    g_texture_refs.Add(
        (char*)"Objects/World00/Slide3.tga", 0, 0)->mip_levels = 2;

    subgame.barrier.SetObject(g_object_list.Add());
    load_object_definition((char*)"Objects/Barrier", subgame.barrier.object);
    subgame.barrier.position.zero_vector3();
    subgame.barrier.color.store_color4f(1.0f, 1.0f, 1.0f, 0.800000012f);
    subgame.barrier.object->blend_mode = 7;
    subgame.segment_cache.initialize_track_render_cache_manager();

    BodBase* fringe_bod =
        &root_bod_catalog.fringe_catalog.entries[0][0][0][0];
    int fringe_family = 0;
    do {
        int fringe_direction = 0;
        do {
            int fringe_row = 0;
            do {
                int fringe_column = 0;
                do {
                    fringe_bod->SetObject(
                        g_object_list.Add());
                    initialize_backdrop_tile_quad(
                        fringe_bod->object,
                        fringe_family,
                        fringe_direction,
                        fringe_row - 1,
                        fringe_column - 1,
                        (char*)"Objects/Universe/Fringe.tga");
                    fringe_bod->object->blend_mode = 5;
                    ++fringe_column;
                    ++fringe_bod;
                } while (fringe_column < TRACK_FRINGE_EDGE_VARIANT_COUNT);
                ++fringe_row;
            } while (fringe_row < TRACK_FRINGE_EDGE_VARIANT_COUNT);
            ++fringe_direction;
        } while (fringe_direction < TRACK_FRINGE_DIRECTION_COUNT);
        ++fringe_family;
    } while (fringe_family < TRACK_FRINGE_FAMILY_COUNT);

    g_texture_refs.Add(
        (char*)"Objects/Universe/Fringe.tga", 0, 0)->flags |=
        TEXTURE_REF_REGISTERED;

    BodList* active_bods = &active_bod_list;
    GameInput* game_input = &game_inputs[0];
    int input_index = 0;
    do {
        active_bods->add_bod_to_front(game_input);
        game_input->input.controller_slot = input_index;
        game_input->input.initialize_input();
        ++input_index;
        ++game_input;
    } while (input_index < GAME_ROOT_PLAYER_SLOT_COUNT);

    int player_index = 0;
    if (player_count > 0) {
        do {
            set_matrix_identity(&players[player_index].transform);
            set_matrix_identity(&players[player_index].camera.transform);
            players[player_index].camera.fov_degrees = 110.0f;
            players[player_index].game_input = &game_inputs[player_index];
            players[player_index].transform =
                *transform.initialize_matrix_from_values(
                0.0733430013f, 0.0f, -0.997310996f, 0.0f,
                0.152129993f, 0.988296986f, 0.0111880004f, 0.0f,
                0.985638976f, -0.152539998f, 0.0724840015f, 0.0f,
                -8.62666702f, 3.11352801f, 4.47740698f, 1.0f);
            players[player_index].frontend_overlay.Init(
                0x1000000);
            players[player_index].mouse_cursor.SetInActive();
            players[player_index].mouse_cursor.suppress_next_draw = 0;
            if (player_index == 0)
                players[0].frontend_state = 12;
            players[player_index].high_score_entry_pending = 0;
            players[player_index].selected_high_score_rank = 0;
            rstrcpy_checked_ascii(
                players[player_index].player_name,
                g_runtime_config.last_entered_player_name);
            ++player_index;
        } while (player_index < player_count);
    }

    subgame.sub_high_score.Init();
    subgame.sub_high_score.load_high_scores_from_file((char*)"ScoreA.dat");
    subgame.sub_high_score.load_high_scores_from_file((char*)"ScoreB.dat");
    subgame.sub_high_score.load_high_scores_from_file((char*)"ScoreC.dat");
    subgame.selected_level_record_persistent = 0;
    subgame.selected_level_record_active = 0;

    tip_manager.Init();
    active_bods->add_bod_to_front(&tip_manager);
    g_game->active_bod_list.add_bod_to_front(
        (BodNode*)&star_manager);
    star_manager.Open(36);
    subgame.bottom_score_widget = 0;
    subgame.top_score_widget = 0;
    active_bods->add_bod_to_front(&backdrop);
    backdrop.backdrop_render_enabled = 0;
    active_bods->append_bod_to_end(&border_manager);
    border_manager.border_stack.initialize_border_stack();
    border_manager.border_stack.owner = &border_manager;
    border_manager.delayed_widget_active = 0;
    border_manager.set_border_justify_centre(25.0f);

    BorderRecord* border = &border_manager.borders[0];
    int border_count = BORDER_RECORD_COUNT;
    do {
        border->flags = 0;
        ++border;
        --border_count;
    } while (border_count != 0);

    g_object_list.BuildObjects();

    set_object_color(
        subgame.path_pairs[51].primary.object, path_transition_color);
    set_object_color(
        subgame.path_pairs[51].secondary.object, path_transition_color);
    set_object_color(
        subgame.path_pairs[52].primary.object, path_transition_color);
    set_object_color(
        subgame.path_pairs[52].secondary.object, path_transition_color);
    set_object_color(
        subgame.path_pairs[53].primary.object, path_transition_color);
    set_object_color(
        subgame.path_pairs[53].secondary.object, path_transition_color);
    set_object_color(
        subgame.path_pairs[57].primary.object, path_transition_color);
    set_object_color(
        subgame.path_pairs[57].secondary.object, path_transition_color);
    set_object_color(
        subgame.path_pairs[54].primary.object, path_transition_color);
    set_object_color(
        subgame.path_pairs[54].secondary.object, path_transition_color);
    set_object_color(
        subgame.path_pairs[55].primary.object, path_transition_color);
    set_object_color(
        subgame.path_pairs[55].secondary.object, path_transition_color);
    set_object_color(
        subgame.path_pairs[56].primary.object, path_transition_color);
    set_object_color(
        subgame.path_pairs[56].secondary.object, path_transition_color);
    set_object_color(
        subgame.path_pairs[58].primary.object, path_transition_color);
    set_object_color(
        subgame.path_pairs[58].secondary.object, path_transition_color);
    set_object_color(
        subgame.path_pairs[62].primary.object, path_transition_color);
    set_object_color(
        subgame.path_pairs[62].secondary.object, path_transition_color);
    set_object_color(
        subgame.path_pairs[59].primary.object, path_transition_color);
    set_object_color(
        subgame.path_pairs[59].secondary.object, path_transition_color);
    set_object_color(
        subgame.path_pairs[61].primary.object, path_transition_color);
    set_object_color(
        subgame.path_pairs[61].secondary.object, path_transition_color);
    set_object_color(
        subgame.path_pairs[60].primary.object, path_transition_color);
    set_object_color(
        subgame.path_pairs[60].secondary.object, path_transition_color);

    set_input_controller_pointer_authored_xy(0, 320.0f, 240.0f);
    set_input_controller_pointer_authored_xy(1, 320.0f, 240.0f);
    subgame.subgame_rebuild_selector = 2;

    return 1;
}
