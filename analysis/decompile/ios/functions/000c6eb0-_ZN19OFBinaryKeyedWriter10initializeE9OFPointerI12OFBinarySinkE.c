/*
 * mangled: _ZN19OFBinaryKeyedWriter10initializeE9OFPointerI12OFBinarySinkE
 * demangled: OFBinaryKeyedWriter::initialize(OFPointer<OFBinarySink>)
 * address: 000c6eb0
 * size: 276
 */

/* OFBinaryKeyedWriter::initialize(OFPointer<OFBinarySink>) */

void __thiscall OFBinaryKeyedWriter::initialize(OFBinaryKeyedWriter *this,int *param_2)

{
  OFSmartObject *this_00;
  int iVar1;
  int *local_ac;
  OFBinaryKeyedWriter *local_a8;
  code *local_a4;
  OFSmartObject *local_a0;
  undefined1 auStack_98 [4];
  undefined4 local_94;
  undefined *local_80;
  undefined *local_7c;
  undefined1 *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  OFSmartObject *local_64 [17];

  local_78 = &stack0xfffffff8;
  local_70 = (undefined1 *)&local_ac;
  local_80 = PTR_001b615c;
  local_7c = &::GCC_except_table0;
  local_74 = &LAB_000c6fc4;
  local_ac = param_2;
  local_a8 = this;
  __Unwind_SjLj_Register(auStack_98);
  this_00 = *(OFSmartObject **)(local_a8 + 0x18);
  if ((OFSmartObject *)*local_ac != this_00) {
    if (this_00 != (OFSmartObject *)0x0) {
      local_94 = 0xffffffff;
      OFSmartObject::Release(this_00);
    }
    iVar1 = *local_ac;
    *(int *)(local_a8 + 0x18) = iVar1;
    if (iVar1 != 0) {
      *(int *)(iVar1 + 4) = *(int *)(iVar1 + 4) + 1;
    }
  }
  local_a4 = *(code **)(*(int *)local_a8 + 0x40);
  local_94 = 0xffffffff;
  (**(code **)(*(int *)local_a8 + 0x14))(local_64,local_a8,"root");
  local_a0 = local_64[0];
  local_94 = 1;
  (*local_a4)(local_a8,local_64[0]);
  if (local_a0 != (OFSmartObject *)0x0) {
    local_94 = 0xffffffff;
    OFSmartObject::Release(local_a0);
  }
  __Unwind_SjLj_Unregister(auStack_98);
  return;
}
