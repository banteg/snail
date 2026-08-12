/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_renderable_bod @ 0x42f650 */
/* selector: initialize_renderable_bod */

// Exact Windows `cRBodPos::cRBodPos()` constructor: invokes `cRBod::cRBod()`, installs the positioned-body callback table and transform flag, and initializes the local matrix to identity. Android and iOS preserve the same authored constructor chain.
RenderableBod *__thiscall initialize_renderable_bod(RenderableBod *body)
{
  initialize_bod_base(&body->bod);
  body->bod.bod.vtable = &g_renderable_bod_vtable;
  body->bod.bod.list_flags = 33555488;
  set_matrix_identity(&body->transform);
  return body;
}
