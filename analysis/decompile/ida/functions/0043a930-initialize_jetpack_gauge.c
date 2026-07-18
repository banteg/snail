/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_jetpack_gauge @ 0x43a930 */
/* selector: initialize_jetpack_gauge */

// Exact Windows `SubHover::initialize_jetpack_gauge`, authored as `cRSubHover::Init`: clears the 0x214-byte child state, seeds its 1/600 progress step, and stores borrowed SubgameRuntime and Player backlinks. The authored contract is void; the Windows integer parameter is unused.
void __thiscall initialize_jetpack_gauge(SubHover *sub_hover, int32_t player_slot)
{
  SubgameRuntime *p_subgame; // edx
  struct Player *p_player; // edx

  sub_hover->progress = 0.0;
  p_subgame = &g_game_base->subgame;
  sub_hover->progress_step = 0.0016666667;
  sub_hover->game = p_subgame;
  p_player = &g_game_base->subgame.player;
  sub_hover->state = SUB_HOVER_STATE_INACTIVE;
  sub_hover->player = p_player;
  sub_hover->wobble_alpha = 0.0;
  sub_hover->wobble_y = 0.0;
  sub_hover->wobble_x = 0.0;
  sub_hover->warning_intensity_latch = 0.0;
}
