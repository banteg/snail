/*
 * mangled: _ZN10cRBackdrop4InitEi
 * demangled: cRBackdrop::Init(int)
 * address: 0003e698
 * size: 336
 */

/* cRBackdrop::Init(int) */

void __thiscall cRBackdrop::Init(cRBackdrop *this,int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  float fVar3;
  undefined8 uVar4;
  undefined4 uVar5;

  *(undefined4 *)(this + 0xe8) = DAT_0003e7e8;
  uVar5 = DAT_0003e7ec;
  *(undefined4 *)(this + 0xec) = 5;
  *(undefined4 *)(this + 0xf0) = uVar5;
  *(undefined4 *)(this + 0xe4) = uVar5;
  this[100] = (cRBackdrop)0x0;
  this[0x88] = (cRBackdrop)0x0;
  *(undefined4 *)(this + 0x84) = 1;
  *(undefined4 *)(this + 0x5c) = 0xffffffff;
  SetWorld(this,5);
  uVar2 = DAT_0003e7f4;
  uVar1 = DAT_0003e7f0;
  if ((*(uint *)(*(int *)(DAT_0003e810 + 0x3e6f8 + DAT_0003e814) + 0x1c) & 1) == 0) {
    *(undefined4 *)(this + 0x80) = 0;
    *(undefined4 *)(this + 0x8c) = uVar5;
    *(undefined4 *)(this + 0x90) = uVar2;
  }
  else {
    *(undefined4 *)(this + 0x80) = 1;
    *(undefined4 *)(this + 0x8c) = uVar1;
    *(undefined4 *)(this + 0x90) = DAT_0003e7f4;
  }
  uVar5 = DAT_0003e7ec;
  if (param_1 == 0) {
    *(undefined4 *)(this + 0xe0) = 0;
    *(undefined4 *)(this + 0x9c) = uVar5;
    *(undefined4 *)(this + 0x94) = uVar5;
    *(undefined4 *)(this + 0xbc) = 0;
    uVar5 = DAT_0003e7f0;
    *(undefined4 *)(this + 0xc0) = 0;
    *(undefined4 *)(this + 0xd4) = uVar5;
    *(undefined4 *)(this + 0xb4) = uVar5;
    *(undefined4 *)(this + 0xdc) = 0;
    *(undefined4 *)(this + 0x98) = DAT_0003e7f8;
    uVar5 = DAT_0003e7fc;
  }
  else {
    if (param_1 != 1) goto LAB_0003e774;
    *(undefined4 *)(this + 0xe0) = 0;
    *(undefined4 *)(this + 0x9c) = uVar5;
    *(undefined4 *)(this + 0x94) = uVar5;
    *(undefined4 *)(this + 0xbc) = 0;
    uVar5 = DAT_0003e7f0;
    *(undefined4 *)(this + 0xc0) = 0;
    *(undefined4 *)(this + 0xd4) = uVar5;
    *(undefined4 *)(this + 0xb4) = uVar5;
    *(undefined4 *)(this + 0xdc) = 0;
    *(undefined4 *)(this + 0x98) = DAT_0003e808;
    uVar5 = DAT_0003e80c;
  }
  *(undefined4 *)(this + 0xa0) = uVar5;
  *(undefined4 *)(this + 0xb8) = DAT_0003e800;
  *(undefined4 *)(this + 0xd8) = DAT_0003e804;
LAB_0003e774:
  fVar3 = (float)SetWorld(this,0);
  uVar4 = SetDistort(this,fVar3);
  SetTextureDimensions(this,(float)uVar4,(float)((ulonglong)uVar4 >> 0x20));
  return;
}
