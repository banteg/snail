/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_salt_hazard_pool @ 0x441540 */
/* selector: initialize_salt_hazard_pool */

// Exact void Windows `cRSaltManager::Init()`: clears the 32-bit SaltState at +0x80 for each of the manager's 40 inline Salt records. Its sole Windows caller discards EAX, and Android preserves the same manager method and loop.
void __thiscall initialize_salt_hazard_pool(SaltManager *manager)
{
  SaltState *p_state; // eax
  int v2; // ecx

  p_state = &manager->slots[0].state;
  v2 = 40;
  do
  {
    *p_state = SALT_STATE_INACTIVE;
    p_state += 38;
    --v2;
  }
  while ( v2 );
}
