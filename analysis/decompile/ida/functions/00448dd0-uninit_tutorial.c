/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: uninit_tutorial @ 0x448dd0 */
/* selector: uninit_tutorial */

// Exact Windows `Tutorial::uninit_tutorial` thunk that tears down the root tip manager for tutorial-mode exit. Android and iOS retain `cRTutorial::UnInit()`.
void __thiscall uninit_tutorial(Tutorial *tutorial)
{
  uninit_tips(&g_game_base->tip_manager);
}
