/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: bind_subgame_owner @ 0x433fc0 */
/* selector: bind_subgame_owner */

// Binds a front-end controller’s first field to the embedded cRSubGame owner. For the 0x28-byte GUI receiver this is `cRGUI::Open()`; Windows folds the identical one-store body with the ThanksScreen owner-binding callsite.
SubgameRuntime *__thiscall bind_subgame_owner(SubgameOwnerLink *owner)
{
  SubgameRuntime *result; // eax

  result = &g_game_base->subgame;
  owner->game = &g_game_base->subgame;
  return result;
}
