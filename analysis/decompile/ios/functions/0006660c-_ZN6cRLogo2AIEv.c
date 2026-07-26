/*
 * mangled: _ZN6cRLogo2AIEv
 * demangled: cRLogo::AI()
 * address: 0006660c
 * size: 528
 */

/* cRLogo::AI() */

void __thiscall cRLogo::AI(cRLogo *this)

{
  undefined *puVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  cRLogo *pcVar6;
  float fVar7;

  puVar1 = PTR__Game_001b60b8;
  if (*(int *)(*(int *)PTR__Game_001b60b8 + 0x24) == 0) {
    if (((*(uint *)(*(int *)(*(int *)PTR__Game_001b60b8 + 0x224) + 0x30) & 0x4000) == 0) &&
       (cVar2 = RShellInkey(), cVar2 != '\v')) {
      iVar3 = *(int *)PTR__Game_001b60b8;
      iVar5 = *(int *)(iVar3 + 0x24);
      goto joined_r0x00066670;
    }
    cRFade::Start((cRFade *)(*(int *)puVar1 + 0x24),(_func_void *)0x0);
    *this = (cRLogo)0x1;
  }
  iVar3 = *(int *)PTR__Game_001b60b8;
  iVar5 = *(int *)(iVar3 + 0x24);
joined_r0x00066670:
  if ((iVar5 == 4) && (*this != (cRLogo)0x0)) {
    *(undefined4 *)(PTR__gConfig_001b60d4 + 0x1c) = *(undefined4 *)(this + 0x10);
    if (*(char *)(iVar3 + 0x2c1) == '\0') {
      *(undefined4 *)(iVar3 + 0x15c) = 3;
    }
    else {
      *(undefined4 *)(iVar3 + 0x15c) = 0x14;
    }
    puVar1 = PTR__Game_001b60b8;
    if (0 < *(int *)(this + 0x2101c)) {
      iVar3 = 0;
      do {
        pcVar6 = this + iVar3 * 0x84 + 0x21020;
        iVar5 = *(int *)puVar1;
        if ((*(uint *)(pcVar6 + 4) & 0x200) == 0) {
          RShellError("List remove");
        }
        else if ((*(uint *)(pcVar6 + 4) & 0x40) == 0) {
          iVar4 = *(int *)(pcVar6 + 0xc);
          if (iVar4 != 0) {
            *(undefined4 *)(iVar4 + 8) = *(undefined4 *)(pcVar6 + 8);
          }
          if (*(int *)(pcVar6 + 8) == 0) {
            *(int *)(iVar5 + 0x35c) = iVar4;
          }
          else {
            *(int *)(*(int *)(pcVar6 + 8) + 0xc) = iVar4;
          }
          *(undefined4 *)(pcVar6 + 0xc) = *(undefined4 *)(iVar5 + 0x360);
          *(cRLogo **)(iVar5 + 0x360) = pcVar6;
          *(uint *)(pcVar6 + 4) = *(uint *)(pcVar6 + 4) & 0xfffffdff;
        }
        else {
          RShellError("List remove NEXTBOD");
        }
        iVar3 = iVar3 + 1;
      } while (iVar3 < *(int *)(this + 0x2101c));
    }
  }
  if (*(int *)(this + 0xc) == 0) {
    *(undefined4 *)(this + 4) = 0;
    *(undefined4 *)(this + 0xc) = 1;
    if (*(float *)(this + 0x14) == 0.0) {
      fVar7 = 0.0;
    }
    else {
      fVar7 = 1.0 / (*(float *)(this + 0x14) * 60.0);
    }
    *(float *)(this + 8) = fVar7;
  }
  else if ((*(int *)(this + 0xc) == 1) &&
          (fVar7 = *(float *)(this + 4), *(float *)(this + 4) = fVar7 + *(float *)(this + 8),
          1.0 < fVar7 + *(float *)(this + 8))) {
    cRFade::Start((cRFade *)(*(int *)PTR__Game_001b60b8 + 0x24),(_func_void *)0x0);
    *this = (cRLogo)0x1;
    *(int *)(this + 0xc) = *(int *)(this + 0xc) + 1;
  }
  return;
}
