/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_subgoldy_resurrect @ 0x441fa0 */
/* selector: initialize_subgoldy_resurrect */

// Void `Player` member that seeds Goldy's resurrect state machine by storing the respawn-or-final-loss selector, enabling the resurrect-active flag, and resetting the shared fade timer. `initialize_subgoldy_death` tail-forwards into it, but both external death callers discard the selector residue. Cross-port Android and iOS symbols match this helper to `cRSubGoldy::RessurectInit(int)`.
void __thiscall initialize_subgoldy_resurrect(Player *player, int32_t final_loss)
{
  LOBYTE(player->resurrect_active) = 1;
  player->resurrect_final_loss = final_loss;
  player->resurrect_progress = 0.0;
  player->resurrect_progress_step = 0.0083333338;
}
