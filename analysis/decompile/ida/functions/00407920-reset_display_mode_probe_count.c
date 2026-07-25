/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: reset_display_mode_probe_count @ 0x407920 */
/* selector: reset_display_mode_probe_count */

// Clears the display-mode probe count after the main window restores from minimization.
void __thiscall reset_display_mode_probe_count(DisplayModeState *state)
{
  state->probe_count = 0;
}
