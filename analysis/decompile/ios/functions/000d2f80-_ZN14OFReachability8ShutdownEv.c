/*
 * mangled: _ZN14OFReachability8ShutdownEv
 * demangled: OFReachability::Shutdown()
 * address: 000d2f80
 * size: 148
 */

/* OFReachability::Shutdown() */

void OFReachability::Shutdown(void)

{
  OFReachability *local_98;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = (undefined1 *)&local_98;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table1;
  local_70 = &DAT_000d3014;
  __Unwind_SjLj_Register(auStack_94);
  local_98 = s_UniqueInstance;
  if (s_UniqueInstance != (OFReachability *)0x0) {
    local_90 = 1;
    ~OFReachability(s_UniqueInstance);
    operator_delete(local_98);
    s_UniqueInstance = (OFReachability *)0x0;
  }
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
