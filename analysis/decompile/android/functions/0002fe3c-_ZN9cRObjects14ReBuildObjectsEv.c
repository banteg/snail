/*
 * mangled: _ZN9cRObjects14ReBuildObjectsEv
 * demangled: cRObjects::ReBuildObjects()
 * address: 0002fe3c
 * size: 136
 */

/* cRObjects::ReBuildObjects() */

void __thiscall cRObjects::ReBuildObjects(cRObjects *this)

{
  cRObject *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;

  wprintf("ReBuild Objects Start %i Objects\n",*(undefined4 *)this);
  iVar2 = *(int *)this;
  if (0 < iVar2) {
    iVar3 = 0;
    iVar4 = 0;
    do {
      while( true ) {
        iVar4 = iVar4 + 1;
        pcVar1 = (cRObject *)(*(int *)(this + 8) + iVar3);
        if ((*(uint *)(*(int *)(this + 8) + iVar3) & 0x200) == 0) break;
        cRObject::ReLoad(pcVar1,(char *)(pcVar1 + 0x20));
        pcVar1 = (cRObject *)(*(int *)(this + 8) + iVar3);
        iVar3 = iVar3 + 0x110;
        cRObject::ReGLVBO(pcVar1);
        iVar2 = *(int *)this;
        if (iVar2 <= iVar4) goto LAB_0002febc;
      }
      iVar3 = iVar3 + 0x110;
    } while (iVar4 < iVar2);
  }
LAB_0002febc:
  GLObjectVBOEnd();
  return;
}
