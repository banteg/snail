/*
 * mangled: _ZNK21OFHttpBinaryParameter26getAsMPURLRequestParameterEv
 * demangled: OFHttpBinaryParameter::getAsMPURLRequestParameter() const
 * address: 000caa54
 * size: 116
 */

/* OFHttpBinaryParameter::getAsMPURLRequestParameter() const */

void __thiscall OFHttpBinaryParameter::getAsMPURLRequestParameter(OFHttpBinaryParameter *this)

{
  ID IVar1;
  ID IVar2;
  ID IVar3;

  IVar1 = _objc_msgSend((ID)&objc::class_t::MPURLRequestParameter,"alloc");
  IVar3 = *(ID *)(this + 8);
  IVar2 = OFBinaryMemorySink::getNSData(*(OFBinaryMemorySink **)(this + 0x10));
  IVar1 = MPURLRequestParameter::initWithName_andBlob_andDataType_
                    (IVar1,"initWithName:andBlob:andDataType:",IVar3,IVar2,*(ID *)(this + 0xc));
  _objc_msgSend(IVar1,"autorelease");
  return;
}
