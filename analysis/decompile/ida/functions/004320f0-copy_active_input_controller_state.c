/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: copy_active_input_controller_state @ 0x4320f0 */
/* selector: copy_active_input_controller_state */

// Copies one of the two global input-controller slots into the caller-owned runtime buffer, including button flags, normalized pointer coordinates, and the per-slot authored cursor lanes used by gameplay input.
float *__cdecl sub_4320F0(
        int a1,
        _DWORD *a2,
        float *a3,
        float *a4,
        float *a5,
        float *a6,
        float *a7,
        float *a8,
        float *a9)
{
  if ( a1 )
  {
    *a2 = MEMORY[0x50337C];
    *a3 = MEMORY[0x503374];
    *a4 = MEMORY[0x503378];
    *a5 = MEMORY[0x503388];
    *a6 = MEMORY[0x50338C];
    *a7 = MEMORY[0x503390];
    *a8 = MEMORY[0x503380];
    *a9 = MEMORY[0x503384];
    return a7;
  }
  else
  {
    *a2 = MEMORY[0x503344][0];
    *a3 = MEMORY[0x50333C][0];
    *a4 = MEMORY[0x503340][0];
    *a5 = *(float *)&MEMORY[0x503350];
    *a6 = *(float *)&MEMORY[0x503354];
    *a7 = MEMORY[0x503358];
    *a8 = MEMORY[0x503348];
    *a9 = MEMORY[0x50334C];
    return a7;
  }
}

