/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: sine @ 0x44c9d0 */
/* selector: sine */

// Computes one sine value through the shared gameplay trigonometry wrapper. Android symbols match this helper to `Sin(float)`.
double __cdecl sub_44C9D0(float a1)
{
  return MEMORY[0x77FF8C][(__int64)(a1 * 0.15915494 * 8192.0) & 0x1FFF];
}

