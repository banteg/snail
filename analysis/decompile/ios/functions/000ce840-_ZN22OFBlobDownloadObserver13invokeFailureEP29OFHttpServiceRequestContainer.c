/*
 * mangled: _ZN22OFBlobDownloadObserver13invokeFailureEP29OFHttpServiceRequestContainer
 * demangled: OFBlobDownloadObserver::invokeFailure(OFHttpServiceRequestContainer*)
 * address: 000ce840
 * size: 152
 */

/* OFBlobDownloadObserver::invokeFailure(OFHttpServiceRequestContainer*) */

void __thiscall
OFBlobDownloadObserver::invokeFailure
          (OFBlobDownloadObserver *this,OFHttpServiceRequestContainer *param_1)

{
  ID IVar1;
  ID IVar2;
  NSObject *pNVar3;

  if (this[0x28] == (OFBlobDownloadObserver)0x0) {
    OFDelegate::invoke((OFDelegate *)(this + 0x18),(NSObject *)0x0);
  }
  else {
    IVar1 = _objc_msgSend(*(ID *)(param_1 + 8),"getResponse");
    IVar1 = _objc_msgSend(IVar1,"statusCode");
    IVar2 = _objc_msgSend((ID)&objc::class_t::OFS3Response,"alloc");
    IVar1 = OFS3Response::initWithData_andUserParam_andStatusCode_
                      (IVar2,"initWithData:andUserParam:andStatusCode:",0,*(ID *)(param_1 + 0x1c),
                       IVar1);
    pNVar3 = (NSObject *)_objc_msgSend(IVar1,"autorelease");
    OFDelegate::invoke((OFDelegate *)(this + 0x18),pNVar3);
  }
  return;
}
