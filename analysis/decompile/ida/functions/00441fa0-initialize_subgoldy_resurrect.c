/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_subgoldy_resurrect @ 0x441fa0 */
/* selector: initialize_subgoldy_resurrect */

// Seeds Goldy's resurrect state machine by storing the respawn-or-final-loss selector, enabling the resurrect-active flag, and resetting the shared fade timer. Cross-port Android and iOS symbols match this helper to `cRSubGoldy::RessurectInit(int)`.
int __thiscall sub_441FA0(int this, int a2)
{
  *(_BYTE *)(this + 132) = 1;
  *(_DWORD *)(this + 128) = a2;
  *(_DWORD *)(this + 140) = 0;
  *(_DWORD *)(this + 144) = 1007192201;
  return a2;
}

