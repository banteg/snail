/*
 * mangled: _ZN9cRObjects12BuildObjectsEv
 * demangled: cRObjects::BuildObjects()
 * address: 00015330
 * size: 412
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
    uVar5 = 0;
    iVar4 = 0;
    do {
      while( true ) {
        if ((uVar5 & 3) == 0) {
          cRLoadingBar::Signal((cRLoadingBar *)PTR__gLoadingBar_001b60bc);
          iVar3 = *(int *)(this + 8);
          iVar2 = *(int *)(iVar4 + iVar3);
        }
        else {
          iVar3 = *(int *)(this + 8);
          iVar2 = *(int *)(iVar4 + iVar3);
        }
        if (iVar2 < 0) {
          wprintf("Build Objects Debug\n");
          iVar3 = *(int *)(this + 8);
        }
        pcVar1 = (cRObject *)(iVar4 + iVar3);
        if ((*(int *)(pcVar1 + 0xa0) != 0) && ((*(uint *)pcVar1 & 0x2000000) == 0)) {
          ObjectProcJoinTextures(pcVar1);
          cRObject::CalcTextureGroups((cRObject *)(iVar4 + *(int *)(this + 8)));
          cRObject::BuildGLVertexArray((cRObject *)(iVar4 + *(int *)(this + 8)));
          iVar3 = *(int *)(this + 8);
          if ((*(uint *)(iVar4 + iVar3) & 0x4000) != 0) {
            cRObject::CalcFaceQuadNormals((cRObject *)(iVar4 + iVar3));
            cRObject::CalcEdges((cRObject *)(iVar4 + *(int *)(this + 8)));
            iVar3 = *(int *)(this + 8);
          }
        }
        cRObject::Save((cRObject *)(iVar4 + iVar3));
        pcVar1 = (cRObject *)(iVar4 + *(int *)(this + 8));
        if ((*(int *)(iVar4 + *(int *)(this + 8)) < 0) && (*(int *)(pcVar1 + 200) != 0)) {
          wprintf("Build Objects Debug Flags%x - %s\n",*(int *)(*(int *)(pcVar1 + 200) + 0xc) + 0xc)
          ;
          pcVar1 = (cRObject *)(iVar4 + *(int *)(this + 8));
        }
        if (((*(uint *)pcVar1 & 0x10000200) != 0x10000000) || ((*(uint *)pcVar1 & 0x200) != 0))
        break;
        GLObjectVBO(pcVar1);
        uVar5 = uVar5 + 1;
        iVar4 = iVar4 + 0x110;
        if (*(int *)this <= (int)uVar5) goto LAB_0001542c;
      }
      uVar5 = uVar5 + 1;
      iVar4 = iVar4 + 0x110;
    } while ((int)uVar5 < *(int *)this);
  }
LAB_0001542c:
  iVar4 = RShellFindFile("Data/NormalsTable.bin",false);
  if (iVar4 == 0) {
    RShellSaveFile("Data/NormalsTable.bin",*(void **)(this + 0x10),*(int *)(this + 0xc) * 0xc);
    return;
  }
  return;
}
