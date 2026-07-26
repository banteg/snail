/*
 * mangled: _ZNK20OFHttpAsciiParameter26getAsMPURLRequestParameterEv
 * demangled: OFHttpAsciiParameter::getAsMPURLRequestParameter() const
 * address: 000caad8
 * size: 88
 */

/* OFHttpAsciiParameter::getAsMPURLRequestParameter() const */

void __thiscall OFHttpAsciiParameter::getAsMPURLRequestParameter(OFHttpAsciiParameter *this)

{
  ID IVar1;
  cfstringStruct *pcVar2;

  pcVar2 = &cf___;
  if (*(cfstringStruct **)(this + 0xc) != (cfstringStruct *)0x0) {
    pcVar2 = *(cfstringStruct **)(this + 0xc);
  }
  IVar1 = _objc_msgSend((ID)&objc::class_t::MPURLRequestParameter,"alloc");
  IVar1 = MPURLRequestParameter::initWithName_andValue_
                    (IVar1,"initWithName:andValue:",*(ID *)(this + 8),(ID)pcVar2);
  _objc_msgSend(IVar1,"autorelease");
  return;
}
