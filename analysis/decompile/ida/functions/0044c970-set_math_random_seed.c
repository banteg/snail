/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_math_random_seed @ 0x44c970 */
/* selector: set_math_random_seed */

// Stores one caller-provided seed into the shared gameplay linear-congruential generator before the random table is consumed. Android symbols match this helper family to `RandSeed(int)`.
int __cdecl sub_44C970(int a1)
{
  return sub_48BFDB(a1);
}

