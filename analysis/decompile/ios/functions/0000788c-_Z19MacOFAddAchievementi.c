/*
 * mangled: _Z19MacOFAddAchievementi
 * demangled: MacOFAddAchievement(int)
 * address: 0000788c
 * size: 256
 */

/* MacOFAddAchievement(int) */

void MacOFAddAchievement(int param_1)

{
  OFDelegate *local_cc [2];
  int local_c4;
  class_t *local_c0;
  char *local_bc;
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
  local_8c = (undefined1 *)local_cc;
  local_9c = PTR_001b615c;
  local_98 = &GCC_except_table0;
  local_90 = &LAB_0000798c;
  local_c4 = param_1;
  __Unwind_SjLj_Register(auStack_b4);
  local_c0 = &objc::class_t::OFAchievementService;
  local_bc = "unlockAchievement:onSuccess:onFailure:";
  local_b0 = 0xffffffff;
  local_b8 = NSString::stringWithUTF8String_
                       ((ID)&_OBJC_CLASS___NSString,"stringWithUTF8String:",
                        *(undefined4 *)(PTR__OFAID_001b61b8 + local_c4 * 4));
  OFDelegate::OFDelegate(aOStack_70);
  local_b0 = 2;
  OFDelegate::OFDelegate(&OStack_80);
  local_cc[0] = &OStack_80;
  local_b0 = 1;
  _objc_msgSend((ID)local_c0,local_bc,local_b8,aOStack_70);
  local_b0 = 2;
  OFDelegate::~OFDelegate(&OStack_80);
  local_b0 = 0xffffffff;
  OFDelegate::~OFDelegate(aOStack_70);
  __Unwind_SjLj_Unregister(auStack_b4);
  return;
}
