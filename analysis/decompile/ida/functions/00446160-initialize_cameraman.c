/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_cameraman @ 0x446160 */
/* selector: initialize_cameraman */

// Initializes the exact 0xd8-byte cRCameraman embedded in Player at +0x200, wiring its Player and SubgameRuntime backlinks, resetting all three matrices and both lift envelopes, and seeding the 110-degree FOV. Android and iOS retain this method as `cRCameraman::Init()`.
void __thiscall initialize_cameraman(Cameraman *cameraman)
{
  SubgameRuntime *p_subgame; // ecx

  cameraman->player = (Player *)((char *)&g_player_block + (_DWORD)g_game_base);
  p_subgame = &g_game_base->subgame;
  cameraman->force_camera_update = 0;
  cameraman->game = p_subgame;
  set_matrix_identity(&cameraman->previous_desired_matrix);
  set_matrix_identity(&cameraman->desired_matrix);
  set_matrix_identity(&cameraman->live_matrix);
  cameraman->attachment_lift_envelope = 0.0;
  cameraman->smoothed_attachment_lift_envelope = 0.0;
  cameraman->fov_degrees = 110.0;
}
