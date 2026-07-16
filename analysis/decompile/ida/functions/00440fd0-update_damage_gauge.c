/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_damage_gauge @ 0x440fd0 */
/* selector: update_damage_gauge */

// Advances the player contact-damage gauge controller at +0x3c4, smoothing its displayed fill, driving the warning or drain presentation, rendering the sprite-backed gauge widget, and applying state-2 drain. Native global gates now recovered here include the suspend byte `Game+0x74621`, warning-start blockers `Game+0x430199`/`Game+0x4301bc`, the `Game+0x42fde8 == 0.49f` drain transition gate, and state-2 exit gates `Game+0x4301c0`, `Game+0x42fe08`, and `Game+0x434064`; some writers remain unresolved. Android and iOS preserve this exact owner role as `cRDamageGuage::AI()`.
void __thiscall update_damage_gauge(DamageGuage *damage_guage)
{
  GameRoot *v2; // ecx
  double v3; // st7
  double v4; // st7
  tColour *v5; // eax
  tColour *v6; // eax
  tColour *v7; // eax
  float y; // [esp+0h] [ebp-48h]
  float v9; // [esp+8h] [ebp-40h]
  float v10; // [esp+28h] [ebp-20h]
  float a; // [esp+30h] [ebp-18h]
  float aa; // [esp+30h] [ebp-18h]
  float ab; // [esp+30h] [ebp-18h]
  float height; // [esp+34h] [ebp-14h]
  Color4f color; // [esp+38h] [ebp-10h] BYREF

  v2 = g_game_base;
  if ( g_game_base->subgame.subgame_pause_gate )
    goto LABEL_26;
  damage_guage->display_fill = (damage_guage->fill - damage_guage->display_fill) * 0.2 + damage_guage->display_fill;
  if ( damage_guage->hit_flash_progress > 0.0 )
  {
    v3 = damage_guage->hit_flash_step + damage_guage->hit_flash_progress;
    damage_guage->hit_flash_progress = v3;
    if ( v3 > 1.0 )
      damage_guage->hit_flash_progress = 0.0;
  }
  if ( damage_guage->state == DAMAGE_GUAGE_STATE_MONITORING )
  {
    if ( LODWORD(damage_guage->fill) == 1065353216 )
    {
      v2 = g_game_base;
      if ( *((_BYTE *)&g_player_attachment_exit_pending_offset + (_DWORD)g_game_base)
        || *((_BYTE *)&g_follow_force_drain_offset + (_DWORD)g_game_base) )
      {
        goto LABEL_26;
      }
      damage_guage->state = DAMAGE_GUAGE_STATE_WARNING_TRANSITION;
      damage_guage->warning_transition_progress = 0.0;
      damage_guage->warning_transition_step = 0.16666667;
      start_warning(&g_game_base->subgame.player.warning);
    }
    goto LABEL_25;
  }
  if ( damage_guage->state == DAMAGE_GUAGE_STATE_WARNING_TRANSITION )
  {
    if ( *((_BYTE *)&g_follow_force_drain_offset + (_DWORD)g_game_base) )
      damage_guage->warning_transition_progress = 1.0;
    v4 = damage_guage->warning_transition_step + damage_guage->warning_transition_progress;
    damage_guage->warning_transition_progress = v4;
    if ( v4 >= 1.0 )
    {
      v2 = g_game_base;
      if ( LODWORD(g_game_base->subgame.player.body.transform.position.y) != 1056629064 )
        goto LABEL_26;
      damage_guage->state = DAMAGE_GUAGE_STATE_DRAINING;
      play_voice_manager((int)g_voice_manager, 14, 0, -1);
    }
    goto LABEL_25;
  }
  if ( damage_guage->state != DAMAGE_GUAGE_STATE_DRAINING )
  {
LABEL_25:
    v2 = g_game_base;
    goto LABEL_26;
  }
  change_snail_skin(&g_game_base->subgame.player.presentation.snail_skin, 1, 0.2);
  apply_damage_gauge_delta(damage_guage, -0.0016666667, 1);
  damage_guage->skin_hold_ticks = 5;
  v2 = g_game_base;
  if ( *((_BYTE *)&g_follow_force_drain_offset + (_DWORD)g_game_base) )
  {
    apply_damage_gauge_delta(damage_guage, -0.0066666668, 0);
    v2 = g_game_base;
  }
  if ( damage_guage->fill == 0.0 && LODWORD(v2->subgame.player.body.transform.position.y) == 1056629064
    || v2->subgame.player.completion_handoff_timer > 0.0
    || v2->subgame.player.resurrect_progress > 0.0
    || v2->subgame.player.presentation.cutscene.state )
  {
    damage_guage->state = DAMAGE_GUAGE_STATE_MONITORING;
    stop_warning(&g_game_base->subgame.player.warning);
    stop_warning_sample();
    goto LABEL_25;
  }
LABEL_26:
  if ( damage_guage->display_fill <= 0.99900001 )
  {
    if ( damage_guage->display_fill >= 0.0099999998 )
      height = 351.0 - damage_guage->display_fill * 308.0;
    else
      height = 396.0;
  }
  else
  {
    height = 0.0;
  }
  if ( !v2->subgame.subgame_pause_gate )
    damage_guage->pulse_progress = damage_guage->pulse_step + damage_guage->pulse_progress;
  if ( damage_guage->pulse_progress > 1.0 )
    damage_guage->pulse_progress = damage_guage->pulse_progress - 1.0;
  if ( damage_guage->display_fill > 0.89999998 || damage_guage->state )
  {
    if ( damage_guage->display_fill <= 0.89999998 )
    {
      if ( damage_guage->display_fill < 0.1 )
      {
        a = damage_guage->display_fill * 10.0;
        goto LABEL_43;
      }
    }
    else if ( damage_guage->state == DAMAGE_GUAGE_STATE_MONITORING )
    {
      a = (damage_guage->display_fill - 0.89999998) * 10.0;
LABEL_43:
      v10 = damage_guage->pulse_progress * 6.2831855;
      aa = a - (sine(v10) + 1.0) * 0.5 * a * 0.5;
      v5 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, aa);
      queue_axis_aligned_textured_quad_uv(
        91,
        560.0,
        70.0,
        64.0,
        396.0,
        0x1000000u,
        v5,
        0.0,
        0.0,
        1.0,
        0.7734375,
        3,
        0.0);
      goto LABEL_44;
    }
    a = 1.0;
    goto LABEL_43;
  }
LABEL_44:
  ab = height * 0.001953125;
  v6 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  queue_axis_aligned_textured_quad_uv(89, 560.0, 70.0, 64.0, height, 0x1000000u, v6, 0.0, 0.0, 1.0, ab, 3, 0.0);
  v7 = set_color_rgba((tColour *)&color, 1.0, 1.0, 1.0, 1.0);
  v9 = 396.0 - height;
  y = height + 70.0;
  queue_axis_aligned_textured_quad_uv(90, 560.0, y, 64.0, v9, 0x1000000u, v7, 0.0, ab, 1.0, 0.7734375, 3, 0.0);
}
