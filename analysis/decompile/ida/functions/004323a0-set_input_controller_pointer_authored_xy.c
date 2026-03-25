/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_input_controller_pointer_authored_xy @ 0x4323a0 */
/* selector: set_input_controller_pointer_authored_xy */

// Seeds one global input-controller slot to an authored 640x480 pointer position, updates its normalized coordinates from the stored region bounds, and warps the backing OS cursor through click_mouse_screen.
void *__cdecl sub_4323A0(int a1, float a2, float a3)
{
  int v3; // edi
  int v4; // eax
  int v5; // ecx

  v3 = MEMORY[0x5088A0][a1];
  v4 = 14 * a1;
  *(float *)&MEMORY[0x503350][v4] = a2;
  v5 = MEMORY[0x508898][a1];
  *(float *)&MEMORY[0x503354][v4] = a3;
  return click_mouse_screen(
           a1,
           (__int64)((double)(MEMORY[0x5088A8][a1] - v3) * a2 * 0.0015625 + (double)v3),
           (__int64)((double)(v5 - MEMORY[0x508890][a1]) * a3 * 0.0020833334 + (double)MEMORY[0x508890][a1]));
}

