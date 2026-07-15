/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: append_enumerated_input_controller_callback @ 0x44b490 */
/* selector: append_enumerated_input_controller_callback */

// DirectInput device-enumeration callback that creates one joystick device from the reported instance, appends it to the global controller list, and stops enumeration once four devices are present.
int __stdcall append_enumerated_input_controller_callback(DIDEVICEINSTANCEA *instance, void *context)
{
  IDirectInputDevice8A **v3; // [esp-8h] [ebp-8h]

  v3 = (IDirectInputDevice8A **)(4 * g_joystick_count++ + 7830324);
  return g_joystick_input->lpVtbl->CreateDevice(g_joystick_input, &instance->guidInstance, v3, nullptr) < 0
      || g_joystick_count < 4;
}
