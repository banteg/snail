/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_fringe_object @ 0x408650 */
/* selector: initialize_fringe_object */

// Constructs one 0x38-byte fringe render object by clearing the shared object base and installing the fringe-object vtable. `initialize_runtime_pools_and_path_template_bank` uses it to seed the 7000-entry fringe-manager pool later consumed by `allocate_fringe_object`.
_DWORD *__thiscall sub_408650(_DWORD *this)
{
  initialize_bod_base(this);
  *this = &off_497344;
  return this;
}

