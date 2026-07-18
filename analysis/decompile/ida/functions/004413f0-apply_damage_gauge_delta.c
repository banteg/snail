/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: apply_damage_gauge_delta @ 0x4413f0 */
/* selector: apply_damage_gauge_delta */

// Applies one signed delta to `Player::damage_gauge` at +0x3c4, clamps the live fill to [0,1], and triggers the matching sound or animation side effects. Unforced deltas are blocked by bit 0x80 of `Player::movement_flags`; state 2 ignores unforced positive deltas and also ignores unforced negative deltas while `Player::trampoline_bounce_active == 1`. Its fallback path changes `Player::presentation.snail_skin`, then dispatches damage animations through the same presentation unless `Player::control_override_active` is set. Windows collision callsites feed this helper with -0.5 health recovery, +0.04 garbage, +0.15 salt, +1.0 slug, and the smaller +0.02 `Wall2` ambient-hazard path. Cross-port iOS symbols match this helper to `cRDamageGuage::Take(float, bool)`.
void __thiscall apply_damage_gauge_delta(DamageGuage *damage_guage, float delta, bool force)
{
  double v4; // st7
  char v6; // c0

  if ( (*((char *)&g_invincible_damage_gate_flags_offset + (_DWORD)g_game_base) >= 0 || force)
    && (damage_guage->state != DAMAGE_GUAGE_STATE_DRAINING
     || delta <= 0.0 && (delta >= 0.0 || g_game_base->subgame.player.trampoline_bounce_active != 1)) )
  {
    if ( damage_guage->hit_flash_progress == 0.0 && delta > 0.0 )
    {
      change_snail_skin(&g_game_base->subgame.player.presentation.snail_skin, 1, 0.2);
      if ( play_voice_manager(&g_voice_manager, 0, 1u, -1) )
      {
        damage_guage->hit_flash_progress = damage_guage->hit_flash_step;
      }
      else
      {
        if ( play_voice_manager(&g_voice_manager, 9, 0, -1) )
          damage_guage->hit_flash_progress = damage_guage->hit_flash_step;
        if ( !g_game_base->subgame.player.control_override_active )
        {
          dispatch_cutscene_animation(&g_game_base->subgame.player.presentation, 6, 1u, -1);
          dispatch_cutscene_animation(&g_game_base->subgame.player.presentation, 1, 0, -1);
        }
      }
    }
    v4 = delta + damage_guage->fill;
    damage_guage->fill = v4;
    if ( v6 )
    {
      damage_guage->fill = 0.0;
    }
    else
    {
      if ( v4 > 1.0 )
        v4 = 1.0;
      damage_guage->fill = v4;
    }
  }
}
