/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: arm_jetpack_gauge @ 0x43a980 */
/* selector: arm_jetpack_gauge */

// Exact Windows `SubHover::arm_jetpack_gauge`, authored as `cRSubHover::On`: arms the child at Player +0x2750, clears progress and wobble, selects the snail jetpack visual, and calls JetInit. The authored contract is void.
void __thiscall arm_jetpack_gauge(SubHover *sub_hover)
{
  if ( sub_hover->state == SUB_HOVER_STATE_INACTIVE )
  {
    sub_hover->state = SUB_HOVER_STATE_ACTIVE;
    sub_hover->progress = 0.0;
    sub_hover->wobble_alpha = 0.0;
    sub_hover->wobble_y = 0.0;
    sub_hover->wobble_x = 0.0;
    set_snail_jetpack(&g_game_base->subgame.player.presentation, 1);
    initialize_jet_particles(sub_hover);
  }
}
