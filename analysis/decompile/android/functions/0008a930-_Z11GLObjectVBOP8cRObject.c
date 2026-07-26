/*
 * mangled: _Z11GLObjectVBOP8cRObject
 * demangled: GLObjectVBO(cRObject*)
 * address: 0008a930
 * size: 560
 */

/* GLObjectVBO(cRObject*) */

void GLObjectVBO(cRObject *param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;

  if (*(int *)(param_1 + 0xa0) < 9) {
    return;
  }
  *(uint *)param_1 = *(uint *)param_1 | 0x200;
  glGenBuffers(1,*(int *)(param_1 + 0x10c) + 0x58);
  glBindBuffer(0x8893,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x58));
  glBufferData(0x8893,*(int *)(*(int *)(param_1 + 0x10c) + 0x44) << 1,
               *(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x48),0x88e4);
  RShellMemoryFree(*(void **)(*(int *)(param_1 + 0x10c) + 0x48));
  if ((*(uint *)param_1 & 0x200000) == 0) {
    glGenBuffers(1,*(int *)(param_1 + 0x10c) + 0x4c);
    if ((*(uint *)param_1 & 0x1000) == 0) {
      glBindBuffer(0x8892,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x4c));
      uVar1 = *(undefined4 *)(*(int *)(param_1 + 0x10c) + 8);
      iVar2 = *(int *)(*(int *)(param_1 + 0x10c) + 4) * 0x14;
    }
    else {
      glBindBuffer(0x8892,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x4c));
      uVar1 = *(undefined4 *)(*(int *)(param_1 + 0x10c) + 8);
      iVar2 = *(int *)(*(int *)(param_1 + 0x10c) + 4) * 10;
    }
    glBufferData(0x8892,iVar2,uVar1,0x88e4);
    RShellMemoryFree(*(void **)(*(int *)(param_1 + 0x10c) + 8));
    return;
  }
  iVar2 = *(int *)(param_1 + 0x104);
  if (0 < *(int *)(iVar2 + 4)) {
    iVar3 = 0;
    do {
      while( true ) {
        glGenBuffers(1,*(int *)(*(int *)(iVar2 + 0xc) + iVar3 * 4) + 4);
        glBindBuffer(0x8892,*(undefined4 *)
                             (*(int *)(*(int *)(*(int *)(param_1 + 0x104) + 0xc) + iVar3 * 4) + 4));
        if ((*(uint *)param_1 & 0x1000) != 0) break;
        iVar2 = iVar3 * 4;
        iVar3 = iVar3 + 1;
        glBufferData(0x8892,*(int *)(param_1 + 0xa0) * 0xc,
                     **(undefined4 **)(*(int *)(*(int *)(param_1 + 0x104) + 0xc) + iVar2),0x88e4);
        iVar2 = *(int *)(param_1 + 0x104);
        if (*(int *)(iVar2 + 4) <= iVar3) goto LAB_0008aa64;
      }
      iVar2 = iVar3 * 4;
      iVar3 = iVar3 + 1;
      glBufferData(0x8892,*(int *)(param_1 + 0xa0) * 6,
                   **(undefined4 **)(*(int *)(*(int *)(param_1 + 0x104) + 0xc) + iVar2),0x88e4);
      iVar2 = *(int *)(param_1 + 0x104);
    } while (iVar3 < *(int *)(iVar2 + 4));
  }
LAB_0008aa64:
  glGenBuffers(1,*(int *)(param_1 + 0x10c) + 0x54);
  glBindBuffer(0x8892,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x54));
  if ((*(uint *)param_1 & 0x1000) == 0) {
    glBufferData(0x8892,*(int *)(*(int *)(param_1 + 0x10c) + 0xc) << 3,
                 *(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x10),0x88e4);
  }
  else {
    glBufferData(0x8892,*(int *)(*(int *)(param_1 + 0x10c) + 0xc) << 2,
                 *(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x10),0x88e4);
  }
  RShellMemoryFree(*(void **)(*(int *)(param_1 + 0x10c) + 0x10));
  return;
}
