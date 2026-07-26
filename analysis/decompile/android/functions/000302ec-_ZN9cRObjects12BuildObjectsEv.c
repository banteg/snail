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
  uint uVar5;

  wprintf("Build Objects Start %i Objects\n",*(undefined4 *)this);
  if (0 < *(int *)this) {
    iVar4 = 0;
    uVar5 = 0;
    do {
      while( true ) {
        if ((uVar5 & 3) == 0) {
          cRLoadingBar::Signal((cRLoadingBar *)&gLoadingBar);
          iVar2 = *(int *)(this + 8);
          iVar3 = *(int *)(iVar2 + iVar4);
        }
        else {
          iVar2 = *(int *)(this + 8);
          iVar3 = *(int *)(iVar2 + iVar4);
        }
        if (iVar3 < 0) {
          wprintf("Build Objects Debug\n");
          iVar2 = *(int *)(this + 8);
        }
        pcVar1 = (cRObject *)(iVar2 + iVar4);
        if ((*(int *)(pcVar1 + 0xa0) != 0) && ((*(uint *)pcVar1 & 0x2000000) == 0)) {
          ObjectProcJoinTextures(pcVar1);
          cRObject::CalcTextureGroups((cRObject *)(*(int *)(this + 8) + iVar4));
          cRObject::BuildGLVertexArray((cRObject *)(*(int *)(this + 8) + iVar4));
          pcVar1 = (cRObject *)(*(int *)(this + 8) + iVar4);
          if ((*(uint *)(*(int *)(this + 8) + iVar4) & 0x4000) != 0) {
            cRObject::CalcFaceQuadNormals(pcVar1);
            cRObject::CalcEdges((cRObject *)(*(int *)(this + 8) + iVar4));
            pcVar1 = (cRObject *)(*(int *)(this + 8) + iVar4);
          }
        }
        cRObject::Save(pcVar1);
        pcVar1 = (cRObject *)(*(int *)(this + 8) + iVar4);
        if ((-1 < *(int *)(*(int *)(this + 8) + iVar4)) || (*(int *)(pcVar1 + 200) == 0)) break;
        wprintf("Build Objects Debug Flags%x - %s\n",*(int *)(*(int *)(pcVar1 + 200) + 0xc) + 0xc);
        pcVar1 = (cRObject *)(*(int *)(this + 8) + iVar4);
        if ((*(uint *)pcVar1 & 0x10000200) != 0x10000000) goto LAB_00030394;
LAB_0003041c:
        cRObject::GLVBO(pcVar1);
        uVar5 = uVar5 + 1;
        iVar4 = iVar4 + 0x110;
        if (*(int *)this <= (int)uVar5) goto LAB_00030434;
      }
      if ((*(uint *)pcVar1 & 0x10000200) == 0x10000000) goto LAB_0003041c;
LAB_00030394:
      uVar5 = uVar5 + 1;
      iVar4 = iVar4 + 0x110;
    } while ((int)uVar5 < *(int *)this);
  }
LAB_00030434:
  iVar4 = RShellFindFile("Data/NormalsTable.bin",false);
  if (iVar4 == 0) {
    RShellSaveFile("Data/NormalsTable.bin",*(void **)(this + 0x10),*(int *)(this + 0xc) * 0xc);
  }
  GLObjectVBOEnd();
  cRResourceManager::Add((cRResourceManager *)&gResourceManager,4,0,"VBO Objects");
  return;
}
