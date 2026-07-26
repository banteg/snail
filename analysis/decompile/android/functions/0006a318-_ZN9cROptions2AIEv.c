/*
 * mangled: _ZN9cROptions2AIEv
 * demangled: cROptions::AI()
 * address: 0006a318
 * size: 348
 */

/* cROptions::AI() */

void __thiscall cROptions::AI(cROptions *this)

{
  int iVar1;
  uint uVar2;

  gConfig._4_4_ = *(undefined4 *)(*(int *)(this + 0x1c) + 0x170);
  gConfig._0_4_ = *(undefined4 *)(*(int *)(this + 0x18) + 0x170);
  if (*(float *)(Game + 0x3c) != *(float *)(Game + 0x44)) {
    UnInit(this);
    Init(this);
  }
  iVar1 = *(int *)(this + 0x14);
  if ((*(uint *)(iVar1 + 0x194) & 0x20) == 0) {
    if (gConfig._8_4_ != 0) goto LAB_0006a424;
  }
  else {
    *(uint *)(iVar1 + 0x194) = *(uint *)(iVar1 + 0x194) & 0xffffffdf;
    if (gConfig._8_4_ == 0) {
      gConfig._8_4_ = 1;
LAB_0006a424:
      Rstrcpy((char *)(iVar1 + 0x2c4),"Touch Mode");
      goto LAB_0006a3b0;
    }
    gConfig._8_4_ = 0;
  }
  Rstrcpy((char *)(iVar1 + 0x2c4),"Tilt Mode");
LAB_0006a3b0:
  uVar2 = *(uint *)(*(int *)(this + 0x18) + 0x194);
  if ((uVar2 & 0x20) != 0) {
    *(uint *)(*(int *)(this + 0x18) + 0x194) = uVar2 & 0xffffffdf;
  }
  uVar2 = *(uint *)(*(int *)(this + 0x10) + 0x194);
  if ((uVar2 & 0x20) != 0) {
    *(uint *)(*(int *)(this + 0x10) + 0x194) = uVar2 & 0xffffffdf;
    UnInit(this);
    iVar1 = Game;
    *(undefined4 *)(Game + 0x15c) = *(undefined4 *)this;
    *(undefined1 *)(iVar1 + 0x324) = 0;
  }
  Apply(SUB41(this,0));
  if (*(float *)(this + 0x24) != (float)gConfig._0_4_) {
    cRSound::Play((int)&gRSound);
    *(undefined4 *)(this + 0x24) = gConfig._0_4_;
    return;
  }
  return;
}
