/*
 * mangled: _Z11GLObjectVBOP8cRObject
 * demangled: GLObjectVBO(cRObject*)
 * address: 0006de14
 * size: 612
 */

/* GLObjectVBO(cRObject*) */

void GLObjectVBO(cRObject *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;

  if (*(int *)(param_1 + 0xa0) < 9) {
    return;
  }
  *(uint *)param_1 = *(uint *)param_1 | 0x200;
  _glGenBuffers(1,*(int *)(param_1 + 0x10c) + 0x58);
  _glBindBuffer(0x8893,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x58));
  _glBufferData(0x8893,*(int *)(*(int *)(param_1 + 0x10c) + 0x44) << 1,
                *(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x48),&DAT_000088e4);
  RShellMemoryFree(*(void **)(*(int *)(param_1 + 0x10c) + 0x48));
  _glBindBuffer(0x8893,0);
  if ((*(uint *)param_1 & 0x200000) == 0) {
    _glGenBuffers(1,*(int *)(param_1 + 0x10c) + 0x4c);
    if ((*(uint *)param_1 & 0x1000) == 0) {
      _glBindBuffer(0x8892,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x4c));
      iVar1 = *(int *)(param_1 + 0x10c);
      iVar2 = *(int *)(iVar1 + 4) << 2;
      iVar3 = *(int *)(iVar1 + 4) << 4;
    }
    else {
      _glBindBuffer(0x8892,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x4c));
      iVar1 = *(int *)(param_1 + 0x10c);
      iVar2 = *(int *)(iVar1 + 4) << 1;
      iVar3 = *(int *)(iVar1 + 4) << 3;
    }
    _glBufferData(0x8892,iVar2 + iVar3,*(undefined4 *)(iVar1 + 8),&DAT_000088e4);
    RShellMemoryFree(*(void **)(*(int *)(param_1 + 0x10c) + 8));
    _glBindBuffer(0x8892,0);
    return;
  }
  iVar2 = *(int *)(param_1 + 0x104);
  if (0 < *(int *)(iVar2 + 4)) {
    iVar3 = 0;
    do {
      while( true ) {
        iVar1 = iVar3 * 4;
        _glGenBuffers(1,*(int *)(*(int *)(iVar2 + 0xc) + iVar3 * 4) + 4);
        _glBindBuffer(0x8892,*(undefined4 *)
                              (*(int *)(*(int *)(*(int *)(param_1 + 0x104) + 0xc) + iVar1) + 4));
        if ((*(uint *)param_1 & 0x1000) != 0) break;
        iVar3 = iVar3 + 1;
        _glBufferData(0x8892,*(int *)(param_1 + 0xa0) * 0xc,
                      **(undefined4 **)(*(int *)(*(int *)(param_1 + 0x104) + 0xc) + iVar1),
                      &DAT_000088e4);
        iVar2 = *(int *)(param_1 + 0x104);
        if (*(int *)(iVar2 + 4) <= iVar3) goto LAB_0006df64;
      }
      iVar3 = iVar3 + 1;
      _glBufferData(0x8892,*(int *)(param_1 + 0xa0) * 6,
                    **(undefined4 **)(*(int *)(*(int *)(param_1 + 0x104) + 0xc) + iVar1),
                    &DAT_000088e4);
      iVar2 = *(int *)(param_1 + 0x104);
    } while (iVar3 < *(int *)(iVar2 + 4));
  }
LAB_0006df64:
  _glGenBuffers(1,*(int *)(param_1 + 0x10c) + 0x54);
  _glBindBuffer(0x8892,*(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x54));
  if ((*(uint *)param_1 & 0x1000) == 0) {
    _glBufferData(0x8892,*(int *)(*(int *)(param_1 + 0x10c) + 0xc) << 3,
                  *(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x10),&DAT_000088e4);
  }
  else {
    _glBufferData(0x8892,*(int *)(*(int *)(param_1 + 0x10c) + 0xc) << 2,
                  *(undefined4 *)(*(int *)(param_1 + 0x10c) + 0x10),&DAT_000088e4);
  }
  RShellMemoryFree(*(void **)(*(int *)(param_1 + 0x10c) + 0x10));
  _glBindBuffer(0x8892,0);
  return;
}
