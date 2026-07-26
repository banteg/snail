/*
 * mangled: _ZN10cRSubGoldy11FallingInitEv
 * demangled: cRSubGoldy::FallingInit()
 * address: 0006bef8
 * size: 112
 */

/* cRSubGoldy::FallingInit() */

void __thiscall cRSubGoldy::FallingInit(cRSubGoldy *this)

{
  undefined4 uVar1;

  uVar1 = DAT_0006bf68;
  if (this[0x374] == (cRSubGoldy)0x0) {
    *(undefined4 *)(this + 0x424) = DAT_0006bf68;
    *(undefined4 *)(this + 0x428) = uVar1;
  }
  else {
    *(undefined4 *)(this + 0x428) = *(undefined4 *)(*(int *)(this + 0x378) + 0x80);
    *(undefined4 *)(this + 0x424) = *(undefined4 *)(this + 0x390);
  }
  this[0x415] = (cRSubGoldy)0x1;
  this[0x445] = (cRSubGoldy)0x0;
  this[0x374] = (cRSubGoldy)0x0;
  uVar1 = DAT_0006bf68;
  *(undefined4 *)(this + 0x41c) = *(undefined4 *)(this + 100);
  this[0x444] = (cRSubGoldy)0x0;
  *(undefined4 *)(this + 0x42c) = uVar1;
  return;
}
