/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_jetpack_gauge @ 0x43a390 */
/* selector: update_jetpack_gauge */

// Windows `SubHover::update_jetpack_gauge`, authored as `cRSubHover::AI`: advances the hover countdown/warning envelope, applies runtime-row auto-shutoff, drives wobble and the authored Hover call, and clears the exact 0x214-byte owner at teardown.
void __thiscall update_jetpack_gauge(SubHover *sub_hover)
{
  double v3; // st7
  char v4; // c0
  double v5; // st7
  float warning_intensity; // eax
  Vec4 *p_position; // [esp-4h] [ebp-18h]
  float v8; // [esp+0h] [ebp-14h]
  float v9; // [esp+0h] [ebp-14h]
  float v10; // [esp+0h] [ebp-14h]
  int progress_low; // [esp+0h] [ebp-14h]
  float v12; // [esp+Ch] [ebp-8h]

  if ( sub_hover->state == SUB_HOVER_STATE_ACTIVE )
  {
    v12 = sub_hover->progress_step + sub_hover->progress;
    sub_hover->progress = v12;
    if ( v12 > 1.0 || (double)(sub_hover->game->completion_row_start - 5) < sub_hover->player->body.transform.position.z )
    {
      end_jetpack_hover(sub_hover);
      if ( sub_hover->progress <= 0.94 )
        set_snail_jetpack(&g_game_base->subgame.player.presentation, 0);
      sub_hover->state = SUB_HOVER_STATE_INACTIVE;
      sub_hover->wobble_alpha = 0.0;
      sub_hover->wobble_y = 0.0;
      sub_hover->wobble_x = 0.0;
    }
    else
    {
      v3 = v12;
      if ( v4 )
      {
        sub_hover->warning_intensity = v3 * 10.0;
      }
      else if ( v3 <= 0.94 )
      {
        sub_hover->warning_intensity = 1.0;
        if ( (BYTE1(get_track_runtime_cell_at_world_z(
                      &g_game_base->subgame,
                      (Vec3 *)&g_game_base->subgame.player.body.transform.position)->flags)
            & 0x80u) != 0 )
        {
          sub_hover->progress = 0.94;
          debug_report_stub();
        }
      }
      else
      {
        sub_hover->warning_intensity = (1.0 - v12) * 16.666668;
        if ( v12 - sub_hover->progress_step <= 0.94 )
        {
          set_snail_jetpack(&g_game_base->subgame.player.presentation, 0);
          uninit_jet_particles(sub_hover);
        }
      }
      v8 = sub_hover->warning_intensity * 3.1415927;
      sub_hover->warning_intensity = 1.0 - (cosine(v8) + 1.0) * 0.5;
      v9 = sub_hover->progress * 25.132742;
      sub_hover->wobble_x = sine(v9) * sub_hover->warning_intensity * 0.25;
      v10 = sub_hover->progress * 37.699112;
      v5 = sine(v10);
      warning_intensity = sub_hover->warning_intensity;
      progress_low = LODWORD(sub_hover->progress);
      p_position = &sub_hover->player->body.transform.position;
      sub_hover->wobble_alpha = 0.0;
      sub_hover->warning_intensity_latch = warning_intensity;
      sub_hover->wobble_y = (v5 * 0.25 + 1.0) * warning_intensity;
      spawn_track_speedup((int)p_position, progress_low);
    }
  }
}
