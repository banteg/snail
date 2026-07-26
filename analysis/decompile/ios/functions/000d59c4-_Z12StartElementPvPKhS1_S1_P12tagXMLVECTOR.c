/*
 * mangled: _Z12StartElementPvPKhS1_S1_P12tagXMLVECTOR
 * demangled: StartElement(void*, unsigned char const*, unsigned char const*, unsigned char const*, tagXMLVECTOR*)
 * address: 000d59c4
 * size: 560
 */

/* StartElement(void*, unsigned char const*, unsigned char const*, unsigned char const*,
   tagXMLVECTOR*) */

undefined4
StartElement(void *param_1,uchar *param_2,uchar *param_3,uchar *param_4,tagXMLVECTOR *param_5)

{
  ID IVar1;
  undefined1 auStack_c8 [4];
  uchar *local_c4;
  void *local_c0;
  undefined *local_bc;
  char *local_b8;
  NSString *local_b4;
  OFXmlElement *local_b0;
  ID local_ac;
  undefined4 *local_a8;
  char *local_a4;
  ID local_a0;
  int local_9c;
  OFXmlElement *local_98;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = auStack_c8;
  local_7c = PTR_001b615c;
  local_78 = &GCC_except_table3;
  local_70 = &LAB_000d5bf4;
  local_c4 = param_4;
  local_c0 = param_1;
  __Unwind_SjLj_Register(auStack_94);
  local_bc = &_OBJC_CLASS___NSString;
  local_b8 = "stringWithUTF8String:";
  local_90 = 0xffffffff;
  local_b4 = (NSString *)
             NSString::stringWithUTF8String_
                       ((ID)&_OBJC_CLASS___NSString,"stringWithUTF8String:",local_c4);
  local_b0 = operator_new(0x24);
  local_90 = 2;
  local_98 = local_b0;
  OFXmlElement::OFXmlElement(local_b0,local_b4);
  if (local_b0 != (OFXmlElement *)0x0) {
    local_98->field1_0x4 = local_98->field1_0x4 + 1;
  }
  if (0 < *(int *)param_5) {
    local_90 = 1;
    local_ac = NSMutableDictionary::dictionaryWithCapacity_
                         ((ID)&_OBJC_CLASS___NSMutableDictionary,"dictionaryWithCapacity:");
    if (0 < *(int *)param_5) {
      local_a4 = "setObject:forKey:";
      local_9c = 0;
      do {
        local_90 = 1;
        local_a8 = (undefined4 *)_XMLVector_Get(param_5,local_9c);
        local_a0 = _objc_msgSend((ID)local_bc,local_b8,local_a8[1]);
        IVar1 = _objc_msgSend((ID)local_bc,local_b8,*local_a8);
        _objc_msgSend(local_ac,local_a4,local_a0,IVar1);
        local_9c = local_9c + 1;
      } while (local_9c < *(int *)param_5);
    }
    IVar1 = (local_98->field5_0x1c).field0_0x0;
    if (local_ac != IVar1) {
      if (IVar1 != 0) {
        local_90 = 1;
        _objc_msgSend(IVar1,"release");
      }
      (local_98->field5_0x1c).field0_0x0 = local_ac;
      if (local_ac != 0) {
        local_90 = 1;
        _objc_msgSend(local_ac,"retain");
      }
    }
  }
  local_90 = 1;
  _objc_msgSend((ID)local_c0,"elementStarted:",local_98);
  if (local_b0 != (OFXmlElement *)0x0) {
    local_90 = 0xffffffff;
    OFSmartObject::Release((OFSmartObject *)local_98);
  }
  __Unwind_SjLj_Unregister(auStack_94);
  return 0;
}
