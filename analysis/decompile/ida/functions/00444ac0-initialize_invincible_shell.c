/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_invincible_shell @ 0x444ac0 */
/* selector: initialize_invincible_shell */

// Authored `cRInvincible::Init()`: resets the exact 0xa4-byte visual owner embedded at `Snail + 0x1894` (`Player + 0x4218`) and restores the normal snail skin.
void __thiscall initialize_invincible_shell(Invincible *invincible)
{
  invincible->state = INVINCIBLE_STATE_INACTIVE;
  change_snail_skin(&g_game_base->subgame.player.presentation.snail_skin, 0, 0.0);
}
