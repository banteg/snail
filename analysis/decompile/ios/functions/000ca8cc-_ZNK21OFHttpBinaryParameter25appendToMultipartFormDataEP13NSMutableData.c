/*
 * mangled: _ZNK21OFHttpBinaryParameter25appendToMultipartFormDataEP13NSMutableData
 * demangled: OFHttpBinaryParameter::appendToMultipartFormData(NSMutableData*) const
 * address: 000ca8cc
 * size: 356
 */

/* OFHttpBinaryParameter::appendToMultipartFormData(NSMutableData*) const */

void __thiscall
OFHttpBinaryParameter::appendToMultipartFormData(OFHttpBinaryParameter *this,NSMutableData *param_1)

{
  ID IVar1;
  ID self;
  ID self_00;
  undefined4 uVar2;
  undefined4 uVar3;

  IVar1 = NSString::stringWithFormat_
                    ((ID)&_OBJC_CLASS___NSString,"stringWithFormat:",
                     &cf_Content_Disposition_form_data_name______filename________,
                     *(undefined4 *)(this + 8),*(undefined4 *)(this + 8),*(undefined4 *)(this + 0xc)
                    );
  self = NSString::stringWithFormat_
                   ((ID)&_OBJC_CLASS___NSString,"stringWithFormat:",&cf_Content_Type___,
                    *(undefined4 *)(this + 0xc));
  self_00 = NSString::stringWithFormat_
                      ((ID)&_OBJC_CLASS___NSString,"stringWithFormat:",
                       &cf_Content_Transfer_Encoding_binary);
  IVar1 = NSString::dataUsingEncoding_(IVar1,"dataUsingEncoding:",4);
  _objc_msgSend((ID)param_1,"appendData:",IVar1);
  IVar1 = NSString::dataUsingEncoding_(self,"dataUsingEncoding:",4);
  _objc_msgSend((ID)param_1,"appendData:",IVar1);
  IVar1 = NSString::dataUsingEncoding_(self_00,"dataUsingEncoding:",4);
  _objc_msgSend((ID)param_1,"appendData:",IVar1);
  IVar1 = _objc_msgSend(0x1b8644,"dataUsingEncoding:",4);
  _objc_msgSend((ID)param_1,"appendData:",IVar1);
  uVar2 = OFBinaryMemorySink::getDataBuffer(*(OFBinaryMemorySink **)(this + 0x10));
  uVar3 = OFBinaryMemorySink::getDataSize(*(OFBinaryMemorySink **)(this + 0x10));
  _objc_msgSend((ID)param_1,"appendBytes:length:",uVar2,uVar3);
  IVar1 = _objc_msgSend(0x1b8644,"dataUsingEncoding:",4);
  _objc_msgSend((ID)param_1,"appendData:",IVar1);
  return;
}
