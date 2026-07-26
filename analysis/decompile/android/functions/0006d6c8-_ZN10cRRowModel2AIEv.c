/*
 * mangled: _ZN10cRRowModel2AIEv
 * demangled: cRRowModel::AI()
 * address: 0006d6c8
 * size: 108
 */

/* cRRowModel::AI() */

void __thiscall cRRowModel::AI(cRRowModel *this)

{
  int iVar1;
  float fVar2;

  iVar1 = Game;
  fVar2 = *(float *)(this + 100);
  *(float *)(this + 0x5c) = *(float *)(this + 0x5c) + *(float *)(this + 0x74);
  *(float *)(this + 100) = fVar2 + *(float *)(this + 0x7c);
  *(float *)(this + 0x60) = *(float *)(this + 0x60) + *(float *)(this + 0x78);
  if (*(float *)(iVar1 + 0x83b60) <= fVar2 + *(float *)(this + 0x7c)) {
    return;
  }
  cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(iVar1 + 0x358),(cRBod *)this);
  return;
}
