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

  uVar1 = RShellMemoryMalloc(*(int *)(this + 0xa0) << 2,"Object Alpha Colours List");
  *(undefined4 *)(this + 0xbc) = uVar1;
  return;
}
