/*
 * mangled: _ZN8cRObject14RequestColoursEv
 * demangled: cRObject::RequestColours()
 * address: 0002d458
 * size: 92
 */

/* cRObject::RequestColours() */

void __thiscall cRObject::RequestColours(cRObject *this)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;

  puVar2 = (undefined4 *)
           RShellMemoryMalloc(*(int *)(this + 0xa0) << 4,
                              (char *)(DAT_0002d4b8 + 0x2d474 + DAT_0002d4bc));
  iVar3 = *(int *)(this + 0xa0);
  *(undefined4 **)(this + 0xb4) = puVar2;
  uVar1 = DAT_0002d4b4;
  if (iVar3 < 1) {
    return;
  }
  iVar4 = 0;
  do {
    iVar4 = iVar4 + 1;
    *puVar2 = uVar1;
    puVar2[1] = uVar1;
    puVar2[2] = uVar1;
    puVar2 = puVar2 + 4;
  } while (iVar4 != iVar3);
  return;
}
