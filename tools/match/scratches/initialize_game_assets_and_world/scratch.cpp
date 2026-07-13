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
char* find_case_insensitive_substring(char* needle, char* haystack); // @ 0x44e600
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

    path = &subgame.path_pairs[16].primary;
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[16].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[16].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[17].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[17].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[18].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[18].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[19].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[19].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[8].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[8].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[10].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[10].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[9].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[9].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[14].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[14].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[11].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[11].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[13].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[13].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[12].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[12].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[20].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[20].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[21].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[21].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[22].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[22].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[23].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[23].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[32].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[32].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
    path->initialize_worm_path_template_pair(
        (char*)"Objects/World00/Worm.tga");
    subgame.path_pairs[24].primary.position.z = 0.0f;
    subgame.path_pairs[24].primary.position.y = 0.0f;
    subgame.path_pairs[24].primary.position.x = 0.0f;

    subgame.path_pairs[24].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[24].secondary.mirror_path_template_pair_x(path);
    subgame.path_pairs[24].secondary.position.z = 0.0f;
    subgame.path_pairs[24].secondary.position.y = 0.0f;
    subgame.path_pairs[24].secondary.position.x = 0.0f;

    subgame.path_pairs[24].primary.fringe_mesh_bod.set_bod_object(
        g_object_list.add_object_to_list());
    disable_object_rendering(
        subgame.path_pairs[24].primary.fringe_mesh_bod.object);
    subgame.path_pairs[24].secondary.fringe_mesh_bod.set_bod_object(
        g_object_list.add_object_to_list());
    disable_object_rendering(
        subgame.path_pairs[24].secondary.fringe_mesh_bod.object);
    subgame.path_pairs[24].primary.object->blend_mode = 8;
    subgame.path_pairs[24].secondary.object->blend_mode = 8;

    path = &subgame.path_pairs[28].primary;
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[28].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[28].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
    path->initialize_cage2_path_template_pair(
        3,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[15].primary.position.z = 0.0f;
    subgame.path_pairs[15].primary.position.y = 0.0f;
    subgame.path_pairs[15].primary.position.x = 0.0f;

    subgame.path_pairs[15].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[15].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[33].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[33].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[34].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[34].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[35].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[35].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[29].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[29].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
    path->initialize_toad_path_template_pair(
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Track0.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[47].primary.position.z = 0.0f;
    subgame.path_pairs[47].primary.position.y = 0.0f;
    subgame.path_pairs[47].primary.position.x = 0.0f;

    subgame.path_pairs[47].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[47].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
    path->initialize_toad_path_template_pair(
        0,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Track0.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[48].primary.position.z = 0.0f;
    subgame.path_pairs[48].primary.position.y = 0.0f;
    subgame.path_pairs[48].primary.position.x = 0.0f;

    subgame.path_pairs[48].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[48].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
    path->initialize_toad_path_template_pair(
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Track0.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[49].primary.position.z = 0.0f;
    subgame.path_pairs[49].primary.position.y = 0.0f;
    subgame.path_pairs[49].primary.position.x = 0.0f;

    subgame.path_pairs[49].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[49].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
    path->initialize_toad_path_template_pair(
        0,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Track0.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[50].primary.position.z = 0.0f;
    subgame.path_pairs[50].primary.position.y = 0.0f;
    subgame.path_pairs[50].primary.position.x = 0.0f;

    subgame.path_pairs[50].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[50].secondary.mirror_path_template_pair_x(path);
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

    Color4f path_transition_color;
    path_transition_color.noop_this_constructor();
    path_transition_color.store_color4f(1.0f, 1.0f, 1.0f, 0.60000002f);

    path = &subgame.path_pairs[51].primary;
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[51].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[51].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[52].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[52].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[53].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[53].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[57].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[57].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[54].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[54].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[55].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[55].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[56].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[56].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[58].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[58].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[62].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[62].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[59].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[59].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
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

    subgame.path_pairs[61].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[61].secondary.mirror_path_template_pair_x(path);
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
    path->set_bod_object(g_object_list.add_object_to_list());
    path->initialize_loopout_path_template_pair(
        3.0f,
        3,
        1,
        (char*)"Objects/World00/Slide0.tga",
        (char*)"Objects/World00/Back.tga",
        (char*)"Objects/Path/VeryDark.tga");
    subgame.path_pairs[60].primary.position.zero_vector3();

    subgame.path_pairs[60].secondary.set_bod_object(
        g_object_list.add_object_to_list());
    subgame.path_pairs[60].secondary.mirror_path_template_pair_x(path);
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

    subgame.player.presentation.cutscene_animation_slots[0].body.set_bod_object(
        g_object_list.add_object_to_list());

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
    ((BodBase*)&subgame.player.presentation)
        ->set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        base_animation_name, subgame.player.presentation.object);

    subgame.player.presentation.cutscene_animation_slots[1].body.set_bod_object(
        g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"turbo-move-000.x",
        subgame.player.presentation.cutscene_animation_slots[1].body.object);
    subgame.player.presentation.cutscene_animation_slots[2].body.set_bod_object(
        g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"turbo-bobalong-000.x",
        subgame.player.presentation.cutscene_animation_slots[2].body.object);
    subgame.player.presentation.cutscene_animation_slots[3].body.set_bod_object(
        g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"turbo-lookbackleft-000.x",
        subgame.player.presentation.cutscene_animation_slots[3].body.object);
    subgame.player.presentation.cutscene_animation_slots[4].body.set_bod_object(
        g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"turbo-lookbackright-000.x",
        subgame.player.presentation.cutscene_animation_slots[4].body.object);
    subgame.player.presentation.cutscene_animation_slots[5].body.set_bod_object(
        g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"turbo-fall-000.x",
        subgame.player.presentation.cutscene_animation_slots[5].body.object);
    subgame.player.presentation.cutscene_animation_slots[6].body.set_bod_object(
        g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"turbo-damaged-000.x",
        subgame.player.presentation.cutscene_animation_slots[6].body.object);
    subgame.player.presentation.cutscene_animation_slots[7].body.set_bod_object(
        g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"turbo-intoshell-000.x",
        subgame.player.presentation.cutscene_animation_slots[7].body.object);
    subgame.player.presentation.cutscene_animation_slots[8].body.set_bod_object(
        g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"turbo-skidstop-000.x",
        subgame.player.presentation.cutscene_animation_slots[8].body.object);
    subgame.player.presentation.cutscene_animation_slots[9].body.set_bod_object(
        g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"turbo-talk-000.x",
        subgame.player.presentation.cutscene_animation_slots[9].body.object);

    subgame.player.presentation.snail_hotspot_body.set_bod_object(
        g_object_list.add_object_to_list());
    loader->load_x_mesh(
        (char*)"TurboHotSpots.x",
        subgame.player.presentation.snail_hotspot_body.object,
        2);
    subgame.player.presentation.build_snail_hotspots();

    int animation_count = 10;
    PresentationAnimationSlot* animation_slot =
        &subgame.player.presentation.cutscene_animation_slots[0];
    do {
        Object* animation_object = animation_slot->body.object;
        animation_object->flags |= 4;
        animation_object->apply_object_toon(0);
        animation_object->distort.z_wave = 0.0f;
        animation_object->distort.y_squash = 0.0f;
        animation_object->distort.xyz_scale = 0.0f;
        ++animation_slot;
    } while (--animation_count != 0);

    subgame.player.presentation.object->flags |= 4;
    subgame.player.presentation.object->apply_object_toon(0);
    subgame.player.presentation.object->distort.z_wave = 0.0f;
    subgame.player.presentation.object->distort.y_squash = 0.0f;
    subgame.player.presentation.object->distort.xyz_scale = 0.0f;

    ((BodBase*)&subgame.player.presentation.jetpack_channel)
        ->set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"jetpack-base-000.x",
        subgame.player.presentation.jetpack_channel.object);
    subgame.player.presentation.jetpack_channel.animation_slots[0]
        .body.set_bod_object(
        g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"jetpack-base-000.x",
        subgame.player.presentation.jetpack_channel.animation_slots[0]
            .body.object);
    subgame.player.presentation.jetpack_channel.animation_slots[1]
        .body.set_bod_object(
        g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"jetpack-draw-000.x",
        subgame.player.presentation.jetpack_channel.animation_slots[1]
            .body.object);

    animation_count = 2;
    animation_slot =
        &subgame.player.presentation.jetpack_channel.animation_slots[0];
    do {
        Object* animation_object = animation_slot->body.object;
        animation_object->flags |= 4;
        animation_object->apply_object_toon(0);
        animation_object->distort.z_wave = 0.0f;
        animation_object->distort.y_squash = 0.0f;
        animation_object->distort.xyz_scale = 0.0f;
        ++animation_slot;
    } while (--animation_count != 0);

    subgame.player.presentation.jetpack_channel.object->flags |= 4;
    subgame.player.presentation.jetpack_channel.object->apply_object_toon(0);
    subgame.player.presentation.jetpack_channel.object->distort.z_wave = 0.0f;
    subgame.player.presentation.jetpack_channel.object->distort.y_squash = 0.0f;
    subgame.player.presentation.jetpack_channel.object->distort.xyz_scale = 0.0f;

    ((BodBase*)&subgame.player.presentation.weapon_channels[0])
        ->set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"blasterleft-base-000.x",
        subgame.player.presentation.weapon_channels[0].object);
    subgame.player.presentation.weapon_channels[0].animation_slots[0]
        .body.set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"blasterleft-base-000.x",
        subgame.player.presentation.weapon_channels[0].animation_slots[0]
            .body.object);
    subgame.player.presentation.weapon_channels[0].animation_slots[1]
        .body.set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"blasterleft-draw-000.x",
        subgame.player.presentation.weapon_channels[0].animation_slots[1]
            .body.object);
    subgame.player.presentation.weapon_channels[0].animation_slots[2]
        .body.set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"blasterleft-fire-000.x",
        subgame.player.presentation.weapon_channels[0].animation_slots[2]
            .body.object);
    subgame.player.presentation.weapon_channels[0].animation_slots[3]
        .body.set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"Laserleft-base-000.x",
        subgame.player.presentation.weapon_channels[0].animation_slots[3]
            .body.object);
    subgame.player.presentation.weapon_channels[0].animation_slots[4]
        .body.set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"Laserleft-draw-000.x",
        subgame.player.presentation.weapon_channels[0].animation_slots[4]
            .body.object);

    animation_count = 5;
    animation_slot =
        &subgame.player.presentation.weapon_channels[0].animation_slots[0];
    do {
        Object* animation_object = animation_slot->body.object;
        animation_object->flags |= 4;
        animation_object->apply_object_toon(0);
        animation_object->distort.z_wave = 0.0f;
        animation_object->distort.y_squash = 0.0f;
        animation_object->distort.xyz_scale = 0.0f;
        ++animation_slot;
    } while (--animation_count != 0);

    subgame.player.presentation.weapon_channels[0].object->flags |= 4;
    subgame.player.presentation.weapon_channels[0].object->apply_object_toon(0);
    subgame.player.presentation.weapon_channels[0].object->distort.z_wave = 0.0f;
    subgame.player.presentation.weapon_channels[0].object->distort.y_squash = 0.0f;
    subgame.player.presentation.weapon_channels[0].object->distort.xyz_scale = 0.0f;

    ((BodBase*)&subgame.player.presentation.weapon_channels[1])
        ->set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"blasterRight-base-000.x",
        subgame.player.presentation.weapon_channels[1].object);
    subgame.player.presentation.weapon_channels[1].animation_slots[0]
        .body.set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"blasterRight-base-000.x",
        subgame.player.presentation.weapon_channels[1].animation_slots[0]
            .body.object);
    subgame.player.presentation.weapon_channels[1].animation_slots[1]
        .body.set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"blasterRight-draw-000.x",
        subgame.player.presentation.weapon_channels[1].animation_slots[1]
            .body.object);
    subgame.player.presentation.weapon_channels[1].animation_slots[2]
        .body.set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"blasterRight-fire-000.x",
        subgame.player.presentation.weapon_channels[1].animation_slots[2]
            .body.object);
    subgame.player.presentation.weapon_channels[1].animation_slots[3]
        .body.set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"Laserright-base-000.x",
        subgame.player.presentation.weapon_channels[1].animation_slots[3]
            .body.object);
    subgame.player.presentation.weapon_channels[1].animation_slots[4]
        .body.set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"Laserright-draw-000.x",
        subgame.player.presentation.weapon_channels[1].animation_slots[4]
            .body.object);

    animation_count = 5;
    animation_slot =
        &subgame.player.presentation.weapon_channels[1].animation_slots[0];
    do {
        Object* animation_object = animation_slot->body.object;
        animation_object->flags |= 4;
        animation_object->apply_object_toon(0);
        animation_object->distort.z_wave = 0.0f;
        animation_object->distort.y_squash = 0.0f;
        animation_object->distort.xyz_scale = 0.0f;
        ++animation_slot;
    } while (--animation_count != 0);

    subgame.player.presentation.weapon_channels[1].object->flags |= 4;
    subgame.player.presentation.weapon_channels[1].object->apply_object_toon(0);
    subgame.player.presentation.weapon_channels[1].object->distort.z_wave = 0.0f;
    subgame.player.presentation.weapon_channels[1].object->distort.y_squash = 0.0f;
    subgame.player.presentation.weapon_channels[1].object->distort.xyz_scale = 0.0f;

    ((BodBase*)&subgame.player.presentation.weapon_channels[2])
        ->set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"blasterTop-base-000.x",
        subgame.player.presentation.weapon_channels[2].object);
    subgame.player.presentation.weapon_channels[2].animation_slots[0]
        .body.set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"blasterTop-base-000.x",
        subgame.player.presentation.weapon_channels[2].animation_slots[0]
            .body.object);
    subgame.player.presentation.weapon_channels[2].animation_slots[1]
        .body.set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"blasterTop-draw-000.x",
        subgame.player.presentation.weapon_channels[2].animation_slots[1]
            .body.object);
    subgame.player.presentation.weapon_channels[2].animation_slots[2]
        .body.set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"blasterTop-fire-000.x",
        subgame.player.presentation.weapon_channels[2].animation_slots[2]
            .body.object);
    subgame.player.presentation.weapon_channels[2].animation_slots[3]
        .body.set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"rocketlauncher-base-000.x",
        subgame.player.presentation.weapon_channels[2].animation_slots[3]
            .body.object);
    subgame.player.presentation.weapon_channels[2].animation_slots[4]
        .body.set_bod_object(g_object_list.add_object_to_list());
    loader->load_x_animation_clip(
        (char*)"rocketlauncher-draw-000.x",
        subgame.player.presentation.weapon_channels[2].animation_slots[4]
            .body.object);

    animation_count = 5;
    animation_slot =
        &subgame.player.presentation.weapon_channels[2].animation_slots[0];
    do {
        Object* animation_object = animation_slot->body.object;
        animation_object->flags |= 4;
        animation_object->apply_object_toon(0);
        animation_object->distort.z_wave = 0.0f;
        animation_object->distort.y_squash = 0.0f;
        animation_object->distort.xyz_scale = 0.0f;
        ++animation_slot;
    } while (--animation_count != 0);

    subgame.player.presentation.weapon_channels[2].object->flags |= 4;
    subgame.player.presentation.weapon_channels[2].object->apply_object_toon(0);
    subgame.player.presentation.weapon_channels[2].object->distort.z_wave = 0.0f;
    subgame.player.presentation.weapon_channels[2].object->distort.y_squash = 0.0f;
    subgame.player.presentation.weapon_channels[2].object->distort.xyz_scale = 0.0f;

    return 1;
}
