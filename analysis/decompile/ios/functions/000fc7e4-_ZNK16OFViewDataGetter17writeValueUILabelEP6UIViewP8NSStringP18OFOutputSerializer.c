/*
 * mangled: _ZNK16OFViewDataGetter17writeValueUILabelEP6UIViewP8NSStringP18OFOutputSerializer
 * demangled: OFViewDataGetter::writeValueUILabel(UIView*, NSString*, OFOutputSerializer*) const
 * address: 000fc7e4
 * size: 224
 */

/* OFViewDataGetter::writeValueUILabel(UIView*, NSString*, OFOutputSerializer*) const */

void __thiscall
OFViewDataGetter::writeValueUILabel
          (OFViewDataGetter *this,UIView *param_1,NSString *param_2,OFOutputSerializer *param_3)

{
  char *pcVar1;
  OFOutputSerializer *local_a8;
  NSString *local_a4;
  UIView *local_a0;
  undefined1 auStack_98 [4];
  undefined4 local_94;
  undefined *local_80;
  undefined *local_7c;
  undefined1 *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  ID local_64 [17];

  local_78 = &stack0xfffffff8;
  local_70 = (undefined1 *)&local_a8;
  local_80 = PTR_001b615c;
  local_7c = &::GCC_except_table4;
  local_74 = &LAB_000fc8c4;
  local_a8 = param_3;
  local_a4 = param_2;
  local_a0 = param_1;
  __Unwind_SjLj_Register(auStack_98);
  local_94 = 0xffffffff;
  local_64[0] = _objc_msgSend((ID)local_a0,"text");
  if (local_64[0] != 0) {
    _objc_msgSend(local_64[0],"retain");
  }
  local_94 = 1;
  pcVar1 = (char *)_objc_msgSend((ID)local_a4,"UTF8String");
  OFISerializer::io((OFISerializer *)local_a8,pcVar1,(OFRetainedPtr *)local_64);
  if (local_64[0] != 0) {
    local_94 = 0xffffffff;
    _objc_msgSend(local_64[0],"release");
  }
  __Unwind_SjLj_Unregister(auStack_98);
  return;
}
