/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_noop_renderable_bod @ 0x408040 */
/* selector: initialize_noop_renderable_bod */

// Constructs one RenderableBod and replaces its callback with the shared noop_runtime_ai slot; construct_game_runtime uses it for the three passive overlay child bodies.
RenderableBod *__thiscall initialize_noop_renderable_bod(RenderableBod *body)
{
  initialize_renderable_bod(body);
  body->bod.bod.vtable = &g_noop_runtime_callback_table;
  return body;
}
