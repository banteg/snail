/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_jetpack_gauge @ 0x43a930 */
/* selector: initialize_jetpack_gauge */

// Initializes the player jetpack countdown or warning controller at +0x2750, wiring the live Game pointer and warning anchor used by `update_jetpack_gauge`. Cross-port Android symbols still name the owning class `cRDamageGuage::Init()`.
int __thiscall sub_43A930(_DWORD *this, int a2)
{
  char *v3; // edx
  char *v4; // edx

  *this = 0;
  v3 = (char *)MEMORY[0x4DF904] + 476696;
  *(this + 1) = 987395086;
  *(this + 128) = v3;
  v4 = (char *)&loc_42FD7C + (_DWORD)MEMORY[0x4DF904];
  *(this + 3) = 0;
  *(this + 4) = v4;
  *(this + 7) = 0;
  *(this + 6) = 0;
  *(this + 5) = 0;
  *(this + 131) = 0;
  return 0;
}

