/*
 * mangled: _ZN8cRObject19RequestVerticesCopyEv
 * demangled: cRObject::RequestVerticesCopy()
 * address: 0002d524
 * size: 100
 */

/* cRObject::RequestVerticesCopy() */

void __thiscall cRObject::RequestVerticesCopy(cRObject *this)

{
  undefined4 uVar1;

  if ((*(uint *)this & 0x1000) == 0) {
    uVar1 = RShellMemoryMalloc(*(int *)(this + 0xa0) * 0xc,
                               (char *)(DAT_0002d588 + 0x2d53c + DAT_0002d58c));
    *(undefined4 *)(this + 0xa8) = uVar1;
  }
  else {
    uVar1 = RShellMemoryMalloc(*(int *)(this + 0xa0) * 6,
                               (char *)(DAT_0002d588 + 0x2d53c + DAT_0002d58c));
    *(undefined4 *)(this + 0xa8) = uVar1;
  }
  CopyVertices(this);
  return;
}
