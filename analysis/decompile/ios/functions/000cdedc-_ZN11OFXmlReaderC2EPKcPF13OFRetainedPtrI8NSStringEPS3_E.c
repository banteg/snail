/*
 * mangled: _ZN11OFXmlReaderC2EPKcPF13OFRetainedPtrI8NSStringEPS3_E
 * demangled: OFXmlReader::OFXmlReader(char const*, OFRetainedPtr<NSString> (*)(NSString*))
 * address: 000cdedc
 * size: 440
 */

/* OFXmlReader::OFXmlReader(char const*, OFRetainedPtr<NSString> (*)(NSString*)) */

void __thiscall
OFXmlReader::OFXmlReader(OFXmlReader *this,char *param_1,_func_OFRetainedPtr_NSString_ptr *param_2)

{
  ID IVar1;
  undefined1 auStack_d0 [4];
  _func_OFRetainedPtr_NSString_ptr *local_cc;
  char *local_c8;
  OFISerializer *local_c4;
  ID local_c0;
  SEL local_bc;
  class_t *local_b8;
  SEL local_b4;
  ID local_b0;
  ID local_ac;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = auStack_d0;
  local_7c = PTR_001b615c;
  local_78 = &GCC_except_table11;
  local_70 = &LAB_000ce094;
  local_cc = param_2;
  local_c8 = param_1;
  local_c4 = (OFISerializer *)this;
  __Unwind_SjLj_Register(auStack_94);
  local_90 = 0xffffffff;
  OFISerializer::OFISerializer(local_c4);
  *(undefined ***)local_c4 = &PTR_GetRTTI_001b7464;
  *(undefined4 *)(local_c4 + 0x18) = 0;
  *(_func_OFRetainedPtr_NSString_ptr **)(local_c4 + 0x1c) = local_cc;
  local_90 = 2;
  local_c0 = NSBundle::mainBundle((ID)&_OBJC_CLASS___NSBundle,"mainBundle");
  local_bc = "pathForResource:ofType:";
  IVar1 = NSString::stringWithUTF8String_
                    ((ID)&_OBJC_CLASS___NSString,"stringWithUTF8String:",local_c8);
  local_ac = _objc_msgSend(local_c0,local_bc,IVar1,&cf_xml);
  IVar1 = NSFileManager::defaultManager((ID)&_OBJC_CLASS___NSFileManager,"defaultManager");
  IVar1 = NSFileManager::fileExistsAtPath_(IVar1,"fileExistsAtPath:",local_ac);
  if ((IVar1 & 0xff) != 0) {
    local_b8 = &objc::class_t::OFXmlDocument;
    local_b4 = "xmlDocumentWithData:";
    IVar1 = NSData::dataWithContentsOfFile_
                      ((ID)&_OBJC_CLASS___NSData,"dataWithContentsOfFile:",local_ac);
    local_b0 = _objc_msgSend((ID)local_b8,local_b4,IVar1);
    IVar1 = *(ID *)(local_c4 + 0x18);
    if (local_b0 != IVar1) {
      if (IVar1 != 0) {
        _objc_msgSend(IVar1,"release");
      }
      *(ID *)(local_c4 + 0x18) = local_b0;
      if (local_b0 != 0) {
        local_90 = 2;
        _objc_msgSend(local_b0,"retain");
      }
    }
  }
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
