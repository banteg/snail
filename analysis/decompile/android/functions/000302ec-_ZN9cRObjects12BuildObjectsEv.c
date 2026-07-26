/*
 * mangled: _ZN9cRObjects12BuildObjectsEv
 * demangled: cRObjects::BuildObjects()
 * address: 000302ec
 * size: 492
 */

/* cRObjects::BuildObjects() */

void __thiscall cRObjects::BuildObjects(cRObjects *this)

{
  cRObject *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  char *pcVar8;
  char *pcVar9;

  iVar5 = DAT_000304d8 + 0x30308;
  wprintf((char *)(iVar5 + DAT_000304dc),*(undefined4 *)this);
  iVar2 = DAT_000304e8;
  if (0 < *(int *)this) {
    iVar6 = 0;
    uVar7 = 0;
    pcVar8 = (char *)(iVar5 + DAT_000304e0);
    pcVar9 = (char *)(iVar5 + DAT_000304e4);
    do {
      while( true ) {
        if ((uVar7 & 3) == 0) {
          cRLoadingBar::Signal(*(cRLoadingBar **)(iVar5 + iVar2));
          iVar3 = *(int *)(this + 8);
          iVar4 = *(int *)(iVar3 + iVar6);
        }
        else {
          iVar3 = *(int *)(this + 8);
          iVar4 = *(int *)(iVar3 + iVar6);
        }
        if (iVar4 < 0) {
          wprintf(pcVar8);
          iVar3 = *(int *)(this + 8);
        }
        pcVar1 = (cRObject *)(iVar3 + iVar6);
        if ((*(int *)(pcVar1 + 0xa0) != 0) && ((*(uint *)pcVar1 & 0x2000000) == 0)) {
          ObjectProcJoinTextures(pcVar1);
          cRObject::CalcTextureGroups((cRObject *)(*(int *)(this + 8) + iVar6));
          cRObject::BuildGLVertexArray((cRObject *)(*(int *)(this + 8) + iVar6));
          pcVar1 = (cRObject *)(*(int *)(this + 8) + iVar6);
          if ((*(uint *)(*(int *)(this + 8) + iVar6) & 0x4000) != 0) {
            cRObject::CalcFaceQuadNormals(pcVar1);
            cRObject::CalcEdges((cRObject *)(*(int *)(this + 8) + iVar6));
            pcVar1 = (cRObject *)(*(int *)(this + 8) + iVar6);
          }
        }
        cRObject::Save(pcVar1);
        pcVar1 = (cRObject *)(*(int *)(this + 8) + iVar6);
        if ((-1 < *(int *)(*(int *)(this + 8) + iVar6)) || (*(int *)(pcVar1 + 200) == 0)) break;
        wprintf(pcVar9,*(int *)(*(int *)(pcVar1 + 200) + 0xc) + 0xc);
        pcVar1 = (cRObject *)(*(int *)(this + 8) + iVar6);
        if ((*(uint *)pcVar1 & 0x10000200) != 0x10000000) goto LAB_00030394;
LAB_0003041c:
        cRObject::GLVBO(pcVar1);
        uVar7 = uVar7 + 1;
        iVar6 = iVar6 + 0x110;
        if (*(int *)this <= (int)uVar7) goto LAB_00030434;
      }
      if ((*(uint *)pcVar1 & 0x10000200) == 0x10000000) goto LAB_0003041c;
LAB_00030394:
      uVar7 = uVar7 + 1;
      iVar6 = iVar6 + 0x110;
    } while ((int)uVar7 < *(int *)this);
  }
LAB_00030434:
  pcVar8 = (char *)(iVar5 + DAT_000304ec);
  iVar2 = RShellFindFile(pcVar8,false);
  if (iVar2 == 0) {
    RShellSaveFile(pcVar8,*(void **)(this + 0x10),*(int *)(this + 0xc) * 0xc);
  }
  GLObjectVBOEnd();
  cRResourceManager::Add(*(cRResourceManager **)(iVar5 + DAT_000304f0),4,0,iVar5 + DAT_000304f4);
  return;
}
