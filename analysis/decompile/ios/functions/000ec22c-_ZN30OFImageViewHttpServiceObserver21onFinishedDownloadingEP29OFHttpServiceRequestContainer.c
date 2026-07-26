/*
 * mangled: _ZN30OFImageViewHttpServiceObserver21onFinishedDownloadingEP29OFHttpServiceRequestContainer
 * demangled: OFImageViewHttpServiceObserver::onFinishedDownloading(OFHttpServiceRequestContainer*)
 * address: 000ec22c
 * size: 96
 */

/* OFImageViewHttpServiceObserver::onFinishedDownloading(OFHttpServiceRequestContainer*) */

void __thiscall
OFImageViewHttpServiceObserver::onFinishedDownloading
          (OFImageViewHttpServiceObserver *this,OFHttpServiceRequestContainer *param_1)

{
  NSObject *self;
  ID IVar1;

  self = *(NSObject **)(param_1 + 0x10);
  if (self == (NSObject *)0x0) {
    self = (NSObject *)_objc_msgSend(*(ID *)(param_1 + 8),"data");
  }
  IVar1 = _objc_msgSend((ID)self,"length");
  if (IVar1 != 0) {
    OFDelegate::invoke((OFDelegate *)(this + 8),self);
    return;
  }
  OFDelegate::invoke((OFDelegate *)(this + 0x18),(NSObject *)0x0);
  return;
}
