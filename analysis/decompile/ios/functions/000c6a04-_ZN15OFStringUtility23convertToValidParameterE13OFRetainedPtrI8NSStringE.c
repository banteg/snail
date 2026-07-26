/*
 * mangled: _ZN15OFStringUtility23convertToValidParameterE13OFRetainedPtrI8NSStringE
 * demangled: OFStringUtility::convertToValidParameter(OFRetainedPtr<NSString>)
 * address: 000c6a04
 * size: 96
 */

/* OFStringUtility::convertToValidParameter(OFRetainedPtr<NSString>) */

OFStringUtility * __thiscall
OFStringUtility::convertToValidParameter(OFStringUtility *this,undefined4 *param_2)

{
  ID IVar1;

  IVar1 = _CFURLCreateStringByAddingPercentEscapes
                    (0,*param_2,0,&cf__________________________<>___,0x8000100);
  IVar1 = _objc_msgSend(IVar1,"autorelease");
  *(ID *)this = IVar1;
  if (IVar1 != 0) {
    _objc_msgSend(IVar1,"retain");
  }
  return this;
}
