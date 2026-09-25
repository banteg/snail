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
void FontInit(); // @ 0x449c70
void FontMake3D(short font_id); // @ 0x44ae10
void register_font_texture_sheet_wrapper(
    char* font_path,
    int shadow_offset_pixels,
    float width_scale,
    float height_scale); // @ 0x432d20
void ObjectProcTileFloorFast(Object* object, char* texture_path, float x_offset); // @ 0x41a1c0
void ObjectProcTileFast(Object* object, char* texture_path, float x_offset); // @ 0x41a0b0
void ObjectProcTileFastRamp(int edge_pair, Object* object); // @ 0x41a170
void ObjectProcTileFloorCornerFast(int corner, Object* object, char* texture_path); // @ 0x41a290
void ObjectProcFringe(
    Object* object,
    int edge_selector,
    int orientation,
    int row_selector,
    int column_selector,
    char* texture_path); // @ 0x41a4d0
void set_object_color(Object* object, tColour color); // @ 0x4141d0
void set_input_controller_pointer_authored_xy(
    int controller,
    float authored_x,
    float authored_y); // @ 0x4323a0
static __forceinline void link_root_bod(BodNode& node)
{
    BodList* list = &g_game->active_bod_list;
    if ((node.list_flags & BOD_FLAG_LINKED) != 0) {
        report_errorf((char*)"List ADD");
    } else {
        if (list->first == 0) {
            list->first = &node;
            node.list_prev = 0;
            list->first->list_next = 0;
        } else {
            list->first->list_prev = &node;
            list->first->list_prev->list_next = list->first;
            list->first = list->first->list_prev;
            list->first->list_prev = 0;
        }
        node.list_flags |= BOD_FLAG_LINKED;
    }
}

static __forceinline void zero_position(tVector& position)
{
    position.z = 0.0f;
    position.y = 0.0f;
    position.x = 0.0f;
}

