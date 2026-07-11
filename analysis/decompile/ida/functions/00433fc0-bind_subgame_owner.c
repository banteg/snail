/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: bind_subgame_owner @ 0x433fc0 */
/* selector: bind_subgame_owner */

// Binds a front-end controller's first field to the embedded cRSubGame owner. Startup calls the same folded helper for both ChallengeSetupScreen and ThanksScreen, so this is not a Thanks-only open action.
SubgameRuntime *__thiscall bind_subgame_owner(SubgameOwnerLink *owner)
{
  SubgameRuntime *result; // eax

  result = (SubgameRuntime *)((char *)g_game_base + 476696);
  owner->game = (SubgameRuntime *)((char *)g_game_base + 476696);
  return result;
}
