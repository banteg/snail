/*
 * mangled: _ZN13OFISerializer2ioEPKcR14OFHashedString
 * demangled: OFISerializer::io(char const*, OFHashedString&)
 * address: 000cba08
 * size: 4
 */

/* OFISerializer::io(char const*, OFHashedString&) */

void __thiscall OFISerializer::io(OFISerializer *this,char *param_1,OFHashedString *param_2)

{
  OFHashedString *pOStack_b0;
  char *pcStack_ac;
  OFISerializer *pOStack_a8;
  code *pcStack_a4;
  OFSmartObject *pOStack_a0;
  undefined1 auStack_98 [4];
  undefined4 uStack_94;
  undefined *puStack_80;
  undefined *puStack_7c;
  undefined1 *puStack_78;
  undefined1 *puStack_74;
  undefined1 *puStack_70;
  OFSmartObject *apOStack_64 [17];

  puStack_78 = &stack0xfffffff8;
  puStack_70 = (undefined1 *)&pOStack_b0;
  puStack_80 = PTR_001b615c;
  puStack_7c = &::GCC_except_table3;
  puStack_74 = &LAB_000cb9b8;
  pOStack_b0 = param_2;
  pcStack_ac = param_1;
  pOStack_a8 = this;
  __Unwind_SjLj_Register(auStack_98);
  pcStack_a4 = *(code **)(*(int *)pOStack_a8 + 0x20);
  uStack_94 = 0xffffffff;
  (**(code **)(*(int *)pOStack_a8 + 0x14))(apOStack_64,pOStack_a8,pcStack_ac);
  pOStack_a0 = apOStack_64[0];
  uStack_94 = 1;
  (*pcStack_a4)(pOStack_a8,apOStack_64[0],pOStack_b0);
  if (pOStack_a0 != (OFSmartObject *)0x0) {
    uStack_94 = 0xffffffff;
    OFSmartObject::Release(pOStack_a0);
  }
  __Unwind_SjLj_Unregister(auStack_98);
  return;
}
