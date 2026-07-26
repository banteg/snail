/*
 * mangled: _ZN12cRInvincible4InitEv
 * demangled: cRInvincible::Init()
 * address: 0006d380
 * size: 44
 */

/* cRInvincible::Init() */

void cRInvincible::Init(void)

{
  int iVar1;
  int in_r0;
  float in_s0;

  iVar1 = DAT_0006d3ac;
  *(undefined4 *)(in_r0 + 0x74) = 0;
  cRSnailSkin::Change((cRSnailSkin *)(**(int **)(iVar1 + 0x6d39c + DAT_0006d3b0) + 0x852d4),0,in_s0)
  ;
  return;
}
