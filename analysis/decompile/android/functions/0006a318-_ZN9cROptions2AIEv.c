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
  int iVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  float *pfVar9;

  iVar1 = DAT_0006a47c;
  iVar7 = DAT_0006a478;
  iVar8 = DAT_0006a474 + 0x6a330;
  piVar3 = *(int **)(iVar8 + DAT_0006a478);
  puVar6 = *(undefined4 **)(iVar8 + DAT_0006a47c);
  puVar6[1] = *(undefined4 *)(*(int *)(this + 0x1c) + 0x170);
  *puVar6 = *(undefined4 *)(*(int *)(this + 0x18) + 0x170);
  if (*(float *)(*piVar3 + 0x3c) != *(float *)(*piVar3 + 0x44)) {
    UnInit(this);
    Init(this);
  }
  iVar2 = *(int *)(this + 0x14);
  if ((*(uint *)(iVar2 + 0x194) & 0x20) == 0) {
    if (*(int *)(*(int *)(iVar8 + iVar1) + 8) != 0) goto LAB_0006a424;
  }
  else {
    iVar4 = *(int *)(iVar8 + iVar1);
    *(uint *)(iVar2 + 0x194) = *(uint *)(iVar2 + 0x194) & 0xffffffdf;
    if (*(int *)(iVar4 + 8) == 0) {
      *(undefined4 *)(iVar4 + 8) = 1;
LAB_0006a424:
      Rstrcpy((char *)(iVar2 + 0x2c4),(char *)(iVar8 + DAT_0006a488));
      goto LAB_0006a3b0;
    }
    *(undefined4 *)(iVar4 + 8) = 0;
  }
  Rstrcpy((char *)(iVar2 + 0x2c4),(char *)(iVar8 + DAT_0006a480));
LAB_0006a3b0:
  uVar5 = *(uint *)(*(int *)(this + 0x18) + 0x194);
  if ((uVar5 & 0x20) != 0) {
    *(uint *)(*(int *)(this + 0x18) + 0x194) = uVar5 & 0xffffffdf;
  }
  uVar5 = *(uint *)(*(int *)(this + 0x10) + 0x194);
  if ((uVar5 & 0x20) != 0) {
    *(uint *)(*(int *)(this + 0x10) + 0x194) = uVar5 & 0xffffffdf;
    UnInit(this);
    iVar7 = **(int **)(iVar8 + iVar7);
    *(undefined4 *)(iVar7 + 0x15c) = *(undefined4 *)this;
    *(undefined1 *)(iVar7 + 0x324) = 0;
  }
  Apply(SUB41(this,0));
  pfVar9 = *(float **)(iVar8 + iVar1);
  if (*(float *)(this + 0x24) != *pfVar9) {
    cRSound::Play(*(int *)(iVar8 + DAT_0006a484));
    *(float *)(this + 0x24) = *pfVar9;
    return;
  }
  return;
}
