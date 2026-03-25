/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_backdrop_progress_fraction @ 0x410c30 */
/* selector: set_backdrop_progress_fraction */

// Stores one normalized progress fraction on the active backdrop controller. Windows `update_subgoldy` drives it from the current track-row payload ratio, and `initialize_backdrop` clears the same field at +0x6c8.
int __thiscall sub_410C30(_DWORD *this, int a2)
{
  *(this + 434) = a2;
  return a2;
}

