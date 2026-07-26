/*
 * mangled: _Z17MacOFAddArcadeProi
 * demangled: MacOFAddArcadePro(int)
 * address: 00007d7c
 * size: 292
 */

/* MacOFAddArcadePro(int) */

void MacOFAddArcadePro(int param_1)

{
  ID local_dc;
  OFDelegate *local_d8;
  OFDelegate *local_d4;
  int local_cc;
  class_t *local_c8;
  char *local_c4;
  int local_c0;
  int local_bc;
  ID local_b8;
  undefined1 auStack_b4 [4];
  undefined4 local_b0;
  undefined *local_9c;
  undefined *local_98;
  undefined1 *local_94;
  undefined1 *local_90;
  undefined1 *local_8c;
  OFDelegate OStack_80;
  OFDelegate aOStack_70 [5];

  local_94 = &stack0xfffffff8;
  local_8c = (undefined1 *)&local_dc;
  local_9c = PTR_001b615c;
  local_98 = &GCC_except_table3;
  local_90 = &LAB_00007ea0;
  local_cc = param_1;
  __Unwind_SjLj_Register(auStack_b4);
  local_c8 = &objc::class_t::OFHighScoreService;
  local_c4 = "setHighScore:forLeaderboard:onSuccess:onFailure:";
  local_bc = local_cc >> 0x1f;
  local_c0 = local_cc;
  local_b0 = 0xffffffff;
  local_b8 = NSString::stringWithUTF8String_
                       ((ID)&_OBJC_CLASS___NSString,"stringWithUTF8String:",
                        PTR__OFID_001b6128 + 0x20);
  OFDelegate::OFDelegate(aOStack_70);
  local_b0 = 2;
  OFDelegate::OFDelegate(&OStack_80);
  local_d8 = aOStack_70;
  local_d4 = &OStack_80;
  local_dc = local_b8;
  local_b0 = 1;
  _objc_msgSend((ID)local_c8,local_c4,local_c0,local_bc);
  local_b0 = 2;
  OFDelegate::~OFDelegate(&OStack_80);
  local_b0 = 0xffffffff;
  OFDelegate::~OFDelegate(aOStack_70);
  __Unwind_SjLj_Unregister(auStack_b4);
  return;
}
