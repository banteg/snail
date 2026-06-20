// initialize_game_assets_and_world @ 0x40acf0 (thiscall)

#include <string.h>

#include "backdrop.h"
#include "bod_types.h"
#include "cameraman_state.h"
#include "directx_loader.h"
#include "game_root.h"
#include "galaxy_route_types.h"
#include "landscape_script_bank.h"
#include "logo_runtime.h"
#include "object_render_types.h"
#include "segment_catalog_types.h"
#include "sprite.h"
#include "thanks_screen.h"
#include "transform_matrix.h"
#include "voice_manager.h"

extern char* g_game_base; // data_4df904
extern int unk_4DF9BC; // data copied into +0x74654 during bootstrap
extern char byte_4B2F40; // cheat-state storage
extern char unk_74EB18; // cleared 0x15c-byte directx scratch
extern char unk_4F7050; // cleared 0x400-byte root scratch
extern void* off_4A2140; // sound bank table
extern BuiltinSegmentDefinition* off_4A63D0[]; // builtin segment table

int report_errorf(char* format, ...); // @ 0x431cc0
int debug_report_stub(char* format, ...); // @ 0x449c00
void sub_449C00(); // stripped no-arg debug callsite before path templates
void initialize_cheat(void* cheat); // @ recovered callsite
void initialize_blink_random(float* blink); // @ recovered callsite
void set_subgame_rate(float* blink, float rate); // @ recovered callsite
void reset_landscape_manager(void* manager); // @ recovered callsite
void load_segment_definitions(void* definitions); // @ recovered callsite
void load_level_definitions(); // @ 0x448900
void apply_audio_config_volumes(); // @ 0x41b070
void initialize_font_wave_state(); // @ 0x449c70
int initialize_font3d_objects(short font_id); // @ 0x44ae10
void sub_432D20(char* font_path, int font_id, float scale, double alpha); // @ font setup callsite
void initialize_overlay(void* overlay); // @ 0x407d40-family overlay init
void initialize_backdrop_slice_quad(Object* object, char* texture_path, float x_offset); // @ 0x41a1c0
void initialize_textured_backdrop_quad(Object* object, char* texture_path, float x_offset); // @ 0x41a2f0
void raise_backdrop_quad_edge_pair(int edge_pair, Object* object); // @ 0x41a440
void initialize_backdrop_corner_quad(int corner, Object* object, char* texture_path); // @ 0x41a450
void initialize_looptheloop_path_template_pair(
    void* path, float curve_source, int width_cells, int arg4,
    char* texture_a, char* texture_b, char* vertical_texture); // @ 0x41b0f0
void mirror_path_template_pair_x(void* destination, void* source); // @ 0x41bf00-family
void build_track_fringe_mesh(void* path, char* texture_path, float z_offset); // @ 0x420030-family
char* __stdcall initialize_sound_bank(void* entries); // @ 0x44dcb0
TextureRef* __stdcall register_sprite_texture(char* texture_path, int texture_id, int flags); // @ 0x44e0f0

static void link_root_bod(char* game, int offset)
{
    char* bod = game + offset;
    unsigned int* flags = (unsigned int*)(bod + 4);
    if ((*flags & 0x200) != 0) {
        report_errorf((char*)"List ADD");
        return;
    }

    char* head = game + 0x5ac;
    char* first = *(char**)head;
    if (first != 0) {
        *(char**)(first + 8) = bod;
        *(char**)(*(char**)(*(char**)head + 8) + 12) = *(char**)head;
        first = *(char**)(*(char**)head + 8);
        *(char**)head = first;
        *(int*)(first + 8) = 0;
    } else {
        *(char**)head = bod;
        *(int*)(bod + 8) = 0;
        *(int*)(*(char**)head + 12) = 0;
    }
    *flags |= 0x200;
}

static void initialize_overlay_slot(char* game, int slot_offset)
{
    link_root_bod(game, slot_offset);
    initialize_overlay(game + slot_offset);
}

