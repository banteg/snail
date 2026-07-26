/*
 * mangled: _ZN9cRDirectX8LoadAnimEPcP8cRObject
 * demangled: cRDirectX::LoadAnim(char*, cRObject*)
 * address: 000681f8
 * size: 796
 */

/* cRDirectX::LoadAnim(char*, cRObject*) */

void __thiscall cRDirectX::LoadAnim(cRDirectX *this,char *param_1,cRObject *param_2)

{
  undefined1 uVar1;
  size_t sVar2;
  int iVar3;
  cRObject *pcVar4;
  int iVar5;
  undefined4 uVar6;
  char *pcVar7;
  undefined1 *puVar8;
  cRBod *this_00;
  uint uVar9;
  float fVar10;
  float fVar11;
  undefined4 local_2b4;
  char acStack_2b0 [256];
  char acStack_1b0 [256];
  char acStack_b0 [128];
  int local_30;
  char *local_2c [3];

  _sprintf(acStack_2b0,param_1);
  sVar2 = _strlen(acStack_2b0);
  this_00 = (cRBod *)0x0;
  acStack_2b0[sVar2 - 2] = '\0';
  _sprintf(acStack_1b0,"Data/O_%s.smo",acStack_2b0);
  iVar3 = RShellFindFile(acStack_1b0,false);
  if (iVar3 == 0) {
    _strcpy(acStack_1b0,param_1);
    local_2c[0] = acStack_1b0;
    iVar3 = Rstrfind("-",acStack_1b0);
    local_2c[0] = (char *)(iVar3 + 1);
    iVar3 = Rstrfind("-",local_2c[0]);
    *(undefined1 *)(iVar3 + 1) = 0x2a;
    *(undefined1 *)(iVar3 + 2) = 0x2e;
    *(undefined1 *)(iVar3 + 3) = 0x78;
    *(undefined1 *)(iVar3 + 4) = 0;
    local_2c[0] = (char *)(iVar3 + 5);
    RShellReadDirectory("X",acStack_1b0,&local_30,&_gAnimDirectory);
    local_2b4 = (cRBod *)RShellMemoryMalloc(local_30 * 0x74,"Anim Key frame bods");
    *(undefined4 *)(this + 0x5808) = 0;
    if (0 < local_30) {
      iVar3 = 0;
      this_00 = local_2b4;
      do {
        pcVar4 = (cRObject *)cRObjects::Add((cRObjects *)PTR__gObjectList_001b61cc);
        cRBod::SetObject(this_00,pcVar4);
        iVar5 = iVar3 * 0x80;
        Load(this,&_gAnimDirectory + iVar5,*(cRObject **)(this_00 + 0x24),0);
        iVar3 = iVar3 + 1;
        **(uint **)(this_00 + 0x24) = **(uint **)(this_00 + 0x24) | 0x2000000;
        local_2c[0] = &_gAnimDirectory + iVar5;
        iVar5 = Rstrfind("-",&_gAnimDirectory + iVar5);
        local_2c[0] = (char *)(iVar5 + 1);
        iVar5 = Rstrfind("-",local_2c[0]);
        local_2c[0] = (char *)(iVar5 + 1);
        uVar6 = Rstrint(local_2c);
        *(undefined4 *)(this_00 + 0x70) = uVar6;
        this_00 = this_00 + 0x74;
      } while (iVar3 < local_30);
    }
    Load(this,&_gAnimDirectory,param_2,0);
    cRObject::RequestVerticesCopy(param_2);
    *(uint *)param_2 = *(uint *)param_2 | 0x800000;
    _sprintf(acStack_b0,"Anim:%s",param_1);
    pcVar7 = (char *)Rstrfind(acStack_b0,*(char **)this);
    if (pcVar7 == (char *)0x0) {
      RShellError("Did not find Anim:%s in _Animation.txt. Using defaults",param_1);
      fVar11 = 0.016666668;
      uVar9 = (uint)this_00 | 1;
    }
    else {
      puVar8 = (undefined1 *)Rstrfind("AnimEnd:",pcVar7);
      if (puVar8 == (undefined1 *)0x0) {
        RShellError("Cannot find AnimEnd: for %s \n",param_1);
        return;
      }
      uVar1 = *puVar8;
      *puVar8 = 0;
      local_2c[0] = (char *)Rstrfind("Duration:",pcVar7);
      if (local_2c[0] == (char *)0x0) {
        fVar11 = 0.016666668;
        local_2c[0] = (char *)0x0;
      }
      else {
        iVar3 = Rstrfind(":",local_2c[0]);
        local_2c[0] = (char *)(iVar3 + 1);
        fVar11 = (float)Rstrfloat(local_2c);
        if (fVar11 == 0.0) {
          fVar11 = 0.0;
        }
        else {
          fVar11 = 1.0 / (fVar11 * 60.0);
        }
      }
      local_2c[0] = (char *)Rstrfind("Mode:Loop",pcVar7);
      uVar9 = (uint)(local_2c[0] != (char *)0x0);
      local_2c[0] = (char *)Rstrfind("Mode:Once",pcVar7);
      if (local_2c[0] != (char *)0x0) {
        uVar9 = uVar9 | 4;
      }
      local_2c[0] = (char *)Rstrfind("Mode:Pingpong",pcVar7);
      if (local_2c[0] != (char *)0x0) {
        uVar9 = uVar9 | 2;
      }
      *puVar8 = uVar1;
    }
    fVar10 = 1.0;
    if (local_30 != 1) {
      fVar10 = fVar11;
    }
    cRObject::RequestAnim(param_2,local_30,(cRBodPos *)local_2b4,fVar10,uVar9);
  }
  else {
    *(uint *)param_2 = *(uint *)param_2 | 0x1000;
    cRObject::Load(param_2,acStack_1b0);
  }
  return;
}
