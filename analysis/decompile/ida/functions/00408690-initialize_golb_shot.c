/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_golb_shot @ 0x408690 */
/* selector: initialize_golb_shot */

// Constructs one 0x2e8-byte Golb shot slot by seeding its three renderable-body prefixes and installing the `update_golb_ai`, vapour, and no-op child callback tables. `initialize_runtime_pools_and_path_template_bank` uses it for the 12-shot bank later driven by `create_golb`.
GolbShot *__thiscall initialize_golb_shot(GolbShot *shot)
{
  initialize_renderable_bod(&shot->primary_body);
  initialize_renderable_bod(&shot->vapour.body);
  shot->vapour.body.bod.bod.vtable = &g_vapour_vtable;
  initialize_renderable_bod(&shot->tertiary_body);
  shot->tertiary_body.bod.bod.vtable = g_golb_noop_body_vtable;
  shot->primary_body.bod.bod.vtable = &g_golb_shot_vtable;
  return shot;
}
