/*
 * mangled: _ZNSt6vectorI9OFPointerI21OFHighScoreBatchEntryESaIS2_EE5eraseEN9__gnu_cxx17__normal_iteratorIPS2_S4_EE
 * demangled: std::vector<OFPointer<OFHighScoreBatchEntry>, std::allocator<OFPointer<OFHighScoreBatchEntry>>>::erase(__gnu_cxx::__normal_iterator<OFPointer<OFHighScoreBatchEntry>*, std::vector<OFPointer<OFHighScoreBatchEntry>, std::allocator<OFPointer<OFHighScoreBatchEntry>>>>)
 * address: 0008f1d4
 * size: 164
 */

/* std::vector<OFPointer<OFHighScoreBatchEntry>, std::allocator<OFPointer<OFHighScoreBatchEntry> >
   >::erase(__gnu_cxx::__normal_iterator<OFPointer<OFHighScoreBatchEntry>*,
   std::vector<OFPointer<OFHighScoreBatchEntry>, std::allocator<OFPointer<OFHighScoreBatchEntry> > >
   >) */

undefined4 * __thiscall
std::vector<OFPointer<OFHighScoreBatchEntry>,std::allocator<OFPointer<OFHighScoreBatchEntry>>>::
erase(vector<OFPointer<OFHighScoreBatchEntry>,std::allocator<OFPointer<OFHighScoreBatchEntry>>>
      *this,undefined4 *param_2)

{
  undefined4 *puVar1;
  OFSmartObject *this_00;
  OFSmartObject *pOVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;

  puVar1 = *(undefined4 **)(this + 4);
  puVar4 = param_2 + 1;
  if ((puVar4 != puVar1) && (iVar5 = (int)puVar1 - (int)puVar4 >> 2, puVar3 = param_2, 0 < iVar5)) {
    do {
      this_00 = (OFSmartObject *)*puVar3;
      pOVar2 = (OFSmartObject *)*puVar4;
      if (pOVar2 != this_00) {
        if (this_00 != (OFSmartObject *)0x0) {
          OFSmartObject::Release(this_00);
          pOVar2 = (OFSmartObject *)*puVar4;
        }
        *puVar3 = pOVar2;
        if (pOVar2 != (OFSmartObject *)0x0) {
          *(int *)(pOVar2 + 4) = *(int *)(pOVar2 + 4) + 1;
        }
      }
      iVar5 = iVar5 + -1;
      puVar4 = puVar4 + 1;
      puVar3 = puVar3 + 1;
    } while (iVar5 != 0);
    puVar1 = *(undefined4 **)(this + 4);
  }
  *(undefined4 **)(this + 4) = puVar1 + -1;
  if ((OFSmartObject *)puVar1[-1] != (OFSmartObject *)0x0) {
    OFSmartObject::Release((OFSmartObject *)puVar1[-1]);
  }
  return param_2;
}
