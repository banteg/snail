/*
 * mangled: _ZN18cRLandscapeManager6ImportEPc
 * demangled: cRLandscapeManager::Import(char*)
 * address: 00063424
 * size: 1676
 */

/* cRLandscapeManager::Import(char*) */

int __thiscall cRLandscapeManager::Import(cRLandscapeManager *this,char *param_1)

{
  int iVar1;
  char *pcVar2;
  undefined4 uVar3;
  char *pcVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  char cVar8;
  char *pcVar9;
  uint in_fpscr;
  float fVar10;
  float fVar11;
  char local_630 [512];
  char local_430 [4];
  char local_42c [508];
  char acStack_230 [512];
  int local_30;
  char *local_2c [3];

  _sprintf(acStack_230,"Backgrounds/%s",param_1);
  if (0 < *(int *)this) {
    iVar5 = 0;
    do {
      iVar1 = Rstrcmp((char *)(this + iVar5 * 0x1ac + 8),param_1);
      if (iVar1 != 0) {
        return iVar5;
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < *(int *)this);
  }
  pcVar2 = (char *)RShellLoadFile(acStack_230,&local_30);
  pcVar2[local_30 + -1] = '\0';
  if (pcVar2 == (char *)0x0) {
    RShellError("Landscape.Cannot load %s",acStack_230);
    iVar5 = 0;
  }
  else {
    Rstrcpy((char *)(this + *(int *)this * 0x1ac + 8),param_1);
    local_2c[0] = (char *)Rstrfind("ID:",pcVar2);
    if (local_2c[0] == (char *)0x0) {
      RShellError("Landscape. Cannot find ID: %s",acStack_230);
      *(undefined4 *)(this + *(int *)this * 0x1ac + 4) = 0;
    }
    else {
      local_2c[0] = (char *)Rstrfind(":",local_2c[0]);
      iVar5 = *(int *)this;
      uVar3 = Rstrint(local_2c);
      *(undefined4 *)(this + iVar5 * 0x1ac + 4) = uVar3;
    }
    *(int *)(this + *(int *)this * 0x1ac + 4) = *(int *)this;
    local_2c[0] = (char *)Rstrfind("Fog:",pcVar2);
    if (local_2c[0] == (char *)0x0) {
      RShellError("Landscape. Cannot find Fog: %s",acStack_230);
      tColour::Black((tColour *)(this + *(int *)this * 0x1ac + 400));
    }
    else {
      local_2c[0] = (char *)Rstrfind(":",local_2c[0]);
      fVar11 = 255.0;
      iVar5 = *(int *)this;
      uVar3 = Rstrint(local_2c);
      fVar10 = (float)VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x16) & 3);
      *(float *)(this + iVar5 * 0x1ac + 400) = fVar10 / fVar11;
      iVar5 = *(int *)this;
      uVar3 = Rstrint(local_2c);
      fVar10 = (float)VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x16) & 3);
      *(float *)(this + iVar5 * 0x1ac + 0x194) = fVar10 / fVar11;
      iVar5 = *(int *)this;
      uVar3 = Rstrint(local_2c);
      fVar10 = (float)VectorSignedToFloat(uVar3,(byte)(in_fpscr >> 0x16) & 3);
      *(float *)(this + iVar5 * 0x1ac + 0x198) = fVar10 / fVar11;
    }
    local_2c[0] = (char *)Rstrfind("Picture:",pcVar2);
    if (local_2c[0] == (char *)0x0) {
      RShellError("Landscape. Cannot find Picture: in %s",acStack_230);
    }
    else {
      iVar5 = Rstrfind(":",local_2c[0]);
      pcVar9 = (char *)(iVar5 + 1);
      cVar8 = *(char *)(iVar5 + 1);
      if (cVar8 == '.') {
        pcVar6 = local_430;
        pcVar4 = local_430 + 1;
        pcVar7 = local_42c;
      }
      else {
        pcVar7 = (char *)(iVar5 + 2);
        pcVar4 = local_430 + 1;
        do {
          pcVar6 = pcVar4;
          pcVar9 = pcVar7;
          pcVar6[-1] = cVar8;
          cVar8 = *pcVar9;
          pcVar4 = pcVar6 + 1;
          pcVar7 = pcVar9 + 1;
        } while (cVar8 != '.');
        pcVar7 = pcVar6 + 4;
      }
      *pcVar6 = '.';
      *pcVar4 = pcVar9[1];
      pcVar6[2] = pcVar9[2];
      pcVar6[3] = pcVar9[3];
      local_2c[0] = pcVar9 + 4;
      *pcVar7 = '\0';
      _sprintf((char *)(this + *(int *)this * 0x1ac + 0x8c),"Backgrounds/%s");
      *(undefined4 *)(this + *(int *)this * 0x1ac + 0x88) = 7;
      wprintf("Loading backdrop texture %s\n",this + *(int *)this * 0x1ac + 0x8c);
    }
    local_2c[0] = (char *)Rstrfind("Portrait:",pcVar2);
    if (local_2c[0] == (char *)0x0) {
      this[*(int *)this * 0x1ac + 0x10c] = (cRLandscapeManager)0x0;
      local_2c[0] = (char *)0x0;
    }
    else {
      iVar5 = Rstrfind(":",local_2c[0]);
      pcVar9 = (char *)(iVar5 + 1);
      cVar8 = *(char *)(iVar5 + 1);
      if (cVar8 == '.') {
        pcVar6 = local_430;
        pcVar4 = local_430 + 1;
        pcVar7 = local_42c;
      }
      else {
        pcVar7 = (char *)(iVar5 + 2);
        pcVar4 = local_430 + 1;
        do {
          pcVar6 = pcVar4;
          pcVar9 = pcVar7;
          pcVar6[-1] = cVar8;
          cVar8 = *pcVar9;
          pcVar4 = pcVar6 + 1;
          pcVar7 = pcVar9 + 1;
        } while (cVar8 != '.');
        pcVar7 = pcVar6 + 4;
      }
      *pcVar6 = '.';
      *pcVar4 = pcVar9[1];
      pcVar6[2] = pcVar9[2];
      pcVar6[3] = pcVar9[3];
      local_2c[0] = pcVar9 + 4;
      *pcVar7 = '\0';
      _sprintf((char *)(this + *(int *)this * 0x1ac + 0x10d),"Backgrounds/%s");
      this[*(int *)this * 0x1ac + 0x10c] = (cRLandscapeManager)0x1;
      RShellFindFile((char *)(this + *(int *)this * 0x1ac + 0x10d),false);
      wprintf("Loading backdrop Portrait texture %s\n",this + *(int *)this * 0x1ac + 0x10d);
    }
    local_2c[0] = (char *)Rstrfind("Landscape:",pcVar2);
    if (local_2c[0] == (char *)0x0) {
      RShellError("Landscape. Cannot find Landscape: in %s",acStack_230);
    }
    else {
      iVar5 = Rstrfind(":",local_2c[0]);
      local_2c[0] = (char *)(iVar5 + 1);
      cVar8 = *(char *)(iVar5 + 1);
      if (' ' < cVar8) {
        if (cVar8 == '.') {
          pcVar4 = local_630;
          pcVar9 = local_630 + 1;
        }
        else {
          pcVar6 = (char *)(iVar5 + 2);
          pcVar9 = local_630 + 1;
          do {
            pcVar4 = pcVar9;
            pcVar7 = pcVar6;
            pcVar4[-1] = cVar8;
            cVar8 = *pcVar7;
            pcVar9 = pcVar4 + 1;
            pcVar6 = pcVar7 + 1;
            local_2c[0] = pcVar7;
          } while (cVar8 != '.');
        }
        *pcVar4 = '.';
        *pcVar9 = 'x';
        pcVar4[2] = '\0';
      }
    }
    local_2c[0] = (char *)Rstrfind("Distort:",pcVar2);
    if (local_2c[0] == (char *)0x0) {
      RShellError("Landscape. Cannot find Distort: in %s",acStack_230);
    }
    else {
      iVar5 = Rstrfind(":",local_2c[0]);
      local_2c[0] = (char *)(iVar5 + 1);
      iVar5 = *(int *)this;
      uVar3 = Rstrfloat(local_2c);
      *(undefined4 *)(this + iVar5 * 0x1ac + 0x1a0) = uVar3;
    }
    local_2c[0] = (char *)Rstrfind("Width:",pcVar2);
    if (local_2c[0] == (char *)0x0) {
      RShellError("Landscape. Cannot find Width: in %s",acStack_230);
    }
    else {
      iVar5 = Rstrfind(":",local_2c[0]);
      local_2c[0] = (char *)(iVar5 + 1);
      iVar5 = *(int *)this;
      uVar3 = Rstrfloat(local_2c);
      *(undefined4 *)(this + iVar5 * 0x1ac + 0x1a4) = uVar3;
    }
    local_2c[0] = (char *)Rstrfind("Height:",pcVar2);
    if (local_2c[0] == (char *)0x0) {
      RShellError("Landscape. Cannot find Height: in %s",acStack_230);
    }
    else {
      iVar5 = Rstrfind(":",local_2c[0]);
      local_2c[0] = (char *)(iVar5 + 1);
      iVar5 = *(int *)this;
      uVar3 = Rstrfloat(local_2c);
      *(undefined4 *)(this + iVar5 * 0x1ac + 0x1a8) = uVar3;
    }
    local_2c[0] = (char *)Rstrfind("Menu:Yes",pcVar2);
    if (local_2c[0] == (char *)0x0) {
      this[*(int *)this * 0x1ac + 0x1ac] = (cRLandscapeManager)0x0;
    }
    else {
      this[*(int *)this * 0x1ac + 0x1ac] = (cRLandscapeManager)0x1;
    }
    *(int *)this = *(int *)this + 1;
    RShellMemoryFree(pcVar2);
    wprintf("Landscape: %s imported\n",param_1);
    iVar5 = *(int *)this + -1;
  }
  return iVar5;
}
