/*
 * mangled: _ZN13OFHttpService17cancelAllRequestsEv
 * demangled: OFHttpService::cancelAllRequests()
 * address: 000cff04
 * size: 60
 */

/* OFHttpService::cancelAllRequests() */

void __thiscall OFHttpService::cancelAllRequests(OFHttpService *this)

{
  OFHttpServiceRequestContainer *pOVar1;
  OFHttpServiceRequestContainer *pOVar2;
  OFHttpServiceRequestContainer *pOVar3;

  pOVar2 = (this->field5_0x14).field0_0x0.field0_0x0;
  pOVar3 = (this->field5_0x14).field0_0x0.field1_0x4;
  if (pOVar2 != pOVar3) {
    do {
      pOVar1 = pOVar2 + 8;
      pOVar2 = pOVar2 + 0x24;
      _objc_msgSend(*(ID *)pOVar1,"cancelImmediately");
    } while (pOVar2 != pOVar3);
    return;
  }
  return;
}
