/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_invincible_shell @ 0x444ac0 */
/* selector: initialize_invincible_shell */

// Resets the runner-owned invincible-shell controller at `player + 0x4218` and restores the normal snail-skin state before gameplay starts.
void __thiscall sub_444AC0(_DWORD *this)
{
  *(this + 32) = 0;
  change_snail_skin((float *)MEMORY[0x4DF904] + 1101838, 0, 0.0);
}

