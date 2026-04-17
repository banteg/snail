/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_cull_mode @ 0x4129f0 */
/* selector: set_cull_mode */

// Programs the shared renderer cull state from the one-bit front-vs-back-face selection. Cross-port Android symbols match this helper to `G0SetCull(int)`.
int __cdecl sub_4129F0(char a1)
{
  return sub_411700(MEMORY[0x4F7458], a1);
}

