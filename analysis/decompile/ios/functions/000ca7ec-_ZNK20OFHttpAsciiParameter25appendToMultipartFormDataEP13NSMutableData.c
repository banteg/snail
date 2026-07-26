/*
 * mangled: _ZNK20OFHttpAsciiParameter25appendToMultipartFormDataEP13NSMutableData
 * demangled: OFHttpAsciiParameter::appendToMultipartFormData(NSMutableData*) const
 * address: 000ca7ec
 * size: 200
 */

/* OFHttpAsciiParameter::appendToMultipartFormData(NSMutableData*) const */

void __thiscall
OFHttpAsciiParameter::appendToMultipartFormData(OFHttpAsciiParameter *this,NSMutableData *param_1)

{
  ID IVar1;

  IVar1 = NSString::stringWithFormat_
                    ((ID)&_OBJC_CLASS___NSString,"stringWithFormat:",
                     &cf_Content_Disposition_form_data_name_____,*(undefined4 *)(this + 8));
  IVar1 = NSString::dataUsingEncoding_(IVar1,"dataUsingEncoding:",4);
  _objc_msgSend((ID)param_1,"appendData:",IVar1);
  IVar1 = _objc_msgSend(0x1b8644,"dataUsingEncoding:",4);
  _objc_msgSend((ID)param_1,"appendData:",IVar1);
  IVar1 = _objc_msgSend(*(ID *)(this + 0xc),"dataUsingEncoding:",4);
  _objc_msgSend((ID)param_1,"appendData:",IVar1);
  IVar1 = _objc_msgSend(0x1b8644,"dataUsingEncoding:",4);
  _objc_msgSend((ID)param_1,"appendData:",IVar1);
  return;
}
