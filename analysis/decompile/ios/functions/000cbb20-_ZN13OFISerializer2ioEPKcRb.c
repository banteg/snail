/*
 * mangled: _ZN13OFISerializer2ioEPKcRb
 * demangled: OFISerializer::io(char const*, bool&)
 * address: 000cbb20
 * size: 212
 */

/* OFISerializer::io(char const*, bool&) */

void __thiscall OFISerializer::io(OFISerializer *this,char *param_1,bool *param_2)

{
  bool *local_b0;
  char *local_ac;
  OFISerializer *local_a8;
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
  local_70 = (undefined1 *)&local_b0;
  local_80 = PTR_001b615c;
  local_7c = &::GCC_except_table5;
  local_74 = &LAB_000cbbf4;
  local_b0 = param_2;
  local_ac = param_1;
  local_a8 = this;
  __Unwind_SjLj_Register(auStack_98);
  local_a4 = *(code **)(*(int *)local_a8 + 0x18);
  local_94 = 0xffffffff;
  (**(code **)(*(int *)local_a8 + 0x14))(local_64,local_a8,local_ac);
  local_a0 = local_64[0];
  local_94 = 1;
  (*local_a4)(local_a8,local_64[0],local_b0);
  if (local_a0 != (OFSmartObject *)0x0) {
    local_94 = 0xffffffff;
    OFSmartObject::Release(local_a0);
  }
  __Unwind_SjLj_Unregister(auStack_98);
  return;
}
