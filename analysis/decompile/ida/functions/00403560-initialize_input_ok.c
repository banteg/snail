/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_input_ok @ 0x403560 */
/* selector: initialize_input_ok */

int __thiscall sub_403560(int this)
{
  int v2; // eax
  int v3; // ecx

  v2 = allocate_border((_DWORD *)MEMORY[0x4DF904] + 723);
  v3 = *(_DWORD *)(this + 28);
  *(_DWORD *)(this + 32) = v2;
  initialize_frontend_widget(v2, 20, aOk, *(_DWORD *)(v3 + 124), 0, 0.0, v3 + 444, 0, 0.0);
  return update_input_ok((float **)this);
}

