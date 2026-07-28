/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_blink_random @ 0x4408c0 */
/* selector: initialize_blink_random */

// Exact void Windows `cRSubGame::BlinkRandInit()`: resets the owned cursor and fills 24 blink-cadence samples with `1 / (((rand / 32768) + 1) * 60)`. Android and iOS preserve the same owner, table cardinality, formula, and void contract.
void __thiscall initialize_blink_random(cRSubGame *game)
{
  float *blink_random_samples; // esi
  int i; // edi

  game->blink_random_index = 0;
  blink_random_samples = game->blink_random_samples;
  for ( i = 24; i != 0; --i )
    *blink_random_samples++ = 1.0 / (((double)next_math_random_value() * 0.000030517578 + 1.0) * 60.0);
}
