/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_cameraman @ 0x446160 */
/* selector: initialize_cameraman */

// Initializes the follow-camera controller, wiring its shared player and global pointers, clearing the cached matrices, and seeding the default zoom used by `update_subgame_camera`. Cross-port Android and iOS symbols match this helper to `cRCameraman::Init()`.
int32_t __thiscall initialize_cameraman(CameramanState *cameraman)
{
  Game *v2; // ecx
  int32_t result; // eax

  cameraman->player = (Player *)((char *)&loc_42FD7C + (_DWORD)MEMORY[0x4DF904]);
  v2 = (Game *)((char *)MEMORY[0x4DF904] + 476696);
  cameraman->unresolved_cc = 0;
  cameraman->game = v2;
  set_matrix_identity(&cameraman->previous_desired_matrix);
  set_matrix_identity(&cameraman->desired_matrix);
  set_matrix_identity(&cameraman->live_matrix);
  cameraman->attachment_lift_envelope = 0.0;
  cameraman->smoothed_attachment_lift_envelope = 0.0;
  cameraman->fov_degrees = 110.0;
  return result;
}

