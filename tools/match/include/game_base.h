// data_4df904: relocatable game-allocation base. Gameplay structures live at
// fixed VA offsets added to it. This is the single canonical extern; keep any
// other view of the same address scratch-local. Repeated native reloads remain
// honest scheduling debt; do not add volatile solely to reproduce them.
// Typed `GameRoot* g_game` views are the same address under the canonical root
// owner; never let a typed view and this raw declaration share one translation
// unit under the same name.
#ifndef GAME_BASE_H
#define GAME_BASE_H

extern char* g_game_base; // data_4df904

#endif
