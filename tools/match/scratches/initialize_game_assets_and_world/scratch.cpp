// initialize_game_assets_and_world @ 0x40acf0 (thiscall)

#include <string.h>

#include "backdrop.h"
#include "bod_types.h"
#include "cameraman.h"
#include "cheat_state.h"
#include "directx_loader.h"
#include "game_root.h"
#include "galaxy_route_types.h"
#include "landscape_manager.h"
#include "object_render_types.h"
#include "runtime_config.h"
#include "segment_catalog_types.h"
#include "sprite.h"
#include "thanks_screen.h"
#include "transform_matrix.h"
#include "voice_manager.h"

extern char* g_game_base; // data_4df904
extern char g_directx_loader_scratch[]; // 0x74eb18, cleared before DirectX loader init
extern void* g_sound_bank_entries; // 0x4a2140, sound bank table
extern SubSegmentRaw* g_builtin_segment_definitions[]; // 0x4a63d0

int report_errorf(char* format, ...); // @ 0x431cc0
int debug_report_stub(char* format, ...); // @ 0x449c00
void sub_449C00(); // stripped no-arg debug callsite before path templates
void initialize_font_wave_state(); // @ 0x449c70
void initialize_font3d_objects(short font_id); // @ 0x44ae10
void register_font_texture_sheet_wrapper(char* font_path, int font_id, float width_scale, float height_scale); // @ 0x432d20
void initialize_backdrop_slice_quad(Object* object, char* texture_path, float x_offset); // @ 0x41a1c0
void initialize_textured_backdrop_quad(Object* object, char* texture_path, float x_offset); // @ 0x41a2f0
void raise_backdrop_quad_edge_pair(int edge_pair, Object* object); // @ 0x41a440
void initialize_backdrop_corner_quad(int corner, Object* object, char* texture_path); // @ 0x41a450
char* __stdcall initialize_sound_bank(void* entries); // @ 0x44dcb0

static __forceinline void link_root_bod(BodBase* bod)
{
    char* node = (char*)bod;
    unsigned int* flags = (unsigned int*)(node + 4);
    if ((*flags & 0x200) != 0) {
        report_errorf((char*)"List ADD");
        return;
    }

    char* head = g_game_base + 0x5ac;
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
    *flags |= 0x200;
}

static __forceinline void initialize_overlay_slot(Overlay* overlay)
{
    link_root_bod(overlay);
    overlay->initialize_overlay();
}

