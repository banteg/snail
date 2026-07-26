/*
 * mangled: _ZN13OFISerializer2ioEPKcP8NSString
 * demangled: OFISerializer::io(char const*, NSString*)
 * address: 000cbf9c
 * size: 200
 */

/* OFISerializer::io(char const*, NSString*) */

void __thiscall OFISerializer::io(OFISerializer *this,char *param_1,NSString *param_2)

{
  NSString *local_a8;
  char *local_a4;
  OFISerializer *local_a0;
  undefined1 auStack_98 [4];
  undefined4 local_94;
  undefined *local_80;
  undefined *local_7c;
  undefined1 *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  NSString *local_64 [17];

  local_78 = &stack0xfffffff8;
  local_70 = (undefined1 *)&local_a8;
  local_80 = PTR_001b615c;
  local_7c = &GCC_except_table10;
  local_74 = &LAB_000cc064;
  local_a8 = param_2;
  local_a4 = param_1;
  local_a0 = this;
  __Unwind_SjLj_Register(auStack_98);
  local_64[0] = local_a8;
  if (local_a8 != (NSString *)0x0) {
    local_94 = 0xffffffff;
    _objc_msgSend((ID)local_a8,"retain");
  }
  local_94 = 1;
  io(local_a0,local_a4,(OFRetainedPtr *)local_64);
  if (local_64[0] != (NSString *)0x0) {
    local_94 = 0xffffffff;
    _objc_msgSend((ID)local_64[0],"release");
  }
  __Unwind_SjLj_Unregister(auStack_98);
  return;
}
