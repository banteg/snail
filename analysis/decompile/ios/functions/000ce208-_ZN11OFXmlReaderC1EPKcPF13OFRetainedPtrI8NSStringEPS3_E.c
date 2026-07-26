/*
 * mangled: _ZN11OFXmlReaderC1EPKcPF13OFRetainedPtrI8NSStringEPS3_E
 * demangled: OFXmlReader::OFXmlReader(char const*, OFRetainedPtr<NSString> (*)(NSString*))
 * address: 000ce208
 * size: 4
 */

/* OFXmlReader::OFXmlReader(char const*, OFRetainedPtr<NSString> (*)(NSString*)) */

void __thiscall
OFXmlReader::OFXmlReader(OFXmlReader *this,char *param_1,_func_OFRetainedPtr_NSString_ptr *param_2)

{
  ID IVar1;
  undefined1 auStack_d0 [4];
  _func_OFRetainedPtr_NSString_ptr *p_Stack_cc;
  char *pcStack_c8;
  OFISerializer *pOStack_c4;
  ID IStack_c0;
  SEL pcStack_bc;
  class_t *pcStack_b8;
  SEL pcStack_b4;
  ID IStack_b0;
  ID IStack_ac;
  undefined1 auStack_94 [4];
  undefined4 uStack_90;
  undefined *puStack_7c;
  undefined *puStack_78;
  undefined1 *puStack_74;
  undefined1 *puStack_70;
  undefined1 *puStack_6c;

  puStack_74 = &stack0xfffffff8;
  puStack_6c = auStack_d0;
  puStack_7c = PTR_001b615c;
  puStack_78 = &GCC_except_table11;
  puStack_70 = &LAB_000ce094;
  p_Stack_cc = param_2;
  pcStack_c8 = param_1;
  pOStack_c4 = (OFISerializer *)this;
  __Unwind_SjLj_Register(auStack_94);
  uStack_90 = 0xffffffff;
  OFISerializer::OFISerializer(pOStack_c4);
  *(undefined ***)pOStack_c4 = &PTR_GetRTTI_001b7464;
  *(undefined4 *)(pOStack_c4 + 0x18) = 0;
  *(_func_OFRetainedPtr_NSString_ptr **)(pOStack_c4 + 0x1c) = p_Stack_cc;
  uStack_90 = 2;
  IStack_c0 = NSBundle::mainBundle((ID)&_OBJC_CLASS___NSBundle,"mainBundle");
  pcStack_bc = "pathForResource:ofType:";
  IVar1 = NSString::stringWithUTF8String_
                    ((ID)&_OBJC_CLASS___NSString,"stringWithUTF8String:",pcStack_c8);
  IStack_ac = _objc_msgSend(IStack_c0,pcStack_bc,IVar1,&cf_xml);
  IVar1 = NSFileManager::defaultManager((ID)&_OBJC_CLASS___NSFileManager,"defaultManager");
  IVar1 = NSFileManager::fileExistsAtPath_(IVar1,"fileExistsAtPath:",IStack_ac);
  if ((IVar1 & 0xff) != 0) {
    pcStack_b8 = &objc::class_t::OFXmlDocument;
    pcStack_b4 = "xmlDocumentWithData:";
    IVar1 = NSData::dataWithContentsOfFile_
                      ((ID)&_OBJC_CLASS___NSData,"dataWithContentsOfFile:",IStack_ac);
    IStack_b0 = _objc_msgSend((ID)pcStack_b8,pcStack_b4,IVar1);
    IVar1 = *(ID *)(pOStack_c4 + 0x18);
    if (IStack_b0 != IVar1) {
      if (IVar1 != 0) {
        _objc_msgSend(IVar1,"release");
      }
      *(ID *)(pOStack_c4 + 0x18) = IStack_b0;
      if (IStack_b0 != 0) {
        uStack_90 = 2;
        _objc_msgSend(IStack_b0,"retain");
      }
    }
  }
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
