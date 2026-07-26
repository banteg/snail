/*
 * mangled: _ZN9cRSubGame24GetSkirtColourRandomOpenEv
 * demangled: cRSubGame::GetSkirtColourRandomOpen()
 * address: 00019508
 * size: 32
 */

/* cRSubGame::GetSkirtColourRandomOpen() */

void __thiscall cRSubGame::GetSkirtColourRandomOpen(cRSubGame *this)

{
  undefined4 uVar1;

  uVar1 = RShellLoadFile("Sprites/FringeColours.tga",(int *)0x0);
  *(undefined4 *)(this + 0x50) = uVar1;
  return;
}
