/*
 * mangled: _ZN10cRSubGoldy5ShootEPS_
 * demangled: cRSubGoldy::Shoot(cRSubGoldy*)
 * address: 0007a424
 * size: 156
 */

/* cRSubGoldy::Shoot(cRSubGoldy*) */

void __thiscall cRSubGoldy::Shoot(cRSubGoldy *this,cRSubGoldy *param_1)

{
  cRSubGoldy *pcVar1;
  uint uVar2;
  int iVar3;
  cRSubGoldy *pcVar4;
  int iVar5;

  uVar2 = *(uint *)(param_1 + 0x324);
  if (((uVar2 & 1) == 0) && ((uVar2 & 0x68) == 0)) {
    if ((uVar2 & 0x12) == 0) {
      if ((uVar2 & 4) == 0) {
        return;
      }
      iVar5 = 3;
    }
    else {
      iVar5 = 2;
    }
  }
  else {
    iVar5 = 1;
  }
  iVar3 = 0;
  pcVar4 = this;
  while( true ) {
    while (pcVar1 = pcVar4 + 0x670, pcVar4 = pcVar4 + 0x2c8, *(int *)pcVar1 != 0) {
      iVar3 = iVar3 + 1;
      if (iVar3 == 0xc) {
        return;
      }
    }
    cRSubGolb::Create((cRSubGolb *)(this + iVar3 * 0x2c8 + 0x44c),this,iVar5,iVar3);
    iVar5 = iVar5 + -1;
    if (iVar5 == 0) break;
    iVar3 = iVar3 + 1;
    if (iVar3 == 0xc) {
      return;
    }
  }
  return;
}
