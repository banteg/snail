/*
 * mangled: _ZN8cRGalaxy4OpenEi
 * demangled: cRGalaxy::Open(int)
 * address: 0005aea4
 * size: 1168
 */

/* cRGalaxy::Open(int) */

void __thiscall cRGalaxy::Open(cRGalaxy *this,int param_1)

{
  bool bVar1;
  cRGalaxy *pcVar2;
  float *pfVar3;
  void *pvVar4;
  cRGalaxy *pcVar5;
  cRGalaxy *pcVar6;
  float *pfVar7;
  cRGalaxy cVar8;
  undefined1 *puVar9;
  cRGalaxy *pcVar10;
  int iVar11;
  int iVar12;
  undefined4 uVar13;
  int local_128;
  int local_124;
  cRGalaxy *local_11c;
  char *local_110;
  cRGalaxy *local_f8;
  char acStack_f4 [128];
  char acStack_74 [64];
  int local_34;

  puVar9 = (undefined1 *)0x1d4;
  this[8] = (cRGalaxy)0x0;
  *(undefined4 *)this = 0;
  local_34 = __stack_chk_guard;
  if (param_1 == 0) {
    puVar9 = (undefined1 *)&gUniverse0;
  }
  else if (param_1 == 1) {
    puVar9 = gUniverse1;
  }
  pfVar7 = (float *)((int)puVar9 + 4);
  iVar12 = (int)*(float *)puVar9;
  *(int *)(this + 0x14) = iVar12;
  if (0 < iVar12) {
    iVar11 = 0;
    pcVar5 = this;
    pfVar3 = (float *)((int)puVar9 + 0xc);
    do {
      pfVar7 = pfVar3;
      iVar11 = iVar11 + 1;
      *(float *)(pcVar5 + 0x1c) = (pfVar7[-2] * 480.0) / 640.0;
      *(float *)(pcVar5 + 0x20) = ((pfVar7[-1] * 320.0) / 480.0 - 240.0) * 0.93 + 250.0;
      pcVar5 = pcVar5 + 8;
      pfVar3 = pfVar7 + 2;
    } while (iVar11 < iVar12);
  }
  iVar12 = iVar12 * 5;
  *(int *)(this + 0x18) = iVar12;
  if (-1 < iVar12) {
    iVar11 = 0;
    pcVar5 = this;
    do {
      iVar11 = iVar11 + 1;
      *(float *)(pcVar5 + 0x6c) = (*pfVar7 * 480.0) / 640.0;
      pfVar3 = pfVar7 + 1;
      pfVar7 = pfVar7 + 2;
      *(float *)(pcVar5 + 0x70) = ((*pfVar3 * 320.0) / 480.0 - 240.0) * 0.93 + 250.0;
      pcVar5 = pcVar5 + 8;
    } while (iVar11 <= iVar12);
  }
  *(int *)(this + 0x8e24) = Game + 0x718a0;
  if (param_1 == 0) {
    pvVar4 = (void *)RShellMemoryScratch();
    local_110 = (char *)RShellLoadFile("Galaxy/_Galaxy.txt",pvVar4,(int *)0x0);
  }
  else if (param_1 == 1) {
    pvVar4 = (void *)RShellMemoryScratch();
    local_110 = (char *)RShellLoadFile("Galaxy/_GalaxyPro.txt",pvVar4,(int *)0x0);
  }
  if (0 < *(int *)(this + 0x14)) {
    pcVar5 = this + 0x8880;
    local_124 = 0;
    local_128 = 0;
    local_11c = this;
    do {
      sprintf(acStack_74,"Galaxy%i:",local_128);
      local_f8 = (cRGalaxy *)Rstrfind(acStack_74,local_110);
      if (local_f8 == (cRGalaxy *)0x0) {
        RShellError("Cannot find Galaxy %i in _Galaxy.txt",local_128);
        goto LAB_0005b29c;
      }
      iVar12 = Rstrfind(":",(char *)local_f8);
      local_f8 = (cRGalaxy *)(iVar12 + 1);
      if (*(char *)(iVar12 + 1) != '\"') {
        RShellError("missing \" in _Galaxy.txt");
        goto LAB_0005b29c;
      }
      local_f8 = (cRGalaxy *)(iVar12 + 2);
      cVar8 = *(cRGalaxy *)(iVar12 + 2);
      pcVar6 = this + local_128 * 0xa0 + 0x87e4;
      if (cVar8 != (cRGalaxy)0x22) {
        pcVar10 = pcVar6;
        pcVar2 = (cRGalaxy *)(iVar12 + 3);
        do {
          local_f8 = pcVar2;
          pcVar6 = pcVar10 + 1;
          *pcVar10 = cVar8;
          cVar8 = *local_f8;
          pcVar10 = pcVar6;
          pcVar2 = local_f8 + 1;
        } while (cVar8 != (cRGalaxy)0x22);
      }
      *pcVar6 = (cRGalaxy)0x0;
      local_f8 = (cRGalaxy *)Rstrfind("StarNumber=",(char *)local_f8);
      iVar12 = Rstrfind("=",(char *)local_f8);
      local_f8 = (cRGalaxy *)(iVar12 + 1);
      iVar12 = Rstrint((char **)&local_f8);
      *(undefined4 *)(pcVar5 + -0x10) = 0x3f800000;
      *(undefined4 *)(pcVar5 + -0x18) = 0x3f800000;
      *(undefined4 *)(pcVar5 + -0x14) = 0x3f800000;
      *(undefined4 *)(pcVar5 + -0xc) = 0x3f4ccccd;
      *(undefined4 *)(pcVar5 + -8) = *(undefined4 *)(local_11c + 0x1c);
      uVar13 = *(undefined4 *)(local_11c + 0x20);
      *(undefined4 *)pcVar5 = 0;
      *(undefined4 *)(pcVar5 + -4) = uVar13;
      *(int *)(pcVar5 + -0x1c) = iVar12;
      if (0 < iVar12) {
        pcVar10 = this + local_124 * 8 + 0x6c;
        pcVar6 = this + local_124 * 0x2a0 + 0x204;
        iVar12 = 1;
        do {
          *(undefined4 *)(pcVar6 + 0x2ac) = *(undefined4 *)(pcVar10 + 8);
          iVar11 = iVar12 + local_124;
          *(undefined4 *)(pcVar6 + 0x2b0) = *(undefined4 *)(pcVar10 + 0xc);
          *(int *)(pcVar6 + 0x2a4) = local_128;
          *(undefined4 *)(pcVar6 + 0x2b4) = 0;
          sprintf(acStack_f4,"LEVEL %i MISSING",iVar11);
          pcVar6 = pcVar6 + 0x2a0;
          pcVar10 = pcVar10 + 8;
          Rstrcpy((char *)(this + iVar11 * 0x2a0 + 0x224),acStack_f4);
          Rstrcpy((char *)(this + iVar11 * 0x2a0 + 0x2a4),acStack_f4);
          bVar1 = iVar12 < *(int *)(pcVar5 + -0x1c);
          iVar12 = iVar12 + 1;
        } while (bVar1);
      }
      pcVar5 = pcVar5 + 0xa0;
      local_128 = local_128 + 1;
      local_124 = local_124 + 5;
      local_11c = local_11c + 8;
    } while (local_128 < *(int *)(this + 0x14));
  }
  this[0x2a4] = (cRGalaxy)0x0;
  *(undefined4 *)(this + 0x210) = *(undefined4 *)(this + 0x6c);
  *(undefined4 *)(this + 0x208) = 0;
  this[0x224] = (cRGalaxy)0x0;
  *(undefined4 *)(this + 0x214) = *(undefined4 *)(this + 0x70);
  *(undefined4 *)(this + 0x218) = 0;
LAB_0005b29c:
  if (local_34 == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}
