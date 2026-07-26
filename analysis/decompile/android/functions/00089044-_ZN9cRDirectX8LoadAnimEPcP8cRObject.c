/*
 * mangled: _ZN9cRDirectX8LoadAnimEPcP8cRObject
 * demangled: cRDirectX::LoadAnim(char*, cRObject*)
 * address: 00089044
 * size: 948
 */

/* cRDirectX::LoadAnim(char*, cRObject*) */

void __thiscall cRDirectX::LoadAnim(cRDirectX *this,char *param_1,cRObject *param_2)

{
  undefined1 uVar1;
  int iVar2;
  size_t sVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  cRBodPos *pcVar7;
  cRObject *pcVar8;
  undefined4 uVar9;
  undefined1 *puVar10;
  float fVar11;
  char *pcVar12;
  cRObjects *this_00;
  float fVar13;
  cRBodPos *this_01;
  int iVar14;
  char *pcVar15;
  float extraout_s0;
  float fVar16;
  int local_2bc;
  undefined4 local_2b8;
  char acStack_2b4 [256];
  char acStack_1b4 [256];
  char acStack_b4 [128];
  int local_34;

  iVar2 = DAT_0008940c;
  iVar14 = DAT_00089408 + 0x89060;
  local_34 = **(int **)(iVar14 + DAT_0008940c);
  sprintf(acStack_2b4,param_1);
  sVar3 = strlen(acStack_2b4);
  acStack_2b4[sVar3 - 2] = '\0';
  sprintf(acStack_1b4,(char *)(iVar14 + DAT_00089410),acStack_2b4);
  iVar4 = RShellFindFile(acStack_1b4,false);
  if (iVar4 == 0) {
    pcVar15 = (char *)(iVar14 + DAT_00089414);
    strcpy(acStack_1b4,param_1);
    local_2b8 = acStack_1b4;
    iVar5 = Rstrfind(pcVar15,acStack_1b4);
    iVar4 = DAT_00089418;
    local_2b8 = (char *)(iVar5 + 1);
    iVar6 = Rstrfind(pcVar15,local_2b8);
    iVar5 = DAT_0008941c;
    pcVar12 = *(char **)(iVar14 + iVar4);
    *(undefined1 *)(iVar6 + 1) = 0x2a;
    *(undefined1 *)(iVar6 + 2) = 0x2e;
    *(undefined1 *)(iVar6 + 3) = 0x78;
    *(undefined1 *)(iVar6 + 4) = 0;
    local_2b8 = (char *)(iVar6 + 5);
    RShellReadDirectory((char *)(iVar14 + iVar5),acStack_1b4,&local_2bc,pcVar12);
    pcVar7 = (cRBodPos *)RShellMemoryMalloc(local_2bc * 0x74,(char *)(iVar14 + DAT_00089420));
    *(undefined4 *)(this + 0x5808) = 0;
    if (0 < local_2bc) {
      this_00 = *(cRObjects **)(iVar14 + DAT_00089424);
      iVar5 = 0;
      this_01 = pcVar7;
      do {
        pcVar8 = (cRObject *)cRObjects::Add(this_00);
        cRBod::SetObject((cRBod *)this_01,pcVar8);
        pcVar12 = (char *)(*(int *)(iVar14 + iVar4) + iVar5 * 0x80);
        iVar5 = iVar5 + 1;
        Load(this,pcVar12,*(cRObject **)(this_01 + 0x24),0);
        **(uint **)(this_01 + 0x24) = **(uint **)(this_01 + 0x24) | 0x2000000;
        local_2b8 = pcVar12;
        iVar6 = Rstrfind(pcVar15,pcVar12);
        local_2b8 = (char *)(iVar6 + 1);
        iVar6 = Rstrfind(pcVar15,local_2b8);
        local_2b8 = (char *)(iVar6 + 1);
        uVar9 = Rstrint((char **)&local_2b8);
        *(undefined4 *)(this_01 + 0x70) = uVar9;
        this_01 = this_01 + 0x74;
      } while (iVar5 < local_2bc);
    }
    Load(this,*(char **)(iVar14 + iVar4),param_2,0);
    cRObject::RequestVerticesCopy(param_2);
    pcVar12 = (char *)(iVar14 + DAT_00089428);
    *(uint *)param_2 = *(uint *)param_2 | 0x800000;
    sprintf(acStack_b4,pcVar12,param_1);
    pcVar12 = (char *)Rstrfind(acStack_b4,*(char **)this);
    fVar16 = DAT_00089404;
    if (pcVar12 == (char *)0x0) {
      fVar11 = (float)RShellError((char *)(iVar14 + DAT_00089448),param_1);
    }
    else {
      puVar10 = (undefined1 *)Rstrfind((char *)(iVar14 + DAT_0008942c),pcVar12);
      iVar4 = DAT_00089430;
      if (puVar10 == (undefined1 *)0x0) {
        RShellError((char *)(iVar14 + DAT_00089444),param_1);
        goto LAB_00089378;
      }
      uVar1 = *puVar10;
      *puVar10 = 0;
      local_2b8 = (char *)Rstrfind((char *)(iVar14 + iVar4),pcVar12);
      if (local_2b8 == (char *)0x0) {
        local_2b8 = (char *)0x0;
        fVar16 = DAT_00089404;
      }
      else {
        iVar4 = Rstrfind((char *)(iVar14 + DAT_00089434),local_2b8);
        local_2b8 = (char *)(iVar4 + 1);
        fVar11 = (float)Rstrfloat((char **)&local_2b8);
        fVar16 = DAT_00089400;
        if (fVar11 != 0.0) {
          fVar16 = DAT_000893fc / (fVar11 * DAT_000893f8);
        }
      }
      local_2b8 = (char *)Rstrfind((char *)(iVar14 + DAT_00089438),pcVar12);
      local_2b8 = (char *)Rstrfind((char *)(iVar14 + DAT_0008943c),pcVar12);
      local_2b8 = (char *)Rstrfind((char *)(iVar14 + DAT_00089440),pcVar12);
      *puVar10 = uVar1;
      fVar11 = extraout_s0;
    }
    fVar13 = DAT_000893fc;
    if (local_2bc != 1) {
      fVar13 = fVar16;
    }
    cRObject::RequestAnim(param_2,local_2bc,pcVar7,fVar11,(int)fVar13);
  }
  else {
    *(uint *)param_2 = *(uint *)param_2 | 0x1000;
    cRObject::Load(param_2,acStack_1b4);
  }
LAB_00089378:
  if (local_34 != **(int **)(iVar14 + iVar2)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}
