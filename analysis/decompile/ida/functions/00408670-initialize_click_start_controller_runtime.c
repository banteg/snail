/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_click_start_controller_runtime @ 0x408670 */
/* selector: initialize_click_start_controller_runtime */

// Constructs the renderable click-start controller and installs the callback table whose first entry is `update_click_start`. This is the runtime slot constructor; `initialize_click_start` later seeds the gameplay prompt state.
_DWORD *__thiscall sub_408670(_DWORD *this)
{
  initialize_renderable_bod(this);
  *this = &g_click_start_controller_vtable;
  return this;
}
