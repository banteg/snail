/*
 * mangled: _ZN8cRObject12RequestStripEi
 * demangled: cRObject::RequestStrip(int)
 * address: 0002d324
 * size: 56
 */

/* cRObject::RequestStrip(int) */

void __thiscall cRObject::RequestStrip(cRObject *this,int param_1)

{
  undefined4 uVar1;
  int iVar2;

  iVar2 = *(int *)(this + 0x10c);
  uVar1 = RShellMemoryMalloc(param_1 << 1,(char *)(DAT_0002d35c + 0x2d344 + DAT_0002d360));
  *(int *)(*(int *)(this + 0x10c) + 0x44) = param_1;
  *(undefined4 *)(iVar2 + 0x48) = uVar1;
  return;
}
