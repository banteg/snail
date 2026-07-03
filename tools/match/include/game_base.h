// data_4df904: relocatable game-allocation base. Gameplay structures live at
// fixed VA offsets added to it. This is the single canonical extern; keep any
// other view of the same address scratch-local:
// - `extern char* volatile g_game_base` (attachment-entry scratches) when the
//   native per-statement base reload schedule is part of the match
// - typed views (e.g. `AppShell* g_app` in app_shell.h) are the same address
//   under a struct lens; never let a typed view and this decl share one
//   translation unit under the same name
#ifndef GAME_BASE_H
#define GAME_BASE_H

extern char* g_game_base; // data_4df904

#endif
