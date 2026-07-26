/*
 * mangled: _ZN10OFSettings10InitializeEv
 * demangled: OFSettings::Initialize()
 * address: 000d4188
 * size: 192
 */

/* OFSettings::Initialize() */

void OFSettings::Initialize(void)

{
  undefined1 auStack_a0 [4];
  OFSettings *local_9c;
  OFSettings *local_98;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = auStack_a0;
  local_7c = PTR_001b615c;
  local_78 = &GCC_except_table6;
  local_70 = &DAT_000d4248;
  __Unwind_SjLj_Register(auStack_94);
  local_90 = 0xffffffff;
  local_9c = operator_new(0x30);
  local_90 = 2;
  OFSettings(local_9c);
  local_98 = s_UniqueInstance;
  if (local_9c != s_UniqueInstance) {
    if (s_UniqueInstance != (OFSettings *)0x0) {
      local_90 = 1;
      ~OFSettings(s_UniqueInstance);
      operator_delete(local_98);
    }
    s_UniqueInstance = local_9c;
  }
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
