/*
 * mangled: _ZN18cRLandscapeManager6ImportEPc
 * demangled: cRLandscapeManager::Import(char*)
 * address: 000681c4
 * size: 1976
 */

/* cRLandscapeManager::Import(char*) */

void __thiscall cRLandscapeManager::Import(cRLandscapeManager *this,char *param_1)

{
  char *pcVar1;
  byte *pbVar2;
  int iVar3;
  char *pcVar4;
  undefined4 uVar5;
  char cVar6;
  cRLandscapeManager extraout_r1;
  cRLandscapeManager cVar7;
  char *pcVar8;
  byte *pbVar9;
  byte *pbVar10;
  byte bVar11;
  char *pcVar12;
  int iVar13;
  char *pcVar14;
  uint in_fpscr;
  float fVar15;
  char *local_65c;
  char *local_650;
  char *local_64c;
  char *local_644;
  int local_63c;
  byte *local_638;
  byte local_634 [512];
  char local_434 [4];
  char local_430 [508];
  char acStack_234 [512];
  int local_34;

  local_34 = __stack_chk_guard;
  sprintf(acStack_234,"Backgrounds/%s",param_1);
  if (0 < *(int *)this) {
    iVar13 = 0;
    do {
      iVar3 = Rstrcmp((char *)(this + iVar13 * 0x1ac + 8),param_1);
      if (iVar3 != 0) goto LAB_0006824c;
      iVar13 = iVar13 + 1;
    } while (iVar13 < *(int *)this);
  }
  pcVar4 = (char *)RShellLoadFile(acStack_234,&local_63c);
  pcVar4[local_63c + -1] = '\0';
  if (pcVar4 == (char *)0x0) {
    RShellError("Landscape.Cannot load %s",acStack_234);
    iVar13 = 0;
  }
  else {
    Rstrcpy((char *)(this + *(int *)this * 0x1ac + 8),param_1);
    local_638 = (byte *)Rstrfind("ID:",pcVar4);
    if (local_638 == (byte *)0x0) {
      RShellError("Landscape. Cannot find ID: %s",acStack_234);
      *(undefined4 *)(this + *(int *)this * 0x1ac + 4) = 0;
    }
    else {
      local_638 = (byte *)Rstrfind(":",(char *)local_638);
      iVar13 = *(int *)this;
      uVar5 = Rstrint((char **)&local_638);
      *(undefined4 *)(this + iVar13 * 0x1ac + 4) = uVar5;
    }
    *(int *)(this + *(int *)this * 0x1ac + 4) = *(int *)this;
    local_638 = (byte *)Rstrfind("Fog:",pcVar4);
    if (local_638 == (byte *)0x0) {
      RShellError("Landscape. Cannot find Fog: %s",acStack_234);
      tColour::Black();
    }
    else {
      local_638 = (byte *)Rstrfind(":",(char *)local_638);
      iVar13 = *(int *)this;
      uVar5 = Rstrint((char **)&local_638);
      fVar15 = (float)VectorSignedToFloat(uVar5,(byte)(in_fpscr >> 0x16) & 3);
      *(float *)(this + iVar13 * 0x1ac + 400) = fVar15 / 255.0;
      iVar13 = *(int *)this;
      uVar5 = Rstrint((char **)&local_638);
      fVar15 = (float)VectorSignedToFloat(uVar5,(byte)(in_fpscr >> 0x16) & 3);
      *(float *)(this + iVar13 * 0x1ac + 0x194) = fVar15 / 255.0;
      iVar13 = *(int *)this;
      uVar5 = Rstrint((char **)&local_638);
      fVar15 = (float)VectorSignedToFloat(uVar5,(byte)(in_fpscr >> 0x16) & 3);
      *(float *)(this + iVar13 * 0x1ac + 0x198) = fVar15 / 255.0;
    }
    local_638 = (byte *)Rstrfind("Picture:",pcVar4);
    if (local_638 == (byte *)0x0) {
      RShellError("Landscape. Cannot find Picture: in %s",acStack_234);
    }
    else {
      iVar13 = Rstrfind(":",(char *)local_638);
      pcVar8 = (char *)(iVar13 + 1);
      cVar6 = *(char *)(iVar13 + 1);
      if (cVar6 == '.') {
        local_64c = local_430;
        pcVar12 = local_434;
        pcVar14 = local_434 + 1;
      }
      else {
        pcVar1 = (char *)(iVar13 + 2);
        pcVar14 = local_434 + 1;
        do {
          pcVar12 = pcVar14;
          pcVar8 = pcVar1;
          pcVar12[-1] = cVar6;
          cVar6 = *pcVar8;
          pcVar14 = pcVar12 + 1;
          pcVar1 = pcVar8 + 1;
        } while (cVar6 != '.');
        local_64c = pcVar12 + 4;
      }
      local_650 = pcVar12 + 3;
      local_65c = pcVar12 + 2;
      *pcVar12 = '.';
      local_638 = (byte *)(pcVar8 + 4);
      *pcVar14 = pcVar8[1];
      *local_65c = pcVar8[2];
      *local_650 = pcVar8[3];
      *local_64c = '\0';
      sprintf((char *)(this + *(int *)this * 0x1ac + 0x8c),"Backgrounds/%s",local_434);
      *(undefined4 *)(this + *(int *)this * 0x1ac + 0x88) = 7;
      wprintf("Found backdrop texture %s\n",this + *(int *)this * 0x1ac + 0x8c);
    }
    local_638 = (byte *)Rstrfind("Portrait:",pcVar4);
    if (local_638 == (byte *)0x0) {
      this[*(int *)this * 0x1ac + 0x10c] = (cRLandscapeManager)0x0;
      local_638 = (byte *)0x0;
    }
    else {
      iVar13 = Rstrfind(":",(char *)local_638);
      pcVar8 = (char *)(iVar13 + 1);
      cVar6 = *(char *)(iVar13 + 1);
      if (cVar6 == '.') {
        local_644 = local_430;
        pcVar12 = local_434;
        pcVar14 = local_434 + 1;
      }
      else {
        pcVar14 = local_434 + 1;
        do {
          pcVar12 = pcVar14;
          pcVar8 = pcVar8 + 1;
          pcVar12[-1] = cVar6;
          cVar6 = *pcVar8;
          pcVar14 = pcVar12 + 1;
        } while (cVar6 != '.');
        local_644 = pcVar12 + 4;
      }
      local_650 = pcVar12 + 3;
      *pcVar12 = '.';
      local_638 = (byte *)(pcVar8 + 4);
      *pcVar14 = pcVar8[1];
      pcVar12[2] = pcVar8[2];
      *local_650 = pcVar8[3];
      *local_644 = '\0';
      sprintf((char *)(this + *(int *)this * 0x1ac + 0x10d),"Backgrounds/%s",local_434);
      iVar13 = *(int *)this;
      this[iVar13 * 0x1ac + 0x10c] = (cRLandscapeManager)0x1;
      RShellFindFile((char *)(this + iVar13 * 0x1ac + 0x10d),false);
      wprintf("Found backdrop Portrait texture %s\n",this + *(int *)this * 0x1ac + 0x10d);
    }
    local_638 = (byte *)Rstrfind("Landscape:",pcVar4);
    if (local_638 == (byte *)0x0) {
      RShellError("Landscape. Cannot find Landscape: in %s",acStack_234);
    }
    else {
      iVar13 = Rstrfind(":",(char *)local_638);
      local_638 = (byte *)(iVar13 + 1);
      bVar11 = *(byte *)(iVar13 + 1);
      if (0x20 < bVar11) {
        if (bVar11 == 0x2e) {
          pbVar10 = local_634;
          pbVar9 = local_634 + 1;
        }
        else {
          pbVar2 = (byte *)(iVar13 + 2);
          pbVar9 = local_634 + 1;
          do {
            pbVar10 = pbVar9;
            local_638 = pbVar2;
            pbVar10[-1] = bVar11;
            pbVar9 = pbVar10 + 1;
            bVar11 = *local_638;
            pbVar2 = local_638 + 1;
          } while (bVar11 != 0x2e);
        }
        *pbVar10 = 0x2e;
        *pbVar9 = 0x78;
        pbVar10[2] = 0;
      }
    }
    local_638 = (byte *)Rstrfind("Distort:",pcVar4);
    if (local_638 == (byte *)0x0) {
      RShellError("Landscape. Cannot find Distort: in %s",acStack_234);
    }
    else {
      iVar13 = Rstrfind(":",(char *)local_638);
      iVar3 = *(int *)this;
      local_638 = (byte *)(iVar13 + 1);
      uVar5 = Rstrfloat((char **)&local_638);
      *(undefined4 *)(this + iVar3 * 0x1ac + 0x1a0) = uVar5;
    }
    local_638 = (byte *)Rstrfind("Width:",pcVar4);
    if (local_638 == (byte *)0x0) {
      RShellError("Landscape. Cannot find Width: in %s",acStack_234);
    }
    else {
      iVar13 = Rstrfind(":",(char *)local_638);
      iVar3 = *(int *)this;
      local_638 = (byte *)(iVar13 + 1);
      uVar5 = Rstrfloat((char **)&local_638);
      *(undefined4 *)(this + iVar3 * 0x1ac + 0x1a4) = uVar5;
    }
    local_638 = (byte *)Rstrfind("Height:",pcVar4);
    if (local_638 == (byte *)0x0) {
      RShellError("Landscape. Cannot find Height: in %s",acStack_234);
    }
    else {
      iVar13 = Rstrfind(":",(char *)local_638);
      iVar3 = *(int *)this;
      local_638 = (byte *)(iVar13 + 1);
      uVar5 = Rstrfloat((char **)&local_638);
      *(undefined4 *)(this + iVar3 * 0x1ac + 0x1a8) = uVar5;
    }
    local_638 = (byte *)Rstrfind("Menu:Yes",pcVar4);
    if (local_638 != (byte *)0x0) {
      iVar13 = *(int *)this;
      cVar7 = (cRLandscapeManager)0x1;
    }
    else {
      iVar13 = *(int *)this;
      cVar7 = extraout_r1;
    }
    *(int *)this = iVar13 + 1;
    if (local_638 != (byte *)0x0) {
      this[iVar13 * 0x1ac + 0x1ac] = cVar7;
    }
    else {
      this[iVar13 * 0x1ac + 0x1ac] = (cRLandscapeManager)0x0;
    }
    RShellMemoryFree(pcVar4);
    wprintf("Landscape: %s imported\n",param_1);
    iVar13 = *(int *)this + -1;
  }
LAB_0006824c:
  if (local_34 == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(iVar13);
}
