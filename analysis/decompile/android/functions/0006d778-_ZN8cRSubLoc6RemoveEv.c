/*
 * mangled: _ZN8cRSubLoc6RemoveEv
 * demangled: cRSubLoc::Remove()
 * address: 0006d778
 * size: 172
 */

/* cRSubLoc::Remove() */

void __thiscall cRSubLoc::Remove(cRSubLoc *this)

{
  int iVar1;
  int iVar2;

  iVar1 = Yi(this);
  if ((byte)((char)this[0x30] - 0x1dU) < 2) {
    iVar2 = Game + iVar1 * 0xdc;
    if (((*(uint *)(gGroup0 + iVar2 + 0xd0d4) & 8) != 0) &&
       ((*(uint *)(gGroup0 + iVar2 + 0xd17c) & 0x200) != 0)) {
      cLinkedList<cRBod>::Remove
                ((cLinkedList<cRBod> *)(Game + 0x358),
                 (cRBod *)(gGroup0 + Game + iVar1 * 0xdc + 0xd178));
    }
  }
  if ((*(uint *)(this + 4) & 0x200) == 0) {
    return;
  }
  cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(Game + 0x358),(cRBod *)this);
  return;
}
