/*
 * mangled: _ZN13OFISerializer8popScopeEv
 * demangled: OFISerializer::popScope()
 * address: 000cbc34
 * size: 236
 */

/* OFISerializer::popScope() */

void __thiscall OFISerializer::popScope(OFISerializer *this)

{
  int iVar1;
  OFSmartObject *this_00;
  OFISerializer *local_a0 [2];
  OFSmartObject *local_98;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = (undefined1 *)local_a0;
  local_7c = PTR_001b615c;
  local_78 = &GCC_except_table7;
  local_70 = &LAB_000cbd20;
  local_a0[0] = this;
  __Unwind_SjLj_Register(auStack_94);
  local_98 = *(OFSmartObject **)(*(int *)(local_a0[0] + 0xc) + -8);
  if (local_98 != (OFSmartObject *)0x0) {
    *(int *)(local_98 + 4) = *(int *)(local_98 + 4) + 1;
  }
  iVar1 = *(int *)(local_a0[0] + 0xc);
  *(int *)(local_a0[0] + 0xc) = iVar1 + -8;
  this_00 = *(OFSmartObject **)(iVar1 + -8);
  if (this_00 != (OFSmartObject *)0x0) {
    local_90 = 1;
    OFSmartObject::Release(this_00);
  }
  local_90 = 1;
  (**(code **)(*(int *)local_a0[0] + 0x44))(local_a0[0],local_98);
  if (local_98 != (OFSmartObject *)0x0) {
    local_90 = 0xffffffff;
    OFSmartObject::Release(local_98);
  }
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
