/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_invincible_shell @ 0x444b50 */
/* selector: update_invincible_shell */

// Authored `cRInvincible::AI()`: fades the embedded shell visual in while the invincible movement bit stays active, spins it on the shared snail matrix, and fades back to the base skin once invincibility clears.
void __thiscall update_invincible_shell(Invincible *invincible)
{
  double v2; // st7
  double v3; // st7
  double v4; // st7
  unsigned __int8 v6; // c0
  unsigned __int8 v7; // c3
  double spin_phase; // st7
  float angle; // [esp+0h] [ebp-10h]

  switch ( invincible->state )
  {
    case INVINCIBLE_STATE_INACTIVE:
      if ( SLOBYTE(g_game_base->subgame.player.movement_flags) >= 0 )
        g_game_base->subgame.player.presentation.invincible_shell.body.bod.bod.list_flags &= ~0x20u;
      else
        start_invincible_shell(invincible);
      return;
    case INVINCIBLE_STATE_FADING_IN:
      v2 = invincible->fade_step + invincible->fade_progress;
      invincible->fade_progress = v2;
      if ( v2 > 1.0 )
      {
        invincible->fade_progress = 1.0;
        invincible->state = INVINCIBLE_STATE_ACTIVE;
      }
      if ( SLOBYTE(g_game_base->subgame.player.movement_flags) >= 0 )
        invincible->state = INVINCIBLE_STATE_FADING_OUT;
      goto LABEL_15;
    case INVINCIBLE_STATE_ACTIVE:
      if ( SLOBYTE(g_game_base->subgame.player.movement_flags) >= 0 )
        invincible->state = INVINCIBLE_STATE_FADING_OUT;
      goto LABEL_15;
    case INVINCIBLE_STATE_FADING_OUT:
      v3 = invincible->fade_progress - invincible->fade_step;
      invincible->fade_progress = v3;
      if ( v3 >= 0.0 )
      {
        if ( SLOBYTE(g_game_base->subgame.player.movement_flags) < 0 )
          invincible->state = INVINCIBLE_STATE_FADING_IN;
LABEL_15:
        v4 = invincible->spin_phase_step + invincible->spin_phase;
        invincible->spin_phase = v4;
        if ( !(v6 | v7) )
          invincible->spin_phase = v4 - 1.0;
        change_snail_skin(&g_game_base->subgame.player.presentation.snail_skin, 2, 0.0);
        set_color_white(&invincible->body.bod.color);
        invincible->body.bod.color.a = invincible->fade_progress * 0.80000001;
        spin_phase = invincible->spin_phase;
        qmemcpy(
          &invincible->body.transform,
          &g_game_base->subgame.player.presentation.body.transform,
          sizeof(invincible->body.transform));
        angle = spin_phase * 6.2831855;
        rotate_matrix_local_y(&invincible->body.transform, angle);
      }
      else
      {
        invincible->fade_progress = 0.0;
        invincible->state = INVINCIBLE_STATE_INACTIVE;
        change_snail_skin(&g_game_base->subgame.player.presentation.snail_skin, 0, 0.0);
      }
      return;
    default:
      goto LABEL_15;
  }
}
