/*
 * mangled: _ZN8cRObject7ReGLVBOEv
 * demangled: cRObject::ReGLVBO()
 * address: 0002d2c0
 * size: 4
 */

/* cRObject::ReGLVBO() */

void __thiscall cRObject::ReGLVBO(cRObject *this)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;

  if (*(int *)(this + 0xa0) < 9) {
    return;
  }
  *(uint *)this = *(uint *)this | 0x200;
  glGenBuffers(1,*(int *)(this + 0x10c) + 0x58);
  glBindBuffer(0x8893,*(undefined4 *)(*(int *)(this + 0x10c) + 0x58));
  glBufferData(0x8893,*(int *)(*(int *)(this + 0x10c) + 0x44) << 1,
               *(undefined4 *)(*(int *)(this + 0x10c) + 0x48),0x88e4);
  RShellMemoryFree(*(void **)(*(int *)(this + 0x10c) + 0x48));
  if ((*(uint *)this & 0x200000) == 0) {
    glGenBuffers(1,*(int *)(this + 0x10c) + 0x4c);
    if ((*(uint *)this & 0x1000) == 0) {
      glBindBuffer(0x8892,*(undefined4 *)(*(int *)(this + 0x10c) + 0x4c));
      uVar1 = *(undefined4 *)(*(int *)(this + 0x10c) + 8);
      iVar2 = *(int *)(*(int *)(this + 0x10c) + 4) * 0x14;
    }
    else {
      glBindBuffer(0x8892,*(undefined4 *)(*(int *)(this + 0x10c) + 0x4c));
      uVar1 = *(undefined4 *)(*(int *)(this + 0x10c) + 8);
      iVar2 = *(int *)(*(int *)(this + 0x10c) + 4) * 10;
    }
    glBufferData(0x8892,iVar2,uVar1,0x88e4);
    RShellMemoryFree(*(void **)(*(int *)(this + 0x10c) + 8));
    return;
  }
  iVar2 = *(int *)(this + 0x104);
  if (0 < *(int *)(iVar2 + 4)) {
    iVar3 = 0;
    do {
      while( true ) {
        glGenBuffers(1,*(int *)(*(int *)(iVar2 + 0xc) + iVar3 * 4) + 4);
        glBindBuffer(0x8892,*(undefined4 *)
                             (*(int *)(*(int *)(*(int *)(this + 0x104) + 0xc) + iVar3 * 4) + 4));
        if ((*(uint *)this & 0x1000) != 0) break;
        iVar2 = iVar3 * 4;
        iVar3 = iVar3 + 1;
        glBufferData(0x8892,*(int *)(this + 0xa0) * 0xc,
                     **(undefined4 **)(*(int *)(*(int *)(this + 0x104) + 0xc) + iVar2),0x88e4);
        iVar2 = *(int *)(this + 0x104);
        if (*(int *)(iVar2 + 4) <= iVar3) goto LAB_0008aa64;
      }
      iVar2 = iVar3 * 4;
      iVar3 = iVar3 + 1;
      glBufferData(0x8892,*(int *)(this + 0xa0) * 6,
                   **(undefined4 **)(*(int *)(*(int *)(this + 0x104) + 0xc) + iVar2),0x88e4);
      iVar2 = *(int *)(this + 0x104);
    } while (iVar3 < *(int *)(iVar2 + 4));
  }
LAB_0008aa64:
  glGenBuffers(1,*(int *)(this + 0x10c) + 0x54);
  glBindBuffer(0x8892,*(undefined4 *)(*(int *)(this + 0x10c) + 0x54));
  if ((*(uint *)this & 0x1000) == 0) {
    glBufferData(0x8892,*(int *)(*(int *)(this + 0x10c) + 0xc) << 3,
                 *(undefined4 *)(*(int *)(this + 0x10c) + 0x10),0x88e4);
  }
  else {
    glBufferData(0x8892,*(int *)(*(int *)(this + 0x10c) + 0xc) << 2,
                 *(undefined4 *)(*(int *)(this + 0x10c) + 0x10),0x88e4);
  }
  RShellMemoryFree(*(void **)(*(int *)(this + 0x10c) + 0x10));
  return;
}
