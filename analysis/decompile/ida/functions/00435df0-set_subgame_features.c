/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_subgame_features @ 0x435df0 */
/* selector: set_subgame_features */

// Derives the active subgame feature flags from the current mode, level, and challenge setup before runtime rows and pickups are built. Cross-port iOS symbols match this helper to `cRSubGame::SetFeatures()` in `SubGame.o`.
int32_t __thiscall set_subgame_features(SubgameRuntime *runtime)
{
  int32_t result; // eax

  if ( runtime->selected_level_record_active )
  {
    result = (int32_t)runtime->selected_level_record;
    runtime->runtime_flags = *(_DWORD *)(result + 56);
  }
  else
  {
    result = runtime->level_mode;
    runtime->runtime_flags = 1156;
    runtime->runtime_flags = (uint32_t)&unk_600484;
    switch ( result )
    {
      case 0:
      case 1:
        runtime->runtime_flags = 16109567;
        break;
      case 4:
        runtime->runtime_flags = (uint32_t)&g_font_queue[269].v0 + 3;
        break;
      case 7:
        runtime->runtime_flags = 14995455;
        break;
      default:
        return result;
    }
  }
  return result;
}