static void register_core_sprite_textures()
{
    register_sprite_texture((char*)"Sprites/Debug.tga", 1, 0);
    register_sprite_texture((char*)"Sprites/Overlay.tga", 2, 0);
    register_sprite_texture((char*)"Sprites/Border.tga", 5, 0x400);
    register_sprite_texture((char*)"Sprites/Mouse.tga", 22, 0x400);
    register_sprite_texture((char*)"Sprites/Warning.tga", 94, 0x400);
    register_sprite_texture((char*)"Sprites/Play.tga", 27, 0x400);
    register_sprite_texture((char*)"Sprites/StartAI.tga", 32, 0x400);
    register_sprite_texture((char*)"Sprites/Jet.tga", 33, 0x400);
    register_sprite_texture((char*)"Sprites/Health.tga", 57, 0x400);
    register_sprite_texture((char*)"Sprites/DamageGuage.tga", 89, 0x400);
    register_sprite_texture((char*)"Sprites/DamageGuageFull.tga", 90, 0x400);
    register_sprite_texture((char*)"Sprites/DamageGuageBright.tga", 91, 0x400);
    register_sprite_texture((char*)"Sprites/Spark.tga", 92, 0x400);
    register_sprite_texture((char*)"Sprites/Black.tga", 93, 0x400);
    register_sprite_texture((char*)"Sprites/BorderGlow.tga", 99, 0x400);
    register_sprite_texture((char*)"Sprites/Slug000.tga", 118, 0x400);
    register_sprite_texture((char*)"Sprites/Slug001.tga", 119, 0x400);
    register_sprite_texture((char*)"Sprites/SlugMask.tga", 120, 0x400);
    register_sprite_texture((char*)"Sprites/Parcel000.tga", 121, 0x400);
    register_sprite_texture((char*)"Sprites/ParcelIcon.tga", 122, 0x400);
    register_sprite_texture((char*)"Sprites/GarbageA.tga", 114, 0x400);
    register_sprite_texture((char*)"Sprites/GarbageB.tga", 115, 0x400);
    register_sprite_texture((char*)"Sprites/GarbageC.tga", 116, 0x400);
    register_sprite_texture((char*)"Sprites/GarbageD.tga", 117, 0x400);
    register_sprite_texture((char*)"Sprites/Life.tga", 123, 0x400);
    register_sprite_texture((char*)"Sprites/JetPack000.tga", 124, 0x400);
    register_sprite_texture((char*)"Sprites/Smoke.tga", 128, 0x400);
    register_sprite_texture((char*)"Sprites/SlugGoo.tga", 129, 0x400);
    register_sprite_texture((char*)"Sprites/SliderBar.tga", 36, 0x400);
    register_sprite_texture((char*)"Sprites/SliderBarFull.tga", 37, 0x400);
    register_sprite_texture((char*)"Sprites/Less.tga", 38, 0x400);
    register_sprite_texture((char*)"Sprites/LessHover.tga", 40, 0x400);
    register_sprite_texture((char*)"Sprites/LessMask.tga", 41, 0x420);
    register_sprite_texture((char*)"Sprites/More.tga", 42, 0x400);
    register_sprite_texture((char*)"Sprites/MoreHover.tga", 44, 0x400);
    register_sprite_texture((char*)"Sprites/MoreMask.tga", 45, 0x420);
    register_sprite_texture((char*)"Galaxy/SpaceMapLogo.tga", 138, 0x400);
    register_sprite_texture((char*)"Galaxy/Galaxy000.tga", 139, 0x400);
    register_sprite_texture((char*)"Galaxy/Galaxy001.tga", 140, 0x400);
    register_sprite_texture((char*)"Galaxy/Galaxy002.tga", 141, 0x400);
    register_sprite_texture((char*)"Galaxy/Galaxy003.tga", 142, 0x400);
    register_sprite_texture((char*)"Galaxy/Galaxy004.tga", 143, 0x400);
    register_sprite_texture((char*)"Galaxy/Galaxy005.tga", 144, 0x400);
    register_sprite_texture((char*)"Galaxy/Galaxy006.tga", 145, 0x400);
    register_sprite_texture((char*)"Galaxy/Galaxy007.tga", 146, 0x400);
    register_sprite_texture((char*)"Galaxy/Galaxy008.tga", 147, 0x400);
    register_sprite_texture((char*)"Galaxy/Galaxy009.tga", 148, 0x400);
    register_sprite_texture((char*)"Galaxy/GalaxySelect.tga", 149, 0x400);
    register_sprite_texture((char*)"Galaxy/LevelSelect.tga", 150, 0x400);
    register_sprite_texture((char*)"Galaxy/LevelStar.tga", 151, 0x400);
    register_sprite_texture((char*)"Galaxy/BorderSpacemap.tga", 152, 0x400);
    register_sprite_texture((char*)"Galaxy/Line.tga", 153, 0x400);
    register_sprite_texture((char*)"Galaxy/LineStar.tga", 154, 0x400);
}

static void initialize_world_backdrop_island(char* game)
{
    int i = 0;
    do {
        int base = 56 * i;
        ((BodBase*)(game + 0x44790 + base))->set_bod_object(g_object_list.add_object_to_list());
        initialize_backdrop_slice_quad(
            *(Object**)(game + 0x447b4 + base),
            (char*)"Objects/World00/Track0.tga",
            (float)i);

        ((BodBase*)(game + 0x44950 + base))->set_bod_object(g_object_list.add_object_to_list());
        initialize_backdrop_slice_quad(
            *(Object**)(game + 0x44974 + base),
            (char*)"Objects/World00/Track1.tga",
            (float)i);

        ((BodBase*)(game + 0x44b10 + base))->set_bod_object(g_object_list.add_object_to_list());
        initialize_backdrop_slice_quad(
            *(Object**)(game + 0x44b34 + base),
            (char*)"Objects/World00/TrackWarn.tga",
            (float)i);
        ++i;
    } while (i < 8);
}

