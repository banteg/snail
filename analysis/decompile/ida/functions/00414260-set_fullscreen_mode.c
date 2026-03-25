/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_fullscreen_mode @ 0x414260 */
/* selector: set_fullscreen_mode */

// Switches the renderer's display mode between windowed (`0`) and fullscreen (`1`) through the shared device wrapper, updates the saved window rectangle bookkeeping, and recenters the cursor after the mode change.
char __usercall sub_414260@<al>(int a1@<edi>, char a2)
{
  return sub_414270((int)MEMORY[0x4F7458], a1, a2);
}

