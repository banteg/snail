/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_tutorial @ 0x448da0 */
/* selector: initialize_tutorial */

// Exact Windows `Tutorial::initialize_tutorial`: seeds the embedded 0x1c-byte tutorial owner, borrows its containing SubgameRuntime, and applies the tutorial runtime flags. Android and iOS retain `cRTutorial::Init()`.
void __thiscall initialize_tutorial(Tutorial *tutorial)
{
  SubgameRuntime *p_subgame; // eax
  SubgameRuntime *game; // ecx
  uint32_t runtime_flags; // eax

  tutorial->state = 0;
  p_subgame = &g_game_base->subgame;
  tutorial->game = &g_game_base->subgame;
  p_subgame->runtime_flags |= 0x600000u;
  game = tutorial->game;
  runtime_flags = game->runtime_flags;
  LOBYTE(runtime_flags) = runtime_flags & 0xFD;
  game->runtime_flags = runtime_flags;
}
