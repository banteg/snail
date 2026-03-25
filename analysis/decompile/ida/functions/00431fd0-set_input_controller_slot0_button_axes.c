/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_input_controller_slot0_button_axes @ 0x431fd0 */
/* selector: set_input_controller_slot0_button_axes */

// Stores the keyboard-derived button mask and X/Y axis floats into input-controller slot 0, overwriting its shared digital and analog lanes before later pointer data is merged in.
int __cdecl sub_431FD0(int a1, float a2, float a3)
{
  MEMORY[0x503344] = a1;
  MEMORY[0x50333C] = a2;
  MEMORY[0x503340] = a3;
  return a1;
}

