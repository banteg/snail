/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: append_enumerated_input_controller_callback @ 0x44b490 */
/* selector: append_enumerated_input_controller_callback */

// DirectInput device-enumeration callback that creates one joystick device from the reported instance, appends it to the global controller list, and stops enumeration once four devices are present.
BOOL __stdcall append_enumerated_input_controller_callback(int a1, int a2)
{
  int v3; // [esp-8h] [ebp-8h]

  v3 = 4 * dword_777B2C[0]++ + 7830324;
  return (*(int (__stdcall **)(int, int, int, _DWORD))(*(_DWORD *)dword_777B2C[1] + 12))(dword_777B2C[1], a1 + 4, v3, 0) < 0
      || dword_777B2C[0] < 4;
}

