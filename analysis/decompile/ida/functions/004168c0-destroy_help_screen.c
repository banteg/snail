/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_help_screen @ 0x4168c0 */
/* selector: destroy_help_screen */

// Clears the Help-screen shell-font scene before control returns to the owning front-end state.
int sub_4168C0()
{
  return kill_all_borders((int *)MEMORY[0x4DF904] + 723);
}

