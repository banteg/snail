/*
 * mangled: _ZN10cRSubGoldyC1Ev
 * demangled: cRSubGoldy::cRSubGoldy()
 * address: 00025834
 * size: 528
 */

/* cRSubGoldy::cRSubGoldy() */

cRSubGoldy * __thiscall cRSubGoldy::cRSubGoldy(cRSubGoldy *this)

{
  int iVar1;
  int iVar2;
  cRBodPos *this_00;
  int iVar3;
  int iVar4;

  iVar4 = DAT_00025a44;
  cRBodPos::cRBodPos((cRBodPos *)this);
  iVar1 = DAT_00025a50;
  iVar3 = DAT_00025a4c;
  iVar4 = iVar4 + 0x25850;
  this_00 = (cRBodPos *)(this + 0x44c);
  *(int *)this = *(int *)(iVar4 + DAT_00025a48) + 8;
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x94));
  iVar2 = DAT_00025a58;
  *(int *)(this + 0x94) = *(int *)(iVar4 + DAT_00025a54) + 8;
  do {
    cRBodPos::cRBodPos(this_00);
    *(int *)this_00 = *(int *)(iVar4 + iVar3) + 8;
    cRBodPos::cRBodPos(this_00 + 0x74);
    *(int *)(this_00 + 0x74) = *(int *)(iVar4 + iVar1) + 8;
    cRBodPos::cRBodPos(this_00 + 0x100);
    *(int *)(this_00 + 0x100) = *(int *)(iVar4 + iVar2) + 8;
    this_00 = this_00 + 0x2c8;
  } while (this_00 != (cRBodPos *)(this + 0x25ac));
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x2800));
  iVar3 = 0;
  *(int *)(this + 0x2800) = *(int *)(iVar4 + DAT_00025a5c) + 8;
  do {
    iVar1 = iVar3 + 0x2940;
    iVar3 = iVar3 + 0x74;
    cRBodPos::cRBodPos((cRBodPos *)(this + iVar1));
    iVar1 = DAT_00025a60;
  } while (iVar3 != 0x488);
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x2dc8));
  iVar3 = 0;
  *(int *)(this + 0x2dc8) = *(int *)(iVar4 + iVar1) + 8;
  do {
    iVar2 = iVar3 + 0x2f0c;
    iVar3 = iVar3 + 0x74;
    cRBodPos::cRBodPos((cRBodPos *)(this + iVar2));
  } while (iVar3 != 0x244);
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x315c));
  iVar3 = 0;
  *(int *)(this + 0x315c) = *(int *)(iVar4 + iVar1) + 8;
  do {
    iVar2 = iVar3 + 0x32a0;
    iVar3 = iVar3 + 0x74;
    cRBodPos::cRBodPos((cRBodPos *)(this + iVar2));
  } while (iVar3 != 0x244);
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x34f0));
  iVar3 = 0;
  *(int *)(this + 0x34f0) = *(int *)(iVar4 + iVar1) + 8;
  do {
    iVar2 = iVar3 + 0x3634;
    iVar3 = iVar3 + 0x74;
    cRBodPos::cRBodPos((cRBodPos *)(this + iVar2));
  } while (iVar3 != 0x244);
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x3884));
  iVar3 = 0;
  *(int *)(this + 0x3884) = *(int *)(iVar4 + iVar1) + 8;
  do {
    iVar1 = iVar3 + 0x39c8;
    iVar3 = iVar3 + 0x74;
    cRBodPos::cRBodPos((cRBodPos *)(this + iVar1));
  } while (iVar3 != 0x244);
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x3c28));
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x3c9c));
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x3ed8));
  *(int *)(this + 0x3ed8) = *(int *)(iVar4 + DAT_00025a64) + 8;
  return this;
}
