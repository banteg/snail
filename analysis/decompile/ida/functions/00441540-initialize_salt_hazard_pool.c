/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_salt_hazard_pool @ 0x441540 */
/* selector: initialize_salt_hazard_pool */

// Exact Windows `cRSaltManager::Init()`: clears the state at +0x80 for each of the manager's 40 inline Salt records. Android preserves the same manager method and loop.
int32_t *__thiscall initialize_salt_hazard_pool(SaltManager *manager)
{
  int32_t *result; // eax
  int v2; // ecx

  result = (int32_t *)&manager->slots[0].state;
  v2 = 40;
  do
  {
    *result = 0;
    result += 38;
    --v2;
  }
  while ( v2 );
  return result;
}
