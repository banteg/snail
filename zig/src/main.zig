const std = @import("std");
const rl = @import("raylib");
const app = @import("app.zig");
const app_ui = @import("app_ui.zig");
const assets = @import("assets.zig");
const background = @import("background.zig");
const config = @import("config.zig");
const debug_levels = @import("debug_levels.zig");
const frontend = @import("frontend.zig");
const frontend_widget = @import("frontend_widget.zig");
const galaxy = @import("galaxy.zig");
const game_font = @import("game_font.zig");
const gameplay = @import("gameplay.zig");
const high_score = @import("high_score.zig");
const intro = @import("intro.zig");
const level_prompt = @import("level_prompt.zig");
const sim = @import("sim.zig");
const track = @import("track.zig");
const track_render = @import("track_render.zig");
const loading_screen = @import("loading_screen.zig");
const object = @import("object.zig");
const segment = @import("segment.zig");
const level = @import("level.zig");
const runtime_state = @import("runtime_state.zig");
const x2 = @import("x2.zig");
const xanim = @import("xanim.zig");

const default_archive_path = app.default_archive_path;
const default_screenshot_dir = app.default_screenshot_dir;
const intro_background_path = app.intro_background_path;
const main_menu_background_path = app.main_menu_background_path;
const help_background_path = app.help_background_path;
const route_map_background_path = app.route_map_background_path;
const thanks_screen_background_path = app.thanks_screen_background_path;
const route_map_logo_texture_path = app.route_map_logo_texture_path;
const route_map_border_texture_path = app.route_map_border_texture_path;
const route_map_galaxy_select_texture_path = app.route_map_galaxy_select_texture_path;
const route_map_level_select_texture_path = app.route_map_level_select_texture_path;
const route_map_level_star_texture_path = app.route_map_level_star_texture_path;
const route_map_line_texture_path = app.route_map_line_texture_path;
const route_map_line_star_texture_path = app.route_map_line_star_texture_path;
const route_map_galaxy_texture_paths = app.route_map_galaxy_texture_paths;
const frontend_cursor_texture_path = app.frontend_cursor_texture_path;
const widget_border_texture_path = app.widget_border_texture_path;
const completion_parcel_icon_texture_path = app.completion_parcel_icon_texture_path;
const frontend_highlight_sound_path = app.frontend_highlight_sound_path;
const frontend_select_sound_path = app.frontend_select_sound_path;
const slider_less_texture_path = app.slider_less_texture_path;
const slider_less_hover_texture_path = app.slider_less_hover_texture_path;
const slider_more_texture_path = app.slider_more_texture_path;
const slider_more_hover_texture_path = app.slider_more_hover_texture_path;
const slider_bar_texture_path = app.slider_bar_texture_path;
const slider_bar_full_texture_path = app.slider_bar_full_texture_path;
const galaxy_names_path = app.galaxy_names_path;
const intro_script_path = app.intro_script_path;
const credits_script_path = app.credits_script_path;
const intro_music_path = app.intro_music_path;
const default_texture_path = app.default_texture_path;
const default_audio_path = app.default_audio_path;
const default_model_path = app.default_model_path;
const default_object_path = app.default_object_path;
const gameplay_turbo_talk_model_path = "X/TURBO-TALK-000.X2";
const gameplay_turbo_into_shell_model_path = "X/TURBO-INTOSHELL-000.X2";
const gameplay_barrier_object_path = "OBJECTS/BARRIER/_OBJECT.TXT";
const gameplay_lazer_object_path = "OBJECTS/LAZER/_OBJECT.TXT";
const gameplay_vapour_lazer_object_path = "OBJECTS/VAPOURLAZER/_OBJECT.TXT";
const gameplay_salt_model_path = "X/SALT.X2";
const gameplay_turret_model_path = "X/BLASTERTOP-BASE-000.X2";
const gameplay_blaster_top_model_path = "X/BLASTERTOP-BASE-000.X2";
const gameplay_blaster_top_draw_model_paths = [_][]const u8{
    "X/BLASTERTOP-DRAW-000.X2",
    "X/BLASTERTOP-DRAW-001.X2",
    "X/BLASTERTOP-DRAW-002.X2",
    "X/BLASTERTOP-DRAW-003.X2",
    "X/BLASTERTOP-DRAW-004.X2",
    "X/BLASTERTOP-DRAW-005.X2",
};
const gameplay_blaster_top_fire_model_path = "X/BLASTERTOP-FIRE-000.X2";
const gameplay_laser_left_model_path = "X/LASERLEFT-BASE-000.X2";
const gameplay_laser_left_draw_model_paths = [_][]const u8{
    "X/LASERLEFT-DRAW-000.X2",
    "X/LASERLEFT-DRAW-001.X2",
    "X/LASERLEFT-DRAW-002.X2",
    "X/LASERLEFT-DRAW-003.X2",
};
const gameplay_laser_right_model_path = "X/LASERRIGHT-BASE-000.X2";
const gameplay_laser_right_draw_model_paths = [_][]const u8{
    "X/LASERRIGHT-DRAW-000.X2",
    "X/LASERRIGHT-DRAW-001.X2",
    "X/LASERRIGHT-DRAW-002.X2",
    "X/LASERRIGHT-DRAW-003.X2",
};
const gameplay_rocket_launcher_model_path = "X/ROCKETLAUNCHER-BASE-000.X2";
const gameplay_rocket_launcher_draw_model_paths = [_][]const u8{
    "X/ROCKETLAUNCHER-DRAW-000.X2",
    "X/ROCKETLAUNCHER-DRAW-001.X2",
    "X/ROCKETLAUNCHER-DRAW-002.X2",
};
const gameplay_rocket_model_path = "X/ROCKET-BASE-000.X2";
const gameplay_invincible_model_paths = [_][]const u8{
    "X/INVINCIBLE-BASE-000.X2",
    "X/INVINCIBLE-BASE-001.X2",
    "X/INVINCIBLE-BASE-002.X2",
    "X/INVINCIBLE-BASE-003.X2",
};
const gameplay_slug_sprite_paths = [_][]const u8{
    "SPRITES/SLUG000.TGA",
    "SPRITES/SLUG001.TGA",
};
const gameplay_garbage_sprite_paths = [_][]const u8{
    "SPRITES/GARBAGEA.TGA",
    "SPRITES/GARBAGEB.TGA",
    "SPRITES/GARBAGEC.TGA",
    "SPRITES/GARBAGED.TGA",
};
const gameplay_health_sprite_path = "SPRITES/HEALTH.TGA";
const gameplay_jetpack_sprite_paths = [_][]const u8{
    "SPRITES/JETPACK000.TGA",
    "SPRITES/JETPACK001.TGA",
};
const gameplay_parcel_sprite_path = "SPRITES/PARCEL000.TGA";
const gameplay_ring_sprite_path = "SPRITES/PARTICLERING-SMALL.TGA";
const gameplay_ring_big_sprite_path = "SPRITES/PARTICLERING-BIG.TGA";
const gameplay_slow_ring_sprite_path = "SPRITES/PARTICLESLOW-SMALL.TGA";
const gameplay_powerup_sprite_path = "SPRITES/PARTICLEBLASTERS.TGA";
const gameplay_life_sprite_path = "SPRITES/LIFE.TGA";
const gameplay_progress_bar_sprite_path = "SPRITES/PROGRESS-BAR.TGA";
const gameplay_progress_bar_lit_sprite_path = "SPRITES/PROGRESS-BAR-LIT.TGA";
const gameplay_progress_cursor_sprite_path = "SPRITES/PROGRESS-CURSOR.TGA";
const gameplay_damage_gauge_sprite_path = "SPRITES/DAMAGEGUAGE.TGA";
const gameplay_damage_gauge_full_sprite_path = "SPRITES/DAMAGEGUAGEFULL.TGA";
const gameplay_damage_gauge_bright_sprite_path = "SPRITES/DAMAGEGUAGEBRIGHT.TGA";
const gameplay_warning_sprite_path = "SPRITES/WARNING.TGA";
const gameplay_explode_big_sprite_path = "SPRITES/PARTICLEEXPLODE-BIG.TGA";
const gameplay_explode_small_sprite_path = "SPRITES/PARTICLEEXPLODE-SMALL.TGA";
const gameplay_slug_goo_sprite_path = "SPRITES/SLUGGOO.TGA";
const gameplay_smoke_sprite_path = "SPRITES/SMOKE.TGA";
const background_light_streak_sprite_path = background.light_streak_sprite_path;
const gameplay_turbo_fire_sound_paths = [_][]const u8{
    "SFX2/TURBOFIRE1.OGG",
    "SFX2/TURBOFIRE2.OGG",
};
const gameplay_laser_sound_paths = [_][]const u8{
    "SFX2/LASER1.OGG",
    "SFX2/LASER2.OGG",
    "SFX2/LASER3.OGG",
};
const gameplay_rocket_sound_paths = [_][]const u8{
    "SFX2/ROCKET1.OGG",
    "SFX2/ROCKET2.OGG",
    "SFX2/ROCKET3.OGG",
};
const gameplay_heart_sound_path = "SFX2/HEART.OGG";
const gameplay_jetpack_sound_path = "SFX2/JETPACK.OGG";
const gameplay_jetpack_shutoff_sound_path = "SFX2/SERVO2.OGG";
const gameplay_slow_ring_sound_path = "SFX2/SLOWRING.OGG";
const gameplay_invincible_sound_path = "SFX2/INVINCIBLE.OGG";
const gameplay_explode_ring_sound_path = "SFX2/EXPLODERING.OGG";
const gameplay_enemy_fire_sound_path = "SFX2/ENEMYFIRE.OGG";
const gameplay_boing_sound_path = "SFX2/BOING.OGG";
const gameplay_completion_init_sound_path = "SFX2/SKIDSTOP.OGG";
const gameplay_row_event_confirm_sound_path = "SFX2/SELECT.OGG";
const gameplay_place_package_sound_path = "SFX2/PLACEPACKAGE.OGG";
const gameplay_package_count_sound_path = "SFX2/PACKAGECOUNT.OGG";
const gameplay_perfect_sound_path = "SFX2/PERFECT.OGG";
const gameplay_powerup_pickup_sound_paths = [_][]const u8{
    "SFX2/PW1.OGG",
    "SFX2/PW2.OGG",
    "SFX2/PW3.OGG",
    "SFX2/PW4.OGG",
    "SFX2/PW5.OGG",
    "SFX2/PW6.OGG",
    "SFX2/PW7.OGG",
};
const native_jetpack_visual_shutoff_threshold: f32 = 0.94;
const gameplay_asteroid_impact_sound_paths = [_][]const u8{
    "SFX2/ASTEROIDIMPACT1.OGG",
    "SFX2/ASTEROIDIMPACT2.OGG",
};
const gameplay_wall_hit_sound_path = "SFX2/WALLHIT.OGG";
const gameplay_slug_hit_voice_paths = [_][]const u8{
    "VOICE/SLUG-HIT1.OGG",
    "VOICE/SLUG-HIT2.OGG",
    "VOICE/SLUG-HIT3.OGG",
};
const gameplay_slug_ambient_voice_paths = [_][]const u8{
    "VOICE/BACKOFFSLUGS.OGG",
    "VOICE/SLUG-SNAILALERT.OGG",
    "VOICE/SLUG-HESTOOFAST.OGG",
    "VOICE/SLUG-GOTHIM.OGG",
};
const gameplay_slug_death_voice_paths = [_][]const u8{
    "VOICE/SLUG-DEATH1.OGG",
    "VOICE/SLUG-DEATH2.OGG",
};
const gameplay_native_voice_damage_paths = [_][]const u8{
    "VOICE/HEYIJUSTWAXED.OGG",
    "VOICE/IMGONNANEEDANEWSHELL.OGG",
    "VOICE/ITBURNS.OGG",
    "VOICE/MYEYES.OGG",
    "VOICE/THATSGONNALEAVEAMARK.OGG",
    "VOICE/UHOH.OGG",
};
const gameplay_native_voice_dying_paths = [_][]const u8{
    "VOICE/ABANDONSHELL.OGG",
    "VOICE/IMFALLINGANDICANTGETUP.OGG",
    "VOICE/INEEDANEWJOB.OGG",
    "VOICE/NOTCOOL.OGG",
    "VOICE/THISISNOTMYDAY.OGG",
};
const gameplay_native_voice_slugged_paths = [_][]const u8{
    "VOICE/INEEDANEWJOB.OGG",
    "VOICE/NOTCOOL.OGG",
    "VOICE/THISISNOTMYDAY.OGG",
};
const gameplay_native_voice_enemies_paths = [_][]const u8{
    "VOICE/ALWAYSTIPYOURMAILCARRIER.OGG",
    "VOICE/ALWAYSTIPYOURPOSTALWORKER.OGG",
    "VOICE/BACKOFF.OGG",
    "VOICE/BACKOFFSLUGS.OGG",
    "VOICE/COMINGTHROUGH.OGG",
    "VOICE/MAKEWAY.OGG",
};
const gameplay_native_voice_fall_paths = [_][]const u8{
    "VOICE/FALL1.OGG",
    "VOICE/FALL2.OGG",
    "VOICE/FALL3.OGG",
};
const gameplay_native_voice_misc_paths = [_][]const u8{
    "VOICE/CHECKMEOUT.OGG",
    "VOICE/DONTHATEME.OGG",
    "VOICE/FOOTACHE.OGG",
    "VOICE/GOTMAIL.OGG",
    "VOICE/ISURECOULDUSE.OGG",
    "VOICE/ITSNOTJUSTASHELL.OGG",
    "VOICE/MYNAMEISTURBO.OGG",
    "VOICE/PARTFOOTPARTTUMMY.OGG",
    "VOICE/SNAILSINSPACE.OGG",
    "VOICE/THATWASCOOL.OGG",
    "VOICE/HELLINASHELL.OGG",
    "VOICE/TRAILBLAZER.OGG",
    "VOICE/ESCARGOT.OGG",
};
const gameplay_native_voice_victory_paths = [_][]const u8{
    "VOICE/HOWSTHATFOREXPRESSSERVICE.OGG",
    "VOICE/IDESERVEAPROMOTION.OGG",
    "VOICE/IDESERVEARAISE.OGG",
    "VOICE/IGOTAHOTFOOT.OGG",
    "VOICE/IMTHESNAIL.OGG",
    "VOICE/ONTIMEANDFEELINGFINE.OGG",
    "VOICE/SOMEBODYPINCHME.OGG",
};
const gameplay_native_voice_ouch_paths = [_][]const u8{
    "VOICE/OW1.OGG",
    "VOICE/OW2.OGG",
    "VOICE/OW3.OGG",
    "VOICE/OW4.OGG",
};
const gameplay_native_voice_worm_tunnel_paths = [_][]const u8{
    "VOICE/WHOAHDUDE.OGG",
    "VOICE/ZIPPIDYDOODAH.OGG",
    "VOICE/WHOHOHOHOAH.OGG",
};
const gameplay_native_voice_supertramp_paths = [_][]const u8{
    "VOICE/WHOAHDUDE.OGG",
    "VOICE/WOOHOO.OGG",
    "VOICE/WHOHOHOHOAH.OGG",
};
const gameplay_native_voice_package_paths = [_][]const u8{
    "VOICE/POSTAGEDUE.OGG",
    "VOICE/SOMEBODYCALLFORADELIVERY.OGG",
    "VOICE/SPECIALDELIVERY.OGG",
    "VOICE/SPEEDYDELIVERY.OGG",
};
const gameplay_native_voice_powerup_paths = [_][]const u8{
    "VOICE/FULLYLOADED.OGG",
    "VOICE/HELLINASHELL.OGG",
    "VOICE/IMONFIRE.OGG",
    "VOICE/IMONFIREBABY.OGG",
    "VOICE/IMPACKIN.OGG",
    "VOICE/MYNEWMAILINGTECHNIQUE.OGG",
    "VOICE/MYSHELLISTRICKEDOUT.OGG",
    "VOICE/SMOKIN.OGG",
    "VOICE/SOMEBODYSTOPME.OGG",
    "VOICE/TRAILBLAZER.OGG",
    "VOICE/THATWASAWESOME.OGG",
};
const gameplay_native_voice_slow_paths = [_][]const u8{
    "VOICE/AMIEVENMOVING.OGG",
    "VOICE/ANYSLOWER.OGG",
    "VOICE/COMEON.OGG",
    "VOICE/FASTERISBETTER.OGG",
    "VOICE/ICANDOBETTER.OGG",
    "VOICE/FASTERWOULDBEBETTER.OGG",
    "VOICE/ISLEEPFASTERTHANTHIS.OGG",
};
const gameplay_native_voice_start_paths = [_][]const u8{
    "VOICE/ALLOWSIXTOEIGHTMINUTES.OGG",
    "VOICE/BRINGITON.OGG",
    "VOICE/IFEELTHENEEDFORSPEED.OGG",
    "VOICE/JUSTRYANDSTOPME.OGG",
    "VOICE/THISISAJOB.OGG",
    "VOICE/TURBOSTHENAME.OGG",
    "VOICE/WATCHOUT.OGG",
    "VOICE/ZOOMZOOM.OGG",
    "VOICE/SNAILMAILALWAYSONTIME.OGG",
    "VOICE/SNAILMAILINTHIRTYMINUTES.OGG",
};
const gameplay_native_voice_tutorial_paths = [_][]const u8{
    "VOICE/TUT1.OGG",
    "VOICE/TUT2.OGG",
    "VOICE/TUT3.OGG",
    "VOICE/TUT4.OGG",
    "VOICE/TUT5.OGG",
    "VOICE/TUT6.OGG",
    "VOICE/TUT7.OGG",
    "VOICE/TUT8.OGG",
    "VOICE/TUT9.OGG",
    "VOICE/TUT10.OGG",
    "VOICE/TUT11.OGG",
    "VOICE/TUT12.OGG",
    "VOICE/TUT13.OGG",
    "VOICE/TUT14.OGG",
    "VOICE/TUT15.OGG",
    "VOICE/TUT16.OGG",
    "VOICE/TUT17.OGG",
    "VOICE/TUT18.OGG",
};
const gameplay_native_voice_postal_paths = [_][]const u8{
    "VOICE/IMGOINGPOSTAL.OGG",
    "VOICE/IMGOINGPOSTAL2.OGG",
    "VOICE/IMGOINGPOSTAL3.OGG",
};
const gameplay_cheers_sound_path = "SFX2/CHEERS.OGG";
const gameplay_extra_life_sound_path = "SFX2/EXTRALIFE.OGG";
const gameplay_weapon_change_sound_path = "SFX2/SERVO1.OGG";
const gameplay_postal_warning_sound_path = "SFX2/POSTALLOOP.OGG";
const native_gameplay_voice_set_cooldown_step: f32 = 1.0 / 240.0;
const native_gameplay_voice_manager_global_step: f32 = 1.0 / 60.0;
const native_gameplay_voice_manager_frequency_seconds: f32 = 20.0;
const native_gameplay_slow_voice_timer_step: f32 = 1.0 / 60.0;
const native_gameplay_start_voice_tick: u64 = 18;
const native_runtime_tile_wall: u8 = 0x0e;
const default_level_path = app.default_level_path;
const simulation_step_seconds = 1.0 / 60.0;
const status_message_duration_ticks: u32 = 180;
const Options = app.Options;
const AppCommand = app.AppCommand;
const AutoScreenshot = app.AutoScreenshot;
const MouseLocalOverride = app.MouseLocalOverride;
const WindowSize = app.WindowSize;
const parseArgs = app.parseArgs;
const defaultWindowSizeForCommand = app.defaultWindowSizeForCommand;

const BootTask = frontend.BootTask;
const boot_tasks = frontend.boot_tasks;
const GamePhase = frontend.GamePhase;
const FrontendTransition = frontend.FrontendTransition;
const MainMenuItem = frontend.MainMenuItem;
const main_menu_items = frontend.main_menu_items;
const NewGameMenuItem = frontend.NewGameMenuItem;
const new_game_menu_items = frontend.new_game_menu_items;
const FrontendLevelMode = frontend.FrontendLevelMode;
const OptionsMenuItem = frontend.OptionsMenuItem;
const options_menu_items = frontend.options_menu_items;
const PauseMenuItem = frontend.PauseMenuItem;
const pause_menu_items = frontend.pause_menu_items;
const RouteMenuAction = frontend.RouteMenuAction;
const frontendRouteModeLabel = frontend.frontendRouteModeLabel;
const routeMenuActionLabel = frontend.routeMenuActionLabel;
const routeMenuHint = frontend.routeMenuHint;
const frontendLevelPath = frontend.frontendLevelPath;

const MenuPanels = app_ui.MenuPanels;
const VirtualLayout = app_ui.VirtualLayout;

const ScreenshotRequest = struct {
    relative_path_z: [:0]u8,
    exit_after_capture: bool,

    fn deinit(self: *ScreenshotRequest, allocator: std.mem.Allocator) void {
        allocator.free(self.relative_path_z);
    }
};

const SliderArt = struct {
    less: ?assets.LoadedTexture = null,
    less_hover: ?assets.LoadedTexture = null,
    more: ?assets.LoadedTexture = null,
    more_hover: ?assets.LoadedTexture = null,
    bar: ?assets.LoadedTexture = null,
    bar_full: ?assets.LoadedTexture = null,

    fn unload(self: *SliderArt) void {
        if (self.less) |*texture| {
            texture.unload();
            self.less = null;
        }
        if (self.less_hover) |*texture| {
            texture.unload();
            self.less_hover = null;
        }
        if (self.more) |*texture| {
            texture.unload();
            self.more = null;
        }
        if (self.more_hover) |*texture| {
            texture.unload();
            self.more_hover = null;
        }
        if (self.bar) |*texture| {
            texture.unload();
            self.bar = null;
        }
        if (self.bar_full) |*texture| {
            texture.unload();
            self.bar_full = null;
        }
    }

    fn textures(self: SliderArt) frontend_widget.SliderTextures {
        return .{
            .less = if (self.less) |texture| texture.texture else null,
            .less_hover = if (self.less_hover) |texture| texture.texture else null,
            .more = if (self.more) |texture| texture.texture else null,
            .more_hover = if (self.more_hover) |texture| texture.texture else null,
            .bar = if (self.bar) |texture| texture.texture else null,
            .bar_full = if (self.bar_full) |texture| texture.texture else null,
        };
    }
};

const FrontendWidgetArt = struct {
    border: ?assets.LoadedTexture = null,
    parcel_icon: ?assets.LoadedTexture = null,

    fn unload(self: *FrontendWidgetArt) void {
        if (self.border) |*texture| {
            texture.unload();
            self.border = null;
        }
        if (self.parcel_icon) |*texture| {
            texture.unload();
            self.parcel_icon = null;
        }
    }
};

const FrontendSoundFx = struct {
    highlight: ?assets.LoadedSound = null,
    select: ?assets.LoadedSound = null,

    fn unload(self: *FrontendSoundFx) void {
        if (self.highlight) |*sound| {
            sound.unload();
            self.highlight = null;
        }
        if (self.select) |*sound| {
            sound.unload();
            self.select = null;
        }
    }
};

const GameplaySpriteArt = struct {
    slug_frames: [gameplay_slug_sprite_paths.len]?assets.LoadedTexture = [_]?assets.LoadedTexture{null} ** gameplay_slug_sprite_paths.len,
    garbage_variants: [gameplay_garbage_sprite_paths.len]?assets.LoadedTexture = [_]?assets.LoadedTexture{null} ** gameplay_garbage_sprite_paths.len,
    health: ?assets.LoadedTexture = null,
    life: ?assets.LoadedTexture = null,
    jetpack_frames: [gameplay_jetpack_sprite_paths.len]?assets.LoadedTexture = [_]?assets.LoadedTexture{null} ** gameplay_jetpack_sprite_paths.len,
    parcel: ?assets.LoadedTexture = null,
    ring: ?assets.LoadedTexture = null,
    ring_big: ?assets.LoadedTexture = null,
    slow_ring: ?assets.LoadedTexture = null,
    powerup: ?assets.LoadedTexture = null,
    progress_bar: ?assets.LoadedTexture = null,
    progress_bar_lit: ?assets.LoadedTexture = null,
    progress_cursor: ?assets.LoadedTexture = null,
    damage_gauge: ?assets.LoadedTexture = null,
    damage_gauge_full: ?assets.LoadedTexture = null,
    damage_gauge_bright: ?assets.LoadedTexture = null,
    warning: ?assets.LoadedTexture = null,
    explode_big: ?assets.LoadedTexture = null,
    explode_small: ?assets.LoadedTexture = null,
    slug_goo: ?assets.LoadedTexture = null,
    smoke: ?assets.LoadedTexture = null,

    fn unload(self: *GameplaySpriteArt) void {
        for (&self.slug_frames) |*texture| {
            if (texture.*) |*loaded| {
                loaded.unload();
                texture.* = null;
            }
        }
        for (&self.garbage_variants) |*texture| {
            if (texture.*) |*loaded| {
                loaded.unload();
                texture.* = null;
            }
        }
        if (self.health) |*texture| {
            texture.unload();
            self.health = null;
        }
        if (self.life) |*texture| {
            texture.unload();
            self.life = null;
        }
        for (&self.jetpack_frames) |*texture| {
            if (texture.*) |*loaded| {
                loaded.unload();
                texture.* = null;
            }
        }
        if (self.parcel) |*texture| {
            texture.unload();
            self.parcel = null;
        }
        if (self.ring) |*texture| {
            texture.unload();
            self.ring = null;
        }
        if (self.ring_big) |*texture| {
            texture.unload();
            self.ring_big = null;
        }
        if (self.slow_ring) |*texture| {
            texture.unload();
            self.slow_ring = null;
        }
        if (self.powerup) |*texture| {
            texture.unload();
            self.powerup = null;
        }
        if (self.progress_bar) |*texture| {
            texture.unload();
            self.progress_bar = null;
        }
        if (self.progress_bar_lit) |*texture| {
            texture.unload();
            self.progress_bar_lit = null;
        }
        if (self.progress_cursor) |*texture| {
            texture.unload();
            self.progress_cursor = null;
        }
        if (self.damage_gauge) |*texture| {
            texture.unload();
            self.damage_gauge = null;
        }
        if (self.damage_gauge_full) |*texture| {
            texture.unload();
            self.damage_gauge_full = null;
        }
        if (self.damage_gauge_bright) |*texture| {
            texture.unload();
            self.damage_gauge_bright = null;
        }
        if (self.warning) |*texture| {
            texture.unload();
            self.warning = null;
        }
        if (self.explode_big) |*texture| {
            texture.unload();
            self.explode_big = null;
        }
        if (self.explode_small) |*texture| {
            texture.unload();
            self.explode_small = null;
        }
        if (self.slug_goo) |*texture| {
            texture.unload();
            self.slug_goo = null;
        }
        if (self.smoke) |*texture| {
            texture.unload();
            self.smoke = null;
        }
    }
};

const GameplaySoundFx = struct {
    turbo_fire: [gameplay_turbo_fire_sound_paths.len]?assets.LoadedSound = [_]?assets.LoadedSound{null} ** gameplay_turbo_fire_sound_paths.len,
    laser: [gameplay_laser_sound_paths.len]?assets.LoadedSound = [_]?assets.LoadedSound{null} ** gameplay_laser_sound_paths.len,
    rocket: [gameplay_rocket_sound_paths.len]?assets.LoadedSound = [_]?assets.LoadedSound{null} ** gameplay_rocket_sound_paths.len,
    cheers: ?assets.LoadedSound = null,
    extra_life: ?assets.LoadedSound = null,
    weapon_change: ?assets.LoadedSound = null,
    heart: ?assets.LoadedSound = null,
    jetpack: ?assets.LoadedSound = null,
    jetpack_shutoff: ?assets.LoadedSound = null,
    slow_ring: ?assets.LoadedSound = null,
    invincible: ?assets.LoadedSound = null,
    explode_ring: ?assets.LoadedSound = null,
    enemy_fire: ?assets.LoadedSound = null,
    boing: ?assets.LoadedSound = null,
    completion_init: ?assets.LoadedSound = null,
    row_event_confirm: ?assets.LoadedSound = null,
    place_package: ?assets.LoadedSound = null,
    package_count: ?assets.LoadedSound = null,
    perfect: ?assets.LoadedSound = null,
    powerup_pickup: [gameplay_powerup_pickup_sound_paths.len]?assets.LoadedSound = [_]?assets.LoadedSound{null} ** gameplay_powerup_pickup_sound_paths.len,
    asteroid_impact: [gameplay_asteroid_impact_sound_paths.len]?assets.LoadedSound = [_]?assets.LoadedSound{null} ** gameplay_asteroid_impact_sound_paths.len,
    wall_hit: ?assets.LoadedSound = null,
    postal_warning: ?assets.LoadedSound = null,

    fn unload(self: *GameplaySoundFx) void {
        inline for (comptime std.meta.fieldNames(GameplaySoundFx)) |field_name| {
            const field = &@field(self, field_name);
            switch (@typeInfo(@TypeOf(field.*))) {
                .array => {
                    for (field) |*entry| {
                        if (entry.*) |*sound| {
                            sound.unload();
                            entry.* = null;
                        }
                    }
                },
                else => {
                    if (field.*) |*sound| {
                        sound.unload();
                        field.* = null;
                    }
                },
            }
        }
    }
};

const max_active_gameplay_effects = 64;
const max_gameplay_mount_draw_frames = 6;

const GameplayWeaponModelSet = struct {
    base: ?x2.Uploaded = null,
    draw_frames: [max_gameplay_mount_draw_frames]?x2.Uploaded = [_]?x2.Uploaded{null} ** max_gameplay_mount_draw_frames,
    draw_frame_count: u8 = 0,
    fire: ?x2.Uploaded = null,

    fn unload(self: *GameplayWeaponModelSet) void {
        if (self.base) |*model| {
            model.deinit();
            self.base = null;
        }
        for (&self.draw_frames) |*model| {
            if (model.*) |*loaded| {
                loaded.deinit();
                model.* = null;
            }
        }
        if (self.fire) |*model| {
            model.deinit();
            self.fire = null;
        }
        self.draw_frame_count = 0;
    }

    fn currentModel(self: *const GameplayWeaponModelSet, draw_ticks: u8, fire_ticks: u8, hide_ticks: u8) ?*const x2.Uploaded {
        if (fire_ticks > 0) {
            if (self.fire) |*model| return model;
        }
        if (draw_ticks > 0 and self.draw_frame_count > 0) {
            const capped_ticks = @min(draw_ticks, self.draw_frame_count);
            const frame_index = self.draw_frame_count - capped_ticks;
            if (self.draw_frames[frame_index]) |*model| return model;
        }
        if (hide_ticks > 0 and self.draw_frame_count > 0) {
            const capped_ticks = @min(hide_ticks, self.draw_frame_count);
            const frame_index = capped_ticks - 1;
            if (self.draw_frames[frame_index]) |*model| return model;
        }
        if (self.base) |*model| return model;
        return null;
    }
};

const GameplayInvincibleModelSet = struct {
    frames: [gameplay_invincible_model_paths.len]?x2.Uploaded = [_]?x2.Uploaded{null} ** gameplay_invincible_model_paths.len,

    fn unload(self: *GameplayInvincibleModelSet) void {
        for (&self.frames) |*model| {
            if (model.*) |*loaded| {
                loaded.deinit();
                model.* = null;
            }
        }
    }

    fn currentModel(self: *const GameplayInvincibleModelSet, render_time_seconds: f64) ?*const x2.Uploaded {
        const frame_count = comptime gameplay_invincible_model_paths.len;
        const frame_index: usize = @intFromFloat(@mod(@floor(render_time_seconds * 10.0), @as(f64, @floatFromInt(frame_count))));
        if (self.frames[frame_index]) |*model| return model;
        if (self.frames[0]) |*model| return model;
        return null;
    }
};

const GameplayWeaponVisualState = struct {
    left_draw_ticks: u8 = 0,
    left_hide_ticks: u8 = 0,
    right_draw_ticks: u8 = 0,
    right_hide_ticks: u8 = 0,
    top_draw_ticks: u8 = 0,
    top_hide_ticks: u8 = 0,
    rocket_draw_ticks: u8 = 0,
    rocket_hide_ticks: u8 = 0,
    top_fire_ticks: u8 = 0,

    fn tick(self: *GameplayWeaponVisualState) void {
        if (self.left_draw_ticks > 0) self.left_draw_ticks -= 1;
        if (self.left_hide_ticks > 0) self.left_hide_ticks -= 1;
        if (self.right_draw_ticks > 0) self.right_draw_ticks -= 1;
        if (self.right_hide_ticks > 0) self.right_hide_ticks -= 1;
        if (self.top_draw_ticks > 0) self.top_draw_ticks -= 1;
        if (self.top_hide_ticks > 0) self.top_hide_ticks -= 1;
        if (self.rocket_draw_ticks > 0) self.rocket_draw_ticks -= 1;
        if (self.rocket_hide_ticks > 0) self.rocket_hide_ticks -= 1;
        if (self.top_fire_ticks > 0) self.top_fire_ticks -= 1;
    }

    fn noteWeaponChannelChange(self: *GameplayWeaponVisualState, previous_flags: u32, current_flags: u32) void {
        const previous = gameplay.nativeWeaponChannelStates(previous_flags);
        const current = gameplay.nativeWeaponChannelStates(current_flags);
        self.noteSideChannelChange(previous.left, current.left, true);
        self.noteSideChannelChange(previous.right, current.right, false);
        self.noteCenterChannelChange(previous.center, current.center);
    }

    fn noteSideChannelChange(self: *GameplayWeaponVisualState, previous: u8, current: u8, left_channel: bool) void {
        if (previous == current) return;
        const draw_ticks: *u8 = if (left_channel) &self.left_draw_ticks else &self.right_draw_ticks;
        const hide_ticks: *u8 = if (left_channel) &self.left_hide_ticks else &self.right_hide_ticks;
        if (previous != 0) hide_ticks.* = @intCast(@max(gameplay_laser_left_draw_model_paths.len, gameplay_laser_right_draw_model_paths.len));
        if (current != 0) draw_ticks.* = @intCast(@max(gameplay_laser_left_draw_model_paths.len, gameplay_laser_right_draw_model_paths.len));
    }

    fn noteCenterChannelChange(self: *GameplayWeaponVisualState, previous: u8, current: u8) void {
        if (previous == current) return;
        switch (previous) {
            1 => self.top_hide_ticks = @intCast(gameplay_blaster_top_draw_model_paths.len),
            3 => self.rocket_hide_ticks = @intCast(gameplay_rocket_launcher_draw_model_paths.len),
            else => {},
        }
        switch (current) {
            1 => self.top_draw_ticks = @intCast(gameplay_blaster_top_draw_model_paths.len),
            3 => self.rocket_draw_ticks = @intCast(gameplay_rocket_launcher_draw_model_paths.len),
            else => {},
        }
    }

    fn noteFire(self: *GameplayWeaponVisualState, movement_flags: u32) void {
        const channel_states = gameplay.nativeWeaponChannelStates(movement_flags);
        if (channel_states.left != 0 and self.left_draw_ticks == 0) self.left_draw_ticks = 1;
        if (channel_states.right != 0 and self.right_draw_ticks == 0) self.right_draw_ticks = 1;
        switch (channel_states.center) {
            1 => self.top_fire_ticks = 3,
            3 => {
                if (self.rocket_draw_ticks == 0) self.rocket_draw_ticks = 1;
            },
            else => {},
        }
    }
};

const GameplayEffectKind = enum {
    explode_big,
    explode_small,
    slug_goo,
    smoke,
};

const GameplayVoiceManager = struct {
    active: bool = false,
    progress: f32 = 0.0,
    delta: f32 = 1.0 / 60.0,

    fn tick(self: *GameplayVoiceManager) void {
        if (!self.active or self.progress <= 0.0) return;
        self.progress += self.delta;
        if (self.progress > 1.0) {
            self.active = false;
            self.progress = 0.0;
        }
    }

    fn arm(self: *GameplayVoiceManager) void {
        self.active = true;
        self.progress = self.delta;
    }

    fn clear(self: *GameplayVoiceManager) void {
        self.* = .{};
    }
};

const NativeGameplayVoiceSet = enum(u8) {
    damage = 0,
    dying = 1,
    enemies = 2,
    fall = 3,
    misc = 4,
    powerup = 5,
    slow = 6,
    start = 7,
    victory = 8,
    ouch = 9,
    package = 10,
    slugged = 11,
    worm_tunnel = 12,
    tutorial = 13,
    postal = 14,
    supertramp = 15,
};

const NativeGameplayVoiceMode = enum(u2) {
    wait_for_idle = 0,
    wait_for_frequency = 1,
    interrupt_current = 2,
};

const NativeGameplayVoiceSetState = struct {
    next_index: usize = 0,
    cooldown_progress: f32 = 0.0,
    cooldown_step: f32 = native_gameplay_voice_set_cooldown_step,

    fn tick(self: *NativeGameplayVoiceSetState) void {
        if (self.cooldown_progress <= 0.0) return;
        self.cooldown_progress += self.cooldown_step;
        if (self.cooldown_progress > 1.0) {
            self.cooldown_progress = 0.0;
        }
    }
};

const NativeGameplayVoiceManager = struct {
    global_progress: f32 = 0.0,
    global_step: f32 = native_gameplay_voice_manager_global_step,
    global_frequency_seconds: f32 = native_gameplay_voice_manager_frequency_seconds,
    sets: [16]NativeGameplayVoiceSetState = [_]NativeGameplayVoiceSetState{.{}} ** 16,

    fn tick(self: *NativeGameplayVoiceManager) void {
        for (&self.sets) |*set_state| {
            set_state.tick();
        }
        self.global_progress += self.global_step;
    }

    fn clear(self: *NativeGameplayVoiceManager) void {
        self.* = .{};
    }

    fn requestPlay(
        self: *NativeGameplayVoiceManager,
        set_id: NativeGameplayVoiceSet,
        mode: NativeGameplayVoiceMode,
        voice_busy: bool,
        sample_count: usize,
    ) ?usize {
        if (sample_count == 0) return null;
        switch (mode) {
            .wait_for_idle => {
                if (voice_busy) return null;
            },
            .wait_for_frequency => {
                if (voice_busy) return null;
                if (self.global_progress < self.global_frequency_seconds) return null;
            },
            .interrupt_current => {},
        }

        const set_state = &self.sets[@intFromEnum(set_id)];
        if (set_state.cooldown_progress != 0.0) return null;

        const sample_index = set_state.next_index % sample_count;
        set_state.next_index = (sample_index + 1) % sample_count;
        set_state.cooldown_progress = set_state.cooldown_step;
        if (mode != .wait_for_idle) {
            self.global_progress = 0.0;
        }
        return sample_index;
    }

    fn requestPayloadPlay(
        self: *NativeGameplayVoiceManager,
        set_id: NativeGameplayVoiceSet,
        mode: NativeGameplayVoiceMode,
        voice_busy: bool,
        payload_index: usize,
    ) ?usize {
        switch (mode) {
            .wait_for_idle => {
                if (voice_busy) return null;
            },
            .wait_for_frequency => {
                if (voice_busy) return null;
                if (self.global_progress < self.global_frequency_seconds) return null;
            },
            .interrupt_current => {},
        }

        const set_state = &self.sets[@intFromEnum(set_id)];
        if (set_state.cooldown_progress != 0.0) return null;

        set_state.cooldown_progress = set_state.cooldown_step;
        if (mode != .wait_for_idle) {
            self.global_progress = 0.0;
        }
        return payload_index;
    }
};

const native_global_audio_bank_paths = [_][]const u8{
    "SFX2/CHEERS.OGG",
    "SFX2/PW1.OGG",
    "SFX2/PW2.OGG",
    "SFX2/PW3.OGG",
    "SFX2/PW4.OGG",
    "SFX2/PW5.OGG",
    "SFX2/PW6.OGG",
    "SFX2/PW7.OGG",
    frontend_select_sound_path,
    frontend_highlight_sound_path,
    "VOICE/OW1.OGG",
    "VOICE/OW2.OGG",
    "VOICE/OW3.OGG",
    "VOICE/OW4.OGG",
    "SFX2/HEART.OGG",
    "SFX2/ENEMYFIRE.OGG",
    "SFX2/JETPACK.OGG",
    "SFX2/TURBOFIRE1.OGG",
    "SFX2/TURBOFIRE2.OGG",
    "SFX2/LASER1.OGG",
    "SFX2/LASER2.OGG",
    "SFX2/LASER3.OGG",
    "SFX2/ROCKET1.OGG",
    "SFX2/ROCKET2.OGG",
    "SFX2/ROCKET3.OGG",
    "SFX2/SERVO1.OGG",
    "SFX2/SERVO2.OGG",
    "SFX2/PLACEPACKAGE.OGG",
    "VOICE/SLUG-DEATH1.OGG",
    "VOICE/SLUG-DEATH2.OGG",
    "VOICE/SLUG-DESTROY.OGG",
    "VOICE/SLUG-GOTHIM.OGG",
    "VOICE/SLUG-HESTOOFAST.OGG",
    "VOICE/SLUG-SNAILALERT.OGG",
    "VOICE/SLUG-VICTORY.OGG",
    "VOICE/SLUG-VICTORY2.OGG",
    "VOICE/SLUG-HIT1.OGG",
    "VOICE/SLUG-HIT2.OGG",
    "VOICE/SLUG-HIT3.OGG",
    "SFX2/ASTEROIDIMPACT1.OGG",
    "SFX2/ASTEROIDIMPACT2.OGG",
    "SFX2/BOING.OGG",
    "SFX2/EXPLODERING.OGG",
    "SFX2/SLOWRING.OGG",
    "SFX2/EXTRALIFE.OGG",
    "SFX2/PACKAGECOUNT.OGG",
    "SFX2/SKIDSTOP.OGG",
    "SFX2/WALLHIT.OGG",
    "SFX2/INVINCIBLE.OGG",
    "SFX2/PERFECT.OGG",
    "SFX2/POSTALLOOP.OGG",
};

const native_global_voice_set_paths = .{
    gameplay_native_voice_damage_paths[0..],
    gameplay_native_voice_dying_paths[0..],
    gameplay_native_voice_enemies_paths[0..],
    gameplay_native_voice_fall_paths[0..],
    gameplay_native_voice_misc_paths[0..],
    gameplay_native_voice_powerup_paths[0..],
    gameplay_native_voice_slow_paths[0..],
    gameplay_native_voice_start_paths[0..],
    gameplay_native_voice_victory_paths[0..],
    gameplay_native_voice_ouch_paths[0..],
    gameplay_native_voice_package_paths[0..],
    gameplay_native_voice_slugged_paths[0..],
    gameplay_native_voice_worm_tunnel_paths[0..],
    gameplay_native_voice_tutorial_paths[0..],
    gameplay_native_voice_postal_paths[0..],
    gameplay_native_voice_supertramp_paths[0..],
};

fn nativeGlobalAudioSamplePath(sample_index: usize) ?[]const u8 {
    if (sample_index < native_global_audio_bank_paths.len) {
        return native_global_audio_bank_paths[sample_index];
    }

    var remaining = sample_index - native_global_audio_bank_paths.len;
    inline for (native_global_voice_set_paths) |paths| {
        if (remaining < paths.len) return paths[remaining];
        remaining -= paths.len;
    }
    return null;
}

fn nativeGlobalAudioSampleIndexForPath(sample_path: []const u8) ?usize {
    for (native_global_audio_bank_paths, 0..) |path, index| {
        if (std.ascii.eqlIgnoreCase(path, sample_path)) return index;
    }

    var base_index = native_global_audio_bank_paths.len;
    inline for (native_global_voice_set_paths) |paths| {
        for (paths, 0..) |path, index| {
            if (std.ascii.eqlIgnoreCase(path, sample_path)) return base_index + index;
        }
        base_index += paths.len;
    }
    return null;
}

fn nativeGameplayVoicePaths(set_id: NativeGameplayVoiceSet) []const []const u8 {
    return switch (set_id) {
        .damage => gameplay_native_voice_damage_paths[0..],
        .dying => gameplay_native_voice_dying_paths[0..],
        .enemies => gameplay_native_voice_enemies_paths[0..],
        .fall => gameplay_native_voice_fall_paths[0..],
        .misc => gameplay_native_voice_misc_paths[0..],
        .package => gameplay_native_voice_package_paths[0..],
        .postal => gameplay_native_voice_postal_paths[0..],
        .powerup => gameplay_native_voice_powerup_paths[0..],
        .slow => gameplay_native_voice_slow_paths[0..],
        .slugged => gameplay_native_voice_slugged_paths[0..],
        .start => gameplay_native_voice_start_paths[0..],
        .supertramp => gameplay_native_voice_supertramp_paths[0..],
        .tutorial => gameplay_native_voice_tutorial_paths[0..],
        .ouch => gameplay_native_voice_ouch_paths[0..],
        .victory => gameplay_native_voice_victory_paths[0..],
        .worm_tunnel => gameplay_native_voice_worm_tunnel_paths[0..],
    };
}

test "native gameplay voice manager enforces native mode gates" {
    var manager: NativeGameplayVoiceManager = .{};

    try std.testing.expectEqual(@as(?usize, null), manager.requestPlay(.victory, .wait_for_frequency, false, 3));
    try std.testing.expectEqual(@as(?usize, 0), manager.requestPlay(.victory, .wait_for_idle, false, 3));
    try std.testing.expectEqual(@as(?usize, null), manager.requestPlay(.victory, .wait_for_idle, false, 3));

    var tick_index: usize = 0;
    while (tick_index < 240) : (tick_index += 1) {
        manager.tick();
    }
    try std.testing.expectEqual(@as(?usize, null), manager.requestPlay(.victory, .wait_for_frequency, false, 3));

    manager.global_progress = native_gameplay_voice_manager_frequency_seconds;
    try std.testing.expectEqual(@as(?usize, 1), manager.requestPlay(.victory, .wait_for_frequency, false, 3));

    manager.clear();
    try std.testing.expectEqual(@as(?usize, null), manager.requestPlay(.fall, .wait_for_idle, true, 2));
    try std.testing.expectEqual(@as(?usize, 0), manager.requestPlay(.fall, .interrupt_current, true, 2));
}

test "native gameplay voice manager payload play preserves set rotation" {
    var manager: NativeGameplayVoiceManager = .{};
    manager.global_progress = native_gameplay_voice_manager_frequency_seconds;

    try std.testing.expectEqual(@as(?usize, 133), manager.requestPayloadPlay(.tutorial, .interrupt_current, false, 133));
    try std.testing.expectEqual(@as(?usize, null), manager.requestPlay(.tutorial, .interrupt_current, false, 18));

    var tick_index: usize = 0;
    while (tick_index < 240) : (tick_index += 1) {
        manager.tick();
    }

    try std.testing.expectEqual(@as(?usize, 0), manager.requestPlay(.tutorial, .interrupt_current, false, 18));
}

test "native global audio sample ids resolve from shipped paths" {
    try std.testing.expectEqual(@as(?usize, 16), nativeGlobalAudioSampleIndexForPath("SFX2/JETPACK.OGG"));
    try std.testing.expectEqual(@as(?usize, 25), nativeGlobalAudioSampleIndexForPath("sfx2/servo1.ogg"));
    try std.testing.expectEqual(@as(?usize, 26), nativeGlobalAudioSampleIndexForPath("SFX2/SERVO2.OGG"));
    try std.testing.expectEqual(@as(?usize, 46), nativeGlobalAudioSampleIndexForPath("SFX2/SKIDSTOP.OGG"));
    try std.testing.expectEqual(@as(?usize, 133), nativeGlobalAudioSampleIndexForPath("VOICE/TUT1.OGG"));
    try std.testing.expectEqual(@as(?usize, 150), nativeGlobalAudioSampleIndexForPath("Voice/tut18.ogg"));
    try std.testing.expectEqualStrings("VOICE/TUT1.OGG", nativeGlobalAudioSamplePath(133).?);
    try std.testing.expectEqualStrings("SFX2/SERVO2.OGG", nativeGlobalAudioSamplePath(26).?);
    try std.testing.expectEqual(@as(?[]const u8, null), nativeGlobalAudioSamplePath(999));
    try std.testing.expectEqual(@as(?usize, null), nativeGlobalAudioSampleIndexForPath("VOICE/DOES-NOT-EXIST.OGG"));
}

const max_announced_slug_voice_cells: usize = 64;

const GameplayEffect = struct {
    active: bool = false,
    kind: GameplayEffectKind = .explode_small,
    position: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    velocity: rl.Vector3 = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    width: f32 = 0.8,
    height: f32 = 0.8,
    tint: rl.Color = .white,
    ticks_remaining: u16 = 0,
};

const RouteMapArt = struct {
    logo: ?assets.LoadedTexture = null,
    border: ?assets.LoadedTexture = null,
    galaxy_select: ?assets.LoadedTexture = null,
    level_select: ?assets.LoadedTexture = null,
    level_star: ?assets.LoadedTexture = null,
    line: ?assets.LoadedTexture = null,
    line_star: ?assets.LoadedTexture = null,
    galaxies: [galaxy.map_galaxy_count]?assets.LoadedTexture = [_]?assets.LoadedTexture{null} ** galaxy.map_galaxy_count,

    fn unload(self: *RouteMapArt) void {
        if (self.logo) |*texture| {
            texture.unload();
            self.logo = null;
        }
        if (self.border) |*texture| {
            texture.unload();
            self.border = null;
        }
        if (self.galaxy_select) |*texture| {
            texture.unload();
            self.galaxy_select = null;
        }
        if (self.level_select) |*texture| {
            texture.unload();
            self.level_select = null;
        }
        if (self.level_star) |*texture| {
            texture.unload();
            self.level_star = null;
        }
        if (self.line) |*texture| {
            texture.unload();
            self.line = null;
        }
        if (self.line_star) |*texture| {
            texture.unload();
            self.line_star = null;
        }
        for (&self.galaxies) |*texture| {
            if (texture.*) |*loaded| {
                loaded.unload();
                texture.* = null;
            }
        }
    }
};

fn loadFrontendWidgetArt(allocator: std.mem.Allocator, catalog: *const assets.Catalog) !FrontendWidgetArt {
    var art = FrontendWidgetArt{};
    errdefer art.unload();

    art.border = try catalog.loadTextureByPath(allocator, widget_border_texture_path);
    art.parcel_icon = try catalog.loadTextureByPath(allocator, completion_parcel_icon_texture_path);

    return art;
}

fn loadFrontendSoundFx(allocator: std.mem.Allocator, catalog: *const assets.Catalog, audio_ready: bool) !FrontendSoundFx {
    if (!audio_ready) return .{};

    var sound_fx = FrontendSoundFx{};
    errdefer sound_fx.unload();

    sound_fx.highlight = try catalog.loadSoundByPath(allocator, frontend_highlight_sound_path);
    sound_fx.select = try catalog.loadSoundByPath(allocator, frontend_select_sound_path);

    return sound_fx;
}

fn loadSliderArt(allocator: std.mem.Allocator, catalog: *const assets.Catalog) !SliderArt {
    var art = SliderArt{};
    errdefer art.unload();

    art.less = try catalog.loadTextureByPath(allocator, slider_less_texture_path);
    art.less_hover = try catalog.loadTextureByPath(allocator, slider_less_hover_texture_path);
    art.more = try catalog.loadTextureByPath(allocator, slider_more_texture_path);
    art.more_hover = try catalog.loadTextureByPath(allocator, slider_more_hover_texture_path);
    art.bar = try catalog.loadTextureByPath(allocator, slider_bar_texture_path);
    art.bar_full = try catalog.loadTextureByPath(allocator, slider_bar_full_texture_path);

    return art;
}

fn loadRouteMapArt(allocator: std.mem.Allocator, catalog: *const assets.Catalog) !RouteMapArt {
    var art = RouteMapArt{};
    errdefer art.unload();

    art.logo = try catalog.loadTextureByPath(allocator, route_map_logo_texture_path);
    art.border = try catalog.loadTextureByPath(allocator, route_map_border_texture_path);
    art.galaxy_select = try catalog.loadTextureByPath(allocator, route_map_galaxy_select_texture_path);
    art.level_select = try catalog.loadTextureByPath(allocator, route_map_level_select_texture_path);
    art.level_star = try catalog.loadTextureByPath(allocator, route_map_level_star_texture_path);
    art.line = try catalog.loadTextureByPath(allocator, route_map_line_texture_path);
    art.line_star = try catalog.loadTextureByPath(allocator, route_map_line_star_texture_path);
    for (route_map_galaxy_texture_paths, 0..) |path, index| {
        art.galaxies[index] = try catalog.loadTextureByPath(allocator, path);
    }

    return art;
}

fn loadGameplaySpriteArt(allocator: std.mem.Allocator, catalog: *const assets.Catalog) !GameplaySpriteArt {
    var art = GameplaySpriteArt{};
    errdefer art.unload();

    for (gameplay_slug_sprite_paths, 0..) |path, index| {
        art.slug_frames[index] = try catalog.loadTextureByPath(allocator, path);
    }
    for (gameplay_garbage_sprite_paths, 0..) |path, index| {
        art.garbage_variants[index] = try catalog.loadTextureByPath(allocator, path);
    }
    art.health = try catalog.loadTextureByPath(allocator, gameplay_health_sprite_path);
    art.life = try catalog.loadTextureByPath(allocator, gameplay_life_sprite_path);
    for (gameplay_jetpack_sprite_paths, 0..) |path, index| {
        art.jetpack_frames[index] = try catalog.loadTextureByPath(allocator, path);
    }
    art.parcel = try catalog.loadTextureByPath(allocator, gameplay_parcel_sprite_path);
    art.ring = try catalog.loadTextureByPath(allocator, gameplay_ring_sprite_path);
    art.ring_big = try catalog.loadTextureByPath(allocator, gameplay_ring_big_sprite_path);
    art.slow_ring = try catalog.loadTextureByPath(allocator, gameplay_slow_ring_sprite_path);
    art.powerup = try catalog.loadTextureByPath(allocator, gameplay_powerup_sprite_path);
    art.progress_bar = try catalog.loadTextureByPath(allocator, gameplay_progress_bar_sprite_path);
    art.progress_bar_lit = try catalog.loadTextureByPath(allocator, gameplay_progress_bar_lit_sprite_path);
    art.progress_cursor = try catalog.loadTextureByPath(allocator, gameplay_progress_cursor_sprite_path);
    art.damage_gauge = try catalog.loadTextureByPath(allocator, gameplay_damage_gauge_sprite_path);
    art.damage_gauge_full = try catalog.loadTextureByPath(allocator, gameplay_damage_gauge_full_sprite_path);
    art.damage_gauge_bright = try catalog.loadTextureByPath(allocator, gameplay_damage_gauge_bright_sprite_path);
    art.warning = try catalog.loadTextureByPath(allocator, gameplay_warning_sprite_path);
    art.explode_big = try catalog.loadTextureByPath(allocator, gameplay_explode_big_sprite_path);
    art.explode_small = try catalog.loadTextureByPath(allocator, gameplay_explode_small_sprite_path);
    art.slug_goo = try catalog.loadTextureByPath(allocator, gameplay_slug_goo_sprite_path);
    art.smoke = try catalog.loadTextureByPath(allocator, gameplay_smoke_sprite_path);

    return art;
}

fn loadGameplaySoundFx(allocator: std.mem.Allocator, catalog: *const assets.Catalog, audio_ready: bool) !GameplaySoundFx {
    if (!audio_ready) return .{};

    var sound_fx = GameplaySoundFx{};
    errdefer sound_fx.unload();

    for (gameplay_turbo_fire_sound_paths, 0..) |path, index| {
        sound_fx.turbo_fire[index] = try catalog.loadSoundByPath(allocator, path);
    }
    for (gameplay_laser_sound_paths, 0..) |path, index| {
        sound_fx.laser[index] = try catalog.loadSoundByPath(allocator, path);
    }
    for (gameplay_rocket_sound_paths, 0..) |path, index| {
        sound_fx.rocket[index] = try catalog.loadSoundByPath(allocator, path);
    }
    sound_fx.cheers = try catalog.loadSoundByPath(allocator, gameplay_cheers_sound_path);
    sound_fx.extra_life = try catalog.loadSoundByPath(allocator, gameplay_extra_life_sound_path);
    sound_fx.weapon_change = try catalog.loadSoundByPath(allocator, gameplay_weapon_change_sound_path);
    sound_fx.heart = try catalog.loadSoundByPath(allocator, gameplay_heart_sound_path);
    sound_fx.jetpack = try catalog.loadSoundByPath(allocator, gameplay_jetpack_sound_path);
    sound_fx.jetpack_shutoff = try catalog.loadSoundByPath(allocator, gameplay_jetpack_shutoff_sound_path);
    sound_fx.slow_ring = try catalog.loadSoundByPath(allocator, gameplay_slow_ring_sound_path);
    sound_fx.invincible = try catalog.loadSoundByPath(allocator, gameplay_invincible_sound_path);
    sound_fx.explode_ring = try catalog.loadSoundByPath(allocator, gameplay_explode_ring_sound_path);
    sound_fx.enemy_fire = try catalog.loadSoundByPath(allocator, gameplay_enemy_fire_sound_path);
    sound_fx.boing = try catalog.loadSoundByPath(allocator, gameplay_boing_sound_path);
    sound_fx.completion_init = try catalog.loadSoundByPath(allocator, gameplay_completion_init_sound_path);
    sound_fx.row_event_confirm = try catalog.loadSoundByPath(allocator, gameplay_row_event_confirm_sound_path);
    sound_fx.place_package = try catalog.loadSoundByPath(allocator, gameplay_place_package_sound_path);
    sound_fx.package_count = try catalog.loadSoundByPath(allocator, gameplay_package_count_sound_path);
    sound_fx.perfect = try catalog.loadSoundByPath(allocator, gameplay_perfect_sound_path);
    for (gameplay_powerup_pickup_sound_paths, 0..) |path, index| {
        sound_fx.powerup_pickup[index] = try catalog.loadSoundByPath(allocator, path);
    }
    for (gameplay_asteroid_impact_sound_paths, 0..) |path, index| {
        sound_fx.asteroid_impact[index] = try catalog.loadSoundByPath(allocator, path);
    }
    sound_fx.wall_hit = try catalog.loadSoundByPath(allocator, gameplay_wall_hit_sound_path);
    sound_fx.postal_warning = try catalog.loadSoundByPath(allocator, gameplay_postal_warning_sound_path);

    return sound_fx;
}

const ResultReturnTarget = enum {
    main_menu,
    new_game_menu,
    postal_route_map,
    time_trial_route_map,
    high_scores_menu,
    replay_current_level,
    thanks_screen,
};

const OuterBridgeOpcode = enum(u8) {
    destroy_return = 26,
    rebuild_return = 27,
    rebuild_clear_replay_return = 28,
    init_thanks_screen = 29,
    update_thanks_screen = 30,
};

const RouteMapBridgeTarget = struct {
    mode: FrontendLevelMode,
    screen_mode: RouteMapScreenMode,
    start_route_override: ?usize = null,
};

const ReplayLevelBridgeTarget = struct {
    mode: FrontendLevelMode,
    level_index: usize,
    selected_level_record_override: ?SelectedLevelRecordOverride = null,
    selected_level_record_source: ?SelectedLevelRecordSource = null,
};

const FrontendBridgeTarget = union(enum) {
    main_menu,
    new_game_menu: NewGameMenuItem,
    route_map: RouteMapBridgeTarget,
    high_scores_menu: high_score.Mode,
    replay_current_level: ReplayLevelBridgeTarget,
    thanks_screen,
};

const OuterBridgeRequest = struct {
    opcode: OuterBridgeOpcode,
    target: FrontendBridgeTarget,
};

const RunOutcome = enum {
    completed,
    failed,
};

const NativeGameplaySoundCues = struct {
    completion_arm_cheers: bool = false,
    extra_life: bool = false,
    trampoline_bounce: bool = false,
    wall_barrier_hit: bool = false,
    parcel_pickup: bool = false,
    parcel_delivery: bool = false,
    parcel_bonus: bool = false,
    row_event_confirm: bool = false,
};

const NativeJetpackSoundCues = struct {
    activate: bool = false,
    deactivate: bool = false,
};

const NativeGameplayVoiceCues = struct {
    start: bool = false,
    package_pickup: bool = false,
    weapon_upgrade: bool = false,
    damage_entry: bool = false,
    damage_escalation: bool = false,
};

const NativeMovementStateSoundFamily = enum {
    turbo,
    laser,
    rocket,
};

fn runnerInCompletionHandoff(runner: gameplay.Runner) bool {
    return switch (runner.phase) {
        .completion_handoff => true,
        else => false,
    };
}

fn nativeGameplaySoundCues(previous: gameplay.Runner, current: gameplay.Runner) NativeGameplaySoundCues {
    return .{
        .completion_arm_cheers = !runnerInCompletionHandoff(previous) and runnerInCompletionHandoff(current),
        .extra_life = current.score.total > previous.score.total and current.visible_life_stock > previous.visible_life_stock,
        .trampoline_bounce = current.counters.trampoline_rows > previous.counters.trampoline_rows,
        .wall_barrier_hit = previous.current_runtime_tile_hint != native_runtime_tile_wall and
            current.current_runtime_tile_hint == native_runtime_tile_wall,
        .parcel_pickup = current.counters.parcels > previous.counters.parcels,
        .parcel_delivery = current.registeredParcelCount() > previous.registeredParcelCount(),
        .parcel_bonus = current.row_event_display.bonus_enabled and
            current.row_event_display.parcel_target_count != 0 and
            previous.registeredParcelCount() < current.row_event_display.parcel_target_count and
            current.registeredParcelCount() == current.row_event_display.parcel_target_count,
        .row_event_confirm = previous.row_event_display.gate_18 == 0 and current.row_event_display.gate_18 != 0,
    };
}

fn nativeRingEffectKindTriggered(previous: gameplay.Runner, current: gameplay.Runner) ?u8 {
    if (current.native_ring_effect_token == previous.native_ring_effect_token) return null;
    return current.last_native_ring_effect_kind;
}

fn nativeRingPickupSoundIndex(previous: gameplay.Runner, current: gameplay.Runner) ?usize {
    if (nativeRingEffectKindTriggered(previous, current)) |effect_kind| {
        return switch (effect_kind) {
            1 => 0,
            4, 5, 8 => @min(
                gameplay_powerup_pickup_sound_paths.len - 1,
                @as(usize, @intCast(@max(current.movement_flag_selector, 1) - 1)),
            ),
            else => null,
        };
    }

    if (current.counters.ring_powerup <= previous.counters.ring_powerup) return null;
    return @min(
        gameplay_powerup_pickup_sound_paths.len - 1,
        @as(usize, current.counters.ring_powerup - 1),
    );
}

fn nativeSlowRingSoundTriggered(previous: gameplay.Runner, current: gameplay.Runner) bool {
    if (nativeRingEffectKindTriggered(previous, current)) |effect_kind| {
        return effect_kind == 3 or effect_kind == 7;
    }
    return current.slow_ticks > previous.slow_ticks;
}

fn nativeExplodeRingSoundTriggered(previous: gameplay.Runner, current: gameplay.Runner) bool {
    if (nativeRingEffectKindTriggered(previous, current)) |effect_kind| {
        return effect_kind == 2 or effect_kind == 6;
    }
    return current.counters.ring_explode > previous.counters.ring_explode;
}

fn nativeWeaponPresentationChanged(previous: gameplay.Runner, current: gameplay.Runner) bool {
    return current.movement_flags != previous.movement_flags;
}

fn nativeMovementStateSoundFamily(current: gameplay.Runner) NativeMovementStateSoundFamily {
    if ((current.movement_flags & 0x7) != 0) return .turbo;
    if ((current.movement_flags & 0x18) != 0) return .laser;
    if ((current.movement_flags & 0x60) != 0) return .rocket;
    return .turbo;
}

fn nativeMovementStateAttachmentExitGain(camera_position: rl.Vector3, player_position: rl.Vector3, attachment_exit_pending: bool) ?f32 {
    if (!attachment_exit_pending) return null;
    const delta = rl.Vector3{
        .x = camera_position.x - player_position.x,
        .y = camera_position.y - player_position.y,
        .z = camera_position.z - player_position.z,
    };
    return std.math.clamp(1.0 - (vectorLength(delta) * (1.0 / 60.0)), 0.0, 1.0);
}

fn nativeMovementStateVariantIndexForSample(sample: u32, comptime count: usize) usize {
    return @min(count - 1, @as(usize, @intCast((@as(u64, sample) * count) / 0x8000)));
}

fn nativeJetpackSoundCues(previous: gameplay.Runner, current: gameplay.Runner) NativeJetpackSoundCues {
    return .{
        .activate = !previous.jetpack.active and current.jetpack.active,
        .deactivate = (previous.jetpack.active and current.jetpack.active and
            previous.jetpack.progress <= native_jetpack_visual_shutoff_threshold and
            current.jetpack.progress > native_jetpack_visual_shutoff_threshold) or
            (previous.jetpack.active and !current.jetpack.active and
                previous.jetpack.progress <= native_jetpack_visual_shutoff_threshold),
    };
}

fn nativeGameplaySlowVoiceBandActive(previous: gameplay.Runner, current: gameplay.Runner) bool {
    if (current.phase != .active) return false;
    if (current.movement_mode != .track) return false;
    if (current.attachment_exit_pending) return false;

    const configured_step = current.movement_rate_scalar;
    if (configured_step <= 0.0001) return false;

    const actual_forward_step = @max(0.0, current.row_position - previous.row_position);
    const lower_bound = configured_step * 0.17;
    const upper_bound = lower_bound + ((configured_step * 0.5) - lower_bound) * 0.1;
    return actual_forward_step > lower_bound and actual_forward_step < upper_bound;
}

test "native gameplay sound cues fire for completion-arm and score-bucket life gain" {
    var previous = gameplay.Runner{};
    var current = previous;

    try std.testing.expectEqual(NativeGameplaySoundCues{}, nativeGameplaySoundCues(previous, current));

    current.phase = .completion_handoff;
    try std.testing.expect(nativeGameplaySoundCues(previous, current).completion_arm_cheers);

    previous = current;
    try std.testing.expect(!nativeGameplaySoundCues(previous, current).completion_arm_cheers);

    previous = gameplay.Runner{};
    current = previous;
    current.score.total = 50_000;
    current.visible_life_stock = previous.visible_life_stock + 1;
    try std.testing.expect(nativeGameplaySoundCues(previous, current).extra_life);

    current.score.total = previous.score.total;
    try std.testing.expect(!nativeGameplaySoundCues(previous, current).extra_life);

    previous = gameplay.Runner{};
    current = previous;
    current.counters.trampoline_rows = 1;
    try std.testing.expect(nativeGameplaySoundCues(previous, current).trampoline_bounce);

    previous = gameplay.Runner{};
    current = previous;
    current.current_runtime_tile_hint = native_runtime_tile_wall;
    try std.testing.expect(nativeGameplaySoundCues(previous, current).wall_barrier_hit);

    previous = gameplay.Runner{};
    current = previous;
    current.counters.parcels = 1;
    try std.testing.expect(nativeGameplaySoundCues(previous, current).parcel_pickup);

    previous = gameplay.Runner{};
    current = previous;
    current.row_event_display.delivered_parcel_count = 1;
    try std.testing.expect(nativeGameplaySoundCues(previous, current).parcel_delivery);

    previous = gameplay.Runner{};
    current = previous;
    current.row_event_display.parcel_target_count = 1;
    current.row_event_display.bonus_enabled = true;
    current.row_event_display.delivered_parcel_count = 1;
    try std.testing.expect(nativeGameplaySoundCues(previous, current).parcel_bonus);

    current.row_event_display.bonus_enabled = false;
    try std.testing.expect(!nativeGameplaySoundCues(previous, current).parcel_bonus);

    previous = gameplay.Runner{};
    current = previous;
    current.row_event_display.gate_18 = 1;
    try std.testing.expect(nativeGameplaySoundCues(previous, current).row_event_confirm);

    previous = gameplay.Runner{};
    current = previous;
    try std.testing.expectEqual(@as(?usize, null), nativeRingPickupSoundIndex(previous, current));

    current.last_native_ring_effect_kind = 1;
    current.native_ring_effect_token = 1;
    try std.testing.expectEqual(@as(?usize, 0), nativeRingPickupSoundIndex(previous, current));
    try std.testing.expect(!nativeSlowRingSoundTriggered(previous, current));
    try std.testing.expect(!nativeExplodeRingSoundTriggered(previous, current));

    previous = current;
    current.last_native_ring_effect_kind = 8;
    current.native_ring_effect_token +%= 1;
    current.movement_flag_selector = 8;
    try std.testing.expectEqual(
        @as(?usize, gameplay_powerup_pickup_sound_paths.len - 1),
        nativeRingPickupSoundIndex(previous, current),
    );
    try std.testing.expect(!nativeSlowRingSoundTriggered(previous, current));
    try std.testing.expect(!nativeExplodeRingSoundTriggered(previous, current));

    previous = gameplay.Runner{};
    current = previous;
    current.last_native_ring_effect_kind = 3;
    current.native_ring_effect_token = 1;
    try std.testing.expectEqual(@as(?usize, null), nativeRingPickupSoundIndex(previous, current));
    try std.testing.expect(nativeSlowRingSoundTriggered(previous, current));
    try std.testing.expect(!nativeExplodeRingSoundTriggered(previous, current));

    previous = gameplay.Runner{};
    current = previous;
    current.last_native_ring_effect_kind = 2;
    current.native_ring_effect_token = 1;
    try std.testing.expect(!nativeSlowRingSoundTriggered(previous, current));
    try std.testing.expect(nativeExplodeRingSoundTriggered(previous, current));

    try std.testing.expectEqual(
        @as(?f32, null),
        nativeMovementStateAttachmentExitGain(
            .{ .x = 0.0, .y = 0.0, .z = 0.0 },
            .{ .x = 0.0, .y = 0.0, .z = 30.0 },
            false,
        ),
    );
    try std.testing.expectApproxEqAbs(
        @as(f32, 0.5),
        nativeMovementStateAttachmentExitGain(
            .{ .x = 0.0, .y = 0.0, .z = 0.0 },
            .{ .x = 0.0, .y = 0.0, .z = 30.0 },
            true,
        ).?,
        0.0001,
    );
    try std.testing.expectApproxEqAbs(
        @as(f32, 0.0),
        nativeMovementStateAttachmentExitGain(
            .{ .x = 0.0, .y = 0.0, .z = 0.0 },
            .{ .x = 0.0, .y = 0.0, .z = 120.0 },
            true,
        ).?,
        0.0001,
    );
    try std.testing.expectEqual(@as(usize, 0), nativeMovementStateVariantIndexForSample(0, 2));
    try std.testing.expectEqual(@as(usize, 0), nativeMovementStateVariantIndexForSample(16383, 2));
    try std.testing.expectEqual(@as(usize, 1), nativeMovementStateVariantIndexForSample(16384, 2));
    try std.testing.expectEqual(@as(usize, 2), nativeMovementStateVariantIndexForSample(32767, 3));
    previous = gameplay.Runner{};
    current = previous;
    current.movement_flags = 8;
    try std.testing.expectEqualDeep(
        gameplay.WeaponChannelStates{ .right = 2 },
        gameplay.nativeWeaponChannelStates(current.movement_flags),
    );
    try std.testing.expect(nativeWeaponPresentationChanged(previous, current));

    previous = gameplay.Runner{};
    current = previous;
    current.movement_flags = 2;
    try std.testing.expectEqualDeep(
        gameplay.WeaponChannelStates{ .left = 1, .right = 1 },
        gameplay.nativeWeaponChannelStates(current.movement_flags),
    );
    try std.testing.expect(nativeWeaponPresentationChanged(previous, current));

    previous = gameplay.Runner{};
    current = previous;
    try std.testing.expect(!nativeWeaponPresentationChanged(previous, current));
    try std.testing.expectEqual(NativeMovementStateSoundFamily.turbo, nativeMovementStateSoundFamily(current));

    current.weapon_level = 2;
    current.movement_flags = 144;
    try std.testing.expectEqual(NativeMovementStateSoundFamily.laser, nativeMovementStateSoundFamily(current));

    current.movement_flags = 192;
    try std.testing.expectEqual(NativeMovementStateSoundFamily.rocket, nativeMovementStateSoundFamily(current));

    previous = gameplay.Runner{};
    current = previous;
    try std.testing.expectEqual(NativeJetpackSoundCues{}, nativeJetpackSoundCues(previous, current));

    current.jetpack.active = true;
    try std.testing.expect(nativeJetpackSoundCues(previous, current).activate);
    try std.testing.expect(!nativeJetpackSoundCues(previous, current).deactivate);

    previous = gameplay.Runner{ .jetpack = .{
        .active = true,
        .progress = native_jetpack_visual_shutoff_threshold,
    } };
    current = previous;
    current.jetpack.progress = native_jetpack_visual_shutoff_threshold + 0.01;
    try std.testing.expect(nativeJetpackSoundCues(previous, current).deactivate);

    previous = gameplay.Runner{ .jetpack = .{
        .active = true,
        .progress = 0.25,
    } };
    current = previous;
    current.jetpack.active = false;
    current.jetpack.progress = 0.0;
    try std.testing.expect(nativeJetpackSoundCues(previous, current).deactivate);

    previous = gameplay.Runner{ .jetpack = .{
        .active = true,
        .progress = native_jetpack_visual_shutoff_threshold + 0.01,
    } };
    current = previous;
    current.jetpack.active = false;
    current.jetpack.progress = 0.0;
    try std.testing.expect(!nativeJetpackSoundCues(previous, current).deactivate);
}

test "native slowdown voice band follows the recovered narrow forward-speed window" {
    var previous = gameplay.Runner{};
    var current = previous;
    previous.row_position = 10.0;
    current.row_position = 10.038;
    current.movement_rate_scalar = 0.2;

    try std.testing.expect(nativeGameplaySlowVoiceBandActive(previous, current));

    current.row_position = 10.03;
    try std.testing.expect(!nativeGameplaySlowVoiceBandActive(previous, current));

    current.row_position = 10.05;
    try std.testing.expect(!nativeGameplaySlowVoiceBandActive(previous, current));

    current.row_position = 10.038;
    current.attachment_exit_pending = true;
    try std.testing.expect(!nativeGameplaySlowVoiceBandActive(previous, current));

    current = previous;
    current.row_position = 10.038;
    current.movement_rate_scalar = 0.2;
    current.movement_mode = .attachment;
    try std.testing.expect(!nativeGameplaySlowVoiceBandActive(previous, current));
}

fn nativeGameplayWeaponUpgradeVoiceCue(
    previous: gameplay.Runner,
    current: gameplay.Runner,
    runtime_build_flags: u32,
) bool {
    if (nativeRingEffectKindTriggered(previous, current)) |effect_kind| {
        return (effect_kind == 4 or effect_kind == 5) and
            (runtime_build_flags & 0x10) != 0 and
            current.session_mode != .time_trial;
    }
    return current.weapon_level > previous.weapon_level;
}

fn nativeGameplayVoiceCues(
    previous: gameplay.Runner,
    current: gameplay.Runner,
    runtime_build_flags: u32,
) NativeGameplayVoiceCues {
    return .{
        .start = previous.tick_count < native_gameplay_start_voice_tick and
            current.tick_count >= native_gameplay_start_voice_tick,
        .package_pickup = current.counters.parcels > previous.counters.parcels,
        .weapon_upgrade = nativeGameplayWeaponUpgradeVoiceCue(previous, current, runtime_build_flags),
        .damage_entry = previous.damage_gauge <= 0.0 and current.damage_gauge > 0.0,
        .damage_escalation = previous.damage_warning_state != .draining and
            current.damage_warning_state == .draining,
    };
}

fn nativeGameplayWarningLoopTriggered(previous: gameplay.Runner, current: gameplay.Runner) bool {
    return previous.damage_warning_actor.sample_generation != current.damage_warning_actor.sample_generation;
}

test "native gameplay voice cues fire on the recovered startup timer" {
    var previous = gameplay.Runner{};
    var current = previous;
    const runtime_build_flags = track.postalChallengeRuntimeBuildFlags;

    current.tick_count = native_gameplay_start_voice_tick - 1;
    try std.testing.expectEqual(NativeGameplayVoiceCues{}, nativeGameplayVoiceCues(previous, current, runtime_build_flags));

    previous = current;
    current.tick_count = native_gameplay_start_voice_tick;
    try std.testing.expect(nativeGameplayVoiceCues(previous, current, runtime_build_flags).start);

    previous = gameplay.Runner{};
    current = previous;
    current.counters.parcels = 1;
    try std.testing.expect(nativeGameplayVoiceCues(previous, current, runtime_build_flags).package_pickup);

    previous = gameplay.Runner{};
    current = previous;
    current.last_native_ring_effect_kind = 4;
    current.native_ring_effect_token = 1;
    current.session_mode = .postal;
    try std.testing.expect(nativeGameplayVoiceCues(previous, current, runtime_build_flags).weapon_upgrade);

    current = previous;
    current.last_native_ring_effect_kind = 8;
    current.native_ring_effect_token = 1;
    current.session_mode = .postal;
    try std.testing.expect(!nativeGameplayVoiceCues(previous, current, runtime_build_flags).weapon_upgrade);

    previous = gameplay.Runner{};
    current = previous;
    current.damage_gauge = 0.04;
    try std.testing.expect(nativeGameplayVoiceCues(previous, current, runtime_build_flags).damage_entry);

    previous = gameplay.Runner{ .damage_warning_state = .filling };
    current = previous;
    current.damage_warning_state = .draining;
    try std.testing.expect(nativeGameplayVoiceCues(previous, current, runtime_build_flags).damage_escalation);

    previous = current;
    try std.testing.expectEqual(NativeGameplayVoiceCues{}, nativeGameplayVoiceCues(previous, current, runtime_build_flags));
}

test "native gameplay warning loop keys from the warning actor cadence" {
    const previous = gameplay.Runner{};
    var current = previous;
    try std.testing.expect(!nativeGameplayWarningLoopTriggered(previous, current));

    current.damage_warning_actor.sample_generation = 1;
    try std.testing.expect(nativeGameplayWarningLoopTriggered(previous, current));
}

fn nativeGameplaySupertrampExitVoice(current: gameplay.Runner, previous_attachment_runtime_kind: ?u8) bool {
    if (previous_attachment_runtime_kind != 31) return false;
    if (current.movement_mode == .attachment or current.attachment_follow.active) return false;
    return current.launch.active and current.launch.vertical_velocity > 0.0;
}

test "native supertramp exit voice keys from the launch handoff" {
    const launched = gameplay.Runner{
        .movement_mode = .track,
        .launch = .{
            .active = true,
            .vertical_velocity = 1.0,
        },
    };
    try std.testing.expect(nativeGameplaySupertrampExitVoice(launched, 31));
    try std.testing.expect(!nativeGameplaySupertrampExitVoice(launched, 24));
    try std.testing.expect(!nativeGameplaySupertrampExitVoice(gameplay.Runner{
        .movement_mode = .track,
        .launch = .{
            .active = true,
            .vertical_velocity = 0.0,
        },
    }, 31));
    try std.testing.expect(!nativeGameplaySupertrampExitVoice(gameplay.Runner{
        .movement_mode = .attachment,
        .attachment_follow = .{ .active = true },
        .launch = .{
            .active = true,
            .vertical_velocity = 1.0,
        },
    }, 31));
}

const NativeDeathCutsceneVoiceCues = struct {
    entry: bool = false,
    fallback: bool = false,
};

fn nativeDeathCutsceneVoiceCues(previous: gameplay.Runner, current: gameplay.Runner) NativeDeathCutsceneVoiceCues {
    const death_cutscene_active = current.cutscene_id == gameplay.cutscene_death_id and current.deathCause() == .hazard;
    if (!death_cutscene_active) return .{};

    return .{
        .entry = previous.cutscene_camera.state != 11 and current.cutscene_camera.state == 11,
        .fallback = previous.cutscene_camera.state != 12 and
            current.cutscene_camera.state == 12 and
            !current.attachment_exit_gate_b,
    };
}

test "native death cutscene voice cues key from states 11 and 12" {
    var previous = gameplay.Runner{};
    var current = previous;
    current.cutscene_id = gameplay.cutscene_death_id;
    current.phase = .{ .fall = .{
        .cause = .hazard,
        .world_x = 0.0,
        .world_y = 0.0,
        .world_z = 0.0,
        .vertical_velocity = 0.0,
        .basis_forward = .{ .x = 0.0, .y = 0.0, .z = 1.0 },
        .basis_up = .{ .x = 0.0, .y = 1.0, .z = 0.0 },
    } };
    current.cutscene_camera.state = 11;
    try std.testing.expect(nativeDeathCutsceneVoiceCues(previous, current).entry);
    try std.testing.expect(!nativeDeathCutsceneVoiceCues(previous, current).fallback);

    previous = current;
    current.cutscene_camera.state = 12;
    try std.testing.expect(nativeDeathCutsceneVoiceCues(previous, current).fallback);

    current.attachment_exit_gate_b = true;
    try std.testing.expect(!nativeDeathCutsceneVoiceCues(previous, current).fallback);
}

const PendingRunPersistence = enum {
    none,
    completed,
    failed,
};

const ThanksScreenStage = enum(u8) {
    title_visible = 0,
    title_hidden = 1,
    challenge_visible = 2,
    challenge_hidden = 3,
    time_trial_visible = 4,
    time_trial_hidden = 5,
    continue_visible = 6,
    continue_hold = 7,
};

const ThanksScreenController = struct {
    stage: ThanksScreenStage = .title_visible,
    progress: f32 = 0.0,
    progress_step: f32 = thanks_screen_hold_step,

    fn reset(self: *ThanksScreenController) void {
        self.* = .{};
    }

    fn step(self: *ThanksScreenController) void {
        if (self.progress_step <= 0.0) return;

        self.progress += self.progress_step;
        if (self.progress <= 1.0) return;

        self.progress = 0.0;
        switch (self.stage) {
            .title_visible => {
                self.stage = .title_hidden;
                self.progress_step = thanks_screen_hide_step;
            },
            .title_hidden => {
                self.stage = .challenge_visible;
                self.progress_step = thanks_screen_hold_step;
            },
            .challenge_visible => {
                self.stage = .challenge_hidden;
                self.progress_step = thanks_screen_hide_step;
            },
            .challenge_hidden => {
                self.stage = .time_trial_visible;
                self.progress_step = thanks_screen_hold_step;
            },
            .time_trial_visible => {
                self.stage = .time_trial_hidden;
                self.progress_step = thanks_screen_hide_step;
            },
            .time_trial_hidden => {
                self.stage = .continue_visible;
                self.progress_step = thanks_screen_hold_step;
            },
            .continue_visible => {
                self.stage = .continue_hold;
                self.progress_step = 0.0;
            },
            .continue_hold => {},
        }
    }

    fn allowsContinue(self: *const ThanksScreenController) bool {
        return @intFromEnum(self.stage) >= @intFromEnum(ThanksScreenStage.challenge_visible);
    }

    fn currentText(self: *const ThanksScreenController) ?[]const u8 {
        return switch (self.stage) {
            .title_visible => "Thanks For Playing!",
            .title_hidden => null,
            .challenge_visible => "Test your reflexes in Challenge Mode!",
            .challenge_hidden => null,
            .time_trial_visible => "Improve your skills in Time Trial!",
            .time_trial_hidden => null,
            .continue_visible, .continue_hold => "Click to Continue",
        };
    }
};

const PendingRunResult = struct {
    outcome: RunOutcome = .completed,
    level_name: []const u8,
    mode: ?FrontendLevelMode,
    elapsed_millis: u32,
    parcel_count: u32,
    parcel_target: usize,
    score: u32,
    score_is_partial: bool,
    score_totals: gameplay.ScoreTotals = .{},
    visible_life_stock: u32 = 0,
    damage_gauge: f32 = 0.0,
    high_score_mode: ?high_score.Mode = null,
    high_score_rank: ?usize = null,
    time_trial_record_improved: bool = false,
    unlocked_next_route: bool = false,
    persistence: PendingRunPersistence = .none,
    return_target: ResultReturnTarget,
};

const PendingHighScoreEntry = struct {
    mode: high_score.Mode,
    rank: usize,
};

const SelectedLevelRecordSource = union(enum) {
    postal: usize,
    challenge: usize,
    completion: usize,
};

const SelectedLevelRecordOverride = struct {
    mode: FrontendLevelMode,
    level_index: usize,
    runtime_build_flags: u32,
    replay_speed_scalar: f32,
    challenge_speed_value: u32,
    challenge_difficulty_value: u32,
    challenge_difficulty_scalar: f32,
    runtime_build_seed: u32,
    garbage_scalar: f32,
    salt_scalar: f32,

    fn fromHighScoreEntry(entry: *const high_score.Entry) ?SelectedLevelRecordOverride {
        const raw_mode = std.math.cast(i32, entry.replay_mode_id) orelse return null;
        const mode = std.meta.intToEnum(FrontendLevelMode, raw_mode) catch return null;
        return .{
            .mode = mode,
            .level_index = @intCast(entry.replay_level_index),
            .runtime_build_flags = entry.runtime_build_flags,
            .replay_speed_scalar = entry.replay_speed_scalar,
            .challenge_speed_value = entry.challenge_speed_value,
            .challenge_difficulty_value = entry.challenge_difficulty_value,
            .challenge_difficulty_scalar = entry.challenge_difficulty_scalar,
            .runtime_build_seed = entry.runtime_build_seed,
            .garbage_scalar = entry.garbage_scalar,
            .salt_scalar = entry.salt_scalar,
        };
    }
};

const CompletionAction = enum {
    continue_flow,
};

const high_score_screen_modes = [_]high_score.Mode{
    .postal,
    .challenge,
};

const ExitPromptMode = enum {
    quit_app,
    abandon_run,
    leave_route_map,
};

const ExitPromptChoice = enum {
    no,
    yes,

    fn label(self: ExitPromptChoice) []const u8 {
        return switch (self) {
            .no => "No",
            .yes => "Yes",
        };
    }
};

const exit_prompt_choices = [_]ExitPromptChoice{
    .yes,
    .no,
};

const PostLevelHighScoreAction = enum {
    cancel,
    submit,

    fn label(self: PostLevelHighScoreAction) []const u8 {
        return switch (self) {
            .cancel => "Cancel",
            .submit => "Submit",
        };
    }
};

const post_level_high_score_actions = [_]PostLevelHighScoreAction{
    .cancel,
    .submit,
};

const HighScoreMenuAction = enum {
    back,
    switch_table,
};

const high_score_menu_actions = [_]HighScoreMenuAction{
    .back,
    .switch_table,
};

const route_menu_actions_without_replay = [_]RouteMenuAction{
    .play,
    .back,
};

const route_menu_actions_with_replay = [_]RouteMenuAction{
    .play,
    .watch_best_trial,
    .back,
};

const route_menu_actions_closed = [_]RouteMenuAction{
    .back,
};

const RouteMapHoverState = enum(u8) {
    none = 0,
    card = 1,
    route = 2,
};

const RouteMapScreenMode = enum(u8) {
    normal = 0,
    post_completion_exit = 1,
    replay = 2,
};

// PORT(verified): `initialize_main_menu` seeds the first button at `y = 90`, then chains
// High Scores, Options, Credits, and Exit with `sub_4027B0`. Windows seeds Exit with
// `y = 390` first, but immediately overrides it by chaining from Credits.
const main_menu_start_y: f32 = 90.0;
// PORT(verified): `initialize_new_game_menu` seeds Tutorial at `y = 80`, chains Postal,
// Time Trial, and Challenge Mode with `stack_widget_below`, places Help explicitly at
// `(center - 220, y = 350)`, then seeds Back at `y = 350` but immediately stacks it below
// Challenge Mode. The explicit `350` for Back is only a constructor seed.
const new_game_start_y: f32 = 80.0;
const new_game_help_anchor_y: f32 = 350.0;
const new_game_help_center_offset_x: f32 = -220.0;
const new_game_back_center_offset_x: f32 = 0.0;
// PORT(verified): `initialize_help` places the lone Back control at `(center, y=420)`.
const help_back_anchor_y: f32 = 420.0;
const options_button_count = 4;
const options_fullscreen_button_index: usize = 0;
const options_sound_button_index: usize = 1;
const options_music_button_index: usize = 2;
const options_back_button_index: usize = 3;
// PORT(verified): `initialize_options` seeds the fullscreen row at `y = 75`, then nudges
// the widget down by `+8`, so the final authored-space anchor is `83`.
const options_fullscreen_anchor_y: f32 = 83.0;
// PORT(verified): `initialize_options` keeps the options rows on the centered shell-font path.
// The constructor's `90.0` seed is only the left-measure start fed into `sub_44abe0`; the final
// centered X comes from `arg13 + 320 - width*0.5`, and `arg13` stays `0.0` for this screen.
const options_button_center_offset_x: f32 = 0.0;
const options_slider_adjust_step: f32 = 0.2;
const options_slider_display_lerp: f32 = 0.8;
// PORT(verified): `initialize_galaxy` places the Star Map title at `(15,15)` with shell-font
// scale `0.83`, the bottom Back/Exit control at `(20,420)` with absolute alignment, and
// `open_galaxy_route` seeds the selected route card from `(route_x + 60, route_y - 130)`.
const route_map_title_x: f32 = 15.0;
const route_map_title_y: f32 = 15.0;
const route_map_title_scale: f32 = 0.83;
// PORT(verified): `initialize_galaxy` seeds sprite `138` at `(300,10)`. The shipped
// `SPACEMAPLOGO.TGA` art is `256x64`, and the Windows sprite path uses that authored size.
const route_map_logo_x: f32 = 300.0;
const route_map_logo_y: f32 = 10.0;
const route_map_logo_width: f32 = 256.0;
const route_map_logo_height: f32 = 64.0;
const route_map_back_x: f32 = 20.0;
const route_map_back_y: f32 = 420.0;
const route_map_card_title_scale: f32 = 0.9;
const route_map_card_subtitle_scale: f32 = 0.9;
const route_map_card_body_scale: f32 = 0.7;
// PORT(verified): `open_galaxy_route` expands the selected card bounds by `8` on the
// left/right and bottom edges only. The top edge stays anchored to the title widget.
const route_map_card_horizontal_padding: f32 = 8.0;
const route_map_card_bottom_padding: f32 = 8.0;
const route_map_card_horizontal_pointer_gap: f32 = 6.0;
const route_map_card_star_gap: f32 = 16.0;
const route_map_card_right_limit: f32 = 631.0;
const route_map_card_min_top: f32 = 49.0;
const route_map_card_bottom_y: f32 = 450.0;
const route_map_card_text_gap: f32 = 0.0;
const route_map_primary_button_gap: f32 = 20.0;
const route_map_replay_button_gap: f32 = 10.0;
// PORT(verified): `sub_401130` renders the selected route card (`69516`) as a type-20 style
// 9-slice frame with a recovered authored edge size of `26.0`, not as a stretched quad.
const route_map_card_frame_edge: f32 = 26.0;
// PORT(verified): `update_galaxy` draws galaxy sprites `139..148` as `256x256` quads
// centered on the transformed `sub_4088E0` points, and the inter-route connector uses
// `LINE.TGA` at width `4.0`.
const route_map_galaxy_size: f32 = 256.0;
const route_map_path_line_width: f32 = 4.0;
const high_score_button_count = 2;
const high_score_replay_button_count = high_score.visible_entry_count;
const help_button_count = 1;
const route_map_button_count = 3;
const route_map_primary_button_index: usize = 0;
const route_map_replay_button_index: usize = 1;
const route_map_back_button_index: usize = 2;
// PORT(verified): `cRSubPause::Init()` creates the centered pause stack with `End Game`
// at `y = 145`, then chains `Options` and `Resume` below it with the shared shell-font
// widget stack helper.
const pause_menu_start_y: f32 = 145.0;
const pause_menu_center_offset_x: f32 = 0.0;
const pause_menu_button_count = pause_menu_items.len;
const exit_prompt_button_count = 2;
// PORT(verified): `initialize_high_score_screen` uses title `y = 64`, row start `111`,
// row pitch `27`, and footer row `111 + 10*27 = 381`. Each visible row is a separate
// type-22 widget bundle anchored at `x = -228/-222/-180/+160/+125` for postal or
// `x = -228/-222/-180/+125/+170` for challenge, rather than a single freehand text strip.
const high_score_title_y: f32 = 64.0;
const high_score_row_start_y: f32 = 111.0;
const high_score_row_pitch: f32 = 27.0;
const high_score_footer_y: f32 = 381.0;
const high_score_rank_marker_x: f32 = -228.0;
const high_score_rank_number_x: f32 = -222.0;
const high_score_name_x: f32 = -180.0;
const high_score_postal_score_x: f32 = 160.0;
const high_score_postal_replay_x: f32 = 125.0;
const high_score_challenge_score_x: f32 = 125.0;
const high_score_challenge_replay_x: f32 = 170.0;
const high_score_entry_cancel_x: f32 = -110.0;
const high_score_entry_submit_x: f32 = 55.0;
const high_score_back_x: f32 = -132.0;
const high_score_toggle_x: f32 = 33.0;
// PORT(verified): `initialize_completion_screen` uses title `80`, package line `160`,
// parcel icon sprite `122` at `(100, 144)`, optional bonus widget `302`, and continue `320/400`.
const completion_title_y: f32 = 80.0;
const completion_package_y: f32 = 160.0;
const completion_parcel_icon_x: f32 = 100.0;
const completion_parcel_icon_y: f32 = 144.0;
const completion_parcel_icon_width: f32 = 32.0;
const completion_parcel_icon_height: f32 = 64.0;
const completion_bonus_y: f32 = 302.0;
const completion_continue_y: f32 = 320.0;
const completion_continue_y_with_bonus: f32 = 400.0;
// PORT(verified): `initialize_completion_screen` seeds an owner-local reveal step of `1/24`
// and starts the bonus plus continue widgets hidden. Stage those UI elements in instead of
// drawing the whole summary immediately.
const completion_reveal_step: f32 = 1.0 / 24.0;
const completion_reveal_bonus_threshold: f32 = 1.0;
const completion_reveal_continue_threshold: f32 = 2.0;
// PORT(verified): `initialize_thanks_screen` and `update_thanks_screen` keep one centered
// type-20 widget at `y = 435`, revealing each message for 240 ticks and hiding the first
// two between swaps over 30 ticks before settling on `Click to Continue`.
const thanks_screen_message_y: f32 = 435.0;
const thanks_screen_hold_step: f32 = 1.0 / 240.0;
const thanks_screen_hide_step: f32 = 1.0 / 30.0;
// PORT(verified): the shared centered exit prompt path in `initialize_exit_prompt`
// seeds the Yes/No buttons at `330`, but then stacks both beneath the title at
// `y = stack_widget_below(title)` while keeping their `x = -80/+80` offsets.
const exit_prompt_title_y: f32 = 200.0;
const exit_prompt_yes_x: f32 = -80.0;
const exit_prompt_no_x: f32 = 80.0;
const frontend_activation_delay_step: f32 = 1.0 / 12.0;
const frontend_canvas_width: i32 = 640;
const frontend_canvas_height: i32 = 480;

const FrontendHoverTarget = enum(u8) {
    main_menu_new_game,
    main_menu_high_scores,
    main_menu_options,
    main_menu_credits,
    main_menu_exit,
    new_game_tutorial,
    new_game_postal_mode,
    new_game_time_trial,
    new_game_challenge_mode,
    new_game_help,
    new_game_back,
    options_fullscreen,
    options_sound_volume,
    options_sound_less,
    options_sound_more,
    options_music_volume,
    options_music_less,
    options_music_more,
    options_back,
    pause_menu_end_game,
    pause_menu_options,
    pause_menu_resume,
    route_map_play,
    route_map_watch_best_trial,
    route_map_back,
    help_back,
    high_scores_back,
    high_scores_switch_table,
    high_scores_replay_0,
    high_scores_replay_1,
    high_scores_replay_2,
    high_scores_replay_3,
    high_scores_replay_4,
    high_scores_replay_5,
    high_scores_replay_6,
    high_scores_replay_7,
    high_scores_replay_8,
    high_scores_replay_9,
    post_level_high_scores_cancel,
    post_level_high_scores_submit,
    completion_continue,
    exit_prompt_yes,
    exit_prompt_no,
};

const FrontendQueuedAction = union(enum) {
    main_menu: MainMenuItem,
    new_game_menu: NewGameMenuItem,
    options_menu: OptionsMenuItem,
    pause_menu: PauseMenuItem,
    route_map_menu: RouteMenuAction,
    help_menu: HelpMenuAction,
    high_scores_menu: HighScoreMenuAction,
    high_score_replay: usize,
    post_level_high_scores: PostLevelHighScoreAction,
    completion_screen: CompletionAction,
    exit_prompt: ExitPromptChoice,
};

const HelpMenuAction = enum {
    back,
};

const FrontendQueuedActivation = struct {
    action: FrontendQueuedAction,
    target: FrontendHoverTarget,
    requires_fade: bool,
    progress: f32 = 0.0,
};

fn hoverTargetForMainMenu(index: usize) FrontendHoverTarget {
    return switch (index) {
        0 => .main_menu_new_game,
        1 => .main_menu_high_scores,
        2 => .main_menu_options,
        3 => .main_menu_credits,
        4 => .main_menu_exit,
        else => unreachable,
    };
}

fn hoverTargetForNewGame(index: usize) FrontendHoverTarget {
    return switch (index) {
        0 => .new_game_tutorial,
        1 => .new_game_postal_mode,
        2 => .new_game_time_trial,
        3 => .new_game_challenge_mode,
        4 => .new_game_help,
        5 => .new_game_back,
        else => unreachable,
    };
}

fn hoverTargetForOptions(index: usize) FrontendHoverTarget {
    return switch (index) {
        0 => .options_fullscreen,
        1 => .options_sound_volume,
        2 => .options_music_volume,
        3 => .options_back,
        else => unreachable,
    };
}

fn hoverTargetForOptionsSliderArrow(item: OptionsMenuItem, direction: frontend_widget.SliderDirection) FrontendHoverTarget {
    return switch (item) {
        .sound_volume => switch (direction) {
            .less => .options_sound_less,
            .more => .options_sound_more,
        },
        .music_volume => switch (direction) {
            .less => .options_music_less,
            .more => .options_music_more,
        },
        else => unreachable,
    };
}

fn sliderHoverTargetBelongsToOptionsRow(target: FrontendHoverTarget, item: OptionsMenuItem) bool {
    return switch (item) {
        .sound_volume => switch (target) {
            .options_sound_volume, .options_sound_less, .options_sound_more => true,
            else => false,
        },
        .music_volume => switch (target) {
            .options_music_volume, .options_music_less, .options_music_more => true,
            else => false,
        },
        else => false,
    };
}

fn hoverTargetForPauseMenu(index: usize) FrontendHoverTarget {
    return switch (index) {
        0 => .pause_menu_end_game,
        1 => .pause_menu_options,
        2 => .pause_menu_resume,
        else => unreachable,
    };
}

fn hoverTargetForRouteMenuAction(action: RouteMenuAction) FrontendHoverTarget {
    return switch (action) {
        .play => .route_map_play,
        .watch_best_trial => .route_map_watch_best_trial,
        .back => .route_map_back,
    };
}

fn newGameMenuItemForFrontendMode(mode: FrontendLevelMode) NewGameMenuItem {
    return switch (mode) {
        .tutorial => .tutorial,
        .postal => .postal_mode,
        .time_trial => .time_trial,
        .challenge => .challenge_mode,
    };
}

fn newGameMenuIndexForItem(target: NewGameMenuItem) usize {
    for (new_game_menu_items, 0..) |item, index| {
        if (item == target) return index;
    }
    return 0;
}

fn defaultRouteMapScreenMode(mode: FrontendLevelMode) RouteMapScreenMode {
    // PORT(verified): `initialize_galaxy` uses internal mode `2` for the Time Trial / replay
    // Star Map path, while normal Postal entry starts in mode `0`.
    return switch (mode) {
        .postal => .normal,
        .time_trial => .replay,
        .challenge, .tutorial => unreachable,
    };
}

fn newGameMenuItemForBridgeMode(mode: ?FrontendLevelMode) NewGameMenuItem {
    return switch (mode orelse .postal) {
        .tutorial => .tutorial,
        .postal => .postal_mode,
        .time_trial => .time_trial,
        .challenge => .challenge_mode,
    };
}

fn bridgeTargetForReplaySource(source: SelectedLevelRecordSource, active_level_index: usize) FrontendBridgeTarget {
    return switch (source) {
        .completion => .{ .route_map = .{
            .mode = .time_trial,
            .screen_mode = defaultRouteMapScreenMode(.time_trial),
            .start_route_override = active_level_index,
        } },
        .postal => .{ .high_scores_menu = .postal },
        .challenge => .{ .high_scores_menu = .challenge },
    };
}

fn preservedFrontendOwnerForLevelLaunch(
    mode: FrontendLevelMode,
    level_index: usize,
    selected_level_record_source: ?SelectedLevelRecordSource,
) FrontendBridgeTarget {
    if (selected_level_record_source) |source| {
        return bridgeTargetForReplaySource(source, level_index);
    }

    return switch (mode) {
        .postal => .{ .route_map = .{
            .mode = .postal,
            .screen_mode = defaultRouteMapScreenMode(.postal),
        } },
        .time_trial => .{ .route_map = .{
            .mode = .time_trial,
            .screen_mode = defaultRouteMapScreenMode(.time_trial),
        } },
        .challenge, .tutorial => .{ .new_game_menu = newGameMenuItemForBridgeMode(mode) },
    };
}

fn hoverTargetForHighScores(index: usize) FrontendHoverTarget {
    return switch (index) {
        0 => .high_scores_back,
        1 => .high_scores_switch_table,
        else => unreachable,
    };
}

fn hoverTargetForHighScoreReplay(index: usize) FrontendHoverTarget {
    return switch (index) {
        0 => .high_scores_replay_0,
        1 => .high_scores_replay_1,
        2 => .high_scores_replay_2,
        3 => .high_scores_replay_3,
        4 => .high_scores_replay_4,
        5 => .high_scores_replay_5,
        6 => .high_scores_replay_6,
        7 => .high_scores_replay_7,
        8 => .high_scores_replay_8,
        9 => .high_scores_replay_9,
        else => unreachable,
    };
}

fn hoverTargetForPostLevelHighScores(index: usize) FrontendHoverTarget {
    return switch (index) {
        0 => .post_level_high_scores_cancel,
        1 => .post_level_high_scores_submit,
        else => unreachable,
    };
}

fn hoverTargetForExitPrompt(index: usize) FrontendHoverTarget {
    return switch (index) {
        0 => .exit_prompt_yes,
        1 => .exit_prompt_no,
        else => unreachable,
    };
}

fn queuedActivationTarget(action: FrontendQueuedAction) FrontendHoverTarget {
    return switch (action) {
        .main_menu => |item| switch (item) {
            .new_game => .main_menu_new_game,
            .high_scores => .main_menu_high_scores,
            .options => .main_menu_options,
            .credits => .main_menu_credits,
            .exit => .main_menu_exit,
        },
        .new_game_menu => |item| switch (item) {
            .tutorial => .new_game_tutorial,
            .postal_mode => .new_game_postal_mode,
            .time_trial => .new_game_time_trial,
            .challenge_mode => .new_game_challenge_mode,
            .help => .new_game_help,
            .back => .new_game_back,
        },
        .options_menu => |item| switch (item) {
            .fullscreen => .options_fullscreen,
            .back => .options_back,
            .sound_volume, .music_volume => unreachable,
        },
        .pause_menu => |item| switch (item) {
            .end_game => .pause_menu_end_game,
            .options => .pause_menu_options,
            .@"resume" => .pause_menu_resume,
        },
        .route_map_menu => |item| switch (item) {
            .play => .route_map_play,
            .watch_best_trial => .route_map_watch_best_trial,
            .back => .route_map_back,
        },
        .help_menu => .help_back,
        .high_scores_menu => |item| switch (item) {
            .back => .high_scores_back,
            .switch_table => .high_scores_switch_table,
        },
        .high_score_replay => |index| hoverTargetForHighScoreReplay(index),
        .post_level_high_scores => |item| switch (item) {
            .cancel => .post_level_high_scores_cancel,
            .submit => .post_level_high_scores_submit,
        },
        .completion_screen => .completion_continue,
        .exit_prompt => |choice| switch (choice) {
            .yes => .exit_prompt_yes,
            .no => .exit_prompt_no,
        },
    };
}

fn queuedActivationRequiresFade(action: FrontendQueuedAction) bool {
    return switch (action) {
        .exit_prompt => |choice| switch (choice) {
            .yes => true,
            .no => false,
        },
        else => false,
    };
}

const Mode = enum {
    textures,
    audio,
    models,
    objects,
    levels,
    segments,
    streaks,
};

const DebugSegmentRenderMode = enum {
    game,
    raw,
};

const DebugLightStreakView = struct {
    controller: background.LightStreakController = background.LightStreakController.init(),
    visible_requested: bool = true,
    paused: bool = false,
    show_textured: bool = true,
    show_lines: bool = true,
    alpha_multiplier: f32 = 1.0,
    size_multiplier: f32 = 1.0,
    stretch_multiplier: f32 = 1.0,
    camera_yaw_degrees: f32 = 0.0,
    camera_pitch_degrees: f32 = 0.0,
    camera_fov_degrees: f32 = 110.0,

    fn step(self: *@This()) void {
        if (self.paused) return;
        self.controller.update(self.camera(), self.visible_requested);
    }

    fn stepOnce(self: *@This()) void {
        self.controller.update(self.camera(), self.visible_requested);
    }

    fn reset(self: *@This()) void {
        self.controller = background.LightStreakController.init();
    }

    fn camera(self: *const @This()) background.LightStreakCamera {
        const yaw = std.math.degreesToRadians(self.camera_yaw_degrees);
        const pitch = std.math.degreesToRadians(self.camera_pitch_degrees);
        const forward = normalizeVector3(.{
            .x = @sin(yaw) * @cos(pitch),
            .y = @sin(pitch),
            .z = @cos(yaw) * @cos(pitch),
        });
        var up = rl.Vector3{ .x = 0.0, .y = 1.0, .z = 0.0 };
        if (@abs(dotVector3(forward, up)) > 0.95) {
            up = .{ .x = 0.0, .y = 0.0, .z = 1.0 };
        }
        var right = crossVector3(up, forward);
        if (vectorLength(right) <= 0.0001) {
            right = .{ .x = 1.0, .y = 0.0, .z = 0.0 };
        } else {
            right = normalizeVector3(right);
        }
        const corrected_up = normalizeVector3(crossVector3(forward, right));
        return .{
            .position = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
            .right = right,
            .up = corrected_up,
            .forward = forward,
            .fov_degrees = self.camera_fov_degrees,
        };
    }
};

const identity_subgame_camera_matrix = rl.Matrix{
    .m0 = 1.0,
    .m4 = 0.0,
    .m8 = 0.0,
    .m12 = 0.0,
    .m1 = 0.0,
    .m5 = 1.0,
    .m9 = 0.0,
    .m13 = 3.0,
    .m2 = 0.0,
    .m6 = 0.0,
    .m10 = 1.0,
    .m14 = 0.0,
    .m3 = 0.0,
    .m7 = 0.0,
    .m11 = 0.0,
    .m15 = 1.0,
};
const subgame_camera_blend_factor: f32 = 0.9;

const SubgameCameraSource = enum {
    live,
    override,
    identity,
};

const SubgameCameraState = struct {
    shared_matrix: rl.Matrix = identity_subgame_camera_matrix,
    fov_degrees: f32 = 110.0,
    source: SubgameCameraSource = .identity,
    snap_next: bool = true,
};

const SubgameCameraSelection = struct {
    source: SubgameCameraSource,
    matrix: rl.Matrix,
    fov_degrees: f32,
    snap_next: bool,
};

const AppState = struct {
    allocator: std.mem.Allocator,
    catalog: assets.Catalog,
    animation_catalog: xanim.Catalog,
    ui_font: game_font.Loaded,
    runtime_root_path: []const u8,
    screenshot_dir: []const u8,
    credits_with_remake: bool,
    runtime_config: config.Blob,
    runtime_config_loaded_from_file: bool,
    command: AppCommand,
    window_size: WindowSize,
    audio_ready: bool,
    audio_muted: bool,
    mouse_local_override: ?MouseLocalOverride = null,
    should_exit: bool = false,
    auto_screenshot: ?AutoScreenshot = null,
    auto_screenshot_taken: bool = false,
    frame_capture_index: u32 = 0,
    pending_screenshot: ?ScreenshotRequest = null,
    start_pause_context: bool = false,
    simulation_clock: sim.FixedStepClock = sim.FixedStepClock.init(simulation_step_seconds),
    render_time_seconds: f64 = 0.0,
    gameplay_audio_variant_counter: u32 = 0,
    game_phase: GamePhase = .boot,
    game_phase_ticks: u64 = 0,
    frontend_transition: FrontendTransition = .{},
    boot_task_index: usize = 0,
    menu_index: usize = 0,
    main_menu_button_states: [main_menu_items.len]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** main_menu_items.len,
    new_game_menu_index: usize = 0,
    new_game_button_states: [new_game_menu_items.len]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** new_game_menu_items.len,
    options_menu_index: usize = 0,
    options_button_states: [options_button_count]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** options_button_count,
    pause_menu_index: usize = 0,
    pause_menu_button_states: [pause_menu_button_count]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** pause_menu_button_count,
    options_return_phase: GamePhase = .main_menu,
    help_button_states: [help_button_count]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** help_button_count,
    route_map_button_states: [route_map_button_count]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** route_map_button_count,
    high_scores_menu_index: usize = 0,
    high_scores_action_index: usize = 1,
    high_score_button_states: [high_score_button_count]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** high_score_button_count,
    high_score_replay_button_states: [high_score_replay_button_count]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** high_score_replay_button_count,
    exit_prompt_choice_index: usize = 0,
    exit_prompt_button_states: [exit_prompt_button_count]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** exit_prompt_button_count,
    exit_prompt_return_phase: GamePhase = .main_menu,
    exit_prompt_mode: ExitPromptMode = .quit_app,
    post_level_high_score_action_index: usize = 1,
    post_level_high_score_button_states: [post_level_high_score_actions.len]frontend_widget.TextButtonState = [_]frontend_widget.TextButtonState{.{}} ** post_level_high_score_actions.len,
    post_level_high_score_name_len: usize = 0,
    post_level_high_score_name_buf: [high_score.name_capacity]u8 = [_]u8{0} ** high_score.name_capacity,
    high_score_tables: high_score.Tables,
    pending_run_result: ?PendingRunResult = null,
    completion_overlay_active: bool = false,
    preserve_completion_screen_reveal_on_enter: bool = false,
    game_status_message: ?[]const u8 = null,
    game_status_ticks: u32 = 0,
    gameplay_click_start_active: bool = false,
    seed_level_intro_cutscene: bool = false,
    subgame_camera: SubgameCameraState = .{},
    tutorial_reference_score: u32 = 0,
    native_gameplay_slow_voice_progress: f32 = 0.0,
    gameplay_voice_manager: GameplayVoiceManager = .{},
    native_gameplay_voice_manager: NativeGameplayVoiceManager = .{},
    announced_slug_voice_cells: [max_announced_slug_voice_cells]gameplay.RowTarget = [_]gameplay.RowTarget{.{ .row = 0, .lane = 0 }} ** max_announced_slug_voice_cells,
    announced_slug_voice_cell_count: usize = 0,
    active_level_segment_index: ?usize = null,
    level_prompt_queue: level_prompt.Queue = .{},
    mouse_level_lane_target: ?f32 = null,
    frontend_route_mode: ?FrontendLevelMode = null,
    route_map_screen_mode: RouteMapScreenMode = .normal,
    frontend_route_index: usize = 0,
    start_route_index_override: ?usize = null,
    route_menu_action_index: usize = 0,
    route_map_open_index: ?usize = null,
    route_map_hover_state: RouteMapHoverState = .none,
    route_map_hovered_index: ?usize = null,
    active_frontend_mode: ?FrontendLevelMode = null,
    active_frontend_level_index: usize = 0,
    preserved_frontend_owner: FrontendBridgeTarget = .main_menu,
    math_random_state: u32 = 1,
    current_runtime_build_seed: u32 = 0,
    current_runtime_build_seed_level_index: ?usize = null,
    current_runtime_build_seed_mode: ?FrontendLevelMode = null,
    selected_level_record_override: ?SelectedLevelRecordOverride = null,
    selected_level_record_source: ?SelectedLevelRecordSource = null,
    selected_replay_cache: ?high_score.DecodedReplay = null,
    selected_replay_fade_exit_pending: bool = false,
    route_map_route_highlight_alpha: [galaxy.map_route_count + 1]f32 = [_]f32{0.0} ** (galaxy.map_route_count + 1),
    route_map_route_highlight_target: [galaxy.map_route_count + 1]f32 = [_]f32{0.0} ** (galaxy.map_route_count + 1),
    mode: Mode = .textures,
    debug_light_streak_view: DebugLightStreakView = .{},
    model_flip_v: bool = true,
    object_flip_v: bool = true,
    texture_index: usize,
    audio_index: usize,
    model_index: usize,
    object_index: usize,
    level_index: usize,
    segment_index: usize = 0,
    segment_render_mode: DebugSegmentRenderMode = .game,
    segment_show_overlay: bool = false,
    segment_show_grid: bool = false,
    segment_show_attachments: bool = true,
    segment_track_set_index: u8 = 0,
    level_segment_index: usize = 0,
    current_texture: ?assets.LoadedTexture = null,
    frontend_canvas: ?rl.RenderTexture2D = null,
    frontend_cursor_texture: ?assets.LoadedTexture = null,
    frontend_widget_art: FrontendWidgetArt = .{},
    frontend_sound_fx: FrontendSoundFx = .{},
    hovered_frontend_target: ?FrontendHoverTarget = null,
    keyboard_frontend_focus_visible: bool = false,
    pending_frontend_activation: ?FrontendQueuedActivation = null,
    completion_continue_button_state: frontend_widget.TextButtonState = .{},
    completion_screen_reveal_progress: f32 = 0.0,
    thanks_screen_controller: ThanksScreenController = .{},
    slider_art: SliderArt = .{},
    route_map_art: RouteMapArt = .{},
    options_sound_display_value: f32 = 0.0,
    options_music_display_value: f32 = 0.0,
    current_sound: ?assets.LoadedSound = null,
    current_voice_sound: ?assets.LoadedSound = null,
    current_music: ?assets.LoadedMusic = null,
    current_model: ?x2.Uploaded = null,
    current_animation: ?xanim.Player = null,
    current_object: ?object.LoadedObject = null,
    current_level: ?level.Definition = null,
    current_segment: ?segment.Definition = null,
    current_track_preview: ?track.LoadedLevelPreview = null,
    current_game_track_scene: ?track_render.Scene = null,
    current_gameplay_turbo_model: ?x2.Uploaded = null,
    current_gameplay_turbo_animation: ?xanim.Player = null,
    current_gameplay_turbo_model_path: ?[]const u8 = null,
    current_gameplay_barrier_object: ?object.LoadedObject = null,
    current_gameplay_lazer_object: ?object.LoadedObject = null,
    current_gameplay_vapour_lazer_object: ?object.LoadedObject = null,
    current_gameplay_salt_model: ?x2.Uploaded = null,
    current_gameplay_turret_model: ?x2.Uploaded = null,
    current_gameplay_blaster_top_models: GameplayWeaponModelSet = .{},
    current_gameplay_laser_left_models: GameplayWeaponModelSet = .{},
    current_gameplay_laser_right_models: GameplayWeaponModelSet = .{},
    current_gameplay_rocket_launcher_models: GameplayWeaponModelSet = .{},
    current_gameplay_rocket_model: ?x2.Uploaded = null,
    current_gameplay_invincible_models: GameplayInvincibleModelSet = .{},
    gameplay_weapon_visual_state: GameplayWeaponVisualState = .{},
    current_gameplay_sprites: GameplaySpriteArt = .{},
    current_gameplay_sound_fx: GameplaySoundFx = .{},
    active_gameplay_effects: [max_active_gameplay_effects]GameplayEffect = [_]GameplayEffect{.{}} ** max_active_gameplay_effects,
    active_gameplay_effect_count: usize = 0,
    current_standalone_segment_preview: ?track.LoadedLevelPreview = null,
    current_standalone_segment_scene: ?track_render.Scene = null,
    current_game_background: ?background.Loaded = null,
    current_game_background_runtime: ?background.Runtime = null,
    current_background_light_streak_texture: ?assets.LoadedTexture = null,
    background_light_streaks: background.LightStreakController = background.LightStreakController.init(),
    current_loading_screen: ?loading_screen.Loaded = null,
    current_text_script: ?intro.Loaded = null,
    galaxy_names: ?galaxy.Definition = null,
    frontend_route_level: ?level.Definition = null,
    preloaded_intro_background: ?background.Loaded = null,
    preloaded_main_menu_background: ?background.Loaded = null,
    preloaded_route_map_background: ?background.Loaded = null,
    preloaded_help_background: ?background.Loaded = null,
    preloaded_intro_script: ?intro.Loaded = null,
    preloaded_credits_script: ?intro.Loaded = null,
    preloaded_intro_music: ?assets.LoadedMusic = null,
    preloaded_menu_music: ?assets.LoadedMusic = null,
    level_runner: ?gameplay.Runner = null,
    pending_level_input: gameplay.RunnerInput = .{},

    fn init(allocator: std.mem.Allocator, options: Options, runtime_config_result: config.LoadResult, audio_ready: bool) !AppState {
        var catalog = try assets.Catalog.init(allocator, options.archive_path);
        errdefer catalog.deinit();
        var animation_catalog = try xanim.Catalog.load(allocator, &catalog);
        errdefer animation_catalog.deinit();
        var ui_font = try game_font.Loaded.load(allocator, &catalog);
        errdefer ui_font.deinit();
        const frontend_canvas = if (options.command == .game) blk: {
            const canvas = try rl.loadRenderTexture(frontend_canvas_width, frontend_canvas_height);
            rl.setTextureWrap(canvas.texture, .clamp);
            rl.setTextureFilter(canvas.texture, .bilinear);
            break :blk canvas;
        } else null;
        errdefer if (frontend_canvas) |canvas| canvas.unload();
        var frontend_cursor_texture = try catalog.loadTextureByPath(allocator, frontend_cursor_texture_path);
        errdefer frontend_cursor_texture.unload();
        var frontend_widget_art = try loadFrontendWidgetArt(allocator, &catalog);
        errdefer frontend_widget_art.unload();
        var frontend_sound_fx = try loadFrontendSoundFx(allocator, &catalog, audio_ready);
        errdefer frontend_sound_fx.unload();
        var gameplay_sound_fx = try loadGameplaySoundFx(allocator, &catalog, audio_ready);
        errdefer gameplay_sound_fx.unload();
        var slider_art = try loadSliderArt(allocator, &catalog);
        errdefer slider_art.unload();
        var route_map_art = try loadRouteMapArt(allocator, &catalog);
        errdefer route_map_art.unload();
        var background_light_streak_texture = try catalog.loadTextureByPath(allocator, background_light_streak_sprite_path);
        rl.setTextureFilter(background_light_streak_texture.texture, .point);
        errdefer background_light_streak_texture.unload();
        var galaxy_names: ?galaxy.Definition = try galaxy.loadByPath(allocator, &catalog, galaxy_names_path);
        errdefer if (galaxy_names) |*names| names.deinit();

        const texture_index = catalog.findTextureIndex(default_texture_path) orelse 0;
        const audio_index = catalog.findAudioIndex(default_audio_path) orelse 0;
        const model_index = catalog.findModelIndex(default_model_path) orelse 0;
        const object_index = catalog.findObjectIndex(default_object_path) orelse 0;
        const level_index = catalog.findLevelIndex(default_level_path) orelse 0;
        const segment_index: usize = 0;

        var state = AppState{
            .allocator = allocator,
            .catalog = catalog,
            .animation_catalog = animation_catalog,
            .ui_font = ui_font,
            .runtime_root_path = options.runtime_root_path,
            .screenshot_dir = options.screenshot_dir,
            .credits_with_remake = options.credits_with_remake,
            .runtime_config = runtime_config_result.blob,
            .runtime_config_loaded_from_file = runtime_config_result.loaded_from_file,
            .command = options.command,
            .window_size = options.window_size_override orelse defaultWindowSizeForCommand(options.command),
            .audio_ready = audio_ready,
            .audio_muted = options.hidden_window,
            .options_sound_display_value = runtime_config_result.blob.soundVolume(),
            .options_music_display_value = runtime_config_result.blob.musicVolume(),
            .mouse_local_override = options.mouse_local_override,
            .auto_screenshot = options.auto_screenshot,
            .start_route_index_override = options.start_route_index,
            .start_pause_context = options.pause_context,
            .high_score_tables = high_score.Tables.initDefault(),
            .texture_index = texture_index,
            .audio_index = audio_index,
            .model_index = model_index,
            .object_index = object_index,
            .level_index = level_index,
            .segment_index = segment_index,
            .frontend_canvas = frontend_canvas,
            .frontend_cursor_texture = frontend_cursor_texture,
            .frontend_widget_art = frontend_widget_art,
            .frontend_sound_fx = frontend_sound_fx,
            .current_gameplay_sound_fx = gameplay_sound_fx,
            .slider_art = slider_art,
            .route_map_art = route_map_art,
            .current_background_light_streak_texture = background_light_streak_texture,
            .galaxy_names = galaxy_names,
        };
        errdefer state.deinit();
        galaxy_names = null;
        state.applyAudioConfigVolumes();

        switch (options.command) {
            .debug, .smoke => {
                try state.high_score_tables.loadFromRuntimeRoot(allocator, options.runtime_root_path);
                try state.reloadTexture();
                try state.reloadModel();
                try state.reloadObject();
                try state.reloadLevel();
                try state.reloadStandaloneSegment();
            },
            .game => if (options.start_phase) |start_phase|
                try state.enterStartPhase(start_phase)
            else
                try state.enterGamePhase(.boot),
        }
        return state;
    }

    fn deinit(self: *AppState) void {
        self.stopAudioPreview();
        self.unloadLoadingScreen();
        self.unloadGameBackground();
        self.unloadPreloadedBootAssets();
        self.clearSelectedReplayCache();
        if (self.current_background_light_streak_texture) |*texture| {
            texture.unload();
            self.current_background_light_streak_texture = null;
        }
        if (self.pending_screenshot) |*request| {
            request.deinit(self.allocator);
            self.pending_screenshot = null;
        }

        if (self.current_model) |*model| {
            model.deinit();
            self.current_model = null;
        }
        if (self.current_animation) |*animation| {
            animation.deinit();
            self.current_animation = null;
        }
        if (self.current_object) |*loaded_object| {
            loaded_object.deinit();
            self.current_object = null;
        }
        if (self.current_segment) |*loaded_segment| {
            loaded_segment.deinit();
            self.current_segment = null;
        }
        if (self.current_level) |*loaded_level| {
            loaded_level.deinit();
            self.current_level = null;
        }
        if (self.current_track_preview) |*loaded_track_preview| {
            loaded_track_preview.deinit();
            self.current_track_preview = null;
        }
        if (self.current_game_track_scene) |*scene| {
            scene.deinit();
            self.current_game_track_scene = null;
        }
        self.unloadGameplayTurbo();
        self.unloadGameplayBarrier();
        self.unloadGameplayLazer();
        self.unloadGameplaySalt();
        self.unloadGameplayActorModels();
        self.unloadGameplaySprites();
        self.unloadGameplaySoundFx();
        if (self.current_standalone_segment_preview) |*loaded_track_preview| {
            loaded_track_preview.deinit();
            self.current_standalone_segment_preview = null;
        }
        if (self.current_standalone_segment_scene) |*scene| {
            scene.deinit();
            self.current_standalone_segment_scene = null;
        }
        if (self.current_text_script) |*script| {
            script.deinit(self.allocator);
            self.current_text_script = null;
        }

        self.stopVoicePlayback();
        if (self.current_texture) |*texture| {
            texture.unload();
            self.current_texture = null;
        }
        if (self.frontend_canvas) |canvas| {
            canvas.unload();
            self.frontend_canvas = null;
        }
        if (self.frontend_cursor_texture) |*texture| {
            texture.unload();
            self.frontend_cursor_texture = null;
        }
        self.frontend_widget_art.unload();
        self.frontend_sound_fx.unload();
        self.slider_art.unload();
        self.route_map_art.unload();
        self.unloadFrontendRouteLevel();
        if (self.galaxy_names) |*names| {
            names.deinit();
            self.galaxy_names = null;
        }

        self.ui_font.deinit();
        self.animation_catalog.deinit();
        self.catalog.deinit();
        self.high_score_tables.deinit(self.allocator);
    }

    fn warmupSmokeTest(self: *AppState) !void {
        var loaded_loading_screen = try loading_screen.Loaded.load(self.allocator, &self.catalog);
        defer loaded_loading_screen.deinit();
        if (loaded_loading_screen.background_texture.texture.width <= 0 or loaded_loading_screen.bar_texture.texture.width <= 0) {
            return error.InvalidLoadingScreenTexture;
        }

        var loaded_intro_background = try background.Loaded.loadByPath(self.allocator, &self.catalog, intro_background_path);
        defer loaded_intro_background.deinit();
        if (loaded_intro_background.primary_texture.texture.width <= 0) {
            return error.InvalidIntroBackgroundTexture;
        }

        var loaded_thanks_background = try background.Loaded.loadByPath(self.allocator, &self.catalog, thanks_screen_background_path);
        defer loaded_thanks_background.deinit();
        if (loaded_thanks_background.primary_texture.texture.width <= 0) {
            return error.InvalidThanksBackgroundTexture;
        }

        var loaded_intro_script = try self.loadConfiguredTextScriptEntry(intro_script_path);
        defer loaded_intro_script.deinit(self.allocator);
        if (loaded_intro_script.entries.len == 0) {
            return error.EmptyIntroScript;
        }

        var loaded_credits_script = try self.loadConfiguredTextScriptEntry(credits_script_path);
        defer loaded_credits_script.deinit(self.allocator);
        if (loaded_credits_script.entries.len == 0) {
            return error.EmptyCreditsScript;
        }

        if (!self.audio_ready or self.catalog.audio_entries.len == 0) {
            return;
        }

        try self.previewSound();
        self.stopAudioPreview();
        try self.previewMusic();
    }

    // PORT(partial): the original loading screen advances from real archive reads
    // and startup initialization loops. The port now advances from actual front-end
    // startup loads instead of a timer, but it still does not cover the full world-init pass.
    fn advanceBootTask(self: *AppState) !bool {
        if (self.boot_task_index >= boot_tasks.len) return true;

        switch (boot_tasks[self.boot_task_index]) {
            .load_high_scores => try self.high_score_tables.loadFromRuntimeRoot(self.allocator, self.runtime_root_path),
            .load_intro_background => {
                self.unloadPreloadedBackground(&self.preloaded_intro_background);
                self.preloaded_intro_background = try background.Loaded.loadByPath(self.allocator, &self.catalog, intro_background_path);
            },
            .load_main_menu_background => {
                self.unloadPreloadedBackground(&self.preloaded_main_menu_background);
                self.preloaded_main_menu_background = try background.Loaded.loadByPath(self.allocator, &self.catalog, main_menu_background_path);
            },
            .load_route_map_background => {
                self.unloadPreloadedBackground(&self.preloaded_route_map_background);
                self.preloaded_route_map_background = try background.Loaded.loadByPath(self.allocator, &self.catalog, route_map_background_path);
            },
            .load_help_background => {
                self.unloadPreloadedBackground(&self.preloaded_help_background);
                self.preloaded_help_background = try background.Loaded.loadByPath(self.allocator, &self.catalog, help_background_path);
            },
            .load_intro_script => {
                self.unloadPreloadedTextScript(&self.preloaded_intro_script);
                self.preloaded_intro_script = try self.loadConfiguredTextScriptEntry(intro_script_path);
            },
            .load_credits_script => {
                self.unloadPreloadedTextScript(&self.preloaded_credits_script);
                self.preloaded_credits_script = try self.loadConfiguredTextScriptEntry(credits_script_path);
            },
            .load_intro_music => {
                self.unloadPreloadedMusic(&self.preloaded_intro_music);
                self.preloaded_intro_music = try self.catalog.loadMusicByPath(self.allocator, intro_music_path);
            },
            .load_menu_music => {
                self.unloadPreloadedMusic(&self.preloaded_menu_music);
                self.preloaded_menu_music = try self.catalog.loadMusicByPath(self.allocator, default_audio_path);
            },
        }

        self.boot_task_index += 1;
        return self.boot_task_index >= boot_tasks.len;
    }

    fn unloadPreloadedBootAssets(self: *AppState) void {
        self.unloadPreloadedBackground(&self.preloaded_intro_background);
        self.unloadPreloadedBackground(&self.preloaded_main_menu_background);
        self.unloadPreloadedBackground(&self.preloaded_route_map_background);
        self.unloadPreloadedBackground(&self.preloaded_help_background);
        self.unloadPreloadedTextScript(&self.preloaded_intro_script);
        self.unloadPreloadedTextScript(&self.preloaded_credits_script);
        self.unloadPreloadedMusic(&self.preloaded_intro_music);
        self.unloadPreloadedMusic(&self.preloaded_menu_music);
    }

    fn unloadPreloadedBackground(self: *AppState, slot: *?background.Loaded) void {
        _ = self;
        if (slot.*) |*loaded| {
            loaded.deinit();
            slot.* = null;
        }
    }

    fn unloadPreloadedTextScript(self: *AppState, slot: *?intro.Loaded) void {
        if (slot.*) |*loaded| {
            loaded.deinit(self.allocator);
            slot.* = null;
        }
    }

    fn unloadPreloadedMusic(self: *AppState, slot: *?assets.LoadedMusic) void {
        _ = self;
        if (slot.*) |*loaded| {
            loaded.unload();
            slot.* = null;
        }
    }

    fn unloadGameplayTurbo(self: *AppState) void {
        if (self.current_gameplay_turbo_animation) |*animation| {
            animation.deinit();
            self.current_gameplay_turbo_animation = null;
        }
        if (self.current_gameplay_turbo_model) |*model| {
            model.deinit();
            self.current_gameplay_turbo_model = null;
        }
        self.current_gameplay_turbo_model_path = null;
    }

    fn unloadGameplayBarrier(self: *AppState) void {
        if (self.current_gameplay_barrier_object) |*loaded_object| {
            loaded_object.deinit();
            self.current_gameplay_barrier_object = null;
        }
    }

    fn unloadGameplayLazer(self: *AppState) void {
        if (self.current_gameplay_lazer_object) |*loaded_object| {
            loaded_object.deinit();
            self.current_gameplay_lazer_object = null;
        }
        if (self.current_gameplay_vapour_lazer_object) |*loaded_object| {
            loaded_object.deinit();
            self.current_gameplay_vapour_lazer_object = null;
        }
    }

    fn unloadGameplaySalt(self: *AppState) void {
        if (self.current_gameplay_salt_model) |*model| {
            model.deinit();
            self.current_gameplay_salt_model = null;
        }
    }

    fn unloadGameplayActorModels(self: *AppState) void {
        if (self.current_gameplay_turret_model) |*model| {
            model.deinit();
            self.current_gameplay_turret_model = null;
        }
        self.current_gameplay_blaster_top_models.unload();
        self.current_gameplay_laser_left_models.unload();
        self.current_gameplay_laser_right_models.unload();
        self.current_gameplay_rocket_launcher_models.unload();
        if (self.current_gameplay_rocket_model) |*model| {
            model.deinit();
            self.current_gameplay_rocket_model = null;
        }
        self.current_gameplay_invincible_models.unload();
        self.gameplay_weapon_visual_state = .{};
    }

    fn unloadGameplaySprites(self: *AppState) void {
        self.current_gameplay_sprites.unload();
    }

    fn unloadGameplaySoundFx(self: *AppState) void {
        self.current_gameplay_sound_fx.unload();
    }

    fn reloadGameplayTurbo(self: *AppState) !void {
        try self.reloadGameplayTurboForPath(default_model_path);
    }

    fn reloadGameplayTurboForPath(self: *AppState, model_path: []const u8) !void {
        self.unloadGameplayTurbo();

        const entry_index = self.catalog.findModelIndex(model_path) orelse return;
        const entry = self.catalog.model_entries[entry_index];
        self.current_gameplay_turbo_model_path = entry.path;

        if (self.animation_catalog.findClipIndexForModelPath(entry.path)) |clip_index| {
            const clip = &self.animation_catalog.clips[clip_index];
            if (clip.frames.len > 1) {
                self.current_gameplay_turbo_animation = try xanim.Player.load(
                    self.allocator,
                    &self.catalog,
                    clip,
                    true,
                    xanim.frameNumberFromPath(entry.path),
                );
                return;
            }
        }

        self.current_gameplay_turbo_model = try x2.Uploaded.loadFromArchive(
            self.allocator,
            &self.catalog,
            entry,
            true,
        );
    }

    fn syncGameplayTurboAnimation(self: *AppState) !void {
        if (self.game_phase != .level) return;
        if (!self.isTutorialGameplay()) return;
        const desired_model_path = if (self.level_prompt_queue.active() != null and !self.gameplay_click_start_active)
            gameplay_turbo_talk_model_path
        else
            default_model_path;
        if (self.current_gameplay_turbo_model_path) |current_path| {
            if (std.ascii.eqlIgnoreCase(current_path, desired_model_path)) return;
        }
        try self.reloadGameplayTurboForPath(desired_model_path);
    }

    fn reloadGameplayBarrier(self: *AppState) !void {
        self.unloadGameplayBarrier();

        const entry_index = self.catalog.findObjectIndex(gameplay_barrier_object_path) orelse return;
        const entry = self.catalog.object_entries[entry_index];
        self.current_gameplay_barrier_object = try object.LoadedObject.loadFromArchive(
            self.allocator,
            &self.catalog,
            entry,
            true,
        );
    }

    fn reloadGameplayLazer(self: *AppState) !void {
        self.unloadGameplayLazer();

        const entry_index = self.catalog.findObjectIndex(gameplay_lazer_object_path) orelse return;
        const entry = self.catalog.object_entries[entry_index];
        self.current_gameplay_lazer_object = try object.LoadedObject.loadFromArchive(
            self.allocator,
            &self.catalog,
            entry,
            true,
        );

        if (self.catalog.findObjectIndex(gameplay_vapour_lazer_object_path)) |vapour_index| {
            self.current_gameplay_vapour_lazer_object = try object.LoadedObject.loadFromArchive(
                self.allocator,
                &self.catalog,
                self.catalog.object_entries[vapour_index],
                true,
            );
        }
    }

    fn reloadGameplaySalt(self: *AppState) !void {
        self.unloadGameplaySalt();

        const entry_index = self.catalog.findModelIndex(gameplay_salt_model_path) orelse return;
        const entry = self.catalog.model_entries[entry_index];
        self.current_gameplay_salt_model = try x2.Uploaded.loadFromArchive(
            self.allocator,
            &self.catalog,
            entry,
            true,
        );
    }

    fn loadGameplayWeaponModelSet(
        self: *AppState,
        set: *GameplayWeaponModelSet,
        base_path: []const u8,
        draw_paths: []const []const u8,
        fire_path: ?[]const u8,
    ) !void {
        if (self.catalog.findModelIndex(base_path)) |entry_index| {
            set.base = try x2.Uploaded.loadFromArchive(
                self.allocator,
                &self.catalog,
                self.catalog.model_entries[entry_index],
                true,
            );
        }
        set.draw_frame_count = @intCast(draw_paths.len);
        for (draw_paths, 0..) |path, index| {
            if (self.catalog.findModelIndex(path)) |entry_index| {
                set.draw_frames[index] = try x2.Uploaded.loadFromArchive(
                    self.allocator,
                    &self.catalog,
                    self.catalog.model_entries[entry_index],
                    true,
                );
            }
        }
        if (fire_path) |path| {
            if (self.catalog.findModelIndex(path)) |entry_index| {
                set.fire = try x2.Uploaded.loadFromArchive(
                    self.allocator,
                    &self.catalog,
                    self.catalog.model_entries[entry_index],
                    true,
                );
            }
        }
    }

    fn reloadGameplayActorModels(self: *AppState) !void {
        self.unloadGameplayActorModels();

        const turret_index = self.catalog.findModelIndex(gameplay_turret_model_path) orelse return;
        self.current_gameplay_turret_model = try x2.Uploaded.loadFromArchive(
            self.allocator,
            &self.catalog,
            self.catalog.model_entries[turret_index],
            true,
        );

        try self.loadGameplayWeaponModelSet(
            &self.current_gameplay_blaster_top_models,
            gameplay_blaster_top_model_path,
            &gameplay_blaster_top_draw_model_paths,
            gameplay_blaster_top_fire_model_path,
        );
        try self.loadGameplayWeaponModelSet(
            &self.current_gameplay_laser_left_models,
            gameplay_laser_left_model_path,
            &gameplay_laser_left_draw_model_paths,
            null,
        );
        try self.loadGameplayWeaponModelSet(
            &self.current_gameplay_laser_right_models,
            gameplay_laser_right_model_path,
            &gameplay_laser_right_draw_model_paths,
            null,
        );
        try self.loadGameplayWeaponModelSet(
            &self.current_gameplay_rocket_launcher_models,
            gameplay_rocket_launcher_model_path,
            &gameplay_rocket_launcher_draw_model_paths,
            null,
        );
        if (self.catalog.findModelIndex(gameplay_rocket_model_path)) |entry_index| {
            self.current_gameplay_rocket_model = try x2.Uploaded.loadFromArchive(
                self.allocator,
                &self.catalog,
                self.catalog.model_entries[entry_index],
                true,
            );
        }
        for (gameplay_invincible_model_paths, 0..) |path, index| {
            if (self.catalog.findModelIndex(path)) |entry_index| {
                self.current_gameplay_invincible_models.frames[index] = try x2.Uploaded.loadFromArchive(
                    self.allocator,
                    &self.catalog,
                    self.catalog.model_entries[entry_index],
                    true,
                );
            }
        }
    }

    fn reloadGameplaySprites(self: *AppState) !void {
        self.unloadGameplaySprites();
        self.current_gameplay_sprites = try loadGameplaySpriteArt(self.allocator, &self.catalog);
    }

    fn reloadGameplaySoundFx(self: *AppState) !void {
        self.unloadGameplaySoundFx();
        self.current_gameplay_sound_fx = try loadGameplaySoundFx(self.allocator, &self.catalog, self.audio_ready);
    }

    fn activeGameplayTurbo(self: *const AppState) ?*const x2.Uploaded {
        if (self.current_gameplay_turbo_animation) |*animation| {
            return &animation.rendered;
        }
        if (self.current_gameplay_turbo_model) |*model| {
            return model;
        }
        return null;
    }

    fn saveRuntimeConfig(self: *const AppState) !void {
        try self.runtime_config.saveToRuntimeRoot(self.runtime_root_path);
    }

    fn update(self: *AppState, frame_delta_seconds: f64) !void {
        self.render_time_seconds += frame_delta_seconds;
        if (self.current_music) |music| {
            rl.updateMusicStream(music.music);
        }
        const tick_count = self.simulation_clock.beginFrame(frame_delta_seconds);
        const runner_input = self.pending_level_input;
        self.pending_level_input = .{};
        for (0..tick_count) |tick_index| {
            try self.simulateTick(if (tick_index == 0) runner_input else .{});
        }
    }

    fn simulateTick(self: *AppState, runner_input: gameplay.RunnerInput) !void {
        switch (self.command) {
            .game => try self.simulateGameTick(runner_input),
            .debug, .smoke => {
                if (self.mode == .streaks) {
                    self.debug_light_streak_view.step();
                }
                if (self.current_animation) |*animation| {
                    try animation.step(self.simulation_clock.step_seconds);
                }
                if (self.current_track_preview) |*loaded_track_preview| {
                    if (self.level_runner) |*runner| {
                        runner.step(loaded_track_preview, runner_input, @floatCast(self.simulation_clock.step_seconds));
                    }
                }
            },
        }
    }

    fn handleInput(self: *AppState) !void {
        if (rl.isKeyPressed(.f12)) {
            try self.queueScreenshot(false);
        }

        switch (self.command) {
            .game => return self.handleGameInput(),
            .smoke => return,
            .debug => {},
        }

        if (rl.isKeyPressed(.tab)) {
            try self.setMode(nextMode(self.mode));
        }
        if (rl.isKeyPressed(.one)) {
            try self.setMode(.textures);
        }
        if (rl.isKeyPressed(.two)) {
            try self.setMode(.audio);
        }
        if (rl.isKeyPressed(.three)) {
            try self.setMode(.models);
        }
        if (rl.isKeyPressed(.four)) {
            try self.setMode(.objects);
        }
        if (rl.isKeyPressed(.five)) {
            try self.setMode(.levels);
        }
        if (rl.isKeyPressed(.six)) {
            try self.setMode(.segments);
        }
        if (rl.isKeyPressed(.seven)) {
            try self.setMode(.streaks);
        }

        if (self.mode == .levels) {
            if (rl.isKeyPressed(.left)) {
                self.level_index = wrappedIndex(self.catalog.level_entries.len, self.level_index, -1);
                try self.reloadLevel();
            }
            if (rl.isKeyPressed(.right)) {
                self.level_index = wrappedIndex(self.catalog.level_entries.len, self.level_index, 1);
                try self.reloadLevel();
            }
            if (rl.isKeyPressed(.up)) {
                try self.stepLevelSegment(-1);
            }
            if (rl.isKeyPressed(.down)) {
                try self.stepLevelSegment(1);
            }
            if (rl.isKeyPressed(.a)) {
                self.pending_level_input.lane_delta -= 1;
            }
            if (rl.isKeyPressed(.d)) {
                self.pending_level_input.lane_delta += 1;
            }
            if (rl.isKeyPressed(.w)) {
                self.pending_level_input.speed_delta_rows_per_second += 2.0;
            }
            if (rl.isKeyPressed(.s)) {
                self.pending_level_input.speed_delta_rows_per_second -= 2.0;
            }
            if (rl.isKeyPressed(.space)) {
                self.pending_level_input.toggle_pause = true;
            }
            if (rl.isKeyPressed(.r)) {
                self.pending_level_input.reset = true;
            }
        } else if (self.mode == .segments) {
            if (rl.isKeyPressed(.left)) {
                try self.stepSelection(-1);
            }
            if (rl.isKeyPressed(.right)) {
                try self.stepSelection(1);
            }
            if (rl.isKeyPressed(.up)) {
                try self.stepSelection(-10);
            }
            if (rl.isKeyPressed(.down)) {
                try self.stepSelection(10);
            }
            if (rl.isKeyPressed(.v)) {
                self.segment_render_mode = switch (self.segment_render_mode) {
                    .game => .raw,
                    .raw => .game,
                };
            }
            if (rl.isKeyPressed(.o)) {
                self.segment_show_overlay = !self.segment_show_overlay;
            }
            if (rl.isKeyPressed(.g)) {
                self.segment_show_grid = !self.segment_show_grid;
            }
            if (rl.isKeyPressed(.a)) {
                self.segment_show_attachments = !self.segment_show_attachments;
            }
            if (rl.isKeyPressed(.t)) {
                self.segment_track_set_index = (self.segment_track_set_index + 1) % 4;
                try self.reloadStandaloneSegmentScene();
            }
        } else if (self.mode == .streaks) {
            self.handleDebugLightStreakInput();
        } else {
            if (rl.isKeyPressed(.left)) {
                try self.stepSelection(-1);
            }
            if (rl.isKeyPressed(.right)) {
                try self.stepSelection(1);
            }
            if (rl.isKeyPressed(.up)) {
                try self.stepSelection(-10);
            }
            if (rl.isKeyPressed(.down)) {
                try self.stepSelection(10);
            }
        }

        if (self.mode == .audio and self.audio_ready) {
            if (rl.isKeyPressed(.space)) {
                try self.previewSound();
            }
            if (rl.isKeyPressed(.enter)) {
                try self.previewMusic();
            }
            if (rl.isKeyPressed(.s)) {
                self.stopAudioPreview();
            }
        }

        if (self.mode == .models and rl.isKeyPressed(.f)) {
            self.model_flip_v = !self.model_flip_v;
            try self.reloadModel();
        }
        if (self.mode == .models and rl.isKeyPressed(.r)) {
            if (self.current_animation) |*animation| {
                try animation.restart();
            }
        }
        if (self.mode == .models and rl.isKeyPressed(.p)) {
            if (self.current_animation) |*animation| {
                animation.togglePause();
            }
        }
        if (self.mode == .objects and rl.isKeyPressed(.f)) {
            self.object_flip_v = !self.object_flip_v;
            try self.reloadObject();
        }
    }

    fn currentUiLayout(self: *const AppState) VirtualLayout {
        _ = self;
        return app_ui.virtualLayout(.{
            .x = 0.0,
            .y = 0.0,
            .width = @floatFromInt(screenWidth()),
            .height = @floatFromInt(screenHeight()),
        });
    }

    fn currentFrontendMouseLocal(self: *const AppState) ?rl.Vector2 {
        return self.currentUiMouseLocal();
    }

    fn currentUiMouseLocal(self: *const AppState) ?rl.Vector2 {
        if (self.mouse_local_override) |mouse| {
            return .{ .x = mouse.x, .y = mouse.y };
        }
        const layout = self.currentUiLayout();
        const mouse_x = @as(f32, @floatFromInt(rl.getMouseX()));
        const mouse_y = @as(f32, @floatFromInt(rl.getMouseY()));
        if (!layout.containsScreenPoint(mouse_x, mouse_y)) return null;
        return layout.unmapPoint(mouse_x, mouse_y);
    }

    fn setFrontendHoverTarget(self: *AppState, target: ?FrontendHoverTarget) void {
        if (self.hovered_frontend_target == target) return;
        self.hovered_frontend_target = target;
        if (target != null) {
            self.keyboard_frontend_focus_visible = false;
            self.playFrontendHoverSound();
        }
    }

    fn noteFrontendKeyboardNavigation(self: *AppState) void {
        self.keyboard_frontend_focus_visible = true;
    }

    fn activeFrontendButtonTarget(self: *const AppState) ?FrontendHoverTarget {
        if (self.pending_frontend_activation) |pending| {
            return pending.target;
        }
        return self.hovered_frontend_target;
    }

    fn frontendButtonHot(self: *const AppState, target: FrontendHoverTarget, fallback_selected: bool) bool {
        if (self.activeFrontendButtonTarget()) |active_target| {
            return active_target == target;
        }
        return self.keyboard_frontend_focus_visible and fallback_selected;
    }

    fn queueFrontendActivation(self: *AppState, action: FrontendQueuedAction) void {
        if (self.pending_frontend_activation != null) return;
        self.playFrontendSelectSound();
        const requires_fade = queuedActivationRequiresFade(action);
        if (requires_fade) {
            self.frontend_transition.beginOverlayFadeOut();
        }
        self.pending_frontend_activation = .{
            .action = action,
            .target = queuedActivationTarget(action),
            .requires_fade = requires_fade,
        };
    }

    fn dispatchFrontendActivation(self: *AppState, action: FrontendQueuedAction) !void {
        switch (action) {
            .main_menu => |item| try self.performMainMenuItem(item),
            .new_game_menu => |item| try self.performNewGameMenuItem(item),
            .options_menu => |item| try self.performOptionsMenuItem(item),
            .pause_menu => |item| try self.performPauseMenuItem(item),
            .route_map_menu => |item| try self.performRouteMenuAction(item),
            .help_menu => |item| try self.performHelpMenuItem(item),
            .high_scores_menu => |item| try self.performHighScoreMenuAction(item),
            .high_score_replay => |index| try self.performHighScoreReplay(index),
            .post_level_high_scores => |item| try self.performPostLevelHighScoreAction(item),
            .completion_screen => |item| try self.performCompletionAction(item),
            .exit_prompt => |choice| try self.performExitPromptChoice(choice),
        }
    }

    fn updatePendingFrontendActivation(self: *AppState) !bool {
        if (self.pending_frontend_activation) |*pending| {
            pending.progress = @min(pending.progress + frontend_activation_delay_step, 1.0);
            const fade_ready = !pending.requires_fade or self.frontend_transition.state == .black_idle;
            if (pending.progress >= 0.999 and fade_ready) {
                const action = pending.action;
                const should_fade_in = pending.requires_fade and self.frontend_transition.state == .black_idle;
                self.pending_frontend_activation = null;
                try self.dispatchFrontendActivation(action);
                if (should_fade_in) {
                    self.frontend_transition.completeHandoff();
                }
                return true;
            }
        }
        return false;
    }

    fn playFrontendHoverSound(self: *AppState) void {
        if (!self.audio_ready) return;
        if (self.frontend_sound_fx.highlight) |sound| {
            rl.stopSound(sound.sound);
            rl.playSound(sound.sound);
        }
    }

    fn playFrontendSelectSound(self: *AppState) void {
        if (!self.audio_ready) return;
        if (self.frontend_sound_fx.select) |sound| {
            rl.stopSound(sound.sound);
            rl.playSound(sound.sound);
        }
    }

    fn readPressedFrontendWidgetShortcutCode(_: *const AppState) ?u8 {
        // PORT(partial): this currently implements only the native text-input codes that
        // recovered widget shortcuts actually use in the shipped front-end: Escape (`11`),
        // Enter (`5` / `6`), and lowercase `o` (`111`).
        if (rl.isKeyPressed(.escape)) return 11;
        if (rl.isKeyPressed(.enter)) {
            return if (rl.isKeyDown(.left_control) or rl.isKeyDown(.right_control)) 6 else 5;
        }
        if (rl.isKeyPressed(.o)) return 111;
        return null;
    }

    fn frontendShortcutActivationForCode(self: *const AppState, code: u8) ?FrontendQueuedAction {
        return switch (self.game_phase) {
            .pause_menu => switch (code) {
                11 => .{ .pause_menu = .end_game },
                111 => .{ .pause_menu = .options },
                5, 6 => .{ .pause_menu = .@"resume" },
                else => null,
            },
            .high_scores_menu => if (self.postLevelHighScoreContext() != null) switch (code) {
                11 => .{ .post_level_high_scores = .cancel },
                5, 6 => .{ .post_level_high_scores = .submit },
                else => null,
            } else null,
            else => null,
        };
    }

    fn handleFrontendWidgetShortcutInput(self: *AppState) !bool {
        if (self.frontend_transition.blocksInput()) return false;
        if (self.pending_frontend_activation != null) return false;
        const code = self.readPressedFrontendWidgetShortcutCode() orelse return false;
        const action = self.frontendShortcutActivationForCode(code) orelse return false;
        self.noteFrontendKeyboardNavigation();
        self.queueFrontendActivation(action);
        return true;
    }

    fn updateFrontendWidgetAnimations(self: *AppState) void {
        const main_menu_active = self.game_phase == .main_menu and !self.frontend_transition.blocksInput();
        for (&self.main_menu_button_states, 0..) |*state, index| {
            state.stepFor(.menu_button, main_menu_active and self.frontendButtonHot(hoverTargetForMainMenu(index), self.menu_index == index));
        }

        const new_game_active = self.game_phase == .new_game_menu and !self.frontend_transition.blocksInput();
        for (&self.new_game_button_states, 0..) |*state, index| {
            state.stepFor(.menu_button, new_game_active and self.frontendButtonHot(hoverTargetForNewGame(index), self.new_game_menu_index == index));
        }

        const options_active = self.game_phase == .options_menu and !self.frontend_transition.blocksInput();
        for (&self.options_button_states, 0..) |*state, index| {
            const item = options_menu_items[index];
            const hot = switch (item) {
                .sound_volume, .music_volume => blk: {
                    const active_target = self.activeFrontendButtonTarget();
                    break :blk options_active and ((active_target != null and sliderHoverTargetBelongsToOptionsRow(active_target.?, item)) or (self.keyboard_frontend_focus_visible and self.options_menu_index == index));
                },
                else => options_active and self.frontendButtonHot(hoverTargetForOptions(index), self.options_menu_index == index),
            };
            state.stepFor(.menu_button, hot);
        }
        self.options_sound_display_value = stepOptionsSliderDisplay(self.options_sound_display_value, self.runtime_config.soundVolume());
        self.options_music_display_value = stepOptionsSliderDisplay(self.options_music_display_value, self.runtime_config.musicVolume());
        const pause_menu_active = self.game_phase == .pause_menu and !self.frontend_transition.blocksInput();
        for (&self.pause_menu_button_states, 0..) |*state, index| {
            state.stepFor(.menu_button, pause_menu_active and self.frontendButtonHot(hoverTargetForPauseMenu(index), self.pause_menu_index == index));
        }
        const route_map_active = self.game_phase == .route_map_menu and !self.frontend_transition.blocksInput();
        const route_map_card_open = self.routeMapCardIsOpen();
        self.route_map_button_states[route_map_primary_button_index].stepFor(
            .menu_button,
            route_map_active and route_map_card_open and self.frontendButtonHot(hoverTargetForRouteMenuAction(.play), self.activeRouteMenuHotAction() == .play),
        );
        self.route_map_button_states[route_map_replay_button_index].stepFor(
            .route_map_secondary_action,
            route_map_active and route_map_card_open and self.routeMapShowsReplay() and self.frontendButtonHot(hoverTargetForRouteMenuAction(.watch_best_trial), self.activeRouteMenuHotAction() == .watch_best_trial),
        );
        self.route_map_button_states[route_map_back_button_index].stepFor(
            .menu_button,
            route_map_active and self.frontendButtonHot(hoverTargetForRouteMenuAction(.back), self.activeRouteMenuHotAction() == .back),
        );
        const help_active = self.game_phase == .help and !self.frontend_transition.blocksInput();
        self.help_button_states[0].stepFor(.menu_button, help_active and self.frontendButtonHot(.help_back, true));

        const high_scores_active = self.game_phase == .high_scores_menu and !self.frontend_transition.blocksInput();
        for (&self.high_score_button_states, 0..) |*state, index| {
            state.stepFor(.footer_button, high_scores_active and self.postLevelHighScoreContext() == null and self.frontendButtonHot(hoverTargetForHighScores(index), self.high_scores_action_index == index));
        }
        for (&self.high_score_replay_button_states, 0..) |*state, index| {
            state.stepFor(
                .compact_score_row,
                high_scores_active and self.postLevelHighScoreContext() == null and self.highScoreReplayAvailable(index) and self.frontendButtonHot(hoverTargetForHighScoreReplay(index), false),
            );
        }
        for (&self.post_level_high_score_button_states, 0..) |*state, index| {
            state.stepFor(.footer_button, high_scores_active and self.postLevelHighScoreContext() != null and self.frontendButtonHot(hoverTargetForPostLevelHighScores(index), self.post_level_high_score_action_index == index));
        }
        const completion_active = self.completionScreenInteractive();
        self.completion_continue_button_state.stepFor(
            .menu_button,
            completion_active and self.completionContinueVisible() and self.frontendButtonHot(.completion_continue, true),
        );

        const exit_prompt_active = self.game_phase == .exit_prompt and !self.frontend_transition.blocksInput();
        for (&self.exit_prompt_button_states, 0..) |*state, index| {
            state.stepFor(.menu_button, exit_prompt_active and self.frontendButtonHot(hoverTargetForExitPrompt(index), self.exit_prompt_choice_index == index));
        }
    }

    fn snapFrontendWidgetStates(self: *AppState) void {
        for (&self.main_menu_button_states, 0..) |*state, index| {
            state.snapFor(.menu_button, self.game_phase == .main_menu and self.frontendButtonHot(hoverTargetForMainMenu(index), self.menu_index == index));
        }
        for (&self.new_game_button_states, 0..) |*state, index| {
            state.snapFor(.menu_button, self.game_phase == .new_game_menu and self.frontendButtonHot(hoverTargetForNewGame(index), self.new_game_menu_index == index));
        }
        for (&self.options_button_states, 0..) |*state, index| {
            const item = options_menu_items[index];
            const hot = switch (item) {
                .sound_volume, .music_volume => blk: {
                    const active_target = self.activeFrontendButtonTarget();
                    break :blk self.game_phase == .options_menu and ((active_target != null and sliderHoverTargetBelongsToOptionsRow(active_target.?, item)) or (self.keyboard_frontend_focus_visible and self.options_menu_index == index));
                },
                else => self.game_phase == .options_menu and self.frontendButtonHot(hoverTargetForOptions(index), self.options_menu_index == index),
            };
            state.snapFor(.menu_button, hot);
        }
        for (&self.pause_menu_button_states, 0..) |*state, index| {
            state.snapFor(.menu_button, self.game_phase == .pause_menu and self.frontendButtonHot(hoverTargetForPauseMenu(index), self.pause_menu_index == index));
        }
        const route_map_card_open = self.routeMapCardIsOpen();
        self.route_map_button_states[route_map_primary_button_index].snapFor(
            .menu_button,
            self.game_phase == .route_map_menu and route_map_card_open and self.frontendButtonHot(hoverTargetForRouteMenuAction(.play), self.activeRouteMenuHotAction() == .play),
        );
        self.route_map_button_states[route_map_replay_button_index].snapFor(
            .route_map_secondary_action,
            self.game_phase == .route_map_menu and route_map_card_open and self.routeMapShowsReplay() and self.frontendButtonHot(hoverTargetForRouteMenuAction(.watch_best_trial), self.activeRouteMenuHotAction() == .watch_best_trial),
        );
        self.route_map_button_states[route_map_back_button_index].snapFor(
            .menu_button,
            self.game_phase == .route_map_menu and self.frontendButtonHot(hoverTargetForRouteMenuAction(.back), self.activeRouteMenuHotAction() == .back),
        );
        self.help_button_states[0].snapFor(.menu_button, self.game_phase == .help and self.frontendButtonHot(.help_back, true));
        for (&self.high_score_button_states, 0..) |*state, index| {
            state.snapFor(.footer_button, self.game_phase == .high_scores_menu and self.postLevelHighScoreContext() == null and self.frontendButtonHot(hoverTargetForHighScores(index), self.high_scores_action_index == index));
        }
        for (&self.high_score_replay_button_states, 0..) |*state, index| {
            state.snapFor(
                .compact_score_row,
                self.game_phase == .high_scores_menu and self.postLevelHighScoreContext() == null and self.highScoreReplayAvailable(index) and self.frontendButtonHot(hoverTargetForHighScoreReplay(index), false),
            );
        }
        for (&self.post_level_high_score_button_states, 0..) |*state, index| {
            state.snapFor(.footer_button, self.game_phase == .high_scores_menu and self.postLevelHighScoreContext() != null and self.frontendButtonHot(hoverTargetForPostLevelHighScores(index), self.post_level_high_score_action_index == index));
        }
        self.completion_continue_button_state.snapFor(
            .menu_button,
            self.completionScreenInteractive() and self.completionContinueVisible() and self.frontendButtonHot(.completion_continue, true),
        );
        for (&self.exit_prompt_button_states, 0..) |*state, index| {
            state.snapFor(.menu_button, self.game_phase == .exit_prompt and self.frontendButtonHot(hoverTargetForExitPrompt(index), self.exit_prompt_choice_index == index));
        }
    }

    fn updateMainMenuMouseSelection(self: *AppState) !void {
        const local_mouse = self.currentFrontendMouseLocal() orelse {
            self.setFrontendHoverTarget(null);
            return;
        };
        var hovered_index: ?usize = null;

        for (main_menu_items, 0..) |item, index| {
            const text_rect = mainMenuTextRect(&self.ui_font, item);
            if (frontend_widget.hitRect(text_rect, self.main_menu_button_states[index]).contains(local_mouse)) {
                hovered_index = index;
            }
        }

        if (hovered_index) |index| {
            self.setFrontendHoverTarget(hoverTargetForMainMenu(index));
            self.menu_index = index;
            if (rl.isMouseButtonPressed(.left)) {
                self.queueFrontendActivation(.{ .main_menu = main_menu_items[index] });
            }
        } else {
            self.setFrontendHoverTarget(null);
        }
    }

    fn updateNewGameMenuMouseSelection(self: *AppState) !void {
        const local_mouse = self.currentFrontendMouseLocal() orelse {
            self.setFrontendHoverTarget(null);
            return;
        };
        var hovered_index: ?usize = null;

        for (new_game_menu_items[0..4], 0..) |item, index| {
            const text_rect = newGameMenuTextRect(&self.ui_font, item);
            if (frontend_widget.hitRect(text_rect, self.new_game_button_states[index]).contains(local_mouse)) {
                hovered_index = index;
            }
        }

        const help_rect = newGameHelpTextRect(&self.ui_font);
        if (frontend_widget.hitRect(help_rect, self.new_game_button_states[4]).contains(local_mouse)) {
            hovered_index = 4;
        }

        const back_rect = newGameBackTextRect(&self.ui_font);
        if (frontend_widget.hitRect(back_rect, self.new_game_button_states[5]).contains(local_mouse)) {
            hovered_index = 5;
        }

        if (hovered_index) |index| {
            self.setFrontendHoverTarget(hoverTargetForNewGame(index));
            self.new_game_menu_index = index;
            if (rl.isMouseButtonPressed(.left)) {
                self.queueFrontendActivation(.{ .new_game_menu = new_game_menu_items[index] });
            }
        } else {
            self.setFrontendHoverTarget(null);
        }
    }

    fn updateOptionsMouseSelection(self: *AppState) !void {
        const local_mouse = self.currentFrontendMouseLocal() orelse {
            self.setFrontendHoverTarget(null);
            return;
        };

        const fullscreen_rect = optionsTextRect(self, .fullscreen);
        if (frontend_widget.hitRect(fullscreen_rect, self.options_button_states[options_fullscreen_button_index]).contains(local_mouse)) {
            self.setFrontendHoverTarget(hoverTargetForOptions(0));
            self.options_menu_index = 0;
            if (rl.isMouseButtonPressed(.left)) {
                self.queueFrontendActivation(.{ .options_menu = .fullscreen });
            }
            return;
        }

        const sound_slider = optionsSliderLayout(self, .sound_volume);
        if (sound_slider.less_rect.contains(local_mouse)) {
            self.setFrontendHoverTarget(hoverTargetForOptionsSliderArrow(.sound_volume, .less));
            self.options_menu_index = 1;
            if (rl.isMouseButtonPressed(.left)) {
                try self.stepOptionsMenuValue(.sound_volume, -options_slider_adjust_step);
            }
            return;
        }
        if (sound_slider.more_rect.contains(local_mouse)) {
            self.setFrontendHoverTarget(hoverTargetForOptionsSliderArrow(.sound_volume, .more));
            self.options_menu_index = 1;
            if (rl.isMouseButtonPressed(.left)) {
                try self.stepOptionsMenuValue(.sound_volume, options_slider_adjust_step);
            }
            return;
        }
        if (sound_slider.frame_rect.contains(local_mouse)) {
            self.setFrontendHoverTarget(hoverTargetForOptions(1));
            self.options_menu_index = 1;
            return;
        }

        const music_slider = optionsSliderLayout(self, .music_volume);
        if (music_slider.less_rect.contains(local_mouse)) {
            self.setFrontendHoverTarget(hoverTargetForOptionsSliderArrow(.music_volume, .less));
            self.options_menu_index = 2;
            if (rl.isMouseButtonPressed(.left)) {
                try self.stepOptionsMenuValue(.music_volume, -options_slider_adjust_step);
            }
            return;
        }
        if (music_slider.more_rect.contains(local_mouse)) {
            self.setFrontendHoverTarget(hoverTargetForOptionsSliderArrow(.music_volume, .more));
            self.options_menu_index = 2;
            if (rl.isMouseButtonPressed(.left)) {
                try self.stepOptionsMenuValue(.music_volume, options_slider_adjust_step);
            }
            return;
        }
        if (music_slider.frame_rect.contains(local_mouse)) {
            self.setFrontendHoverTarget(hoverTargetForOptions(2));
            self.options_menu_index = 2;
            return;
        }

        const back_rect = optionsTextRect(self, .back);
        if (frontend_widget.hitRect(back_rect, self.options_button_states[options_back_button_index]).contains(local_mouse)) {
            self.setFrontendHoverTarget(hoverTargetForOptions(3));
            self.options_menu_index = 3;
            if (rl.isMouseButtonPressed(.left)) {
                self.queueFrontendActivation(.{ .options_menu = .back });
            }
            return;
        }

        self.setFrontendHoverTarget(null);
    }

    fn updatePauseMenuMouseSelection(self: *AppState) void {
        const local_mouse = self.currentFrontendMouseLocal() orelse {
            self.setFrontendHoverTarget(null);
            return;
        };
        var hovered_index: ?usize = null;

        for (pause_menu_items, 0..) |item, index| {
            const text_rect = pauseMenuTextRect(&self.ui_font, item);
            if (frontend_widget.hitRect(text_rect, self.pause_menu_button_states[index]).contains(local_mouse)) {
                hovered_index = index;
            }
        }

        if (hovered_index) |index| {
            self.setFrontendHoverTarget(hoverTargetForPauseMenu(index));
            self.pause_menu_index = index;
            if (rl.isMouseButtonPressed(.left)) {
                self.queueFrontendActivation(.{ .pause_menu = pause_menu_items[index] });
            }
        } else {
            self.setFrontendHoverTarget(null);
        }
    }

    fn updateRouteMapMouseSelection(self: *AppState) !void {
        const local_mouse = self.currentFrontendMouseLocal() orelse {
            self.route_map_hover_state = .none;
            self.route_map_hovered_index = null;
            self.setFrontendHoverTarget(null);
            return;
        };
        const mode = self.frontend_route_mode orelse {
            self.route_map_hover_state = .none;
            self.route_map_hovered_index = null;
            self.setFrontendHoverTarget(null);
            return;
        };

        const back_rect = routeMapBackTextRect(self);
        if (frontend_widget.hitRect(back_rect, self.route_map_button_states[route_map_back_button_index]).contains(local_mouse)) {
            self.route_map_hover_state = .none;
            self.route_map_hovered_index = null;
            self.setFrontendHoverTarget(hoverTargetForRouteMenuAction(.back));
            if (self.routeMenuActionIndexForAction(.back)) |index| {
                self.route_menu_action_index = index;
            }
            if (rl.isMouseButtonPressed(.left)) {
                self.queueFrontendActivation(.{ .route_map_menu = .back });
            }
            return;
        }

        const hovered_route_index = if (routeMapAllowsRouteSwitching(self.route_map_screen_mode))
            routeMapHoveredRouteIndex(self, local_mouse, self.availableFrontendRouteLimit(mode))
        else
            null;
        self.route_map_hover_state = if (hovered_route_index != null) .route else .none;
        self.route_map_hovered_index = hovered_route_index;

        if (self.currentRouteMapOpenIndex()) |route_index| {
            const route_galaxy_name = self.currentFrontendGalaxyName() orelse frontendRouteModeLabel(mode);
            const route_level_name = if (self.frontend_route_level) |loaded_level| loaded_level.name else "Route";
            const route_body = routeMapBodyText(if (self.frontend_route_level) |loaded_level| loaded_level.galaxy_text else null);
            if (routeMapPointForRouteIndex(self, route_index)) |route_point| {
                const card_layout = routeMapCardLayout(
                    &self.ui_font,
                    route_point,
                    route_galaxy_name,
                    route_level_name,
                    route_body,
                    routeMenuActionLabel(mode, .play),
                    if (self.routeMapShowsReplay()) routeMenuActionLabel(mode, .watch_best_trial) else null,
                );

                if (frontend_widget.hitRect(card_layout.primary_text_rect, self.route_map_button_states[route_map_primary_button_index]).contains(local_mouse)) {
                    self.route_map_hover_state = .card;
                    self.route_map_hovered_index = null;
                    self.setFrontendHoverTarget(hoverTargetForRouteMenuAction(.play));
                    if (self.routeMenuActionIndexForAction(.play)) |index| {
                        self.route_menu_action_index = index;
                    }
                    if (rl.isMouseButtonPressed(.left)) {
                        self.queueFrontendActivation(.{ .route_map_menu = .play });
                    }
                    return;
                }

                if (card_layout.replay_text_rect) |replay_rect| {
                    if (frontend_widget.hitRect(replay_rect, self.route_map_button_states[route_map_replay_button_index]).contains(local_mouse)) {
                        self.route_map_hover_state = .card;
                        self.route_map_hovered_index = null;
                        self.setFrontendHoverTarget(hoverTargetForRouteMenuAction(.watch_best_trial));
                        if (self.routeMenuActionIndexForAction(.watch_best_trial)) |index| {
                            self.route_menu_action_index = index;
                        }
                        if (rl.isMouseButtonPressed(.left)) {
                            self.queueFrontendActivation(.{ .route_map_menu = .watch_best_trial });
                        }
                        return;
                    }
                }

                if (card_layout.card_rect.contains(local_mouse)) {
                    self.route_map_hover_state = .card;
                    self.route_map_hovered_index = null;
                    self.setFrontendHoverTarget(null);
                    return;
                }
            }
        }

        if (hovered_route_index) |route_index| {
            self.setFrontendHoverTarget(null);
            if (rl.isMouseButtonPressed(.left) and self.currentRouteMapOpenIndex() != route_index) {
                try self.openFrontendRouteCard(route_index);
                self.playFrontendSelectSound();
            }
            return;
        }

        if (self.routeMapCanCloseCard() and rl.isMouseButtonPressed(.left)) {
            self.closeFrontendRouteCard();
            self.playFrontendSelectSound();
            self.setFrontendHoverTarget(null);
            return;
        }

        self.setFrontendHoverTarget(null);
    }

    fn updateHelpMouseSelection(self: *AppState) void {
        const local_mouse = self.currentFrontendMouseLocal() orelse {
            self.setFrontendHoverTarget(null);
            return;
        };

        const back_rect = helpBackTextRect(&self.ui_font);
        if (frontend_widget.hitRect(back_rect, self.help_button_states[0]).contains(local_mouse)) {
            self.setFrontendHoverTarget(.help_back);
            if (rl.isMouseButtonPressed(.left)) {
                self.queueFrontendActivation(.{ .help_menu = .back });
            }
            return;
        }

        self.setFrontendHoverTarget(null);
    }

    fn highScoreReplayAvailable(self: *const AppState, entry_index: usize) bool {
        const selected_mode = high_score_screen_modes[@min(self.high_scores_menu_index, high_score_screen_modes.len - 1)];
        if (!highScoreRowsShowReplay(selected_mode, self.postLevelHighScoreContext() != null)) return false;
        const entries = self.high_score_tables.visibleEntries(selected_mode);
        return entry_index < entries.len and entries[entry_index].has_replay;
    }

    fn updateHighScoresMouseSelection(self: *AppState) !void {
        const local_mouse = self.currentFrontendMouseLocal() orelse {
            self.setFrontendHoverTarget(null);
            return;
        };

        if (self.postLevelHighScoreContext() != null) {
            const cancel_rect = highScoreFooterTextRect(self, post_level_high_score_actions[0].label(), high_score_entry_cancel_x);
            if (frontend_widget.hitRect(cancel_rect, self.post_level_high_score_button_states[0]).contains(local_mouse)) {
                self.setFrontendHoverTarget(hoverTargetForPostLevelHighScores(0));
                self.post_level_high_score_action_index = 0;
                if (rl.isMouseButtonPressed(.left)) {
                    self.queueFrontendActivation(.{ .post_level_high_scores = .cancel });
                }
                return;
            }

            const submit_rect = highScoreFooterTextRect(self, post_level_high_score_actions[1].label(), high_score_entry_submit_x);
            if (frontend_widget.hitRect(submit_rect, self.post_level_high_score_button_states[1]).contains(local_mouse)) {
                self.setFrontendHoverTarget(hoverTargetForPostLevelHighScores(1));
                self.post_level_high_score_action_index = 1;
                if (rl.isMouseButtonPressed(.left)) {
                    self.queueFrontendActivation(.{ .post_level_high_scores = .submit });
                }
                return;
            }
        } else {
            const selected_mode = high_score_screen_modes[@min(self.high_scores_menu_index, high_score_screen_modes.len - 1)];
            const entries = self.high_score_tables.visibleEntries(selected_mode);
            if (highScoreRowsShowReplay(selected_mode, false)) {
                for (entries, 0..) |entry, entry_index| {
                    if (!entry.has_replay) continue;
                    const replay_rect = highScoreReplayTextRect(self, selected_mode, high_score_row_start_y + @as(f32, @floatFromInt(entry_index)) * high_score_row_pitch);
                    if (frontend_widget.hitRect(replay_rect, self.high_score_replay_button_states[entry_index]).contains(local_mouse)) {
                        self.setFrontendHoverTarget(hoverTargetForHighScoreReplay(entry_index));
                        if (rl.isMouseButtonPressed(.left)) {
                            self.queueFrontendActivation(.{ .high_score_replay = entry_index });
                        }
                        return;
                    }
                }
            }

            const back_rect = highScoreFooterTextRect(self, "Back", high_score_back_x);
            if (frontend_widget.hitRect(back_rect, self.high_score_button_states[0]).contains(local_mouse)) {
                self.setFrontendHoverTarget(hoverTargetForHighScores(0));
                self.high_scores_action_index = 0;
                if (rl.isMouseButtonPressed(.left)) {
                    self.queueFrontendActivation(.{ .high_scores_menu = .back });
                }
                return;
            }

            const toggle_rect = highScoreFooterTextRect(self, highScoreTableToggleLabel(high_score_screen_modes[@min(self.high_scores_menu_index, high_score_screen_modes.len - 1)]), high_score_toggle_x);
            if (frontend_widget.hitRect(toggle_rect, self.high_score_button_states[1]).contains(local_mouse)) {
                self.setFrontendHoverTarget(hoverTargetForHighScores(1));
                self.high_scores_action_index = 1;
                if (rl.isMouseButtonPressed(.left)) {
                    self.queueFrontendActivation(.{ .high_scores_menu = .switch_table });
                }
                return;
            }
        }

        self.setFrontendHoverTarget(null);
    }

    fn updateCompletionScreenMouseSelection(self: *AppState) void {
        const result = self.pending_run_result orelse {
            self.setFrontendHoverTarget(null);
            return;
        };
        if (!self.completionContinueVisible()) {
            self.setFrontendHoverTarget(null);
            return;
        }
        const local_mouse = self.currentFrontendMouseLocal() orelse {
            self.setFrontendHoverTarget(null);
            return;
        };
        const continue_rect = completionContinueTextRect(&self.ui_font, result);
        if (frontend_widget.hitRect(continue_rect, self.completion_continue_button_state).contains(local_mouse)) {
            self.setFrontendHoverTarget(.completion_continue);
            if (rl.isMouseButtonPressed(.left)) {
                self.queueFrontendActivation(.{ .completion_screen = .continue_flow });
            }
            return;
        }
        self.setFrontendHoverTarget(null);
    }

    fn updateExitPromptMouseSelection(self: *AppState) !void {
        const local_mouse = self.currentFrontendMouseLocal() orelse {
            self.setFrontendHoverTarget(null);
            return;
        };

        const yes_rect = exitPromptTextRect(self, exit_prompt_choices[0].label(), exit_prompt_yes_x);
        if (frontend_widget.hitRect(yes_rect, self.exit_prompt_button_states[0]).contains(local_mouse)) {
            self.setFrontendHoverTarget(hoverTargetForExitPrompt(0));
            self.exit_prompt_choice_index = 0;
            if (rl.isMouseButtonPressed(.left)) {
                self.queueFrontendActivation(.{ .exit_prompt = .yes });
            }
            return;
        }

        const no_rect = exitPromptTextRect(self, exit_prompt_choices[1].label(), exit_prompt_no_x);
        if (frontend_widget.hitRect(no_rect, self.exit_prompt_button_states[1]).contains(local_mouse)) {
            self.setFrontendHoverTarget(hoverTargetForExitPrompt(1));
            self.exit_prompt_choice_index = 1;
            if (rl.isMouseButtonPressed(.left)) {
                self.queueFrontendActivation(.{ .exit_prompt = .no });
            }
            return;
        }

        self.setFrontendHoverTarget(null);
    }

    fn simulateGameTick(self: *AppState, runner_input: gameplay.RunnerInput) !void {
        const effective_runner_input = if (self.completionScreenOverlayActive())
            gameplay.RunnerInput{}
        else
            runner_input;
        self.game_phase_ticks += 1;
        if (self.current_game_background_runtime) |*runtime| {
            runtime.update();
        }
        self.background_light_streaks.update(
            backgroundLightStreakCamera(self),
            backgroundLightStreaksVisible(self),
        );
        if (self.game_status_ticks > 0) {
            self.game_status_ticks -= 1;
            if (self.game_status_ticks == 0) {
                self.game_status_message = null;
            }
        }
        self.gameplay_voice_manager.tick();
        self.native_gameplay_voice_manager.tick();
        if (self.game_phase == .level and !self.frontend_transition.blocksInput()) {
            if (self.level_runner) |runner| {
                if (!runner.paused and !self.startupGameplayBlockActive()) {
                    self.level_prompt_queue.tick();
                }
                if (self.isTutorialGameplay() and runner.score.total > self.tutorial_reference_score) {
                    self.tutorial_reference_score = runner.score.total;
                }
            }
        }

        if (self.frontend_transition.update()) |next_phase| {
            try self.enterGamePhase(next_phase);
            self.frontend_transition.completeHandoff();
            return;
        }

        if (try self.updatePendingFrontendActivation()) {
            return;
        }

        self.updateFrontendWidgetAnimations();
        self.stepCompletionScreenReveal();
        if (self.game_phase == .thanks_screen) {
            self.thanks_screen_controller.step();
        }

        if (self.game_phase == .boot) {
            if (try self.advanceBootTask()) {
                try self.enterGamePhase(.intro);
                self.frontend_transition.beginFadeIn();
            }
            return;
        }

        if (self.game_phase == .intro or self.game_phase == .credits) {
            if (self.currentTextScriptDurationTicks()) |duration_ticks| {
                if (self.game_phase_ticks >= duration_ticks and !self.frontend_transition.blocksInput()) {
                    self.frontend_transition.beginFadeOut(.main_menu);
                }
            }
        }

        if (self.game_phase == .level) {
            if (try self.handleSelectedReplayFadeExit()) return;
            try self.syncGameplayTurboAnimation();
            if (self.current_track_preview) |*loaded_track_preview| {
                if (self.level_runner) |*runner| {
                    const previous_runner = runner.*;
                    const previous_active_level_segment_index = self.active_level_segment_index;
                    const startup_block_active = self.startupGameplayBlockActive();
                    if (!startup_block_active and !self.tutorialPromptBlocksGameplay()) {
                        runner.stepWithReplay(
                            loaded_track_preview,
                            effective_runner_input,
                            self.selectedReplayDirectiveForRunner(runner),
                            @floatCast(self.simulation_clock.step_seconds),
                        );
                        if (runner.consumeReplayFadeRequest()) {
                            self.selected_replay_fade_exit_pending = true;
                            if (self.frontend_transition.state == .idle) {
                                self.frontend_transition.beginOverlayFadeOut();
                            }
                            return;
                        }
                        self.updateGameplayRunnerPresentation(previous_runner, runner.*, effective_runner_input);
                        self.playGameplayRunnerAudio(previous_runner, runner.*, loaded_track_preview, effective_runner_input);
                        self.updateGameplayAmbientVoices(runner.*, loaded_track_preview);
                        self.spawnGameplayRunnerEffects(previous_runner, runner.*, loaded_track_preview);
                    } else {
                        self.refreshRunnerForStartupBlock(
                            runner,
                            loaded_track_preview,
                            @floatCast(self.simulation_clock.step_seconds),
                        );
                    }
                    self.updateSubgameCamera(runner);
                    try self.syncActiveLevelSegment();
                    try self.dispatchCurrentRunnerRowMessage(
                        previous_active_level_segment_index,
                        previous_runner.currentRowMessageToken(),
                        false,
                    );
                }
            }
            self.updateGameplayEffects();
            if (self.current_gameplay_turbo_animation) |*animation| {
                try animation.step(self.simulation_clock.step_seconds);
            }
            if (self.level_runner) |*runner| {
                switch (runner.consumeHandoff()) {
                    .none => {},
                    .completion_screen_init => {
                        self.playGameplayEffect(self.current_gameplay_sound_fx.completion_init);
                        try self.beginCompletedRunOverlay();
                        return;
                    },
                    .completion_finalize => {
                        try self.finalizeCompletedRunScreen();
                        return;
                    },
                    .respawn => {
                        try self.beginRespawnRun();
                        return;
                    },
                    .final_loss => |cause| {
                        try self.beginFailedRun(cause);
                        return;
                    },
                }
            }
        }
    }

    fn playGameplayRunnerAudio(
        self: *AppState,
        previous: gameplay.Runner,
        current: gameplay.Runner,
        preview: *const track.LoadedLevelPreview,
        _: gameplay.RunnerInput,
    ) void {
        if (!self.audio_ready) return;
        const native_sound_cues = nativeGameplaySoundCues(previous, current);
        const native_jetpack_sound_cues = nativeJetpackSoundCues(previous, current);
        const native_voice_cues = nativeGameplayVoiceCues(previous, current, preview.runtime_build_flags);

        if (native_sound_cues.completion_arm_cheers) {
            self.playGameplayEffect(self.current_gameplay_sound_fx.cheers);
        }
        if (native_sound_cues.extra_life) {
            self.playGameplayEffect(self.current_gameplay_sound_fx.extra_life);
        }
        if (native_sound_cues.trampoline_bounce) {
            self.playGameplayEffect(self.current_gameplay_sound_fx.boing);
        }
        if (native_sound_cues.wall_barrier_hit) {
            self.playGameplayEffect(self.current_gameplay_sound_fx.wall_hit);
        }
        if (native_sound_cues.parcel_pickup) {
            self.playGameplayEffect(self.current_gameplay_sound_fx.place_package);
        }
        if (native_sound_cues.parcel_delivery) {
            self.playGameplayEffect(self.current_gameplay_sound_fx.package_count);
        }
        if (native_sound_cues.parcel_bonus) {
            self.playGameplayEffect(self.current_gameplay_sound_fx.perfect);
        }
        if (native_sound_cues.row_event_confirm) {
            self.playGameplayEffect(self.current_gameplay_sound_fx.row_event_confirm);
        }
        if (native_jetpack_sound_cues.activate) {
            self.playGameplayEffect(self.current_gameplay_sound_fx.jetpack);
        }
        if (native_jetpack_sound_cues.deactivate) {
            self.playGameplayEffect(self.current_gameplay_sound_fx.jetpack_shutoff);
        }
        if (nativeRingPickupSoundIndex(previous, current)) |sound_index| {
            self.playGameplayEffect(self.current_gameplay_sound_fx.powerup_pickup[sound_index]);
        }
        if (native_voice_cues.start) {
            self.tryPlayNativeGameplayVoiceSet(.start, .interrupt_current) catch {};
        }
        if (native_voice_cues.package_pickup) {
            self.tryPlayNativeGameplayVoiceSet(.package, .wait_for_frequency) catch {};
        }
        if (native_voice_cues.weapon_upgrade) {
            self.tryPlayNativeGameplayVoiceSet(.powerup, .wait_for_frequency) catch {};
        }
        if (native_voice_cues.damage_entry) {
            const played_damage = self.tryPlayNativeGameplayVoiceSetPlayed(.damage, .wait_for_frequency) catch false;
            if (!played_damage) {
                self.tryPlayNativeGameplayVoiceSet(.ouch, .wait_for_idle) catch {};
            }
        }
        if (native_voice_cues.damage_escalation) {
            self.tryPlayNativeGameplayVoiceSet(.postal, .wait_for_idle) catch {};
        }
        if (nativeGameplaySlowVoiceBandActive(previous, current)) {
            self.native_gameplay_slow_voice_progress += native_gameplay_slow_voice_timer_step;
            if (self.native_gameplay_slow_voice_progress > 1.0) {
                self.native_gameplay_slow_voice_progress = 0.0;
                self.tryPlayNativeGameplayVoiceSet(.slow, .wait_for_frequency) catch {};
            }
        } else {
            self.native_gameplay_slow_voice_progress = 0.0;
        }
        const death_cutscene_voice_cues = nativeDeathCutsceneVoiceCues(previous, current);
        if (death_cutscene_voice_cues.entry) {
            self.tryPlayNativeGameplayVoiceSet(.fall, .interrupt_current) catch {};
        }
        if (death_cutscene_voice_cues.fallback) {
            self.tryPlayNativeGameplayVoiceSet(.slugged, .interrupt_current) catch {};
        }

        const previous_attachment_runtime_kind = previous.currentAttachmentRuntimeKind(preview);
        if (!previous.attachment_follow.active and current.attachment_follow.active and
            current.movement_mode == .attachment)
        {
            if (current.currentAttachmentRuntimeKind(preview)) |runtime_kind| {
                if (runtime_kind == 24) {
                    self.tryPlayNativeGameplayVoiceSet(.worm_tunnel, .wait_for_idle) catch {};
                }
            }
        }
        if (nativeGameplaySupertrampExitVoice(current, previous_attachment_runtime_kind)) {
            self.tryPlayNativeGameplayVoiceSet(.supertramp, .wait_for_idle) catch {};
        }
        if (!previous.completion_handoff_voice_gate and current.completion_handoff_voice_gate) {
            self.tryPlayNativeGameplayVoiceSet(.victory, .interrupt_current) catch {};
        }
        if (!previous.attachment_exit_gate_a and current.attachment_exit_gate_a) {
            self.tryPlayNativeGameplayVoiceSet(.fall, .wait_for_idle) catch {};
        }
        if (!previous.attachment_exit_gate_b and current.attachment_exit_gate_b) {
            self.tryPlayNativeGameplayVoiceSet(.dying, .interrupt_current) catch {};
        }

        if (nativeGameplayWarningLoopTriggered(previous, current)) {
            self.playGameplayEffect(self.current_gameplay_sound_fx.postal_warning);
        }

        if (previous.shot_cooldown_ticks == 0 and current.shot_cooldown_ticks > 0) {
            const fired_sound = switch (nativeMovementStateSoundFamily(current)) {
                .turbo => self.pickNativeMovementStateSoundVariant(
                    gameplay_turbo_fire_sound_paths.len,
                    self.current_gameplay_sound_fx.turbo_fire,
                ),
                .laser => self.pickNativeMovementStateSoundVariant(
                    gameplay_laser_sound_paths.len,
                    self.current_gameplay_sound_fx.laser,
                ),
                .rocket => self.pickNativeMovementStateSoundVariant(
                    gameplay_rocket_sound_paths.len,
                    self.current_gameplay_sound_fx.rocket,
                ),
            };
            if (nativeMovementStateAttachmentExitGain(
                cameraWorldTransformFromMatrix(self.subgame_camera.shared_matrix).position,
                current.worldPosition(preview, 0.0),
                current.attachment_exit_pending,
            )) |gain| {
                self.playGameplayEffectScaled(fired_sound, gain);
            } else {
                self.playGameplayEffect(fired_sound);
            }
        }
        if (countGameplayProjectiles(previous, .enemy_laser) < countGameplayProjectiles(current, .enemy_laser)) {
            self.playGameplayEffect(self.current_gameplay_sound_fx.enemy_fire);
        }
        if (nativeWeaponPresentationChanged(previous, current)) {
            self.playGameplayEffect(self.current_gameplay_sound_fx.weapon_change);
        }
        if (current.counters.health_pickups > previous.counters.health_pickups) {
            self.playGameplayEffect(self.current_gameplay_sound_fx.heart);
        }
        if (current.invincible_ticks > previous.invincible_ticks) {
            self.playGameplayEffect(self.current_gameplay_sound_fx.invincible);
        }
        if (nativeSlowRingSoundTriggered(previous, current)) {
            self.playGameplayEffect(self.current_gameplay_sound_fx.slow_ring);
        }
        if (nativeExplodeRingSoundTriggered(previous, current)) {
            self.playGameplayEffect(self.current_gameplay_sound_fx.explode_ring);
        }
        if (current.counters.garbage_hits > previous.counters.garbage_hits) {
            self.playGameplayEffect(self.pickGameplaySoundVariant(
                gameplay_asteroid_impact_sound_paths.len,
                self.current_gameplay_sound_fx.asteroid_impact,
            ));
        }
        if (current.counters.salt_hits > previous.counters.salt_hits) {
            self.playGameplayEffect(self.pickGameplaySoundVariant(
                gameplay_asteroid_impact_sound_paths.len,
                self.current_gameplay_sound_fx.asteroid_impact,
            ));
        }
        if (current.counters.turret_hits > previous.counters.turret_hits) {
            self.playGameplayEffect(self.current_gameplay_sound_fx.wall_hit);
        }
        if (current.counters.slug_hits > previous.counters.slug_hits) {
            self.tryPlayGameplayVoiceVariant(
                gameplay_slug_hit_voice_paths.len,
                gameplay_slug_hit_voice_paths,
            ) catch {};
        }
        if (current.defeated_slug_cell_count > previous.defeated_slug_cell_count) {
            self.playGameplayEffect(self.pickGameplaySoundVariant(
                gameplay_asteroid_impact_sound_paths.len,
                self.current_gameplay_sound_fx.asteroid_impact,
            ));
            self.tryPlayGameplayVoiceVariant(
                gameplay_slug_death_voice_paths.len,
                gameplay_slug_death_voice_paths,
            ) catch {};
        }
    }

    fn countGameplayProjectiles(runner: gameplay.Runner, kind: gameplay.Projectile.Kind) usize {
        var count: usize = 0;
        for (runner.activeProjectiles()) |projectile| {
            if (projectile.kind == kind) count += 1;
        }
        return count;
    }

    fn updateGameplayRunnerPresentation(self: *AppState, previous: gameplay.Runner, current: gameplay.Runner, _: gameplay.RunnerInput) void {
        self.gameplay_weapon_visual_state.tick();
        self.gameplay_weapon_visual_state.noteWeaponChannelChange(previous.movement_flags, current.movement_flags);
        if (previous.shot_cooldown_ticks == 0 and current.shot_cooldown_ticks > 0) {
            self.gameplay_weapon_visual_state.noteFire(current.movement_flags);
        }
    }

    fn updateGameplayEffects(self: *AppState) void {
        var write_index: usize = 0;
        for (0..self.active_gameplay_effect_count) |read_index| {
            var effect = self.active_gameplay_effects[read_index];
            if (!effect.active or effect.ticks_remaining == 0) continue;
            effect.position = .{
                .x = effect.position.x + effect.velocity.x,
                .y = effect.position.y + effect.velocity.y,
                .z = effect.position.z + effect.velocity.z,
            };
            effect.ticks_remaining -= 1;
            if (effect.ticks_remaining == 0) continue;
            self.active_gameplay_effects[write_index] = effect;
            write_index += 1;
        }
        self.active_gameplay_effect_count = write_index;
        for (write_index..max_active_gameplay_effects) |index| {
            self.active_gameplay_effects[index].active = false;
        }
    }

    fn spawnGameplayEffect(
        self: *AppState,
        kind: GameplayEffectKind,
        position: rl.Vector3,
        width: f32,
        height: f32,
        ticks_remaining: u16,
        tint: rl.Color,
    ) void {
        self.spawnGameplayEffectWithVelocity(kind, position, .{ .x = 0.0, .y = 0.0, .z = 0.0 }, width, height, ticks_remaining, tint);
    }

    fn spawnGameplayEffectWithVelocity(
        self: *AppState,
        kind: GameplayEffectKind,
        position: rl.Vector3,
        velocity: rl.Vector3,
        width: f32,
        height: f32,
        ticks_remaining: u16,
        tint: rl.Color,
    ) void {
        if (self.active_gameplay_effect_count >= max_active_gameplay_effects) return;
        self.active_gameplay_effects[self.active_gameplay_effect_count] = .{
            .active = true,
            .kind = kind,
            .position = position,
            .velocity = velocity,
            .width = width,
            .height = height,
            .tint = tint,
            .ticks_remaining = ticks_remaining,
        };
        self.active_gameplay_effect_count += 1;
    }

    fn spawnGameplayRunnerEffects(
        self: *AppState,
        previous: gameplay.Runner,
        current: gameplay.Runner,
        preview: *const track.LoadedLevelPreview,
    ) void {
        const forward = current.worldForward(preview);
        if (current.counters.ring_explode > previous.counters.ring_explode) {
            self.spawnGameplayEffect(
                .explode_big,
                current.worldPosition(preview, 0.52),
                1.8,
                1.8,
                28,
                .{ .r = 255, .g = 228, .b = 168, .a = 244 },
            );
        }
        if (current.counters.health_pickups > previous.counters.health_pickups) {
            self.spawnGameplayHealthPickupEffects(current, preview);
        }
        if (current.counters.garbage_hits > previous.counters.garbage_hits or current.counters.salt_hits > previous.counters.salt_hits or current.counters.turret_hits > previous.counters.turret_hits) {
            const impact_origin = current.last_garbage_hit_position orelse current.last_salt_hit_position orelse current.worldPosition(preview, 0.44);
            self.spawnGameplayEffect(
                .explode_small,
                impact_origin,
                0.9,
                0.9,
                18,
                .{ .r = 255, .g = 220, .b = 180, .a = 236 },
            );
        }
        if (current.counters.garbage_hits > previous.counters.garbage_hits) {
            const smoke_origin = current.last_garbage_hit_position orelse current.worldPosition(preview, 0.34);
            self.spawnGameplayEffectWithVelocity(
                .smoke,
                .{
                    .x = smoke_origin.x - 0.18,
                    .y = smoke_origin.y + 0.22,
                    .z = smoke_origin.z,
                },
                .{
                    .x = forward.x * 0.02,
                    .y = 0.012,
                    .z = forward.z * 0.02,
                },
                0.56,
                0.56,
                22,
                .{ .r = 255, .g = 255, .b = 255, .a = 208 },
            );
            self.spawnGameplayEffectWithVelocity(
                .smoke,
                .{
                    .x = smoke_origin.x + 0.14,
                    .y = smoke_origin.y + 0.36,
                    .z = smoke_origin.z - 0.08,
                },
                .{
                    .x = forward.x * 0.014,
                    .y = 0.018,
                    .z = (forward.z * 0.014) - 0.004,
                },
                0.72,
                0.72,
                28,
                .{ .r = 255, .g = 255, .b = 255, .a = 176 },
            );
        }
        if (current.counters.salt_hits > previous.counters.salt_hits) {
            const smoke_origin = current.last_salt_hit_position orelse current.worldPosition(preview, 0.52);
            self.spawnGameplayEffectWithVelocity(
                .smoke,
                .{
                    .x = smoke_origin.x,
                    .y = smoke_origin.y + 0.6,
                    .z = smoke_origin.z,
                },
                .{
                    .x = 0.0,
                    .y = 0.02,
                    .z = forward.z * 0.01,
                },
                0.68,
                0.82,
                24,
                .{ .r = 255, .g = 255, .b = 255, .a = 192 },
            );
        }
        if (current.defeated_slug_cell_count > previous.defeated_slug_cell_count) {
            for (previous.defeated_slug_cell_count..current.defeated_slug_cell_count) |index| {
                const defeated = current.defeated_slug_cells[index];
                const position = gameplayLaneWorldPosition(preview, defeated.row, defeated.lane, 0.38);
                self.spawnGameplayEffect(
                    .slug_goo,
                    position,
                    0.82,
                    0.82,
                    24,
                    .white,
                );
            }
        }
    }

    // PORT(partial): native `health_collect_particles` emits 8 smoke sprites from the
    // picked-up runtime slot with a fixed circular spread plus the runner's current motion.
    // The port now mirrors the recovered smoke-sprite ownership and 8-particle burst shape
    // through the existing gameplay-effect system, while still approximating the original
    // velocity source because the native player motion lanes are not ported literally yet.
    fn spawnGameplayHealthPickupEffects(
        self: *AppState,
        current: gameplay.Runner,
        preview: *const track.LoadedLevelPreview,
    ) void {
        const pickup_origin = current.last_health_pickup_position orelse current.worldPosition(preview, 0.34);
        const forward = normalizeVector3(current.worldForward(preview));
        var up = normalizeVector3(current.worldUp(preview));
        var right = crossVector3(forward, up);
        if (vectorLength(right) <= 0.0001) {
            right = .{ .x = 1.0, .y = 0.0, .z = 0.0 };
            up = .{ .x = 0.0, .y = 1.0, .z = 0.0 };
        } else {
            right = normalizeVector3(right);
            up = normalizeVector3(crossVector3(right, forward));
        }

        const forward_velocity = scaleVector3(forward, current.speed_rows_per_second * 0.02);
        var particle_index: usize = 0;
        while (particle_index < 8) : (particle_index += 1) {
            const angle =
                (@as(f32, @floatFromInt(particle_index)) / 8.0) * std.math.tau;
            const radial_velocity = addVector3(
                scaleVector3(right, std.math.sin(angle) * 0.015),
                scaleVector3(up, std.math.cos(angle) * 0.015),
            );
            self.spawnGameplayEffectWithVelocity(
                .smoke,
                pickup_origin,
                addVector3(
                    radial_velocity,
                    .{
                        .x = forward_velocity.x,
                        .y = forward_velocity.y + 0.01,
                        .z = forward_velocity.z + (current.speed_rows_per_second * 0.008),
                    },
                ),
                0.32,
                0.32,
                16,
                .{ .r = 255, .g = 191, .b = 191, .a = 224 },
            );
        }
    }

    fn handleGameInput(self: *AppState) !void {
        if (try self.handleFrontendWidgetShortcutInput()) return;

        if (rl.isKeyPressed(.escape)) {
            switch (self.game_phase) {
                .level => if (!self.completionScreenOverlayActive()) try self.enterPauseMenu(),
                .boot => self.should_exit = true,
                .main_menu => try self.beginExitPrompt(.main_menu),
                .intro, .credits => self.frontend_transition.beginFadeOut(.main_menu),
                .new_game_menu, .help => try self.enterGamePhase(.main_menu),
                .high_scores_menu => if (self.postLevelHighScoreContext() != null)
                    try self.cancelPostLevelHighScoreEntry()
                else
                    try self.enterGamePhase(.main_menu),
                .options_menu => try self.leaveOptionsMenu(),
                .pause_menu => try self.resumeFromPauseMenu(),
                .route_map_menu => try self.enterGamePhase(.main_menu),
                .exit_prompt => try self.enterGamePhase(self.exit_prompt_return_phase),
                .completion_screen => if (self.completionContinueVisible()) try self.continueCompletionScreen(),
                .thanks_screen => self.beginThanksScreenExit(),
            }
            return;
        }

        if (self.frontend_transition.blocksInput()) return;
        if (self.pending_frontend_activation != null) return;

        switch (self.game_phase) {
            .boot => {},
            .intro => {
                if (rl.isMouseButtonPressed(.left)) {
                    self.frontend_transition.beginFadeOut(.main_menu);
                }
            },
            .main_menu => {
                try self.updateMainMenuMouseSelection();
                if (rl.isKeyPressed(.up)) {
                    self.menu_index = wrappedIndex(main_menu_items.len, self.menu_index, -1);
                    self.noteFrontendKeyboardNavigation();
                }
                if (rl.isKeyPressed(.down)) {
                    self.menu_index = wrappedIndex(main_menu_items.len, self.menu_index, 1);
                    self.noteFrontendKeyboardNavigation();
                }
                if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    self.queueFrontendActivation(.{ .main_menu = main_menu_items[self.menu_index] });
                }
            },
            .new_game_menu => {
                try self.updateNewGameMenuMouseSelection();
                if (rl.isKeyPressed(.up)) {
                    self.new_game_menu_index = wrappedIndex(new_game_menu_items.len, self.new_game_menu_index, -1);
                    self.noteFrontendKeyboardNavigation();
                }
                if (rl.isKeyPressed(.down)) {
                    self.new_game_menu_index = wrappedIndex(new_game_menu_items.len, self.new_game_menu_index, 1);
                    self.noteFrontendKeyboardNavigation();
                }
                if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    self.queueFrontendActivation(.{ .new_game_menu = new_game_menu_items[self.new_game_menu_index] });
                }
            },
            .options_menu => {
                try self.updateOptionsMouseSelection();
                if (rl.isKeyPressed(.up)) {
                    self.options_menu_index = wrappedIndex(options_menu_items.len, self.options_menu_index, -1);
                    self.noteFrontendKeyboardNavigation();
                }
                if (rl.isKeyPressed(.down)) {
                    self.options_menu_index = wrappedIndex(options_menu_items.len, self.options_menu_index, 1);
                    self.noteFrontendKeyboardNavigation();
                }

                const selected = options_menu_items[self.options_menu_index];
                if (rl.isKeyPressed(.left) or rl.isKeyPressed(.a)) {
                    self.noteFrontendKeyboardNavigation();
                    try self.stepOptionsMenuValue(selected, -options_slider_adjust_step);
                }
                if (rl.isKeyPressed(.right) or rl.isKeyPressed(.d)) {
                    self.noteFrontendKeyboardNavigation();
                    try self.stepOptionsMenuValue(selected, options_slider_adjust_step);
                }
                if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    switch (selected) {
                        .fullscreen, .back => self.queueFrontendActivation(.{ .options_menu = selected }),
                        .sound_volume, .music_volume => {},
                    }
                }
            },
            .pause_menu => {
                self.updatePauseMenuMouseSelection();
                if (rl.isKeyPressed(.up)) {
                    self.pause_menu_index = wrappedIndex(pause_menu_items.len, self.pause_menu_index, -1);
                    self.noteFrontendKeyboardNavigation();
                }
                if (rl.isKeyPressed(.down)) {
                    self.pause_menu_index = wrappedIndex(pause_menu_items.len, self.pause_menu_index, 1);
                    self.noteFrontendKeyboardNavigation();
                }
                if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    self.queueFrontendActivation(.{ .pause_menu = pause_menu_items[self.pause_menu_index] });
                }
            },
            .route_map_menu => {
                try self.updateRouteMapMouseSelection();
                const route_actions = self.activeRouteMenuActions();
                if (rl.isKeyPressed(.up)) {
                    self.route_menu_action_index = wrappedIndex(route_actions.len, self.route_menu_action_index, -1);
                    self.noteFrontendKeyboardNavigation();
                }
                if (rl.isKeyPressed(.down)) {
                    self.route_menu_action_index = wrappedIndex(route_actions.len, self.route_menu_action_index, 1);
                    self.noteFrontendKeyboardNavigation();
                }
                if (routeMapAllowsRouteSwitching(self.route_map_screen_mode) and rl.isKeyPressed(.left)) {
                    self.noteFrontendKeyboardNavigation();
                    try self.stepFrontendRouteSelection(-1);
                }
                if (routeMapAllowsRouteSwitching(self.route_map_screen_mode) and rl.isKeyPressed(.right)) {
                    self.noteFrontendKeyboardNavigation();
                    try self.stepFrontendRouteSelection(1);
                }
                if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    self.queueFrontendActivation(.{ .route_map_menu = route_actions[self.route_menu_action_index] });
                }
                self.syncRouteMapHighlightTargets();
                self.stepRouteMapHighlightAnimations();
            },
            .high_scores_menu => {
                try self.updateHighScoresMouseSelection();
                if (self.postLevelHighScoreContext() != null) {
                    self.collectPostLevelHighScoreTextInput();
                    if (rl.isKeyPressed(.up) or rl.isKeyPressed(.left)) {
                        self.post_level_high_score_action_index = wrappedIndex(post_level_high_score_actions.len, self.post_level_high_score_action_index, -1);
                        self.noteFrontendKeyboardNavigation();
                    }
                    if (rl.isKeyPressed(.down) or rl.isKeyPressed(.right)) {
                        self.post_level_high_score_action_index = wrappedIndex(post_level_high_score_actions.len, self.post_level_high_score_action_index, 1);
                        self.noteFrontendKeyboardNavigation();
                    }
                    if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                        self.queueFrontendActivation(.{ .post_level_high_scores = post_level_high_score_actions[self.post_level_high_score_action_index] });
                    }
                } else {
                    if (rl.isKeyPressed(.up) or rl.isKeyPressed(.left)) {
                        self.high_scores_action_index = wrappedIndex(high_score_menu_actions.len, self.high_scores_action_index, -1);
                        self.noteFrontendKeyboardNavigation();
                    }
                    if (rl.isKeyPressed(.down) or rl.isKeyPressed(.right)) {
                        self.high_scores_action_index = wrappedIndex(high_score_menu_actions.len, self.high_scores_action_index, 1);
                        self.noteFrontendKeyboardNavigation();
                    }
                    if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                        self.queueFrontendActivation(.{ .high_scores_menu = high_score_menu_actions[self.high_scores_action_index] });
                    }
                }
            },
            .exit_prompt => {
                try self.updateExitPromptMouseSelection();
                if (rl.isKeyPressed(.up) or rl.isKeyPressed(.left)) {
                    self.exit_prompt_choice_index = wrappedIndex(exit_prompt_choices.len, self.exit_prompt_choice_index, -1);
                    self.noteFrontendKeyboardNavigation();
                }
                if (rl.isKeyPressed(.down) or rl.isKeyPressed(.right)) {
                    self.exit_prompt_choice_index = wrappedIndex(exit_prompt_choices.len, self.exit_prompt_choice_index, 1);
                    self.noteFrontendKeyboardNavigation();
                }
                if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    self.queueFrontendActivation(.{ .exit_prompt = exit_prompt_choices[self.exit_prompt_choice_index] });
                }
            },
            .completion_screen => {
                self.updateCompletionScreenMouseSelection();
                if (self.completionContinueVisible() and (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space))) {
                    self.noteFrontendKeyboardNavigation();
                    self.queueFrontendActivation(.{ .completion_screen = .continue_flow });
                }
            },
            .thanks_screen => {
                if (rl.isMouseButtonPressed(.left) or rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    self.beginThanksScreenExit();
                }
            },
            .credits => {
                if (rl.isMouseButtonPressed(.left)) {
                    self.frontend_transition.beginFadeOut(.main_menu);
                }
            },
            .help => {
                self.updateHelpMouseSelection();
                if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                    self.queueFrontendActivation(.{ .help_menu = .back });
                }
            },
            .level => {
                if (self.gameplay_click_start_active) {
                    if (rl.isMouseButtonPressed(.left) or rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                        try self.activateGameplayClickStart();
                    }
                    return;
                }
                if (self.level_runner) |runner| {
                    if (runner.introCutsceneBlocksGameplay()) return;
                }
                if (self.tutorialPromptBlocksGameplay()) {
                    if (rl.isKeyPressed(.enter) or rl.isKeyPressed(.space)) {
                        self.level_prompt_queue.dismissActive();
                    } else if (rl.isMouseButtonPressed(.left)) {
                        if (self.currentUiMouseLocal()) |mouse| {
                            if (activeLevelPromptOkHitRect(self, &self.level_prompt_queue, true)) |ok_button| {
                                if (ok_button.contains(mouse)) {
                                    self.level_prompt_queue.dismissActive();
                                }
                            }
                        }
                    }
                    return;
                }
                if (self.completionScreenOverlayActive()) return;
                const accepts_runner_input = if (self.level_runner) |runner| runner.acceptsGameplayInput() else false;
                const accepts_live_replay_controls = accepts_runner_input and !self.selectedReplayPlaybackActive();
                self.mouse_level_lane_target = null;
                if (accepts_live_replay_controls and (rl.isKeyPressed(.left) or rl.isKeyPressed(.a))) {
                    self.mouse_level_lane_target = null;
                    self.pending_level_input.lane_delta -= 1;
                }
                if (accepts_live_replay_controls and (rl.isKeyPressed(.right) or rl.isKeyPressed(.d))) {
                    self.mouse_level_lane_target = null;
                    self.pending_level_input.lane_delta += 1;
                }
                if (accepts_live_replay_controls and (rl.isKeyPressed(.up) or rl.isKeyPressed(.w))) {
                    self.pending_level_input.speed_delta_rows_per_second += 2.0;
                }
                if (accepts_live_replay_controls and (rl.isKeyPressed(.down) or rl.isKeyPressed(.s))) {
                    self.pending_level_input.speed_delta_rows_per_second -= 2.0;
                }
                if (accepts_live_replay_controls and rl.isMouseButtonPressed(.left)) {
                    self.pending_level_input.fire_pressed = true;
                }
                if (accepts_live_replay_controls and rl.isMouseButtonDown(.left)) {
                    self.pending_level_input.fire_down = true;
                }
                if (accepts_runner_input and rl.isKeyPressed(.space)) {
                    try self.enterPauseMenu();
                    return;
                }
                if (rl.isKeyPressed(.r)) {
                    self.mouse_level_lane_target = null;
                    self.pending_level_input.reset = true;
                }
                if (accepts_live_replay_controls) {
                    if (self.current_track_preview) |loaded_track_preview| {
                        if (self.level_runner) |runner| {
                            self.mouse_level_lane_target = laneCenterTargetForRunnerMouse(
                                loaded_track_preview,
                                runner,
                                @floatFromInt(rl.getMouseX()),
                            );
                            if (self.mouse_level_lane_target) |lane_target| {
                                self.pending_level_input.target_lane_center = lane_target;
                            }
                        }
                    }
                }
            },
        }
    }

    fn enterGamePhase(self: *AppState, phase: GamePhase) !void {
        self.game_phase = phase;
        self.game_phase_ticks = 0;
        self.hovered_frontend_target = null;
        self.keyboard_frontend_focus_visible = false;
        self.pending_frontend_activation = null;
        try self.syncGamePhaseResources();
        self.snapFrontendWidgetStates();
    }

    fn enterStartPhase(self: *AppState, phase: GamePhase) !void {
        try self.high_score_tables.loadFromRuntimeRoot(self.allocator, self.runtime_root_path);

        switch (phase) {
            .boot => try self.enterGamePhase(.boot),
            .intro,
            .main_menu,
            .new_game_menu,
            .high_scores_menu,
            .help,
            .credits,
            .thanks_screen,
            => try self.enterGamePhase(phase),
            .options_menu => {
                if (self.start_pause_context) {
                    try self.loadGameLevel(default_level_path);
                    self.options_return_phase = .pause_menu;
                } else {
                    self.options_return_phase = .main_menu;
                }
                try self.enterGamePhase(.options_menu);
            },
            .pause_menu => {
                try self.enterGameplayShell(default_level_path);
                try self.enterPauseMenu();
            },
            .exit_prompt => {
                if (self.start_pause_context) {
                    try self.loadGameLevel(default_level_path);
                    try self.beginEndGamePrompt(.pause_menu);
                } else {
                    try self.beginExitPrompt(.main_menu);
                }
            },
            .route_map_menu => try self.enterRouteMapMenu(.postal),
            .level => try self.enterGameplayShell(default_level_path),
            .completion_screen => {
                try self.loadGameLevel(default_level_path);
                self.active_frontend_mode = .postal;
                self.active_frontend_level_index = 1;
                self.pending_run_result = .{
                    .outcome = .completed,
                    .level_name = "Snail Mail 101",
                    .mode = .postal,
                    .elapsed_millis = 62_340,
                    .parcel_count = 1,
                    .parcel_target = 1,
                    .score = 50_300,
                    .score_is_partial = true,
                    .score_totals = .{
                        .parcel_pickup = 100,
                        .parcel_register = 100,
                        .completion_bonus = 50_000,
                        .total = 50_300,
                    },
                    .visible_life_stock = 3,
                    .return_target = .postal_route_map,
                };
                try self.enterGamePhase(.completion_screen);
            },
        }
    }

    fn performMainMenuItem(self: *AppState, item: MainMenuItem) !void {
        switch (item) {
            .new_game => try self.enterGamePhase(.new_game_menu),
            .high_scores => {
                self.high_scores_action_index = 1;
                try self.enterGamePhase(.high_scores_menu);
            },
            .options => {
                self.options_return_phase = .main_menu;
                try self.enterGamePhase(.options_menu);
            },
            .credits => try self.enterGamePhase(.credits),
            .exit => try self.beginExitPrompt(.main_menu),
        }
    }

    fn activateMainMenuItem(self: *AppState, item: MainMenuItem) !void {
        self.playFrontendSelectSound();
        try self.performMainMenuItem(item);
    }

    fn performNewGameMenuItem(self: *AppState, item: NewGameMenuItem) !void {
        switch (item) {
            .tutorial => try self.enterFrontendLevelMode(.tutorial),
            .postal_mode => try self.enterFrontendLevelMode(.postal),
            .time_trial => try self.enterFrontendLevelMode(.time_trial),
            .challenge_mode => try self.enterFrontendLevelMode(.challenge),
            .help => try self.enterGamePhase(.help),
            .back => try self.enterGamePhase(.main_menu),
        }
    }

    fn activateNewGameMenuItem(self: *AppState, item: NewGameMenuItem) !void {
        self.playFrontendSelectSound();
        try self.performNewGameMenuItem(item);
    }

    fn performOptionsMenuItem(self: *AppState, item: OptionsMenuItem) !void {
        switch (item) {
            .fullscreen => self.toggleFullscreenPreference(),
            .sound_volume, .music_volume => {},
            .back => try self.leaveOptionsMenu(),
        }
    }

    fn performPauseMenuItem(self: *AppState, item: PauseMenuItem) !void {
        switch (item) {
            .end_game => try self.beginEndGamePrompt(.pause_menu),
            .options => {
                self.options_return_phase = .pause_menu;
                try self.enterGamePhase(.options_menu);
            },
            .@"resume" => try self.resumeFromPauseMenu(),
        }
    }

    fn performHelpMenuItem(self: *AppState, item: HelpMenuAction) !void {
        switch (item) {
            .back => try self.returnToNewGameMenu(.help),
        }
    }

    fn activateOptionsMenuItem(self: *AppState, item: OptionsMenuItem) !void {
        self.playFrontendSelectSound();
        try self.performOptionsMenuItem(item);
    }

    fn beginExitPrompt(self: *AppState, return_phase: GamePhase) !void {
        self.exit_prompt_choice_index = 1;
        self.exit_prompt_return_phase = return_phase;
        self.exit_prompt_mode = .quit_app;
        try self.enterGamePhase(.exit_prompt);
    }

    fn beginEndGamePrompt(self: *AppState, return_phase: GamePhase) !void {
        self.exit_prompt_choice_index = 1;
        self.exit_prompt_return_phase = return_phase;
        self.exit_prompt_mode = .abandon_run;
        try self.enterGamePhase(.exit_prompt);
    }

    // PORT(verified): the special postal-return Star Map mode (`initialize_galaxy` with
    // `this + 4 == 1`) routes its bottom `Exit` control through the shared exit-prompt
    // controller before returning to the outer front-end flow.
    fn beginRouteMapExitPrompt(self: *AppState) !void {
        self.exit_prompt_choice_index = 1;
        self.exit_prompt_return_phase = .route_map_menu;
        self.exit_prompt_mode = .leave_route_map;
        try self.enterGamePhase(.exit_prompt);
    }

    fn performExitPromptChoice(self: *AppState, choice: ExitPromptChoice) !void {
        switch (choice) {
            .no => try self.enterGamePhase(self.exit_prompt_return_phase),
            .yes => switch (self.exit_prompt_mode) {
                .quit_app => self.should_exit = true,
                .abandon_run => try self.abandonActiveRun(),
                .leave_route_map => try self.returnToNewGameMenu(.route_map_menu),
            },
        }
    }

    fn activateExitPromptChoice(self: *AppState, choice: ExitPromptChoice) !void {
        self.playFrontendSelectSound();
        try self.performExitPromptChoice(choice);
    }

    fn performRouteMenuAction(self: *AppState, action: RouteMenuAction) !void {
        switch (action) {
            .play => try self.enterSelectedFrontendRoute(),
            .watch_best_trial => {
                const route_index = self.currentRouteMapOpenIndex() orelse return;
                const completion_index = high_score.completionIndexForRouteIndex(route_index) orelse return;
                try self.enterSelectedLevelRecordSource(.{ .completion = completion_index });
            },
            .back => if (self.route_map_screen_mode == .post_completion_exit)
                try self.beginRouteMapExitPrompt()
            else
                try self.returnToNewGameMenu(.route_map_menu),
        }
    }

    fn performCompletionAction(self: *AppState, action: CompletionAction) !void {
        switch (action) {
            .continue_flow => try self.continueCompletionScreen(),
        }
    }

    fn performPostLevelHighScoreAction(self: *AppState, action: PostLevelHighScoreAction) !void {
        switch (action) {
            .cancel => try self.cancelPostLevelHighScoreEntry(),
            .submit => try self.submitPostLevelHighScore(),
        }
    }

    fn activatePostLevelHighScoreAction(self: *AppState, action: PostLevelHighScoreAction) !void {
        self.playFrontendSelectSound();
        try self.performPostLevelHighScoreAction(action);
    }

    fn performHighScoreMenuAction(self: *AppState, action: HighScoreMenuAction) !void {
        switch (action) {
            .back => try self.enterGamePhase(.main_menu),
            .switch_table => self.high_scores_menu_index = wrappedIndex(high_score_screen_modes.len, self.high_scores_menu_index, 1),
        }
    }

    fn performHighScoreReplay(self: *AppState, entry_index: usize) !void {
        if (!self.highScoreReplayAvailable(entry_index)) return;
        const selected_mode = high_score_screen_modes[@min(self.high_scores_menu_index, high_score_screen_modes.len - 1)];
        const source: SelectedLevelRecordSource = switch (selected_mode) {
            .postal => .{ .postal = entry_index },
            .challenge => .{ .challenge = entry_index },
        };
        try self.enterSelectedLevelRecordSource(source);
    }

    fn activateHighScoreMenuAction(self: *AppState, action: HighScoreMenuAction) !void {
        self.playFrontendSelectSound();
        try self.performHighScoreMenuAction(action);
    }

    fn enterPauseMenu(self: *AppState) !void {
        self.pause_menu_index = 0;
        try self.enterGamePhase(.pause_menu);
    }

    fn resumeFromPauseMenu(self: *AppState) !void {
        try self.enterGamePhase(.level);
    }

    fn outerBridgeRequestForAbandonActiveRun(self: *const AppState) OuterBridgeRequest {
        if (self.selectedReplayPlaybackActive()) {
            const source = self.selected_level_record_source orelse return .{
                .opcode = .destroy_return,
                .target = .main_menu,
            };
            return .{
                .opcode = .rebuild_clear_replay_return,
                .target = bridgeTargetForReplaySource(source, self.active_frontend_level_index),
            };
        }

        return .{
            .opcode = .destroy_return,
            .target = self.preserved_frontend_owner,
        };
    }

    fn outerBridgeRequestForPendingRunResult(self: *const AppState, result: PendingRunResult) OuterBridgeRequest {
        return switch (result.return_target) {
            .main_menu => .{
                .opcode = .destroy_return,
                .target = .main_menu,
            },
            .new_game_menu => .{
                .opcode = .destroy_return,
                .target = .{ .new_game_menu = newGameMenuItemForBridgeMode(result.mode) },
            },
            .postal_route_map => .{
                .opcode = .destroy_return,
                .target = .{ .route_map = .{
                    .mode = .postal,
                    .screen_mode = .post_completion_exit,
                } },
            },
            .time_trial_route_map => .{
                .opcode = if (self.selectedReplayPlaybackActive())
                    .rebuild_clear_replay_return
                else
                    .destroy_return,
                .target = .{ .route_map = .{
                    .mode = .time_trial,
                    .screen_mode = defaultRouteMapScreenMode(.time_trial),
                    .start_route_override = if (self.selectedReplayPlaybackActive())
                        self.active_frontend_level_index
                    else
                        null,
                } },
            },
            .high_scores_menu => .{
                .opcode = if (self.selectedReplayPlaybackActive())
                    .rebuild_clear_replay_return
                else
                    .destroy_return,
                .target = .{ .high_scores_menu = if (self.selected_level_record_source) |source|
                    switch (source) {
                        .postal => .postal,
                        .challenge => .challenge,
                        .completion => result.high_score_mode orelse .postal,
                    }
                else
                    result.high_score_mode orelse .postal },
            },
            .replay_current_level => blk: {
                if (self.selected_level_record_override) |record| {
                    break :blk .{
                        .opcode = .rebuild_return,
                        .target = .{ .replay_current_level = .{
                            .mode = record.mode,
                            .level_index = record.level_index,
                            .selected_level_record_override = record,
                            .selected_level_record_source = self.selected_level_record_source,
                        } },
                    };
                }
                if (result.mode) |mode| {
                    break :blk .{
                        .opcode = .rebuild_return,
                        .target = .{ .replay_current_level = .{
                            .mode = mode,
                            .level_index = self.active_frontend_level_index,
                        } },
                    };
                }
                break :blk .{
                    .opcode = .destroy_return,
                    .target = .main_menu,
                };
            },
            .thanks_screen => .{
                .opcode = .init_thanks_screen,
                .target = .thanks_screen,
            },
        };
    }

    fn applyOuterBridgeTeardown(self: *AppState, opcode: OuterBridgeOpcode) !void {
        self.active_frontend_mode = null;
        self.active_frontend_level_index = 0;
        if (opcode == .rebuild_clear_replay_return) {
            try self.setSelectedLevelRecordContext(null, null);
        }
    }

    fn dispatchOuterBridgeRequest(self: *AppState, request: OuterBridgeRequest) !void {
        try self.applyOuterBridgeTeardown(request.opcode);

        switch (request.target) {
            .main_menu => try self.enterGamePhase(.main_menu),
            .new_game_menu => |item| {
                self.new_game_menu_index = newGameMenuIndexForItem(item);
                try self.enterGamePhase(.new_game_menu);
            },
            .route_map => |target| {
                self.start_route_index_override = target.start_route_override;
                try self.enterRouteMapMenuWithScreenMode(target.mode, target.screen_mode);
            },
            .high_scores_menu => |mode| {
                self.high_scores_menu_index = highScoreModeIndex(mode);
                try self.enterGamePhase(.high_scores_menu);
            },
            .replay_current_level => |target| {
                try self.beginFrontendLevelPath(
                    target.mode,
                    target.level_index,
                    target.selected_level_record_override,
                    target.selected_level_record_source,
                );
            },
            .thanks_screen => try self.enterGamePhase(.thanks_screen),
        }
    }

    fn abandonActiveRun(self: *AppState) !void {
        self.pending_run_result = null;
        self.clearPostLevelHighScoreEntry();
        try self.dispatchOuterBridgeRequest(self.outerBridgeRequestForAbandonActiveRun());
    }

    fn enterGameplayShell(self: *AppState, level_path: []const u8) !void {
        self.active_frontend_mode = null;
        self.active_frontend_level_index = 0;
        self.preserved_frontend_owner = .main_menu;
        try self.setSelectedLevelRecordContext(null, null);
        try self.loadGameLevel(level_path);
        try self.enterGamePhase(.level);
    }

    fn enterFrontendLevelPath(self: *AppState, mode: FrontendLevelMode, level_index: usize) !void {
        try self.beginFrontendLevelPath(mode, level_index, null, null);
    }

    fn enterSelectedLevelRecordPath(self: *AppState, record: SelectedLevelRecordOverride) !void {
        try self.beginFrontendLevelPath(record.mode, record.level_index, record, self.selected_level_record_source);
    }

    fn enterSelectedLevelRecordSource(self: *AppState, source: SelectedLevelRecordSource) !void {
        const entry = self.selectedReplayEntryForSource(source) orelse return;
        const record = SelectedLevelRecordOverride.fromHighScoreEntry(entry) orelse return;
        try self.beginFrontendLevelPath(record.mode, record.level_index, record, source);
    }

    fn beginFrontendLevelPath(
        self: *AppState,
        mode: FrontendLevelMode,
        level_index: usize,
        selected_level_record_override: ?SelectedLevelRecordOverride,
        selected_level_record_source: ?SelectedLevelRecordSource,
    ) !void {
        var path_buffer: [64]u8 = undefined;
        const level_path = try frontendLevelPath(mode, level_index, &path_buffer);
        try self.setSelectedLevelRecordContext(selected_level_record_override, selected_level_record_source);
        self.active_frontend_mode = mode;
        self.active_frontend_level_index = level_index;
        self.preserved_frontend_owner = preservedFrontendOwnerForLevelLaunch(mode, level_index, selected_level_record_source);
        self.seed_level_intro_cutscene = true;
        try self.loadGameLevel(level_path);
        try self.enterGamePhase(.level);
    }

    fn leaveOptionsMenu(self: *AppState) !void {
        try self.saveRuntimeConfig();
        try self.enterGamePhase(self.options_return_phase);
    }

    // PORT(verified): `update_help` writes frontend state `2` on Back, and the frontend
    // state machine handles that by rebuilding the New Game screen/controller path rather than
    // jumping straight to the main menu. The normal Star Map `update_galaxy -> return 3`
    // path in `update_subgame` also tears down the galaxy screen and returns to the New Game
    // flow. Preserve that return target in the port instead of routing Help/Star Map Back to
    // the main menu.
    fn returnToNewGameMenu(self: *AppState, from_phase: GamePhase) !void {
        switch (from_phase) {
            .help => self.new_game_menu_index = newGameMenuIndexForItem(.help),
            .route_map_menu => {
                if (self.frontend_route_mode) |mode| {
                    self.new_game_menu_index = newGameMenuIndexForItem(newGameMenuItemForFrontendMode(mode));
                }
            },
            else => {},
        }
        try self.enterGamePhase(.new_game_menu);
    }

    fn enterFrontendLevelMode(self: *AppState, mode: FrontendLevelMode) !void {
        switch (mode) {
            .postal, .time_trial => try self.enterRouteMapMenu(mode),
            .challenge, .tutorial => try self.enterFrontendLevelPath(mode, 0),
        }
    }

    fn enterRouteMapMenu(self: *AppState, mode: FrontendLevelMode) !void {
        try self.enterRouteMapMenuWithScreenMode(mode, defaultRouteMapScreenMode(mode));
    }

    fn enterRouteMapMenuWithScreenMode(self: *AppState, mode: FrontendLevelMode, screen_mode: RouteMapScreenMode) !void {
        try self.setSelectedLevelRecordContext(null, null);
        self.frontend_route_mode = mode;
        self.route_map_screen_mode = screen_mode;
        self.frontend_route_index = self.initialFrontendRouteIndex(mode);
        if (self.start_route_index_override) |override| {
            const highest_available = self.highestAvailableFrontendRouteIndex(mode);
            if (highest_available > 0) {
                self.frontend_route_index = std.math.clamp(override, @as(usize, 1), highest_available);
            }
            self.start_route_index_override = null;
        }
        try self.openFrontendRouteCard(self.frontend_route_index);
        self.resetRouteMapHighlightAnimations();
        self.syncRouteMapHighlightTargets();
        try self.enterGamePhase(.route_map_menu);
    }

    fn unloadFrontendRouteLevel(self: *AppState) void {
        if (self.frontend_route_level) |*loaded_level| {
            loaded_level.deinit();
            self.frontend_route_level = null;
        }
    }

    fn reloadFrontendRouteLevel(self: *AppState) !void {
        self.unloadFrontendRouteLevel();
        const mode = self.frontend_route_mode orelse return;
        var path_buffer: [64]u8 = undefined;
        const level_path = frontendLevelPath(mode, self.frontend_route_index, &path_buffer) catch return;
        const level_index = self.catalog.findLevelIndex(level_path) orelse return;
        self.frontend_route_level = try level.loadFromArchive(self.allocator, &self.catalog, self.catalog.level_entries[level_index]);
    }

    fn currentFrontendGalaxyName(self: *const AppState) ?[]const u8 {
        const names = self.galaxy_names orelse return null;
        return names.nameForRouteIndex(self.currentRouteMapOpenIndex() orelse self.frontend_route_index);
    }

    fn routeMapShowsReplay(self: *const AppState) bool {
        // PORT(verified): `open_galaxy_route` only reveals "Watch Best Trial" when the Star
        // Map is in internal mode `2` and the route's completion slot has replay data.
        if (self.route_map_screen_mode != .replay) return false;
        const route_index = self.currentRouteMapOpenIndex() orelse return false;
        return routeMapHasReplayEntry(self.frontend_route_mode, route_index, &self.high_score_tables);
    }

    fn routeMapCardIsOpen(self: *const AppState) bool {
        return self.route_map_open_index != null;
    }

    // PORT(verified): `open_galaxy_route` stores the active route index at `this + 69504`,
    // while `close_galaxy_route` clears that slot back to `-1`. Model the open-card route
    // separately instead of assuming the saved/default route is always the open one.
    fn currentRouteMapOpenIndex(self: *const AppState) ?usize {
        return self.route_map_open_index;
    }

    // PORT(verified): the late `update_galaxy` close-card branch only fires when the
    // open-route flag is set and the authored route count is greater than `1`
    // (`dword_4DF9B8 > 1`). Preserve that gate so the first available route stays pinned
    // open instead of letting the user dismiss the card into an empty Star Map.
    fn routeMapCanCloseCard(self: *const AppState) bool {
        if (!self.routeMapCardIsOpen()) return false;
        if (!routeMapAllowsRouteSwitching(self.route_map_screen_mode)) return false;
        const mode = self.frontend_route_mode orelse return false;
        return self.availableFrontendRouteLimit(mode) > 1;
    }

    fn openFrontendRouteCard(self: *AppState, route_index: usize) !void {
        self.route_map_open_index = route_index;
        self.route_map_hover_state = .none;
        self.route_map_hovered_index = null;
        self.frontend_route_index = route_index;
        self.syncRouteMapHighlightTargets();
        try self.reloadFrontendRouteLevel();
        if (self.routeMenuActionIndexForAction(.play)) |index| {
            self.route_menu_action_index = index;
        } else {
            self.route_menu_action_index = 0;
        }
    }

    fn closeFrontendRouteCard(self: *AppState) void {
        self.route_map_open_index = null;
        self.route_map_hover_state = .none;
        self.route_map_hovered_index = null;
        self.route_menu_action_index = 0;
        self.syncRouteMapHighlightTargets();
    }

    fn resetRouteMapHighlightAnimations(self: *AppState) void {
        @memset(&self.route_map_route_highlight_alpha, 0.0);
        @memset(&self.route_map_route_highlight_target, 0.0);
    }

    // PORT(verified): `update_galaxy` ticks each route entry through `sub_409BD0`, which
    // eases the current highlight alpha at `+40` toward the target at `+44` with a `0.1`
    // step. The target is `1.0` for the hovered route in hover state `2`, otherwise for the
    // open route while the card is up.
    fn syncRouteMapHighlightTargets(self: *AppState) void {
        @memset(&self.route_map_route_highlight_target, 0.0);
        const highlighted_route_index = switch (self.route_map_hover_state) {
            .route => self.route_map_hovered_index,
            .card, .none => self.currentRouteMapOpenIndex(),
        } orelse return;
        if (highlighted_route_index < self.route_map_route_highlight_target.len) {
            self.route_map_route_highlight_target[highlighted_route_index] = 1.0;
        }
    }

    fn stepRouteMapHighlightAnimations(self: *AppState) void {
        for (1..self.route_map_route_highlight_alpha.len) |route_index| {
            const current = self.route_map_route_highlight_alpha[route_index];
            const target = self.route_map_route_highlight_target[route_index];
            self.route_map_route_highlight_alpha[route_index] = current + (target - current) * 0.1;
        }
    }

    // PORT(verified): `update_galaxy` and `close_galaxy_route` gate the Star Map card actions
    // on the route-open flag at `this + 8`. When the card is closed, only the absolute Back
    // control remains actionable; Play and Watch Best Trial are hidden until `open_galaxy_route`.
    fn activeRouteMenuActions(self: *const AppState) []const RouteMenuAction {
        if (!self.routeMapCardIsOpen()) return &route_menu_actions_closed;
        return if (self.routeMapShowsReplay())
            &route_menu_actions_with_replay
        else
            &route_menu_actions_without_replay;
    }

    fn activeRouteMenuHotAction(self: *const AppState) RouteMenuAction {
        const actions = self.activeRouteMenuActions();
        return actions[@min(self.route_menu_action_index, actions.len - 1)];
    }

    fn routeMenuActionIndexForAction(self: *const AppState, action: RouteMenuAction) ?usize {
        for (self.activeRouteMenuActions(), 0..) |candidate, index| {
            if (candidate == action) return index;
        }
        return null;
    }

    fn clearLevelPromptQueue(self: *AppState) void {
        self.level_prompt_queue.clear();
    }

    fn isTutorialGameplay(self: *const AppState) bool {
        if (self.isTutorialFlow()) return true;
        return self.isTutorialLevel();
    }

    fn isTutorialFlow(self: *const AppState) bool {
        if (self.active_frontend_mode == .tutorial) return true;
        if (self.level_runner) |runner| {
            if (runner.session_mode == .tutorial) return true;
        }
        return false;
    }

    fn isTutorialLevel(self: *const AppState) bool {
        const loaded_level = self.current_level orelse return false;
        return std.mem.eql(u8, loaded_level.source_path, "LEVELS/TUTORIAL.TXT");
    }

    fn tutorialPromptBlocksGameplay(self: *const AppState) bool {
        if (!self.isTutorialGameplay()) return false;
        const prompt = self.level_prompt_queue.active() orelse return false;
        return prompt.interactive;
    }

    fn tutorialClickStartCutsceneActive(self: *const AppState) bool {
        if (!self.gameplay_click_start_active) return false;
        const runner = self.level_runner orelse return false;
        return runner.introCutsceneBlocksGameplay();
    }

    fn startupGameplayBlockActive(self: *const AppState) bool {
        if (self.gameplay_click_start_active) return true;
        const runner = self.level_runner orelse return false;
        return runner.introCutsceneBlocksGameplay();
    }

    fn refreshRunnerForStartupBlock(
        self: *const AppState,
        runner: *gameplay.Runner,
        loaded_track_preview: *const track.LoadedLevelPreview,
        delta_seconds: f32,
    ) void {
        if (self.gameplay_click_start_active) {
            runner.refreshBlockedStartupState(loaded_track_preview);
            return;
        }
        if (runner.introCutsceneBlocksGameplay()) {
            runner.stepIntroStartupBlock(loaded_track_preview, delta_seconds);
            return;
        }
        runner.refreshCameraState(loaded_track_preview);
    }

    fn resetSubgameCamera(self: *AppState) void {
        self.subgame_camera = .{};
    }

    fn updateSubgameCamera(self: *AppState, runner: *gameplay.Runner) void {
        const selection = subgameCameraSelectionForRunner(runner);
        updateSubgameCameraState(&self.subgame_camera, selection);
    }

    fn queueLevelSegmentPrompt(self: *AppState, segment_entry: *const level.SegmentEntry) void {
        const message = segment_entry.message orelse return;
        const duration_ticks = level_prompt.durationTicks(segment_entry.duration);
        if (self.isTutorialGameplay()) {
            self.level_prompt_queue.replaceSingle(message, duration_ticks);
            return;
        }
        self.level_prompt_queue.enqueue(message, duration_ticks);
    }

    fn activateGameplayClickStart(self: *AppState) !void {
        if (!self.gameplay_click_start_active) return;
        self.gameplay_click_start_active = false;
        self.mouse_level_lane_target = null;
        self.pending_level_input = .{};
        if (self.audio_ready) {
            if (self.frontend_sound_fx.select) |loaded| {
                rl.playSound(loaded.sound);
            }
        }
        rl.setMousePosition(@divTrunc(rl.getScreenWidth(), 2), @divTrunc(rl.getScreenHeight(), 2));
        const previous_active_level_segment_index = self.active_level_segment_index;
        try self.syncActiveLevelSegment();
        try self.dispatchCurrentRunnerRowMessage(previous_active_level_segment_index, null, true);
    }

    fn currentRunnerRowMessageSegmentIndex(self: *const AppState) ?usize {
        const loaded_level = self.current_level orelse return null;
        const runner = self.level_runner orelse return null;
        const logical_segment_index = runner.currentRowMessageLogicalSegmentIndex() orelse return null;
        if (logical_segment_index >= loaded_level.segments.len) return null;
        return logical_segment_index;
    }

    fn playLevelSegmentSample(self: *AppState, segment_entry: *const level.SegmentEntry) !void {
        const sample_path = segment_entry.sample orelse return;
        if (std.ascii.startsWithIgnoreCase(sample_path, "VOICE/")) {
            if (nativeGlobalAudioSampleIndexForPath(sample_path)) |payload_index| {
                _ = try self.tryPlayNativeGameplayVoicePayload(.tutorial, .interrupt_current, payload_index);
            } else {
                try self.playVoiceByPath(sample_path);
            }
        } else {
            try self.playSoundByPath(sample_path);
        }
    }

    fn dispatchCurrentRunnerRowMessage(
        self: *AppState,
        previous_segment_index: ?usize,
        previous_token: ?u32,
        replay_sample_on_match: bool,
    ) !void {
        const logical_segment_index = self.currentRunnerRowMessageSegmentIndex() orelse return;
        if (self.startupGameplayBlockActive()) return;

        const loaded_level = self.current_level orelse return;
        const runner = self.level_runner orelse return;
        const segment_changed = previous_segment_index == null or previous_segment_index.? != logical_segment_index;
        const token_changed = if (previous_token) |token|
            runner.currentRowMessageToken() != token
        else
            false;
        if (!segment_changed and !token_changed and !replay_sample_on_match) return;

        const segment_entry = &loaded_level.segments[logical_segment_index];
        if (segment_changed or token_changed) {
            self.queueLevelSegmentPrompt(segment_entry);
        }
        if (segment_changed or token_changed or replay_sample_on_match) {
            try self.playLevelSegmentSample(segment_entry);
        }
    }

    fn enterSelectedFrontendRoute(self: *AppState) !void {
        const mode = self.frontend_route_mode orelse return;
        try self.enterFrontendLevelPath(mode, self.currentRouteMapOpenIndex() orelse self.frontend_route_index);
    }

    fn replaySpeedScalarForSliderValue(value: u32) f32 {
        const normalized = @as(f32, @floatFromInt(value)) * 0.01;
        return if (normalized >= 1.0)
            1.1
        else
            (normalized * 0.9) + 0.2;
    }

    fn currentRunReplaySpeedScalar(self: *const AppState) f32 {
        if (self.selected_level_record_override) |record| return record.replay_speed_scalar;
        return switch (self.active_frontend_mode orelse .tutorial) {
            .challenge => replaySpeedScalarForSliderValue(self.runtime_config.challengeReplaySpeedValue()),
            .postal, .time_trial, .tutorial => replaySpeedScalarForSliderValue(if (self.current_level) |loaded_level|
                @as(u32, @intCast(loaded_level.speed orelse 0))
            else
                0),
        };
    }

    fn currentRunChallengeDifficultyValue(self: *const AppState) u32 {
        if (self.selected_level_record_override) |record| return record.challenge_difficulty_value;
        return switch (self.active_frontend_mode orelse .tutorial) {
            .challenge => self.runtime_config.challengeReplayDifficultyValue(),
            .postal, .time_trial, .tutorial => 0,
        };
    }

    fn currentRunChallengeDifficultyScalar(self: *const AppState) f32 {
        if (self.selected_level_record_override) |record| return record.challenge_difficulty_scalar;
        return switch (self.active_frontend_mode orelse .tutorial) {
            .challenge => @as(f32, @floatFromInt(self.currentRunChallengeDifficultyValue())) * 0.01,
            .postal, .time_trial, .tutorial => 0.0,
        };
    }

    fn currentRunChallengeSpeedValue(self: *const AppState) u32 {
        if (self.selected_level_record_override) |record| return record.challenge_speed_value;
        return switch (self.active_frontend_mode orelse .tutorial) {
            .challenge => self.runtime_config.challengeReplaySpeedValue(),
            .postal, .time_trial, .tutorial => 0,
        };
    }

    fn challengeParcelTargetCount(speed_value: u32, difficulty_scalar: f32) usize {
        const scaled_target = (@as(f32, @floatFromInt(speed_value)) * 50.0 * 0.01) +
            (difficulty_scalar * 50.0);
        return @as(usize, @intFromFloat(@floor(@max(scaled_target, 0.0)))) + 1;
    }

    fn challengeRuntimeHazardScalar(value: u32) f32 {
        return @as(f32, @floatFromInt(value)) * 0.01 * 0.8;
    }

    fn currentRunGarbageScalar(self: *const AppState) f32 {
        if (self.selected_level_record_override) |record| return record.garbage_scalar;
        return switch (self.active_frontend_mode orelse .tutorial) {
            .challenge => challengeRuntimeHazardScalar(self.currentRunChallengeDifficultyValue()),
            .postal, .time_trial, .tutorial => if (self.current_level) |loaded_level|
                loaded_level.normalizedGarbageScalar() orelse 0.0
            else
                0.0,
        };
    }

    fn currentRunSaltScalar(self: *const AppState) f32 {
        if (self.selected_level_record_override) |record| return record.salt_scalar;
        return switch (self.active_frontend_mode orelse .tutorial) {
            .challenge => challengeRuntimeHazardScalar(self.currentRunChallengeDifficultyValue()),
            .postal, .time_trial, .tutorial => if (self.current_level) |loaded_level|
                loaded_level.normalizedSaltScalar() orelse 0.0
            else
                0.0,
        };
    }

    fn currentParcelTarget(self: *const AppState) usize {
        if (self.current_track_preview) |preview| return preview.parcel_target_count;
        return if (self.current_level) |loaded_level|
            loaded_level.parcels orelse 0
        else
            0;
    }

    fn configureRuntimeParcels(self: *AppState, loaded_track_preview: *track.LoadedLevelPreview) !void {
        switch (self.active_frontend_mode orelse .tutorial) {
            .challenge => {
                const target_count = challengeParcelTargetCount(
                    self.currentRunChallengeSpeedValue(),
                    self.currentRunChallengeDifficultyScalar(),
                );
                _ = try loaded_track_preview.trimParcelAnnotationsToTarget(&self.math_random_state, target_count);
            },
            .postal, .time_trial, .tutorial => {},
        }
    }

    fn runtimeBuildFlagsForFrontendMode(mode: ?FrontendLevelMode) u32 {
        return frontendModeDispatch(mode).runtime_build_flags;
    }

    fn currentRunRuntimeBuildFlags(self: *const AppState) u32 {
        return if (self.current_track_preview) |preview|
            preview.runtime_build_flags
        else if (self.selected_level_record_override) |record|
            record.runtime_build_flags
        else
            runtimeBuildFlagsForFrontendMode(self.active_frontend_mode);
    }

    fn currentRunHighScoreEntry(self: *const AppState, score: u32) high_score.Entry {
        return .{
            .score = score,
            .replay_level_index = @intCast(self.active_frontend_level_index),
            .replay_mode_id = if (self.active_frontend_mode) |mode|
                @as(u32, @intCast(@intFromEnum(mode)))
            else
                0,
            .challenge_speed_value = self.currentRunChallengeSpeedValue(),
            .runtime_build_flags = self.currentRunRuntimeBuildFlags(),
            .replay_speed_scalar = self.currentRunReplaySpeedScalar(),
            .challenge_difficulty_value = self.currentRunChallengeDifficultyValue(),
            .challenge_difficulty_scalar = self.currentRunChallengeDifficultyScalar(),
            .runtime_build_seed = self.current_runtime_build_seed,
            .garbage_scalar = self.currentRunGarbageScalar(),
            .salt_scalar = self.currentRunSaltScalar(),
        };
    }

    fn saveHighScoreTables(self: *AppState) !void {
        try self.high_score_tables.saveToRuntimeRoot(self.allocator, self.runtime_root_path);
    }

    fn beginCompletedRunOverlay(self: *AppState) !void {
        if (self.pending_run_result != null) return;

        const loaded_level = self.current_level orelse return;
        const active_mode = self.active_frontend_mode;
        const parcel_target = self.currentParcelTarget();
        if (self.level_runner) |*runner| {
            if (completionBonusAppliesForMode(active_mode)) {
                runner.applyCompletionBonus(parcel_target);
            }
            runner.flushPendingParcelDeliveries();
        }
        const runner = self.level_runner orelse return;
        const parcel_count = runner.counters.parcels;
        const elapsed_millis = completionElapsedMillis(runner);
        var result = PendingRunResult{
            .outcome = .completed,
            .level_name = loaded_level.name,
            .mode = active_mode,
            .elapsed_millis = elapsed_millis,
            .parcel_count = parcel_count,
            .parcel_target = parcel_target,
            .score = 0,
            .score_is_partial = false,
            .score_totals = runner.score,
            .visible_life_stock = runner.visible_life_stock,
            .damage_gauge = runner.damage_gauge,
            .persistence = .completed,
            .return_target = resultReturnTargetForOutcome(.completed, active_mode),
        };

        switch (active_mode orelse .tutorial) {
            .postal => {
                result.score = runner.score.total;
                result.score_is_partial = true;
                const highest_available = self.highestAvailableFrontendRouteIndex(.postal);
                result.return_target = postalCompletionReturnTarget(
                    self.active_frontend_level_index,
                    highest_available,
                );
                // PORT(verified): normal postal completion uses `complete_subgame(..., 0)`,
                // not the arcade-high-score commit path. Only the last postal route upgrades
                // to `complete_subgame(..., 1)`, so keep postal score insertion gated on the
                // final shipped route instead of every completed delivery.
                if (postalCompletionCommitsHighScore(self.active_frontend_level_index, highest_available)) {
                    result.high_score_mode = .postal;
                    result.high_score_rank = previewDescendingHighScoreRank(self.high_score_tables.postal[0..], result.score);
                }
                result.unlocked_next_route = previewPostalRouteUnlock(
                    self.active_frontend_level_index,
                    highest_available,
                    @intCast(self.runtime_config.routeUnlockLimit()),
                );
            },
            .challenge => {
                result.score = runner.score.total;
                result.score_is_partial = true;
                result.high_score_mode = .challenge;
                result.high_score_rank = previewDescendingHighScoreRank(self.high_score_tables.challenge[0..], result.score);
            },
            .time_trial => {
                result.score = elapsed_millis;
                result.time_trial_record_improved = self.previewTimeTrialRecordImproved(
                    self.active_frontend_level_index,
                    elapsed_millis,
                );
            },
            .tutorial => result.persistence = .none,
        }

        self.applySelectedReplayResultOverrides(&result);

        self.pending_run_result = result;
        self.completion_overlay_active = true;
        self.preserve_completion_screen_reveal_on_enter = false;
        self.resetCompletionScreenReveal();
    }

    fn finalizeCompletedRunScreen(self: *AppState) !void {
        if (self.pending_run_result == null) {
            try self.beginCompletedRunOverlay();
        }
        if (self.pending_run_result == null) return;

        self.completion_overlay_active = false;
        self.preserve_completion_screen_reveal_on_enter = true;
        try self.enterGamePhase(.completion_screen);
    }

    fn beginFailedRun(self: *AppState, cause: gameplay.DeathCause) !void {
        _ = cause;
        if (self.pending_run_result != null) return;

        const loaded_level = self.current_level orelse return;
        const active_mode = self.active_frontend_mode;
        const parcel_target = self.currentParcelTarget();
        if (self.level_runner) |*runner| {
            runner.flushPendingParcelDeliveries();
        }
        const runner = self.level_runner orelse return;
        const elapsed_millis = completionElapsedMillis(runner);
        var result = PendingRunResult{
            .outcome = .failed,
            .level_name = loaded_level.name,
            .mode = active_mode,
            .elapsed_millis = elapsed_millis,
            .parcel_count = runner.counters.parcels,
            .parcel_target = parcel_target,
            .score = 0,
            .score_is_partial = true,
            .score_totals = runner.score,
            .visible_life_stock = runner.visible_life_stock,
            .damage_gauge = runner.damage_gauge,
            .persistence = .failed,
            .return_target = resultReturnTargetForOutcome(.failed, active_mode),
        };

        switch (active_mode orelse .tutorial) {
            .postal => {
                result.score = runner.score.total;
                result.high_score_mode = .postal;
                result.high_score_rank = previewDescendingHighScoreRank(self.high_score_tables.postal[0..], result.score);
            },
            .challenge => {
                result.score = runner.score.total;
                result.high_score_mode = .challenge;
                result.high_score_rank = previewDescendingHighScoreRank(self.high_score_tables.challenge[0..], result.score);
            },
            .time_trial => {
                // PORT(verified): `add_time_trial_high_score(..., success_flag)` only copies
                // failed runs into scratch memory. It does not replace the persistent ScoreC
                // route record unless the run completed successfully.
                result.score = elapsed_millis;
            },
            .tutorial => {
                result.score = runner.score.total;
                result.persistence = .none;
            },
        }

        self.applySelectedReplayResultOverrides(&result);

        self.pending_run_result = result;
        self.completion_overlay_active = false;
        self.preserve_completion_screen_reveal_on_enter = false;
        try self.enterGamePhase(.completion_screen);
    }

    fn beginRespawnRun(self: *AppState) !void {
        var previous_runner = self.level_runner orelse return;
        previous_runner.flushPendingParcelDeliveries();
        const preserved_session_mode = previous_runner.session_mode;
        const preserved_score = previous_runner.score;
        const preserved_visible_life_stock = previous_runner.visible_life_stock;
        const preserved_tick_count = previous_runner.tick_count;
        const preserved_stopwatch = previous_runner.stopwatch;
        const preserved_parcel_count = previous_runner.counters.parcels;
        const preserved_row_event_display = previous_runner.row_event_display;
        const preserved_collected_parcel_rows = previous_runner.collected_parcel_rows;
        const preserved_collected_parcel_row_count = previous_runner.collected_parcel_row_count;

        self.completion_overlay_active = false;
        self.preserve_completion_screen_reveal_on_enter = false;
        try self.reloadLevel();
        if (self.level_runner) |*runner| {
            runner.session_mode = preserved_session_mode;
            runner.score = preserved_score;
            runner.visible_life_stock = preserved_visible_life_stock;
            runner.tick_count = preserved_tick_count;
            runner.stopwatch = preserved_stopwatch;
            runner.counters.parcels = preserved_parcel_count;
            runner.row_event_display = preserved_row_event_display;
            runner.collected_parcel_rows = preserved_collected_parcel_rows;
            runner.collected_parcel_row_count = preserved_collected_parcel_row_count;
        }
        self.clearLevelPromptQueue();
        try self.syncActiveLevelSegment();
    }

    fn resetCompletionScreenReveal(self: *AppState) void {
        const result = self.pending_run_result orelse {
            self.completion_screen_reveal_progress = 0.0;
            return;
        };
        self.completion_screen_reveal_progress = if (result.outcome == .completed) 0.0 else completionRevealTarget(result);
    }

    fn completionScreenActive(self: *const AppState) bool {
        return self.pending_run_result != null and
            (self.game_phase == .completion_screen or self.completionScreenOverlayActive());
    }

    fn completionScreenOverlayActive(self: *const AppState) bool {
        return self.game_phase == .level and self.completion_overlay_active and self.pending_run_result != null;
    }

    fn completionScreenInteractive(self: *const AppState) bool {
        return self.game_phase == .completion_screen and
            self.pending_run_result != null and
            !self.frontend_transition.blocksInput();
    }

    fn stepCompletionScreenReveal(self: *AppState) void {
        if (!self.completionScreenActive()) return;
        const result = self.pending_run_result orelse return;
        const target = completionRevealTarget(result);
        if (self.completion_screen_reveal_progress >= target) return;
        self.completion_screen_reveal_progress = std.math.clamp(
            self.completion_screen_reveal_progress + completion_reveal_step,
            0.0,
            target,
        );
    }

    fn beginThanksScreenExit(self: *AppState) void {
        if (!self.thanks_screen_controller.allowsContinue()) return;
        self.frontend_transition.beginFadeOut(.main_menu);
    }

    fn completionBonusVisible(self: *const AppState, result: PendingRunResult) bool {
        return completionBonusVisibleAtProgress(result, self.completion_screen_reveal_progress);
    }

    fn completionContinueVisible(self: *const AppState) bool {
        const result = self.pending_run_result orelse return false;
        return completionContinueVisibleAtProgress(result, self.completion_screen_reveal_progress);
    }

    fn commitPendingRunResultIfNeeded(self: *AppState) !void {
        const result = self.pending_run_result orelse return;
        if (result.persistence == .none) return;

        var updated = result;
        switch (result.persistence) {
            .none => return,
            .completed => switch (result.mode orelse .tutorial) {
                .postal => {
                    if (postalCompletionCommitsHighScore(
                        self.active_frontend_level_index,
                        self.highestAvailableFrontendRouteIndex(.postal),
                    )) {
                        const entry = self.currentRunHighScoreEntry(result.score);
                        const insert = self.high_score_tables.addArcade(self.allocator, entry);
                        updated.high_score_mode = .postal;
                        updated.high_score_rank = insert.rank;
                        try self.saveHighScoreTables();
                    }
                    updated.unlocked_next_route = try self.commitPostalRouteProgress();
                },
                .challenge => {
                    const entry = self.currentRunHighScoreEntry(result.score);
                    const insert = self.high_score_tables.addSurvival(self.allocator, entry);
                    updated.high_score_mode = .challenge;
                    updated.high_score_rank = insert.rank;
                    try self.saveHighScoreTables();
                },
                .time_trial => {
                    const entry = self.currentRunHighScoreEntry(result.score);
                    const insert = self.high_score_tables.addTimeTrial(
                        self.allocator,
                        self.active_frontend_level_index,
                        entry,
                        true,
                    );
                    updated.time_trial_record_improved = insert.improved;
                    try self.saveHighScoreTables();
                },
                .tutorial => {},
            },
            .failed => switch (result.mode orelse .tutorial) {
                .postal => {
                    const entry = self.currentRunHighScoreEntry(result.score);
                    const insert = self.high_score_tables.addArcade(self.allocator, entry);
                    updated.high_score_mode = .postal;
                    updated.high_score_rank = insert.rank;
                    try self.saveHighScoreTables();
                },
                .challenge => {
                    const entry = self.currentRunHighScoreEntry(result.score);
                    const insert = self.high_score_tables.addSurvival(self.allocator, entry);
                    updated.high_score_mode = .challenge;
                    updated.high_score_rank = insert.rank;
                    try self.saveHighScoreTables();
                },
                .time_trial, .tutorial => {},
            },
        }
        updated.persistence = .none;
        self.pending_run_result = updated;
    }

    fn continueCompletionScreen(self: *AppState) !void {
        try self.commitPendingRunResultIfNeeded();
        if (self.postLevelHighScoreContext()) |context| {
            self.preparePostLevelHighScoreEntry();
            self.high_scores_menu_index = highScoreModeIndex(context.mode);
            try self.enterGamePhase(.high_scores_menu);
            return;
        }
        try self.finishPendingRunReturn();
    }

    fn cancelPostLevelHighScoreEntry(self: *AppState) !void {
        self.clearPostLevelHighScoreEntry();
        try self.finishPendingRunReturn();
    }

    fn finishPendingRunReturn(self: *AppState) !void {
        const result = self.pending_run_result orelse {
            self.completion_overlay_active = false;
            self.preserve_completion_screen_reveal_on_enter = false;
            try self.enterGamePhase(.main_menu);
            return;
        };
        self.clearPostLevelHighScoreEntry();
        self.pending_run_result = null;
        self.completion_overlay_active = false;
        self.preserve_completion_screen_reveal_on_enter = false;
        try self.dispatchOuterBridgeRequest(self.outerBridgeRequestForPendingRunResult(result));
    }

    fn postLevelHighScoreContext(self: *const AppState) ?PendingHighScoreEntry {
        const result = self.pending_run_result orelse return null;
        const mode = result.high_score_mode orelse return null;
        const rank = result.high_score_rank orelse return null;
        return .{
            .mode = mode,
            .rank = rank,
        };
    }

    fn preparePostLevelHighScoreEntry(self: *AppState) void {
        self.clearPostLevelHighScoreEntry();
        self.post_level_high_score_action_index = 1;

        const context = self.postLevelHighScoreContext() orelse return;
        const entry = self.highScoreEntry(context.mode, context.rank) orelse return;
        const existing_name = entry.name();
        const clipped = existing_name[0..@min(existing_name.len, self.post_level_high_score_name_buf.len)];
        @memcpy(self.post_level_high_score_name_buf[0..clipped.len], clipped);
        self.post_level_high_score_name_len = clipped.len;
    }

    fn clearPostLevelHighScoreEntry(self: *AppState) void {
        @memset(&self.post_level_high_score_name_buf, 0);
        self.post_level_high_score_name_len = 0;
        self.post_level_high_score_action_index = 1;
    }

    fn postLevelHighScoreDraft(self: *const AppState) []const u8 {
        return self.post_level_high_score_name_buf[0..self.post_level_high_score_name_len];
    }

    fn collectPostLevelHighScoreTextInput(self: *AppState) void {
        var codepoint = rl.getCharPressed();
        while (codepoint > 0) : (codepoint = rl.getCharPressed()) {
            if (codepoint < 0x20 or codepoint > 0x7e) continue;
            if (self.post_level_high_score_name_len >= high_score.compact_name_capacity) continue;

            const byte: u8 = @intCast(codepoint);
            const normalized = if (byte >= 'a' and byte <= 'z') std.ascii.toUpper(byte) else byte;
            self.post_level_high_score_name_buf[self.post_level_high_score_name_len] = normalized;
            self.post_level_high_score_name_len += 1;
        }

        if (rl.isKeyPressed(.backspace) and self.post_level_high_score_name_len > 0) {
            self.post_level_high_score_name_len -= 1;
            self.post_level_high_score_name_buf[self.post_level_high_score_name_len] = 0;
        }
    }

    fn submitPostLevelHighScore(self: *AppState) !void {
        if (self.pending_run_result == null) {
            try self.enterGamePhase(.main_menu);
            return;
        }
        const context = self.postLevelHighScoreContext() orelse {
            try self.finishPendingRunReturn();
            return;
        };
        const entry = self.highScoreEntryMut(context.mode, context.rank) orelse {
            try self.finishPendingRunReturn();
            return;
        };

        entry.setName(std.mem.trimRight(u8, self.postLevelHighScoreDraft(), " "));
        try self.saveHighScoreTables();
        try self.finishPendingRunReturn();
    }

    fn highScoreEntry(self: *const AppState, mode: high_score.Mode, index: usize) ?*const high_score.Entry {
        return switch (mode) {
            .postal => if (index < self.high_score_tables.postal.len) &self.high_score_tables.postal[index] else null,
            .challenge => if (index < self.high_score_tables.challenge.len) &self.high_score_tables.challenge[index] else null,
        };
    }

    fn highScoreEntryMut(self: *AppState, mode: high_score.Mode, index: usize) ?*high_score.Entry {
        return switch (mode) {
            .postal => if (index < self.high_score_tables.postal.len) &self.high_score_tables.postal[index] else null,
            .challenge => if (index < self.high_score_tables.challenge.len) &self.high_score_tables.challenge[index] else null,
        };
    }

    fn routeMapReplayEntry(self: *const AppState) ?*const high_score.Entry {
        const route_index = self.currentRouteMapOpenIndex() orelse return null;
        const completion_index = high_score.completionIndexForRouteIndex(route_index) orelse return null;
        return &self.high_score_tables.completion[completion_index];
    }

    fn selectedReplayEntryForSource(self: *const AppState, source: SelectedLevelRecordSource) ?*const high_score.Entry {
        return switch (source) {
            .postal => |index| if (index < self.high_score_tables.postal.len) &self.high_score_tables.postal[index] else null,
            .challenge => |index| if (index < self.high_score_tables.challenge.len) &self.high_score_tables.challenge[index] else null,
            .completion => |index| if (index < self.high_score_tables.completion.len) &self.high_score_tables.completion[index] else null,
        };
    }

    fn selectedReplayEntry(self: *const AppState) ?*const high_score.Entry {
        const source = self.selected_level_record_source orelse return null;
        return self.selectedReplayEntryForSource(source);
    }

    fn selectedReplayPlaybackActive(self: *const AppState) bool {
        if (self.selected_replay_cache) |replay| return replay.samples.len != 0;
        const entry = self.selectedReplayEntry() orelse return false;
        return entry.replaySampleCount() != 0;
    }

    fn replayMathType16To32(value: i16, scale: f32) f32 {
        return @as(f32, @floatFromInt(value)) * scale * (1.0 / 65536.0);
    }

    fn selectedReplayDirectiveForDecodedReplay(replay: *const high_score.DecodedReplay, runtime_track_index: usize) gameplay.ReplayDirective {
        if (replay.samples.len == 0) return .{};
        const sample = replay.sampleAt(runtime_track_index) orelse return .{ .active = true };
        return .{
            .active = true,
            .lateral_world_x = replayMathType16To32(sample.lateral, 16.0),
            .secondary_lane = sample.secondary_lane,
            .raw_flag_bits = sample.flags,
        };
    }

    fn selectedReplayDirectiveForRunner(self: *const AppState, runner: *const gameplay.Runner) gameplay.ReplayDirective {
        const replay = self.selected_replay_cache orelse return .{};
        return selectedReplayDirectiveForDecodedReplay(&replay, runner.runtime_track_index);
    }

    fn resultReturnTargetForSelectedReplaySource(source: SelectedLevelRecordSource) ResultReturnTarget {
        return switch (source) {
            .completion => .time_trial_route_map,
            .postal, .challenge => .high_scores_menu,
        };
    }

    fn applySelectedReplayResultOverrides(self: *const AppState, result: *PendingRunResult) void {
        if (!self.selectedReplayPlaybackActive()) return;
        result.persistence = .none;
        result.high_score_mode = null;
        result.high_score_rank = null;
        result.time_trial_record_improved = false;
        result.unlocked_next_route = false;
        if (self.selected_level_record_source) |source| {
            result.return_target = resultReturnTargetForSelectedReplaySource(source);
        }
    }

    fn exitSelectedReplayOnMarker(self: *AppState) !void {
        const source = self.selected_level_record_source orelse return;
        switch (source) {
            .completion => {
                self.start_route_index_override = self.active_frontend_level_index;
                try self.enterRouteMapMenu(.time_trial);
            },
            .postal => {
                try self.setSelectedLevelRecordContext(null, null);
                self.high_scores_menu_index = highScoreModeIndex(.postal);
                try self.enterGamePhase(.high_scores_menu);
            },
            .challenge => {
                try self.setSelectedLevelRecordContext(null, null);
                self.high_scores_menu_index = highScoreModeIndex(.challenge);
                try self.enterGamePhase(.high_scores_menu);
            },
        }
    }

    fn clearSelectedReplayCache(self: *AppState) void {
        if (self.selected_replay_cache) |*replay| {
            replay.deinit();
            self.selected_replay_cache = null;
        }
    }

    fn setSelectedLevelRecordContext(
        self: *AppState,
        selected_level_record_override: ?SelectedLevelRecordOverride,
        selected_level_record_source: ?SelectedLevelRecordSource,
    ) !void {
        self.clearSelectedReplayCache();
        self.selected_level_record_override = selected_level_record_override;
        self.selected_level_record_source = selected_level_record_source;
        self.selected_replay_fade_exit_pending = false;

        const source = selected_level_record_source orelse return;
        const entry = self.selectedReplayEntryForSource(source) orelse return;
        if (entry.replaySampleCount() == 0) return;
        self.selected_replay_cache = try entry.decodeReplay(self.allocator);
    }

    fn handleSelectedReplayFadeExit(self: *AppState) !bool {
        if (!self.selected_replay_fade_exit_pending) return false;

        switch (self.frontend_transition.state) {
            .idle => self.frontend_transition.beginOverlayFadeOut(),
            .black_idle => {
                self.selected_replay_fade_exit_pending = false;
                try self.exitSelectedReplayOnMarker();
                self.frontend_transition.completeHandoff();
            },
            else => {},
        }

        return true;
    }

    fn highScoreReplayEntry(self: *const AppState, entry_index: usize) ?*const high_score.Entry {
        const selected_mode = high_score_screen_modes[@min(self.high_scores_menu_index, high_score_screen_modes.len - 1)];
        return self.highScoreEntry(selected_mode, entry_index);
    }

    fn commitPostalRouteProgress(self: *AppState) !bool {
        const highest_available = self.highestAvailableFrontendRouteIndex(.postal);
        if (highest_available == 0) return false;

        const current_index = std.math.clamp(self.active_frontend_level_index, @as(usize, 1), highest_available);
        self.runtime_config.setRouteSelectionIndex(@intCast(current_index));

        const saved_limit: usize = @intCast(self.runtime_config.routeUnlockLimit());
        const next_unlock_limit = nextPostalUnlockLimit(current_index, highest_available, saved_limit);
        const unlocked = current_index < highest_available and next_unlock_limit > std.math.clamp(saved_limit, @as(usize, 1), highest_available);
        if (next_unlock_limit != saved_limit) {
            self.runtime_config.setRouteUnlockLimit(@intCast(next_unlock_limit));
        }
        if (unlocked) {
            self.setGameStatusMessage("Unlocked the next delivery route.");
        }
        try self.saveRuntimeConfig();
        return unlocked;
    }

    fn postalCompletionCommitsHighScore(current_index: usize, highest_available: usize) bool {
        if (highest_available == 0) return false;
        return current_index >= highest_available;
    }

    fn previewDescendingHighScoreRank(entries: []const high_score.Entry, score: u32) ?usize {
        const visible = @min(high_score.visible_entry_count, entries.len);
        var rank: usize = 0;
        while (rank < visible and score <= entries[rank].score and entries[rank].isActive()) : (rank += 1) {}
        if (rank >= visible) return null;
        return rank;
    }

    fn previewPostalRouteUnlock(current_index: usize, highest_available: usize, saved_limit: usize) bool {
        if (highest_available == 0) return false;
        const clamped_saved = std.math.clamp(saved_limit, @as(usize, 1), highest_available);
        const clamped_current = std.math.clamp(current_index, @as(usize, 1), highest_available);
        const next_unlock_limit = nextPostalUnlockLimit(clamped_current, highest_available, clamped_saved);
        return clamped_current < highest_available and next_unlock_limit > clamped_saved;
    }

    fn previewTimeTrialRecordImproved(self: *const AppState, route_index: usize, elapsed_millis: u32) bool {
        const completion_index = high_score.completionIndexForRouteIndex(route_index) orelse return false;
        const current = &self.high_score_tables.completion[completion_index];
        return !current.isActive() or elapsed_millis < current.score;
    }

    fn nextPostalUnlockLimit(current_index: usize, highest_available: usize, saved_limit: usize) usize {
        if (highest_available == 0) return 0;
        const clamped_saved = std.math.clamp(saved_limit, @as(usize, 1), highest_available);
        const clamped_current = std.math.clamp(current_index, @as(usize, 1), highest_available);
        if (clamped_current < highest_available) {
            return @max(clamped_saved, clamped_current + 1);
        }
        return clamped_saved;
    }

    fn initialFrontendRouteIndex(self: *const AppState, mode: FrontendLevelMode) usize {
        const available_limit = self.availableFrontendRouteLimit(mode);
        if (available_limit == 0) return 0;
        const saved_index: usize = @intCast(self.runtime_config.routeSelectionIndex());
        return std.math.clamp(saved_index, @as(usize, 1), available_limit);
    }

    fn availableFrontendRouteLimit(self: *const AppState, mode: FrontendLevelMode) usize {
        const highest_available = self.highestAvailableFrontendRouteIndex(mode);
        if (highest_available == 0) return 0;
        const saved_limit: usize = @intCast(self.runtime_config.routeUnlockLimit());
        return std.math.clamp(saved_limit, @as(usize, 1), highest_available);
    }

    fn highestAvailableFrontendRouteIndex(self: *const AppState, mode: FrontendLevelMode) usize {
        switch (mode) {
            .postal => {
                if (self.catalog.findLevelIndex("LEVELS/ARCADEEXTRA000.TXT") != null) return 0x33;
                return 0x32;
            },
            .time_trial => {
                var scratch: [64]u8 = undefined;
                var last_index: usize = 0x32;
                var extra_index: usize = 0x33;
                while (extra_index < 0x80) : (extra_index += 1) {
                    const path = frontendLevelPath(.time_trial, extra_index, &scratch) catch break;
                    if (self.catalog.findLevelIndex(path) == null) break;
                    last_index = extra_index;
                }
                return last_index;
            },
            .challenge, .tutorial => return 0,
        }
    }

    fn stepFrontendRouteSelection(self: *AppState, delta: isize) !void {
        const mode = self.frontend_route_mode orelse return;
        const route_count = self.availableFrontendRouteLimit(mode);
        if (route_count == 0) return;
        const next_route_index = wrappedIndex(route_count, self.frontend_route_index - 1, delta) + 1;
        try self.openFrontendRouteCard(next_route_index);
    }

    fn syncGamePhaseResources(self: *AppState) !void {
        switch (self.game_phase) {
            .level, .pause_menu => {},
            else => self.stopVoicePlayback(),
        }
        switch (self.game_phase) {
            .boot => {
                self.stopAudioPreview();
                self.active_level_segment_index = null;
                self.clearLevelPromptQueue();
                self.mouse_level_lane_target = null;
                self.boot_task_index = 0;
                self.unloadPreloadedBootAssets();
                self.unloadTextScript();
                self.unloadGameBackground();
                try self.loadLoadingScreen();
            },
            .intro => {
                self.active_level_segment_index = null;
                self.clearLevelPromptQueue();
                self.mouse_level_lane_target = null;
                self.unloadLoadingScreen();
                try self.loadGameBackground(intro_background_path);
                try self.playMusicByPath(intro_music_path);
                try self.loadTextScript(intro_script_path);
            },
            .main_menu, .new_game_menu, .high_scores_menu => {
                self.active_level_segment_index = null;
                self.clearLevelPromptQueue();
                self.mouse_level_lane_target = null;
                self.unloadTextScript();
                self.unloadLoadingScreen();
                try self.loadGameBackground(main_menu_background_path);
                try self.playMusicByPath(default_audio_path);
            },
            .options_menu => {
                self.options_sound_display_value = self.runtime_config.soundVolume();
                self.options_music_display_value = self.runtime_config.musicVolume();
                self.unloadTextScript();
                self.unloadLoadingScreen();
                if (self.options_return_phase == .pause_menu) {
                    try self.loadCurrentLevelBackground();
                } else {
                    self.active_level_segment_index = null;
                    self.clearLevelPromptQueue();
                    self.mouse_level_lane_target = null;
                    try self.loadGameBackground(main_menu_background_path);
                    try self.playMusicByPath(default_audio_path);
                }
            },
            .pause_menu => {
                self.unloadTextScript();
                self.unloadLoadingScreen();
                try self.loadCurrentLevelBackground();
            },
            .route_map_menu => {
                self.active_level_segment_index = null;
                self.clearLevelPromptQueue();
                self.mouse_level_lane_target = null;
                self.unloadTextScript();
                self.unloadLoadingScreen();
                try self.loadGameBackground(route_map_background_path);
                try self.playMusicByPath(default_audio_path);
            },
            .credits => {
                self.active_level_segment_index = null;
                self.clearLevelPromptQueue();
                self.mouse_level_lane_target = null;
                self.unloadLoadingScreen();
                try self.loadGameBackground(intro_background_path);
                try self.playMusicByPath(intro_music_path);
                try self.loadTextScript(credits_script_path);
            },
            .help => {
                self.active_level_segment_index = null;
                self.clearLevelPromptQueue();
                self.mouse_level_lane_target = null;
                self.unloadTextScript();
                self.unloadLoadingScreen();
                try self.loadGameBackground(help_background_path);
                try self.playMusicByPath(default_audio_path);
            },
            .exit_prompt => {
                self.unloadTextScript();
                self.unloadLoadingScreen();
                if (self.exit_prompt_return_phase == .pause_menu) {
                    try self.loadCurrentLevelBackground();
                } else if (self.exit_prompt_return_phase == .route_map_menu) {
                    self.active_level_segment_index = null;
                    self.clearLevelPromptQueue();
                    self.mouse_level_lane_target = null;
                    try self.loadGameBackground(route_map_background_path);
                    try self.playMusicByPath(default_audio_path);
                } else {
                    self.active_level_segment_index = null;
                    self.clearLevelPromptQueue();
                    self.mouse_level_lane_target = null;
                    try self.loadGameBackground(main_menu_background_path);
                    try self.playMusicByPath(default_audio_path);
                }
            },
            .completion_screen => {
                if (self.preserve_completion_screen_reveal_on_enter) {
                    self.preserve_completion_screen_reveal_on_enter = false;
                } else {
                    self.resetCompletionScreenReveal();
                }
                self.clearLevelPromptQueue();
                self.mouse_level_lane_target = null;
                self.unloadTextScript();
                self.unloadLoadingScreen();
                try self.loadCurrentLevelBackground();
            },
            .thanks_screen => {
                self.thanks_screen_controller.reset();
                self.active_level_segment_index = null;
                self.clearLevelPromptQueue();
                self.mouse_level_lane_target = null;
                self.unloadTextScript();
                self.unloadLoadingScreen();
                try self.loadGameBackground(thanks_screen_background_path);
                try self.playMusicByPath(intro_music_path);
            },
            .level => {
                self.stopAudioPreview();
                self.clearLevelPromptQueue();
                self.mouse_level_lane_target = null;
                self.unloadTextScript();
                self.unloadLoadingScreen();
                try self.loadCurrentLevelBackground();
                const previous_active_level_segment_index = self.active_level_segment_index;
                try self.syncActiveLevelSegment();
                try self.dispatchCurrentRunnerRowMessage(previous_active_level_segment_index, null, true);
            },
        }
    }

    fn loadGameLevel(self: *AppState, level_path: []const u8) !void {
        self.level_index = self.catalog.findLevelIndex(level_path) orelse return error.EntryNotFound;
        self.invalidateTrackBuildSeed();
        try self.reloadLevel();
    }

    fn playMusicByPath(self: *AppState, path: []const u8) !void {
        if (!self.audio_ready) return;
        if (self.current_music) |music| {
            if (std.ascii.eqlIgnoreCase(music.path, path)) {
                self.applyAudioConfigVolumes();
                if (!rl.isMusicStreamPlaying(music.music)) {
                    rl.playMusicStream(music.music);
                }
                return;
            }
        }

        self.stopAudioPreview();
        self.current_music = if (self.takePreloadedMusic(path)) |music|
            music
        else
            try self.catalog.loadMusicByPath(self.allocator, path);
        self.applyAudioConfigVolumes();
        rl.playMusicStream(self.current_music.?.music);
    }

    fn playSoundByPath(self: *AppState, path: []const u8) !void {
        if (!self.audio_ready) return;
        if (self.current_sound) |*sound| {
            sound.unload();
            self.current_sound = null;
        }

        self.current_sound = try self.catalog.loadSoundByPath(self.allocator, path);
        self.applyAudioConfigVolumes();
        rl.playSound(self.current_sound.?.sound);
    }

    fn playVoiceByPath(self: *AppState, path: []const u8) !void {
        if (!self.audio_ready) return;
        self.stopVoicePlayback();
        self.current_voice_sound = try self.catalog.loadSoundByPath(self.allocator, path);
        self.applyAudioConfigVolumes();
        rl.playSound(self.current_voice_sound.?.sound);
    }

    fn tryPlayNativeGameplayVoiceSet(self: *AppState, set_id: NativeGameplayVoiceSet, mode: NativeGameplayVoiceMode) !void {
        _ = try self.tryPlayNativeGameplayVoiceSetPlayed(set_id, mode);
    }

    fn tryPlayNativeGameplayVoiceSetPlayed(self: *AppState, set_id: NativeGameplayVoiceSet, mode: NativeGameplayVoiceMode) !bool {
        if (!self.audio_ready) return false;
        const paths = nativeGameplayVoicePaths(set_id);
        if (paths.len == 0) return false;

        const sample_index = self.native_gameplay_voice_manager.requestPlay(
            set_id,
            mode,
            self.gameplayVoiceBusy(),
            paths.len,
        ) orelse return false;
        try self.playVoiceByPath(paths[sample_index]);
        return true;
    }

    fn tryPlayNativeGameplayVoicePayload(self: *AppState, set_id: NativeGameplayVoiceSet, mode: NativeGameplayVoiceMode, payload_index: usize) !bool {
        if (!self.audio_ready) return false;

        const sample_index = self.native_gameplay_voice_manager.requestPayloadPlay(
            set_id,
            mode,
            self.gameplayVoiceBusy(),
            payload_index,
        ) orelse return false;
        const sample_path = nativeGlobalAudioSamplePath(sample_index) orelse return false;
        try self.playVoiceByPath(sample_path);
        return true;
    }

    fn gameplayVoiceBusy(self: *const AppState) bool {
        if (self.current_voice_sound) |sound| {
            return rl.isSoundPlaying(sound.sound);
        }
        return false;
    }

    fn tryPlayGameplayVoiceVariant(self: *AppState, comptime count: usize, variants: [count][]const u8) !void {
        if (!self.audio_ready) return;
        if (self.gameplay_click_start_active) return;
        if (self.level_prompt_queue.active() != null) return;
        if (self.gameplay_voice_manager.active) return;
        if (self.gameplayVoiceBusy()) return;

        const index = self.nextGameplaySoundVariantIndex(count);
        try self.playVoiceByPath(variants[index]);
        self.gameplay_voice_manager.arm();
    }

    fn gameplaySlugVoiceCellAnnounced(self: *const AppState, row: usize, lane: usize) bool {
        for (0..self.announced_slug_voice_cell_count) |index| {
            const announced = self.announced_slug_voice_cells[index];
            if (announced.row == row and announced.lane == lane) return true;
        }
        return false;
    }

    fn noteGameplaySlugVoiceCell(self: *AppState, row: usize, lane: usize) void {
        if (self.gameplaySlugVoiceCellAnnounced(row, lane)) return;
        if (self.announced_slug_voice_cell_count >= self.announced_slug_voice_cells.len) return;
        self.announced_slug_voice_cells[self.announced_slug_voice_cell_count] = .{ .row = row, .lane = lane };
        self.announced_slug_voice_cell_count += 1;
    }

    fn updateGameplayAmbientVoices(self: *AppState, runner: gameplay.Runner, preview: *const track.LoadedLevelPreview) void {
        if (!self.isTutorialGameplay()) return;
        if (runner.paused or self.gameplay_click_start_active) return;
        if (self.level_prompt_queue.active() != null) return;
        if (self.gameplay_voice_manager.active or self.gameplayVoiceBusy()) return;

        const current_row_floor = @as(usize, @intFromFloat(@floor(runner.row_position)));
        const bark_row_limit = @min(preview.total_rows, current_row_floor + 2);
        var row = current_row_floor;
        while (row < bark_row_limit) : (row += 1) {
            for (0..preview.max_width) |lane| {
                if (runner.isSlugDefeated(row, lane)) continue;
                const sample = preview.gameplayCellSampleAt(row, lane) orelse continue;
                if (sample.kind != .slug) continue;
                if (self.gameplaySlugVoiceCellAnnounced(row, lane)) continue;

                self.noteGameplaySlugVoiceCell(row, lane);
                if (deterministicGameplayAmbientSlugRoll(row, lane) > 0.6) {
                    self.tryPlayGameplayVoiceVariant(
                        gameplay_slug_ambient_voice_paths.len,
                        gameplay_slug_ambient_voice_paths,
                    ) catch {};
                }
                return;
            }
        }
    }

    fn playGameplayEffect(self: *AppState, sound: ?assets.LoadedSound) void {
        if (!self.audio_ready) return;
        const loaded = sound orelse return;
        rl.playSound(loaded.sound);
    }

    fn gameplaySoundBaseVolume(self: *const AppState) f32 {
        return if (self.audio_muted) 0.0 else self.runtime_config.soundVolume();
    }

    fn playGameplayEffectScaled(self: *AppState, sound: ?assets.LoadedSound, gain: f32) void {
        if (!self.audio_ready) return;
        const loaded = sound orelse return;
        const base_volume = self.gameplaySoundBaseVolume();
        const scaled_volume = std.math.clamp(base_volume * gain, 0.0, 1.0);
        rl.setSoundVolume(loaded.sound, scaled_volume);
        rl.playSound(loaded.sound);
        rl.setSoundVolume(loaded.sound, base_volume);
    }

    fn nextGameplaySoundVariantIndex(self: *AppState, comptime count: usize) usize {
        const index = @as(usize, @intCast(self.gameplay_audio_variant_counter % count));
        self.gameplay_audio_variant_counter +%= 1;
        return index;
    }

    fn nextNativeMovementStateVariantIndex(self: *AppState, comptime count: usize) usize {
        return nativeMovementStateVariantIndexForSample(self.nextMathRandomInt15(), count);
    }

    fn pickGameplaySoundVariant(self: *AppState, comptime count: usize, variants: [count]?assets.LoadedSound) ?assets.LoadedSound {
        var start = self.nextGameplaySoundVariantIndex(count);
        var remaining = count;
        while (remaining > 0) : (remaining -= 1) {
            if (variants[start]) |loaded| return loaded;
            start = (start + 1) % count;
        }
        return null;
    }

    fn pickNativeMovementStateSoundVariant(self: *AppState, comptime count: usize, variants: [count]?assets.LoadedSound) ?assets.LoadedSound {
        var start = self.nextNativeMovementStateVariantIndex(count);
        var remaining = count;
        while (remaining > 0) : (remaining -= 1) {
            if (variants[start]) |loaded| return loaded;
            start = (start + 1) % count;
        }
        return null;
    }

    fn syncActiveLevelSegment(self: *AppState) !void {
        _ = self.current_level orelse {
            self.active_level_segment_index = null;
            self.clearLevelPromptQueue();
            return;
        };
        const logical_segment_index = self.currentRunnerRowMessageSegmentIndex() orelse {
            self.active_level_segment_index = null;
            self.clearLevelPromptQueue();
            return;
        };

        self.level_segment_index = logical_segment_index;
        const previous_segment_index = self.active_level_segment_index;
        const segment_changed = previous_segment_index == null or previous_segment_index.? != logical_segment_index;
        self.active_level_segment_index = logical_segment_index;
        if (segment_changed) {
            if (previous_segment_index) |previous_index| {
                if (logical_segment_index < previous_index) {
                    self.clearLevelPromptQueue();
                }
            }
        }
    }

    fn loadCurrentLevelBackground(self: *AppState) !void {
        const loaded_level = self.current_level orelse {
            self.unloadGameBackground();
            return;
        };
        const background_name = loaded_level.background orelse {
            self.unloadGameBackground();
            return;
        };

        var path_buffer: [256]u8 = undefined;
        const script_path = try std.fmt.bufPrint(&path_buffer, "BACKGROUNDS/{s}", .{background_name});
        try self.loadGameBackground(script_path);
    }

    fn loadGameBackground(self: *AppState, script_path: []const u8) !void {
        self.unloadGameBackground();
        var loaded = if (self.takePreloadedBackground(script_path)) |loaded|
            loaded
        else
            try background.Loaded.loadByPath(self.allocator, &self.catalog, script_path);
        self.current_game_background_runtime = background.Runtime.init(&loaded);
        self.current_game_background = loaded;
    }

    fn loadLoadingScreen(self: *AppState) !void {
        self.unloadLoadingScreen();
        self.current_loading_screen = try loading_screen.Loaded.load(self.allocator, &self.catalog);
    }

    fn loadTextScript(self: *AppState, path: []const u8) !void {
        self.unloadTextScript();
        self.current_text_script = if (self.takePreloadedTextScript(path)) |loaded|
            loaded
        else
            try self.loadConfiguredTextScriptEntry(path);
    }

    fn loadConfiguredTextScriptEntry(self: *AppState, path: []const u8) !intro.Loaded {
        if (std.ascii.eqlIgnoreCase(path, credits_script_path)) {
            return try intro.loadByPathWithOptions(
                self.allocator,
                &self.catalog,
                path,
                .{ .add_remake_credit = self.credits_with_remake },
            );
        }
        return try intro.loadByPath(self.allocator, &self.catalog, path);
    }

    fn unloadTextScript(self: *AppState) void {
        if (self.current_text_script) |*script| {
            script.deinit(self.allocator);
            self.current_text_script = null;
        }
    }

    fn unloadLoadingScreen(self: *AppState) void {
        if (self.current_loading_screen) |*loaded_screen| {
            loaded_screen.deinit();
            self.current_loading_screen = null;
        }
    }

    fn takePreloadedBackground(self: *AppState, script_path: []const u8) ?background.Loaded {
        if (std.ascii.eqlIgnoreCase(script_path, intro_background_path)) {
            return takeOptional(background.Loaded, &self.preloaded_intro_background);
        }
        if (std.ascii.eqlIgnoreCase(script_path, main_menu_background_path)) {
            return takeOptional(background.Loaded, &self.preloaded_main_menu_background);
        }
        if (std.ascii.eqlIgnoreCase(script_path, route_map_background_path)) {
            return takeOptional(background.Loaded, &self.preloaded_route_map_background);
        }
        if (std.ascii.eqlIgnoreCase(script_path, help_background_path)) {
            return takeOptional(background.Loaded, &self.preloaded_help_background);
        }
        return null;
    }

    fn takePreloadedTextScript(self: *AppState, path: []const u8) ?intro.Loaded {
        if (std.ascii.eqlIgnoreCase(path, intro_script_path)) {
            return takeOptional(intro.Loaded, &self.preloaded_intro_script);
        }
        if (std.ascii.eqlIgnoreCase(path, credits_script_path)) {
            return takeOptional(intro.Loaded, &self.preloaded_credits_script);
        }
        return null;
    }

    fn takePreloadedMusic(self: *AppState, path: []const u8) ?assets.LoadedMusic {
        if (std.ascii.eqlIgnoreCase(path, intro_music_path)) {
            return takeOptional(assets.LoadedMusic, &self.preloaded_intro_music);
        }
        if (std.ascii.eqlIgnoreCase(path, default_audio_path)) {
            return takeOptional(assets.LoadedMusic, &self.preloaded_menu_music);
        }
        return null;
    }

    fn currentTextScriptDurationTicks(self: *const AppState) ?u64 {
        const script = self.current_text_script orelse return null;
        return script.durationTicks();
    }

    fn applyAudioConfigVolumes(self: *AppState) void {
        if (!self.audio_ready) return;

        const sound_volume = if (self.audio_muted) 0.0 else self.runtime_config.soundVolume();
        const music_volume = if (self.audio_muted) 0.0 else self.runtime_config.musicVolume();

        if (self.current_sound) |sound| {
            rl.setSoundVolume(sound.sound, sound_volume);
        }
        if (self.current_voice_sound) |sound| {
            rl.setSoundVolume(sound.sound, sound_volume);
        }
        if (self.frontend_sound_fx.highlight) |sound| {
            rl.setSoundVolume(sound.sound, sound_volume);
        }
        if (self.frontend_sound_fx.select) |sound| {
            rl.setSoundVolume(sound.sound, sound_volume);
        }
        inline for (comptime std.meta.fieldNames(GameplaySoundFx)) |field_name| {
            const field = &@field(self.current_gameplay_sound_fx, field_name);
            switch (@typeInfo(@TypeOf(field.*))) {
                .array => {
                    for (field) |entry| {
                        if (entry) |sound| {
                            rl.setSoundVolume(sound.sound, sound_volume);
                        }
                    }
                },
                else => {
                    if (field.*) |sound| {
                        rl.setSoundVolume(sound.sound, sound_volume);
                    }
                },
            }
        }
        if (self.current_music) |music| {
            rl.setMusicVolume(music.music, music_volume);
        }
    }

    fn toggleFullscreenPreference(self: *AppState) void {
        self.runtime_config.setFullscreenEnabled(!self.runtime_config.fullscreenEnabled());
        self.syncWindowFullscreenPreference();
    }

    fn syncWindowFullscreenPreference(self: *AppState) void {
        const want_fullscreen = self.runtime_config.fullscreenEnabled();
        const is_fullscreen = rl.isWindowFullscreen();
        if (want_fullscreen == is_fullscreen) return;

        rl.toggleFullscreen();
        if (!want_fullscreen) {
            rl.setWindowSize(self.window_size.width, self.window_size.height);
        }
    }

    fn stepOptionsMenuValue(self: *AppState, item: OptionsMenuItem, delta: f32) !void {
        switch (item) {
            .fullscreen => {
                if (delta != 0.0) {
                    self.playFrontendSelectSound();
                    self.toggleFullscreenPreference();
                }
            },
            .sound_volume => {
                const previous = self.runtime_config.soundVolume();
                self.runtime_config.setSoundVolume(self.runtime_config.soundVolume() + delta);
                self.applyAudioConfigVolumes();
                if (self.runtime_config.soundVolume() != previous) {
                    self.playFrontendSelectSound();
                }
            },
            .music_volume => {
                self.runtime_config.setMusicVolume(self.runtime_config.musicVolume() + delta);
                self.applyAudioConfigVolumes();
            },
            .back => if (delta != 0.0) {
                self.playFrontendSelectSound();
                try self.leaveOptionsMenu();
            },
        }
    }

    fn stepOptionsSliderDisplay(current: f32, target: f32) f32 {
        const next = current + (target - current) * options_slider_display_lerp;
        if (@abs(target - next) < 0.001) return target;
        return next;
    }

    fn currentTextScriptProgress(self: *const AppState) ?f32 {
        const script = self.currentTextScript() orelse return null;
        return script.progressForTicks(self.game_phase_ticks);
    }

    fn currentTextScript(self: *const AppState) ?*const intro.Loaded {
        if (self.current_text_script) |*script| {
            return script;
        }
        return null;
    }

    fn maybeQueueAutoScreenshot(self: *AppState) !void {
        const auto_screenshot = self.auto_screenshot orelse return;
        if (self.auto_screenshot_taken) return;
        if (self.game_phase != auto_screenshot.phase) return;
        if (self.game_phase_ticks < auto_screenshot.tick) return;

        self.auto_screenshot_taken = true;
        try self.queueScreenshot(true);
    }

    fn queueScreenshot(self: *AppState, exit_after_capture: bool) !void {
        if (self.pending_screenshot != null) return;

        self.frame_capture_index += 1;
        const relative_path = try std.fmt.allocPrint(
            self.allocator,
            "{s}/snail-{s}-{s}-{d:0>6}-{d:0>3}.png",
            .{
                self.screenshot_dir,
                @tagName(self.command),
                @tagName(self.game_phase),
                self.game_phase_ticks,
                self.frame_capture_index,
            },
        );
        errdefer self.allocator.free(relative_path);
        const relative_path_z = try self.allocator.dupeZ(u8, relative_path);
        defer self.allocator.free(relative_path);
        errdefer self.allocator.free(relative_path_z);

        self.pending_screenshot = .{
            .relative_path_z = relative_path_z,
            .exit_after_capture = exit_after_capture,
        };
    }

    fn flushQueuedScreenshot(self: *AppState) !void {
        var request = self.pending_screenshot orelse return;
        self.pending_screenshot = null;
        defer request.deinit(self.allocator);

        var screenshot = if (self.command == .game and frontendPhaseUsesCanvas(self) and self.frontend_canvas != null)
            try rl.loadImageFromTexture(self.frontend_canvas.?.texture)
        else
            try rl.loadImageFromScreen();
        defer screenshot.unload();
        if (self.command == .game and frontendPhaseUsesCanvas(self) and self.frontend_canvas != null) {
            screenshot.flipVertical();
        }
        if (!rl.exportImage(screenshot, request.relative_path_z)) {
            return error.ScreenshotExportFailed;
        }
        std.log.info("captured screenshot {s}", .{request.relative_path_z});

        if (request.exit_after_capture) {
            self.should_exit = true;
        }
    }

    fn unloadGameBackground(self: *AppState) void {
        if (self.current_game_background) |*loaded_background| {
            loaded_background.deinit();
            self.current_game_background = null;
        }
        self.current_game_background_runtime = null;
    }

    fn setGameStatusMessage(self: *AppState, message: []const u8) void {
        self.game_status_message = message;
        self.game_status_ticks = status_message_duration_ticks;
    }

    fn setMode(self: *AppState, mode: Mode) !void {
        if (self.mode == mode) return;

        if (self.mode == .audio) {
            self.stopAudioPreview();
        }
        self.mode = mode;
    }

    fn stepSelection(self: *AppState, delta: isize) !void {
        switch (self.mode) {
            .textures => {
                self.texture_index = wrappedIndex(self.catalog.texture_entries.len, self.texture_index, delta);
                try self.reloadTexture();
            },
            .audio => {
                self.stopAudioPreview();
                self.audio_index = wrappedIndex(self.catalog.audio_entries.len, self.audio_index, delta);
            },
            .models => {
                self.model_index = wrappedIndex(self.catalog.model_entries.len, self.model_index, delta);
                try self.reloadModel();
            },
            .objects => {
                self.object_index = wrappedIndex(self.catalog.object_entries.len, self.object_index, delta);
                try self.reloadObject();
            },
            .levels => {},
            .segments => {
                self.segment_index = wrappedIndex(self.catalog.segment_entries.len, self.segment_index, delta);
                try self.reloadStandaloneSegment();
            },
            .streaks => {},
        }
    }

    fn handleDebugLightStreakInput(self: *AppState) void {
        if (rl.isKeyPressed(.space)) {
            self.debug_light_streak_view.paused = !self.debug_light_streak_view.paused;
        }
        if (rl.isKeyPressed(.n)) {
            self.debug_light_streak_view.stepOnce();
        }
        if (rl.isKeyPressed(.r)) {
            self.debug_light_streak_view.reset();
        }
        if (rl.isKeyPressed(.h)) {
            self.debug_light_streak_view.visible_requested = !self.debug_light_streak_view.visible_requested;
        }
        if (rl.isKeyPressed(.t)) {
            self.debug_light_streak_view.show_textured = !self.debug_light_streak_view.show_textured;
        }
        if (rl.isKeyPressed(.l)) {
            self.debug_light_streak_view.show_lines = !self.debug_light_streak_view.show_lines;
        }
        if (rl.isKeyPressed(.q)) {
            self.debug_light_streak_view.alpha_multiplier = std.math.clamp(self.debug_light_streak_view.alpha_multiplier - 0.25, 0.0, 16.0);
        }
        if (rl.isKeyPressed(.e)) {
            self.debug_light_streak_view.alpha_multiplier = std.math.clamp(self.debug_light_streak_view.alpha_multiplier + 0.25, 0.0, 16.0);
        }
        if (rl.isKeyPressed(.z)) {
            self.debug_light_streak_view.size_multiplier = std.math.clamp(self.debug_light_streak_view.size_multiplier - 0.25, 0.0, 16.0);
        }
        if (rl.isKeyPressed(.x)) {
            self.debug_light_streak_view.size_multiplier = std.math.clamp(self.debug_light_streak_view.size_multiplier + 0.25, 0.0, 16.0);
        }
        if (rl.isKeyPressed(.c)) {
            self.debug_light_streak_view.stretch_multiplier = std.math.clamp(self.debug_light_streak_view.stretch_multiplier - 0.25, 0.0, 16.0);
        }
        if (rl.isKeyPressed(.v)) {
            self.debug_light_streak_view.stretch_multiplier = std.math.clamp(self.debug_light_streak_view.stretch_multiplier + 0.25, 0.0, 16.0);
        }
        if (rl.isKeyPressed(.a)) {
            self.debug_light_streak_view.camera_yaw_degrees -= 5.0;
        }
        if (rl.isKeyPressed(.d)) {
            self.debug_light_streak_view.camera_yaw_degrees += 5.0;
        }
        if (rl.isKeyPressed(.w)) {
            self.debug_light_streak_view.camera_pitch_degrees = std.math.clamp(self.debug_light_streak_view.camera_pitch_degrees + 5.0, -85.0, 85.0);
        }
        if (rl.isKeyPressed(.s)) {
            self.debug_light_streak_view.camera_pitch_degrees = std.math.clamp(self.debug_light_streak_view.camera_pitch_degrees - 5.0, -85.0, 85.0);
        }
        if (rl.isKeyPressed(.f)) {
            self.debug_light_streak_view.camera_fov_degrees = std.math.clamp(self.debug_light_streak_view.camera_fov_degrees - 5.0, 30.0, 160.0);
        }
        if (rl.isKeyPressed(.g)) {
            self.debug_light_streak_view.camera_fov_degrees = std.math.clamp(self.debug_light_streak_view.camera_fov_degrees + 5.0, 30.0, 160.0);
        }
    }

    fn stepLevelSegment(self: *AppState, delta: isize) !void {
        const loaded_level = self.current_level orelse return;
        self.level_segment_index = wrappedIndex(loaded_level.segments.len, self.level_segment_index, delta);
        try self.reloadLevelSegment();
    }

    fn previewSound(self: *AppState) !void {
        if (!self.audio_ready or self.catalog.audio_entries.len == 0) {
            return;
        }

        self.stopAudioPreview();
        const sound = try self.catalog.loadSound(self.allocator, self.catalog.audio_entries[self.audio_index]);
        self.current_sound = sound;
        self.applyAudioConfigVolumes();
        rl.playSound(self.current_sound.?.sound);
    }

    fn previewMusic(self: *AppState) !void {
        if (!self.audio_ready or self.catalog.audio_entries.len == 0) {
            return;
        }

        self.stopAudioPreview();
        const music = try self.catalog.loadMusic(self.allocator, self.catalog.audio_entries[self.audio_index]);
        self.current_music = music;
        self.applyAudioConfigVolumes();
        rl.playMusicStream(self.current_music.?.music);
    }

    fn stopAudioPreview(self: *AppState) void {
        if (self.current_sound) |*sound| {
            sound.unload();
            self.current_sound = null;
        }
        if (self.current_music) |*music| {
            music.unload();
            self.current_music = null;
        }
    }

    fn stopVoicePlayback(self: *AppState) void {
        if (self.current_voice_sound) |*sound| {
            sound.unload();
            self.current_voice_sound = null;
        }
    }

    fn reloadTexture(self: *AppState) !void {
        if (self.current_texture) |*texture| {
            texture.unload();
            self.current_texture = null;
        }

        const texture = try self.catalog.loadTexture(self.allocator, self.catalog.texture_entries[self.texture_index]);
        self.current_texture = texture;
    }

    fn reloadModel(self: *AppState) !void {
        if (self.current_model) |*model| {
            model.deinit();
            self.current_model = null;
        }
        if (self.current_animation) |*animation| {
            animation.deinit();
            self.current_animation = null;
        }

        const entry = self.catalog.model_entries[self.model_index];
        if (self.animation_catalog.findClipIndexForModelPath(entry.path)) |clip_index| {
            const clip = &self.animation_catalog.clips[clip_index];
            if (clip.frames.len > 1) {
                const animation = try xanim.Player.load(
                    self.allocator,
                    &self.catalog,
                    clip,
                    self.model_flip_v,
                    xanim.frameNumberFromPath(entry.path),
                );
                self.current_animation = animation;
                return;
            }
        }

        self.current_model = try x2.Uploaded.loadFromArchive(
            self.allocator,
            &self.catalog,
            entry,
            self.model_flip_v,
        );
    }

    fn reloadObject(self: *AppState) !void {
        if (self.current_object) |*loaded_object| {
            loaded_object.deinit();
            self.current_object = null;
        }
        if (self.catalog.object_entries.len == 0) return;

        const entry = self.catalog.object_entries[self.object_index];
        self.current_object = try object.LoadedObject.loadFromArchive(
            self.allocator,
            &self.catalog,
            entry,
            self.object_flip_v,
        );
    }

    fn reloadLevel(self: *AppState) !void {
        const seed_intro_cutscene = self.command == .game and self.seed_level_intro_cutscene;
        self.seed_level_intro_cutscene = false;
        if (self.current_level) |*loaded_level| {
            loaded_level.deinit();
            self.current_level = null;
        }
        if (self.current_segment) |*loaded_segment| {
            loaded_segment.deinit();
            self.current_segment = null;
        }
        if (self.current_track_preview) |*loaded_track_preview| {
            loaded_track_preview.deinit();
            self.current_track_preview = null;
        }
        if (self.current_game_track_scene) |*scene| {
            scene.deinit();
            self.current_game_track_scene = null;
        }
        self.unloadGameplayTurbo();
        self.unloadGameplayBarrier();
        self.unloadGameplayLazer();
        self.unloadGameplaySalt();
        self.unloadGameplayActorModels();
        self.unloadGameplaySprites();
        self.unloadGameplaySoundFx();
        self.active_gameplay_effect_count = 0;
        self.stopVoicePlayback();
        self.gameplay_voice_manager.clear();
        self.native_gameplay_voice_manager.clear();
        self.native_gameplay_slow_voice_progress = 0.0;
        self.announced_slug_voice_cell_count = 0;
        self.level_runner = null;
        self.gameplay_click_start_active = false;
        self.resetSubgameCamera();
        self.tutorial_reference_score = 0;
        if (self.catalog.level_entries.len == 0) return;

        const entry = self.catalog.level_entries[self.level_index];
        self.current_level = try level.loadFromArchive(self.allocator, &self.catalog, entry);
        if (self.current_level) |*loaded_level| {
            const runtime_build_seed = self.trackBuildSeedForCurrentLoad();
            self.current_track_preview = try track.LoadedLevelPreview.loadWithOptions(
                self.allocator,
                &self.catalog,
                loaded_level,
                .{
                    .runtime_build_flags = self.currentRunRuntimeBuildFlags(),
                    .runtime_build_seed = runtime_build_seed,
                    .garbage_scalar_override = self.currentRunGarbageScalar(),
                    .salt_scalar_override = self.currentRunSaltScalar(),
                },
            );
            if (self.current_track_preview) |*loaded_track_preview| {
                self.math_random_state = loaded_track_preview.runtime_build_final_random_state;
                try self.configureRuntimeParcels(loaded_track_preview);
                if (gameTrackSetIndexForLevel(loaded_level.track)) |track_set_index| {
                    self.current_game_track_scene = try track_render.Scene.buildStandaloneSegmentScene(
                        self.allocator,
                        &self.catalog,
                        track_set_index,
                    );
                }
                if (self.command == .game) {
                    try self.reloadGameplayTurbo();
                    try self.reloadGameplayBarrier();
                    try self.reloadGameplayLazer();
                    try self.reloadGameplaySalt();
                    try self.reloadGameplayActorModels();
                    try self.reloadGameplaySprites();
                    try self.reloadGameplaySoundFx();
                    self.applyAudioConfigVolumes();
                }
                self.level_runner = gameplay.Runner.init(loaded_track_preview);
                self.level_runner.?.configureCompletionBonus(
                    self.currentParcelTarget(),
                    completionBonusAppliesForMode(self.active_frontend_mode),
                );
                self.level_runner.?.configureSessionMode(runnerSessionModeForFrontendMode(self.active_frontend_mode));
                self.gameplay_click_start_active = seed_intro_cutscene and self.isTutorialFlow();
                if (seed_intro_cutscene) {
                    self.level_runner.?.setCutscene(gameplay.cutscene_intro_id);
                } else {
                    self.level_runner.?.clearCutscene();
                }
                if (self.level_runner) |*runner| {
                    self.updateSubgameCamera(runner);
                }
                if (self.isTutorialGameplay()) {
                    self.tutorial_reference_score = self.high_score_tables.postal[0].score;
                }
            }
        }
        self.level_segment_index = 0;
        try self.reloadLevelSegment();
        try self.syncActiveLevelSegment();
    }

    fn nextMathRandomInt15(self: *AppState) u32 {
        self.math_random_state = (self.math_random_state *% 0x343fd) +% 0x269ec3;
        return (self.math_random_state >> 16) & 0x7fff;
    }

    fn trackBuildSeedForCurrentLoad(self: *AppState) u32 {
        if (self.command != .game) return 0;

        const mode = self.active_frontend_mode;
        if (self.selected_level_record_override) |record| {
            if (mode == record.mode and self.active_frontend_level_index == record.level_index) {
                self.current_runtime_build_seed = record.runtime_build_seed;
                self.current_runtime_build_seed_level_index = self.level_index;
                self.current_runtime_build_seed_mode = mode;
                return record.runtime_build_seed;
            }
        }
        if (self.current_runtime_build_seed_level_index == self.level_index and self.current_runtime_build_seed_mode == mode) {
            return self.current_runtime_build_seed;
        }

        const seed: u32 = switch (mode orelse return 0) {
            .tutorial, .time_trial => 0,
            .postal, .challenge => self.nextMathRandomInt15(),
        };
        self.current_runtime_build_seed = seed;
        self.current_runtime_build_seed_level_index = self.level_index;
        self.current_runtime_build_seed_mode = mode;
        return seed;
    }

    fn invalidateTrackBuildSeed(self: *AppState) void {
        self.current_runtime_build_seed_level_index = null;
        self.current_runtime_build_seed_mode = null;
    }

    fn reloadLevelSegment(self: *AppState) !void {
        if (self.current_segment) |*loaded_segment| {
            loaded_segment.deinit();
            self.current_segment = null;
        }

        const loaded_level = self.current_level orelse return;
        if (loaded_level.segments.len == 0) return;
        if (self.level_segment_index >= loaded_level.segments.len) {
            self.level_segment_index = loaded_level.segments.len - 1;
        }

        var path_buffer: [512]u8 = undefined;
        const archive_path = try std.fmt.bufPrint(&path_buffer, "SEGMENTS/{s}", .{loaded_level.segments[self.level_segment_index].path});
        const entry = self.catalog.dat.entryByPath(archive_path) orelse return;
        self.current_segment = try segment.loadFromArchive(self.allocator, &self.catalog, entry);
    }

    fn reloadStandaloneSegment(self: *AppState) !void {
        if (self.current_standalone_segment_scene) |*scene| {
            scene.deinit();
            self.current_standalone_segment_scene = null;
        }
        if (self.current_standalone_segment_preview) |*loaded_track_preview| {
            loaded_track_preview.deinit();
            self.current_standalone_segment_preview = null;
        }
        if (self.catalog.segment_entries.len == 0) return;
        if (self.segment_index >= self.catalog.segment_entries.len) {
            self.segment_index = self.catalog.segment_entries.len - 1;
        }

        const entry = self.catalog.segment_entries[self.segment_index];
        self.current_standalone_segment_preview = try track.LoadedLevelPreview.loadStandaloneSegment(
            self.allocator,
            &self.catalog,
            entry,
        );
        try self.reloadStandaloneSegmentScene();
    }

    fn reloadStandaloneSegmentScene(self: *AppState) !void {
        if (self.current_standalone_segment_scene) |*scene| {
            scene.deinit();
            self.current_standalone_segment_scene = null;
        }
        _ = self.current_standalone_segment_preview orelse return;
        self.current_standalone_segment_scene = try track_render.Scene.buildStandaloneSegmentScene(
            self.allocator,
            &self.catalog,
            self.segment_track_set_index,
        );
    }

    fn activeModel(self: *const AppState) ?*const x2.Uploaded {
        if (self.current_animation) |*animation| {
            return &animation.rendered;
        }
        if (self.current_model) |*model| {
            return model;
        }
        return null;
    }

    pub fn activeLevelSegmentEntry(self: *const AppState) ?*const level.SegmentEntry {
        const loaded_level = self.current_level orelse return null;
        if (loaded_level.segments.len == 0 or self.level_segment_index >= loaded_level.segments.len) return null;
        return &loaded_level.segments[self.level_segment_index];
    }
};

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    const options = try parseArgs(allocator);
    try runtime_state.ensureRootExists(options.runtime_root_path);
    try std.fs.cwd().makePath(options.screenshot_dir);
    var runtime_config_result = try config.Blob.loadFromRuntimeRoot(allocator, options.runtime_root_path);
    if (options.fullscreen) {
        runtime_config_result.blob.setFullscreenEnabled(true);
    }

    const startup_fullscreen = options.fullscreen or
        (runtime_config_result.loaded_from_file and runtime_config_result.blob.fullscreenEnabled());
    runtime_config_result.blob.setFullscreenEnabled(startup_fullscreen);
    // Development default: stay windowed until fullscreen is requested explicitly or a saved runtime config says otherwise.
    rl.setConfigFlags(.{
        .fullscreen_mode = startup_fullscreen,
        .window_hidden = options.hidden_window,
    });
    const initial_window_size = options.window_size_override orelse defaultWindowSizeForCommand(options.command);
    rl.initWindow(initial_window_size.width, initial_window_size.height, "snail");
    // Keep ESC available for game/frontend input; window close still comes from the platform close event.
    rl.setExitKey(.null);
    defer rl.closeWindow();
    if (options.command == .game) {
        rl.hideCursor();
    } else {
        rl.showCursor();
    }

    rl.initAudioDevice();
    const audio_ready = rl.isAudioDeviceReady();
    defer {
        if (audio_ready) {
            rl.closeAudioDevice();
        }
    }

    var state = try AppState.init(allocator, options, runtime_config_result, audio_ready);
    defer state.saveRuntimeConfig() catch |err| std.log.err("failed to save runtime config: {}", .{err});
    defer state.deinit();
    var frame_timer = try std.time.Timer.start();
    var runtime_timer = try std.time.Timer.start();

    if (options.command == .smoke) {
        try state.warmupSmokeTest();
    }

    rl.setTargetFPS(144);
    var frames_left: usize = if (options.command == .smoke) 3 else std.math.maxInt(usize);

    while (!rl.windowShouldClose() and !state.should_exit and frames_left > 0) {
        if (options.timeout_seconds) |timeout_seconds| {
            const timeout_ns = @as(u64, timeout_seconds) * std.time.ns_per_s;
            if (runtime_timer.read() >= timeout_ns) {
                return error.RunTimeout;
            }
        }
        const frame_delta_seconds = @as(f64, @floatFromInt(frame_timer.lap())) / @as(f64, std.time.ns_per_s);
        if (options.command == .smoke) {
            frames_left -= 1;
        }

        try state.flushQueuedScreenshot();
        try state.handleInput();
        try state.update(frame_delta_seconds);
        try state.maybeQueueAutoScreenshot();

        rl.beginDrawing();
        defer rl.endDrawing();

        rl.clearBackground(.black);
        try drawUi(&state, options.archive_path);
    }
}

fn drawUi(state: *const AppState, archive_path: []const u8) !void {
    switch (state.command) {
        .game => return drawGameUi(state),
        .debug, .smoke => return drawDebugUi(state, archive_path),
    }
}

fn phaseUsesGameplayBackdrop(state: *const AppState) bool {
    return switch (state.game_phase) {
        .pause_menu => true,
        .options_menu => state.options_return_phase == .pause_menu,
        .exit_prompt => state.exit_prompt_return_phase == .pause_menu,
        else => false,
    };
}

const default_light_streak_camera = background.LightStreakCamera{
    .position = .{ .x = 0.0, .y = 0.0, .z = 0.0 },
    .right = .{ .x = 1.0, .y = 0.0, .z = 0.0 },
    .up = .{ .x = 0.0, .y = 1.0, .z = 0.0 },
    .forward = .{ .x = 0.0, .y = 0.0, .z = 1.0 },
    .fov_degrees = 38.0,
};

fn backgroundLightStreaksVisible(state: *const AppState) bool {
    if (phaseUsesGameplayBackdrop(state)) return true;
    return switch (state.game_phase) {
        .intro, .credits, .level => true,
        else => false,
    };
}

fn backgroundLightStreakCamera(state: *const AppState) background.LightStreakCamera {
    if (backgroundLightStreaksVisible(state) and state.subgame_camera.source != .identity) {
        const transform = normalizeCameraWorldTransform(cameraWorldTransformFromMatrix(state.subgame_camera.shared_matrix));
        return .{
            .position = transform.position,
            .right = transform.right,
            .up = transform.up,
            .forward = transform.forward,
            .fov_degrees = default_light_streak_camera.fov_degrees,
        };
    }
    return default_light_streak_camera;
}

fn frontendPhaseUsesCanvas(state: *const AppState) bool {
    if (phaseUsesGameplayBackdrop(state)) return false;
    return switch (state.game_phase) {
        .main_menu,
        .new_game_menu,
        .options_menu,
        .route_map_menu,
        .high_scores_menu,
        .exit_prompt,
        .completion_screen,
        .thanks_screen,
        .help,
        => true,
        .boot, .intro, .credits, .pause_menu, .level => false,
    };
}

fn drawGamePhaseContents(state: *const AppState, bounds: rl.Rectangle, ui_layout: VirtualLayout) !void {
    if (phaseUsesGameplayBackdrop(state)) {
        if (state.current_game_background) |loaded_background| {
            if (state.current_game_background_runtime) |runtime| {
                _ = runtime.draw(&loaded_background, bounds);
            } else {
                _ = loaded_background.draw(bounds);
            }
            state.background_light_streaks.draw(
                bounds,
                backgroundLightStreakCamera(state),
                if (state.current_background_light_streak_texture) |loaded| loaded.texture else null,
            );
        } else {
            rl.drawRectangleRec(bounds, .black);
        }
        drawGameplayLevelViewport(state);
    } else if (state.current_game_background) |loaded_background| {
        if (state.current_game_background_runtime) |runtime| {
            switch (state.game_phase) {
                .intro, .credits => runtime.drawStretched(&loaded_background, bounds),
                else => _ = runtime.draw(&loaded_background, bounds),
            }
        } else {
            _ = loaded_background.draw(bounds);
        }
        state.background_light_streaks.draw(
            bounds,
            backgroundLightStreakCamera(state),
            if (state.current_background_light_streak_texture) |loaded| loaded.texture else null,
        );
    } else {
        rl.drawRectangleRec(bounds, .black);
    }

    switch (state.game_phase) {
        .boot => unreachable,
        .intro => drawCurrentTextScript(state, ui_layout),
        .main_menu => try drawMainMenuUi(state, ui_layout),
        .new_game_menu => try drawNewGameMenuUi(state, ui_layout),
        .options_menu => try drawOptionsMenuUi(state, ui_layout),
        .pause_menu => try drawPauseMenuUi(state, ui_layout),
        .route_map_menu => try drawRouteMapMenuUi(state, ui_layout),
        .high_scores_menu => try drawHighScoresMenuUi(state, ui_layout),
        .exit_prompt => try drawExitPromptUi(state, ui_layout),
        .completion_screen => try drawCompletionScreenUi(state, ui_layout),
        .thanks_screen => drawThanksScreenUi(state, ui_layout),
        .credits => drawCurrentTextScript(state, ui_layout),
        .help => drawHelpUi(state, ui_layout),
        .level => try drawGameplayLevelUi(state, ui_layout),
    }
}

fn drawGameUi(state: *const AppState) !void {
    const full_bounds: rl.Rectangle = .{
        .x = 0.0,
        .y = 0.0,
        .width = @floatFromInt(screenWidth()),
        .height = @floatFromInt(screenHeight()),
    };
    const ui_layout = app_ui.virtualLayout(full_bounds);

    if (state.game_phase == .boot) {
        if (state.current_loading_screen) |loaded_screen| {
            loaded_screen.draw(full_bounds, bootPhaseProgress(state));
        } else {
            rl.drawRectangleRec(full_bounds, .black);
        }
        return drawGameBootUi(state, ui_layout);
    }

    if (frontendPhaseUsesCanvas(state)) {
        if (state.frontend_canvas) |canvas| {
            const authored_bounds: rl.Rectangle = .{
                .x = 0.0,
                .y = 0.0,
                .width = app_ui.authored_width,
                .height = app_ui.authored_height,
            };
            const authored_layout = app_ui.virtualLayout(authored_bounds);

            {
                canvas.begin();
                defer canvas.end();
                rl.clearBackground(.black);
                try drawGamePhaseContents(state, authored_bounds, authored_layout);
                drawFrontendCursorOverlay(state, authored_layout);
            }

            rl.drawTexturePro(
                canvas.texture,
                .{
                    .x = 0.0,
                    .y = 0.0,
                    .width = @floatFromInt(canvas.texture.width),
                    .height = -@as(f32, @floatFromInt(canvas.texture.height)),
                },
                full_bounds,
                .{ .x = 0.0, .y = 0.0 },
                0.0,
                .white,
            );
        } else {
            try drawGamePhaseContents(state, full_bounds, ui_layout);
            drawFrontendCursorOverlay(state, ui_layout);
        }
    } else {
        try drawGamePhaseContents(state, full_bounds, ui_layout);
        drawFrontendCursorOverlay(state, ui_layout);
    }

    state.frontend_transition.draw(full_bounds);
}

fn drawGameBootUi(state: *const AppState, layout: VirtualLayout) !void {
    if (state.current_loading_screen != null) return;

    const font_size = layout.fontSize(30);
    const title_width = measureAppText(state, "Loading...", font_size);
    const title_point = layout.mapPoint(320.0, 240.0);
    const title_x: i32 = @intFromFloat(title_point.x);
    const title_y: i32 = @intFromFloat(title_point.y);
    drawAppText(
        state,
        "Loading...",
        title_x - @divTrunc(title_width, 2),
        title_y - layout.scaleInt(18),
        font_size,
        .ray_white,
    );
}

fn optionsMenuMeasurementLabel(state: *const AppState, item: OptionsMenuItem) []const u8 {
    return switch (item) {
        .fullscreen => if (state.runtime_config.fullscreenEnabled()) "Full-screen On" else "Full-screen Off",
        .sound_volume => "     Sounds Volume     >",
        .music_volume => "      Music Volume      >",
        .back => "Back",
    };
}

fn optionsMenuVisibleLabel(state: *const AppState, item: OptionsMenuItem) []const u8 {
    return switch (item) {
        .fullscreen => optionsMenuMeasurementLabel(state, .fullscreen),
        .sound_volume => "Sounds Volume",
        .music_volume => "Music Volume",
        .back => "Back",
    };
}

fn optionsSliderLayout(state: *const AppState, item: OptionsMenuItem) frontend_widget.SliderLayout {
    var value_buffer: [16]u8 = undefined;
    const title_rect = switch (item) {
        .sound_volume => optionsTextRect(state, .sound_volume),
        .music_volume => optionsTextRect(state, .music_volume),
        else => unreachable,
    };
    const value = switch (item) {
        .sound_volume => state.runtime_config.soundVolume(),
        .music_volume => state.runtime_config.musicVolume(),
        else => unreachable,
    };
    const value_text = optionsSliderValueText(value, &value_buffer);
    const button_index = switch (item) {
        .sound_volume => options_sound_button_index,
        .music_volume => options_music_button_index,
        else => unreachable,
    };
    return frontend_widget.sliderLayout(
        &state.ui_font,
        title_rect,
        state.options_button_states[button_index],
        value_text,
    );
}

fn optionsTextRect(state: *const AppState, item: OptionsMenuItem) frontend_widget.Rect {
    return switch (item) {
        .fullscreen => frontend_widget.type20TextRect(
            &state.ui_font,
            optionsMenuMeasurementLabel(state, .fullscreen),
            options_fullscreen_anchor_y,
            options_button_center_offset_x,
        ),
        .sound_volume => frontend_widget.type20TextRect(
            &state.ui_font,
            optionsMenuMeasurementLabel(state, .sound_volume),
            optionsTextRect(state, .fullscreen).top + optionsTextRect(state, .fullscreen).height + frontend_widget.type20_stack_gap,
            options_button_center_offset_x,
        ),
        .music_volume => frontend_widget.type20TextRect(
            &state.ui_font,
            optionsMenuMeasurementLabel(state, .music_volume),
            // PORT(verified): `initialize_options` stacks Music below the full slider parent,
            // not below a hardcoded surrogate row height. The parent frame height comes from
            // the child-arrow/value layout in the shared widget pipeline.
            frontend_widget.sliderStackBelowLayout(optionsSliderLayout(state, .sound_volume)),
            options_button_center_offset_x,
        ),
        .back => frontend_widget.type20TextRect(
            &state.ui_font,
            "Back",
            // PORT(verified): the Back button is chained from the Music slider widget after
            // its children are attached, so this needs the live computed slider frame height.
            frontend_widget.sliderStackBelowLayout(optionsSliderLayout(state, .music_volume)),
            options_button_center_offset_x,
        ),
    };
}

fn optionsSliderValueText(value: f32, buffer: []u8) []const u8 {
    return std.fmt.bufPrint(buffer, "{d:0>2.0}%", .{std.math.clamp(value, 0.0, 1.0) * 100.0}) catch "00%";
}

fn mainMenuTextRect(font: *const game_font.Loaded, item: MainMenuItem) frontend_widget.Rect {
    return switch (item) {
        .new_game => frontend_widget.type20TextRect(font, item.label(), main_menu_start_y, frontend_widget.type20_center_offset_x),
        .high_scores => frontend_widget.type20TextRect(font, item.label(), frontend_widget.stackBelow(mainMenuTextRect(font, .new_game)), frontend_widget.type20_center_offset_x),
        .options => frontend_widget.type20TextRect(font, item.label(), frontend_widget.stackBelow(mainMenuTextRect(font, .high_scores)), frontend_widget.type20_center_offset_x),
        .credits => frontend_widget.type20TextRect(font, item.label(), frontend_widget.stackBelow(mainMenuTextRect(font, .options)), frontend_widget.type20_center_offset_x),
        .exit => frontend_widget.type20TextRect(font, item.label(), frontend_widget.stackBelow(mainMenuTextRect(font, .credits)), frontend_widget.type20_center_offset_x),
    };
}

fn newGameMenuTextRect(font: *const game_font.Loaded, item: NewGameMenuItem) frontend_widget.Rect {
    return switch (item) {
        .tutorial => frontend_widget.type20TextRect(font, item.label(), new_game_start_y, frontend_widget.type20_center_offset_x),
        .postal_mode => frontend_widget.type20TextRect(font, item.label(), frontend_widget.stackBelow(newGameMenuTextRect(font, .tutorial)), frontend_widget.type20_center_offset_x),
        .time_trial => frontend_widget.type20TextRect(font, item.label(), frontend_widget.stackBelow(newGameMenuTextRect(font, .postal_mode)), frontend_widget.type20_center_offset_x),
        .challenge_mode => frontend_widget.type20TextRect(font, item.label(), frontend_widget.stackBelow(newGameMenuTextRect(font, .time_trial)), frontend_widget.type20_center_offset_x),
        .help => newGameHelpTextRect(font),
        .back => newGameBackTextRect(font),
    };
}

fn newGameHelpTextRect(font: *const game_font.Loaded) frontend_widget.Rect {
    return frontend_widget.type20TextRect(font, "Help", new_game_help_anchor_y, new_game_help_center_offset_x);
}

fn newGameBackTextRect(font: *const game_font.Loaded) frontend_widget.Rect {
    return frontend_widget.type20TextRect(
        font,
        "Back",
        frontend_widget.stackBelow(newGameMenuTextRect(font, .challenge_mode)),
        new_game_back_center_offset_x,
    );
}

fn helpBackTextRect(font: *const game_font.Loaded) frontend_widget.Rect {
    return frontend_widget.type20TextRect(font, "Back", help_back_anchor_y, 0.0);
}

fn pauseMenuTextRect(font: *const game_font.Loaded, item: PauseMenuItem) frontend_widget.Rect {
    return switch (item) {
        .end_game => frontend_widget.type20TextRect(font, item.label(), pause_menu_start_y, pause_menu_center_offset_x),
        .options => frontend_widget.type20TextRect(font, item.label(), frontend_widget.stackBelow(pauseMenuTextRect(font, .end_game)), pause_menu_center_offset_x),
        .@"resume" => frontend_widget.type20TextRect(font, item.label(), frontend_widget.stackBelow(pauseMenuTextRect(font, .options)), pause_menu_center_offset_x),
    };
}

fn routeMapBackTextRect(state: *const AppState) frontend_widget.Rect {
    return frontend_widget.widgetTextRect(&state.ui_font, .menu_button, .absolute, routeMapBackLabel(state), route_map_back_y, route_map_back_x);
}

fn routeMapBackLabel(state: *const AppState) []const u8 {
    return routeMapBackLabelForScreenMode(state.route_map_screen_mode);
}

fn routeMapBackLabelForScreenMode(screen_mode: RouteMapScreenMode) []const u8 {
    return switch (screen_mode) {
        .post_completion_exit => "Exit",
        .normal, .replay => "Back",
    };
}

fn routeMapAllowsRouteSwitching(screen_mode: RouteMapScreenMode) bool {
    // PORT(verified): `update_galaxy` skips the open/switch/close route branch entirely
    // for internal mode `1`, keeping the postal-return Star Map locked on its current
    // route card while still allowing Play/Exit.
    return screen_mode != .post_completion_exit;
}

fn routeMapBodyText(maybe_text: ?[]const u8) []const u8 {
    // PORT(verified): `open_galaxy_route` copies the route body from the per-route record
    // once when the card opens. `update_galaxy` does not swap that body text based on
    // hover state or selected action.
    return maybe_text orelse "";
}

fn highScoreFooterTextRect(state: *const AppState, text: []const u8, center_offset_x: f32) frontend_widget.Rect {
    return frontend_widget.widgetTextRect(&state.ui_font, .footer_button, .center, text, high_score_footer_y, center_offset_x);
}

fn highScoreRowBackgroundText(mode: high_score.Mode) []const u8 {
    return switch (mode) {
        .postal => "                                               ",
        .challenge => "                                           ",
    };
}

fn highScoreRowBackgroundTextRect(state: *const AppState, mode: high_score.Mode, row_y: f32) frontend_widget.Rect {
    return frontend_widget.widgetTextRect(&state.ui_font, .compact_score_row, .left, highScoreRowBackgroundText(mode), row_y, high_score_rank_marker_x);
}

fn highScoreRankTextRect(state: *const AppState, row_y: f32, rank_text: []const u8) frontend_widget.Rect {
    return frontend_widget.widgetTextRect(&state.ui_font, .compact_score_row, .left, rank_text, row_y, high_score_rank_number_x);
}

fn highScoreNameTextRect(state: *const AppState, row_y: f32, display_name: []const u8) frontend_widget.Rect {
    return frontend_widget.widgetTextRect(&state.ui_font, .compact_score_row, .left, display_name, row_y, high_score_name_x);
}

fn highScoreScoreTextRect(state: *const AppState, mode: high_score.Mode, row_y: f32, score_text: []const u8) frontend_widget.Rect {
    return frontend_widget.widgetTextRect(
        &state.ui_font,
        .compact_score_row,
        .right,
        score_text,
        row_y,
        switch (mode) {
            .postal => high_score_postal_score_x,
            .challenge => high_score_challenge_score_x,
        },
    );
}

fn highScoreReplayTextRect(state: *const AppState, mode: high_score.Mode, row_y: f32) frontend_widget.Rect {
    return frontend_widget.widgetTextRect(
        &state.ui_font,
        .compact_score_row,
        .center,
        "Replay",
        row_y,
        switch (mode) {
            .postal => high_score_postal_replay_x,
            .challenge => high_score_challenge_replay_x,
        },
    );
}

fn completionTitleTextRect(font: *const game_font.Loaded, text: []const u8) frontend_widget.Rect {
    return frontend_widget.type20TextRect(font, text, completion_title_y, 0.0);
}

fn completionPackageTextRect(font: *const game_font.Loaded, text: []const u8) frontend_widget.Rect {
    return frontend_widget.type20TextRect(font, text, completion_package_y, 0.0);
}

fn completionBonusTextRect(font: *const game_font.Loaded, text: []const u8) frontend_widget.Rect {
    return frontend_widget.type20TextRect(font, text, completion_bonus_y, 0.0);
}

fn completionContinueAnchorY(result: PendingRunResult) f32 {
    return if (completionHasBonusLine(result)) completion_continue_y_with_bonus else completion_continue_y;
}

fn completionContinueTextRect(font: *const game_font.Loaded, result: PendingRunResult) frontend_widget.Rect {
    return frontend_widget.type20TextRect(font, "Click to Continue", completionContinueAnchorY(result), 0.0);
}

fn exitPromptTextRect(state: *const AppState, text: []const u8, center_offset_x: f32) frontend_widget.Rect {
    // PORT(verified): `initialize_exit_prompt` seeds the Yes/No widgets at `330`, but then
    // immediately runs both through `stack_widget_below(title)`. The live authored Y comes
    // from the title height plus the shared shell-font stack gap, not the constructor seed.
    const title_rect = frontend_widget.widgetTextRect(
        &state.ui_font,
        .menu_button,
        .center,
        "Do you really want to quit?",
        exit_prompt_title_y,
        0.0,
    );
    return frontend_widget.widgetTextRect(
        &state.ui_font,
        .menu_button,
        .center,
        text,
        frontend_widget.stackBelow(title_rect),
        center_offset_x,
    );
}

fn drawMainMenuUi(state: *const AppState, layout: VirtualLayout) !void {
    for (main_menu_items, 0..) |item, index| {
        const text_rect = mainMenuTextRect(&state.ui_font, item);
        frontend_widget.drawType20Button(
            layout,
            .{
                .border = state.frontend_widget_art.border.?.texture,
            },
            &state.ui_font,
            item.label(),
            text_rect,
            state.main_menu_button_states[index],
            false,
        );
    }

    if (state.game_status_message) |message| {
        try drawFrontendStatusMessage(state, layout, message);
    }
}

fn drawNewGameMenuUi(state: *const AppState, layout: VirtualLayout) !void {
    for (new_game_menu_items[0..4], 0..) |item, index| {
        const text_rect = newGameMenuTextRect(&state.ui_font, item);
        frontend_widget.drawType20Button(
            layout,
            .{
                .border = state.frontend_widget_art.border.?.texture,
            },
            &state.ui_font,
            item.label(),
            text_rect,
            state.new_game_button_states[index],
            false,
        );
    }
    frontend_widget.drawType20Button(
        layout,
        .{
            .border = state.frontend_widget_art.border.?.texture,
        },
        &state.ui_font,
        "Help",
        newGameHelpTextRect(&state.ui_font),
        state.new_game_button_states[4],
        false,
    );
    frontend_widget.drawType20Button(
        layout,
        .{
            .border = state.frontend_widget_art.border.?.texture,
        },
        &state.ui_font,
        "Back",
        newGameBackTextRect(&state.ui_font),
        state.new_game_button_states[5],
        false,
    );

    if (state.game_status_message) |message| {
        try drawFrontendStatusMessage(state, layout, message);
    }
}

fn drawOptionsMenuUi(state: *const AppState, layout: VirtualLayout) !void {
    frontend_widget.drawType20Button(
        layout,
        .{
            .border = state.frontend_widget_art.border.?.texture,
        },
        &state.ui_font,
        optionsMenuVisibleLabel(state, .fullscreen),
        optionsTextRect(state, .fullscreen),
        state.options_button_states[options_fullscreen_button_index],
        false,
    );
    const active_target = state.activeFrontendButtonTarget();
    drawOptionsSliderRow(
        state,
        layout,
        .sound_volume,
        state.runtime_config.soundVolume(),
        state.options_sound_display_value,
        state.options_button_states[options_sound_button_index],
        if (active_target) |target| target == .options_sound_less else false,
        if (active_target) |target| target == .options_sound_more else false,
    );
    drawOptionsSliderRow(
        state,
        layout,
        .music_volume,
        state.runtime_config.musicVolume(),
        state.options_music_display_value,
        state.options_button_states[options_music_button_index],
        if (active_target) |target| target == .options_music_less else false,
        if (active_target) |target| target == .options_music_more else false,
    );
    frontend_widget.drawType20Button(
        layout,
        .{
            .border = state.frontend_widget_art.border.?.texture,
        },
        &state.ui_font,
        "Back",
        optionsTextRect(state, .back),
        state.options_button_states[options_back_button_index],
        false,
    );

    if (state.game_status_message) |message| {
        try drawFrontendStatusMessage(state, layout, message);
    }
}

fn drawPauseMenuUi(state: *const AppState, layout: VirtualLayout) !void {
    for (pause_menu_items, 0..) |item, index| {
        frontend_widget.drawType20Button(
            layout,
            .{
                .border = state.frontend_widget_art.border.?.texture,
            },
            &state.ui_font,
            item.label(),
            pauseMenuTextRect(&state.ui_font, item),
            state.pause_menu_button_states[index],
            false,
        );
    }
}

const RouteMapCardLayout = struct {
    card_rect: frontend_widget.Rect,
    title_rect: frontend_widget.Rect,
    subtitle_rect: frontend_widget.Rect,
    body_rect: frontend_widget.Rect,
    primary_text_rect: frontend_widget.Rect,
    replay_text_rect: ?frontend_widget.Rect,
    pointer_start: galaxy.Point,
    pointer_end: galaxy.Point,
};

fn drawRouteMapMenuUi(state: *const AppState, layout: VirtualLayout) !void {
    const mode = state.frontend_route_mode orelse return;
    const widget_art: frontend_widget.Art = .{
        .border = state.frontend_widget_art.border.?.texture,
    };
    // PORT(verified): `initialize_galaxy` passes an explicit white color into the title
    // widget constructor instead of reusing the orange menu-heading tint.
    drawUiFontTextAbsolute(state, layout, "Intergalactic Delivery Route", route_map_title_x, route_map_title_y, route_map_title_scale, .ray_white);
    drawRouteMapLogo(state, layout);
    drawRouteMapStars(state, layout, mode);
    if (state.currentRouteMapOpenIndex()) |route_index| {
        const route_galaxy_name = state.currentFrontendGalaxyName() orelse frontendRouteModeLabel(mode);
        const route_level_name = if (state.frontend_route_level) |loaded_level| loaded_level.name else "Route";
        const route_body = routeMapBodyText(if (state.frontend_route_level) |loaded_level| loaded_level.galaxy_text else null);
        const primary_label = routeMenuActionLabel(mode, .play);
        const replay_label = if (state.routeMapShowsReplay()) routeMenuActionLabel(mode, .watch_best_trial) else null;
        if (routeMapPointForRouteIndex(state, route_index)) |route_point| {
            const card_layout = routeMapCardLayout(
                &state.ui_font,
                route_point,
                route_galaxy_name,
                route_level_name,
                route_body,
                primary_label,
                replay_label,
            );
            drawRouteMapConnection(layout, card_layout.pointer_start, card_layout.pointer_end, state.route_map_art.line_star, 4.0, .white);
            drawRouteMapCard(state, layout, card_layout, route_galaxy_name, route_level_name, route_body, primary_label, replay_label);
        }
    }

    frontend_widget.drawType20Button(
        layout,
        widget_art,
        &state.ui_font,
        routeMapBackLabel(state),
        routeMapBackTextRect(state),
        state.route_map_button_states[route_map_back_button_index],
        false,
    );

    if (state.game_status_message) |message| {
        try drawFrontendNoticeBlock(state, layout, 320.0, 438.0, message, .ray_white);
    }
}

fn drawHighScoresMenuUi(state: *const AppState, layout: VirtualLayout) !void {
    const pending_entry = state.postLevelHighScoreContext();
    const selected_mode = if (pending_entry) |context|
        context.mode
    else
        high_score_screen_modes[@min(state.high_scores_menu_index, high_score_screen_modes.len - 1)];
    const art: frontend_widget.Art = .{
        .border = state.frontend_widget_art.border.?.texture,
    };
    var title_state = frontend_widget.TextButtonState{};
    title_state.snapFor(.footer_button, false);
    const title_text = if (pending_entry != null) "Enter your name here!" else highScoreScreenTitle(selected_mode);
    frontend_widget.drawTextButton(
        layout,
        art,
        &state.ui_font,
        .footer_button,
        title_text,
        frontend_widget.widgetTextRect(&state.ui_font, .footer_button, .center, title_text, high_score_title_y, 0.0),
        title_state,
        false,
    );

    if (pending_entry) |context| {
        var draft_buffer: [high_score.name_capacity + 1]u8 = undefined;
        const draft_name = if (state.postLevelHighScoreDraft().len == 0)
            "_"
        else
            try std.fmt.bufPrint(&draft_buffer, "{s}_", .{state.postLevelHighScoreDraft()});
        drawHighScoreTable(state, layout, context.rank, draft_name, true, selected_mode);
        frontend_widget.drawTextButton(
            layout,
            art,
            &state.ui_font,
            .footer_button,
            post_level_high_score_actions[0].label(),
            highScoreFooterTextRect(state, post_level_high_score_actions[0].label(), high_score_entry_cancel_x),
            state.post_level_high_score_button_states[0],
            false,
        );
        frontend_widget.drawTextButton(
            layout,
            art,
            &state.ui_font,
            .footer_button,
            post_level_high_score_actions[1].label(),
            highScoreFooterTextRect(state, post_level_high_score_actions[1].label(), high_score_entry_submit_x),
            state.post_level_high_score_button_states[1],
            false,
        );
    } else {
        drawHighScoreTable(state, layout, null, null, false, selected_mode);
        frontend_widget.drawTextButton(
            layout,
            art,
            &state.ui_font,
            .footer_button,
            "Back",
            highScoreFooterTextRect(state, "Back", high_score_back_x),
            state.high_score_button_states[0],
            false,
        );
        frontend_widget.drawTextButton(
            layout,
            art,
            &state.ui_font,
            .footer_button,
            highScoreTableToggleLabel(selected_mode),
            highScoreFooterTextRect(state, highScoreTableToggleLabel(selected_mode), high_score_toggle_x),
            state.high_score_button_states[1],
            false,
        );
    }

    if (state.game_status_message) |message| {
        try drawFrontendStatusMessage(state, layout, message);
    }
}

fn drawExitPromptUi(state: *const AppState, layout: VirtualLayout) !void {
    const art: frontend_widget.Art = .{
        .border = state.frontend_widget_art.border.?.texture,
    };
    drawFrontendHeading(state, layout, 320.0, exit_prompt_title_y, "Do you really want to quit?", 26, .center, .ray_white);
    frontend_widget.drawType20Button(
        layout,
        art,
        &state.ui_font,
        exit_prompt_choices[0].label(),
        exitPromptTextRect(state, exit_prompt_choices[0].label(), exit_prompt_yes_x),
        state.exit_prompt_button_states[0],
        false,
    );
    frontend_widget.drawType20Button(
        layout,
        art,
        &state.ui_font,
        exit_prompt_choices[1].label(),
        exitPromptTextRect(state, exit_prompt_choices[1].label(), exit_prompt_no_x),
        state.exit_prompt_button_states[1],
        false,
    );
}

fn drawHighScoreTable(
    state: *const AppState,
    layout: VirtualLayout,
    highlight_index: ?usize,
    editing_name: ?[]const u8,
    hide_replay: bool,
    mode: high_score.Mode,
) void {
    const entries = state.high_score_tables.visibleEntries(mode);
    const art: frontend_widget.Art = .{
        .border = state.frontend_widget_art.border.?.texture,
    };
    const row_background_text = highScoreRowBackgroundText(mode);
    const text_only_score_cell: frontend_widget.DrawOptions = .{
        // PORT(verified): `initialize_high_score_screen` gives the rank, name,
        // and numeric score cells flags `0x20400000`, so those type-22 widgets
        // render as text-only entries on top of the shared row background.
        .flags = 0x20400000,
    };

    for (entries, 0..) |table_entry, entry_index| {
        const row_highlighted = highlight_index != null and highlight_index.? == entry_index;
        if (!table_entry.isActive() and !row_highlighted) continue;

        const row_y = high_score_row_start_y + @as(f32, @floatFromInt(entry_index)) * high_score_row_pitch;
        var row_state = frontend_widget.TextButtonState{};
        row_state.snapFor(.compact_score_row, row_highlighted);
        frontend_widget.drawTextButton(
            layout,
            art,
            &state.ui_font,
            .compact_score_row,
            row_background_text,
            highScoreRowBackgroundTextRect(state, mode, row_y),
            row_state,
            false,
        );

        var rank_buffer: [8]u8 = undefined;
        const rank_text = std.fmt.bufPrint(&rank_buffer, "{d}", .{entry_index + 1}) catch "";
        const display_name = if (row_highlighted and editing_name != null)
            editing_name.?
        else
            highScoreDisplayName(&table_entry);

        frontend_widget.drawTextButtonWithOptions(
            layout,
            art,
            &state.ui_font,
            .compact_score_row,
            rank_text,
            highScoreRankTextRect(state, row_y, rank_text),
            row_state,
            false,
            text_only_score_cell,
        );
        frontend_widget.drawTextButtonWithOptions(
            layout,
            art,
            &state.ui_font,
            .compact_score_row,
            display_name,
            highScoreNameTextRect(state, row_y, display_name),
            row_state,
            false,
            text_only_score_cell,
        );

        var score_buffer: [32]u8 = undefined;
        const score_text = if (table_entry.isActive())
            (std.fmt.bufPrint(&score_buffer, "{d}", .{table_entry.score}) catch "0")
        else
            "";
        frontend_widget.drawTextButtonWithOptions(
            layout,
            art,
            &state.ui_font,
            .compact_score_row,
            score_text,
            highScoreScoreTextRect(state, mode, row_y, score_text),
            row_state,
            false,
            text_only_score_cell,
        );
        if (highScoreRowsShowReplay(mode, hide_replay) and table_entry.has_replay) {
            frontend_widget.drawTextButton(
                layout,
                art,
                &state.ui_font,
                .compact_score_row,
                "Replay",
                highScoreReplayTextRect(state, mode, row_y),
                state.high_score_replay_button_states[entry_index],
                false,
            );
        }
    }
}

fn highScoreDisplayName(entry: *const high_score.Entry) []const u8 {
    const name = entry.name();
    if (name.len == 0) return "---";
    return name;
}

fn highScoreRowsShowReplay(mode: high_score.Mode, in_name_entry: bool) bool {
    // PORT(verified): `initialize_high_score_screen` only enables the row Replay widgets for the
    // Challenge table, and `update_high_score_screen` suppresses them while inline name-entry is active.
    return mode == .challenge and !in_name_entry;
}

fn drawFooterMessage(state: *const AppState, layout: VirtualLayout, footer_panel: rl.Rectangle, message: []const u8) !void {
    rl.drawRectangleRounded(footer_panel, 0.2, 8, .{ .r = 0, .g = 0, .b = 0, .a = 172 });
    try drawWrappedText(
        state,
        message,
        @intFromFloat(footer_panel.x + layout.scaleFloat(20.0)),
        @intFromFloat(footer_panel.y + layout.scaleFloat(11.0)),
        @intFromFloat(footer_panel.width - layout.scaleFloat(32.0)),
        layout.fontSize(20),
        .ray_white,
    );
}

const FrontendTextAlign = enum {
    left,
    center,
    right,
};

const FrontendButtonOptions = struct {
    min_width: f32 = 0.0,
    show_cursor: bool = true,
};

const FrontendButtonColors = struct {
    fill: rl.Color,
    outline: rl.Color,
    text: rl.Color,
    shadow: rl.Color,
};

fn drawFrontendTextAligned(
    state: *const AppState,
    layout: VirtualLayout,
    local_x: f32,
    local_y: f32,
    text: []const u8,
    authored_size: i32,
    color: rl.Color,
    alignment: FrontendTextAlign,
) void {
    const point = layout.mapPoint(local_x, local_y);
    const font_size = layout.fontSize(authored_size);
    const width = measureAppText(state, text, font_size);
    const draw_x = switch (alignment) {
        .left => @as(i32, @intFromFloat(point.x)),
        .center => @as(i32, @intFromFloat(point.x)) - @divTrunc(width, 2),
        .right => @as(i32, @intFromFloat(point.x)) - width,
    };
    drawAppText(state, text, draw_x, @intFromFloat(point.y), font_size, color);
}

fn frontendButtonColors(active: bool) FrontendButtonColors {
    return if (active)
        .{
            .fill = .{ .r = 184, .g = 112, .b = 214, .a = 232 },
            .outline = .{ .r = 226, .g = 194, .b = 255, .a = 255 },
            .text = .ray_white,
            .shadow = .{ .r = 74, .g = 18, .b = 84, .a = 220 },
        }
    else
        .{
            .fill = .{ .r = 96, .g = 78, .b = 152, .a = 164 },
            .outline = .{ .r = 112, .g = 96, .b = 176, .a = 112 },
            .text = .{ .r = 216, .g = 138, .b = 28, .a = 255 },
            .shadow = .{ .r = 40, .g = 16, .b = 58, .a = 220 },
        };
}

fn measureFrontendLocalTextWidth(state: *const AppState, layout: VirtualLayout, text: []const u8, authored_size: i32) f32 {
    const pixel_width = measureAppText(state, text, layout.fontSize(authored_size));
    return @as(f32, @floatFromInt(pixel_width)) / layout.scale;
}

fn drawFrontendPill(
    layout: VirtualLayout,
    center_x: f32,
    center_y: f32,
    width: f32,
    height: f32,
    fill: rl.Color,
    outline: rl.Color,
) void {
    const shadow_rect = layout.mapRect(center_x - width * 0.5, center_y - height * 0.5 + 2.0, width, height);
    const rect = layout.mapRect(center_x - width * 0.5, center_y - height * 0.5, width, height);
    rl.drawRectangleRounded(shadow_rect, 0.4, 10, .{ .r = 30, .g = 6, .b = 34, .a = 110 });
    rl.drawRectangleRounded(rect, 0.4, 10, fill);
    rl.drawRectangleRoundedLinesEx(rect, 0.4, 10, layout.scaleFloat(1.0), outline);
}

fn drawFrontendCursorRocket(state: *const AppState, layout: VirtualLayout, local_x: f32, local_y: f32) void {
    const loaded_texture = state.frontend_cursor_texture orelse return;
    const destination = layout.mapRect(
        local_x - frontend_widget.cursor_hotspot_x,
        local_y - frontend_widget.cursor_hotspot_y,
        frontend_widget.cursor_size,
        frontend_widget.cursor_size,
    );
    rl.drawTexturePro(
        loaded_texture.texture,
        .{
            .x = 0.0,
            .y = 0.0,
            .width = @as(f32, @floatFromInt(loaded_texture.texture.width)),
            .height = @as(f32, @floatFromInt(loaded_texture.texture.height)),
        },
        destination,
        .{ .x = 0.0, .y = 0.0 },
        0.0,
        .white,
    );
}

fn drawFrontendCursorOverlay(state: *const AppState, layout: VirtualLayout) void {
    if (state.command != .game) return;
    if (!frontendPhaseShowsCursor(state.game_phase)) return;
    const local_mouse = state.currentFrontendMouseLocal() orelse return;
    drawFrontendCursorRocket(state, layout, local_mouse.x, local_mouse.y);
}

fn frontendPhaseShowsCursor(phase: GamePhase) bool {
    return switch (phase) {
        .main_menu,
        .new_game_menu,
        .options_menu,
        .pause_menu,
        .route_map_menu,
        .high_scores_menu,
        .exit_prompt,
        .completion_screen,
        .thanks_screen,
        .help,
        => true,
        .boot, .intro, .credits, .level => false,
    };
}

fn drawFrontendHeading(
    state: *const AppState,
    layout: VirtualLayout,
    local_x: f32,
    local_y: f32,
    text: []const u8,
    authored_size: i32,
    alignment: FrontendTextAlign,
    color: rl.Color,
) void {
    drawFrontendTextAligned(state, layout, local_x + 2.0, local_y + 2.0, text, authored_size, .{ .r = 30, .g = 10, .b = 28, .a = 224 }, alignment);
    drawFrontendTextAligned(state, layout, local_x, local_y, text, authored_size, color, alignment);
}

fn scaledUiFontSize(font: *const game_font.Loaded, text_scale: f32) f32 {
    return font.nominal_height * text_scale;
}

fn multilineUiTextHeight(font: *const game_font.Loaded, text: []const u8, text_scale: f32) f32 {
    if (text.len == 0) return 0.0;
    var line_count: usize = 1;
    for (text) |byte| {
        if (byte == '\n') line_count += 1;
    }
    return @as(f32, @floatFromInt(line_count)) * scaledUiFontSize(font, text_scale);
}

fn uiFontTextRectAbsolute(font: *const game_font.Loaded, text: []const u8, left: f32, top: f32, text_scale: f32) frontend_widget.Rect {
    const font_size = scaledUiFontSize(font, text_scale);
    return .{
        .left = left,
        .top = top,
        .width = font.measureText(text, font_size),
        .height = multilineUiTextHeight(font, text, text_scale),
    };
}

fn drawUiFontTextAbsolute(
    state: *const AppState,
    layout: VirtualLayout,
    text: []const u8,
    left: f32,
    top: f32,
    text_scale: f32,
    color: rl.Color,
) void {
    const point = layout.mapPoint(left, top);
    state.ui_font.drawText(text, point.x, point.y, layout.scaleFloat(scaledUiFontSize(&state.ui_font, text_scale)), color);
}

fn drawUiFontTextRect(
    state: *const AppState,
    layout: VirtualLayout,
    text: []const u8,
    rect: frontend_widget.Rect,
    text_scale: f32,
    color: rl.Color,
) void {
    drawUiFontTextAbsolute(state, layout, text, rect.left, rect.top, text_scale, color);
}

fn drawFrontendMenuButton(
    state: *const AppState,
    layout: VirtualLayout,
    center_x: f32,
    center_y: f32,
    text: []const u8,
    active: bool,
    options: FrontendButtonOptions,
) void {
    const authored_font_size: i32 = if (active) 28 else 26;
    const horizontal_padding: f32 = if (active) 54.0 else 42.0;
    const local_width = @max(measureFrontendLocalTextWidth(state, layout, text, authored_font_size) + horizontal_padding, options.min_width);
    const local_height: f32 = if (active) 38.0 else 34.0;
    const colors = frontendButtonColors(active);
    drawFrontendPill(layout, center_x, center_y, local_width, local_height, colors.fill, colors.outline);
    drawFrontendTextAligned(state, layout, center_x + 2.0, center_y - @as(f32, if (active) 13 else 12), text, authored_font_size, colors.shadow, .center);
    drawFrontendTextAligned(state, layout, center_x, center_y - @as(f32, if (active) 15 else 14), text, authored_font_size, colors.text, .center);
}

fn drawTextureLocalRectSource(
    layout: VirtualLayout,
    loaded_texture: assets.LoadedTexture,
    source: rl.Rectangle,
    local_x: f32,
    local_y: f32,
    local_width: f32,
    local_height: f32,
    tint: rl.Color,
) void {
    if (local_width <= 0.0 or local_height <= 0.0) return;
    rl.drawTexturePro(
        loaded_texture.texture,
        source,
        layout.mapRect(local_x, local_y, local_width, local_height),
        .{ .x = 0.0, .y = 0.0 },
        0.0,
        tint,
    );
}

fn drawTextureLocalRect(
    layout: VirtualLayout,
    loaded_texture: assets.LoadedTexture,
    local_x: f32,
    local_y: f32,
    local_width: f32,
    local_height: f32,
    tint: rl.Color,
) void {
    drawTextureLocalRectSource(
        layout,
        loaded_texture,
        .{
            .x = 0.0,
            .y = 0.0,
            .width = @as(f32, @floatFromInt(loaded_texture.texture.width)),
            .height = @as(f32, @floatFromInt(loaded_texture.texture.height)),
        },
        local_x,
        local_y,
        local_width,
        local_height,
        tint,
    );
}

fn drawTextureCenteredLocal(
    layout: VirtualLayout,
    loaded_texture: assets.LoadedTexture,
    center_x: f32,
    center_y: f32,
    local_width: f32,
    local_height: f32,
    tint: rl.Color,
) void {
    drawTextureLocalRect(
        layout,
        loaded_texture,
        center_x - local_width * 0.5,
        center_y - local_height * 0.5,
        local_width,
        local_height,
        tint,
    );
}

fn drawOptionsSliderRow(
    state: *const AppState,
    layout: VirtualLayout,
    item: OptionsMenuItem,
    value: f32,
    displayed_value: f32,
    row_state: frontend_widget.TextButtonState,
    less_hovered: bool,
    more_hovered: bool,
) void {
    var value_buffer: [16]u8 = undefined;
    const title_rect = optionsTextRect(state, item);
    const value_text = optionsSliderValueText(value, &value_buffer);
    frontend_widget.drawSliderMenuRow(
        layout,
        .{
            .border = state.frontend_widget_art.border.?.texture,
        },
        state.slider_art.textures(),
        &state.ui_font,
        optionsMenuVisibleLabel(state, item),
        title_rect,
        value_text,
        value,
        displayed_value,
        row_state,
        less_hovered,
        more_hovered,
    );
}

fn routeMapCardLayout(
    font: *const game_font.Loaded,
    route_point: galaxy.Point,
    route_galaxy_name: []const u8,
    route_level_name: []const u8,
    route_body: []const u8,
    primary_action: []const u8,
    replay_action: ?[]const u8,
) RouteMapCardLayout {
    var title_left = route_point.x + 60.0;
    var title_top = route_point.y - 130.0;

    while (true) {
        const title_rect = uiFontTextRectAbsolute(font, route_galaxy_name, title_left, title_top, route_map_card_title_scale);
        const subtitle_rect = uiFontTextRectAbsolute(
            font,
            route_level_name,
            title_left,
            frontend_widget.stackBelowWithGap(title_rect, route_map_card_text_gap),
            route_map_card_subtitle_scale,
        );
        const body_rect = uiFontTextRectAbsolute(
            font,
            route_body,
            title_left,
            frontend_widget.stackBelowWithGap(subtitle_rect, route_map_card_text_gap),
            route_map_card_body_scale,
        );
        // PORT(verified): `open_galaxy_route` chains the selected route card with the shared
        // `stack_widget_below` helper: title -> subtitle -> body -> replay? -> primary. The
        // title/subtitle/body use zero extra gap, the replay row uses `10`, and the primary
        // action uses `20`. Windows first centers the action widgets from the title width,
        // then recenters them from the final card box after the clamp loop.
        const title_center_offset = title_rect.left + title_rect.width * 0.5 - 320.0;

        var primary_text_rect = frontend_widget.widgetTextRect(
            font,
            .menu_button,
            .center,
            primary_action,
            frontend_widget.stackBelowWithGap(body_rect, route_map_primary_button_gap),
            title_center_offset,
        );
        var replay_text_rect: ?frontend_widget.Rect = null;
        if (replay_action) |label| {
            replay_text_rect = frontend_widget.widgetTextRect(
                font,
                .route_map_secondary_action,
                .center,
                label,
                frontend_widget.stackBelowWithGap(body_rect, route_map_replay_button_gap),
                title_center_offset,
            );
            primary_text_rect = frontend_widget.widgetTextRect(
                font,
                .menu_button,
                .center,
                primary_action,
                frontend_widget.stackBelowWithGap(replay_text_rect.?, route_map_primary_button_gap),
                title_center_offset,
            );
        }

        var left = @min(title_rect.left, @min(subtitle_rect.left, @min(body_rect.left, primary_text_rect.left)));
        const top = @min(title_rect.top, @min(subtitle_rect.top, @min(body_rect.top, primary_text_rect.top)));
        var right = @max(
            title_rect.left + title_rect.width,
            @max(
                subtitle_rect.left + subtitle_rect.width,
                @max(body_rect.left + body_rect.width, primary_text_rect.left + primary_text_rect.width),
            ),
        );
        var bottom = @max(
            title_rect.top + title_rect.height,
            @max(
                subtitle_rect.top + subtitle_rect.height,
                @max(body_rect.top + body_rect.height, primary_text_rect.top + primary_text_rect.height),
            ),
        );
        // PORT(verified): `open_galaxy_route` clamps the selected card against the title,
        // subtitle, body, and primary action widgets only. The replay action is recentered
        // from the finished card box afterwards, but it does not expand the box bounds.
        left -= route_map_card_horizontal_padding;
        right += route_map_card_horizontal_padding;
        bottom += route_map_card_bottom_padding;

        var adjusted = false;
        if (right > route_map_card_right_limit) {
            title_left = route_point.x - (right - left) - 40.0;
            adjusted = true;
        }
        if (top < route_map_card_min_top) {
            title_top = 50.0;
            adjusted = true;
        }
        if (bottom > route_map_card_bottom_y) {
            title_top = route_map_card_bottom_y - (bottom - top);
            adjusted = true;
        }
        if (adjusted) continue;

        const card_rect: frontend_widget.Rect = .{
            .left = left,
            .top = top,
            .width = right - left,
            .height = bottom - top,
        };
        const card_center_offset = card_rect.left + card_rect.width * 0.5 - 320.0;
        primary_text_rect = frontend_widget.widgetTextRect(
            font,
            .menu_button,
            .center,
            primary_action,
            primary_text_rect.top,
            card_center_offset,
        );
        if (replay_action) |label| {
            if (replay_text_rect) |replay_rect| {
                replay_text_rect = frontend_widget.widgetTextRect(
                    font,
                    .route_map_secondary_action,
                    .center,
                    label,
                    replay_rect.top,
                    card_center_offset,
                );
            }
        }
        const pointer_start_x = if (card_rect.left <= route_point.x)
            route_point.x - route_map_card_star_gap
        else
            route_point.x + route_map_card_star_gap;
        const pointer_end_x = if (card_rect.left <= route_point.x)
            card_rect.left + card_rect.width + route_map_card_horizontal_pointer_gap
        else
            card_rect.left - route_map_card_horizontal_pointer_gap;
        return .{
            .card_rect = card_rect,
            .title_rect = title_rect,
            .subtitle_rect = subtitle_rect,
            .body_rect = body_rect,
            .primary_text_rect = primary_text_rect,
            .replay_text_rect = replay_text_rect,
            .pointer_start = .{ .x = pointer_start_x, .y = route_point.y },
            .pointer_end = .{ .x = pointer_end_x, .y = route_point.y },
        };
    }
}

fn routeMapPointForRouteIndex(state: *const AppState, route_index: usize) ?galaxy.Point {
    if (state.galaxy_names) |names| {
        if (names.routePointForRouteIndex(route_index)) |point| return point;
    }
    return galaxy.routePointForRouteIndex(route_index);
}

fn routeMapHoveredRouteIndex(state: *const AppState, local_mouse: rl.Vector2, route_limit: usize) ?usize {
    if (route_limit == 0) return null;

    const selection_radius_squared = 17.0 * 17.0;
    for (1..@min(route_limit, galaxy.map_route_count) + 1) |route_index| {
        const point = routeMapPointForRouteIndex(state, route_index) orelse continue;
        const dx = point.x - local_mouse.x;
        const dy = point.y - local_mouse.y;
        if (dx * dx + dy * dy < selection_radius_squared) {
            return route_index;
        }
    }
    return null;
}

fn drawRouteMapConnection(
    layout: VirtualLayout,
    start_point: galaxy.Point,
    end_point: galaxy.Point,
    line_texture: ?assets.LoadedTexture,
    authored_width: f32,
    tint: rl.Color,
) void {
    const start = layout.mapPoint(start_point.x, start_point.y);
    const end = layout.mapPoint(end_point.x, end_point.y);
    const dx = end.x - start.x;
    const dy = end.y - start.y;
    const length = std.math.sqrt(dx * dx + dy * dy);
    if (length <= 0.01) return;

    if (line_texture) |loaded_texture| {
        const scaled_width = layout.scaleFloat(authored_width);
        rl.drawTexturePro(
            loaded_texture.texture,
            .{
                .x = 0.0,
                .y = 0.0,
                .width = @as(f32, @floatFromInt(loaded_texture.texture.width)),
                .height = @as(f32, @floatFromInt(loaded_texture.texture.height)),
            },
            .{
                .x = start.x,
                .y = start.y,
                .width = length,
                .height = scaled_width,
            },
            .{ .x = 0.0, .y = scaled_width * 0.5 },
            @as(f32, @floatCast(std.math.atan2(dy, dx) * 180.0 / std.math.pi)),
            tint,
        );
    } else {
        rl.drawLineEx(start, end, layout.scaleFloat(authored_width), tint);
    }
}

fn drawRouteMapStars(state: *const AppState, layout: VirtualLayout, mode: FrontendLevelMode) void {
    const available_limit = state.availableFrontendRouteLimit(mode);
    const active_route_index = state.currentRouteMapOpenIndex() orelse state.frontend_route_index;
    const selected_galaxy_index = if (state.galaxy_names) |names|
        names.galaxyIndexForRouteIndex(state.frontend_route_index)
    else
        null;
    for (0..galaxy.map_galaxy_count) |galaxy_index| {
        const center = galaxy.galaxyCenter(galaxy_index);
        if (state.route_map_art.galaxies[galaxy_index]) |loaded_texture| {
            drawTextureCenteredLocal(layout, loaded_texture, center.x, center.y, route_map_galaxy_size, route_map_galaxy_size, .white);
        }
    }

    if (state.galaxy_names) |names| {
        if (selected_galaxy_index) |galaxy_index| {
            var route_cursor: usize = 0;
            for (0..galaxy_index) |prior_index| {
                route_cursor += names.starCountForGalaxyIndex(prior_index) orelse 0;
            }
            const star_count = names.starCountForGalaxyIndex(galaxy_index) orelse 0;
            var visible_star_count = if (available_limit > route_cursor)
                @min(star_count, available_limit - route_cursor)
            else
                0;
            // PORT(verified): the postal post-completion Star Map variant (`this + 4 == 1`)
            // stops drawing future route stars once it reaches the current route. Only the
            // normal/replay variants keep the remainder of the available route strip visible.
            if (state.route_map_screen_mode == .post_completion_exit and active_route_index > route_cursor) {
                visible_star_count = @min(visible_star_count, active_route_index - route_cursor);
            }

            if (visible_star_count >= 2) {
                for (0..visible_star_count - 1) |local_index| {
                    const start_route_index = route_cursor + local_index + 1;
                    const end_route_index = start_route_index + 1;
                    // PORT(verified): `update_galaxy` iterates route links only up to the
                    // live available-route count in `dword_4DF9B8`, then shades them in two
                    // authored bands: `0.8` before the current route and `0.2` afterwards.
                    // The postal post-completion variant omits the later `0.2` links entirely.
                    if (state.route_map_screen_mode == .post_completion_exit and start_route_index >= active_route_index) continue;
                    const line_tint: rl.Color = if (start_route_index < active_route_index)
                        .{ .r = 255, .g = 255, .b = 255, .a = 204 }
                    else
                        .{ .r = 255, .g = 255, .b = 255, .a = 51 };
                    drawRouteMapConnection(
                        layout,
                        names.routePointForRouteIndex(start_route_index).?,
                        names.routePointForRouteIndex(end_route_index).?,
                        state.route_map_art.line,
                        route_map_path_line_width,
                        line_tint,
                    );
                }
            }

            for (0..visible_star_count) |local_index| {
                const route_index = route_cursor + local_index + 1;
                const point = names.routePointForRouteIndex(route_index).?;
                if (state.route_map_art.level_star) |loaded_texture| {
                    drawTextureCenteredLocal(layout, loaded_texture, point.x, point.y, 32.0, 32.0, .white);
                }
            }
        }
    }

    for (1..@min(available_limit, galaxy.map_route_count) + 1) |route_index| {
        const highlight_alpha = state.route_map_route_highlight_alpha[route_index];
        if (highlight_alpha <= 0.001) continue;
        if (routeMapPointForRouteIndex(state, route_index)) |selected_point| {
            if (state.route_map_art.level_select) |loaded_texture| {
                drawTextureCenteredLocal(
                    layout,
                    loaded_texture,
                    selected_point.x,
                    selected_point.y,
                    64.0,
                    64.0,
                    .{
                        .r = 255,
                        .g = 255,
                        .b = 255,
                        .a = @intFromFloat(std.math.clamp(highlight_alpha * 255.0, 0.0, 255.0)),
                    },
                );
            }
        }
    }
}

fn drawRouteMapCard(
    state: *const AppState,
    layout: VirtualLayout,
    card_layout: RouteMapCardLayout,
    route_galaxy_name: []const u8,
    route_level_name: []const u8,
    route_body: []const u8,
    primary_action: []const u8,
    replay_action: ?[]const u8,
) void {
    if (state.route_map_art.border) |loaded_texture| {
        frontend_widget.drawNineSliceFrame(
            layout,
            loaded_texture.texture,
            card_layout.card_rect,
            route_map_card_frame_edge,
            route_map_card_frame_edge / 128.0,
            .white,
        );
    }

    drawUiFontTextRect(state, layout, route_galaxy_name, card_layout.title_rect, route_map_card_title_scale, .ray_white);
    drawUiFontTextRect(state, layout, route_level_name, card_layout.subtitle_rect, route_map_card_subtitle_scale, .ray_white);
    drawUiFontTextRect(state, layout, route_body, card_layout.body_rect, route_map_card_body_scale, .ray_white);

    const widget_art: frontend_widget.Art = .{
        .border = state.frontend_widget_art.border.?.texture,
    };
    frontend_widget.drawType20Button(
        layout,
        widget_art,
        &state.ui_font,
        primary_action,
        card_layout.primary_text_rect,
        state.route_map_button_states[route_map_primary_button_index],
        false,
    );
    if (replay_action) |label| {
        if (card_layout.replay_text_rect) |replay_text_rect| {
            frontend_widget.drawTextButton(
                layout,
                widget_art,
                &state.ui_font,
                .route_map_secondary_action,
                label,
                replay_text_rect,
                state.route_map_button_states[route_map_replay_button_index],
                false,
            );
        }
    }
}

fn drawRouteMapLogo(state: *const AppState, layout: VirtualLayout) void {
    const loaded_texture = state.route_map_art.logo orelse return;
    drawTextureLocalRect(
        layout,
        loaded_texture,
        route_map_logo_x,
        route_map_logo_y,
        route_map_logo_width,
        route_map_logo_height,
        .white,
    );
}

fn drawFrontendStatusMessage(state: *const AppState, layout: VirtualLayout, message: []const u8) !void {
    try drawFrontendNoticeBlock(state, layout, app_ui.authored_width * 0.5, 438.0, message, .ray_white);
}

fn drawFrontendNoticeBlock(
    state: *const AppState,
    layout: VirtualLayout,
    center_x: f32,
    local_y: f32,
    message: []const u8,
    color: rl.Color,
) !void {
    var line_buffer: [512]u8 = undefined;
    var line_index: i32 = 0;
    var parts = std.mem.tokenizeAny(u8, message, ">\n");
    while (parts.next()) |part| {
        const trimmed = std.mem.trim(u8, part, " \t\r");
        if (trimmed.len == 0) continue;
        const clipped = if (trimmed.len > line_buffer.len - 1) trimmed[0 .. line_buffer.len - 1] else trimmed;
        @memcpy(line_buffer[0..clipped.len], clipped);
        line_buffer[clipped.len] = 0;
        drawFrontendTextAligned(
            state,
            layout,
            center_x,
            local_y + @as(f32, @floatFromInt(line_index * 20)),
            line_buffer[0..clipped.len],
            20,
            color,
            .center,
        );
        line_index += 1;
    }
}

fn highScoreScreenTitle(mode: high_score.Mode) []const u8 {
    return switch (mode) {
        .postal => "Postal High Scores",
        .challenge => "Challenge High Scores",
    };
}

fn highScoreTableToggleLabel(mode: high_score.Mode) []const u8 {
    return switch (mode) {
        .postal => "Challenge Score",
        .challenge => "Postal Scores",
    };
}

fn completionHasBonusLine(result: PendingRunResult) bool {
    return result.outcome == .completed and result.score_totals.completion_bonus > 0;
}

fn completionRevealTarget(result: PendingRunResult) f32 {
    if (result.outcome != .completed) return completion_reveal_bonus_threshold;
    return if (completionHasBonusLine(result))
        completion_reveal_continue_threshold
    else
        completion_reveal_bonus_threshold;
}

fn completionBonusVisibleAtProgress(result: PendingRunResult, progress: f32) bool {
    return completionHasBonusLine(result) and progress >= completion_reveal_bonus_threshold;
}

fn completionContinueVisibleAtProgress(result: PendingRunResult, progress: f32) bool {
    return progress >= if (completionHasBonusLine(result))
        completion_reveal_continue_threshold
    else
        completion_reveal_bonus_threshold;
}

fn completionPackageLine(buffer: []u8, result: PendingRunResult) ![]const u8 {
    return if (result.parcel_count == 1)
        std.fmt.bufPrint(buffer, "1 Package Delivered", .{})
    else
        std.fmt.bufPrint(buffer, "{d:0>2} Packages Delivered", .{result.parcel_count});
}

fn completionBonusLine(buffer: []u8, result: PendingRunResult) !?[]const u8 {
    if (!completionHasBonusLine(result)) return null;
    if (result.score_totals.completion_bonus == 50_000 and result.parcel_count == result.parcel_target) {
        return try std.fmt.bufPrint(buffer, "Perfect Score! 50,000 Bonus Points!", .{});
    }
    return try std.fmt.bufPrint(buffer, "{d} Bonus Points!", .{result.score_totals.completion_bonus});
}

fn resultReturnTargetForOutcome(outcome: RunOutcome, mode: ?FrontendLevelMode) ResultReturnTarget {
    if (outcome == .failed) {
        return switch (mode orelse .postal) {
            // PORT(verified): ordinary postal final-loss uses the outer bridge's
            // `26 -> 2` return when replay-backed routing and the post-level high-score
            // owner do not override it.
            .postal => .new_game_menu,
            .challenge => .main_menu,
            .time_trial => .main_menu,
            .tutorial => .main_menu,
        };
    }
    return switch (mode orelse .postal) {
        .postal => .postal_route_map,
        .time_trial => .time_trial_route_map,
        .challenge => .replay_current_level,
        // PORT(verified): tutorial completion forces the outer bridge's `26 -> 2` path in
        // `update_subgoldy`, so the native return target is the New Game owner.
        .tutorial => .new_game_menu,
    };
}

fn postalCompletionReturnTarget(current_index: usize, highest_available: usize) ResultReturnTarget {
    return if (AppState.postalCompletionCommitsHighScore(current_index, highest_available))
        .thanks_screen
    else
        .postal_route_map;
}

const FrontendModeDispatch = struct {
    session_mode: gameplay.SessionMode,
    runtime_build_flags: u32,
    completion_bonus_enabled: bool,
};

fn frontendModeDispatch(mode: ?FrontendLevelMode) FrontendModeDispatch {
    // PORT(verified): the native subgame keeps one shared gameplay sim and dispatches most
    // mode differences through a small mode-to-config lane in `set_subgame_features` and
    // `build_subgame_level`. Keep the shared runner wiring centralized here instead of
    // scattering per-mode switches across unrelated helpers.
    return switch (mode orelse .postal) {
        .postal => .{
            .session_mode = .postal,
            .runtime_build_flags = track.postalChallengeRuntimeBuildFlags,
            .completion_bonus_enabled = true,
        },
        .challenge => .{
            .session_mode = .challenge,
            .runtime_build_flags = track.postalChallengeRuntimeBuildFlags,
            .completion_bonus_enabled = false,
        },
        .time_trial => .{
            .session_mode = .time_trial,
            .runtime_build_flags = track.timeTrialRuntimeBuildFlags,
            .completion_bonus_enabled = false,
        },
        .tutorial => .{
            .session_mode = .tutorial,
            .runtime_build_flags = track.tutorialRuntimeBuildFlags,
            .completion_bonus_enabled = false,
        },
    };
}

fn runnerSessionModeForFrontendMode(mode: ?FrontendLevelMode) gameplay.SessionMode {
    return frontendModeDispatch(mode).session_mode;
}

fn completionBonusAppliesForMode(mode: ?FrontendLevelMode) bool {
    return frontendModeDispatch(mode).completion_bonus_enabled;
}

fn routeMapHasReplayEntry(
    mode: ?FrontendLevelMode,
    route_index: usize,
    tables: *const high_score.Tables,
) bool {
    // PORT(verified): `open_galaxy_route` only reveals the replay action when the Star Map
    // controller is in its time-trial mode (`this + 4 == 2`) and the selected completion
    // slot reports state `1`. The closest persisted Windows-equivalent signal in the port
    // is a ScoreC completion entry with replay samples still present.
    if (mode != .time_trial) return false;
    const completion_index = high_score.completionIndexForRouteIndex(route_index) orelse return false;
    return tables.completion[completion_index].has_replay;
}

fn completionElapsedMillis(runner: gameplay.Runner) u32 {
    return runner.stopwatch.elapsedMillis();
}

fn formatElapsedMillis(buffer: []u8, elapsed_millis: u32) ![]const u8 {
    const total_seconds = @divTrunc(elapsed_millis, 1000);
    const minutes = @divTrunc(total_seconds, 60);
    const seconds = @mod(total_seconds, 60);
    const centiseconds = @divTrunc(@mod(elapsed_millis, 1000), 10);
    return std.fmt.bufPrint(buffer, "{d:0>2}:{d:0>2}.{d:0>2}", .{ minutes, seconds, centiseconds });
}

// PORT(partial): this now follows the recovered Windows `cRSubGoldy::ScoreAdd` constants for the
// score events the current runner actually models:
// ring collect (+100 for the scoring ring families), parcel pickup/register (+100 each), and the
// postal-only completion bonus (+50,000). Health pickup no longer scores in the Windows-targeted path.
// Slug kills (+500), garbage-side score events (+10),
// jetpack/speed-up scoring, and the rest of the original `cRSubGoldy::AI()` path remain unported.
fn bootPhaseProgress(state: *const AppState) f32 {
    if (boot_tasks.len == 0) return 1.0;
    return std.math.clamp(
        @as(f32, @floatFromInt(state.boot_task_index)) / @as(f32, @floatFromInt(boot_tasks.len)),
        0.0,
        1.0,
    );
}

fn drawCurrentTextScript(state: *const AppState, layout: VirtualLayout) void {
    const script = state.currentTextScript() orelse return;
    const progress = state.currentTextScriptProgress() orelse 0.0;
    script.drawCrawl(&state.ui_font, progress, .{
        .x = layout.x,
        .y = layout.y,
        .width = layout.width,
        .height = layout.height,
    });
}

fn drawHelpUi(state: *const AppState, layout: VirtualLayout) void {
    frontend_widget.drawType20Button(
        layout,
        .{
            .border = state.frontend_widget_art.border.?.texture,
        },
        &state.ui_font,
        "Back",
        helpBackTextRect(&state.ui_font),
        state.help_button_states[0],
        false,
    );
}

fn resultTitle(result: PendingRunResult) []const u8 {
    return switch (result.outcome) {
        .completed => if (result.mode) |mode|
            switch (mode) {
                .postal => "Delivery Complete!",
                .time_trial => "Route Complete",
                .challenge => "Challenge Complete",
                .tutorial => "Tutorial Complete",
            }
        else
            "Level Complete",
        .failed => if (result.mode) |mode|
            switch (mode) {
                .postal => "Game Over",
                .time_trial => "Route Failed",
                .challenge => "Challenge Failed",
                .tutorial => "Tutorial Failed",
            }
        else
            "Run Failed",
    };
}

fn drawGameplayLevelUi(state: *const AppState, layout: VirtualLayout) !void {
    drawGameplayLevelViewport(state);

    const loaded_level = state.current_level orelse return;
    if (state.level_runner) |runner| {
        if (state.isTutorialGameplay()) {
            try drawTutorialGameplayUi(state, layout, loaded_level, runner);
        } else {
            const hud_panel = layout.mapRect(16.0, 14.0, 360.0, 58.0);
            rl.drawRectangleRounded(hud_panel, 0.08, 8, .{ .r = 0, .g = 0, .b = 0, .a = 176 });

            const title_point = layout.mapPoint(28.0, 24.0);
            const meta_point = layout.mapPoint(28.0, 50.0);
            const parcel_target = state.currentParcelTarget();
            const parcel_count = runner.counters.parcels;
            const score_total = runner.score.total;
            const elapsed_millis = runner.stopwatch.elapsedMillis();
            const title_text = gameplayHudTitle(loaded_level, runner);
            const package_icon = game_font.IconGlyph.package.byte();
            const title_font_size = layout.fontSize(28);
            const body_font_size = layout.fontSize(18);

            drawAppText(state, title_text, @intFromFloat(title_point.x), @intFromFloat(title_point.y), title_font_size, .gold);

            var elapsed_buffer: [32]u8 = undefined;
            const elapsed_text = try formatElapsedMillis(&elapsed_buffer, elapsed_millis);
            var meta_buffer: [256]u8 = undefined;
            const meta_text = if (parcel_target > 0)
                try std.fmt.bufPrintZ(
                    &meta_buffer,
                    "{c} {d}/{d}   Score {d}   Time {s}",
                    .{ package_icon, parcel_count, parcel_target, score_total, elapsed_text },
                )
            else
                try std.fmt.bufPrintZ(&meta_buffer, "Score {d}   Time {s}", .{ score_total, elapsed_text });
            drawAppText(state, meta_text, @intFromFloat(meta_point.x), @intFromFloat(meta_point.y), body_font_size, .ray_white);

            drawGameplayStatusWidgets(state, layout, runner);
            try drawGameplayPromptStack(state, layout, &state.level_prompt_queue);
        }
    }

    if (state.completionScreenOverlayActive()) {
        try drawCompletionScreenUi(state, layout);
    }
}

fn gameplayHudTitle(loaded_level: level.Definition, runner: gameplay.Runner) [:0]const u8 {
    _ = loaded_level;
    return switch (runner.session_mode) {
        .tutorial => "Snail Mail 101",
        else => "Snail Mail",
    };
}

const gameplay_prompt_anchor_y: f32 = 330.0;
const tutorial_prompt_anchor_y: f32 = 116.0;
const tutorial_prompt_interactive_anchor_y: f32 = 176.0;

const ActiveLevelPromptLayout = struct {
    lines: [frontend_widget.multiline_prompt_max_lines][]const u8 = [_][]const u8{""} ** frontend_widget.multiline_prompt_max_lines,
    line_count: usize = 0,
    widget_layout: frontend_widget.MultilinePromptLayout = .{},
};

fn levelPromptLines(text: []const u8, lines: *[frontend_widget.multiline_prompt_max_lines][]const u8) []const []const u8 {
    var count: usize = 0;
    var start: usize = 0;
    for (text, 0..) |char, index| {
        if (char != '>') continue;
        if (count < lines.len) {
            lines[count] = text[start..index];
            count += 1;
        }
        start = index + 1;
    }
    if (count < lines.len) {
        lines[count] = text[start..];
        count += 1;
    }
    return lines[0..count];
}

fn levelPromptAnchorY(tutorial: bool, interactive: bool) f32 {
    if (!tutorial) return gameplay_prompt_anchor_y;
    return if (interactive) tutorial_prompt_interactive_anchor_y else tutorial_prompt_anchor_y;
}

fn activeLevelPromptLayout(state: *const AppState, prompt: level_prompt.Entry, tutorial: bool) ActiveLevelPromptLayout {
    return promptLayoutForText(state, prompt.message, tutorial, prompt.interactive);
}

fn promptLayoutForText(state: *const AppState, text: []const u8, tutorial: bool, interactive: bool) ActiveLevelPromptLayout {
    var prompt_layout = ActiveLevelPromptLayout{};
    const lines = levelPromptLines(text, &prompt_layout.lines);
    prompt_layout.line_count = lines.len;
    prompt_layout.widget_layout = frontend_widget.type20PromptLayout(
        &state.ui_font,
        lines,
        levelPromptAnchorY(tutorial, interactive),
        interactive,
    );
    return prompt_layout;
}

fn activeLevelPromptOkHitRect(state: *const AppState, queue: *const level_prompt.Queue, tutorial: bool) ?frontend_widget.Rect {
    const prompt = queue.active() orelse return null;
    if (!prompt.interactive) return null;
    const prompt_layout = activeLevelPromptLayout(state, prompt, tutorial);
    const ok_text_rect = prompt_layout.widget_layout.ok_text_rect orelse return null;
    var idle_state = frontend_widget.TextButtonState{};
    idle_state.snapFor(.menu_button, false);
    return frontend_widget.hitRect(ok_text_rect, idle_state);
}

fn drawLevelPromptMessageLines(state: *const AppState, layout: VirtualLayout, prompt_layout: ActiveLevelPromptLayout) void {
    const widget_art: frontend_widget.Art = .{
        .border = state.frontend_widget_art.border.?.texture,
    };
    for (0..prompt_layout.line_count) |index| {
        const line = prompt_layout.lines[index];
        var text_state = frontend_widget.TextButtonState{};
        text_state.snapFor(.menu_button, true);
        frontend_widget.drawTextButtonWithOptions(
            layout,
            widget_art,
            &state.ui_font,
            .menu_button,
            line,
            prompt_layout.widget_layout.line_rects[index],
            text_state,
            false,
            .{ .flags = @intFromEnum(frontend_widget.WidgetFlags.invisible_background) },
        );
    }
}

fn drawLevelPromptWidget(state: *const AppState, layout: VirtualLayout, queue: *const level_prompt.Queue, tutorial: bool) !void {
    const prompt = queue.active() orelse return;
    const prompt_layout = activeLevelPromptLayout(state, prompt, tutorial);
    var frame_state = frontend_widget.TextButtonState{};
    frame_state.snapFor(.menu_button, false);
    const colors = frontend_widget.colorsForState(frame_state, false);
    frontend_widget.drawNineSliceFrame(
        layout,
        state.frontend_widget_art.border.?.texture,
        prompt_layout.widget_layout.frame_rect,
        frontend_widget.type20_border_edge,
        frontend_widget.type20_border_edge / 128.0,
        colors.fill,
    );
    drawLevelPromptMessageLines(state, layout, prompt_layout);

    if (prompt_layout.widget_layout.ok_text_rect) |ok_text_rect| {
        var idle_state = frontend_widget.TextButtonState{};
        idle_state.snapFor(.menu_button, false);
        const hit_rect = frontend_widget.hitRect(ok_text_rect, idle_state);
        const hovered = if (state.currentUiMouseLocal()) |mouse|
            hit_rect.contains(mouse)
        else
            false;
        var ok_state = frontend_widget.TextButtonState{};
        ok_state.snapFor(.menu_button, hovered);
        frontend_widget.drawTextButton(
            layout,
            .{ .border = state.frontend_widget_art.border.?.texture },
            &state.ui_font,
            .menu_button,
            "OK",
            ok_text_rect,
            ok_state,
            false,
        );
    }
}

fn drawGameplayPromptStack(state: *const AppState, layout: VirtualLayout, queue: *const level_prompt.Queue) !void {
    try drawLevelPromptWidget(state, layout, queue, false);
}

fn drawStaticPromptWidget(state: *const AppState, layout: VirtualLayout, text: []const u8, tutorial: bool) void {
    const prompt_layout = promptLayoutForText(state, text, tutorial, false);
    drawLevelPromptMessageLines(state, layout, prompt_layout);
}

fn drawTutorialPromptStack(state: *const AppState, layout: VirtualLayout, queue: *const level_prompt.Queue) !void {
    try drawLevelPromptWidget(state, layout, queue, true);
}

fn drawTutorialGameplayUi(state: *const AppState, layout: VirtualLayout, loaded_level: level.Definition, runner: gameplay.Runner) !void {
    try drawTutorialGameplayHud(state, layout, loaded_level, runner);
    drawTutorialProgressBar(state, layout, runner);
    drawTutorialLives(state, layout, runner.visible_life_stock);
    drawDamageGaugeWidget(state, layout, runner, false);
    if (runner.jetpack.active) {
        drawJetpackGaugeWidget(state, layout, runner);
    }
    if (state.gameplay_click_start_active) {
        if (!state.tutorialClickStartCutsceneActive()) {
            drawStaticPromptWidget(state, layout, "Click to Start", true);
        }
        return;
    }
    try drawTutorialPromptStack(state, layout, &state.level_prompt_queue);
}

fn tutorialGameplayBestScore(state: *const AppState) u32 {
    return state.tutorial_reference_score;
}

fn drawTutorialGameplayHud(state: *const AppState, layout: VirtualLayout, loaded_level: level.Definition, runner: gameplay.Runner) !void {
    _ = loaded_level;
    const parcel_target = state.currentParcelTarget();
    const parcel_count = runner.counters.parcels;

    var parcel_buffer: [32]u8 = undefined;
    const parcel_text = if (parcel_target > 0)
        try std.fmt.bufPrint(&parcel_buffer, "{d}/{d}", .{ parcel_count, parcel_target })
    else
        try std.fmt.bufPrint(&parcel_buffer, "{d}", .{parcel_count});
    drawGameplayIconCounter(
        state,
        layout,
        .package,
        parcel_text,
        12.0,
        10.0,
        22,
        .white,
    );

    const best_score = tutorialGameplayBestScore(state);
    if (best_score > 0) {
        var best_buffer: [32]u8 = undefined;
        const best_text = try formatScoreWithCommas(&best_buffer, best_score);
        drawCenteredGameplayHudTextShadowed(state, layout, 320.0, 10.0, best_text, 22, .white);
    }

    var score_buffer: [32]u8 = undefined;
    const score_text = try formatScoreWithCommas(&score_buffer, runner.score.total);
    drawRightAlignedGameplayHudTextShadowed(state, layout, 628.0, 10.0, score_text, 22, .white);
}

fn drawCenteredGameplayHudText(
    state: *const AppState,
    layout: VirtualLayout,
    authored_center_x: f32,
    authored_y: f32,
    text: []const u8,
    authored_size: i32,
    color: rl.Color,
) void {
    const font_size = layout.fontSize(authored_size);
    const width = measureAppText(state, text, font_size);
    const point = layout.mapPoint(authored_center_x, authored_y);
    drawAppText(state, text, @intFromFloat(point.x - @as(f32, @floatFromInt(width)) * 0.5), @intFromFloat(point.y), font_size, color);
}

fn drawGameplayHudTextShadowed(
    state: *const AppState,
    layout: VirtualLayout,
    authored_x: f32,
    authored_y: f32,
    text: []const u8,
    authored_size: i32,
    color: rl.Color,
) void {
    const font_size = layout.fontSize(authored_size);
    const point = layout.mapPoint(authored_x, authored_y);
    drawAppText(state, text, @intFromFloat(point.x + layout.scaleFloat(2.0)), @intFromFloat(point.y + layout.scaleFloat(2.0)), font_size, .black);
    drawAppText(state, text, @intFromFloat(point.x), @intFromFloat(point.y), font_size, color);
}

fn drawRightAlignedGameplayHudTextShadowed(
    state: *const AppState,
    layout: VirtualLayout,
    authored_right_x: f32,
    authored_y: f32,
    text: []const u8,
    authored_size: i32,
    color: rl.Color,
) void {
    const font_size = layout.fontSize(authored_size);
    const width = measureAppText(state, text, font_size);
    drawGameplayHudTextShadowed(
        state,
        layout,
        authored_right_x - @as(f32, @floatFromInt(width)),
        authored_y,
        text,
        authored_size,
        color,
    );
}

fn drawCenteredGameplayHudTextShadowed(
    state: *const AppState,
    layout: VirtualLayout,
    authored_center_x: f32,
    authored_y: f32,
    text: []const u8,
    authored_size: i32,
    color: rl.Color,
) void {
    const font_size = layout.fontSize(authored_size);
    const width = measureAppText(state, text, font_size);
    drawGameplayHudTextShadowed(
        state,
        layout,
        authored_center_x - @as(f32, @floatFromInt(width)) * 0.5,
        authored_y,
        text,
        authored_size,
        color,
    );
}

fn drawGameplayIconCounter(
    state: *const AppState,
    layout: VirtualLayout,
    glyph: game_font.IconGlyph,
    text: []const u8,
    authored_x: f32,
    authored_y: f32,
    authored_size: i32,
    color: rl.Color,
) void {
    const font_size = layout.fontSize(authored_size);
    const point = layout.mapPoint(authored_x, authored_y);
    state.ui_font.drawText(&[_]u8{glyph.byte()}, point.x, point.y, @floatFromInt(font_size), .white);
    drawAppText(state, text, @intFromFloat(point.x + layout.scaleFloat(26.0)), @intFromFloat(point.y), font_size, color);
}

fn deterministicGameplayAmbientSlugRoll(row: usize, lane: usize) f32 {
    const mixed = (@as(u64, row) *% 0x9e3779b97f4a7c15) ^ (@as(u64, lane) *% 0xc2b2ae3d27d4eb4f);
    const normalized = @as(f64, @floatFromInt(mixed & 0xffff)) / 65535.0;
    return @floatCast(normalized);
}

fn drawTutorialProgressBar(state: *const AppState, layout: VirtualLayout, runner: gameplay.Runner) void {
    const preview = state.current_track_preview orelse return;
    const total_rows = @max(preview.total_rows, 1);
    const progress = std.math.clamp(runner.row_position / @as(f32, @floatFromInt(total_rows)), 0.0, 1.0);
    const remaining_height = (1.0 - progress) * 232.0 + 12.0;
    if (state.current_gameplay_sprites.progress_bar_lit) |loaded_texture| {
        drawTextureLocalRectSource(
            layout,
            loaded_texture,
            rl.Rectangle{
                .x = 0.0,
                .y = 0.0,
                .width = @floatFromInt(loaded_texture.texture.width),
                .height = remaining_height,
            },
            13.0,
            150.0,
            64.0,
            remaining_height,
            .white,
        );
    }
    if (state.current_gameplay_sprites.progress_bar) |loaded_texture| {
        drawTextureLocalRectSource(
            layout,
            loaded_texture,
            rl.Rectangle{
                .x = 0.0,
                .y = remaining_height,
                .width = @floatFromInt(loaded_texture.texture.width),
                .height = 256.0 - remaining_height,
            },
            13.0,
            150.0 + remaining_height,
            64.0,
            256.0 - remaining_height,
            .white,
        );
    }
    if (state.current_gameplay_sprites.progress_cursor) |loaded_texture| {
        drawTextureLocalRect(
            layout,
            loaded_texture,
            12.0,
            remaining_height + 111.0,
            64.0,
            64.0,
            .white,
        );
    }
}

fn drawTutorialLives(state: *const AppState, layout: VirtualLayout, visible_life_stock: u32) void {
    const count = @min(visible_life_stock, 9);
    const loaded_texture = state.current_gameplay_sprites.life orelse return;
    for (0..count) |slot_index| {
        drawTextureLocalRect(
            layout,
            loaded_texture,
            12.0 + @as(f32, @floatFromInt(slot_index)) * 20.0,
            438.0,
            32.0,
            32.0,
            .white,
        );
    }
}

fn formatScoreWithCommas(buffer: []u8, score: u32) ![:0]const u8 {
    var digits_buffer: [16]u8 = undefined;
    const digits = try std.fmt.bufPrint(&digits_buffer, "{d}", .{score});

    var write_index: usize = 0;
    const remainder = digits.len % 3;
    for (digits, 0..) |digit, index| {
        if (index != 0 and (index % 3 == remainder or (remainder == 0 and index % 3 == 0))) {
            if (write_index >= buffer.len - 1) return error.NoSpaceLeft;
            buffer[write_index] = ',';
            write_index += 1;
        }
        if (write_index >= buffer.len - 1) return error.NoSpaceLeft;
        buffer[write_index] = digit;
        write_index += 1;
    }
    if (write_index >= buffer.len) return error.NoSpaceLeft;
    buffer[write_index] = 0;
    return buffer[0..write_index :0];
}

fn drawGameplayStatusWidgets(state: *const AppState, layout: VirtualLayout, runner: gameplay.Runner) void {
    drawJetpackGaugeWidget(state, layout, runner);
    drawDamageGaugeWidget(state, layout, runner, true);
    if (runner.session_mode == .postal) {
        drawVisibleLifeStrip(state, layout, runner.visible_life_stock);
    }
}

fn drawJetpackGaugeWidget(state: *const AppState, layout: VirtualLayout, runner: gameplay.Runner) void {
    if (!runner.jetpack.active) return;

    const panel = layout.mapRect(548.0, 108.0, 28.0, 224.0);
    const fill_margin = layout.scaleFloat(4.0);
    const fill_height = @max(panel.height - fill_margin * 2.0, 0.0);
    const fill_width = @max(panel.width - fill_margin * 2.0, 0.0);
    const fill_ratio = runner.jetpackFuelRemaining();
    const active_fill_height = fill_height * fill_ratio;
    const pulse = if (runner.jetpack.warning_band == .near_empty) runner.jetpack.pulse_envelope else @as(f32, 0.0);
    const outline_alpha: u8 = @intFromFloat(160.0 + 64.0 * pulse);
    const label_y: i32 = @intFromFloat(panel.y - layout.scaleFloat(20.0));
    const fill_color = jetpackGaugeColor(runner.jetpack.warning_band, pulse);

    drawAppText(state, "Jet", @intFromFloat(panel.x + layout.scaleFloat(2.0)), label_y, layout.fontSize(16), .light_gray);
    rl.drawRectangleRounded(panel, 0.18, 8, .{ .r = 0, .g = 0, .b = 0, .a = 176 });

    const inner = rl.Rectangle{
        .x = panel.x + fill_margin,
        .y = panel.y + fill_margin,
        .width = fill_width,
        .height = fill_height,
    };
    rl.drawRectangleRounded(inner, 0.12, 6, .{ .r = 255, .g = 255, .b = 255, .a = 20 });

    if (active_fill_height > 0.0) {
        const fill_rect = rl.Rectangle{
            .x = inner.x,
            .y = inner.y + (fill_height - active_fill_height),
            .width = fill_width,
            .height = active_fill_height,
        };
        rl.drawRectangleRounded(fill_rect, 0.12, 6, fill_color);
    }

    rl.drawRectangleRoundedLinesEx(
        panel,
        0.18,
        8,
        layout.scaleFloat(2.0),
        .{ .r = 255, .g = 255, .b = 255, .a = outline_alpha },
    );
}

fn drawDamageGaugeWidget(state: *const AppState, layout: VirtualLayout, runner: gameplay.Runner, show_label: bool) void {
    const panel = layout.mapRect(586.0, 108.0, 28.0, 224.0);
    const fill_ratio = runner.damageGaugeDisplayFill();
    const pulse = (@sin(runner.damage_gauge_runtime.pulse_progress * std.math.tau) + 1.0) * 0.5;
    const bright_overlay_alpha = runner.damageGaugeWarningOverlayAlpha();
    const warning_actor_alpha = runner.damageWarningActorAlpha();
    const label_y: i32 = @intFromFloat(panel.y - layout.scaleFloat(20.0));
    const warning_alpha: u8 = @intFromFloat(std.math.clamp(warning_actor_alpha, 0.0, 1.0) * 255.0);
    const bright_alpha: u8 = @intFromFloat(std.math.clamp(bright_overlay_alpha, 0.0, 1.0) * 255.0);

    if (show_label) {
        drawAppText(state, "Damage", @intFromFloat(panel.x - layout.scaleFloat(2.0)), label_y, layout.fontSize(16), .light_gray);
    }
    if (state.current_gameplay_sprites.damage_gauge_full) |loaded_texture| {
        if (fill_ratio > 0.0) {
            const source_height = @as(f32, @floatFromInt(loaded_texture.texture.height));
            const source_width = @as(f32, @floatFromInt(loaded_texture.texture.width));
            const source = rl.Rectangle{
                .x = 0.0,
                .y = source_height * (1.0 - fill_ratio),
                .width = source_width,
                .height = source_height * fill_ratio,
            };
            drawTextureLocalRectSource(
                layout,
                loaded_texture,
                source,
                586.0,
                108.0 + (224.0 * (1.0 - fill_ratio)),
                28.0,
                224.0 * fill_ratio,
                .white,
            );
        }
    }
    if (bright_alpha > 0) {
        if (state.current_gameplay_sprites.damage_gauge_bright) |loaded_texture| {
            drawTextureLocalRect(
                layout,
                loaded_texture,
                586.0,
                108.0,
                28.0,
                224.0,
                .{ .r = 255, .g = 255, .b = 255, .a = bright_alpha },
            );
        }
    }
    if (warning_alpha > 0) {
        if (state.current_gameplay_sprites.warning) |loaded_texture| {
            drawTextureLocalRect(
                layout,
                loaded_texture,
                288.0,
                64.0,
                64.0,
                64.0,
                .{ .r = 255, .g = 255, .b = 255, .a = warning_alpha },
            );
        }
    }
    if (state.current_gameplay_sprites.damage_gauge) |loaded_texture| {
        drawTextureLocalRect(layout, loaded_texture, 586.0, 108.0, 28.0, 224.0, .white);
        return;
    }

    const fill_margin = layout.scaleFloat(4.0);
    const fill_height = @max(panel.height - fill_margin * 2.0, 0.0);
    const fill_width = @max(panel.width - fill_margin * 2.0, 0.0);
    const active_fill_height = fill_height * fill_ratio;
    const outline_alpha: u8 = @intFromFloat(160.0 + 64.0 * pulse);
    const fill_color = damageGaugeColor(fill_ratio, runner.damage_warning_state, pulse);
    rl.drawRectangleRounded(panel, 0.18, 8, .{ .r = 0, .g = 0, .b = 0, .a = 176 });
    const inner = rl.Rectangle{
        .x = panel.x + fill_margin,
        .y = panel.y + fill_margin,
        .width = fill_width,
        .height = fill_height,
    };
    rl.drawRectangleRounded(inner, 0.12, 6, .{ .r = 255, .g = 255, .b = 255, .a = 20 });
    if (active_fill_height > 0.0) {
        const fill_rect = rl.Rectangle{
            .x = inner.x,
            .y = inner.y + (fill_height - active_fill_height),
            .width = fill_width,
            .height = active_fill_height,
        };
        rl.drawRectangleRounded(fill_rect, 0.12, 6, fill_color);
    }
    rl.drawRectangleRoundedLinesEx(
        panel,
        0.18,
        8,
        layout.scaleFloat(2.0),
        .{ .r = 255, .g = 255, .b = 255, .a = outline_alpha },
    );
}

fn drawVisibleLifeStrip(state: *const AppState, layout: VirtualLayout, visible_life_stock: u32) void {
    const panel = layout.mapRect(448.0, 26.0, 158.0, 28.0);
    const slot_width = layout.scaleFloat(12.0);
    const slot_height = layout.scaleFloat(14.0);
    const gap = layout.scaleFloat(4.0);
    const start_x = panel.x + layout.scaleFloat(38.0);
    const slot_y = panel.y + layout.scaleFloat(7.0);

    drawAppText(state, "Lives", @intFromFloat(panel.x), @intFromFloat(panel.y + layout.scaleFloat(5.0)), layout.fontSize(16), .light_gray);

    for (0..9) |slot_index| {
        const filled = slot_index < visible_life_stock;
        const rect = rl.Rectangle{
            .x = start_x + (@as(f32, @floatFromInt(slot_index)) * (slot_width + gap)),
            .y = slot_y,
            .width = slot_width,
            .height = slot_height,
        };
        rl.drawRectangleRounded(
            rect,
            0.22,
            6,
            if (filled)
                .{ .r = 248, .g = 196, .b = 82, .a = 232 }
            else
                .{ .r = 255, .g = 255, .b = 255, .a = 24 },
        );
        rl.drawRectangleRoundedLinesEx(
            rect,
            0.22,
            6,
            layout.scaleFloat(1.0),
            if (filled)
                .{ .r = 255, .g = 234, .b = 172, .a = 255 }
            else
                .{ .r = 255, .g = 255, .b = 255, .a = 96 },
        );
    }
}

fn damageGaugeColor(fill_ratio: f32, warning_state: gameplay.DamageWarningState, pulse: f32) rl.Color {
    if (warning_state != .idle) {
        const green: u8 = @intFromFloat(160.0 + 72.0 * pulse);
        return .{ .r = 255, .g = green, .b = 88, .a = 232 };
    }
    if (fill_ratio >= 0.75) {
        return .{ .r = 232, .g = 78, .b = 72, .a = 224 };
    }
    if (fill_ratio >= 0.35) {
        return .{ .r = 244, .g = 170, .b = 64, .a = 216 };
    }
    return .{ .r = 94, .g = 204, .b = 122, .a = 208 };
}

fn jetpackGaugeColor(warning_band: gameplay.JetpackWarningBand, pulse: f32) rl.Color {
    return switch (warning_band) {
        .idle => .{ .r = 94, .g = 204, .b = 122, .a = 0 },
        .steady => .{ .r = 90, .g = 172, .b = 255, .a = 224 },
        .near_empty => .{
            .r = 255,
            .g = @intFromFloat(164.0 + 72.0 * pulse),
            .b = 84,
            .a = 232,
        },
    };
}

fn drawCompletionScreenUi(state: *const AppState, layout: VirtualLayout) !void {
    drawGameplayLevelViewport(state);
    const result = state.pending_run_result orelse return;
    if (result.outcome == .completed) {
        try drawCompletedRunScreenUi(state, layout, result);
    } else {
        try drawFailedRunScreenUi(state, layout, result);
    }
}

fn drawThanksScreenUi(state: *const AppState, layout: VirtualLayout) void {
    const text = state.thanks_screen_controller.currentText() orelse return;
    const widget_art: frontend_widget.Art = .{
        .border = state.frontend_widget_art.border.?.texture,
    };
    var idle_state = frontend_widget.TextButtonState{};
    idle_state.snapFor(.menu_button, false);
    frontend_widget.drawTextButtonWithOptions(
        layout,
        widget_art,
        &state.ui_font,
        .menu_button,
        text,
        frontend_widget.type20TextRect(&state.ui_font, text, thanks_screen_message_y, 0.0),
        idle_state,
        false,
        .{ .flags = 0x20400002 },
    );
}

fn drawCompletionParcelIcon(state: *const AppState, layout: VirtualLayout) void {
    const loaded_texture = state.frontend_widget_art.parcel_icon orelse return;
    drawTextureLocalRect(
        layout,
        loaded_texture,
        completion_parcel_icon_x,
        completion_parcel_icon_y,
        completion_parcel_icon_width,
        completion_parcel_icon_height,
        .white,
    );
}

fn drawCompletedRunScreenUi(state: *const AppState, layout: VirtualLayout, result: PendingRunResult) !void {
    const widget_art: frontend_widget.Art = .{
        .border = state.frontend_widget_art.border.?.texture,
    };
    var idle_state = frontend_widget.TextButtonState{};
    idle_state.snapFor(.menu_button, false);
    const completion_text_only: frontend_widget.DrawOptions = .{
        // PORT(verified): `initialize_completion_screen` builds the title,
        // package line, bonus line, and continue prompt with flags
        // `0x20400002`, which suppress the pill background while keeping the
        // type-20 shell-font metrics.
        .flags = 0x20400002,
    };

    const title_text = resultTitle(result);
    frontend_widget.drawTextButtonWithOptions(
        layout,
        widget_art,
        &state.ui_font,
        .menu_button,
        title_text,
        completionTitleTextRect(&state.ui_font, title_text),
        idle_state,
        false,
        completion_text_only,
    );

    var package_buffer: [64]u8 = undefined;
    const package_text = switch (result.mode orelse .tutorial) {
        .postal => try completionPackageLine(&package_buffer, result),
        .time_trial, .challenge, .tutorial => result.level_name,
    };
    frontend_widget.drawTextButtonWithOptions(
        layout,
        widget_art,
        &state.ui_font,
        .menu_button,
        package_text,
        completionPackageTextRect(&state.ui_font, package_text),
        idle_state,
        false,
        completion_text_only,
    );

    if ((result.mode orelse .tutorial) == .postal) {
        drawCompletionParcelIcon(state, layout);
    }

    if (state.completionBonusVisible(result)) {
        if (try completionBonusLine(&package_buffer, result)) |bonus_text| {
            frontend_widget.drawTextButtonWithOptions(
                layout,
                widget_art,
                &state.ui_font,
                .menu_button,
                bonus_text,
                completionBonusTextRect(&state.ui_font, bonus_text),
                idle_state,
                false,
                completion_text_only,
            );
        }
    }

    if (state.completionContinueVisible()) {
        frontend_widget.drawTextButtonWithOptions(
            layout,
            widget_art,
            &state.ui_font,
            .menu_button,
            "Click to Continue",
            completionContinueTextRect(&state.ui_font, result),
            state.completion_continue_button_state,
            false,
            completion_text_only,
        );
    }
}

fn drawFailedRunScreenUi(state: *const AppState, layout: VirtualLayout, result: PendingRunResult) !void {
    const overlay_panel = layout.mapRect(120.0, 132.0, 400.0, 204.0);
    const title_point = layout.mapPoint(144.0, 156.0);
    const body_point = layout.mapPoint(144.0, 196.0);
    const title_x: i32 = @intFromFloat(title_point.x);
    const title_y: i32 = @intFromFloat(title_point.y);
    const body_x: i32 = @intFromFloat(body_point.x);
    const body_y: i32 = @intFromFloat(body_point.y);
    const title = resultTitle(result);
    var elapsed_buffer: [32]u8 = undefined;
    const elapsed_text = try formatElapsedMillis(&elapsed_buffer, result.elapsed_millis);

    rl.drawRectangleRounded(overlay_panel, 0.08, 8, .{ .r = 0, .g = 0, .b = 0, .a = 214 });
    drawAppText(state, title, title_x, title_y, layout.fontSize(28), .gold);

    var summary_buffer: [256]u8 = undefined;
    const summary_text = try std.fmt.bufPrint(
        &summary_buffer,
        "{s}>Time {s}>Packages {d}/{d}",
        .{
            if (result.outcome == .completed) result.level_name else "Run ended before route completion",
            elapsed_text,
            result.parcel_count,
            result.parcel_target,
        },
    );
    try drawWrappedText(
        state,
        summary_text,
        body_x,
        body_y,
        layout.scaleInt(332),
        layout.fontSize(20),
        .ray_white,
    );

    const score_y = body_y + layout.scaleInt(70);
    if (result.mode == .time_trial) {
        var time_buffer: [128]u8 = undefined;
        const time_text = try std.fmt.bufPrint(&time_buffer, "Route time {s}", .{elapsed_text});
        drawAppText(state, time_text, body_x, score_y, layout.fontSize(18), .sky_blue);
    } else {
        var score_buffer: [128]u8 = undefined;
        const score_text = try std.fmt.bufPrint(&score_buffer, "Score {d}{s}", .{
            result.score,
            if (result.score_is_partial) " (partial)" else "",
        });
        drawAppText(state, score_text, body_x, score_y, layout.fontSize(18), .sky_blue);

        var breakdown_buffer: [224]u8 = undefined;
        const breakdown_text = try std.fmt.bufPrint(
            &breakdown_buffer,
            "Rings {d}  Garbage {d}  Health {d}  Pickup {d}  Register {d}  Bonus {d}  Lives {d}  Damage {d:.2}",
            .{
                result.score_totals.ring_collect,
                result.score_totals.garbage_collision,
                result.score_totals.health_collect,
                result.score_totals.parcel_pickup,
                result.score_totals.parcel_register,
                result.score_totals.completion_bonus,
                result.visible_life_stock,
                result.damage_gauge,
            },
        );
        try drawWrappedText(
            state,
            breakdown_text,
            body_x,
            score_y + layout.scaleInt(22),
            layout.scaleInt(332),
            layout.fontSize(16),
            .light_gray,
        );
    }

    if (result.unlocked_next_route) {
        drawAppText(state, "Unlocked the next delivery route.", body_x, score_y + layout.scaleInt(24), layout.fontSize(18), .gold);
    } else if (result.time_trial_record_improved) {
        drawAppText(state, "Saved a new best route time.", body_x, score_y + layout.scaleInt(24), layout.fontSize(18), .gold);
    } else if (result.high_score_rank) |rank| {
        var rank_buffer: [96]u8 = undefined;
        const rank_text = try std.fmt.bufPrint(&rank_buffer, "New high score rank: {d}", .{rank + 1});
        drawAppText(state, rank_text, body_x, score_y + layout.scaleInt(24), layout.fontSize(18), .gold);
    }

    frontend_widget.drawType20Button(
        layout,
        .{
            .border = state.frontend_widget_art.border.?.texture,
        },
        &state.ui_font,
        "Click to Continue",
        completionContinueTextRect(&state.ui_font, result),
        state.completion_continue_button_state,
        false,
    );
}

// PORT(debug): this browser is intentionally a tooling surface, not the shipping game path.
fn drawDebugUi(state: *const AppState, archive_path: []const u8) !void {
    if (state.mode == .models) {
        drawModelViewport(state);
    } else if (state.mode == .objects) {
        drawObjectViewport(state);
    } else if (state.mode == .levels) {
        debug_levels.drawLevelViewport(state);
    } else if (state.mode == .segments) {
        debug_levels.drawSegmentViewport(state);
    }

    drawAppText(state, "snail debug browser", 24, 18, 24, .ray_white);
    drawAppText(state, "1 textures  2 audio  3 x2  4 objects  5 levels  6 segments  7 streaks", 24, 48, 16, .light_gray);
    const controls_text: []const u8 = switch (state.mode) {
        .levels => "tab mode  arrows browse  levels: left/right level up/down segment  gameplay: a/d lane w/s speed space pause r reset",
        .segments => "tab mode  arrows browse  segments: v render o overlay g grid a attachments t track",
        .streaks => "streaks: space pause  n step  r reset  h fade  t texture  l lines  q/e alpha  z/x size  c/v stretch  a/d yaw  w/s pitch  f/g fov",
        else => "tab mode  arrows browse",
    };
    drawAppText(state, controls_text, 24, 70, 16, .light_gray);

    var source_buffer: [256]u8 = undefined;
    const source_text = try std.fmt.bufPrintZ(
        &source_buffer,
        "{s}  runtime {s}",
        .{ std.fs.path.basename(archive_path), std.fs.path.basename(state.runtime_root_path) },
    );
    drawAppText(state, source_text, 24, 92, 14, .dark_gray);

    drawModeBadge(state, .textures, state.mode, "Textures", 24, 114);
    drawModeBadge(state, .audio, state.mode, "Audio", 136, 114);
    drawModeBadge(state, .models, state.mode, "X2", 248, 114);
    drawModeBadge(state, .objects, state.mode, "Objects", 360, 114);
    drawModeBadge(state, .levels, state.mode, "Levels", 472, 114);
    drawModeBadge(state, .segments, state.mode, "Segments", 584, 114);
    drawModeBadge(state, .streaks, state.mode, "Streaks", 696, 114);

    switch (state.mode) {
        .textures => drawTexturePanel(state),
        .audio => try drawAudioPanel(state),
        .models => try drawModelPanel(state),
        .objects => try drawObjectPanel(state),
        .levels => try debug_levels.drawLevelPanel(state),
        .segments => try debug_levels.drawSegmentPanel(state),
        .streaks => try drawLightStreakDebugPanel(state),
    }
}

fn drawModeBadge(state: *const AppState, mode: Mode, active_mode: Mode, text: [:0]const u8, x: i32, y: i32) void {
    const color: rl.Color = if (mode == active_mode) .orange else .dark_gray;
    rl.drawRectangleRounded(.{ .x = @floatFromInt(x), .y = @floatFromInt(y), .width = 94, .height = 28 }, 0.22, 8, color);
    drawAppText(state, text, x + 16, y + 6, 16, .ray_white);
}

fn drawTexturePanel(state: *const AppState) void {
    const current = state.current_texture orelse return;
    const entry = state.catalog.texture_entries[state.texture_index];

    var summary_buffer: [256]u8 = undefined;
    const summary_text = std.fmt.bufPrintZ(
        &summary_buffer,
        "Texture {d}/{d}  {d}x{d}",
        .{
            state.texture_index + 1,
            state.catalog.texture_entries.len,
            current.texture.width,
            current.texture.height,
        },
    ) catch "Texture";
    drawAppText(state, summary_text, 32, 194, 24, .ray_white);

    var path_buffer: [512]u8 = undefined;
    const path_text = std.fmt.bufPrintZ(&path_buffer, "{s}", .{entry.path}) catch "";
    drawAppText(state, path_text, 32, 226, 18, .light_gray);

    const max_width = 860.0;
    const max_height = 430.0;
    const scale_x = max_width / @as(f32, @floatFromInt(current.texture.width));
    const scale_y = max_height / @as(f32, @floatFromInt(current.texture.height));
    const scale = @min(scale_x, scale_y);
    const draw_width = @as(f32, @floatFromInt(current.texture.width)) * scale;
    const draw_height = @as(f32, @floatFromInt(current.texture.height)) * scale;
    const draw_x = (@as(f32, @floatFromInt(screenWidth())) - draw_width) / 2.0;
    const draw_y = 280.0 + (max_height - draw_height) / 2.0;

    rl.drawRectangleLines(200, 268, 880, 454, .dark_gray);
    rl.drawTextureEx(current.texture, .{ .x = draw_x, .y = draw_y }, 0.0, scale, .white);
}

fn drawAudioPanel(state: *const AppState) !void {
    const entry = state.catalog.audio_entries[state.audio_index];

    var summary_buffer: [256]u8 = undefined;
    const summary_text = try std.fmt.bufPrintZ(
        &summary_buffer,
        "Audio {d}/{d}",
        .{ state.audio_index + 1, state.catalog.audio_entries.len },
    );
    drawAppText(state, summary_text, 32, 194, 24, .ray_white);

    var path_buffer: [512]u8 = undefined;
    const path_text = try std.fmt.bufPrintZ(&path_buffer, "{s}", .{entry.path});
    drawAppText(state, path_text, 32, 226, 18, .light_gray);

    const status_text: [:0]const u8 = blk: {
        if (!state.audio_ready) break :blk "Audio device unavailable";
        if (state.current_music != null) break :blk "Playing as music stream";
        if (state.current_sound) |sound| {
            if (rl.isSoundPlaying(sound.sound)) break :blk "Playing as one-shot sound";
        }
        break :blk "Stopped";
    };
    drawAppText(state, status_text, 32, 260, 22, .sky_blue);

    rl.drawRectangleRounded(.{ .x = 32, .y = 308, .width = 1216, .height = 380 }, 0.03, 8, .dark_blue);
    drawAppText(state, "Audio preview stays archive-backed: OGG bytes are decoded from SnailMail.dat in memory.", 56, 338, 24, .ray_white);
    drawAppText(state, "Space loads the current OGG as a sound effect and plays it once.", 56, 384, 22, .light_gray);
    drawAppText(state, "Enter loads the same OGG as a music stream and keeps updating it each frame.", 56, 420, 22, .light_gray);
    drawAppText(state, "This lets us exercise both playback paths before game logic exists.", 56, 456, 22, .light_gray);
}

fn drawLightStreakDebugPanel(state: *const AppState) !void {
    const debug = &state.debug_light_streak_view;
    const camera = debug.camera();
    const textured_bounds = rl.Rectangle{ .x = 32.0, .y = 170.0, .width = 520.0, .height = 390.0 };
    const line_bounds = rl.Rectangle{ .x = 728.0, .y = 170.0, .width = 520.0, .height = 390.0 };

    drawLightStreakDebugViewportFrame(state, textured_bounds, "STARTAIL textured", debug.show_textured);
    drawLightStreakDebugViewportFrame(state, line_bounds, "Line fallback", debug.show_lines);

    const draw_options = background.LightStreakDrawOptions{
        .alpha_multiplier = debug.alpha_multiplier,
        .size_multiplier = debug.size_multiplier,
        .stretch_multiplier = debug.stretch_multiplier,
    };

    const textured_stats = if (debug.show_textured)
        debug.controller.drawWithOptions(
            textured_bounds,
            camera,
            if (state.current_background_light_streak_texture) |loaded| loaded.texture else null,
            .{
                .mode = .textured,
                .alpha_multiplier = draw_options.alpha_multiplier,
                .size_multiplier = draw_options.size_multiplier,
                .stretch_multiplier = draw_options.stretch_multiplier,
                .draw_debug_centers = true,
                .draw_debug_quads = true,
            },
        )
    else
        background.LightStreakDrawStats{};
    const line_stats = if (debug.show_lines)
        debug.controller.drawWithOptions(
            line_bounds,
            camera,
            null,
            .{
                .mode = .lines,
                .alpha_multiplier = draw_options.alpha_multiplier,
                .size_multiplier = draw_options.size_multiplier,
                .stretch_multiplier = draw_options.stretch_multiplier,
                .draw_debug_centers = true,
            },
        )
    else
        background.LightStreakDrawStats{};

    try drawLightStreakDebugStats(state, textured_bounds, textured_stats, 574);
    try drawLightStreakDebugStats(state, line_bounds, line_stats, 574);

    const texture_preview_bounds = rl.Rectangle{ .x = 32.0, .y = 622.0, .width = 80.0, .height = 80.0 };
    rl.drawRectangleRec(texture_preview_bounds, .black);
    rl.drawRectangleLinesEx(texture_preview_bounds, 1.0, .dark_gray);
    if (state.current_background_light_streak_texture) |loaded| {
        const preview_size = 64.0;
        const preview_x = texture_preview_bounds.x + (texture_preview_bounds.width - preview_size) * 0.5;
        const preview_y = texture_preview_bounds.y + (texture_preview_bounds.height - preview_size) * 0.5;
        rl.drawTexturePro(
            loaded.texture,
            .{
                .x = 0.0,
                .y = 0.0,
                .width = @floatFromInt(loaded.texture.width),
                .height = @floatFromInt(loaded.texture.height),
            },
            .{
                .x = preview_x,
                .y = preview_y,
                .width = preview_size,
                .height = preview_size,
            },
            .{ .x = 0.0, .y = 0.0 },
            0.0,
            .white,
        );

        var sprite_buffer: [128]u8 = undefined;
        const sprite_text = try std.fmt.bufPrintZ(
            &sprite_buffer,
            "STARTAIL {d}x{d}",
            .{ loaded.texture.width, loaded.texture.height },
        );
        drawAppText(state, sprite_text, 32, 706, 16, .light_gray);
    }

    drawAppText(state, "Both panes use the same controller state and camera; only the draw path changes.", 136, 628, 18, .ray_white);

    var controller_buffer: [256]u8 = undefined;
    const controller_text = try std.fmt.bufPrintZ(
        &controller_buffer,
        "Controller {s}  fade {d:.2}  visible {s}  paused {s}",
        .{
            debug.controller.debugStateLabel(),
            debug.controller.debugFade(),
            if (debug.visible_requested) "on" else "off",
            if (debug.paused) "yes" else "no",
        },
    );
    drawAppText(state, controller_text, 136, 652, 16, .light_gray);

    var camera_buffer: [256]u8 = undefined;
    const camera_text = try std.fmt.bufPrintZ(
        &camera_buffer,
        "Camera yaw {d:.1}  pitch {d:.1}  fov {d:.1}",
        .{ debug.camera_yaw_degrees, debug.camera_pitch_degrees, debug.camera_fov_degrees },
    );
    drawAppText(state, camera_text, 136, 674, 16, .light_gray);

    var scale_buffer: [256]u8 = undefined;
    const scale_text = try std.fmt.bufPrintZ(
        &scale_buffer,
        "Multipliers alpha {d:.2}  size {d:.2}  stretch {d:.2}",
        .{ debug.alpha_multiplier, debug.size_multiplier, debug.stretch_multiplier },
    );
    drawAppText(state, scale_text, 136, 696, 16, .light_gray);

    drawAppText(state, "Use this to answer two questions: are stars being generated/projected at all, and does STARTAIL differ from the line fallback?", 136, 718, 14, .gold);
}

fn drawLightStreakDebugViewportFrame(
    state: *const AppState,
    bounds: rl.Rectangle,
    label: []const u8,
    enabled: bool,
) void {
    rl.drawRectangleRec(bounds, .black);
    rl.drawRectangleLinesEx(bounds, 2.0, if (enabled) .dark_gray else .gray);
    const center_x = bounds.x + bounds.width * 0.5;
    const center_y = bounds.y + bounds.height * 0.5;
    rl.drawLineV(.{ .x = center_x - 12.0, .y = center_y }, .{ .x = center_x + 12.0, .y = center_y }, .dark_gray);
    rl.drawLineV(.{ .x = center_x, .y = center_y - 12.0 }, .{ .x = center_x, .y = center_y + 12.0 }, .dark_gray);
    drawAppText(state, label, @intFromFloat(bounds.x + 14.0), @intFromFloat(bounds.y + 12.0), 20, if (enabled) .ray_white else .gray);
}

fn drawLightStreakDebugStats(
    state: *const AppState,
    bounds: rl.Rectangle,
    stats: background.LightStreakDrawStats,
    base_y: i32,
) !void {
    var summary_buffer: [192]u8 = undefined;
    const summary_text = try std.fmt.bufPrintZ(
        &summary_buffer,
        "entries {d}  alpha>0 {d}  projected {d}  drawn {d}",
        .{ stats.total_entries, stats.alpha_visible_entries, stats.center_projected_entries, stats.drawn_entries },
    );
    drawAppText(state, summary_text, @intFromFloat(bounds.x), base_y, 16, .light_gray);

    var detail_buffer: [192]u8 = undefined;
    const detail_text = try std.fmt.bufPrintZ(
        &detail_buffer,
        "avg alpha {d:.3}  max alpha {d:.3}  avg stretch {d:.2}",
        .{ stats.average_alpha, stats.max_alpha, stats.average_stretch },
    );
    drawAppText(state, detail_text, @intFromFloat(bounds.x), base_y + 22, 16, .light_gray);
}

fn drawModelPanel(state: *const AppState) !void {
    const entry = state.catalog.model_entries[state.model_index];
    const model = state.activeModel() orelse return;
    const parsed = &model.doc;

    var summary_buffer: [256]u8 = undefined;
    const summary_text = try std.fmt.bufPrintZ(
        &summary_buffer,
        "X2 {d}/{d}  submeshes {d}  vertices {d}  faces {d}  triangles {d}",
        .{
            state.model_index + 1,
            state.catalog.model_entries.len,
            model.submeshes.len,
            parsed.vertices.len,
            parsed.polygons.len,
            parsed.triangle_count,
        },
    );
    drawAppText(state, summary_text, 32, 194, 24, .ray_white);

    var path_buffer: [512]u8 = undefined;
    const path_text = try std.fmt.bufPrintZ(&path_buffer, "{s}", .{entry.path});
    drawAppText(state, path_text, 32, 226, 18, .light_gray);

    var detail_buffer: [256]u8 = undefined;
    const detail_text = try std.fmt.bufPrintZ(
        &detail_buffer,
        "frame {s}  mesh {s}  materials {d}  flipV {s}",
        .{
            parsed.frame_name,
            parsed.mesh_name,
            parsed.materials.len,
            if (state.model_flip_v) "on" else "off",
        },
    );
    drawAppText(state, detail_text, 32, 258, 20, .sky_blue);

    rl.drawRectangleRounded(.{ .x = 32, .y = 304, .width = 460, .height = 332 }, 0.03, 8, .dark_blue);
    drawAppText(state, "RWG loader notes", 56, 332, 26, .ray_white);

    var mesh_buffer: [384]u8 = undefined;
    const mesh_text = try std.fmt.bufPrintZ(&mesh_buffer, "Bounds center: {d:.2}, {d:.2}, {d:.2}", .{ model.bounds.center.x, model.bounds.center.y, model.bounds.center.z });
    drawAppText(state, mesh_text, 56, 378, 20, .light_gray);

    var material_buffer: [384]u8 = undefined;
    const material_text = try std.fmt.bufPrintZ(&material_buffer, "Preview radius: {d:.2}", .{model.bounds.radius});
    drawAppText(state, material_text, 56, 410, 20, .light_gray);

    var texture_buffer: [384]u8 = undefined;
    const texture_text = try std.fmt.bufPrintZ(
        &texture_buffer,
        "First texture: {s}",
        .{if (model.submeshes.len > 0)
            (if (model.submeshes[0].texture) |texture| texture.path else model.submeshes[0].texture_filename orelse "<none>")
        else
            "<none>"},
    );
    drawAppText(state, texture_text, 56, 442, 20, .light_gray);

    if (state.current_animation) |animation| {
        var anim_buffer: [384]u8 = undefined;
        const anim_text = try std.fmt.bufPrintZ(
            &anim_buffer,
            "Anim: {s}  mode {s}  sample {d:.2}  paused {s}",
            .{
                animation.clip.name,
                modeLabel(animation.clip.mode),
                animation.current_sample_number,
                if (animation.paused) "yes" else "no",
            },
        );
        drawAppText(state, anim_text, 56, 486, 20, .gold);

        var trigger_buffer: [384]u8 = undefined;
        const trigger_text = try std.fmt.bufPrintZ(
            &trigger_buffer,
            "Trigger steps {d}  first {s}  last {s}",
            .{
                animation.clip.trigger_steps.len,
                animation.clip.trigger_steps[0],
                animation.clip.trigger_steps[animation.clip.trigger_steps.len - 1],
            },
        );
        drawAppText(state, trigger_text, 56, 520, 20, .light_gray);
        drawAppText(state, "Binary Ninja + Ghidra + IDA agree the runtime interpolates numbered keyframes.", 56, 550, 20, .light_gray);
        drawAppText(state, "Duration and Mode come from X/_ANIMATION.TXT; frame numbers come from .x2 filenames.", 56, 580, 20, .light_gray);
        drawAppText(state, "Trigger lists are parsed strictly but not applied yet in this viewer.", 56, 610, 20, .light_gray);
    } else {
        drawAppText(state, "Binary Ninja + Ghidra + IDA agree on the loader shape:", 56, 486, 20, .gold);
        drawAppText(state, "TextureFilename resolves to X/<basename>.tga", 56, 520, 20, .light_gray);
        drawAppText(state, "MeshMaterialList assigns one material index per face", 56, 550, 20, .light_gray);
        drawAppText(state, "Faces with 4 indices are quads; others are triangles", 56, 580, 20, .light_gray);
        drawAppText(state, "This viewer triangulates quads and draws archive-backed textures directly.", 56, 610, 20, .light_gray);
    }
}

fn drawModelViewport(state: *const AppState) void {
    const model = state.activeModel() orelse return;
    const camera = model.previewCamera(@floatCast(state.render_time_seconds));
    camera.begin();
    defer rl.endMode3D();

    const grid_slices: i32 = @intFromFloat(@min(@max(model.bounds.radius * 6.0, 10.0), 80.0));
    const grid_spacing = @max(model.bounds.radius / 2.0, 0.5);
    rl.drawGrid(grid_slices, grid_spacing);
    model.draw();
}

fn drawObjectPanel(state: *const AppState) !void {
    const entry = state.catalog.object_entries[state.object_index];
    const loaded_object = state.current_object orelse return;

    var summary_buffer: [256]u8 = undefined;
    const summary_text = try std.fmt.bufPrintZ(
        &summary_buffer,
        "Object {d}/{d}  vertices {d}  faces {d}  textures {d}",
        .{
            state.object_index + 1,
            state.catalog.object_entries.len,
            loaded_object.parsed.vertices.len,
            loaded_object.parsed.faces.len,
            loaded_object.parsed.texture_names.len,
        },
    );
    drawAppText(state, summary_text, 32, 194, 24, .ray_white);

    var path_buffer: [512]u8 = undefined;
    const path_text = try std.fmt.bufPrintZ(&path_buffer, "{s}", .{entry.path});
    drawAppText(state, path_text, 32, 226, 18, .light_gray);

    var detail_buffer: [256]u8 = undefined;
    const detail_text = try std.fmt.bufPrintZ(
        &detail_buffer,
        "submeshes {d}  triangles {d}  flipV {s}",
        .{
            loaded_object.submeshes.len,
            triangleCountForObject(loaded_object),
            if (state.object_flip_v) "on" else "off",
        },
    );
    drawAppText(state, detail_text, 32, 258, 20, .sky_blue);

    rl.drawRectangleRounded(.{ .x = 32, .y = 304, .width = 460, .height = 332 }, 0.03, 8, .dark_blue);
    drawAppText(state, "Object notes", 56, 332, 26, .ray_white);

    var bounds_buffer: [384]u8 = undefined;
    const bounds_text = try std.fmt.bufPrintZ(
        &bounds_buffer,
        "Bounds center: {d:.2}, {d:.2}, {d:.2}",
        .{ loaded_object.center.x, loaded_object.center.y, loaded_object.center.z },
    );
    drawAppText(state, bounds_text, 56, 378, 20, .light_gray);

    var radius_buffer: [256]u8 = undefined;
    const radius_text = try std.fmt.bufPrintZ(&radius_buffer, "Preview radius: {d:.2}", .{loaded_object.radius});
    drawAppText(state, radius_text, 56, 410, 20, .light_gray);

    var texture_buffer: [384]u8 = undefined;
    const texture_text = try std.fmt.bufPrintZ(
        &texture_buffer,
        "First texture: {s}",
        .{if (loaded_object.submeshes.len > 0 and loaded_object.submeshes[0].archive_texture_path != null) loaded_object.submeshes[0].archive_texture_path.? else "<none>"},
    );
    drawAppText(state, texture_text, 56, 442, 20, .light_gray);

    drawAppText(state, "Simple text object format:", 56, 486, 20, .gold);
    drawAppText(state, "[VERTEX START] defines indexed positions", 56, 520, 20, .light_gray);
    drawAppText(state, "[FACEQUAD START] defines quads with four UV pairs", 56, 550, 20, .light_gray);
    drawAppText(state, "Texture tokens resolve to sibling TGA files in the same OBJECTS folder.", 56, 580, 20, .light_gray);
    drawAppText(state, "This viewer triangulates those quads into a textured mesh directly.", 56, 610, 20, .light_gray);
}

fn drawObjectViewport(state: *const AppState) void {
    const loaded_object = state.current_object orelse return;
    const camera = loaded_object.previewCamera(@floatCast(state.render_time_seconds));
    camera.begin();
    defer rl.endMode3D();

    const grid_slices: i32 = @intFromFloat(@min(@max(loaded_object.radius * 6.0, 10.0), 80.0));
    const grid_spacing = @max(loaded_object.radius / 2.0, 0.5);
    rl.drawGrid(grid_slices, grid_spacing);
    loaded_object.draw();
}

fn drawGameplayLevelViewport(state: *const AppState) void {
    const loaded_track_preview = state.current_track_preview orelse return;
    const runner = state.level_runner orelse {
        debug_levels.drawLevelViewport(state);
        return;
    };
    const camera = gameplayLevelCamera(&state.subgame_camera, &loaded_track_preview, state.subgame_camera.fov_degrees);
    camera.begin();
    defer rl.endMode3D();

    const selected_segment_index = if (loaded_track_preview.locateRow(runner.current_global_row)) |row_location|
        row_location.segment_index
    else
        0;
    if (state.current_game_track_scene) |*scene| {
        scene.drawGameplay(&loaded_track_preview, selected_segment_index);
    } else {
        loaded_track_preview.draw(selected_segment_index);
    }
    if (state.gameplay_click_start_active) {
        drawGameplayTurbo(state, &loaded_track_preview, runner);
        return;
    }
    drawGameplayRuntimeActors(state, &loaded_track_preview, runner, camera);
    drawGameplayBarrier(state, &loaded_track_preview, runner);
    drawGameplayTurbo(state, &loaded_track_preview, runner);
}
const BillboardUv = struct {
    left: f32,
    top: f32,
    right: f32,
    bottom: f32,
};

fn drawGameplayRuntimeActors(
    state: *const AppState,
    loaded_track_preview: *const track.LoadedLevelPreview,
    runner: gameplay.Runner,
    camera: rl.Camera3D,
) void {
    if (loaded_track_preview.max_width == 0 or loaded_track_preview.total_rows == 0) return;

    const current_row = loaded_track_preview.rowIndexAtWorldZ(runner.row_position);
    const start_row = current_row -| 1;
    const end_row = @min(loaded_track_preview.total_rows, current_row + 72);

    for (start_row..end_row) |global_row| {
        if (!shouldRenderGameplayActorRow(runner, global_row)) continue;
        const row_location = loaded_track_preview.locateRow(global_row) orelse continue;
        for (0..row_location.row.cells.len) |lane_index| {
            const sample = loaded_track_preview.gameplayCellSampleAt(global_row, lane_index) orelse continue;
            switch (sample.kind) {
                .slug => drawGameplaySlugActor(state, loaded_track_preview, camera, global_row, lane_index),
                .ring => {
                    if (shouldRenderStaticGameplayRing(loaded_track_preview, row_location, loaded_track_preview.runtimeTileAt(global_row, lane_index))) {
                        drawGameplayStaticRingActor(state, loaded_track_preview, camera, row_location, lane_index);
                    }
                },
                .health, .jetpack, .attachment_probe, .attachment_entry, .trampoline, .garbage, .salt => {},
            }
            if (row_location.row.cells[lane_index] == '=') {
                drawGameplayTurretActor(state, loaded_track_preview, runner, global_row, lane_index);
            }
        }
    }

    for (runner.activeTrackParcels()) |parcel| {
        if (!parcel.active()) continue;
        if (!shouldRenderGameplayActorRow(runner, parcel.row)) continue;
        drawGameplayTrackParcelActor(state, camera, parcel);
    }

    for (runner.activeRuntimeHazards()) |hazard| {
        if (!shouldRenderGameplayHazard(runner, hazard)) continue;
        switch (hazard.kind) {
            .garbage => {
                drawGameplayGarbageActor(state, loaded_track_preview, camera, hazard);
            },
            .salt => {
                drawGameplaySaltActor(state, camera, hazard);
            },
        }
    }

    for (runner.activeRuntimePickups()) |pickup| {
        if (!shouldRenderGameplayPickup(runner, pickup)) continue;
        switch (pickup.kind) {
            .health => drawGameplayHealthPickupActor(state, camera, pickup),
            .jetpack => drawGameplayJetpackPickupActor(state, camera, pickup),
        }
    }

    for (runner.activeRuntimeRingEffects()) |effect| {
        if (!shouldRenderGameplayRingEffect(runner, effect)) continue;
        drawGameplayRuntimeRingEffectActor(state, camera, effect);
    }

    for (runner.activeProjectiles()) |projectile| {
        drawGameplayProjectileActor(state, projectile);
    }

    drawGameplayEffects(state, camera);
}

fn shouldRenderGameplayActorRow(runner: gameplay.Runner, global_row: usize) bool {
    return @as(f32, @floatFromInt(global_row)) + 0.25 >= runner.row_position;
}

fn shouldRenderGameplayHazard(runner: gameplay.Runner, hazard: gameplay.RuntimeHazard) bool {
    const trailing_rows: f32 = switch (hazard.kind) {
        .garbage => switch (hazard.state) {
            .active => @as(f32, 0.25),
            else => @as(f32, 8.0),
        },
        .salt => @as(f32, 48.0),
    };
    return hazard.world_position.z + trailing_rows >= runner.row_position and
        hazard.world_position.z <= runner.row_position + 72.0;
}

fn shouldRenderGameplayPickup(runner: gameplay.Runner, pickup: gameplay.RuntimePickup) bool {
    return pickup.world_position.z + 0.25 >= runner.row_position and
        pickup.world_position.z <= runner.row_position + 72.0;
}

fn shouldRenderGameplayRingEffect(runner: gameplay.Runner, effect: gameplay.RuntimeRingEffect) bool {
    return effect.world_position.z + 0.25 >= runner.row_position and
        effect.world_position.z <= runner.row_position + 72.0;
}

fn shouldRenderStaticGameplayRing(
    preview: *const track.LoadedLevelPreview,
    row_location: track.RowLocation,
    runtime_tile_hint: ?u8,
) bool {
    return !gameplay.runtimeHandledRingAnnotation(runtime_tile_hint, preview.runtimeRowFlagsAt(row_location.global_row));
}

fn deterministicGameplayActorYaw(global_row: usize, lane_index: usize) f32 {
    var seed: u64 = 0x9e3779b97f4a7c15;
    seed ^= @as(u64, @intCast(global_row)) *% 0xbf58476d1ce4e5b9;
    seed ^= @as(u64, @intCast(lane_index + 1)) *% 0x94d049bb133111eb;
    const angle_fraction = @as(f32, @floatFromInt(@as(u16, @truncate(seed >> 16)))) / 65535.0;
    return (angle_fraction * std.math.tau) - std.math.pi;
}

fn drawGameplaySlugActor(state: *const AppState, preview: *const track.LoadedLevelPreview, camera: rl.Camera3D, global_row: usize, lane_index: usize) void {
    const base_phase = deterministicGameplayActorYaw(global_row, lane_index);
    const frame_index: usize = @intFromFloat(@mod(
        @floor((state.render_time_seconds * 8.0) + @as(f64, base_phase * 2.0)),
        @as(f64, @floatFromInt(gameplay_slug_sprite_paths.len)),
    ));
    const loaded_texture = state.current_gameplay_sprites.slug_frames[frame_index] orelse return;
    const bob_phase = base_phase + @as(f32, @floatCast(state.render_time_seconds * 3.0));
    const position = gameplayLaneWorldPosition(
        preview,
        global_row,
        lane_index,
        0.34 + (std.math.sin(bob_phase) * 0.04),
    );
    drawGameplayBillboardTextureRectRolled(
        loaded_texture.texture,
        .{ .x = 0.0, .y = 0.0, .width = @floatFromInt(loaded_texture.texture.width), .height = @floatFromInt(loaded_texture.texture.height) },
        position,
        0.7,
        0.7,
        camera,
        std.math.sin(bob_phase * 0.5) * 0.08,
        .white,
    );
}

fn drawGameplayGarbageActor(
    state: *const AppState,
    preview: *const track.LoadedLevelPreview,
    camera: rl.Camera3D,
    hazard: gameplay.RuntimeHazard,
) void {
    _ = preview;
    if (hazard.state == .inactive) return;
    const variant_index = @as(usize, @intCast((hazard.row + hazard.lane * 3) % gameplay_garbage_sprite_paths.len));
    const loaded_texture = state.current_gameplay_sprites.garbage_variants[variant_index] orelse return;
    drawGameplayBillboardTextureRectRolled(
        loaded_texture.texture,
        .{ .x = 0.0, .y = 0.0, .width = @floatFromInt(loaded_texture.texture.width), .height = @floatFromInt(loaded_texture.texture.height) },
        hazard.world_position,
        hazard.presentation_scale,
        hazard.presentation_scale,
        camera,
        hazard.presentation_phase + (@as(f32, @floatCast(state.render_time_seconds)) * 1.75),
        .{ .r = 255, .g = 255, .b = 255, .a = if (hazard.state == .active) 232 else 255 },
    );
}

fn drawGameplaySaltActor(
    state: *const AppState,
    camera: rl.Camera3D,
    hazard: gameplay.RuntimeHazard,
) void {
    if (hazard.state != .active) return;
    const presentation_alpha: u8 = 232;
    if (state.current_gameplay_salt_model) |*model| {
        const yaw = hazard.yaw_radians;
        const yaw_sin = std.math.sin(yaw);
        const yaw_cos = std.math.cos(yaw);
        const right: rl.Vector3 = .{ .x = yaw_cos, .y = 0.0, .z = -yaw_sin };
        const up: rl.Vector3 = .{ .x = 0.0, .y = 1.0, .z = 0.0 };
        const forward: rl.Vector3 = .{ .x = yaw_sin, .y = 0.0, .z = yaw_cos };
        const world_transform = modelTransformFromBasis(hazard.world_position, right, up, forward);
        const local_offset = rl.Matrix.translate(
            -model.bounds.center.x,
            -model.bounds.center.y,
            -model.bounds.center.z,
        );
        const scale_value = 0.46;
        const scale = rl.Matrix.scale(scale_value, scale_value, scale_value);
        model.drawTintedEx(
            world_transform.multiply(local_offset).multiply(scale),
            .{ .r = 255, .g = 255, .b = 255, .a = presentation_alpha },
        );
        return;
    }

    const slot = state.ui_font.slots[game_font.IconGlyph.salt.slotIndex()];
    drawGameplayBillboardTextureRect(
        state.ui_font.texture,
        .{
            .x = slot.source_x,
            .y = slot.source_y,
            .width = slot.source_width,
            .height = slot.source_height,
        },
        hazard.world_position,
        0.58,
        0.72,
        camera,
        .{ .r = 144, .g = 198, .b = 255, .a = presentation_alpha },
    );
}

fn drawGameplayTurretActor(
    state: *const AppState,
    preview: *const track.LoadedLevelPreview,
    runner: gameplay.Runner,
    global_row: usize,
    lane_index: usize,
) void {
    const flash_ticks = runner.turretFlashTicksAt(global_row, lane_index);
    const model = blk: {
        if (flash_ticks > 0) {
            if (state.current_gameplay_blaster_top_models.fire) |*fire_model| break :blk fire_model.*;
        }
        break :blk state.current_gameplay_turret_model orelse return;
    };
    const floor_height = preview.floorHeightAtCellCenter(global_row, lane_index) orelse 0.0;
    const position = preview.worldPositionForLane(
        @as(f32, @floatFromInt(lane_index)) + 0.5,
        @as(f32, @floatFromInt(global_row)),
        floor_height + 0.18,
    );
    drawGameplayUploadedModel(
        model,
        position,
        .{ .x = 1.0, .y = 0.0, .z = 0.0 },
        .{ .x = 0.0, .y = 1.0, .z = 0.0 },
        .{ .x = 0.0, .y = 0.0, .z = 1.0 },
        .{ .x = 0.34, .y = 0.34, .z = 0.34 },
        null,
    );
}

fn drawGameplayHealthPickupActor(
    state: *const AppState,
    camera: rl.Camera3D,
    pickup: gameplay.RuntimePickup,
) void {
    const loaded_texture = state.current_gameplay_sprites.health orelse return;
    drawGameplayBillboardTexture(loaded_texture.texture, pickup.presentation_position, 0.52, 0.52, camera, .white);
}

fn drawGameplayJetpackPickupActor(
    state: *const AppState,
    camera: rl.Camera3D,
    pickup: gameplay.RuntimePickup,
) void {
    const frame_index: usize = @intFromFloat(@mod(@floor(state.render_time_seconds * 8.0), @as(f64, @floatFromInt(gameplay_jetpack_sprite_paths.len))));
    const loaded_texture = state.current_gameplay_sprites.jetpack_frames[frame_index] orelse return;
    drawGameplayBillboardTexture(loaded_texture.texture, pickup.presentation_position, 0.64, 0.88, camera, .white);
}

fn drawGameplayStaticRingActor(
    state: *const AppState,
    preview: *const track.LoadedLevelPreview,
    camera: rl.Camera3D,
    row_location: track.RowLocation,
    lane_index: usize,
) void {
    const ring_kind = if (row_location.row.annotation) |annotation|
        switch (annotation) {
            .ring => |kind| kind,
            else => segment.RingKind.normal,
        }
    else
        segment.RingKind.normal;
    const position = gameplayLaneWorldPosition(preview, row_location.global_row, lane_index, 0.72);
    switch (ring_kind) {
        .none => {},
        .normal => if (state.current_gameplay_sprites.ring) |loaded_texture| {
            drawGameplayBillboardTexture(loaded_texture.texture, position, 0.46, 0.46, camera, .{ .r = 255, .g = 246, .b = 180, .a = 232 });
        },
        .powerup => if (state.current_gameplay_sprites.powerup) |loaded_texture| {
            drawGameplayBillboardTexture(loaded_texture.texture, position, 0.64, 0.64, camera, .white);
        },
        .explode => if (state.current_gameplay_sprites.ring_big) |loaded_texture| {
            drawGameplayBillboardTexture(loaded_texture.texture, position, 0.72, 0.72, camera, .{ .r = 255, .g = 220, .b = 120, .a = 232 });
        },
        .slow => if (state.current_gameplay_sprites.slow_ring) |loaded_texture| {
            drawGameplayBillboardTexture(loaded_texture.texture, position, 0.5, 0.5, camera, .white);
        },
    }
}

fn drawGameplayRuntimeRingEffectActor(
    state: *const AppState,
    camera: rl.Camera3D,
    effect: gameplay.RuntimeRingEffect,
) void {
    const ring_kind = gameplay.nativeRuntimeRingKindLabel(effect.kind) orelse return;
    const position = effect.world_position;
    switch (ring_kind) {
        .none => {},
        .normal => if (state.current_gameplay_sprites.ring) |loaded_texture| {
            drawGameplayBillboardTexture(loaded_texture.texture, position, 0.46, 0.46, camera, .{ .r = 255, .g = 246, .b = 180, .a = 232 });
        },
        .powerup => if (state.current_gameplay_sprites.powerup) |loaded_texture| {
            drawGameplayBillboardTexture(loaded_texture.texture, position, 0.64, 0.64, camera, .white);
        },
        .explode => if (state.current_gameplay_sprites.ring_big) |loaded_texture| {
            drawGameplayBillboardTexture(loaded_texture.texture, position, 0.72, 0.72, camera, .{ .r = 255, .g = 220, .b = 120, .a = 232 });
        },
        .slow => if (state.current_gameplay_sprites.slow_ring) |loaded_texture| {
            drawGameplayBillboardTexture(loaded_texture.texture, position, 0.5, 0.5, camera, .white);
        },
    }
}

fn drawGameplayTrackParcelActor(
    state: *const AppState,
    camera: rl.Camera3D,
    parcel: gameplay.TrackParcelRuntime,
) void {
    const loaded_texture = state.current_gameplay_sprites.parcel orelse return;
    const position = parcel.presentationPosition();
    const scale = parcel.presentationScale();
    drawGameplayBillboardTexture(
        loaded_texture.texture,
        position,
        0.56 * scale,
        0.56 * scale,
        camera,
        if (parcel.parcel_id == 0)
            .white
        else
            .{ .r = 196, .g = 255, .b = 196, .a = 232 },
    );
}

fn gameplayLaneWorldPosition(preview: *const track.LoadedLevelPreview, global_row: usize, lane_index: usize, y_offset: f32) rl.Vector3 {
    const floor_height = preview.floorHeightAtCellCenter(global_row, lane_index) orelse 0.0;
    return preview.worldPositionForLane(@as(f32, @floatFromInt(lane_index)) + 0.5, @as(f32, @floatFromInt(global_row)), floor_height + y_offset);
}

fn drawGameplayBillboardTexture(
    texture: rl.Texture2D,
    position: rl.Vector3,
    width: f32,
    height: f32,
    camera: rl.Camera3D,
    tint: rl.Color,
) void {
    drawGameplayBillboardTextureRect(
        texture,
        .{ .x = 0.0, .y = 0.0, .width = @floatFromInt(texture.width), .height = @floatFromInt(texture.height) },
        position,
        width,
        height,
        camera,
        tint,
    );
}

fn drawGameplayBillboardTextureRectRolled(
    texture: rl.Texture2D,
    source: rl.Rectangle,
    position: rl.Vector3,
    width: f32,
    height: f32,
    camera: rl.Camera3D,
    roll_radians: f32,
    tint: rl.Color,
) void {
    const forward = normalizeVector3(.{
        .x = camera.target.x - camera.position.x,
        .y = camera.target.y - camera.position.y,
        .z = camera.target.z - camera.position.z,
    });
    var right = crossVector3(forward, camera.up);
    if (vectorLength(right) <= 0.0001) {
        right = .{ .x = 1.0, .y = 0.0, .z = 0.0 };
    } else {
        right = normalizeVector3(right);
    }
    var up = crossVector3(right, forward);
    if (vectorLength(up) <= 0.0001) {
        up = .{ .x = 0.0, .y = 1.0, .z = 0.0 };
    } else {
        up = normalizeVector3(up);
    }

    if (@abs(roll_radians) > 0.0001) {
        const roll_cos = std.math.cos(roll_radians);
        const roll_sin = std.math.sin(roll_radians);
        const rotated_right: rl.Vector3 = .{
            .x = (right.x * roll_cos) - (up.x * roll_sin),
            .y = (right.y * roll_cos) - (up.y * roll_sin),
            .z = (right.z * roll_cos) - (up.z * roll_sin),
        };
        const rotated_up: rl.Vector3 = .{
            .x = (right.x * roll_sin) + (up.x * roll_cos),
            .y = (right.y * roll_sin) + (up.y * roll_cos),
            .z = (right.z * roll_sin) + (up.z * roll_cos),
        };
        right = rotated_right;
        up = rotated_up;
    }

    const half_width = width * 0.5;
    const half_height = height * 0.5;
    const top_left: rl.Vector3 = .{
        .x = position.x - (right.x * half_width) + (up.x * half_height),
        .y = position.y - (right.y * half_width) + (up.y * half_height),
        .z = position.z - (right.z * half_width) + (up.z * half_height),
    };
    const bottom_left: rl.Vector3 = .{
        .x = position.x - (right.x * half_width) - (up.x * half_height),
        .y = position.y - (right.y * half_width) - (up.y * half_height),
        .z = position.z - (right.z * half_width) - (up.z * half_height),
    };
    const bottom_right: rl.Vector3 = .{
        .x = position.x + (right.x * half_width) - (up.x * half_height),
        .y = position.y + (right.y * half_width) - (up.y * half_height),
        .z = position.z + (right.z * half_width) - (up.z * half_height),
    };
    const top_right: rl.Vector3 = .{
        .x = position.x + (right.x * half_width) + (up.x * half_height),
        .y = position.y + (right.y * half_width) + (up.y * half_height),
        .z = position.z + (right.z * half_width) + (up.z * half_height),
    };
    const uv = BillboardUv{
        .left = source.x / @as(f32, @floatFromInt(texture.width)),
        .top = source.y / @as(f32, @floatFromInt(texture.height)),
        .right = (source.x + source.width) / @as(f32, @floatFromInt(texture.width)),
        .bottom = (source.y + source.height) / @as(f32, @floatFromInt(texture.height)),
    };
    drawGameplayBillboardQuad(texture, top_left, bottom_left, bottom_right, top_right, uv, tint);
    drawGameplayBillboardQuad(texture, top_right, bottom_right, bottom_left, top_left, uv, tint);
}

fn drawGameplayBillboardTextureRect(
    texture: rl.Texture2D,
    source: rl.Rectangle,
    position: rl.Vector3,
    width: f32,
    height: f32,
    camera: rl.Camera3D,
    tint: rl.Color,
) void {
    drawGameplayBillboardTextureRectRolled(texture, source, position, width, height, camera, 0.0, tint);
}

fn drawGameplayBillboardQuad(
    texture: rl.Texture2D,
    top_left: rl.Vector3,
    bottom_left: rl.Vector3,
    bottom_right: rl.Vector3,
    top_right: rl.Vector3,
    uv: BillboardUv,
    tint: rl.Color,
) void {
    rl.gl.rlSetTexture(texture.id);
    defer rl.gl.rlSetTexture(0);

    rl.gl.rlBegin(rl.gl.rl_quads);
    defer rl.gl.rlEnd();
    rl.gl.rlColor4ub(tint.r, tint.g, tint.b, tint.a);

    rl.gl.rlTexCoord2f(uv.left, uv.top);
    rl.gl.rlVertex3f(top_left.x, top_left.y, top_left.z);
    rl.gl.rlTexCoord2f(uv.left, uv.bottom);
    rl.gl.rlVertex3f(bottom_left.x, bottom_left.y, bottom_left.z);
    rl.gl.rlTexCoord2f(uv.right, uv.bottom);
    rl.gl.rlVertex3f(bottom_right.x, bottom_right.y, bottom_right.z);
    rl.gl.rlTexCoord2f(uv.right, uv.top);
    rl.gl.rlVertex3f(top_right.x, top_right.y, top_right.z);
}

fn drawGameplayBarrier(state: *const AppState, loaded_track_preview: *const track.LoadedLevelPreview, runner: gameplay.Runner) void {
    const loaded_object = state.current_gameplay_barrier_object orelse return;
    const tutorial_level_active = state.isTutorialLevel();
    const barrier_active = tutorial_level_active or runner.current_annotation == .no_fall;
    if (!barrier_active) return;

    const runner_position = runner.worldPosition(loaded_track_preview, 0.4);
    // Android `cRBarrier::AI()` only updates the object-space Y/Z slots:
    // `y = 0.4`, `z = owner->+100`. The barrier mesh itself is already authored
    // in the correct orientation, so gameplay should follow the owner without
    // inventing an extra upright rotation.
    const world_transform = rl.Matrix.translate(0.0, 0.4, runner_position.z);
    rl.gl.rlDisableBackfaceCulling();
    defer rl.gl.rlEnableBackfaceCulling();
    // Android `ObjectProcBarrier` only modulates alpha on the authored object.
    // Preserve the original material colours and just apply translucency here.
    const barrier_tint = rl.Color{ .r = 255, .g = 255, .b = 255, .a = 204 };
    loaded_object.drawTintedEx(world_transform, barrier_tint);
}

fn drawGameplayProjectileActor(state: *const AppState, projectile: gameplay.Projectile) void {
    const forward = normalizeVector3(.{
        .x = projectile.dir_x,
        .y = projectile.dir_y,
        .z = projectile.dir_z,
    });
    var up: rl.Vector3 = .{ .x = 0.0, .y = 1.0, .z = 0.0 };
    if (@abs(dotVector3(forward, up)) > 0.95) {
        up = .{ .x = 1.0, .y = 0.0, .z = 0.0 };
    }

    var right = crossVector3(up, forward);
    if (vectorLength(right) <= 0.0001) {
        right = .{ .x = 1.0, .y = 0.0, .z = 0.0 };
    } else {
        right = normalizeVector3(right);
    }
    const corrected_up = normalizeVector3(crossVector3(forward, right));
    const position: rl.Vector3 = .{
        .x = projectile.world_x,
        .y = projectile.world_y,
        .z = projectile.world_z,
    };
    const world_transform = modelTransformFromBasis(position, right, corrected_up, forward);
    const local_offset = rl.Matrix.translate(
        0.0,
        0.0,
        0.0,
    );
    _ = local_offset;

    switch (projectile.kind) {
        .turbo => {
            const loaded_object = state.current_gameplay_lazer_object orelse return;
            const offset = rl.Matrix.translate(
                -loaded_object.center.x,
                -loaded_object.center.y,
                -loaded_object.center.z,
            );
            const scale = rl.Matrix.scale(0.18, 0.18, 0.18);
            loaded_object.drawTintedEx(
                world_transform.multiply(offset).multiply(scale),
                .{ .r = 170, .g = 220, .b = 255, .a = 232 },
            );
        },
        .laser => {
            const loaded_object = state.current_gameplay_vapour_lazer_object orelse state.current_gameplay_lazer_object orelse return;
            const offset = rl.Matrix.translate(
                -loaded_object.center.x,
                -loaded_object.center.y,
                -loaded_object.center.z,
            );
            const scale = rl.Matrix.scale(0.22, 0.22, 0.22);
            loaded_object.drawTintedEx(
                world_transform.multiply(offset).multiply(scale),
                .{ .r = 180, .g = 255, .b = 255, .a = 236 },
            );
        },
        .enemy_laser => {
            const loaded_object = state.current_gameplay_vapour_lazer_object orelse state.current_gameplay_lazer_object orelse return;
            const offset = rl.Matrix.translate(
                -loaded_object.center.x,
                -loaded_object.center.y,
                -loaded_object.center.z,
            );
            const scale = rl.Matrix.scale(0.18, 0.18, 0.18);
            loaded_object.drawTintedEx(
                world_transform.multiply(offset).multiply(scale),
                .{ .r = 255, .g = 136, .b = 96, .a = 236 },
            );
        },
        .rocket => {
            const model = state.current_gameplay_rocket_model orelse {
                const loaded_object = state.current_gameplay_lazer_object orelse return;
                const offset = rl.Matrix.translate(
                    -loaded_object.center.x,
                    -loaded_object.center.y,
                    -loaded_object.center.z,
                );
                const scale = rl.Matrix.scale(0.22, 0.22, 0.22);
                loaded_object.drawTintedEx(
                    world_transform.multiply(offset).multiply(scale),
                    .{ .r = 255, .g = 224, .b = 164, .a = 236 },
                );
                return;
            };
            drawGameplayUploadedModel(
                model,
                position,
                right,
                corrected_up,
                forward,
                .{ .x = 0.16, .y = 0.16, .z = 0.16 },
                null,
            );
        },
    }
}

fn drawGameplayEffects(state: *const AppState, camera: rl.Camera3D) void {
    for (0..state.active_gameplay_effect_count) |index| {
        const effect = state.active_gameplay_effects[index];
        if (!effect.active or effect.ticks_remaining == 0) continue;
        const loaded_texture = switch (effect.kind) {
            .explode_big => state.current_gameplay_sprites.explode_big,
            .explode_small => state.current_gameplay_sprites.explode_small,
            .slug_goo => state.current_gameplay_sprites.slug_goo,
            .smoke => state.current_gameplay_sprites.smoke,
        } orelse continue;
        drawGameplayBillboardTexture(
            loaded_texture.texture,
            effect.position,
            effect.width,
            effect.height,
            camera,
            effect.tint,
        );
    }
}

fn drawGameplayTurbo(state: *const AppState, loaded_track_preview: *const track.LoadedLevelPreview, runner: gameplay.Runner) void {
    const model = state.activeGameplayTurbo() orelse return;
    const click_start_active = state.gameplay_click_start_active;
    const pose = if (click_start_active and state.tutorialClickStartCutsceneActive())
        tutorialClickStartTurboPose(model, loaded_track_preview, runner)
    else
        gameplayTurboPose(model, loaded_track_preview, runner);
    model.drawEx(pose.transform);

    if (click_start_active) return;
    drawGameplayTurboAttachments(state, pose.position, pose.right, pose.up, pose.forward, runner);
}

fn drawGameplayTurboAttachments(
    state: *const AppState,
    position: rl.Vector3,
    right: rl.Vector3,
    up: rl.Vector3,
    forward: rl.Vector3,
    runner: gameplay.Runner,
) void {
    const channel_states = gameplay.nativeWeaponChannelStates(runner.movement_flags);

    const top_active = channel_states.center == 1 or
        state.gameplay_weapon_visual_state.top_draw_ticks > 0 or
        state.gameplay_weapon_visual_state.top_hide_ticks > 0;
    if (top_active) {
        if (state.current_gameplay_blaster_top_models.currentModel(
            state.gameplay_weapon_visual_state.top_draw_ticks,
            state.gameplay_weapon_visual_state.top_fire_ticks,
            state.gameplay_weapon_visual_state.top_hide_ticks,
        )) |model| {
            drawGameplayUploadedModel(
                model.*,
                offsetPosition(position, right, up, forward, 0.0, 0.22, 0.10),
                right,
                up,
                forward,
                .{ .x = 0.22, .y = 0.22, .z = 0.22 },
                null,
            );
        }
    }

    const left_active = channel_states.left != 0 or
        state.gameplay_weapon_visual_state.left_draw_ticks > 0 or
        state.gameplay_weapon_visual_state.left_hide_ticks > 0;
    if (left_active) {
        if (state.current_gameplay_laser_left_models.currentModel(
            state.gameplay_weapon_visual_state.left_draw_ticks,
            0,
            state.gameplay_weapon_visual_state.left_hide_ticks,
        )) |model| {
            drawGameplayUploadedModel(
                model.*,
                offsetPosition(position, right, up, forward, -0.24, 0.11, 0.08),
                right,
                up,
                forward,
                .{ .x = 0.22, .y = 0.22, .z = 0.22 },
                null,
            );
        }
    }

    const right_active = channel_states.right != 0 or
        state.gameplay_weapon_visual_state.right_draw_ticks > 0 or
        state.gameplay_weapon_visual_state.right_hide_ticks > 0;
    if (right_active) {
        if (state.current_gameplay_laser_right_models.currentModel(
            state.gameplay_weapon_visual_state.right_draw_ticks,
            0,
            state.gameplay_weapon_visual_state.right_hide_ticks,
        )) |model| {
            drawGameplayUploadedModel(
                model.*,
                offsetPosition(position, right, up, forward, 0.24, 0.11, 0.08),
                right,
                up,
                forward,
                .{ .x = 0.22, .y = 0.22, .z = 0.22 },
                null,
            );
        }
    }

    const rocket_active = channel_states.center == 3 or
        state.gameplay_weapon_visual_state.rocket_draw_ticks > 0 or
        state.gameplay_weapon_visual_state.rocket_hide_ticks > 0;
    if (rocket_active) {
        if (state.current_gameplay_rocket_launcher_models.currentModel(
            state.gameplay_weapon_visual_state.rocket_draw_ticks,
            0,
            state.gameplay_weapon_visual_state.rocket_hide_ticks,
        )) |model| {
            drawGameplayUploadedModel(
                model.*,
                offsetPosition(position, right, up, forward, 0.0, 0.23, 0.12),
                right,
                up,
                forward,
                .{ .x = 0.24, .y = 0.24, .z = 0.24 },
                null,
            );
        }
    }

    if (runner.invincible_ticks > 0) {
        if (state.current_gameplay_invincible_models.currentModel(state.render_time_seconds)) |model| {
            drawGameplayUploadedModel(
                model.*,
                offsetPosition(position, right, up, forward, 0.0, 0.02, 0.0),
                right,
                up,
                forward,
                .{ .x = 1.05, .y = 1.05, .z = 1.05 },
                .{ .r = 220, .g = 240, .b = 255, .a = 180 },
            );
        }
    }
}

fn drawGameplayUploadedModel(
    model: x2.Uploaded,
    position: rl.Vector3,
    right: rl.Vector3,
    up: rl.Vector3,
    forward: rl.Vector3,
    scale: rl.Vector3,
    tint: ?rl.Color,
) void {
    const world_transform = modelTransformFromBasis(position, right, up, forward);
    const local_offset = rl.Matrix.translate(
        -model.bounds.center.x,
        -model.bounds.center.y,
        -model.bounds.center.z,
    );
    const model_scale = rl.Matrix.scale(scale.x, scale.y, scale.z);
    const transform = world_transform.multiply(local_offset).multiply(model_scale);
    if (tint) |tint_color| {
        drawGameplayUploadedModelTinted(&model, transform, tint_color);
    } else {
        model.drawEx(transform);
    }
}

fn drawGameplayUploadedModelTinted(model: *const x2.Uploaded, transform: rl.Matrix, tint: rl.Color) void {
    for (model.submeshes) |submesh| {
        var material = submesh.material;
        material.maps[@intFromEnum(rl.MaterialMapIndex.albedo)].color = tint;
        rl.drawMesh(submesh.mesh, material, transform);
    }
}

const GameplayTurboPose = struct {
    position: rl.Vector3,
    right: rl.Vector3,
    up: rl.Vector3,
    forward: rl.Vector3,
    transform: rl.Matrix,
};

const gameplay_turbo_body_height: f32 = 0.02;
const tutorial_click_start_body_height: f32 = 0.08;

fn gameplayTurboPose(model: *const x2.Uploaded, loaded_track_preview: *const track.LoadedLevelPreview, runner: gameplay.Runner) GameplayTurboPose {
    const forward = normalizeVector3(runner.worldForward(loaded_track_preview));
    const up = normalizeVector3(runner.worldUp(loaded_track_preview));
    var right = crossVector3(up, forward);
    if (vectorLength(right) <= 0.0001) {
        right = .{ .x = 1.0, .y = 0.0, .z = 0.0 };
    } else {
        right = normalizeVector3(right);
    }
    const corrected_up = normalizeVector3(crossVector3(forward, right));
    const position = runner.worldPosition(loaded_track_preview, gameplay_turbo_body_height);
    const world_transform = modelTransformFromBasis(position, right, corrected_up, forward);
    const local_offset = groundedCharacterModelOffset(model);
    return .{
        .position = position,
        .right = right,
        .up = corrected_up,
        .forward = forward,
        .transform = world_transform.multiply(local_offset),
    };
}

fn tutorialClickStartTurboPose(model: *const x2.Uploaded, loaded_track_preview: *const track.LoadedLevelPreview, runner: gameplay.Runner) GameplayTurboPose {
    const base_pose = gameplayTurboPose(model, loaded_track_preview, runner);
    const position = runner.worldPosition(loaded_track_preview, tutorial_click_start_body_height);
    const world_transform = modelTransformFromBasis(position, base_pose.right, base_pose.up, base_pose.forward);
    const local_offset = groundedCharacterModelOffset(model);
    return .{
        .position = position,
        .right = base_pose.right,
        .up = base_pose.up,
        .forward = base_pose.forward,
        .transform = world_transform.multiply(local_offset),
    };
}

fn groundedCharacterModelOffset(model: *const x2.Uploaded) rl.Matrix {
    return rl.Matrix.translate(
        -model.bounds.center.x,
        -model.bounds.min.y,
        -model.bounds.center.z,
    );
}

fn centeredModelOffset(model: *const x2.Uploaded) rl.Matrix {
    return rl.Matrix.translate(
        -model.bounds.center.x,
        -model.bounds.center.y,
        -model.bounds.center.z,
    );
}

fn offsetPosition(
    origin: rl.Vector3,
    right: rl.Vector3,
    up: rl.Vector3,
    forward: rl.Vector3,
    local_x: f32,
    local_y: f32,
    local_z: f32,
) rl.Vector3 {
    return .{
        .x = origin.x + (right.x * local_x) + (up.x * local_y) + (forward.x * local_z),
        .y = origin.y + (right.y * local_x) + (up.y * local_y) + (forward.y * local_z),
        .z = origin.z + (right.z * local_x) + (up.z * local_y) + (forward.z * local_z),
    };
}

fn vectorLength(v: rl.Vector3) f32 {
    return std.math.sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

fn addVector3(a: rl.Vector3, b: rl.Vector3) rl.Vector3 {
    return .{
        .x = a.x + b.x,
        .y = a.y + b.y,
        .z = a.z + b.z,
    };
}

fn scaleVector3(v: rl.Vector3, scalar: f32) rl.Vector3 {
    return .{
        .x = v.x * scalar,
        .y = v.y * scalar,
        .z = v.z * scalar,
    };
}

fn normalizeVector3(v: rl.Vector3) rl.Vector3 {
    const len = vectorLength(v);
    if (len <= 0.0001) return .{ .x = 0.0, .y = 0.0, .z = 1.0 };
    return .{
        .x = v.x / len,
        .y = v.y / len,
        .z = v.z / len,
    };
}

fn crossVector3(a: rl.Vector3, b: rl.Vector3) rl.Vector3 {
    return .{
        .x = (a.y * b.z) - (a.z * b.y),
        .y = (a.z * b.x) - (a.x * b.z),
        .z = (a.x * b.y) - (a.y * b.x),
    };
}

fn lerpVector3(a: rl.Vector3, b: rl.Vector3, t: f32) rl.Vector3 {
    return .{
        .x = std.math.lerp(a.x, b.x, t),
        .y = std.math.lerp(a.y, b.y, t),
        .z = std.math.lerp(a.z, b.z, t),
    };
}

fn dotVector3(a: rl.Vector3, b: rl.Vector3) f32 {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

fn modelTransformFromBasis(position: rl.Vector3, right: rl.Vector3, up: rl.Vector3, forward: rl.Vector3) rl.Matrix {
    return .{
        .m0 = right.x,
        .m4 = up.x,
        .m8 = forward.x,
        .m12 = position.x,
        .m1 = right.y,
        .m5 = up.y,
        .m9 = forward.y,
        .m13 = position.y,
        .m2 = right.z,
        .m6 = up.z,
        .m10 = forward.z,
        .m14 = position.z,
        .m3 = 0.0,
        .m7 = 0.0,
        .m11 = 0.0,
        .m15 = 1.0,
    };
}

const CameraWorldTransform = struct {
    position: rl.Vector3,
    right: rl.Vector3,
    up: rl.Vector3,
    forward: rl.Vector3,
};

fn cameraWorldTransformFromMatrix(matrix: rl.Matrix) CameraWorldTransform {
    return .{
        .position = .{ .x = matrix.m12, .y = matrix.m13, .z = matrix.m14 },
        .right = .{ .x = matrix.m0, .y = matrix.m1, .z = matrix.m2 },
        .up = .{ .x = matrix.m4, .y = matrix.m5, .z = matrix.m6 },
        .forward = .{ .x = matrix.m8, .y = matrix.m9, .z = matrix.m10 },
    };
}

fn normalizeCameraWorldTransform(transform: CameraWorldTransform) CameraWorldTransform {
    const forward = normalizeVector3(transform.forward);
    var right = crossVector3(transform.up, forward);
    if (vectorLength(right) <= 0.0001) {
        right = normalizeVector3(transform.right);
    } else {
        right = normalizeVector3(right);
    }
    const up = normalizeVector3(crossVector3(forward, right));
    return .{
        .position = transform.position,
        .right = right,
        .up = up,
        .forward = forward,
    };
}

fn blendCameraWorldMatrices(lhs: rl.Matrix, rhs: rl.Matrix, t: f32) rl.Matrix {
    return gameplay.linearInterpolateCameraMatrices(lhs, rhs, t);
}

fn fovDegreesForSubgameCameraSource(source: SubgameCameraSource, live_fov_degrees: f32) f32 {
    return switch (source) {
        .live => live_fov_degrees,
        .override, .identity => 110.0,
    };
}

fn subgameCameraSelectionForRunner(runner: *gameplay.Runner) SubgameCameraSelection {
    if (runner.cutsceneCameraActive()) {
        return .{
            .source = .override,
            .matrix = runner.cutsceneCameraMatrix(),
            .fov_degrees = fovDegreesForSubgameCameraSource(.override, runner.cameramanFovDegrees()),
            .snap_next = runner.takeCutsceneCameraSnap(),
        };
    }
    return .{
        .source = .live,
        .matrix = runner.cameramanMatrix(),
        .fov_degrees = fovDegreesForSubgameCameraSource(.live, runner.cameramanFovDegrees()),
        .snap_next = runner.takeCameramanSnap(),
    };
}

fn updateSubgameCameraState(state: *SubgameCameraState, selection: SubgameCameraSelection) void {
    if (state.snap_next or selection.snap_next) {
        state.shared_matrix = selection.matrix;
        state.fov_degrees = selection.fov_degrees;
        state.source = selection.source;
        state.snap_next = false;
        return;
    }
    state.shared_matrix = blendCameraWorldMatrices(state.shared_matrix, selection.matrix, subgame_camera_blend_factor);
    state.fov_degrees = selection.fov_degrees;
    state.source = selection.source;
}

fn camera3DFromCameraWorldMatrix(matrix: rl.Matrix, fov_degrees: f32) rl.Camera3D {
    const transform = cameraWorldTransformFromMatrix(matrix);
    return .{
        .position = transform.position,
        .target = .{
            .x = transform.position.x + transform.forward.x,
            .y = transform.position.y + transform.forward.y,
            .z = transform.position.z + transform.forward.z,
        },
        .up = transform.up,
        .fovy = fov_degrees,
        .projection = .perspective,
    };
}

fn gameTrackSetIndexForLevel(level_track: level.Track) ?u8 {
    return switch (level_track) {
        .index => |index| switch (index) {
            0, 1, 2, 3 => @intCast(index),
            else => null,
        },
        .random => null,
    };
}

fn gameplayLevelCamera(subgame_camera: *const SubgameCameraState, loaded_track_preview: *const track.LoadedLevelPreview, fov_degrees: f32) rl.Camera3D {
    if (loaded_track_preview.total_rows == 0) {
        return loaded_track_preview.previewCamera(0.0, 0);
    }
    return camera3DFromCameraWorldMatrix(subgame_camera.shared_matrix, fov_degrees);
}

fn laneCenterTargetForRunnerMouse(
    loaded_track_preview: track.LoadedLevelPreview,
    runner: gameplay.Runner,
    mouse_x: f32,
) ?f32 {
    const probe_row_position = std.math.clamp(
        runner.row_position + 6.0,
        0.0,
        @max(@as(f32, @floatFromInt(loaded_track_preview.total_rows)) - 0.001, 0.0),
    );
    const probe_global_row = loaded_track_preview.rowIndexAtWorldZ(probe_row_position);
    const row_location = loaded_track_preview.locateRow(probe_global_row) orelse return null;
    const bounds = loaded_track_preview.laneBoundsForRow(row_location);
    return laneCenterTargetForMouseX(
        loaded_track_preview,
        mouse_x,
        @floatFromInt(screenWidth()),
        bounds,
    );
}

fn laneCenterTargetForMouseX(
    loaded_track_preview: track.LoadedLevelPreview,
    mouse_x: f32,
    screen_width: f32,
    bounds: track.LaneBounds,
) f32 {
    const width_offset = @as(f32, @floatFromInt(loaded_track_preview.max_width)) * 0.5;
    const authored_mouse_x = if (screen_width <= 1.0)
        320.0
    else
        (std.math.clamp(mouse_x, 0.0, screen_width - 1.0) / (screen_width - 1.0)) * 639.0;
    // PORT(verified): native `update_subgoldy` steers toward
    // `clamp((320.0 - mouse_x) * 0.0125, -3.7, 3.7)` in authored mouse space.
    const target_world_x = std.math.clamp((320.0 - authored_mouse_x) * (8.0 / 640.0), -3.7, 3.7);
    const lane_center = width_offset + target_world_x;
    return std.math.clamp(
        lane_center,
        @as(f32, @floatFromInt(bounds.min)) + 0.5,
        @as(f32, @floatFromInt(bounds.max)) + 0.5,
    );
}

fn triangleCountForObject(loaded_object: object.LoadedObject) usize {
    var total: usize = 0;
    for (loaded_object.submeshes) |submesh| {
        total += submesh.triangle_count;
    }
    return total;
}

fn uiContext(state: *const AppState) app_ui.Context {
    return .{ .font = &state.ui_font };
}

fn drawAppText(state: *const AppState, text: []const u8, x: i32, y: i32, font_size: i32, color: rl.Color) void {
    app_ui.drawText(uiContext(state), text, x, y, font_size, color);
}

fn measureAppText(state: *const AppState, text: []const u8, font_size: i32) i32 {
    return app_ui.measureText(uiContext(state), text, font_size);
}

fn drawWrappedText(state: *const AppState, text: []const u8, x: i32, y: i32, max_width: i32, line_height: i32, color: rl.Color) !void {
    return app_ui.drawWrappedText(uiContext(state), text, x, y, max_width, line_height, color);
}

fn drawMenuItem(state: *const AppState, layout: VirtualLayout, index: usize, selected_index: usize, label: []const u8) void {
    app_ui.drawMenuItem(uiContext(state), layout, index, selected_index, label);
}

fn drawRouteSelectionDots(state: *const AppState, layout: VirtualLayout, panels: MenuPanels, current_index: usize, max_index: usize) void {
    app_ui.drawRouteSelectionDots(uiContext(state), layout, panels, current_index, max_index);
}

fn modeLabel(mode: xanim.Mode) [:0]const u8 {
    return switch (mode) {
        .loop => "loop",
        .once => "once",
        .pingpong => "pingpong",
    };
}

fn nextMode(mode: Mode) Mode {
    return switch (mode) {
        .textures => .audio,
        .audio => .models,
        .models => .objects,
        .objects => .levels,
        .levels => .segments,
        .segments => .streaks,
        .streaks => .textures,
    };
}

fn optionalUsizeToText(buffer: []u8, value: ?usize) []const u8 {
    return if (value != null) std.fmt.bufPrint(buffer, "{d}", .{value.?}) catch "?" else "-";
}

fn takeOptional(comptime T: type, slot: *?T) ?T {
    if (slot.*) |value| {
        slot.* = null;
        return value;
    }
    return null;
}

fn wrappedIndex(count: usize, current: usize, delta: isize) usize {
    if (count == 0) return 0;

    const count_isize: isize = @intCast(count);
    const current_isize: isize = @intCast(current);
    var next = @mod(current_isize + delta, count_isize);
    if (next < 0) {
        next += count_isize;
    }
    return @intCast(next);
}

fn highScoreModeIndex(mode: high_score.Mode) usize {
    for (high_score_screen_modes, 0..) |candidate, index| {
        if (candidate == mode) return index;
    }
    return 0;
}

// PORT(verified): the original window bootstrap falls back to a 640x480 client area
// in windowed mode, while its fullscreen presets are also all 4:3.
// Evidence: sub_4119d0.
fn screenWidth() i32 {
    return rl.getScreenWidth();
}

fn screenHeight() i32 {
    return rl.getScreenHeight();
}

test "wrapped index handles negative deltas" {
    try std.testing.expectEqual(@as(usize, 4), wrappedIndex(5, 0, -1));
    try std.testing.expectEqual(@as(usize, 0), wrappedIndex(5, 0, 5));
}

test "next mode cycles through streak debug browser" {
    try std.testing.expectEqual(Mode.streaks, nextMode(.segments));
    try std.testing.expectEqual(Mode.textures, nextMode(.streaks));
}

test "completion bonus only applies to postal mode" {
    try std.testing.expect(completionBonusAppliesForMode(.postal));
    try std.testing.expect(!completionBonusAppliesForMode(.challenge));
    try std.testing.expect(!completionBonusAppliesForMode(.time_trial));
    try std.testing.expect(!completionBonusAppliesForMode(.tutorial));
    try std.testing.expect(completionBonusAppliesForMode(null));
}

test "frontend mode dispatch matches the recovered shared subgame routing" {
    try std.testing.expectEqual(gameplay.SessionMode.postal, frontendModeDispatch(.postal).session_mode);
    try std.testing.expectEqual(gameplay.SessionMode.challenge, frontendModeDispatch(.challenge).session_mode);
    try std.testing.expectEqual(gameplay.SessionMode.time_trial, frontendModeDispatch(.time_trial).session_mode);
    try std.testing.expectEqual(gameplay.SessionMode.tutorial, frontendModeDispatch(.tutorial).session_mode);

    try std.testing.expectEqual(track.postalChallengeRuntimeBuildFlags, frontendModeDispatch(.postal).runtime_build_flags);
    try std.testing.expectEqual(track.postalChallengeRuntimeBuildFlags, frontendModeDispatch(.challenge).runtime_build_flags);
    try std.testing.expectEqual(track.timeTrialRuntimeBuildFlags, frontendModeDispatch(.time_trial).runtime_build_flags);
    try std.testing.expectEqual(track.tutorialRuntimeBuildFlags, frontendModeDispatch(.tutorial).runtime_build_flags);
}

test "route map replay gate follows time-trial completion replays" {
    var tables = high_score.Tables.initDefault();
    tables.completion[0].has_replay = true;

    try std.testing.expect(routeMapHasReplayEntry(.time_trial, 1, &tables));
    try std.testing.expect(!routeMapHasReplayEntry(.postal, 1, &tables));
    try std.testing.expect(!routeMapHasReplayEntry(.time_trial, 0, &tables));
    try std.testing.expect(!routeMapHasReplayEntry(.time_trial, tables.completion.len + 1, &tables));

    tables.completion[0].has_replay = false;
    try std.testing.expect(!routeMapHasReplayEntry(.time_trial, 1, &tables));
}

test "high-score row replay is challenge-only" {
    try std.testing.expect(!highScoreRowsShowReplay(.postal, false));
    try std.testing.expect(highScoreRowsShowReplay(.challenge, false));
    try std.testing.expect(!highScoreRowsShowReplay(.challenge, true));
}

test "route map screen modes follow windows route-map entry paths" {
    try std.testing.expectEqual(RouteMapScreenMode.normal, defaultRouteMapScreenMode(.postal));
    try std.testing.expectEqual(RouteMapScreenMode.replay, defaultRouteMapScreenMode(.time_trial));
    try std.testing.expect(routeMapAllowsRouteSwitching(.normal));
    try std.testing.expect(routeMapAllowsRouteSwitching(.replay));
    try std.testing.expect(!routeMapAllowsRouteSwitching(.post_completion_exit));
    try std.testing.expectEqualStrings("Back", routeMapBackLabelForScreenMode(.normal));
    try std.testing.expectEqualStrings("Back", routeMapBackLabelForScreenMode(.replay));
    try std.testing.expectEqualStrings("Exit", routeMapBackLabelForScreenMode(.post_completion_exit));
}

test "route map body text stays empty without route script copy" {
    try std.testing.expectEqualStrings("", routeMapBodyText(null));
    try std.testing.expectEqualStrings("My first route!", routeMapBodyText("My first route!"));
}

test "run return targets follow the recovered native bridge where confirmed" {
    try std.testing.expectEqual(ResultReturnTarget.postal_route_map, resultReturnTargetForOutcome(.completed, .postal));
    try std.testing.expectEqual(ResultReturnTarget.time_trial_route_map, resultReturnTargetForOutcome(.completed, .time_trial));
    try std.testing.expectEqual(ResultReturnTarget.replay_current_level, resultReturnTargetForOutcome(.completed, .challenge));
    try std.testing.expectEqual(ResultReturnTarget.new_game_menu, resultReturnTargetForOutcome(.completed, .tutorial));
    try std.testing.expectEqual(ResultReturnTarget.new_game_menu, resultReturnTargetForOutcome(.failed, .postal));
    try std.testing.expectEqual(ResultReturnTarget.main_menu, resultReturnTargetForOutcome(.failed, .challenge));
    try std.testing.expectEqual(ResultReturnTarget.main_menu, resultReturnTargetForOutcome(.failed, .time_trial));
    try std.testing.expectEqual(ResultReturnTarget.main_menu, resultReturnTargetForOutcome(.failed, .tutorial));
}

test "selected replay return targets follow the launch surface" {
    try std.testing.expectEqual(
        ResultReturnTarget.time_trial_route_map,
        AppState.resultReturnTargetForSelectedReplaySource(.{ .completion = 7 }),
    );
    try std.testing.expectEqual(
        ResultReturnTarget.high_scores_menu,
        AppState.resultReturnTargetForSelectedReplaySource(.{ .postal = 2 }),
    );
    try std.testing.expectEqual(
        ResultReturnTarget.high_scores_menu,
        AppState.resultReturnTargetForSelectedReplaySource(.{ .challenge = 5 }),
    );
}

test "preserved frontend owner follows the native launch surface" {
    try std.testing.expectEqualDeep(
        FrontendBridgeTarget{ .route_map = .{
            .mode = .postal,
            .screen_mode = .normal,
        } },
        preservedFrontendOwnerForLevelLaunch(.postal, 1, null),
    );
    try std.testing.expectEqualDeep(
        FrontendBridgeTarget{ .route_map = .{
            .mode = .time_trial,
            .screen_mode = .replay,
        } },
        preservedFrontendOwnerForLevelLaunch(.time_trial, 3, null),
    );
    try std.testing.expectEqualDeep(
        FrontendBridgeTarget{ .new_game_menu = .challenge_mode },
        preservedFrontendOwnerForLevelLaunch(.challenge, 0, null),
    );
    try std.testing.expectEqualDeep(
        FrontendBridgeTarget{ .new_game_menu = .tutorial },
        preservedFrontendOwnerForLevelLaunch(.tutorial, 0, null),
    );
    try std.testing.expectEqualDeep(
        FrontendBridgeTarget{ .high_scores_menu = .postal },
        preservedFrontendOwnerForLevelLaunch(.postal, 2, .{ .postal = 2 }),
    );
    try std.testing.expectEqualDeep(
        FrontendBridgeTarget{ .route_map = .{
            .mode = .time_trial,
            .screen_mode = .replay,
            .start_route_override = 7,
        } },
        preservedFrontendOwnerForLevelLaunch(.time_trial, 7, .{ .completion = 3 }),
    );
}

test "abandon run bridge request follows replay-backed launch surfaces" {
    var state: AppState = undefined;
    const samples = try std.testing.allocator.alloc(high_score.DecodedReplaySample, 1);
    samples[0] = .{ .lateral = 0, .secondary_lane = 0, .flags = 0 };
    state.selected_replay_cache = .{
        .allocator = std.testing.allocator,
        .samples = samples,
    };
    defer if (state.selected_replay_cache) |*replay| replay.deinit();

    state.selected_level_record_source = .{ .challenge = 2 };
    state.active_frontend_level_index = 2;
    try std.testing.expectEqualDeep(
        OuterBridgeRequest{
            .opcode = .rebuild_clear_replay_return,
            .target = .{ .high_scores_menu = .challenge },
        },
        state.outerBridgeRequestForAbandonActiveRun(),
    );

    state.selected_level_record_source = .{ .completion = 7 };
    state.active_frontend_level_index = 7;
    try std.testing.expectEqualDeep(
        OuterBridgeRequest{
            .opcode = .rebuild_clear_replay_return,
            .target = .{ .route_map = .{
                .mode = .time_trial,
                .screen_mode = .replay,
                .start_route_override = 7,
            } },
        },
        state.outerBridgeRequestForAbandonActiveRun(),
    );
}

test "abandon run bridge request falls back to the preserved frontend owner" {
    var state: AppState = undefined;
    state.selected_replay_cache = null;
    state.selected_level_record_source = null;
    state.preserved_frontend_owner = .{ .route_map = .{
        .mode = .postal,
        .screen_mode = .normal,
    } };
    try std.testing.expectEqualDeep(
        OuterBridgeRequest{
            .opcode = .destroy_return,
            .target = .{ .route_map = .{
                .mode = .postal,
                .screen_mode = .normal,
            } },
        },
        state.outerBridgeRequestForAbandonActiveRun(),
    );

    state.preserved_frontend_owner = .{ .new_game_menu = .challenge_mode };
    try std.testing.expectEqualDeep(
        OuterBridgeRequest{
            .opcode = .destroy_return,
            .target = .{ .new_game_menu = .challenge_mode },
        },
        state.outerBridgeRequestForAbandonActiveRun(),
    );

    state.preserved_frontend_owner = .main_menu;
    try std.testing.expectEqualDeep(
        OuterBridgeRequest{
            .opcode = .destroy_return,
            .target = .main_menu,
        },
        state.outerBridgeRequestForAbandonActiveRun(),
    );
}

test "final postal completion returns through the thanks screen" {
    try std.testing.expectEqual(ResultReturnTarget.postal_route_map, postalCompletionReturnTarget(1, 0x32));
    try std.testing.expectEqual(ResultReturnTarget.thanks_screen, postalCompletionReturnTarget(0x32, 0x32));
    try std.testing.expectEqual(ResultReturnTarget.thanks_screen, postalCompletionReturnTarget(0x33, 0x33));
}

test "pending run result maps to explicit outer bridge opcodes" {
    var state: AppState = undefined;
    state.selected_level_record_source = null;
    state.selected_replay_cache = null;
    state.active_frontend_level_index = 4;
    state.selected_level_record_override = null;

    var result = PendingRunResult{
        .level_name = "x",
        .mode = .postal,
        .elapsed_millis = 0,
        .parcel_count = 0,
        .parcel_target = 0,
        .score = 0,
        .score_is_partial = false,
        .return_target = .new_game_menu,
    };
    try std.testing.expectEqualDeep(
        OuterBridgeRequest{
            .opcode = .destroy_return,
            .target = .{ .new_game_menu = .postal_mode },
        },
        state.outerBridgeRequestForPendingRunResult(result),
    );

    result.return_target = .thanks_screen;
    try std.testing.expectEqualDeep(
        OuterBridgeRequest{
            .opcode = .init_thanks_screen,
            .target = .thanks_screen,
        },
        state.outerBridgeRequestForPendingRunResult(result),
    );

    result.return_target = .replay_current_level;
    result.mode = .challenge;
    try std.testing.expectEqualDeep(
        OuterBridgeRequest{
            .opcode = .rebuild_return,
            .target = .{ .replay_current_level = .{
                .mode = .challenge,
                .level_index = 4,
            } },
        },
        state.outerBridgeRequestForPendingRunResult(result),
    );
}

test "frontend widget shortcut codes follow the recovered pause and post-score widgets" {
    var state: AppState = undefined;
    state.game_phase = .pause_menu;
    state.pending_run_result = null;
    try std.testing.expectEqualDeep(
        FrontendQueuedAction{ .pause_menu = .end_game },
        state.frontendShortcutActivationForCode(11).?,
    );
    try std.testing.expectEqualDeep(
        FrontendQueuedAction{ .pause_menu = .options },
        state.frontendShortcutActivationForCode(111).?,
    );
    try std.testing.expectEqualDeep(
        FrontendQueuedAction{ .pause_menu = .@"resume" },
        state.frontendShortcutActivationForCode(5).?,
    );
    try std.testing.expectEqualDeep(
        FrontendQueuedAction{ .pause_menu = .@"resume" },
        state.frontendShortcutActivationForCode(6).?,
    );

    state.game_phase = .high_scores_menu;
    state.pending_run_result = .{
        .level_name = "x",
        .mode = .postal,
        .elapsed_millis = 0,
        .parcel_count = 0,
        .parcel_target = 0,
        .score = 0,
        .score_is_partial = false,
        .high_score_mode = .postal,
        .high_score_rank = 0,
        .return_target = .postal_route_map,
    };
    try std.testing.expectEqualDeep(
        FrontendQueuedAction{ .post_level_high_scores = .cancel },
        state.frontendShortcutActivationForCode(11).?,
    );
    try std.testing.expectEqualDeep(
        FrontendQueuedAction{ .post_level_high_scores = .submit },
        state.frontendShortcutActivationForCode(5).?,
    );
    try std.testing.expectEqualDeep(
        FrontendQueuedAction{ .post_level_high_scores = .submit },
        state.frontendShortcutActivationForCode(6).?,
    );
    try std.testing.expectEqual(@as(?FrontendQueuedAction, null), state.frontendShortcutActivationForCode(111));
}

test "level segment prompt dispatch keys from the runner row message owner" {
    var catalog = try assets.Catalog.init(std.testing.allocator, default_archive_path);
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath(default_level_path) orelse return error.EntryNotFound;
    var loaded_level = try level.loadFromArchive(std.testing.allocator, &catalog, entry);

    var loaded_track_preview = try track.LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &loaded_level,
        .{ .load_models = false },
    );
    defer loaded_track_preview.deinit();

    var runner = gameplay.Runner.init(&loaded_track_preview);
    var target_logical_segment_index: ?usize = null;
    for (0..loaded_track_preview.total_rows) |global_row| {
        const row_location = loaded_track_preview.locateRow(global_row) orelse continue;
        const logical_segment_index = loaded_track_preview.segment_logical_indices[row_location.segment_index] orelse continue;
        if (loaded_level.segments[logical_segment_index].message == null) continue;
        target_logical_segment_index = logical_segment_index;
        break;
    }

    const logical_segment_index = target_logical_segment_index orelse return error.TestExpectedSegmentMessage;
    const expected_message = loaded_level.segments[logical_segment_index].message.?;
    var tick: usize = 0;
    while (tick < 4096 and runner.currentRowMessageLogicalSegmentIndex() != logical_segment_index) : (tick += 1) {
        runner.step(&loaded_track_preview, .{}, 1.0 / 60.0);
    }

    try std.testing.expectEqual(logical_segment_index, runner.currentRowMessageLogicalSegmentIndex().?);

    var state: AppState = undefined;
    state.current_level = loaded_level;
    defer if (state.current_level) |*owned_level| owned_level.deinit();
    state.level_runner = runner;
    state.active_frontend_mode = .tutorial;
    state.active_level_segment_index = null;
    state.level_prompt_queue = .{};
    state.gameplay_click_start_active = false;
    state.audio_ready = false;

    try state.syncActiveLevelSegment();
    try std.testing.expectEqual(@as(?level_prompt.Entry, null), state.level_prompt_queue.active());

    try state.dispatchCurrentRunnerRowMessage(null, null, true);
    try std.testing.expectEqual(@as(?usize, logical_segment_index), state.active_level_segment_index);
    try std.testing.expectEqualStrings(expected_message, state.level_prompt_queue.active().?.message);
}

test "completion reveal stages the bonus line before continue" {
    const result = PendingRunResult{
        .level_name = "To Infinity!",
        .mode = .postal,
        .elapsed_millis = 0,
        .parcel_count = 7,
        .parcel_target = 7,
        .score = 50_000,
        .score_is_partial = false,
        .score_totals = .{ .completion_bonus = 50_000 },
        .return_target = .postal_route_map,
    };

    try std.testing.expect(!completionBonusVisibleAtProgress(result, 0.999));
    try std.testing.expect(!completionContinueVisibleAtProgress(result, 0.999));
    try std.testing.expect(completionBonusVisibleAtProgress(result, 1.0));
    try std.testing.expect(!completionContinueVisibleAtProgress(result, 1.999));
    try std.testing.expect(completionContinueVisibleAtProgress(result, 2.0));
}

test "completion reveal skips the bonus stage when no bonus line exists" {
    const result = PendingRunResult{
        .level_name = "To Infinity!",
        .mode = .postal,
        .elapsed_millis = 0,
        .parcel_count = 5,
        .parcel_target = 7,
        .score = 0,
        .score_is_partial = true,
        .return_target = .postal_route_map,
    };

    try std.testing.expect(!completionBonusVisibleAtProgress(result, 1.0));
    try std.testing.expect(!completionContinueVisibleAtProgress(result, 0.999));
    try std.testing.expect(completionContinueVisibleAtProgress(result, 1.0));
}

test "completion overlay helpers distinguish overlay from finalized screen" {
    var state: AppState = undefined;
    state.pending_run_result = .{
        .outcome = .completed,
        .level_name = "To Infinity!",
        .mode = .postal,
        .elapsed_millis = 0,
        .parcel_count = 7,
        .parcel_target = 7,
        .score = 50_000,
        .score_is_partial = true,
        .return_target = .postal_route_map,
    };
    state.game_phase = .level;
    state.completion_overlay_active = true;
    state.frontend_transition = .{};

    try std.testing.expect(state.completionScreenActive());
    try std.testing.expect(state.completionScreenOverlayActive());
    try std.testing.expect(!state.completionScreenInteractive());

    state.game_phase = .completion_screen;
    state.completion_overlay_active = false;

    try std.testing.expect(state.completionScreenActive());
    try std.testing.expect(!state.completionScreenOverlayActive());
    try std.testing.expect(state.completionScreenInteractive());
}

test "completion reveal advances while the early overlay is active in level phase" {
    var state: AppState = undefined;
    state.pending_run_result = .{
        .outcome = .completed,
        .level_name = "To Infinity!",
        .mode = .postal,
        .elapsed_millis = 0,
        .parcel_count = 7,
        .parcel_target = 7,
        .score = 50_000,
        .score_is_partial = false,
        .score_totals = .{ .completion_bonus = 50_000 },
        .return_target = .postal_route_map,
    };
    state.game_phase = .level;
    state.completion_overlay_active = true;
    state.frontend_transition = .{};
    state.completion_screen_reveal_progress = 0.0;

    state.stepCompletionScreenReveal();

    try std.testing.expectApproxEqAbs(completion_reveal_step, state.completion_screen_reveal_progress, 0.0001);
}

test "postal completion copy matches the recovered widget strings" {
    var buffer: [64]u8 = undefined;
    try std.testing.expectEqualStrings("Delivery Complete!", resultTitle(.{
        .level_name = "To Infinity!",
        .mode = .postal,
        .elapsed_millis = 0,
        .parcel_count = 1,
        .parcel_target = 1,
        .score = 0,
        .score_is_partial = false,
        .return_target = .postal_route_map,
    }));
    try std.testing.expectEqualStrings("1 Package Delivered", try completionPackageLine(&buffer, .{
        .level_name = "To Infinity!",
        .mode = .postal,
        .elapsed_millis = 0,
        .parcel_count = 1,
        .parcel_target = 1,
        .score = 0,
        .score_is_partial = false,
        .return_target = .postal_route_map,
    }));
    try std.testing.expectEqualStrings("07 Packages Delivered", try completionPackageLine(&buffer, .{
        .level_name = "To Infinity!",
        .mode = .postal,
        .elapsed_millis = 0,
        .parcel_count = 7,
        .parcel_target = 7,
        .score = 0,
        .score_is_partial = false,
        .return_target = .postal_route_map,
    }));
}

test "elapsed millis format as mm:ss.cc" {
    var buffer: [32]u8 = undefined;
    const text = try formatElapsedMillis(&buffer, 91_230);
    try std.testing.expectEqualStrings("01:31.23", text);
}

test "tutorial score format uses commas" {
    var buffer: [24]u8 = undefined;
    const text = try formatScoreWithCommas(&buffer, 61_450);
    try std.testing.expectEqualStrings("61,450", text);
}

test "high score mode index follows screen order" {
    try std.testing.expectEqual(@as(usize, 0), highScoreModeIndex(.postal));
    try std.testing.expectEqual(@as(usize, 1), highScoreModeIndex(.challenge));
}

test "new game menu mapping matches frontend route modes" {
    try std.testing.expectEqual(NewGameMenuItem.postal_mode, newGameMenuItemForFrontendMode(.postal));
    try std.testing.expectEqual(NewGameMenuItem.time_trial, newGameMenuItemForFrontendMode(.time_trial));
    try std.testing.expectEqual(NewGameMenuItem.challenge_mode, newGameMenuItemForFrontendMode(.challenge));
    try std.testing.expectEqual(NewGameMenuItem.tutorial, newGameMenuItemForFrontendMode(.tutorial));
    try std.testing.expectEqual(@as(usize, 1), newGameMenuIndexForItem(.postal_mode));
    try std.testing.expectEqual(@as(usize, 2), newGameMenuIndexForItem(.time_trial));
    try std.testing.expectEqual(@as(usize, 4), newGameMenuIndexForItem(.help));
}

test "postal unlock limit stops at the highest available route" {
    try std.testing.expectEqual(@as(usize, 2), AppState.nextPostalUnlockLimit(1, 0x32, 1));
    try std.testing.expectEqual(@as(usize, 0x32), AppState.nextPostalUnlockLimit(0x32, 0x32, 0x32));
    try std.testing.expectEqual(@as(usize, 0x33), AppState.nextPostalUnlockLimit(0x33, 0x33, 0x33));
    try std.testing.expectEqual(@as(usize, 0x32), AppState.nextPostalUnlockLimit(0x33, 0x32, 0x40));
}

test "postal unlock preview only reports newly unlocked routes" {
    try std.testing.expect(AppState.previewPostalRouteUnlock(1, 0x32, 1));
    try std.testing.expect(!AppState.previewPostalRouteUnlock(0x32, 0x32, 0x32));
    try std.testing.expect(!AppState.previewPostalRouteUnlock(0x33, 0x32, 0x40));
}

test "postal high-score commit gates on the final shipped route" {
    try std.testing.expect(!AppState.postalCompletionCommitsHighScore(1, 0x32));
    try std.testing.expect(!AppState.postalCompletionCommitsHighScore(0x31, 0x32));
    try std.testing.expect(AppState.postalCompletionCommitsHighScore(0x32, 0x32));
    try std.testing.expect(AppState.postalCompletionCommitsHighScore(0x33, 0x33));
}

test "thanks screen message sequence matches the recovered owner timing" {
    var controller = ThanksScreenController{};
    try std.testing.expectEqualStrings("Thanks For Playing!", controller.currentText().?);
    try std.testing.expect(!controller.allowsContinue());

    for (0..241) |_| controller.step();
    try std.testing.expectEqual(ThanksScreenStage.title_hidden, controller.stage);
    try std.testing.expectEqual(@as(?[]const u8, null), controller.currentText());

    for (0..31) |_| controller.step();
    try std.testing.expectEqual(ThanksScreenStage.challenge_visible, controller.stage);
    try std.testing.expectEqualStrings("Test your reflexes in Challenge Mode!", controller.currentText().?);
    try std.testing.expect(controller.allowsContinue());

    for (0..241) |_| controller.step();
    try std.testing.expectEqual(ThanksScreenStage.challenge_hidden, controller.stage);
    try std.testing.expectEqual(@as(?[]const u8, null), controller.currentText());

    for (0..31) |_| controller.step();
    try std.testing.expectEqual(ThanksScreenStage.time_trial_visible, controller.stage);
    try std.testing.expectEqualStrings("Improve your skills in Time Trial!", controller.currentText().?);

    for (0..241) |_| controller.step();
    try std.testing.expectEqual(ThanksScreenStage.time_trial_hidden, controller.stage);
    try std.testing.expectEqual(@as(?[]const u8, null), controller.currentText());

    for (0..31) |_| controller.step();
    try std.testing.expectEqual(ThanksScreenStage.continue_visible, controller.stage);
    try std.testing.expectEqualStrings("Click to Continue", controller.currentText().?);

    for (0..241) |_| controller.step();
    try std.testing.expectEqual(ThanksScreenStage.continue_hold, controller.stage);
    try std.testing.expectEqualStrings("Click to Continue", controller.currentText().?);
    try std.testing.expectEqual(@as(f32, 0.0), controller.progress_step);
}

test "preview descending high-score rank matches visible insertion rules" {
    var tables = high_score.Tables.initDefault();
    defer tables.deinit(std.testing.allocator);

    for (tables.postal[0..high_score.visible_entry_count], 0..) |*entry, index| {
        entry.* = .{ .score = @as(u32, @intCast(1000 - index * 10)) };
    }

    try std.testing.expectEqual(@as(?usize, 5), AppState.previewDescendingHighScoreRank(tables.postal[0..], 955));
    try std.testing.expectEqual(@as(?usize, null), AppState.previewDescendingHighScoreRank(tables.postal[0..], 900));
}

test "current run high-score entry carries replay mode and build settings" {
    var state: AppState = undefined;
    state.runtime_config = config.Blob.initDefault();
    state.runtime_config.setChallengeReplaySpeedValue(100);
    state.runtime_config.setChallengeReplayDifficultyValue(55);
    state.active_frontend_mode = .challenge;
    state.active_frontend_level_index = 7;
    state.current_track_preview = null;
    state.current_runtime_build_seed = 321;
    state.selected_level_record_override = null;
    state.selected_replay_cache = null;

    const entry = state.currentRunHighScoreEntry(12_345);
    try std.testing.expectEqual(@as(u32, 12_345), entry.score);
    try std.testing.expectEqual(@as(u32, 7), entry.replay_level_index);
    try std.testing.expectEqual(@as(u32, 1), entry.replay_mode_id);
    try std.testing.expectEqual(@as(u32, 100), entry.challenge_speed_value);
    try std.testing.expectApproxEqAbs(@as(f32, 1.1), entry.replay_speed_scalar, 0.0001);
    try std.testing.expectEqual(@as(u32, 55), entry.challenge_difficulty_value);
    try std.testing.expectEqual(@as(u32, track.defaultRuntimeBuildFlags), entry.runtime_build_flags);
    try std.testing.expectApproxEqAbs(@as(f32, 0.55), entry.challenge_difficulty_scalar, 0.0001);
    try std.testing.expectEqual(@as(u32, 321), entry.runtime_build_seed);
    try std.testing.expectApproxEqAbs(@as(f32, 0.44), entry.garbage_scalar, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.44), entry.salt_scalar, 0.0001);
}

test "challenge parcel target matches recovered placement formula" {
    try std.testing.expectEqual(@as(usize, 1), AppState.challengeParcelTargetCount(0, 0.0));
    try std.testing.expectEqual(@as(usize, 41), AppState.challengeParcelTargetCount(40, 0.4));
    try std.testing.expectEqual(@as(usize, 78), AppState.challengeParcelTargetCount(100, 0.55));
}

test "current parcel target prefers live preview count" {
    var state: AppState = undefined;
    var preview: track.LoadedLevelPreview = undefined;
    preview.parcel_target_count = 37;
    state.current_track_preview = preview;
    state.current_level = null;
    try std.testing.expectEqual(@as(usize, 37), state.currentParcelTarget());

    var loaded_level: level.Definition = undefined;
    loaded_level.parcels = 9;
    state.current_track_preview = null;
    state.current_level = loaded_level;
    try std.testing.expectEqual(@as(usize, 9), state.currentParcelTarget());
}

test "mode-specific runtime build flags follow recovered subgame presets" {
    var state: AppState = undefined;
    state.current_track_preview = null;
    state.selected_level_record_override = null;
    state.selected_replay_cache = null;

    state.active_frontend_mode = .postal;
    try std.testing.expectEqual(@as(u32, track.postalChallengeRuntimeBuildFlags), state.currentRunRuntimeBuildFlags());

    state.active_frontend_mode = .challenge;
    try std.testing.expectEqual(@as(u32, track.postalChallengeRuntimeBuildFlags), state.currentRunRuntimeBuildFlags());

    state.active_frontend_mode = .time_trial;
    try std.testing.expectEqual(@as(u32, track.timeTrialRuntimeBuildFlags), state.currentRunRuntimeBuildFlags());

    state.active_frontend_mode = .tutorial;
    try std.testing.expectEqual(@as(u32, track.tutorialRuntimeBuildFlags), state.currentRunRuntimeBuildFlags());
}

test "selected level record override follows recovered compact lanes" {
    const entry = high_score.Entry{
        .replay_level_index = 12,
        .replay_mode_id = 4,
        .runtime_build_flags = 0x0075cfff,
        .replay_speed_scalar = 0.74,
        .challenge_speed_value = 55,
        .challenge_difficulty_value = 40,
        .challenge_difficulty_scalar = 0.4,
        .runtime_build_seed = 222,
        .garbage_scalar = 0.32,
        .salt_scalar = 0.45,
    };
    const record = SelectedLevelRecordOverride.fromHighScoreEntry(&entry) orelse return error.TestUnexpectedResult;

    try std.testing.expectEqual(FrontendLevelMode.time_trial, record.mode);
    try std.testing.expectEqual(@as(usize, 12), record.level_index);
    try std.testing.expectEqual(@as(u32, 0x0075cfff), record.runtime_build_flags);
    try std.testing.expectApproxEqAbs(@as(f32, 0.74), record.replay_speed_scalar, 0.0001);
    try std.testing.expectEqual(@as(u32, 55), record.challenge_speed_value);
    try std.testing.expectEqual(@as(u32, 40), record.challenge_difficulty_value);
    try std.testing.expectApproxEqAbs(@as(f32, 0.4), record.challenge_difficulty_scalar, 0.0001);
    try std.testing.expectEqual(@as(u32, 222), record.runtime_build_seed);
    try std.testing.expectApproxEqAbs(@as(f32, 0.32), record.garbage_scalar, 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.45), record.salt_scalar, 0.0001);
}

test "selected level record override rejects unresolved mode ids" {
    const entry = high_score.Entry{
        .replay_level_index = 1,
        .replay_mode_id = 3,
    };
    try std.testing.expect(SelectedLevelRecordOverride.fromHighScoreEntry(&entry) == null);
}

test "selected replay directive decodes compact lateral x and the secondary lane" {
    var tables = high_score.Tables.initDefault();
    defer tables.deinit(std.testing.allocator);

    const record_len = 0x88 + 5;
    const raw_record = try std.testing.allocator.alloc(u8, record_len);
    @memset(raw_record, 0);
    std.mem.writeInt(u32, raw_record[0x74..0x78], 1, .little);
    std.mem.writeInt(i16, raw_record[0x88..0x8a], 0x1800, .little);
    std.mem.writeInt(i16, raw_record[0x8a..0x8c], 0, .little);
    raw_record[0x8c] = 0x0c;
    tables.completion[0].raw_record = raw_record;
    tables.completion[0].has_replay = true;

    var replay = try tables.completion[0].decodeReplay(std.testing.allocator);
    defer replay.deinit();

    const first = AppState.selectedReplayDirectiveForDecodedReplay(&replay, 0);
    try std.testing.expect(first.active);
    try std.testing.expectApproxEqAbs(@as(f32, 1.5), first.lateral_world_x.?, 0.0001);
    try std.testing.expectEqual(@as(?i32, 0), first.secondary_lane);
    try std.testing.expectEqual(@as(u8, 0x0c), first.raw_flag_bits);

    const tail = AppState.selectedReplayDirectiveForDecodedReplay(&replay, 1);
    try std.testing.expect(tail.active);
    try std.testing.expect(tail.lateral_world_x == null);
    try std.testing.expectEqual(@as(u8, 0), tail.raw_flag_bits);
}

test "selected replay results skip persistence and score-table awards" {
    var state: AppState = undefined;
    state.high_score_tables = high_score.Tables.initDefault();
    defer state.high_score_tables.deinit(std.testing.allocator);
    state.selected_level_record_source = .{ .challenge = 2 };
    state.selected_replay_cache = null;

    const raw_record = try std.testing.allocator.alloc(u8, 0x88 + 5);
    @memset(raw_record, 0);
    std.mem.writeInt(u32, raw_record[0x74..0x78], 1, .little);
    state.high_score_tables.challenge[2].raw_record = raw_record;
    state.high_score_tables.challenge[2].has_replay = true;
    state.selected_replay_cache = try state.high_score_tables.challenge[2].decodeReplay(std.testing.allocator);
    defer if (state.selected_replay_cache) |*replay| replay.deinit();

    var result = PendingRunResult{
        .level_name = "Replay",
        .mode = .challenge,
        .elapsed_millis = 1234,
        .parcel_count = 0,
        .parcel_target = 0,
        .score = 42_000,
        .score_is_partial = true,
        .high_score_mode = .challenge,
        .high_score_rank = 3,
        .time_trial_record_improved = true,
        .unlocked_next_route = true,
        .persistence = .completed,
        .return_target = .main_menu,
    };
    state.applySelectedReplayResultOverrides(&result);

    try std.testing.expectEqual(PendingRunPersistence.none, result.persistence);
    try std.testing.expect(result.high_score_mode == null);
    try std.testing.expect(result.high_score_rank == null);
    try std.testing.expect(!result.time_trial_record_improved);
    try std.testing.expect(!result.unlocked_next_route);
    try std.testing.expectEqual(ResultReturnTarget.high_scores_menu, result.return_target);
}

test "selected level record override drives live run tuning lanes" {
    var state: AppState = undefined;
    state.runtime_config = config.Blob.initDefault();
    state.current_track_preview = null;
    state.current_level = null;
    state.active_frontend_mode = .challenge;
    state.selected_replay_cache = null;
    state.selected_level_record_override = .{
        .mode = .challenge,
        .level_index = 0,
        .runtime_build_flags = 0x00f5cfff,
        .replay_speed_scalar = 0.56,
        .challenge_speed_value = 40,
        .challenge_difficulty_value = 55,
        .challenge_difficulty_scalar = 0.55,
        .runtime_build_seed = 444,
        .garbage_scalar = 0.12,
        .salt_scalar = 0.34,
    };

    try std.testing.expectApproxEqAbs(@as(f32, 0.56), state.currentRunReplaySpeedScalar(), 0.0001);
    try std.testing.expectEqual(@as(u32, 40), state.currentRunChallengeSpeedValue());
    try std.testing.expectEqual(@as(u32, 55), state.currentRunChallengeDifficultyValue());
    try std.testing.expectApproxEqAbs(@as(f32, 0.55), state.currentRunChallengeDifficultyScalar(), 0.0001);
    try std.testing.expectEqual(@as(u32, 0x00f5cfff), state.currentRunRuntimeBuildFlags());
    try std.testing.expectApproxEqAbs(@as(f32, 0.12), state.currentRunGarbageScalar(), 0.0001);
    try std.testing.expectApproxEqAbs(@as(f32, 0.34), state.currentRunSaltScalar(), 0.0001);
}

test "selected level record override seeds track rebuilds without frontend rng" {
    var state: AppState = undefined;
    state.command = .game;
    state.active_frontend_mode = .time_trial;
    state.active_frontend_level_index = 9;
    state.level_index = 123;
    state.current_runtime_build_seed = 0;
    state.current_runtime_build_seed_level_index = null;
    state.current_runtime_build_seed_mode = null;
    state.selected_level_record_override = .{
        .mode = .time_trial,
        .level_index = 9,
        .runtime_build_flags = track.timeTrialRuntimeBuildFlags,
        .replay_speed_scalar = 0.74,
        .challenge_speed_value = 0,
        .challenge_difficulty_value = 0,
        .challenge_difficulty_scalar = 0.0,
        .runtime_build_seed = 777,
        .garbage_scalar = 0.11,
        .salt_scalar = 0.22,
    };

    try std.testing.expectEqual(@as(u32, 777), state.trackBuildSeedForCurrentLoad());
    try std.testing.expectEqual(@as(u32, 777), state.current_runtime_build_seed);
    try std.testing.expectEqual(@as(?usize, 123), state.current_runtime_build_seed_level_index);
    try std.testing.expectEqual(@as(?FrontendLevelMode, .time_trial), state.current_runtime_build_seed_mode);
}

fn seededLiveSubgameCamera(runner_input: gameplay.Runner) SubgameCameraState {
    var runner = runner_input;
    var subgame_camera = SubgameCameraState{};
    updateSubgameCameraState(&subgame_camera, subgameCameraSelectionForRunner(&runner));
    return subgame_camera;
}

test "gameplay camera looks ahead of the runner" {
    var catalog = try assets.Catalog.init(std.testing.allocator, default_archive_path);
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath(default_level_path) orelse return error.EntryNotFound;
    var loaded_level = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer loaded_level.deinit();

    var loaded_track_preview = try track.LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &loaded_level,
        .{ .load_models = false },
    );
    defer loaded_track_preview.deinit();

    var runner = gameplay.Runner.init(&loaded_track_preview);
    runner.step(&loaded_track_preview, .{}, @floatCast(simulation_step_seconds));
    const subgame_camera = seededLiveSubgameCamera(runner);

    const camera = gameplayLevelCamera(&subgame_camera, &loaded_track_preview, subgame_camera.fov_degrees);
    const transform = cameraWorldTransformFromMatrix(subgame_camera.shared_matrix);
    const player_position = runner.worldPosition(&loaded_track_preview, 0.82);
    try std.testing.expect(camera.target.z > camera.position.z);
    try std.testing.expect(camera.position.z < player_position.z);
    try std.testing.expect(camera.position.y > 0.0);
    try std.testing.expect(camera.position.y > player_position.y);
    try std.testing.expectApproxEqAbs(transform.position.x + transform.forward.x, camera.target.x, 0.001);
    try std.testing.expectApproxEqAbs(transform.position.y + transform.forward.y, camera.target.y, 0.001);
    try std.testing.expectApproxEqAbs(transform.position.z + transform.forward.z, camera.target.z, 0.001);
    try std.testing.expectApproxEqAbs(runner.cameramanFovDegrees(), camera.fovy, 0.001);
}

test "gameplay camera keeps lateral steering mostly behind turbo" {
    var catalog = try assets.Catalog.init(std.testing.allocator, default_archive_path);
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath(default_level_path) orelse return error.EntryNotFound;
    var loaded_level = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer loaded_level.deinit();

    var loaded_track_preview = try track.LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &loaded_level,
        .{ .load_models = false },
    );
    defer loaded_track_preview.deinit();

    var runner = gameplay.Runner.init(&loaded_track_preview);
    runner.lane_center = 6.5;
    runner.lane_index = 6;
    runner.resolved_lane_index = 6;
    runner.step(&loaded_track_preview, .{}, @floatCast(simulation_step_seconds));
    const subgame_camera = seededLiveSubgameCamera(runner);

    const camera = gameplayLevelCamera(&subgame_camera, &loaded_track_preview, subgame_camera.fov_degrees);
    const player_position = runner.worldPosition(&loaded_track_preview, 0.82);

    try std.testing.expect(player_position.x > 0.0);
    try std.testing.expect(camera.position.x > 0.0);
    try std.testing.expect(camera.target.x > 0.0);
    try std.testing.expect(camera.target.x < player_position.x);
    try std.testing.expect(camera.position.x <= player_position.x);
}

test "shared gameplay camera derives target and up from the shared matrix" {
    var catalog = try assets.Catalog.init(std.testing.allocator, default_archive_path);
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath(default_level_path) orelse return error.EntryNotFound;
    var loaded_level = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer loaded_level.deinit();

    var loaded_track_preview = try track.LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &loaded_level,
        .{ .load_models = false },
    );
    defer loaded_track_preview.deinit();

    var runner = gameplay.Runner.init(&loaded_track_preview);
    runner.step(&loaded_track_preview, .{}, @floatCast(simulation_step_seconds));
    const subgame_camera = seededLiveSubgameCamera(runner);
    const camera = gameplayLevelCamera(&subgame_camera, &loaded_track_preview, subgame_camera.fov_degrees);
    const transform = cameraWorldTransformFromMatrix(subgame_camera.shared_matrix);
    try std.testing.expectApproxEqAbs(transform.position.x, camera.position.x, 0.001);
    try std.testing.expectApproxEqAbs(transform.position.y, camera.position.y, 0.001);
    try std.testing.expectApproxEqAbs(transform.position.z, camera.position.z, 0.001);
    try std.testing.expectApproxEqAbs(transform.up.x, camera.up.x, 0.001);
    try std.testing.expectApproxEqAbs(transform.up.y, camera.up.y, 0.001);
    try std.testing.expectApproxEqAbs(transform.up.z, camera.up.z, 0.001);
    try std.testing.expectApproxEqAbs(transform.position.z + transform.forward.z, camera.target.z, 0.001);
}

test "intro cutscene override seeds the shared camera and later clears back to live" {
    var catalog = try assets.Catalog.init(std.testing.allocator, default_archive_path);
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath(default_level_path) orelse return error.EntryNotFound;
    var loaded_level = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer loaded_level.deinit();

    var loaded_track_preview = try track.LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &loaded_level,
        .{ .load_models = false },
    );
    defer loaded_track_preview.deinit();

    var runner = gameplay.Runner.init(&loaded_track_preview);
    var subgame_camera = SubgameCameraState{};
    runner.setCutscene(gameplay.cutscene_intro_id);
    runner.refreshCameraState(&loaded_track_preview);
    updateSubgameCameraState(&subgame_camera, subgameCameraSelectionForRunner(&runner));

    try std.testing.expectEqual(SubgameCameraSource.override, subgame_camera.source);
    try std.testing.expectApproxEqAbs(@as(f32, 110.0), subgame_camera.fov_degrees, 0.001);

    for (0..gameplay.intro_cutscene_duration_ticks + 2) |_| {
        runner.refreshCameraState(&loaded_track_preview);
        updateSubgameCameraState(&subgame_camera, subgameCameraSelectionForRunner(&runner));
    }

    try std.testing.expectEqual(gameplay.cutscene_none_id, runner.cutscene_id);
    try std.testing.expectEqual(SubgameCameraSource.live, subgame_camera.source);
}

test "blocked click-start refresh path primes the tutorial start attachment camera" {
    var catalog = try assets.Catalog.init(std.testing.allocator, default_archive_path);
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath(default_level_path) orelse return error.EntryNotFound;
    var loaded_level = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer loaded_level.deinit();

    var loaded_track_preview = try track.LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &loaded_level,
        .{ .load_models = false },
    );
    defer loaded_track_preview.deinit();

    var runner = gameplay.Runner.init(&loaded_track_preview);
    var subgame_camera = SubgameCameraState{};

    runner.refreshBlockedStartupState(&loaded_track_preview);
    updateSubgameCameraState(&subgame_camera, subgameCameraSelectionForRunner(&runner));

    const camera = gameplayLevelCamera(&subgame_camera, &loaded_track_preview, subgame_camera.fov_degrees);
    try std.testing.expectEqual(gameplay.MovementMode.attachment, runner.movement_mode);
    try std.testing.expect(runner.worldPosition(&loaded_track_preview, 0.0).y >= 7.9);
    try std.testing.expect(camera.position.y > 0.0);
    try std.testing.expect(camera.target.z > camera.position.z);
    try std.testing.expect(subgame_camera.source == .live);
    try std.testing.expect(!subgame_camera.snap_next);
}

test "intro cutscene click-start path still primes the tutorial start attachment under override camera" {
    var catalog = try assets.Catalog.init(std.testing.allocator, default_archive_path);
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath(default_level_path) orelse return error.EntryNotFound;
    var loaded_level = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer loaded_level.deinit();

    var loaded_track_preview = try track.LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &loaded_level,
        .{ .load_models = false },
    );
    defer loaded_track_preview.deinit();

    var runner = gameplay.Runner.init(&loaded_track_preview);
    var subgame_camera = SubgameCameraState{};
    runner.setCutscene(gameplay.cutscene_intro_id);

    runner.refreshBlockedStartupState(&loaded_track_preview);
    updateSubgameCameraState(&subgame_camera, subgameCameraSelectionForRunner(&runner));

    try std.testing.expectEqual(gameplay.MovementMode.attachment, runner.movement_mode);
    try std.testing.expect(runner.attachment_follow.active);
    try std.testing.expectEqual(SubgameCameraSource.override, subgame_camera.source);
    try std.testing.expect(runner.cutsceneCameraActive());
}

test "startup block after click-start dismissal resumes the live runner under intro camera" {
    var catalog = try assets.Catalog.init(std.testing.allocator, default_archive_path);
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath(default_level_path) orelse return error.EntryNotFound;
    var loaded_level = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer loaded_level.deinit();

    var loaded_track_preview = try track.LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &loaded_level,
        .{ .load_models = false },
    );
    defer loaded_track_preview.deinit();

    var state: AppState = undefined;
    state.gameplay_click_start_active = false;
    state.level_runner = gameplay.Runner.init(&loaded_track_preview);
    state.level_runner.?.setCutscene(gameplay.cutscene_intro_id);
    state.level_runner.?.refreshBlockedStartupState(&loaded_track_preview);
    const starting_row_position = state.level_runner.?.row_position;

    try std.testing.expect(state.startupGameplayBlockActive());

    state.refreshRunnerForStartupBlock(
        &state.level_runner.?,
        &loaded_track_preview,
        @floatCast(simulation_step_seconds),
    );

    try std.testing.expectEqual(gameplay.MovementMode.attachment, state.level_runner.?.movement_mode);
    try std.testing.expect(state.level_runner.?.attachment_follow.active);
    try std.testing.expect(state.level_runner.?.cutsceneCameraActive());
    try std.testing.expect(state.level_runner.?.movement_rate_scalar > 0.0);
    try std.testing.expect(state.level_runner.?.row_position > starting_row_position);
}

test "intro light streak camera falls back to the default star-field camera" {
    var state: AppState = undefined;
    state.game_phase = .intro;
    state.subgame_camera = .{};

    const camera = backgroundLightStreakCamera(&state);
    try std.testing.expectApproxEqAbs(default_light_streak_camera.position.x, camera.position.x, 0.001);
    try std.testing.expectApproxEqAbs(default_light_streak_camera.position.y, camera.position.y, 0.001);
    try std.testing.expectApproxEqAbs(default_light_streak_camera.position.z, camera.position.z, 0.001);
    try std.testing.expectApproxEqAbs(default_light_streak_camera.fov_degrees, camera.fov_degrees, 0.001);
    try std.testing.expectApproxEqAbs(default_light_streak_camera.forward.x, camera.forward.x, 0.001);
    try std.testing.expectApproxEqAbs(default_light_streak_camera.forward.y, camera.forward.y, 0.001);
    try std.testing.expectApproxEqAbs(default_light_streak_camera.forward.z, camera.forward.z, 0.001);
}

test "credits phase keeps the native star-field visibility" {
    var state: AppState = undefined;
    state.game_phase = .credits;
    state.options_return_phase = .main_menu;
    state.exit_prompt_return_phase = .main_menu;

    try std.testing.expect(backgroundLightStreaksVisible(&state));
}

test "shared subgame camera honors snap flags and otherwise blends across source changes" {
    const basis_right = rl.Vector3{ .x = 1.0, .y = 0.0, .z = 0.0 };
    const basis_up = rl.Vector3{ .x = 0.0, .y = 1.0, .z = 0.0 };
    const basis_forward = rl.Vector3{ .x = 0.0, .y = 0.0, .z = 1.0 };
    const live_matrix = modelTransformFromBasis(.{ .x = 1.0, .y = 2.0, .z = 3.0 }, basis_right, basis_up, basis_forward);
    const override_matrix = modelTransformFromBasis(.{ .x = 5.0, .y = 6.0, .z = 7.0 }, basis_right, basis_up, basis_forward);
    const next_live_matrix = modelTransformFromBasis(.{ .x = 9.0, .y = 10.0, .z = 11.0 }, basis_right, basis_up, basis_forward);
    var state = SubgameCameraState{};

    updateSubgameCameraState(&state, .{
        .source = .live,
        .matrix = live_matrix,
        .fov_degrees = 110.0,
        .snap_next = true,
    });
    try std.testing.expectApproxEqAbs(@as(f32, 1.0), state.shared_matrix.m12, 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, 2.0), state.shared_matrix.m13, 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, 3.0), state.shared_matrix.m14, 0.001);

    updateSubgameCameraState(&state, .{
        .source = .override,
        .matrix = override_matrix,
        .fov_degrees = 110.0,
        .snap_next = true,
    });
    try std.testing.expectApproxEqAbs(@as(f32, 5.0), state.shared_matrix.m12, 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, 6.0), state.shared_matrix.m13, 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, 7.0), state.shared_matrix.m14, 0.001);

    updateSubgameCameraState(&state, .{
        .source = .live,
        .matrix = live_matrix,
        .fov_degrees = 120.0,
        .snap_next = false,
    });
    try std.testing.expectApproxEqAbs(std.math.lerp(@as(f32, 5.0), @as(f32, 1.0), subgame_camera_blend_factor), state.shared_matrix.m12, 0.001);
    try std.testing.expectApproxEqAbs(std.math.lerp(@as(f32, 6.0), @as(f32, 2.0), subgame_camera_blend_factor), state.shared_matrix.m13, 0.001);
    try std.testing.expectApproxEqAbs(std.math.lerp(@as(f32, 7.0), @as(f32, 3.0), subgame_camera_blend_factor), state.shared_matrix.m14, 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, 120.0), state.fov_degrees, 0.001);

    updateSubgameCameraState(&state, .{
        .source = .live,
        .matrix = next_live_matrix,
        .fov_degrees = 130.0,
        .snap_next = false,
    });
    try std.testing.expectApproxEqAbs(
        std.math.lerp(
            std.math.lerp(@as(f32, 5.0), @as(f32, 1.0), subgame_camera_blend_factor),
            @as(f32, 9.0),
            subgame_camera_blend_factor,
        ),
        state.shared_matrix.m12,
        0.001,
    );
    try std.testing.expectApproxEqAbs(
        std.math.lerp(
            std.math.lerp(@as(f32, 6.0), @as(f32, 2.0), subgame_camera_blend_factor),
            @as(f32, 10.0),
            subgame_camera_blend_factor,
        ),
        state.shared_matrix.m13,
        0.001,
    );
    try std.testing.expectApproxEqAbs(
        std.math.lerp(
            std.math.lerp(@as(f32, 7.0), @as(f32, 3.0), subgame_camera_blend_factor),
            @as(f32, 11.0),
            subgame_camera_blend_factor,
        ),
        state.shared_matrix.m14,
        0.001,
    );
    try std.testing.expectApproxEqAbs(@as(f32, 130.0), state.fov_degrees, 0.001);
}

test "non-live subgame camera sources force the recovered 110-degree FOV" {
    try std.testing.expectApproxEqAbs(@as(f32, 160.0), fovDegreesForSubgameCameraSource(.live, 160.0), 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, 110.0), fovDegreesForSubgameCameraSource(.override, 160.0), 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, 110.0), fovDegreesForSubgameCameraSource(.identity, 160.0), 0.001);
}

test "mouse lane-center target mapping respects bounds" {
    const bounds: track.LaneBounds = .{ .min = 2, .max = 4 };
    var catalog = try assets.Catalog.init(std.testing.allocator, default_archive_path);
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath(default_level_path) orelse return error.EntryNotFound;
    var loaded_level = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer loaded_level.deinit();

    var loaded_track_preview = try track.LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &loaded_level,
        .{ .load_models = false },
    );
    defer loaded_track_preview.deinit();

    try std.testing.expectApproxEqAbs(@as(f32, 4.5), laneCenterTargetForMouseX(loaded_track_preview, 0.0, 1280.0, bounds), 0.001);
    try std.testing.expectApproxEqAbs(@as(f32, 4.5), laneCenterTargetForMouseX(loaded_track_preview, 640.0, 1280.0, bounds), 0.01);
    try std.testing.expectApproxEqAbs(@as(f32, 2.5), laneCenterTargetForMouseX(loaded_track_preview, 1279.0, 1280.0, bounds), 0.001);
}

test "tutorial startup mouse steering matches the native mirrored authored x axis" {
    var catalog = try assets.Catalog.init(std.testing.allocator, default_archive_path);
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath(default_level_path) orelse return error.EntryNotFound;
    var loaded_level = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer loaded_level.deinit();

    var loaded_track_preview = try track.LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &loaded_level,
        .{ .load_models = false },
    );
    defer loaded_track_preview.deinit();

    var runner = gameplay.Runner.init(&loaded_track_preview);
    runner.refreshBlockedStartupState(&loaded_track_preview);

    const probe_row_position = std.math.clamp(
        runner.row_position + 6.0,
        0.0,
        @max(@as(f32, @floatFromInt(loaded_track_preview.total_rows)) - 0.001, 0.0),
    );
    const probe_global_row = loaded_track_preview.rowIndexAtWorldZ(probe_row_position);
    const row_location = loaded_track_preview.locateRow(probe_global_row) orelse return error.TestUnexpectedResult;
    const bounds = loaded_track_preview.laneBoundsForRow(row_location);
    const left_target = laneCenterTargetForMouseX(loaded_track_preview, 0.0, 1280.0, bounds);
    const right_target = laneCenterTargetForMouseX(loaded_track_preview, 1279.0, 1280.0, bounds);

    try std.testing.expect(left_target > right_target);
}

test "tutorial mouse center maps to the authored track center after startup" {
    var catalog = try assets.Catalog.init(std.testing.allocator, default_archive_path);
    defer catalog.deinit();

    const entry = catalog.dat.entryByPath(default_level_path) orelse return error.EntryNotFound;
    var loaded_level = try level.loadFromArchive(std.testing.allocator, &catalog, entry);
    defer loaded_level.deinit();

    var loaded_track_preview = try track.LoadedLevelPreview.loadWithOptions(
        std.testing.allocator,
        &catalog,
        &loaded_level,
        .{ .load_models = false },
    );
    defer loaded_track_preview.deinit();

    const row_location = loaded_track_preview.locateRow(track.defaultRuntimeActiveRowStart) orelse return error.TestUnexpectedResult;
    const bounds = loaded_track_preview.laneBoundsForRow(row_location);
    try std.testing.expectApproxEqAbs(
        @as(f32, 5.0),
        laneCenterTargetForMouseX(loaded_track_preview, 640.0, 1280.0, bounds),
        0.01,
    );
}
