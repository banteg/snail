/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: advance_blink_random @ 0x4408a0 */
/* selector: advance_blink_random */

// Exact Windows `cRSubGame::BlinkRand()`: advances the owned cursor modulo 24 and returns the selected blink-cadence sample. Android preserves the same method and table cardinality.
double __thiscall advance_blink_random(SubgameRuntime *game)
{
  int32_t v1; // edx

  v1 = (game->blink_random_index + 1) % 24;
  game->blink_random_index = v1;
  return game->blink_random_samples[v1];
}
