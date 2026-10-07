#ifndef SNAIL_PORT_GAME_SESSION_H
#define SNAIL_PORT_GAME_SESSION_H

// The parts of game_startup_and_main_loop (decomp/game/G0/) the shell runs,
// shared by the headless and browser entry points.

// Startup through the first fade-in. `warmup` replaces the original's
// timeGetTime() % 1000 random draws. Returns false with a message on stderr.
bool start_game(int warmup);

// One fixed 1/60 s step: poll input and run cRGame::AI fixed_update_count
// times. `renders` says whether a frame is rendered after this step; the game
// queues text and overlays only then (g_render_queue_active). Returns the
// game's quit code (1-3), or 0 to continue.
int run_fixed_step(bool renders);

// Render the scene and present it, as the loop does when a frame is due.
void render_frame();

// The saves of the loop's shutdown: the high-score tables (ScoreA/B/C.dat)
// and SnailMail.cfg. Progress and options save as they change; scores only
// here, so a host that never quits runs this when the player leaves.
void save_game();

// The audio part of the loop's shutdown (stop_audio_backend,
// shutdown_bass_audio_window), which also deletes the extracted tBass.dll.
void end_game();

#endif
