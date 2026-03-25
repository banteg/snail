/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_track_row_runtime @ 0x408590 */
/* selector: initialize_track_row_runtime */

// Constructs one runtime track-row record by seeding its shared bod header, installing the row vtable on the embedded renderable body, and clearing the per-row auxiliary bod. `initialize_runtime_pools_and_path_template_bank` uses it for the `0x5ccac8 + row * 0xf4` bank documented as the native runtime row grid.
_DWORD *__thiscall sub_408590(_DWORD *this)
{
  _DWORD *v2; // edi

  v2 = this + 1;
  initialize_renderable_bod(this + 1);
  *v2 = &off_497330;
  initialize_bod_base(this + 44);
  return this;
}

