/*
 * mangled: _ZN13OFISerializer9serializeI21OFHighScoreBatchEntryEEvPKcR9OFPointerIT_E
 * demangled: void OFISerializer::serialize<OFHighScoreBatchEntry>(char const*, OFPointer<OFHighScoreBatchEntry>&)
 * address: 0008f278
 * size: 304
 */

/* void OFISerializer::serialize<OFHighScoreBatchEntry>(char const*,
   OFPointer<OFHighScoreBatchEntry>&) */

void __thiscall
OFISerializer::serialize<OFHighScoreBatchEntry>
          (OFISerializer *this,char *param_1,OFPointer *param_2)

{
  int iVar1;
  OFSmartObject *this_00;
  undefined4 *local_ac;
  char *local_a8;
  OFISerializer *local_a4;
  OFSmartObject *local_9c;
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
  local_7c = &::GCC_except_table3;
  local_74 = &LAB_0008f3a8;
  local_ac = (undefined4 *)param_2;
  local_a8 = param_1;
  local_a4 = this;
  __Unwind_SjLj_Register(auStack_98);
  local_94 = 0xffffffff;
  iVar1 = (**(code **)(*(int *)local_a4 + 0x10))(local_a4);
  if (iVar1 == 0) {
    if ((OFHighScoreBatchEntry *)*local_ac != (OFHighScoreBatchEntry *)0x0) {
      local_94 = 0xffffffff;
      serialize<OFHighScoreBatchEntry>(local_a4,local_a8,(OFHighScoreBatchEntry *)*local_ac);
    }
  }
  else {
    deserializeObject<OFHighScoreBatchEntry>((char *)local_64);
    local_9c = local_64[0];
    this_00 = (OFSmartObject *)*local_ac;
    if (local_64[0] == this_00) {
      if (local_64[0] == (OFSmartObject *)0x0) goto LAB_0008f2f8;
    }
    else {
      if (this_00 != (OFSmartObject *)0x0) {
        local_94 = 1;
        OFSmartObject::Release(this_00);
      }
      *local_ac = local_9c;
      if (local_9c == (OFSmartObject *)0x0) goto LAB_0008f2f8;
      *(int *)(local_9c + 4) = *(int *)(local_9c + 4) + 1;
    }
    local_94 = 0xffffffff;
    OFSmartObject::Release(local_9c);
  }
LAB_0008f2f8:
  __Unwind_SjLj_Unregister(auStack_98);
  return;
}
