/*
 * mangled: _ZN10cRSubGoldy13SetShootFlagsEv
 * demangled: cRSubGoldy::SetShootFlags()
 * address: 000709dc
 * size: 272
 */

/* cRSubGoldy::SetShootFlags() */

void __thiscall cRSubGoldy::SetShootFlags(cRSubGoldy *this)

{
  int iVar1;
  int iVar2;

  *(undefined4 *)(this + 0x324) = 0;
  switch(*(undefined4 *)(this + 0x2f0)) {
  case 0:
    iVar2 = 1;
    break;
  case 1:
    iVar2 = 2;
    break;
  case 2:
    iVar2 = 4;
    break;
  case 3:
    iVar2 = 8;
    goto LAB_00070a24;
  case 4:
    iVar2 = 0x10;
    goto LAB_00070a24;
  case 5:
    iVar2 = 0x20;
    goto LAB_00070a60;
  case 6:
    iVar2 = 0x40;
    goto LAB_00070ac8;
  case 7:
    iVar2 = 0xc0;
LAB_00070ac8:
    *(int *)(this + 0x324) = iVar2;
    *(undefined4 *)(this + 0x25b0) = DAT_00070af8;
    goto LAB_00070a3c;
  case 8:
    iVar2 = 0x90;
LAB_00070a24:
    *(int *)(this + 0x324) = iVar2;
    *(undefined4 *)(this + 0x25b0) = DAT_00070aec;
    goto LAB_00070a3c;
  default:
    iVar2 = 0x81;
LAB_00070a60:
    *(int *)(this + 0x324) = iVar2;
    *(undefined4 *)(this + 0x25b0) = DAT_00070af0;
    goto LAB_00070a3c;
  }
  *(int *)(this + 0x324) = iVar2;
  *(undefined4 *)(this + 0x25b0) = DAT_00070af4;
LAB_00070a3c:
  iVar1 = *(int *)(this + 0x328);
  if (iVar1 != iVar2) {
    cRSnail::SetWeapon((cRSnail *)(this + 0x2800),iVar2);
    iVar1 = *(int *)(this + 0x324);
  }
  *(int *)(this + 0x328) = iVar1;
  return;
}
