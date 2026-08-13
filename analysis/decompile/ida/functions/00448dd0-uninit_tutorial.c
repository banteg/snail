/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: uninit_tutorial @ 0x448dd0 */
/* selector: uninit_tutorial */

// Exact Windows `cRTutorial::UnInit()` thunk that tears down the root tip manager for tutorial-mode exit. Android and iOS retain the same owner and method.
void __thiscall uninit_tutorial(cRTutorial *tutorial)
{
  uninit_tips(&g_game_base->tip_manager);
}
