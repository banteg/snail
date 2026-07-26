/*
 * mangled: _ZN8cRObject13RequestAlphasEv
 * demangled: cRObject::RequestAlphas()
 * address: 0002d3b0
 * size: 44
 */

/* cRObject::RequestAlphas() */

void __thiscall cRObject::RequestAlphas(cRObject *this)

{
  undefined4 uVar1;

  uVar1 = RShellMemoryMalloc(*(int *)(this + 0xa0) << 2,
                             (char *)(DAT_0002d3dc + 0x2d3cc + DAT_0002d3e0));
  *(undefined4 *)(this + 0xbc) = uVar1;
  return;
}
