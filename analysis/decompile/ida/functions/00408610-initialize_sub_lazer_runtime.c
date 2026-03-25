/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_sub_lazer_runtime @ 0x408610 */
/* selector: initialize_sub_lazer_runtime */

// Constructs one laser-projectile runtime slot by running the shared renderable-body constructor and installing the laser vtable. The 20-slot pool built by `initialize_runtime_pools_and_path_template_bank` totals `0xdc0`, matching the native `cRSubLazerManager` size ledger.
_DWORD *__thiscall sub_408610(_DWORD *this)
{
  initialize_renderable_bod(this);
  *this = &off_49733C;
  return this;
}

