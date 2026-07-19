/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_completion_screen @ 0x406060 */
/* selector: destroy_completion_screen */

// Exact void Windows `Exit::destroy_completion_screen`: tears down the three widgets owned by the root prompt and restores its saved front-end state. Android retains this member as `cRExit::UnInit()`; it is distinct from the embedded subgame `cRCompletion::UnInit()`.
void __thiscall destroy_completion_screen(Exit *exit_controller)
{
  kill_border(&g_game_base->border_manager, exit_controller->prompt_title);
  kill_border(&g_game_base->border_manager, exit_controller->yes_button);
  kill_border(&g_game_base->border_manager, exit_controller->no_button);
  unhide_all_borders(&g_game_base->border_manager);
  g_game_base->players[0].frontend_state = exit_controller->previous_frontend_state;
}
