const app = @import("../app.zig");
const background = @import("../background.zig");

pub const default_model_path = app.default_model_path;
pub const default_object_path = app.default_object_path;
pub const gameplay_turbo_talk_model_path = "X/TURBO-TALK-000.X2";
pub const gameplay_turbo_into_shell_model_path = "X/TURBO-INTOSHELL-000.X2";
pub const gameplay_barrier_object_path = "OBJECTS/BARRIER/_OBJECT.TXT";
pub const gameplay_lazer_object_path = "OBJECTS/LAZER/_OBJECT.TXT";
pub const gameplay_vapour_lazer_object_path = "OBJECTS/VAPOURLAZER/_OBJECT.TXT";
pub const gameplay_salt_model_path = "X/SALT.X2";
pub const gameplay_wall2_pillar_model_paths = [_][]const u8{
    "X/PILLAR1.X2",
    "X/PILLAR2.X2",
    "X/PILLAR3.X2",
    "X/PILLAR4.X2",
    "X/PILLAR5.X2",
    "X/PILLAR6.X2",
    "X/PILLAR7.X2",
    "X/PILLAR8.X2",
};
pub const gameplay_blaster_top_model_path = "X/BLASTERTOP-BASE-000.X2";
pub const gameplay_blaster_top_draw_model_paths = [_][]const u8{
    "X/BLASTERTOP-DRAW-000.X2",
    "X/BLASTERTOP-DRAW-001.X2",
    "X/BLASTERTOP-DRAW-002.X2",
    "X/BLASTERTOP-DRAW-003.X2",
    "X/BLASTERTOP-DRAW-004.X2",
    "X/BLASTERTOP-DRAW-005.X2",
};
pub const gameplay_blaster_top_fire_model_path = "X/BLASTERTOP-FIRE-000.X2";
pub const gameplay_blaster_left_model_path = "X/BLASTERLEFT-BASE-000.X2";
pub const gameplay_blaster_left_draw_model_paths = [_][]const u8{
    "X/BLASTERLEFT-DRAW-000.X2",
    "X/BLASTERLEFT-DRAW-001.X2",
    "X/BLASTERLEFT-DRAW-002.X2",
    "X/BLASTERLEFT-DRAW-003.X2",
    "X/BLASTERLEFT-DRAW-004.X2",
    "X/BLASTERLEFT-DRAW-005.X2",
};
pub const gameplay_blaster_right_model_path = "X/BLASTERRIGHT-BASE-000.X2";
pub const gameplay_blaster_right_draw_model_paths = [_][]const u8{
    "X/BLASTERRIGHT-DRAW-000.X2",
    "X/BLASTERRIGHT-DRAW-001.X2",
    "X/BLASTERRIGHT-DRAW-002.X2",
    "X/BLASTERRIGHT-DRAW-003.X2",
    "X/BLASTERRIGHT-DRAW-004.X2",
    "X/BLASTERRIGHT-DRAW-005.X2",
};
pub const gameplay_laser_left_model_path = "X/LASERLEFT-BASE-000.X2";
pub const gameplay_laser_left_draw_model_paths = [_][]const u8{
    "X/LASERLEFT-DRAW-000.X2",
    "X/LASERLEFT-DRAW-001.X2",
    "X/LASERLEFT-DRAW-002.X2",
    "X/LASERLEFT-DRAW-003.X2",
};
pub const gameplay_laser_right_model_path = "X/LASERRIGHT-BASE-000.X2";
pub const gameplay_laser_right_draw_model_paths = [_][]const u8{
    "X/LASERRIGHT-DRAW-000.X2",
    "X/LASERRIGHT-DRAW-001.X2",
    "X/LASERRIGHT-DRAW-002.X2",
    "X/LASERRIGHT-DRAW-003.X2",
};
pub const gameplay_rocket_launcher_model_path = "X/ROCKETLAUNCHER-BASE-000.X2";
pub const gameplay_rocket_launcher_draw_model_paths = [_][]const u8{
    "X/ROCKETLAUNCHER-DRAW-000.X2",
    "X/ROCKETLAUNCHER-DRAW-001.X2",
    "X/ROCKETLAUNCHER-DRAW-002.X2",
};
pub const gameplay_rocket_model_path = "X/ROCKET-BASE-000.X2";
pub const gameplay_post_office_stop_model_path = "X/POSTOFFICESTOP.X2";
pub const gameplay_jetpack_thrust_model_paths = [_][]const u8{
    "X/JETPACKTHRUST-BASE-000.X2",
    "X/JETPACKTHRUST-BASE-001.X2",
    "X/JETPACKTHRUST-BASE-002.X2",
};
pub const gameplay_invincible_model_paths = [_][]const u8{
    "X/INVINCIBLE-BASE-000.X2",
    "X/INVINCIBLE-BASE-001.X2",
    "X/INVINCIBLE-BASE-002.X2",
    "X/INVINCIBLE-BASE-003.X2",
};
pub const gameplay_slug_sprite_paths = [_][]const u8{
    "SPRITES/SLUG000.TGA",
    "SPRITES/SLUG001.TGA",
};
pub const gameplay_ghost_sprite_path = "SPRITES/GHOST.TGA";
pub const gameplay_garbage_sprite_paths = [_][]const u8{
    "SPRITES/GARBAGEA.TGA",
    "SPRITES/GARBAGEB.TGA",
    "SPRITES/GARBAGEC.TGA",
    "SPRITES/GARBAGED.TGA",
};
pub const gameplay_health_sprite_path = "SPRITES/HEALTH.TGA";
pub const gameplay_jetpack_sprite_paths = [_][]const u8{
    "SPRITES/JETPACK000.TGA",
    "SPRITES/JETPACK001.TGA",
};
pub const gameplay_parcel_sprite_path = "SPRITES/PARCEL000.TGA";
pub const gameplay_ring_sprite_path = "SPRITES/PARTICLERING-SMALL.TGA";
pub const gameplay_ring_big_sprite_path = "SPRITES/PARTICLERING-BIG.TGA";
pub const gameplay_slow_ring_sprite_path = "SPRITES/PARTICLESLOW-SMALL.TGA";
pub const gameplay_powerup_sprite_path = "SPRITES/PARTICLEBLASTERS.TGA";
pub const gameplay_life_sprite_path = "SPRITES/LIFE.TGA";
pub const gameplay_progress_bar_sprite_path = "SPRITES/PROGRESS-BAR.TGA";
pub const gameplay_progress_bar_lit_sprite_path = "SPRITES/PROGRESS-BAR-LIT.TGA";
pub const gameplay_progress_cursor_sprite_path = "SPRITES/PROGRESS-CURSOR.TGA";
pub const gameplay_damage_gauge_sprite_path = "SPRITES/DAMAGEGUAGE.TGA";
pub const gameplay_damage_gauge_full_sprite_path = "SPRITES/DAMAGEGUAGEFULL.TGA";
pub const gameplay_damage_gauge_bright_sprite_path = "SPRITES/DAMAGEGUAGEBRIGHT.TGA";
pub const gameplay_warning_sprite_path = "SPRITES/WARNING.TGA";
pub const gameplay_explode_big_sprite_path = "SPRITES/PARTICLEEXPLODE-BIG.TGA";
pub const gameplay_explode_small_sprite_path = "SPRITES/PARTICLEEXPLODE-SMALL.TGA";
pub const gameplay_slug_goo_sprite_path = "SPRITES/SLUGGOO.TGA";
pub const gameplay_smoke_sprite_path = "SPRITES/SMOKE.TGA";
pub const background_light_streak_sprite_path = background.light_streak_sprite_path;
pub const gameplay_turbo_fire_sound_paths = [_][]const u8{
    "SFX2/TURBOFIRE1.OGG",
    "SFX2/TURBOFIRE2.OGG",
};
pub const gameplay_laser_sound_paths = [_][]const u8{
    "SFX2/LASER1.OGG",
    "SFX2/LASER2.OGG",
    "SFX2/LASER3.OGG",
};
pub const gameplay_rocket_sound_paths = [_][]const u8{
    "SFX2/ROCKET1.OGG",
    "SFX2/ROCKET2.OGG",
    "SFX2/ROCKET3.OGG",
};
pub const gameplay_heart_sound_path = "SFX2/HEART.OGG";
pub const gameplay_jetpack_sound_path = "SFX2/JETPACK.OGG";
pub const gameplay_jetpack_shutoff_sound_path = "SFX2/SERVO2.OGG";
pub const gameplay_slow_ring_sound_path = "SFX2/SLOWRING.OGG";
pub const gameplay_invincible_sound_path = "SFX2/INVINCIBLE.OGG";
pub const gameplay_explode_ring_sound_path = "SFX2/EXPLODERING.OGG";
pub const gameplay_enemy_fire_sound_path = "SFX2/ENEMYFIRE.OGG";
pub const gameplay_boing_sound_path = "SFX2/BOING.OGG";
pub const gameplay_completion_init_sound_path = "SFX2/SKIDSTOP.OGG";
pub const gameplay_row_event_confirm_sound_path = "SFX2/SELECT.OGG";
pub const gameplay_place_package_sound_path = "SFX2/PLACEPACKAGE.OGG";
pub const gameplay_package_count_sound_path = "SFX2/PACKAGECOUNT.OGG";
pub const gameplay_perfect_sound_path = "SFX2/PERFECT.OGG";
pub const gameplay_powerup_pickup_sound_paths = [_][]const u8{
    "SFX2/PW1.OGG",
    "SFX2/PW2.OGG",
    "SFX2/PW3.OGG",
    "SFX2/PW4.OGG",
    "SFX2/PW5.OGG",
    "SFX2/PW6.OGG",
    "SFX2/PW7.OGG",
};
pub const native_jetpack_visual_shutoff_threshold: f32 = 0.94;
pub const gameplay_asteroid_impact_sound_paths = [_][]const u8{
    "SFX2/ASTEROIDIMPACT1.OGG",
    "SFX2/ASTEROIDIMPACT2.OGG",
};
pub const gameplay_wall_hit_sound_path = "SFX2/WALLHIT.OGG";
pub const gameplay_slug_hit_voice_paths = [_][]const u8{
    "VOICE/SLUG-HIT1.OGG",
    "VOICE/SLUG-HIT2.OGG",
    "VOICE/SLUG-HIT3.OGG",
};
pub const gameplay_slug_ambient_voice_paths = [_][]const u8{
    "VOICE/SLUG-DESTROY.OGG",
    "VOICE/SLUG-GOTHIM.OGG",
    "VOICE/SLUG-HESTOOFAST.OGG",
    "VOICE/SLUG-SNAILALERT.OGG",
};
pub const gameplay_slug_death_voice_paths = [_][]const u8{
    "VOICE/SLUG-DEATH1.OGG",
    "VOICE/SLUG-DEATH2.OGG",
};
pub const gameplay_native_voice_damage_paths = [_][]const u8{
    "VOICE/HEYIJUSTWAXED.OGG",
    "VOICE/IMGONNANEEDANEWSHELL.OGG",
    "VOICE/ITBURNS.OGG",
    "VOICE/MYEYES.OGG",
    "VOICE/THATSGONNALEAVEAMARK.OGG",
    "VOICE/UHOH.OGG",
};
pub const gameplay_native_voice_dying_paths = [_][]const u8{
    "VOICE/ABANDONSHELL.OGG",
    "VOICE/IMFALLINGANDICANTGETUP.OGG",
    "VOICE/INEEDANEWJOB.OGG",
    "VOICE/NOTCOOL.OGG",
    "VOICE/THISISNOTMYDAY.OGG",
};
pub const gameplay_native_voice_slugged_paths = [_][]const u8{
    "VOICE/INEEDANEWJOB.OGG",
    "VOICE/NOTCOOL.OGG",
    "VOICE/THISISNOTMYDAY.OGG",
};
pub const gameplay_native_voice_enemies_paths = [_][]const u8{
    "VOICE/ALWAYSTIPYOURMAILCARRIER.OGG",
    "VOICE/ALWAYSTIPYOURPOSTALWORKER.OGG",
    "VOICE/BACKOFF.OGG",
    "VOICE/BACKOFFSLUGS.OGG",
    "VOICE/COMINGTHROUGH.OGG",
    "VOICE/MAKEWAY.OGG",
};
pub const gameplay_native_voice_fall_paths = [_][]const u8{
    "VOICE/FALL1.OGG",
    "VOICE/FALL2.OGG",
    "VOICE/FALL3.OGG",
};
pub const gameplay_native_voice_misc_paths = [_][]const u8{
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
pub const gameplay_native_voice_victory_paths = [_][]const u8{
    "VOICE/HOWSTHATFOREXPRESSSERVICE.OGG",
    "VOICE/IDESERVEAPROMOTION.OGG",
    "VOICE/IDESERVEARAISE.OGG",
    "VOICE/IGOTAHOTFOOT.OGG",
    "VOICE/IMTHESNAIL.OGG",
    "VOICE/ONTIMEANDFEELINGFINE.OGG",
    "VOICE/SOMEBODYPINCHME.OGG",
};
pub const gameplay_native_voice_ouch_paths = [_][]const u8{
    "VOICE/OW1.OGG",
    "VOICE/OW2.OGG",
    "VOICE/OW3.OGG",
    "VOICE/OW4.OGG",
};
pub const gameplay_native_voice_worm_tunnel_paths = [_][]const u8{
    "VOICE/WHOAHDUDE.OGG",
    "VOICE/ZIPPIDYDOODAH.OGG",
    "VOICE/WHOHOHOHOAH.OGG",
};
pub const gameplay_native_voice_supertramp_paths = [_][]const u8{
    "VOICE/WHOAHDUDE.OGG",
    "VOICE/WOOHOO.OGG",
    "VOICE/WHOHOHOHOAH.OGG",
};
pub const gameplay_native_voice_package_paths = [_][]const u8{
    "VOICE/POSTAGEDUE.OGG",
    "VOICE/SOMEBODYCALLFORADELIVERY.OGG",
    "VOICE/SPECIALDELIVERY.OGG",
    "VOICE/SPEEDYDELIVERY.OGG",
};
pub const gameplay_native_voice_powerup_paths = [_][]const u8{
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
pub const gameplay_native_voice_slow_paths = [_][]const u8{
    "VOICE/AMIEVENMOVING.OGG",
    "VOICE/ANYSLOWER.OGG",
    "VOICE/COMEON.OGG",
    "VOICE/FASTERISBETTER.OGG",
    "VOICE/ICANDOBETTER.OGG",
    "VOICE/FASTERWOULDBEBETTER.OGG",
    "VOICE/ISLEEPFASTERTHANTHIS.OGG",
};
pub const gameplay_native_voice_start_paths = [_][]const u8{
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
pub const gameplay_native_voice_tutorial_paths = [_][]const u8{
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
pub const gameplay_native_voice_postal_paths = [_][]const u8{
    "VOICE/IMGOINGPOSTAL.OGG",
    "VOICE/IMGOINGPOSTAL2.OGG",
    "VOICE/IMGOINGPOSTAL3.OGG",
};
pub const gameplay_cheers_sound_path = "SFX2/CHEERS.OGG";
pub const gameplay_extra_life_sound_path = "SFX2/EXTRALIFE.OGG";
pub const gameplay_weapon_change_sound_path = "SFX2/SERVO1.OGG";
pub const gameplay_postal_warning_sound_path = "SFX2/POSTALLOOP.OGG";
pub const native_gameplay_slow_voice_timer_step: f32 = 1.0 / 60.0;
pub const native_gameplay_start_voice_tick: u64 = 18;