static void initialize_pillar_island(char* game)
{
    TransformMatrix matrix;
    set_matrix_identity(&matrix);

    static char* meshes[] = {
        (char*)"pillar1.x",
        (char*)"pillar2.x",
        (char*)"pillar3.x",
        (char*)"pillar4.x",
        (char*)"pillar5.x",
        (char*)"pillar6.x",
        (char*)"pillar7.x",
        (char*)"pillar8.x",
    };

    int i = 0;
    do {
        int offset = 0x445d0 + i * 0x38;
        ((BodBase*)(game + offset))->set_bod_object(g_object_list.add_object_to_list());
        ((DirectXLoader*)(game + 0x48e00))
            ->load_x_mesh(meshes[i], *(void**)(game + offset + 0x24), 1);
        ((BodBase*)(game + offset))->apply_bod_position(&matrix);
        ++i;
    } while (i < 8);
}

static void initialize_small_track_template_island(char* game)
{
    char* dark = (char*)"Objects/Path/VeryDark.tga";
    char* ramp = (char*)"Objects/Universe/Ramp.tga";
    char* fringe = (char*)"Objects/Universe/Fringe.tga";

    ((BodBase*)(game + 0x106bd5c))->set_bod_object(g_object_list.add_object_to_list());
    initialize_looptheloop_path_template_pair(
        game + 0x106bd5c, 6.0f, 3, 1, dark, ramp, (char*)"Objects/Path/Vert.tga");
    *(int*)(game + 0x106bd74) = 0;
    *(int*)(game + 0x106bd70) = 0;
    *(int*)(game + 0x106bd6c) = 0;

    ((BodBase*)(game + 0x106be04))->set_bod_object(g_object_list.add_object_to_list());
    mirror_path_template_pair_x(game + 0x106be04, game + 0x106bd5c);
    *(int*)(game + 0x106be1c) = 0;
    *(int*)(game + 0x106be18) = 0;
    *(int*)(game + 0x106be14) = 0;

    build_track_fringe_mesh(game + 0x106bd5c, fringe, 0.0f);
    *(int*)(game + 0x106bdd4) = 0;
    *(int*)(game + 0x106bdd0) = 0;
    *(int*)(game + 0x106bdcc) = 0;
    build_track_fringe_mesh(game + 0x106be04, fringe, 0.0f);
    *(int*)(game + 0x106be7c) = 0;
    *(int*)(game + 0x106be78) = 0;
    *(int*)(game + 0x106be74) = 0;
}

