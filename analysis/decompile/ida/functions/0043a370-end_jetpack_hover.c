/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: end_jetpack_hover @ 0x43a370 */
/* selector: end_jetpack_hover */

// Exact Windows `SubHover::end_jetpack_hover`, authored as `cRSubHover::End`: while the exact 0x214-byte owner is active, clamps progress to the 0.94 teardown threshold.
void __thiscall end_jetpack_hover(SubHover *sub_hover)
{
  if ( sub_hover->state == SUB_HOVER_STATE_ACTIVE && sub_hover->progress < 0.94 )
    sub_hover->progress = 0.94;
}
