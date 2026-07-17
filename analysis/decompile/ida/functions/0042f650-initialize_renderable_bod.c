/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_renderable_bod @ 0x42f650 */
/* selector: initialize_renderable_bod */

// Builds the shared renderable bod shell on top of the base bod header, seeding its object-oriented vtable, default render flags, and identity local transform. iOS RObject.o names this positioned-body constructor `cRBodPos::cRBodPos()`.
RenderableBod *__thiscall initialize_renderable_bod(RenderableBod *body)
{
  initialize_bod_base(&body->bod);
  body->bod.bod.vtable = &g_renderable_bod_vtable;
  body->bod.bod.list_flags = 33555488;
  set_matrix_identity(&body->transform);
  return body;
}