char GameRoot::initialize_game_assets_and_world()
{
    char* game = (char*)this;
    Color4f asset_color;
    asset_color.noop_this_constructor();

    ((Color4f*)(game + 0x14))->store_color4f(1.0f, 1.0f, 1.0f, 1.0f);
    *(float*)(game + 0x10) = 1.0f;
    *(float*)(game + 0x08) = 30.0f;
    *(float*)(game + 0x0c) = 50.0f;
    *(unsigned char*)(game + 0x04) = 1;
    player_count = 2;
    frontend_link_latch = 0;
    subgame.subgame_pause_gate = 0;

    g_cheat_state.initialize_cheat();
    *(unsigned char*)(game + 0x4f2e0) = 0;
    subgame.initialize_blink_random();
    subgame.set_subgame_rate(1.1f);
    *(int*)(game + 0x56c) = 2;
    *(int*)(game + 0x3c) = 1;

    g_texture_refs.initialize_texture_list(500);
    g_object_list.initialize_object_list(3000);
    *(int*)(game + 0x514) = 0;
    ((GameRoot*)game)->fixed_update_accumulator = 0.0f;
    ((GameRoot*)game)->frame_counter = 0;
    inactive_bod_sentinel.list_next = 0;
    active_bod_list.free_top = &inactive_bod_sentinel;
    active_bod_list.first = 0;
    *(int*)(game + 0xb48) = 0;
    memset(g_sprite_depth_buckets, 0, sizeof(g_sprite_depth_buckets));

    render_camera_slots[0].sort_key = 0;
    render_camera_slots[0].flags = 0x1000003;
    render_camera_slots[0].source = &overlay_0.camera;
    render_camera_slots[0].viewport_x = 0.0f;
    render_camera_slots[0].viewport_y = 0.0f;
    render_camera_slots[0].viewport_width = 1.0f;
    render_camera_slots[0].viewport_height = 1.0f;
    render_camera_slots[2].draw_world = 0;
    initialize_overlay_slot(&overlay_0);

    memset(g_directx_loader_scratch, 0, 0x15c);
    DirectXLoader* loader = &directx_loader;
    loader->initialize_directx_loader();
    LandscapeManager* landscape = (LandscapeManager*)(game + 0x106c218);
    landscape->reset_landscape_manager();
    SMTracks* sm_tracks = &subgame.sm_tracks;
    sm_tracks->load_segment_definitions();
    landscape->load_landscape_script_by_name((char*)"Starmap.txt");
    landscape->load_landscape_script_by_name((char*)"Splash.txt");
    landscape->load_landscape_script_by_name((char*)"Help.txt");

    subgame.level_mode_arg = g_runtime_config.landscape_backdrop_variant_selector;
    ((SubgameOwnerLink*)&subgame.gui)->bind_subgame_owner();
    ((SubgameOwnerLink*)&subgame.thanks_screen)->bind_subgame_owner();
    subgame.galaxy.load_galaxy_layout();
    subgame.player.cameraman.initialize_cameraman();
    logo.open_logo();
    initialize_sound_bank(&g_sound_bank_entries);
    g_voice_manager.initialize_voice_manager();
    options.apply_audio_config_volumes();
    sm_tracks->load_level_definitions();
    ((LandscapeManager*)(g_game_base + 0x106c218))
        ->load_landscape_script_by_name((char*)"Menubg.txt");
    subgame.level_definition_scratch.load_builtin_segment_definitions(
        g_builtin_segment_definitions);

    render_camera_slots[1].sort_key = 1;
    render_camera_slots[1].flags = 0x2000001;
    render_camera_slots[1].attach_render_camera_source(&players[0].camera);
    players[0].camera.render_mask = 0x2000000;

    render_camera_slots[4].sort_key = 1;
    render_camera_slots[4].flags = 0x10000003;
    render_camera_slots[4].attach_render_camera_source(&players[1].camera);
    players[1].camera.render_mask = 0x10000000;

    render_camera_slots[3].sort_key = 3;
    render_camera_slots[3].flags = 0x8000003;
    render_camera_slots[3].source = &overlay_2.camera;
    render_camera_slots[3].viewport_x = 0.0f;
    render_camera_slots[3].viewport_y = 0.0f;
    render_camera_slots[3].viewport_width = 1.0f;
    render_camera_slots[3].viewport_height = 1.0f;
    initialize_overlay_slot(&overlay_2);

    render_camera_slots[2].sort_key = 2;
    render_camera_slots[2].flags = 0x4000003;
    render_camera_slots[2].source = &overlay_1.camera;
    render_camera_slots[2].viewport_x = 0.0f;
    render_camera_slots[2].viewport_y = 0.0f;
    render_camera_slots[2].viewport_width = 1.0f;
    render_camera_slots[2].viewport_height = 1.0f;
    initialize_overlay_slot(&overlay_1);

    register_font_texture_sheet_wrapper((char*)"Objects/Font/Font-menu-hover.tga", 2, 0.75f, 1.0f);
    initialize_font3d_objects(0);
    initialize_font_wave_state();
    g_sprite_manager.initialize_sprite_manager();
    g_sprite_manager.register_sprite_texture((char*)"Sprites/Debug.tga", 1, 0);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/Overlay.tga", 2, 0);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/Border.tga", 5, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/Mouse.tga", 22, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/Warning.tga", 94, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/Play.tga", 27, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/StarTail.tga", 32, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/Jet.tga", 33, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/Health.tga", 57, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/DamageGuage.tga", 89, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/DamageGuageFull.tga", 90, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/DamageGuageBright.tga", 91, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/Spark.tga", 92, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/Black.tga", 93, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/BorderGlow.tga", 99, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/Slug000.tga", 118, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/Slug001.tga", 119, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/SlugMask.tga", 120, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/Parcel000.tga", 121, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/ParcelIcon.tga", 122, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/GarbageA.tga", 114, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/GarbageB.tga", 115, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/GarbageC.tga", 116, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/GarbageD.tga", 117, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/Life.tga", 123, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/JetPack000.tga", 124, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/Smoke.tga", 128, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/SlugGoo.tga", 129, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/SliderBar.tga", 36, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/SliderBarFull.tga", 37, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/Less.tga", 38, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/LessHover.tga", 40, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/LessMask.tga", 41, 0x420);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/More.tga", 42, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/MoreHover.tga", 44, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/MoreMask.tga", 45, 0x420);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/ParticleBlasters.tga", 130, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/ParticleExplode-big.tga", 131, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/ParticleExplode-small.tga", 132, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/ParticleSlow-big.tga", 133, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/ParticleSlow-small.tga", 134, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/ParticleRing-big.tga", 135, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/ParticleRing-small.tga", 136, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/Collision.tga", 137, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Galaxy/SpaceMapLogo.tga", 138, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Galaxy/Galaxy000.tga", 139, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Galaxy/Galaxy001.tga", 140, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Galaxy/Galaxy002.tga", 141, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Galaxy/Galaxy003.tga", 142, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Galaxy/Galaxy004.tga", 143, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Galaxy/Galaxy005.tga", 144, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Galaxy/Galaxy006.tga", 145, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Galaxy/Galaxy007.tga", 146, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Galaxy/Galaxy008.tga", 147, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Galaxy/Galaxy009.tga", 148, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Galaxy/GalaxySelect.tga", 149, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Galaxy/LevelSelect.tga", 150, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Galaxy/LevelStar.tga", 151, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Galaxy/BorderSpacemap.tga", 152, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Galaxy/Line.tga", 153, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Galaxy/LineStar.tga", 154, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/Progress-Bar.tga", 155, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/Progress-Bar-lit.tga", 156, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/Progress-Cursor.tga", 157, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/JetPackThrust.tga", 158, 0x400);
    g_sprite_manager.register_sprite_texture((char*)"Sprites/Ghost.tga", 159, 0x400);

    float slice_index = 0.0f;
    do {
        int storage_index = (int)slice_index;
        BodBase* floor_slice = &root_bod_catalog.floor_slices.storage[storage_index];
        floor_slice->set_bod_object(g_object_list.add_object_to_list());
        initialize_backdrop_slice_quad(
            floor_slice->object, (char*)"Objects/World00/Track0.tga", slice_index);

        BodBase* warning_slice = &root_bod_catalog.warning_slices.storage[storage_index];
        warning_slice->set_bod_object(g_object_list.add_object_to_list());
        initialize_backdrop_slice_quad(
            warning_slice->object, (char*)"Objects/World00/TrackWarn.tga", slice_index);

        BodBase* slide_slice = &root_bod_catalog.slide_slices.storage[storage_index];
        slide_slice->set_bod_object(g_object_list.add_object_to_list());
        initialize_backdrop_slice_quad(
            slide_slice->object, (char*)"Objects/World00/Slide0.tga", slice_index);
        slice_index += 1.0f;
    } while (slice_index < 8.0f);

    TransformMatrix transform;
    set_matrix_identity(&transform);

    BodBase* pillar = &root_bod_catalog.pillars[0];
    pillar->set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_mesh((char*)"pillar1.x", pillar->object, 1);
    transform.position.x = 0.0f;
    pillar->apply_bod_position(&transform);

    pillar = &root_bod_catalog.pillars[1];
    pillar->set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_mesh((char*)"pillar2.x", pillar->object, 1);
    transform.position.x = 0.5f;
    pillar->apply_bod_position(&transform);

    pillar = &root_bod_catalog.pillars[2];
    pillar->set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_mesh((char*)"pillar3.x", pillar->object, 1);
    transform.position.x = 1.0f;
    pillar->apply_bod_position(&transform);

    pillar = &root_bod_catalog.pillars[3];
    pillar->set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_mesh((char*)"pillar4.x", pillar->object, 1);
    transform.position.x = 1.5f;
    pillar->apply_bod_position(&transform);

    pillar = &root_bod_catalog.pillars[4];
    pillar->set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_mesh((char*)"pillar5.x", pillar->object, 1);
    transform.position.x = 2.0f;
    pillar->apply_bod_position(&transform);

    pillar = &root_bod_catalog.pillars[5];
    pillar->set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_mesh((char*)"pillar6.x", pillar->object, 1);
    transform.position.x = 2.5f;
    pillar->apply_bod_position(&transform);

    pillar = &root_bod_catalog.pillars[6];
    pillar->set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_mesh((char*)"pillar7.x", pillar->object, 1);
    transform.position.x = 3.0f;
    pillar->apply_bod_position(&transform);

    pillar = &root_bod_catalog.pillars[7];
    pillar->set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_mesh((char*)"pillar8.x", pillar->object, 1);
    transform.position.x = 3.5f;
    pillar->apply_bod_position(&transform);

    BodBase* ramp_edge = &root_bod_catalog.ramp_edges[0];
    ramp_edge->set_bod_object(g_object_list.add_object_to_list());
    initialize_textured_backdrop_quad(
        ramp_edge->object, (char*)"Objects/Universe/Ramp.tga", 0.0f);
    raise_backdrop_quad_edge_pair(-1, ramp_edge->object);

    ramp_edge = &root_bod_catalog.ramp_edges[1];
    ramp_edge->set_bod_object(g_object_list.add_object_to_list());
    initialize_textured_backdrop_quad(
        ramp_edge->object, (char*)"Objects/Universe/Ramp.tga", 0.0f);
    raise_backdrop_quad_edge_pair(0, ramp_edge->object);

    ramp_edge = &root_bod_catalog.ramp_edges[2];
    ramp_edge->set_bod_object(g_object_list.add_object_to_list());
    initialize_textured_backdrop_quad(
        ramp_edge->object, (char*)"Objects/Universe/Ramp.tga", 0.0f);
    raise_backdrop_quad_edge_pair(1, ramp_edge->object);

    BodBase* corner = &root_bod_catalog.floor_corners.storage[TRACK_CORNER_0_STORAGE_INDEX];
    corner->set_bod_object(g_object_list.add_object_to_list());
    initialize_backdrop_corner_quad(
        0, corner->object, (char*)"Objects/World00/Track0.tga");
    corner = &root_bod_catalog.floor_corners.storage[TRACK_CORNER_1_STORAGE_INDEX];
    corner->set_bod_object(g_object_list.add_object_to_list());
    initialize_backdrop_corner_quad(
        1, corner->object, (char*)"Objects/World00/Track0.tga");
    corner = &root_bod_catalog.floor_corners.storage[TRACK_CORNER_2_STORAGE_INDEX];
    corner->set_bod_object(g_object_list.add_object_to_list());
    initialize_backdrop_corner_quad(
        2, corner->object, (char*)"Objects/World00/Track0.tga");
    corner = &root_bod_catalog.floor_corners.storage[TRACK_CORNER_3_STORAGE_INDEX];
    corner->set_bod_object(g_object_list.add_object_to_list());
    initialize_backdrop_corner_quad(
        3, corner->object, (char*)"Objects/World00/Track0.tga");

    corner = &root_bod_catalog.warning_corners.storage[TRACK_CORNER_0_STORAGE_INDEX];
    corner->set_bod_object(g_object_list.add_object_to_list());
    initialize_backdrop_corner_quad(
        0, corner->object, (char*)"Objects/World00/TrackWarn.tga");
    corner = &root_bod_catalog.warning_corners.storage[TRACK_CORNER_1_STORAGE_INDEX];
    corner->set_bod_object(g_object_list.add_object_to_list());
    initialize_backdrop_corner_quad(
        1, corner->object, (char*)"Objects/World00/TrackWarn.tga");
    corner = &root_bod_catalog.warning_corners.storage[TRACK_CORNER_2_STORAGE_INDEX];
    corner->set_bod_object(g_object_list.add_object_to_list());
    initialize_backdrop_corner_quad(
        2, corner->object, (char*)"Objects/World00/TrackWarn.tga");
    corner = &root_bod_catalog.warning_corners.storage[TRACK_CORNER_3_STORAGE_INDEX];
    corner->set_bod_object(g_object_list.add_object_to_list());
    initialize_backdrop_corner_quad(
        3, corner->object, (char*)"Objects/World00/TrackWarn.tga");

    corner = &root_bod_catalog.slide_corners.storage[TRACK_CORNER_0_STORAGE_INDEX];
    corner->set_bod_object(g_object_list.add_object_to_list());
    initialize_backdrop_corner_quad(
        0, corner->object, (char*)"Objects/World00/Slide0.tga");
    corner = &root_bod_catalog.slide_corners.storage[TRACK_CORNER_1_STORAGE_INDEX];
    corner->set_bod_object(g_object_list.add_object_to_list());
    initialize_backdrop_corner_quad(
        1, corner->object, (char*)"Objects/World00/Slide0.tga");
    corner = &root_bod_catalog.slide_corners.storage[TRACK_CORNER_2_STORAGE_INDEX];
    corner->set_bod_object(g_object_list.add_object_to_list());
    initialize_backdrop_corner_quad(
        2, corner->object, (char*)"Objects/World00/Slide0.tga");
    corner = &root_bod_catalog.slide_corners.storage[TRACK_CORNER_3_STORAGE_INDEX];
    corner->set_bod_object(g_object_list.add_object_to_list());
    initialize_backdrop_corner_quad(
        3, corner->object, (char*)"Objects/World00/Slide0.tga");

    BodBase* trampoline = &root_bod_catalog.trampoline;
    trampoline->set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_mesh((char*)"Tramp.x", trampoline->object, 1);
    trampoline->object->blend_mode = 6;
    trampoline->object->facequads[0].texture_ref->flags |= TEXTURE_REF_REGISTERED;

    BodBase* universe_hole = &root_bod_catalog.universe_hole;
    universe_hole->set_bod_object(g_object_list.add_object_to_list());
    initialize_textured_backdrop_quad(
        universe_hole->object, (char*)"Objects/Universe/Hole.tga", 0.0f);
    universe_hole->object->blend_mode = 5;
    universe_hole->object->facequads[0].texture_ref->flags |= 4;

    BodBase* lazer = &root_bod_catalog.lazer_model;
    lazer->set_bod_object(g_object_list.add_object_to_list());
    load_object_definition((char*)"Objects/Lazer", lazer->object);

    sub_449C00();
    return 1;
}
