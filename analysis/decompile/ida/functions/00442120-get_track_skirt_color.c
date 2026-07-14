/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_track_skirt_color @ 0x442120 */
/* selector: get_track_skirt_color */

// Builds the shared RGBA skirt or fringe colour from the current track colour scalars and a fixed alpha, then copies it into one runtime row or fringe object. Cross-port Android symbols match this helper to `cRSubGame::GetSkirtColour(tColourSmall)`.
tColour *__thiscall get_track_skirt_color(SubgameRuntime *game, tColour *out)
{
  struct tColour color; // [esp+4h] [ebp-10h] BYREF

  *out = *set_color_rgba(
            &color,
            game->level_definition.fringe_color.r,
            game->level_definition.fringe_color.g,
            game->level_definition.fringe_color.b,
            0.40000001);
  return out;
}

