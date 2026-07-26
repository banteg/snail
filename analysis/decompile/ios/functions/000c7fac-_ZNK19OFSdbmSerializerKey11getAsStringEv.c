/*
 * mangled: _ZNK19OFSdbmSerializerKey11getAsStringEv
 * demangled: OFSdbmSerializerKey::getAsString() const
 * address: 000c7fac
 * size: 148
 */

/* OFSdbmSerializerKey::getAsString() const */

void __thiscall OFSdbmSerializerKey::getAsString(OFSdbmSerializerKey *this)

{
  ID self;
  ID self_00;

  self = *(ID *)(this + 0xc);
  if (self == 0) {
    self_00 = NSString::stringWithFormat_
                        ((ID)&_OBJC_CLASS___NSString,"stringWithFormat:",&cf__x,
                         *(undefined4 *)(this + 8));
    self = *(ID *)(this + 0xc);
    if (self_00 != self) {
      if (self != 0) {
        _objc_msgSend(self,"release");
      }
      *(ID *)(this + 0xc) = self_00;
      self = 0;
      if (self_00 != 0) {
        NSString::retain(self_00,"retain");
        _objc_msgSend(*(ID *)(this + 0xc),"UTF8String");
        return;
      }
    }
  }
  _objc_msgSend(self,"UTF8String");
  return;
}
