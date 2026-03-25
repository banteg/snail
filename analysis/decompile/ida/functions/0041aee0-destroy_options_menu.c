/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: destroy_options_menu @ 0x41aee0 */
/* selector: destroy_options_menu */

// Tears down the Options-screen widgets and writes the current SnailMail.cfg blob back to disk. Cross-port Android and iOS symbols match this helper to `cROptions::UnInit()`.
char *__thiscall destroy_options(_DWORD **this)
{
  unhide_all_borders((int *)MEMORY[0x4DF904] + 723);
  kill_border(*(this + 4));
  kill_border(*(this + 7));
  kill_border(*(this + 6));
  kill_border(*(this + 5));
  return (char *)save_config_file(aSnailmailCfg, &unk_4DF918, 196);
}

