/*
 * mangled: _ZN10cRBackdrop4InitEi
 * demangled: cRBackdrop::Init(int)
 * address: 0003e698
 * size: 336
 */

/* cRBackdrop::Init(int) */

void __thiscall cRBackdrop::Init(cRBackdrop *this,int param_1)

{
  float fVar1;
  undefined8 uVar2;
  undefined4 uVar3;

  *(undefined4 *)(this + 0xe8) = 0x3b5a740e;
  *(undefined4 *)(this + 0xec) = 5;
  *(undefined4 *)(this + 0xf0) = 0;
  *(undefined4 *)(this + 0xe4) = 0;
  this[100] = (cRBackdrop)0x0;
  this[0x88] = (cRBackdrop)0x0;
  *(undefined4 *)(this + 0x84) = 1;
  *(undefined4 *)(this + 0x5c) = 0xffffffff;
  SetWorld(this,5);
  if ((gConfig._28_4_ & 1) == 0) {
    *(undefined4 *)(this + 0x80) = 0;
    *(undefined4 *)(this + 0x8c) = 0;
    *(undefined4 *)(this + 0x90) = 0x3caaaaab;
  }
  else {
    *(undefined4 *)(this + 0x80) = 1;
    *(undefined4 *)(this + 0x8c) = 0x3f800000;
    *(undefined4 *)(this + 0x90) = 0x3caaaaab;
  }
  if (param_1 == 0) {
    *(undefined4 *)(this + 0xe0) = 0;
    *(undefined4 *)(this + 0x9c) = 0;
    *(undefined4 *)(this + 0x94) = 0;
    *(undefined4 *)(this + 0xbc) = 0;
    *(undefined4 *)(this + 0xc0) = 0;
    *(undefined4 *)(this + 0xd4) = 0x3f800000;
    *(undefined4 *)(this + 0xb4) = 0x3f800000;
    *(undefined4 *)(this + 0xdc) = 0;
    *(undefined4 *)(this + 0x98) = 0x3aab92a7;
    uVar3 = 0x3ae4c389;
  }
  else {
    if (param_1 != 1) goto LAB_0003e774;
    *(undefined4 *)(this + 0xe0) = 0;
    *(undefined4 *)(this + 0x9c) = 0;
    *(undefined4 *)(this + 0x94) = 0;
    *(undefined4 *)(this + 0xbc) = 0;
    *(undefined4 *)(this + 0xc0) = 0;
    *(undefined4 *)(this + 0xd4) = 0x3f800000;
    *(undefined4 *)(this + 0xb4) = 0x3f800000;
    *(undefined4 *)(this + 0xdc) = 0;
    *(undefined4 *)(this + 0x98) = 0xbb2b92a7;
    uVar3 = 0xbb64c389;
  }
  *(undefined4 *)(this + 0xa0) = uVar3;
  *(undefined4 *)(this + 0xb8) = 0x3bb60b61;
  *(undefined4 *)(this + 0xd8) = 0x3b888889;
LAB_0003e774:
  fVar1 = (float)SetWorld(this,0);
  uVar2 = SetDistort(this,fVar1);
  SetTextureDimensions(this,(float)uVar2,(float)((ulonglong)uVar2 >> 0x20));
  return;
}
