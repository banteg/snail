/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_salt_hazard_runtime @ 0x408630 */
/* selector: initialize_salt_hazard_runtime */

// Constructs one salt-hazard runtime slot by running the shared body constructor and installing the salt-hazard vtable. `initialize_runtime_pools_and_path_template_bank` uses it to seed the 40-slot array later reset by `initialize_salt_hazard_pool`.
_DWORD *__thiscall sub_408630(_DWORD *this)
{
  initialize_renderable_bod(this);
  *this = &off_497340;
  return this;
}

