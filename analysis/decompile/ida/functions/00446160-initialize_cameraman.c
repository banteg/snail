/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_cameraman @ 0x446160 */
/* selector: initialize_cameraman */

// Initializes the follow-camera controller, wiring its shared player and global pointers, clearing the cached matrices, and seeding the default zoom used by `update_subgame_camera`. Cross-port Android and iOS symbols match this helper to `cRCameraman::Init()`.
int __thiscall sub_446160(int this)
{
  char *v2; // ecx
  int result; // eax

  *(_DWORD *)(this + 192) = (char *)&loc_42FD7C + (_DWORD)MEMORY[0x4DF904];
  v2 = (char *)MEMORY[0x4DF904] + 476696;
  *(_BYTE *)(this + 204) = 0;
  *(_DWORD *)(this + 196) = v2;
  set_matrix_identity((_DWORD *)(this + 128));
  set_matrix_identity((_DWORD *)(this + 64));
  result = set_matrix_identity((_DWORD *)this);
  *(_DWORD *)(this + 208) = 0;
  *(_DWORD *)(this + 212) = 0;
  *(_DWORD *)(this + 200) = 1121714176;
  return result;
}

