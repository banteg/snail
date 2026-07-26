/*
 * mangled: _ZN22OFBlobDownloadObserver21onFinishedDownloadingEP29OFHttpServiceRequestContainer
 * demangled: OFBlobDownloadObserver::onFinishedDownloading(OFHttpServiceRequestContainer*)
 * address: 000ce8f4
 * size: 260
 */

/* OFBlobDownloadObserver::onFinishedDownloading(OFHttpServiceRequestContainer*) */

void __thiscall
OFBlobDownloadObserver::onFinishedDownloading
          (OFBlobDownloadObserver *this,OFHttpServiceRequestContainer *param_1)

{
  ID IVar1;
  ID IVar2;
  NSObject *pNVar3;
  ID IVar4;

  IVar1 = _objc_msgSend(*(ID *)(param_1 + 8),"getResponse");
  IVar1 = _objc_msgSend(IVar1,"statusCode");
  if (IVar1 - 200 < 100) {
    IVar2 = *(ID *)(param_1 + 0x10);
    if (IVar2 == 0) {
      IVar2 = _objc_msgSend(*(ID *)(param_1 + 8),"data");
    }
    if (this[0x28] == (OFBlobDownloadObserver)0x0) {
      pNVar3 = (NSObject *)
               OFCompressableData::uncompressedDataFromSerializedData_
                         ((ID)&objc::class_t::OFCompressableData,
                          "uncompressedDataFromSerializedData:",IVar2);
      OFDelegate::invoke((OFDelegate *)(this + 8),pNVar3);
    }
    else {
      IVar4 = _objc_msgSend((ID)&objc::class_t::OFS3Response,"alloc");
      IVar1 = OFS3Response::initWithData_andUserParam_andStatusCode_
                        (IVar4,"initWithData:andUserParam:andStatusCode:",IVar2,
                         *(ID *)(param_1 + 0x1c),IVar1);
      pNVar3 = (NSObject *)_objc_msgSend(IVar1,"autorelease");
      OFDelegate::invoke((OFDelegate *)(this + 8),pNVar3);
    }
    return;
  }
  invokeFailure(this,param_1);
  return;
}
