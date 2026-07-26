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
  size_t sVar2;
  int iVar3;
  cRBodPos *pcVar4;
  cRObject *pcVar5;
  int iVar6;
  undefined4 uVar7;
  undefined1 *puVar8;
  float fVar9;
  cRBodPos *this_00;
  char *pcVar10;
  float extraout_s0;
  float fVar11;
  float fVar12;
  int local_2bc;
  undefined4 local_2b8;
  char acStack_2b4 [256];
  char acStack_1b4 [256];
  char acStack_b4 [128];
  int local_34;

  local_34 = __stack_chk_guard;
  sprintf(acStack_2b4,param_1);
  sVar2 = strlen(acStack_2b4);
  acStack_2b4[sVar2 - 2] = '\0';
  sprintf(acStack_1b4,"Data/O_%s.smo",acStack_2b4);
  iVar3 = RShellFindFile(acStack_1b4,false);
  if (iVar3 == 0) {
    strcpy(acStack_1b4,param_1);
    local_2b8 = acStack_1b4;
    iVar3 = Rstrfind("-",acStack_1b4);
    local_2b8 = (char *)(iVar3 + 1);
    iVar3 = Rstrfind("-",local_2b8);
    *(undefined1 *)(iVar3 + 1) = 0x2a;
    *(undefined1 *)(iVar3 + 2) = 0x2e;
    *(undefined1 *)(iVar3 + 3) = 0x78;
    *(undefined1 *)(iVar3 + 4) = 0;
    local_2b8 = (char *)(iVar3 + 5);
    RShellReadDirectory("X",acStack_1b4,&local_2bc,&gAnimDirectory);
    pcVar4 = (cRBodPos *)RShellMemoryMalloc(local_2bc * 0x74,"Anim Key frame bods");
    *(undefined4 *)(this + 0x5808) = 0;
    if (0 < local_2bc) {
      iVar3 = 0;
      this_00 = pcVar4;
      do {
        pcVar5 = (cRObject *)cRObjects::Add((cRObjects *)gObjectList);
        cRBod::SetObject((cRBod *)this_00,pcVar5);
        pcVar10 = &gAnimDirectory + iVar3 * 0x80;
        iVar3 = iVar3 + 1;
        Load(this,pcVar10,*(cRObject **)(this_00 + 0x24),0);
        **(uint **)(this_00 + 0x24) = **(uint **)(this_00 + 0x24) | 0x2000000;
        local_2b8 = pcVar10;
        iVar6 = Rstrfind("-",pcVar10);
        local_2b8 = (char *)(iVar6 + 1);
        iVar6 = Rstrfind("-",local_2b8);
        local_2b8 = (char *)(iVar6 + 1);
        uVar7 = Rstrint((char **)&local_2b8);
        *(undefined4 *)(this_00 + 0x70) = uVar7;
        this_00 = this_00 + 0x74;
      } while (iVar3 < local_2bc);
    }
    Load(this,&gAnimDirectory,param_2,0);
    cRObject::RequestVerticesCopy(param_2);
    *(uint *)param_2 = *(uint *)param_2 | 0x800000;
    sprintf(acStack_b4,"Anim:%s",param_1);
    pcVar10 = (char *)Rstrfind(acStack_b4,*(char **)this);
    if (pcVar10 == (char *)0x0) {
      fVar12 = 0.016666668;
      fVar9 = (float)RShellError("Did not find Anim:%s in _Animation.txt. Using defaults",param_1);
    }
    else {
      puVar8 = (undefined1 *)Rstrfind("AnimEnd:",pcVar10);
      if (puVar8 == (undefined1 *)0x0) {
        RShellError("Cannot find AnimEnd: for %s \n",param_1);
        goto LAB_00089378;
      }
      uVar1 = *puVar8;
      *puVar8 = 0;
      local_2b8 = (char *)Rstrfind("Duration:",pcVar10);
      if (local_2b8 == (char *)0x0) {
        fVar12 = 0.016666668;
        local_2b8 = (char *)0x0;
      }
      else {
        iVar3 = Rstrfind(":",local_2b8);
        local_2b8 = (char *)(iVar3 + 1);
        fVar9 = (float)Rstrfloat((char **)&local_2b8);
        if (fVar9 == 0.0) {
          fVar12 = 0.0;
        }
        else {
          fVar12 = 1.0 / (fVar9 * 60.0);
        }
      }
      local_2b8 = (char *)Rstrfind("Mode:Loop",pcVar10);
      local_2b8 = (char *)Rstrfind("Mode:Once",pcVar10);
      local_2b8 = (char *)Rstrfind("Mode:Pingpong",pcVar10);
      *puVar8 = uVar1;
      fVar9 = extraout_s0;
    }
    fVar11 = 1.0;
    if (local_2bc != 1) {
      fVar11 = fVar12;
    }
    cRObject::RequestAnim(param_2,local_2bc,pcVar4,fVar9,(int)fVar11);
  }
  else {
    *(uint *)param_2 = *(uint *)param_2 | 0x1000;
    cRObject::Load(param_2,acStack_1b4);
  }
LAB_00089378:
  if (local_34 != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}
