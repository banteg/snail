/*
 * mangled: _ZN21OFHttpServiceObserverD0Ev
 * demangled: OFHttpServiceObserver::~OFHttpServiceObserver()
 * address: 000cea1c
 * size: 36
 */

/* OFHttpServiceObserver::~OFHttpServiceObserver() */

void __thiscall OFHttpServiceObserver::~OFHttpServiceObserver(OFHttpServiceObserver *this)

{
  *(undefined ***)this = &PTR_GetRTTI_001b750c;
  OFSmartObject::~OFSmartObject((OFSmartObject *)this);
  operator_delete(this);
  return;
}
