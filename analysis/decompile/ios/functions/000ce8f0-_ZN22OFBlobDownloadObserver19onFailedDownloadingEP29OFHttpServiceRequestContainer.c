/*
 * mangled: _ZN22OFBlobDownloadObserver19onFailedDownloadingEP29OFHttpServiceRequestContainer
 * demangled: OFBlobDownloadObserver::onFailedDownloading(OFHttpServiceRequestContainer*)
 * address: 000ce8f0
 * size: 4
 */

/* OFBlobDownloadObserver::onFailedDownloading(OFHttpServiceRequestContainer*) */

void __thiscall
OFBlobDownloadObserver::onFailedDownloading
          (OFBlobDownloadObserver *this,OFHttpServiceRequestContainer *param_1)

{
  invokeFailure(this,param_1);
  return;
}
