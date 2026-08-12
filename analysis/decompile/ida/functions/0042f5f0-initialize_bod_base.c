/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_bod_base @ 0x42f5f0 */
/* selector: initialize_bod_base */

// Exact Windows `cRBod::cRBod()` constructor: installs the base callback table and default flags, initializes the white color block, clears position/render state, and increments the global bod count. Android and iOS independently preserve the authored owner and constructor.
BodBase *__thiscall initialize_bod_base(BodBase *bod)
{
  tColour *p_color; // edi

  p_color = &bod->color;
  noop_this_constructor(&bod->color);
  bod->bod.vtable = &g_bod_base_vtable;
  bod->bod.list_flags = 33554464;
  store_color4f(p_color, 1.0, 1.0, 1.0, 1.0);
  ++g_bod_base_init_count;
  bod->position.z = 0.0;
  bod->position.y = 0.0;
  bod->position.x = 0.0;
  bod->render_arg_1c = 0.0;
  bod->render_arg_20 = 0.0;
  return bod;
}
