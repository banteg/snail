/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_active_landscape_entry @ 0x408820 */
/* selector: initialize_active_landscape_entry */

// Constructs one active landscape-entry runtime record by clearing its shared body-list links and installing the landscape-entry update selector. `initialize_runtime_pools_and_path_template_bank` uses it to seed the 10-slot pool later driven by `activate_landscape_entry`.
_DWORD *__thiscall sub_408820(_DWORD *this)
{
  initialize_renderable_bod(this);
  *this = &off_497360;
  return this;
}

