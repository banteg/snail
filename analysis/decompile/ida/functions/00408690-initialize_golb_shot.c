/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_golb_shot @ 0x408690 */
/* selector: initialize_golb_shot */

// Constructs one 0x2e8-byte Golb shot slot by seeding its three renderable-body prefixes and installing the `update_golb_ai`, vapour, and no-op child callback tables. `initialize_runtime_pools_and_path_template_bank` uses it for the 12-shot bank later driven by `create_golb`.
_DWORD *__thiscall sub_408690(_DWORD *this)
{
  initialize_renderable_bod(this);
  initialize_renderable_bod(this + 32);
  *(this + 32) = &g_vapour_vtable;
  initialize_renderable_bod(this + 70);
  *(this + 70) = g_golb_noop_body_vtable;
  *this = g_golb_shot_vtable;
  return this;
}
