/*
 * mangled: _ZN13OFSmartObject7ReleaseEv
 * demangled: OFSmartObject::Release()
 * address: 000c6940
 * size: 32
 */

/* OFSmartObject::Release() */

void __thiscall OFSmartObject::Release(OFSmartObject *this)

{
  int iVar1;

  iVar1 = *(int *)(this + 4);
  *(int *)(this + 4) = iVar1 + -1;
  if (iVar1 + -1 != 0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x000c695c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)this + 8))();
  return;
}
