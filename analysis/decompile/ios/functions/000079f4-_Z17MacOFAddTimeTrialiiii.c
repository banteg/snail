/*
 * mangled: _Z17MacOFAddTimeTrialiiii
 * demangled: MacOFAddTimeTrial(int, int, int, int)
 * address: 000079f4
 * size: 396
 */

/* MacOFAddTimeTrial(int, int, int, int) */

void MacOFAddTimeTrial(int param_1,int param_2,int param_3,int param_4)

{
  ID local_e8;
  OFDelegate *local_e4;
  OFDelegate *local_e0;
  int local_d8;
  int local_d4;
  int local_d0;
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
  local_8c = (undefined1 *)&local_e8;
  local_9c = PTR_001b615c;
  local_98 = &GCC_except_table1;
  local_90 = &LAB_00007b80;
  local_d8 = param_4;
  local_d4 = param_3;
  local_d0 = param_2;
  local_cc = param_1;
  __Unwind_SjLj_Register(auStack_b4);
  local_c8 = &objc::class_t::OFHighScoreService;
  local_c4 = "setHighScore:forLeaderboard:onSuccess:onFailure:";
  local_c0 = local_cc * 10000 + local_d0 * 100 + local_d4 % 100;
  local_bc = local_c0 >> 0x1f;
  local_b0 = 0xffffffff;
  local_b8 = NSString::stringWithUTF8String_
                       ((ID)&_OBJC_CLASS___NSString,"stringWithUTF8String:",
                        PTR__OFID_001b6128 + local_d8 * 0x20 + 0xa0);
  OFDelegate::OFDelegate(aOStack_70);
  local_b0 = 2;
  OFDelegate::OFDelegate(&OStack_80);
  local_e4 = aOStack_70;
  local_e0 = &OStack_80;
  local_b0 = 1;
  local_e8 = local_b8;
  _objc_msgSend((ID)local_c8,local_c4,local_c0,local_bc);
  local_b0 = 2;
  OFDelegate::~OFDelegate(&OStack_80);
  local_b0 = 0xffffffff;
  OFDelegate::~OFDelegate(aOStack_70);
  __Unwind_SjLj_Unregister(auStack_b4);
  return;
}
