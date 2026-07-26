/*
 * mangled: _ZN12_GLOBAL__N_118readValueAsIntegerEPKcP12OFXmlElement
 * demangled: (anonymous namespace)::readValueAsInteger(char const*, OFXmlElement*)
 * address: 000c3064
 * size: 192
 */

/* (anonymous namespace)::readValueAsInteger(char const*, OFXmlElement*) */

OFSmartObject * (anonymous_namespace)::readValueAsInteger(char *param_1,OFXmlElement *param_2)

{
  undefined1 auStack_ac [4];
  OFXmlElement *local_a8;
  char *local_a4;
  OFSmartObject *local_a0;
  OFSmartObject *local_9c;
  undefined1 auStack_98 [4];
  undefined4 local_94;
  undefined *local_80;
  undefined *local_7c;
  undefined1 *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  OFXmlElement local_64;

  local_78 = &stack0xfffffff8;
  local_70 = auStack_ac;
  local_80 = PTR_001b615c;
  local_7c = &::GCC_except_table0;
  local_74 = &LAB_000c3124;
  local_a8 = param_2;
  local_a4 = param_1;
  __Unwind_SjLj_Register(auStack_98);
  local_94 = 0xffffffff;
  OFXmlElement::dequeueNextUnreadChild(&local_64,(char *)local_a8);
  local_9c = (OFSmartObject *)local_64.field0_0x0;
  if ((OFSmartObject *)local_64.field0_0x0 == (OFSmartObject *)0x0) {
    local_a0 = (OFSmartObject *)local_64.field0_0x0;
  }
  else {
    local_94 = 1;
    local_a0 = (OFSmartObject *)_objc_msgSend(*(ID *)((int)local_64.field0_0x0 + 8),"integerValue");
    local_94 = 0xffffffff;
    OFSmartObject::Release(local_9c);
  }
  __Unwind_SjLj_Unregister(auStack_98);
  return local_a0;
}
