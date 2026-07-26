/*
 * mangled: _ZNK16OFViewDataGetter18writeValueUISwitchEP6UIViewP8NSStringP18OFOutputSerializer
 * demangled: OFViewDataGetter::writeValueUISwitch(UIView*, NSString*, OFOutputSerializer*) const
 * address: 000fc3e8
 * size: 92
 */

/* OFViewDataGetter::writeValueUISwitch(UIView*, NSString*, OFOutputSerializer*) const */

void __thiscall
OFViewDataGetter::writeValueUISwitch
          (OFViewDataGetter *this,UIView *param_1,NSString *param_2,OFOutputSerializer *param_3)

{
  ID IVar1;
  char *pcVar2;
  bool local_11;

  IVar1 = _objc_msgSend((ID)param_1,"isOn");
  local_11 = (IVar1 & 0xff) != 0;
  pcVar2 = (char *)_objc_msgSend((ID)param_2,"UTF8String");
  OFISerializer::io((OFISerializer *)param_3,pcVar2,&local_11);
  return;
}