char GameRoot::initialize_game_assets_and_world()
{
    char* game = (char*)this;

    ((Color4f*)(game + 0x14))->store_color4f(1.0f, 1.0f, 1.0f, 1.0f);
    *(float*)(game + 0x10) = 1.0f;
    *(float*)(game + 0x08) = 30.0f;
    *(float*)(game + 0x0c) = 50.0f;
    *(unsigned char*)(game + 0x04) = 1;
    *(int*)(game + 0x40) = 2;
    *(unsigned char*)(game + 0x568) = 0;
    *(unsigned char*)(game + 0x74659) = 0;

    initialize_cheat(&byte_4B2F40);
    *(unsigned char*)(game + 0x4f2e0) = 0;
    initialize_blink_random((float*)(game + 0x74618));
    set_subgame_rate((float*)(game + 0x74618), 1.1f);
    *(int*)(game + 0x56c) = 2;
    *(int*)(game + 0x3c) = 1;

    g_texture_refs.initialize_texture_list(500);
    g_object_list.initialize_object_list(3000);
    *(int*)(game + 0x514) = 0;
    *(int*)(game + 0x518) = 0;
    *(int*)(game + 0x51c) = 0;
    *(int*)(game + 0x57c) = 0;
    *(int*)(game + 0x5b0) = (int)(game + 0x570);
    *(int*)(game + 0x5ac) = 0;
    *(int*)(game + 0xb48) = 0;
    memset(&unk_4F7050, 0, 0x400);

    *(int*)(game + 0x5b8) = 0;
    *(int*)(game + 0x5bc) = 0x1000003;
    *(int*)(game + 0x5d4) = (int)(game + 0x6fc);
    *(int*)(game + 0x5c0) = 0;
    *(int*)(game + 0x5c4) = 0;
    *(float*)(game + 0x5c8) = 1.0f;
    *(float*)(game + 0x5cc) = 1.0f;
    *(unsigned char*)(game + 0x628) = 0;
    initialize_overlay_slot(game, 0x67c);

    memset(&unk_74EB18, 0, 0x15c);
    ((DirectXLoader*)(game + 0x48e00))->initialize_directx_loader();
    reset_landscape_manager(game + 0x106c218);
    load_segment_definitions(game + 0x1075fac);
    ((LandscapeScriptBank*)(game + 0x106c218))->load_landscape_script_by_name((char*)"Starmap.txt");
    ((LandscapeScriptBank*)(game + 0x106c218))->load_landscape_script_by_name((char*)"Splash.txt");
    ((LandscapeScriptBank*)(game + 0x106c218))->load_landscape_script_by_name((char*)"Help.txt");

    *(int*)(game + 0x74654) = unk_4DF9BC;
    ((ThanksScreenOwner*)(game + 0x12d3b78))->open_thanks_screen();
    ((ThanksScreenOwner*)(game + 0x12d3ba4))->open_thanks_screen();
    ((GalaxyRoute*)(game + 0x12d3bb8))->load_galaxy_layout();
    ((CameramanState*)(game + 0x54e8c))->initialize_cameraman();
    ((LogoRuntime*)(game + 0x4f400))->open_logo();
    initialize_sound_bank(&off_4A2140);
    g_voice_manager.initialize_voice_manager();
    apply_audio_config_volumes();
    load_level_definitions();
    ((LandscapeScriptBank*)(game + 0x106c218))->load_landscape_script_by_name((char*)"Menubg.txt");
    ((LevelSegmentSlotStore*)(game + 0x224a04))->load_builtin_segment_definitions(off_4A63D0);

    *(int*)(game + 0x5e0) = 1;
    *(int*)(game + 0x5e4) = 0x2000001;
    *(int*)(game + 0x288) = 0x2000000;
    *(int*)(game + 0x658) = 1;
    *(int*)(game + 0x65c) = 0x10000003;
    *(int*)(game + 0x480) = 0x10000000;
    initialize_overlay_slot(game, 0x914);
    initialize_overlay_slot(game, 0x7c8);

    sub_432D20((char*)"Objects/Font/Font-menu-hover.tga", 2, 0.800000012f, 1.0);
    initialize_font3d_objects(0);
    initialize_font_wave_state();
    g_sprite_manager.initialize_sprite_manager();
    register_core_sprite_textures();

    initialize_world_backdrop_island(game);
    initialize_pillar_island(game);

    ((BodBase*)(game + 0x44d10))->set_bod_object(g_object_list.add_object_to_list());
    initialize_textured_backdrop_quad(
        *(Object**)(game + 0x44d34), (char*)"Objects/Universe/Hole.tga", 0.0f);
    raise_backdrop_quad_edge_pair(-1, *(Object**)(game + 0x44d34));
    ((BodBase*)(game + 0x44d48))->set_bod_object(g_object_list.add_object_to_list());
    initialize_textured_backdrop_quad(
        *(Object**)(game + 0x44d6c), (char*)"Objects/Universe/Hole.tga", 0.0f);
    raise_backdrop_quad_edge_pair(0, *(Object**)(game + 0x44d6c));
    ((BodBase*)(game + 0x44d80))->set_bod_object(g_object_list.add_object_to_list());
    initialize_textured_backdrop_quad(
        *(Object**)(game + 0x44da4), (char*)"Objects/Universe/Hole.tga", 0.0f);
    raise_backdrop_quad_edge_pair(1, *(Object**)(game + 0x44da4));

    ((BodBase*)(game + 0x44218))->set_bod_object(g_object_list.add_object_to_list());
    initialize_backdrop_corner_quad(
        0, *(Object**)(game + 0x4423c), (char*)"Objects/World00/Track0.tga");
    ((BodBase*)(game + 0x44250))->set_bod_object(g_object_list.add_object_to_list());
    initialize_backdrop_corner_quad(
        1, *(Object**)(game + 0x44274), (char*)"Objects/World00/Track0.tga");

    ((BodBase*)(game + 0x44100))->set_bod_object(g_object_list.add_object_to_list());
    ((DirectXLoader*)(game + 0x48e00))
        ->load_x_mesh((char*)"Tramp.x", *(void**)(game + 0x44124), 1);
    *(int*)(*(int*)(game + 0x44124) + 0x14) = 6;

    ((BodBase*)(game + 0x441d0))->set_bod_object(g_object_list.add_object_to_list());
    initialize_textured_backdrop_quad(
        *(Object**)(game + 0x441f4), (char*)"Objects/Universe/Ramp.tga", 0.0f);
    *(int*)(*(int*)(game + 0x441f4) + 0x14) = 5;

    ((BodBase*)(game + 0x44db8))->set_bod_object(g_object_list.add_object_to_list());
    load_object_definition((char*)"Objects/Lazer", *(Object**)(game + 0x44ddc));

    initialize_small_track_template_island(game);

    sub_449C00();
    return 1;
}
