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

    void** sub_lazer_object = &subgame.sub_lazers.slots[0].object;
    int sub_lazer_count = 20;
    do {
        ((BodBase*)((char*)sub_lazer_object - 0x24))
            ->set_bod_object(lazer->object);
        ((Object*)*sub_lazer_object)
            ->facequads[0].texture_ref->flags |= TEXTURE_REF_REGISTERED;
        *(SubgameRuntime**)((char*)sub_lazer_object + 0x64) =
            (SubgameRuntime*)(game + 0x74618);
        ((Color4f*)(sub_lazer_object + 1))
            ->store_color4f(1.0f, 1.0f, 1.0f, 0.7f);
        ((Object*)*sub_lazer_object)->blend_mode = 9;
        sub_lazer_object = (void**)((char*)sub_lazer_object + sizeof(SubLazer));
        --sub_lazer_count;
    } while (sub_lazer_count != 0);

    BodBase* salt_model = &root_bod_catalog.salt_model;
    salt_model->set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_mesh((char*)"salt.x", salt_model->object, 1);

    SubgameRuntime** salt_owner = &subgame.salt_hazards.slots[0].owner_game;
    int salt_count = 40;
    do {
        Salt* salt = (Salt*)((char*)salt_owner - 0x88);
        ((BodBase*)salt)->set_bod_object(salt_model->object);
        *salt_owner = (SubgameRuntime*)(game + 0x74618);
        salt->color.store_color4f(1.0f, 1.0f, 1.0f, 0.9f);
        ((Object*)salt->object)->blend_mode = 12;
        set_matrix_identity((TransformMatrix*)&salt->basis_right);
        salt_owner = (SubgameRuntime**)((char*)salt_owner + sizeof(Salt));
        --salt_count;
    } while (salt_count != 0);

    int banner_index = 0;
    do {
        char* banner_cursor = game + banner_index * sizeof(Banner);
        ((Banner*)(banner_cursor + 0x3cd698))
            ->set_bod_object(g_object_list.add_object_to_list());
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
        ((Banner*)(banner_cursor + 0x3cd698))->position.z = 0.0f;
        ((Banner*)(banner_cursor + 0x3cd698))->position.y = 0.0f;
        ((Banner*)(banner_cursor + 0x3cd698))->position.x = 0.0f;
        subgame.banners.slots[banner_index].owner_game = &subgame;
        ((Banner*)(banner_cursor + 0x3cd698))->visibility_mode = banner_index;
        ++banner_index;
        ((Banner*)(banner_cursor + 0x3cd698))->phase = 0.0f;
        ((Banner*)(banner_cursor + 0x3cd698))->phase_step = 0.006944444f;
    } while (banner_index < 2);

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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[0].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[0].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[1].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[1].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[2].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[2].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[6].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[6].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[3].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[3].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[4].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[4].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[5].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[5].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[7].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[7].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[37].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[37].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[38].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[38].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[43].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[43].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[44].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[44].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[45].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[45].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[46].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[46].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[39].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[39].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[41].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[41].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
    path->initialize_halfpipe_path_template_pair(
        0x40c00000,
        8,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[42].primary.position.z = 0.0f;
    subgame.path_pairs[42].primary.position.y = 0.0f;
    subgame.path_pairs[42].primary.position.x = 0.0f;

    subgame.path_pairs[42].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[42].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[40].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[40].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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
    path->set_bod_object(g_object_list.add_object_to_list());
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
    path->set_bod_object(g_object_list.add_object_to_list());
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
    path->set_bod_object(g_object_list.add_object_to_list());
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[25].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[25].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[27].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[27].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[26].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[26].secondary.mirror_path_template_pair_x(path);
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

    return 1;
}
