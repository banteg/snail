/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_slug_hazard_runtime @ 0x408530 */
/* selector: initialize_slug_hazard_runtime */

// Constructs one slug-hazard runtime slot by running the shared renderable-body constructor and installing the slug vtable. `initialize_runtime_pools_and_path_template_bank` uses it to seed the 8-slot slug bank whose total footprint matches the native `cRSlug` size ledger.
_DWORD *__thiscall sub_408530(_DWORD *this)
{
  initialize_renderable_bod(this);
  *this = off_497324;
  return this;
}

