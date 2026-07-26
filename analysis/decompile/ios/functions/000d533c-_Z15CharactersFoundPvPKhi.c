/*
 * mangled: _Z15CharactersFoundPvPKhi
 * demangled: CharactersFound(void*, unsigned char const*, int)
 * address: 000d533c
 * size: 208
 */

/* CharactersFound(void*, unsigned char const*, int) */

undefined4 CharactersFound(void *param_1,uchar *param_2,int param_3)

{
  ID IVar1;
  ID IVar2;
  ID self;

  IVar1 = _objc_msgSend((ID)param_1,"activeElement");
  IVar2 = NSString::alloc((ID)&_OBJC_CLASS___NSString,"alloc");
  IVar2 = NSString::initWithBytes_length_encoding_
                    (IVar2,"initWithBytes:length:encoding:",param_2,param_3,4);
  self = NSString::autorelease(IVar2,"autorelease");
  IVar2 = 0;
  if (*(ID *)(IVar1 + 8) != 0) {
    self = _objc_msgSend(*(ID *)(IVar1 + 8),"stringByAppendingString:",self);
    IVar2 = *(ID *)(IVar1 + 8);
  }
  if (self != IVar2) {
    if (IVar2 != 0) {
      _objc_msgSend(IVar2,"release");
    }
    *(ID *)(IVar1 + 8) = self;
    if (self != 0) {
      _objc_msgSend(self,"retain");
    }
  }
  return 0;
}
