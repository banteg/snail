/*
 * mangled: _ZN18OFBinaryMemorySink5writeEPKvj
 * demangled: OFBinaryMemorySink::write(void const*, unsigned int)
 * address: 000c85f8
 * size: 112
 */

/* OFBinaryMemorySink::write(void const*, unsigned int) */

void __thiscall OFBinaryMemorySink::write(OFBinaryMemorySink *this,void *param_1,uint param_2)

{
  ID self;
  ID self_00;

  self = NSData::dataWithBytes_length_
                   ((ID)&_OBJC_CLASS___NSData,"dataWithBytes:length:",param_1,param_2);
  self_00 = *(ID *)(this + 8);
  if (self == self_00) {
    return;
  }
  if (self_00 != 0) {
    _objc_msgSend(self_00,"release");
  }
  *(ID *)(this + 8) = self;
  if (self == 0) {
    return;
  }
  NSData::retain(self,"retain");
  return;
}
