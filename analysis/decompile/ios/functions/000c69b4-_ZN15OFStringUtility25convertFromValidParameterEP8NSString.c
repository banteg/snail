/*
 * mangled: _ZN15OFStringUtility25convertFromValidParameterEP8NSString
 * demangled: OFStringUtility::convertFromValidParameter(NSString*)
 * address: 000c69b4
 * size: 68
 */

/* OFStringUtility::convertFromValidParameter(NSString*) */

OFStringUtility * __thiscall
OFStringUtility::convertFromValidParameter(OFStringUtility *this,NSString *param_1)

{
  ID IVar1;

  IVar1 = _CFURLCreateStringByReplacingPercentEscapes(0,param_1,&cf___);
  IVar1 = _objc_msgSend(IVar1,"autorelease");
  *(ID *)this = IVar1;
  if (IVar1 != 0) {
    _objc_msgSend(IVar1,"retain");
  }
  return this;
}
