/*
 * mangled: _ZNK13OFISerializer9createKeyEPKc
 * demangled: OFISerializer::createKey(char const*) const
 * address: 000cb7fc
 * size: 184
 */

/* OFISerializer::createKey(char const*) const */

char * OFISerializer::createKey(char *param_1)

{
  undefined4 in_r2;
  undefined1 auStack_a8 [4];
  undefined4 local_a4;
  char *local_a0;
  OFSmartObject *local_9c;
  char *local_98;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = auStack_a8;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table0;
  local_70 = &LAB_000cb8b4;
  local_a4 = in_r2;
  local_a0 = param_1;
  __Unwind_SjLj_Register(auStack_94);
  local_90 = 0xffffffff;
  local_98 = local_a0;
  local_9c = operator_new(0xc);
  local_90 = 1;
  OFSmartObject::OFSmartObject(local_9c);
  *(undefined ***)local_9c = &PTR_GetRTTI_001b7334;
  *(undefined4 *)(local_9c + 8) = local_a4;
  *(OFSmartObject **)local_98 = local_9c;
  *(int *)(local_9c + 4) = *(int *)(local_9c + 4) + 1;
  __Unwind_SjLj_Unregister(auStack_94);
  return local_a0;
}
