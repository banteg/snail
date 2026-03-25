/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_garbage_hazard @ 0x408550 */
/* selector: initialize_garbage_hazard */

// Constructs one garbage-hazard runtime object by running the shared body constructor and installing the cRSubGarbage vtable. `initialize_runtime_pools_and_path_template_bank` uses it to seed the 50-slot garbage pool that later feeds `spawn_track_garbage_hazard`.
_DWORD *__thiscall sub_408550(_DWORD *this)
{
  initialize_renderable_bod(this);
  *this = &off_497328;
  return this;
}

