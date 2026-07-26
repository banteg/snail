/*
 * mangled: _ZN8cRGalaxy4OpenEi
 * demangled: cRGalaxy::Open(int)
 * address: 000687c8
 * size: 1008
 */

/* cRGalaxy::Open(int) */

void __thiscall cRGalaxy::Open(cRGalaxy *this,int param_1)

{
  bool bVar1;
  int iVar2;
  void *pvVar3;
  float *pfVar4;
  cRGalaxy *pcVar5;
  cRGalaxy *pcVar6;
  cRGalaxy cVar7;
  float *pfVar8;
  cRGalaxy *pcVar9;
  cRGalaxy *pcVar10;
  int iVar11;
  char *local_f4;
  int local_f0;
  cRGalaxy *local_ec;
  int local_e8;
  char acStack_e4 [128];
  char acStack_64 [64];
  cRGalaxy *local_24;

  pfVar8 = (float *)0x0;
  *(undefined4 *)this = 0;
  this[8] = (cRGalaxy)0x0;
  if (param_1 == 0) {
    pfVar8 = (float *)&_gUniverse0;
  }
  else if (param_1 == 1) {
    pfVar8 = (float *)&_gUniverse1;
  }
  pfVar4 = pfVar8 + 1;
  iVar11 = (int)*pfVar8;
  *(int *)(this + 0x14) = iVar11;
  if (0 < iVar11) {
    iVar2 = 0;
    pfVar8 = pfVar8 + 3;
    pcVar10 = this;
    do {
      pfVar4 = pfVar8;
      iVar2 = iVar2 + 1;
      *(float *)(pcVar10 + 0x1c) = (pfVar4[-2] * 480.0) / 640.0;
      *(float *)(pcVar10 + 0x20) = ((pfVar4[-1] * 320.0) / 480.0 - 240.0) * 0.93 + 250.0;
      pcVar10 = pcVar10 + 8;
      pfVar8 = pfVar4 + 2;
    } while (iVar2 < iVar11);
  }
  iVar11 = iVar11 * 5;
  *(int *)(this + 0x18) = iVar11;
  if (0 < iVar11 + 1) {
    iVar2 = 0;
    pcVar10 = this;
    do {
      iVar2 = iVar2 + 1;
      *(float *)(pcVar10 + 0x6c) = (*pfVar4 * 480.0) / 640.0;
      pfVar8 = pfVar4 + 1;
      pfVar4 = pfVar4 + 2;
      *(float *)(pcVar10 + 0x70) = ((*pfVar8 * 320.0) / 480.0 - 240.0) * 0.93 + 250.0;
      pcVar10 = pcVar10 + 8;
    } while (iVar2 < iVar11 + 1);
  }
  *(int *)(this + 0x8e24) = *(int *)PTR__Game_001b60b8 + 0x72b78;
  if (param_1 == 0) {
    pvVar3 = (void *)RShellMemoryScratch();
    local_f4 = (char *)RShellLoadFile("Galaxy/_Galaxy.txt",pvVar3,(int *)0x0);
  }
  else if (param_1 == 1) {
    pvVar3 = (void *)RShellMemoryScratch();
    local_f4 = (char *)RShellLoadFile("Galaxy/_GalaxyPro.txt",pvVar3,(int *)0x0);
  }
  if (0 < *(int *)(this + 0x14)) {
    pcVar10 = this + 0x8868;
    local_e8 = 0;
    local_f0 = 0;
    local_ec = this;
    do {
      _sprintf(acStack_64,"Galaxy%i:");
      local_24 = (cRGalaxy *)Rstrfind(acStack_64,local_f4);
      if (local_24 == (cRGalaxy *)0x0) {
        RShellError("Cannot find Galaxy %i in _Galaxy.txt",local_e8);
        return;
      }
      iVar11 = Rstrfind(":",(char *)local_24);
      local_24 = (cRGalaxy *)(iVar11 + 1);
      if (*(char *)(iVar11 + 1) != '\"') {
        RShellError("missing \" in _Galaxy.txt");
        return;
      }
      local_24 = (cRGalaxy *)(iVar11 + 2);
      pcVar5 = this + local_e8 * 0xa0 + 0x87e4;
      cVar7 = *(cRGalaxy *)(iVar11 + 2);
      if (cVar7 != (cRGalaxy)0x22) {
        pcVar9 = (cRGalaxy *)(iVar11 + 3);
        pcVar6 = pcVar5;
        do {
          local_24 = pcVar9;
          pcVar5 = pcVar6 + 1;
          *pcVar6 = cVar7;
          cVar7 = *local_24;
          pcVar9 = local_24 + 1;
          pcVar6 = pcVar5;
        } while (cVar7 != (cRGalaxy)0x22);
      }
      *pcVar5 = (cRGalaxy)0x0;
      local_24 = (cRGalaxy *)Rstrfind("StarNumber=",(char *)local_24);
      iVar11 = Rstrfind("=",(char *)local_24);
      local_24 = (cRGalaxy *)(iVar11 + 1);
      iVar11 = Rstrint((char **)&local_24);
      *(undefined4 *)pcVar10 = 0x3f800000;
      *(undefined4 *)(pcVar10 + 4) = 0x3f800000;
      *(undefined4 *)(pcVar10 + 8) = 0x3f800000;
      *(undefined4 *)(pcVar10 + 0xc) = 0x3f4ccccd;
      *(int *)(pcVar10 + -4) = iVar11;
      *(undefined4 *)(pcVar10 + 0x10) = *(undefined4 *)(local_ec + 0x1c);
      *(undefined4 *)(pcVar10 + 0x14) = *(undefined4 *)(local_ec + 0x20);
      *(undefined4 *)(pcVar10 + 0x18) = 0;
      if (0 < iVar11) {
        pcVar5 = this + local_f0 * 0x2a0 + 0x204;
        pcVar9 = this + local_f0 * 8 + 0x6c;
        iVar11 = 1;
        do {
          *(int *)(pcVar5 + 0x2a4) = local_e8;
          *(undefined4 *)(pcVar5 + 0x2ac) = *(undefined4 *)(pcVar9 + 8);
          pcVar6 = pcVar9 + 0xc;
          pcVar9 = pcVar9 + 8;
          *(undefined4 *)(pcVar5 + 0x2b0) = *(undefined4 *)pcVar6;
          *(undefined4 *)(pcVar5 + 0x2b4) = 0;
          pcVar5 = pcVar5 + 0x2a0;
          _sprintf(acStack_e4,"LEVEL %i MISSING",iVar11 + local_f0);
          iVar2 = (iVar11 + local_f0) * 0x2a0;
          Rstrcpy((char *)(this + iVar2 + 0x224),acStack_e4);
          Rstrcpy((char *)(this + iVar2 + 0x2a4),acStack_e4);
          bVar1 = iVar11 < *(int *)(pcVar10 + -4);
          iVar11 = iVar11 + 1;
        } while (bVar1);
      }
      local_f0 = local_f0 + 5;
      local_e8 = local_e8 + 1;
      local_ec = local_ec + 8;
      pcVar10 = pcVar10 + 0xa0;
    } while (local_e8 < *(int *)(this + 0x14));
  }
  *(undefined4 *)(this + 0x208) = 0;
  *(undefined4 *)(this + 0x210) = *(undefined4 *)(this + 0x6c);
  this[0x224] = (cRGalaxy)0x0;
  this[0x2a4] = (cRGalaxy)0x0;
  *(undefined4 *)(this + 0x214) = *(undefined4 *)(this + 0x70);
  *(undefined4 *)(this + 0x218) = 0;
  return;
}