char cRGame::initialize_game_assets_and_world()
{
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
    BodNode* inactive_node = &inactive_bod_sentinel;
    inactive_node->list_next = 0;
    active_bod_list.free_top = inactive_node;
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
    link_root_bod(overlay_0);
    overlay_0.Init();

    memset(g_directx_loader_scratch, 0, 0x15c);
    cRDirectX* loader = &directx_loader;
    loader->Init();
    cRLandscapeManager* landscape = &subgame.landscape_manager;
    landscape->Open();
    cRSMTracks* sm_tracks = &subgame.sm_tracks;
    sm_tracks->Import();
    landscape->Import((char*)"Starmap.txt");
    landscape->Import((char*)"Splash.txt");
    landscape->Import(g_help_script_path);

    subgame.level_mode_arg = g_runtime_config.landscape_backdrop_variant_selector;
    subgame.gui.Open();
    subgame.splash.Open();
    subgame.galaxy.Open();
    subgame.player.cameraman.Init();
    logo.Open();
    g_sound_effect_manager.Init(g_sound_bank_entries);
    g_voice_manager.Init();
    options.apply_audio_config_volumes();
    sm_tracks->OpenLevels();
    g_game->subgame.landscape_manager
        .Import(g_menu_background_script_path);
    subgame.level_definition_scratch.Init(
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
    link_root_bod(overlay_2);
    overlay_2.Init();

    viewports[2].sort_key = 2;
    viewports[2].flags = RENDER_SCENE_OVERLAY_1 | 3;
    viewports[2].camera = &overlay_1.camera;
    viewports[2].viewport_x = 0.0f;
    viewports[2].viewport_y = 0.0f;
    viewports[2].viewport_width = 1.0f;
    viewports[2].viewport_height = 1.0f;
    link_root_bod(overlay_1);
    overlay_1.Init();

    register_font_texture_sheet_wrapper((char*)"Objects/Font/Font-menu-hover.tga", 2, 0.75f, 1.0f);
    FontMake3D(0);
    FontInit();
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
        ObjectProcTileFloorFast(
            floor_slice->object, (char*)"Objects/World00/Track0.tga", slice_index);

        BodBase* warning_slice = &root_bod_catalog.warning_slices.storage[storage_index];
        warning_slice->SetObject(g_object_list.Add());
        ObjectProcTileFloorFast(
            warning_slice->object, (char*)"Objects/World00/TrackWarn.tga", slice_index);

        BodBase* slide_slice = &root_bod_catalog.slide_slices.storage[storage_index];
        slide_slice->SetObject(g_object_list.Add());
        ObjectProcTileFloorFast(
            root_bod_catalog.slide_slices.storage[storage_index].object,
            (char*)"Objects/World00/Slide0.tga",
            slice_index);
        slice_index += 1.0f;
    } while (slice_index < 8.0f);

    TransformMatrix transform;
    transform.Identity();

    BodBase* pillar = &root_bod_catalog.pillars[0];
    pillar->SetObject(g_object_list.Add());
    loader->Load((char*)"pillar1.x", root_bod_catalog.pillars[0].object, 1);
    transform.position.x = 0.0f;
    pillar->ApplyPos(transform);

    pillar = &root_bod_catalog.pillars[1];
    pillar->SetObject(g_object_list.Add());
    loader->Load((char*)"pillar2.x", root_bod_catalog.pillars[1].object, 1);
    transform.position.x = 0.5f;
    pillar->ApplyPos(transform);

    pillar = &root_bod_catalog.pillars[2];
    pillar->SetObject(g_object_list.Add());
    loader->Load((char*)"pillar3.x", root_bod_catalog.pillars[2].object, 1);
    transform.position.x = 1.0f;
    pillar->ApplyPos(transform);

    pillar = &root_bod_catalog.pillars[3];
    pillar->SetObject(g_object_list.Add());
    loader->Load((char*)"pillar4.x", root_bod_catalog.pillars[3].object, 1);
    transform.position.x = 1.5f;
    pillar->ApplyPos(transform);

    pillar = &root_bod_catalog.pillars[4];
    pillar->SetObject(g_object_list.Add());
    loader->Load((char*)"pillar5.x", root_bod_catalog.pillars[4].object, 1);
    transform.position.x = 2.0f;
    pillar->ApplyPos(transform);

    pillar = &root_bod_catalog.pillars[5];
    pillar->SetObject(g_object_list.Add());
    loader->Load((char*)"pillar6.x", root_bod_catalog.pillars[5].object, 1);
    transform.position.x = 2.5f;
    pillar->ApplyPos(transform);

    pillar = &root_bod_catalog.pillars[6];
    pillar->SetObject(g_object_list.Add());
    loader->Load((char*)"pillar7.x", root_bod_catalog.pillars[6].object, 1);
    transform.position.x = 3.0f;
    pillar->ApplyPos(transform);

    pillar = &root_bod_catalog.pillars[7];
    pillar->SetObject(g_object_list.Add());
    loader->Load((char*)"pillar8.x", root_bod_catalog.pillars[7].object, 1);
    transform.position.x = 3.5f;
    pillar->ApplyPos(transform);

    root_bod_catalog.ramp_edges[0].SetObject(g_object_list.Add());
    ObjectProcTileFast(
        root_bod_catalog.ramp_edges[0].object, (char*)"Objects/Universe/Ramp.tga", 0.0f);
    ObjectProcTileFastRamp(-1, root_bod_catalog.ramp_edges[0].object);

    root_bod_catalog.ramp_edges[1].SetObject(g_object_list.Add());
    ObjectProcTileFast(
        root_bod_catalog.ramp_edges[1].object, (char*)"Objects/Universe/Ramp.tga", 0.0f);
    ObjectProcTileFastRamp(0, root_bod_catalog.ramp_edges[1].object);

    root_bod_catalog.ramp_edges[2].SetObject(g_object_list.Add());
    ObjectProcTileFast(
        root_bod_catalog.ramp_edges[2].object, (char*)"Objects/Universe/Ramp.tga", 0.0f);
    ObjectProcTileFastRamp(1, root_bod_catalog.ramp_edges[2].object);

    root_bod_catalog.floor_corners.storage[TRACK_CORNER_0_STORAGE_INDEX].SetObject(g_object_list.Add());
    ObjectProcTileFloorCornerFast(
        0, root_bod_catalog.floor_corners.storage[TRACK_CORNER_0_STORAGE_INDEX].object, (char*)"Objects/World00/Track0.tga");
    root_bod_catalog.floor_corners.storage[TRACK_CORNER_1_STORAGE_INDEX].SetObject(g_object_list.Add());
    ObjectProcTileFloorCornerFast(
        1, root_bod_catalog.floor_corners.storage[TRACK_CORNER_1_STORAGE_INDEX].object, (char*)"Objects/World00/Track0.tga");
    root_bod_catalog.floor_corners.storage[TRACK_CORNER_2_STORAGE_INDEX].SetObject(g_object_list.Add());
    ObjectProcTileFloorCornerFast(
        2, root_bod_catalog.floor_corners.storage[TRACK_CORNER_2_STORAGE_INDEX].object, (char*)"Objects/World00/Track0.tga");
    root_bod_catalog.floor_corners.storage[TRACK_CORNER_3_STORAGE_INDEX].SetObject(g_object_list.Add());
    ObjectProcTileFloorCornerFast(
        3, root_bod_catalog.floor_corners.storage[TRACK_CORNER_3_STORAGE_INDEX].object, (char*)"Objects/World00/Track0.tga");

    root_bod_catalog.warning_corners.storage[TRACK_CORNER_0_STORAGE_INDEX].SetObject(g_object_list.Add());
    ObjectProcTileFloorCornerFast(
        0, root_bod_catalog.warning_corners.storage[TRACK_CORNER_0_STORAGE_INDEX].object, (char*)"Objects/World00/TrackWarn.tga");
    root_bod_catalog.warning_corners.storage[TRACK_CORNER_1_STORAGE_INDEX].SetObject(g_object_list.Add());
    ObjectProcTileFloorCornerFast(
        1, root_bod_catalog.warning_corners.storage[TRACK_CORNER_1_STORAGE_INDEX].object, (char*)"Objects/World00/TrackWarn.tga");
    root_bod_catalog.warning_corners.storage[TRACK_CORNER_2_STORAGE_INDEX].SetObject(g_object_list.Add());
    ObjectProcTileFloorCornerFast(
        2, root_bod_catalog.warning_corners.storage[TRACK_CORNER_2_STORAGE_INDEX].object, (char*)"Objects/World00/TrackWarn.tga");
    root_bod_catalog.warning_corners.storage[TRACK_CORNER_3_STORAGE_INDEX].SetObject(g_object_list.Add());
    ObjectProcTileFloorCornerFast(
        3, root_bod_catalog.warning_corners.storage[TRACK_CORNER_3_STORAGE_INDEX].object, (char*)"Objects/World00/TrackWarn.tga");

    root_bod_catalog.slide_corners.storage[TRACK_CORNER_0_STORAGE_INDEX].SetObject(g_object_list.Add());
    ObjectProcTileFloorCornerFast(
        0, root_bod_catalog.slide_corners.storage[TRACK_CORNER_0_STORAGE_INDEX].object, (char*)"Objects/World00/Slide0.tga");
    root_bod_catalog.slide_corners.storage[TRACK_CORNER_1_STORAGE_INDEX].SetObject(g_object_list.Add());
    ObjectProcTileFloorCornerFast(
        1, root_bod_catalog.slide_corners.storage[TRACK_CORNER_1_STORAGE_INDEX].object, (char*)"Objects/World00/Slide0.tga");
    root_bod_catalog.slide_corners.storage[TRACK_CORNER_2_STORAGE_INDEX].SetObject(g_object_list.Add());
    ObjectProcTileFloorCornerFast(
        2, root_bod_catalog.slide_corners.storage[TRACK_CORNER_2_STORAGE_INDEX].object, (char*)"Objects/World00/Slide0.tga");
    root_bod_catalog.slide_corners.storage[TRACK_CORNER_3_STORAGE_INDEX].SetObject(g_object_list.Add());
    ObjectProcTileFloorCornerFast(
        3, root_bod_catalog.slide_corners.storage[TRACK_CORNER_3_STORAGE_INDEX].object, (char*)"Objects/World00/Slide0.tga");

    root_bod_catalog.trampoline.SetObject(g_object_list.Add());
    loader->Load((char*)"Tramp.x", root_bod_catalog.trampoline.object, 1);
    root_bod_catalog.trampoline.object->blend_mode = 6;
    root_bod_catalog.trampoline.object->facequads[0].texture_ref->flags |= TEXTURE_REF_REGISTERED;

    root_bod_catalog.universe_hole.SetObject(g_object_list.Add());
    ObjectProcTileFast(
        root_bod_catalog.universe_hole.object, (char*)"Objects/Universe/Hole.tga", 0.0f);
    root_bod_catalog.universe_hole.object->blend_mode = 5;
    root_bod_catalog.universe_hole.object->facequads[0].texture_ref->flags |= TEXTURE_REF_REGISTERED;

    root_bod_catalog.lazer_model.SetObject(g_object_list.Add());
    load_object_definition((char*)"Objects/Lazer", root_bod_catalog.lazer_model.object);

    enum {
        SUB_LAZER_SLOT_COUNT =
            sizeof(((cRSubLazerManager*)0)->slots)
            / sizeof(((cRSubLazerManager*)0)->slots[0]),
        BANNER_SLOT_COUNT =
            sizeof(((BannerPool*)0)->slots) / sizeof(((BannerPool*)0)->slots[0])
    };
    for (int sub_lazer_index = 0; sub_lazer_index < SUB_LAZER_SLOT_COUNT; sub_lazer_index++) {
        subgame.sub_lazers.slots[sub_lazer_index].SetObject(root_bod_catalog.lazer_model.object);
        subgame.sub_lazers.slots[sub_lazer_index].object->facequads[0].texture_ref->flags |=
            TEXTURE_REF_REGISTERED;
        subgame.sub_lazers.slots[sub_lazer_index].owner_game = &subgame;
        subgame.sub_lazers.slots[sub_lazer_index].color.store_color4f(1.0f, 1.0f, 1.0f, 0.7f);
        subgame.sub_lazers.slots[sub_lazer_index].object->blend_mode = 9;
    }

    root_bod_catalog.salt_model.SetObject(g_object_list.Add());
    loader->Load((char*)"salt.x", root_bod_catalog.salt_model.object, 1);

    for (int salt_index = 0; salt_index < 40; salt_index++) {
        subgame.salt_hazards.slots[salt_index].SetObject(root_bod_catalog.salt_model.object);
        subgame.salt_hazards.slots[salt_index].owner_game = &subgame;
        subgame.salt_hazards.slots[salt_index].color.store_color4f(1.0f, 1.0f, 1.0f, 0.9f);
        subgame.salt_hazards.slots[salt_index].object->blend_mode = 12;
        subgame.salt_hazards.slots[salt_index].transform.Identity();
    }

    for (int banner_index = 0; banner_index < BANNER_SLOT_COUNT; banner_index++) {
        subgame.banners.slots[banner_index].SetObject(g_object_list.Add());
        if (banner_index == 0) {
            loader->Load(
                (char*)"postofficestop.x",
                subgame.banners.slots[0].object,
                1);
        }
        if (banner_index == 1) {
            loader->Load(
                (char*)"postofficestop.x",
                subgame.banners.slots[1].object,
                banner_index);
        }
        zero_position(subgame.banners.slots[banner_index].position);
        subgame.banners.slots[banner_index].owner_game = &subgame;
        subgame.banners.slots[banner_index].visibility_mode = banner_index;
        subgame.banners.slots[banner_index].phase = 0.0f;
        subgame.banners.slots[banner_index].phase_step = 0.006944444f;
    }

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
    zero_position(subgame.path_pairs[0].primary.position);

    subgame.path_pairs[0].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[0].secondary.Mirror(path);
    zero_position(subgame.path_pairs[0].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[0].primary.fringe_mesh_bod.position);
    subgame.path_pairs[0].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[0].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[1].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_looptheloop_path_template_pair(
        6.0f,
        2,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[1].primary.position);

    subgame.path_pairs[1].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[1].secondary.Mirror(path);
    zero_position(subgame.path_pairs[1].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[1].primary.fringe_mesh_bod.position);
    subgame.path_pairs[1].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[1].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[2].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_looptheloop_path_template_pair(
        8.0f,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[2].primary.position);

    subgame.path_pairs[2].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[2].secondary.Mirror(path);
    zero_position(subgame.path_pairs[2].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[2].primary.fringe_mesh_bod.position);
    subgame.path_pairs[2].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[2].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[6].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_looptheloopw_path_template_pair(
        8.0f,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[6].primary.position);

    subgame.path_pairs[6].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[6].secondary.Mirror(path);
    zero_position(subgame.path_pairs[6].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[6].primary.fringe_mesh_bod.position);
    subgame.path_pairs[6].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[6].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[3].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_looptheloop_path_template_pair(
        3.0f,
        2,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[3].primary.position);

    subgame.path_pairs[3].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[3].secondary.Mirror(path);
    zero_position(subgame.path_pairs[3].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[3].primary.fringe_mesh_bod.position);
    subgame.path_pairs[3].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[3].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[4].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_looptheloop_path_template_pair(
        3.0f,
        3,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[4].primary.position);

    subgame.path_pairs[4].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[4].secondary.Mirror(path);
    zero_position(subgame.path_pairs[4].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[4].primary.fringe_mesh_bod.position);
    subgame.path_pairs[4].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[4].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[5].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_looptheloop_path_template_pair(
        3.0f,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[5].primary.position);

    subgame.path_pairs[5].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[5].secondary.Mirror(path);
    zero_position(subgame.path_pairs[5].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[5].primary.fringe_mesh_bod.position);
    subgame.path_pairs[5].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[5].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[7].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_loopbow_path_template_pair(
        6.0f,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[7].primary.position);

    subgame.path_pairs[7].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[7].secondary.Mirror(path);
    zero_position(subgame.path_pairs[7].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[7].primary.fringe_mesh_bod.position);
    subgame.path_pairs[7].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[7].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[37].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_turnover_path_template_pair(
        6.0f,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[37].primary.position);

    subgame.path_pairs[37].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[37].secondary.Mirror(path);
    zero_position(subgame.path_pairs[37].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[37].primary.fringe_mesh_bod.position);
    subgame.path_pairs[37].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[37].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[38].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_turnoverdouble_path_template_pair(
        6.0f,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[38].primary.position);

    subgame.path_pairs[38].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[38].secondary.Mirror(path);
    zero_position(subgame.path_pairs[38].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[38].primary.fringe_mesh_bod.position);
    subgame.path_pairs[38].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[38].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[43].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_twister_path_template_pair(
        2.5f,
        3,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[43].primary.position);

    subgame.path_pairs[43].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[43].secondary.Mirror(path);
    zero_position(subgame.path_pairs[43].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[43].primary.fringe_mesh_bod.position);
    subgame.path_pairs[43].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[43].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[44].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_twister_path_template_pair(
        2.5f,
        3,
        0,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[44].primary.position);

    subgame.path_pairs[44].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[44].secondary.Mirror(path);
    zero_position(subgame.path_pairs[44].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[44].primary.fringe_mesh_bod.position);
    subgame.path_pairs[44].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[44].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[45].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_twister2_path_template_pair(
        2.5f,
        3,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[45].primary.position);

    subgame.path_pairs[45].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[45].secondary.Mirror(path);
    zero_position(subgame.path_pairs[45].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[45].primary.fringe_mesh_bod.position);
    subgame.path_pairs[45].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[45].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[46].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_twister2_path_template_pair(
        2.5f,
        3,
        0,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[46].primary.position);

    subgame.path_pairs[46].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[46].secondary.Mirror(path);
    zero_position(subgame.path_pairs[46].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[46].primary.fringe_mesh_bod.position);
    subgame.path_pairs[46].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[46].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[39].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_turnunder_path_template_pair(
        6.0f,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[39].primary.position);

    subgame.path_pairs[39].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[39].secondary.Mirror(path);
    zero_position(subgame.path_pairs[39].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[39].primary.fringe_mesh_bod.position);
    subgame.path_pairs[39].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[39].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[41].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_invert_path_template_pair(
        6.0f,
        8,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[41].primary.position);

    subgame.path_pairs[41].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[41].secondary.Mirror(path);
    zero_position(subgame.path_pairs[41].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[41].primary.fringe_mesh_bod.position);
    subgame.path_pairs[41].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[41].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[42].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_halfpipe_path_template_pair(
        6.0f,
        8,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[42].primary.position);

    subgame.path_pairs[42].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[42].secondary.Mirror(path);
    zero_position(subgame.path_pairs[42].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[42].primary.fringe_mesh_bod.position);
    subgame.path_pairs[42].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[42].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[40].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_wibble_path_template_pair(
        6.0f,
        8,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[40].primary.position);

    subgame.path_pairs[40].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[40].secondary.Mirror(path);
    zero_position(subgame.path_pairs[40].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[40].primary.fringe_mesh_bod.position);
    subgame.path_pairs[40].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[40].secondary.fringe_mesh_bod.position);

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
    zero_position(subgame.path_pairs[31].primary.position);
    path->build_track_fringe_supertramp_mesh(
        (char*)"Objects/Universe/Fringe.tga");
    zero_position(subgame.path_pairs[31].primary.fringe_mesh_bod.position);

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
    zero_position(subgame.path_pairs[31].secondary.position);
    path->build_track_fringe_supertramp_mesh(
        (char*)"Objects/Universe/Fringe.tga");
    zero_position(subgame.path_pairs[31].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[36].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_start_path_template_pair(
        4.0f,
        8,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[36].primary.position);
    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[36].primary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[36].secondary;
    path->SetObject(g_object_list.Add());
    path->initialize_start_path_template_pair(
        4.0f,
        8,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Slidex.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[36].secondary.position);
    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[36].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[25].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_loopout_path_template_pair(
        3.0f,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[25].primary.position);

    subgame.path_pairs[25].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[25].secondary.Mirror(path);
    zero_position(subgame.path_pairs[25].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[25].primary.fringe_mesh_bod.position);
    subgame.path_pairs[25].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[25].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[27].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_loopout_path_template_pair(
        5.0f,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[27].primary.position);

    subgame.path_pairs[27].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[27].secondary.Mirror(path);
    zero_position(subgame.path_pairs[27].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[27].primary.fringe_mesh_bod.position);
    subgame.path_pairs[27].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[27].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[26].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_loopout_path_template_pair(
        3.0f,
        3,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[26].primary.position);

    subgame.path_pairs[26].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[26].secondary.Mirror(path);
    zero_position(subgame.path_pairs[26].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[26].primary.fringe_mesh_bod.position);
    subgame.path_pairs[26].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[26].secondary.fringe_mesh_bod.position);

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
    zero_position(subgame.path_pairs[16].primary.position);

    subgame.path_pairs[16].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[16].secondary.Mirror(path);
    zero_position(subgame.path_pairs[16].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[16].primary.fringe_mesh_bod.position);
    subgame.path_pairs[16].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[16].secondary.fringe_mesh_bod.position);

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
    zero_position(subgame.path_pairs[17].primary.position);

    subgame.path_pairs[17].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[17].secondary.Mirror(path);
    zero_position(subgame.path_pairs[17].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[17].primary.fringe_mesh_bod.position);
    subgame.path_pairs[17].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[17].secondary.fringe_mesh_bod.position);

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
    zero_position(subgame.path_pairs[18].primary.position);

    subgame.path_pairs[18].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[18].secondary.Mirror(path);
    zero_position(subgame.path_pairs[18].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[18].primary.fringe_mesh_bod.position);
    subgame.path_pairs[18].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[18].secondary.fringe_mesh_bod.position);

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
    zero_position(subgame.path_pairs[19].primary.position);

    subgame.path_pairs[19].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[19].secondary.Mirror(path);
    zero_position(subgame.path_pairs[19].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[19].primary.fringe_mesh_bod.position);
    subgame.path_pairs[19].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[19].secondary.fringe_mesh_bod.position);

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
    zero_position(subgame.path_pairs[8].primary.position);

    subgame.path_pairs[8].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[8].secondary.Mirror(path);
    zero_position(subgame.path_pairs[8].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[8].primary.fringe_mesh_bod.position);
    subgame.path_pairs[8].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[8].secondary.fringe_mesh_bod.position);

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
    zero_position(subgame.path_pairs[10].primary.position);

    subgame.path_pairs[10].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[10].secondary.Mirror(path);
    zero_position(subgame.path_pairs[10].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[10].primary.fringe_mesh_bod.position);
    subgame.path_pairs[10].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[10].secondary.fringe_mesh_bod.position);

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
    zero_position(subgame.path_pairs[9].primary.position);

    subgame.path_pairs[9].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[9].secondary.Mirror(path);
    zero_position(subgame.path_pairs[9].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[9].primary.fringe_mesh_bod.position);
    subgame.path_pairs[9].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[9].secondary.fringe_mesh_bod.position);

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
    zero_position(subgame.path_pairs[14].primary.position);

    subgame.path_pairs[14].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[14].secondary.Mirror(path);
    zero_position(subgame.path_pairs[14].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[14].primary.fringe_mesh_bod.position);
    subgame.path_pairs[14].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[14].secondary.fringe_mesh_bod.position);

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
    zero_position(subgame.path_pairs[11].primary.position);

    subgame.path_pairs[11].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[11].secondary.Mirror(path);
    zero_position(subgame.path_pairs[11].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[11].primary.fringe_mesh_bod.position);
    subgame.path_pairs[11].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[11].secondary.fringe_mesh_bod.position);

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
    zero_position(subgame.path_pairs[13].primary.position);

    subgame.path_pairs[13].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[13].secondary.Mirror(path);
    zero_position(subgame.path_pairs[13].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[13].primary.fringe_mesh_bod.position);
    subgame.path_pairs[13].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[13].secondary.fringe_mesh_bod.position);

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
    zero_position(subgame.path_pairs[12].primary.position);

    subgame.path_pairs[12].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[12].secondary.Mirror(path);
    zero_position(subgame.path_pairs[12].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[12].primary.fringe_mesh_bod.position);
    subgame.path_pairs[12].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[12].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[20].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_dip_path_template_pair(
        4.0f,
        2,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[20].primary.position);

    subgame.path_pairs[20].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[20].secondary.Mirror(path);
    zero_position(subgame.path_pairs[20].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[20].primary.fringe_mesh_bod.position);
    subgame.path_pairs[20].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[20].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[21].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_screw_path_template_pair(
        0x18,
        3,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[21].primary.position);

    subgame.path_pairs[21].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[21].secondary.Mirror(path);
    zero_position(subgame.path_pairs[21].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[21].primary.fringe_mesh_bod.position);
    subgame.path_pairs[21].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[21].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[22].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_slalom_path_template_pair(
        0x20,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[22].primary.position);

    subgame.path_pairs[22].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[22].secondary.Mirror(path);
    zero_position(subgame.path_pairs[22].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[22].primary.fringe_mesh_bod.position);
    subgame.path_pairs[22].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[22].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[23].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_slalombig_path_template_pair(
        0x20,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[23].primary.position);

    subgame.path_pairs[23].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[23].secondary.Mirror(path);
    zero_position(subgame.path_pairs[23].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[23].primary.fringe_mesh_bod.position);
    subgame.path_pairs[23].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[23].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[32].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_slalomdouble_path_template_pair(
        0x20,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[32].primary.position);

    subgame.path_pairs[32].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[32].secondary.Mirror(path);
    zero_position(subgame.path_pairs[32].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[32].primary.fringe_mesh_bod.position);
    subgame.path_pairs[32].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[32].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[24].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_worm_path_template_pair(
        (char*)"Objects/World00/Worm.tga");
    zero_position(subgame.path_pairs[24].primary.position);

    subgame.path_pairs[24].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[24].secondary.Mirror(path);
    zero_position(subgame.path_pairs[24].secondary.position);

    subgame.path_pairs[24].primary.fringe_mesh_bod.SetObject(
        g_object_list.Add());
    ObjectProcNull(
        subgame.path_pairs[24].primary.fringe_mesh_bod.object);
    subgame.path_pairs[24].secondary.fringe_mesh_bod.SetObject(
        g_object_list.Add());
    ObjectProcNull(
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
    zero_position(subgame.path_pairs[28].primary.position);

    subgame.path_pairs[28].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[28].secondary.Mirror(path);
    zero_position(subgame.path_pairs[28].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[28].primary.fringe_mesh_bod.position);
    subgame.path_pairs[28].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[28].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[15].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_cage2_path_template_pair(
        3,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[15].primary.position);

    subgame.path_pairs[15].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[15].secondary.Mirror(path);
    zero_position(subgame.path_pairs[15].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[15].primary.fringe_mesh_bod.position);
    subgame.path_pairs[15].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[15].secondary.fringe_mesh_bod.position);

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
    zero_position(subgame.path_pairs[33].primary.position);

    subgame.path_pairs[33].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[33].secondary.Mirror(path);
    zero_position(subgame.path_pairs[33].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[33].primary.fringe_mesh_bod.position);
    subgame.path_pairs[33].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[33].secondary.fringe_mesh_bod.position);

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
    zero_position(subgame.path_pairs[34].primary.position);

    subgame.path_pairs[34].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[34].secondary.Mirror(path);
    zero_position(subgame.path_pairs[34].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[34].primary.fringe_mesh_bod.position);
    subgame.path_pairs[34].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[34].secondary.fringe_mesh_bod.position);

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
    zero_position(subgame.path_pairs[35].primary.position);

    subgame.path_pairs[35].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[35].secondary.Mirror(path);
    zero_position(subgame.path_pairs[35].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[35].primary.fringe_mesh_bod.position);
    subgame.path_pairs[35].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[35].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[29].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_snake_path_template_pair(
        2.0f,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Track0.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[29].primary.position);

    subgame.path_pairs[29].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[29].secondary.Mirror(path);
    zero_position(subgame.path_pairs[29].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[29].primary.fringe_mesh_bod.position);
    subgame.path_pairs[29].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[29].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[47].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_toad_path_template_pair(
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Track0.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[47].primary.position);

    subgame.path_pairs[47].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[47].secondary.Mirror(path);
    zero_position(subgame.path_pairs[47].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[47].primary.fringe_mesh_bod.position);
    subgame.path_pairs[47].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[47].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[48].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_toad_path_template_pair(
        0,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Track0.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[48].primary.position);

    subgame.path_pairs[48].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[48].secondary.Mirror(path);
    zero_position(subgame.path_pairs[48].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[48].primary.fringe_mesh_bod.position);
    subgame.path_pairs[48].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[48].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[49].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_toad_path_template_pair(
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Track0.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[49].primary.position);

    subgame.path_pairs[49].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[49].secondary.Mirror(path);
    zero_position(subgame.path_pairs[49].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", -1.0f);
    zero_position(subgame.path_pairs[49].primary.fringe_mesh_bod.position);
    subgame.path_pairs[49].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 1.0f);
    zero_position(subgame.path_pairs[49].secondary.fringe_mesh_bod.position);

    path = &subgame.path_pairs[50].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_toad_path_template_pair(
        0,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Track0.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[50].primary.position);

    subgame.path_pairs[50].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[50].secondary.Mirror(path);
    zero_position(subgame.path_pairs[50].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 1.0f);
    zero_position(subgame.path_pairs[50].primary.fringe_mesh_bod.position);
    subgame.path_pairs[50].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", -1.0f);
    zero_position(subgame.path_pairs[50].secondary.fringe_mesh_bod.position);

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
    zero_position(subgame.path_pairs[51].primary.position);

    subgame.path_pairs[51].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[51].secondary.Mirror(path);
    zero_position(subgame.path_pairs[51].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[51].primary.fringe_mesh_bod.position);
    subgame.path_pairs[51].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[51].secondary.fringe_mesh_bod.position);

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
    zero_position(subgame.path_pairs[52].primary.position);

    subgame.path_pairs[52].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[52].secondary.Mirror(path);
    zero_position(subgame.path_pairs[52].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[52].primary.fringe_mesh_bod.position);
    subgame.path_pairs[52].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[52].secondary.fringe_mesh_bod.position);

    subgame.path_pairs[1].primary.entry_transition_strip_mesh =
        subgame.path_pairs[52].primary.object;
    subgame.path_pairs[1].primary.entry_base_strip_mesh =
        subgame.path_pairs[1].primary.object;
    subgame.path_pairs[1].secondary.entry_transition_strip_mesh =
        subgame.path_pairs[52].secondary.object;
    subgame.path_pairs[1].secondary.entry_base_strip_mesh =
        subgame.path_pairs[1].secondary.object;

    path = &subgame.path_pairs[53].primary;
    path->SetObject(g_object_list.Add());
    path->initialize_looptheloop_path_template_pair(
        8.0f,
        4,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    zero_position(subgame.path_pairs[53].primary.position);

    subgame.path_pairs[53].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[53].secondary.Mirror(path);
    zero_position(subgame.path_pairs[53].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[53].primary.fringe_mesh_bod.position);
    subgame.path_pairs[53].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[53].secondary.fringe_mesh_bod.position);

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
    zero_position(subgame.path_pairs[57].primary.position);

    subgame.path_pairs[57].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[57].secondary.Mirror(path);
    zero_position(subgame.path_pairs[57].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[57].primary.fringe_mesh_bod.position);
    subgame.path_pairs[57].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[57].secondary.fringe_mesh_bod.position);

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
    zero_position(subgame.path_pairs[54].primary.position);

    subgame.path_pairs[54].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[54].secondary.Mirror(path);
    zero_position(subgame.path_pairs[54].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[54].primary.fringe_mesh_bod.position);
    subgame.path_pairs[54].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[54].secondary.fringe_mesh_bod.position);

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
    zero_position(subgame.path_pairs[55].primary.position);

    subgame.path_pairs[55].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[55].secondary.Mirror(path);
    zero_position(subgame.path_pairs[55].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[55].primary.fringe_mesh_bod.position);
    subgame.path_pairs[55].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[55].secondary.fringe_mesh_bod.position);

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
    zero_position(subgame.path_pairs[56].primary.position);

    subgame.path_pairs[56].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[56].secondary.Mirror(path);
    zero_position(subgame.path_pairs[56].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[56].primary.fringe_mesh_bod.position);
    subgame.path_pairs[56].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[56].secondary.fringe_mesh_bod.position);

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
    zero_position(subgame.path_pairs[58].primary.position);

    subgame.path_pairs[58].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[58].secondary.Mirror(path);
    zero_position(subgame.path_pairs[58].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[58].primary.fringe_mesh_bod.position);
    subgame.path_pairs[58].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[58].secondary.fringe_mesh_bod.position);

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
    zero_position(subgame.path_pairs[62].primary.position);

    subgame.path_pairs[62].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[62].secondary.Mirror(path);
    zero_position(subgame.path_pairs[62].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[62].primary.fringe_mesh_bod.position);
    subgame.path_pairs[62].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[62].secondary.fringe_mesh_bod.position);

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
    zero_position(subgame.path_pairs[59].primary.position);

    subgame.path_pairs[59].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[59].secondary.Mirror(path);
    zero_position(subgame.path_pairs[59].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[59].primary.fringe_mesh_bod.position);
    subgame.path_pairs[59].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[59].secondary.fringe_mesh_bod.position);

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
    zero_position(subgame.path_pairs[61].primary.position);

    subgame.path_pairs[61].secondary.SetObject(
        g_object_list.Add());
    subgame.path_pairs[61].secondary.Mirror(path);
    zero_position(subgame.path_pairs[61].secondary.position);

    path->build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[61].primary.fringe_mesh_bod.position);
    subgame.path_pairs[61].secondary.build_track_fringe_mesh(
        (char*)"Objects/Universe/Fringe.tga", 0.0f);
    zero_position(subgame.path_pairs[61].secondary.fringe_mesh_bod.position);

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
    char* test_line = Rstrfind(
        (char*)"Test:", loader->animation_bytes);
    if (test_line != 0) {
        char* source = Rstrfind((char*)":", test_line) + 1;
        char* destination = base_animation_name;
        while (*source != '.')
            *destination++ = *source++;
        *destination++ = '.';
        *destination++ = 'x';
        *destination = 0;
    } else {
        Rstrcpy(
            base_animation_name, (char*)"turbo-base-000.x");
    }

    loader->LoadAnim(
        base_animation_name,
        subgame.player.presentation.cutscene_animation_slots[0].body.object);
    subgame.player.presentation.SetObject(g_object_list.Add());
    loader->LoadAnim(
        base_animation_name, subgame.player.presentation.object);

    subgame.player.presentation.cutscene_animation_slots[1].body.SetObject(
        g_object_list.Add());
    loader->LoadAnim(
        (char*)"turbo-move-000.x",
        subgame.player.presentation.cutscene_animation_slots[1].body.object);
    subgame.player.presentation.cutscene_animation_slots[2].body.SetObject(
        g_object_list.Add());
    loader->LoadAnim(
        (char*)"turbo-bobalong-000.x",
        subgame.player.presentation.cutscene_animation_slots[2].body.object);
    subgame.player.presentation.cutscene_animation_slots[3].body.SetObject(
        g_object_list.Add());
    loader->LoadAnim(
        (char*)"turbo-lookbackleft-000.x",
        subgame.player.presentation.cutscene_animation_slots[3].body.object);
    subgame.player.presentation.cutscene_animation_slots[4].body.SetObject(
        g_object_list.Add());
    loader->LoadAnim(
        (char*)"turbo-lookbackright-000.x",
        subgame.player.presentation.cutscene_animation_slots[4].body.object);
    subgame.player.presentation.cutscene_animation_slots[5].body.SetObject(
        g_object_list.Add());
    loader->LoadAnim(
        (char*)"turbo-fall-000.x",
        subgame.player.presentation.cutscene_animation_slots[5].body.object);
    subgame.player.presentation.cutscene_animation_slots[6].body.SetObject(
        g_object_list.Add());
    loader->LoadAnim(
        (char*)"turbo-damaged-000.x",
        subgame.player.presentation.cutscene_animation_slots[6].body.object);
    subgame.player.presentation.cutscene_animation_slots[7].body.SetObject(
        g_object_list.Add());
    loader->LoadAnim(
        (char*)"turbo-intoshell-000.x",
        subgame.player.presentation.cutscene_animation_slots[7].body.object);
    subgame.player.presentation.cutscene_animation_slots[8].body.SetObject(
        g_object_list.Add());
    loader->LoadAnim(
        (char*)"turbo-skidstop-000.x",
        subgame.player.presentation.cutscene_animation_slots[8].body.object);
    subgame.player.presentation.cutscene_animation_slots[9].body.SetObject(
        g_object_list.Add());
    loader->LoadAnim(
        (char*)"turbo-talk-000.x",
        subgame.player.presentation.cutscene_animation_slots[9].body.object);

    subgame.player.presentation.snail_hotspot_body.SetObject(
        g_object_list.Add());
    loader->Load(
        (char*)"TurboHotSpots.x",
        subgame.player.presentation.snail_hotspot_body.object,
        2);
    subgame.player.presentation.ExtractHotSpots();

    int animation_count =
        sizeof(subgame.player.presentation.cutscene_animation_slots)
        / sizeof(subgame.player.presentation.cutscene_animation_slots[0]);
    PresentationAnimationSlot* animation_slot;
    int cutscene_animation_index = 0;
    do {
        subgame.player.presentation.cutscene_animation_slots[cutscene_animation_index].body.object->flags |= OBJECT_FLAG_DYNAMIC_VERTICES;
        subgame.player.presentation.cutscene_animation_slots[cutscene_animation_index].body.object->ApplyToon(0);
        subgame.player.presentation.cutscene_animation_slots[cutscene_animation_index].body.object->distort.z_wave = 0.0f;
        subgame.player.presentation.cutscene_animation_slots[cutscene_animation_index].body.object->distort.y_squash = 0.0f;
        subgame.player.presentation.cutscene_animation_slots[cutscene_animation_index].body.object->distort.xyz_scale = 0.0f;
        ++cutscene_animation_index;
    } while (--animation_count != 0);

    subgame.player.presentation.object->flags |= OBJECT_FLAG_DYNAMIC_VERTICES;
    subgame.player.presentation.object->ApplyToon(0);
    subgame.player.presentation.object->distort.z_wave = 0.0f;
    subgame.player.presentation.object->distort.y_squash = 0.0f;
    subgame.player.presentation.object->distort.xyz_scale = 0.0f;

    subgame.player.presentation.jetpack_channel.SetObject(
        g_object_list.Add());
    loader->LoadAnim(
        (char*)"jetpack-base-000.x",
        subgame.player.presentation.jetpack_channel.object);
    subgame.player.presentation.jetpack_channel.animation_slots[0]
        .body.SetObject(
        g_object_list.Add());
    loader->LoadAnim(
        (char*)"jetpack-base-000.x",
        subgame.player.presentation.jetpack_channel.animation_slots[0]
            .body.object);
    subgame.player.presentation.jetpack_channel.animation_slots[1]
        .body.SetObject(
        g_object_list.Add());
    loader->LoadAnim(
        (char*)"jetpack-draw-000.x",
        subgame.player.presentation.jetpack_channel.animation_slots[1]
            .body.object);

    animation_count = 2;
    animation_slot =
        &subgame.player.presentation.jetpack_channel.animation_slots[0];
    do {
        animation_slot->body.object->flags |= OBJECT_FLAG_DYNAMIC_VERTICES;
        animation_slot->body.object->ApplyToon(0);
        animation_slot->body.object->distort.z_wave = 0.0f;
        animation_slot->body.object->distort.y_squash = 0.0f;
        animation_slot->body.object->distort.xyz_scale = 0.0f;
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
    loader->LoadAnim(
        (char*)"blasterleft-base-000.x",
        subgame.player.presentation.weapon_channels[0].object);
    subgame.player.presentation.weapon_channels[0].animation_slots[0]
        .body.SetObject(g_object_list.Add());
    loader->LoadAnim(
        (char*)"blasterleft-base-000.x",
        subgame.player.presentation.weapon_channels[0].animation_slots[0]
            .body.object);
    subgame.player.presentation.weapon_channels[0].animation_slots[1]
        .body.SetObject(g_object_list.Add());
    loader->LoadAnim(
        (char*)"blasterleft-draw-000.x",
        subgame.player.presentation.weapon_channels[0].animation_slots[1]
            .body.object);
    subgame.player.presentation.weapon_channels[0].animation_slots[2]
        .body.SetObject(g_object_list.Add());
    loader->LoadAnim(
        (char*)"blasterleft-fire-000.x",
        subgame.player.presentation.weapon_channels[0].animation_slots[2]
            .body.object);
    subgame.player.presentation.weapon_channels[0].animation_slots[3]
        .body.SetObject(g_object_list.Add());
    loader->LoadAnim(
        (char*)"Laserleft-base-000.x",
        subgame.player.presentation.weapon_channels[0].animation_slots[3]
            .body.object);
    subgame.player.presentation.weapon_channels[0].animation_slots[4]
        .body.SetObject(g_object_list.Add());
    loader->LoadAnim(
        (char*)"Laserleft-draw-000.x",
        subgame.player.presentation.weapon_channels[0].animation_slots[4]
            .body.object);

    animation_count =
        sizeof(subgame.player.presentation.weapon_channels[0].animation_slots)
        / sizeof(subgame.player.presentation.weapon_channels[0].animation_slots[0]);
    animation_slot =
        &subgame.player.presentation.weapon_channels[0].animation_slots[0];
    do {
        animation_slot->body.object->flags |= OBJECT_FLAG_DYNAMIC_VERTICES;
        animation_slot->body.object->ApplyToon(0);
        animation_slot->body.object->distort.z_wave = 0.0f;
        animation_slot->body.object->distort.y_squash = 0.0f;
        animation_slot->body.object->distort.xyz_scale = 0.0f;
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
    loader->LoadAnim(
        (char*)"blasterRight-base-000.x",
        subgame.player.presentation.weapon_channels[1].object);
    subgame.player.presentation.weapon_channels[1].animation_slots[0]
        .body.SetObject(g_object_list.Add());
    loader->LoadAnim(
        (char*)"blasterRight-base-000.x",
        subgame.player.presentation.weapon_channels[1].animation_slots[0]
            .body.object);
    subgame.player.presentation.weapon_channels[1].animation_slots[1]
        .body.SetObject(g_object_list.Add());
    loader->LoadAnim(
        (char*)"blasterRight-draw-000.x",
        subgame.player.presentation.weapon_channels[1].animation_slots[1]
            .body.object);
    subgame.player.presentation.weapon_channels[1].animation_slots[2]
        .body.SetObject(g_object_list.Add());
    loader->LoadAnim(
        (char*)"blasterRight-fire-000.x",
        subgame.player.presentation.weapon_channels[1].animation_slots[2]
            .body.object);
    subgame.player.presentation.weapon_channels[1].animation_slots[3]
        .body.SetObject(g_object_list.Add());
    loader->LoadAnim(
        (char*)"Laserright-base-000.x",
        subgame.player.presentation.weapon_channels[1].animation_slots[3]
            .body.object);
    subgame.player.presentation.weapon_channels[1].animation_slots[4]
        .body.SetObject(g_object_list.Add());
    loader->LoadAnim(
        (char*)"Laserright-draw-000.x",
        subgame.player.presentation.weapon_channels[1].animation_slots[4]
            .body.object);

    animation_count =
        sizeof(subgame.player.presentation.weapon_channels[1].animation_slots)
        / sizeof(subgame.player.presentation.weapon_channels[1].animation_slots[0]);
    animation_slot =
        &subgame.player.presentation.weapon_channels[1].animation_slots[0];
    do {
        animation_slot->body.object->flags |= OBJECT_FLAG_DYNAMIC_VERTICES;
        animation_slot->body.object->ApplyToon(0);
        animation_slot->body.object->distort.z_wave = 0.0f;
        animation_slot->body.object->distort.y_squash = 0.0f;
        animation_slot->body.object->distort.xyz_scale = 0.0f;
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
    loader->LoadAnim(
        (char*)"blasterTop-base-000.x",
        subgame.player.presentation.weapon_channels[2].object);
    subgame.player.presentation.weapon_channels[2].animation_slots[0]
        .body.SetObject(g_object_list.Add());
    loader->LoadAnim(
        (char*)"blasterTop-base-000.x",
        subgame.player.presentation.weapon_channels[2].animation_slots[0]
            .body.object);
    subgame.player.presentation.weapon_channels[2].animation_slots[1]
        .body.SetObject(g_object_list.Add());
    loader->LoadAnim(
        (char*)"blasterTop-draw-000.x",
        subgame.player.presentation.weapon_channels[2].animation_slots[1]
            .body.object);
    subgame.player.presentation.weapon_channels[2].animation_slots[2]
        .body.SetObject(g_object_list.Add());
    loader->LoadAnim(
        (char*)"blasterTop-fire-000.x",
        subgame.player.presentation.weapon_channels[2].animation_slots[2]
            .body.object);
    subgame.player.presentation.weapon_channels[2].animation_slots[3]
        .body.SetObject(g_object_list.Add());
    loader->LoadAnim(
        (char*)"rocketlauncher-base-000.x",
        subgame.player.presentation.weapon_channels[2].animation_slots[3]
            .body.object);
    subgame.player.presentation.weapon_channels[2].animation_slots[4]
        .body.SetObject(g_object_list.Add());
    loader->LoadAnim(
        (char*)"rocketlauncher-draw-000.x",
        subgame.player.presentation.weapon_channels[2].animation_slots[4]
            .body.object);

    animation_count =
        sizeof(subgame.player.presentation.weapon_channels[2].animation_slots)
        / sizeof(subgame.player.presentation.weapon_channels[2].animation_slots[0]);
    animation_slot =
        &subgame.player.presentation.weapon_channels[2].animation_slots[0];
    do {
        animation_slot->body.object->flags |= OBJECT_FLAG_DYNAMIC_VERTICES;
        animation_slot->body.object->ApplyToon(0);
        animation_slot->body.object->distort.z_wave = 0.0f;
        animation_slot->body.object->distort.y_squash = 0.0f;
        animation_slot->body.object->distort.xyz_scale = 0.0f;
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
    loader->Load(
        (char*)"invincible-base-000.x",
        subgame.player.presentation.invincible_shell.object,
        1);
    subgame.player.presentation.invincible_shell.object->flags &=
        ~OBJECT_FLAG_DISABLE_CULLING;

    cRSubGolb* golb_shot = &subgame.player.golb_shots[0];
    golb_shot->tertiary_body.SetObject(
        g_object_list.Add());
    loader->Load(
        (char*)"rocket-base-000.x", golb_shot->tertiary_body.object, 1);
    int golb_shot_count = 12;
    do {
        golb_shot->vapour.SetObject(
            g_object_list.Add());
        golb_shot->vapour.object->flags |=
            OBJECT_FLAG_DISABLE_CULLING | OBJECT_FLAG_DYNAMIC_VERTICES;
        golb_shot->vapour.object->blend_mode = 9;
        load_object_definition((char*)"Objects/VapourLazer", golb_shot->vapour.object);
        golb_shot->vapour.Init(golb_shot->vapour.object, 0.159999996f);
        golb_shot->tertiary_body.SetObject(subgame.player.golb_shots[0].tertiary_body.object);
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

    int fringe_family = 0;
    do {
        int fringe_direction = 0;
        do {
            int fringe_row = 0;
            do {
                int fringe_column = 0;
                do {
                    BodBase& fringe_bod = root_bod_catalog.fringe_catalog
                        .entries[fringe_family][fringe_direction][fringe_row][fringe_column];
                    fringe_bod.SetObject(
                        g_object_list.Add());
                    ObjectProcFringe(
                        fringe_bod.object,
                        fringe_family,
                        fringe_direction,
                        fringe_row - 1,
                        fringe_column - 1,
                        (char*)"Objects/Universe/Fringe.tga");
                    fringe_bod.object->blend_mode = 5;
                    ++fringe_column;
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

    for (int input_index = 0; input_index < GAME_ROOT_PLAYER_SLOT_COUNT; input_index++) {
        active_bod_list.add_bod_to_front(&game_inputs[input_index]);
        game_inputs[input_index].input.controller_slot = input_index;
        game_inputs[input_index].input.Init();
    }

    int player_index = 0;
    if (player_count > 0) {
        do {
            players[player_index].transform.Identity();
            players[player_index].camera.transform.Identity();
            players[player_index].camera.fov_degrees = 110.0f;
            players[player_index].game_input = &game_inputs[player_index];
            players[player_index].transform =
                TransformMatrix(
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
            Rstrcpy(
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
    active_bod_list.add_bod_to_front(&tip_manager);
    g_game->active_bod_list.add_bod_to_front(
        (BodNode*)&star_manager);
    star_manager.Open(36);
    subgame.bottom_score_widget = 0;
    subgame.top_score_widget = 0;
    active_bod_list.add_bod_to_front(&backdrop);
    backdrop.backdrop_render_enabled = 0;
    active_bod_list.append_bod_to_end(&border_manager);
    border_manager.border_stack.initialize_border_stack();
    border_manager.border_stack.owner = &border_manager;
    border_manager.delayed_widget_active = 0;
    border_manager.SetJustifyCentre(25.0f);

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
