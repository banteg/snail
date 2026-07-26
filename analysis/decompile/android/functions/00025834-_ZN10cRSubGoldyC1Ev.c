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
  cRBodPos *this_00;
  int iVar2;

  cRBodPos::cRBodPos((cRBodPos *)this);
  this_00 = (cRBodPos *)(this + 0x44c);
  *(undefined ***)this = &PTR_AI_0009ace0;
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x94));
  *(undefined ***)(this + 0x94) = &PTR_AI_0009ad20;
  do {
    cRBodPos::cRBodPos(this_00);
    *(undefined ***)this_00 = &PTR_AI_0009ac60;
    cRBodPos::cRBodPos(this_00 + 0x74);
    *(undefined ***)(this_00 + 0x74) = &PTR_AI_0009add0;
    cRBodPos::cRBodPos(this_00 + 0x100);
    *(undefined ***)(this_00 + 0x100) = &PTR_AI_0009ac70;
    this_00 = this_00 + 0x2c8;
  } while (this_00 != (cRBodPos *)(this + 0x25ac));
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x2800));
  iVar2 = 0;
  *(undefined ***)(this + 0x2800) = &PTR_AI_0009acf0;
  do {
    iVar1 = iVar2 + 0x2940;
    iVar2 = iVar2 + 0x74;
    cRBodPos::cRBodPos((cRBodPos *)(this + iVar1));
  } while (iVar2 != 0x488);
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x2dc8));
  iVar2 = 0;
  *(undefined ***)(this + 0x2dc8) = &PTR_AI_0009ad00;
  do {
    iVar1 = iVar2 + 0x2f0c;
    iVar2 = iVar2 + 0x74;
    cRBodPos::cRBodPos((cRBodPos *)(this + iVar1));
  } while (iVar2 != 0x244);
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x315c));
  iVar2 = 0;
  *(undefined ***)(this + 0x315c) = &PTR_AI_0009ad00;
  do {
    iVar1 = iVar2 + 0x32a0;
    iVar2 = iVar2 + 0x74;
    cRBodPos::cRBodPos((cRBodPos *)(this + iVar1));
  } while (iVar2 != 0x244);
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x34f0));
  iVar2 = 0;
  *(undefined ***)(this + 0x34f0) = &PTR_AI_0009ad00;
  do {
    iVar1 = iVar2 + 0x3634;
    iVar2 = iVar2 + 0x74;
    cRBodPos::cRBodPos((cRBodPos *)(this + iVar1));
  } while (iVar2 != 0x244);
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x3884));
  iVar2 = 0;
  *(undefined ***)(this + 0x3884) = &PTR_AI_0009ad00;
  do {
    iVar1 = iVar2 + 0x39c8;
    iVar2 = iVar2 + 0x74;
    cRBodPos::cRBodPos((cRBodPos *)(this + iVar1));
  } while (iVar2 != 0x244);
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x3c28));
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x3c9c));
  cRBodPos::cRBodPos((cRBodPos *)(this + 0x3ed8));
  *(undefined ***)(this + 0x3ed8) = &PTR_AI_0009ad10;
  return this;
}
