/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_track_row_runtime @ 0x408590 */
/* selector: initialize_track_row_runtime */

// Exact initializer for one authored `SubRow`: constructs its embedded `RowModel` base at +0x04, installs the cRRowModel vtable whose entry is exact update_row_model, constructs its embedded attachment `BodBase` at +0xb0, and returns the receiver. It leaves the scalar/copied row payload untouched. `initialize_runtime_pools_and_path_template_bank` invokes it over the owned 3200-entry, 0xf4-stride row slab.
SubRow *__thiscall initialize_track_row_runtime(SubRow *row)
{
  RowModel *p_row_model; // edi

  p_row_model = &row->row_model;
  initialize_renderable_bod(&row->row_model.body);
  p_row_model->body.bod.bod.vtable = g_row_model_vtable;
  initialize_bod_base(&row->attachment_body);
  return row;
}
