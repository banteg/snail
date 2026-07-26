/*
 * mangled: _ZN14OFReachability14removeObserverEP23OFIReachabilityObserver
 * demangled: OFReachability::removeObserver(OFIReachabilityObserver*)
 * address: 000d2dd8
 * size: 92
 */

/* WARNING: Removing unreachable block (ram,0x000d2e30) */
/* OFReachability::removeObserver(OFIReachabilityObserver*) */

void __thiscall
OFReachability::removeObserver(OFReachability *this,OFIReachabilityObserver *param_1)

{
  OFReachability *pOVar1;
  OFReachability *pOVar2;

  pOVar1 = this + 8;
  pOVar2 = *(OFReachability **)pOVar1;
  while( true ) {
    if (pOVar1 == pOVar2) {
      return;
    }
    if (*(OFIReachabilityObserver **)(pOVar2 + 8) == param_1) break;
    pOVar2 = *(OFReachability **)pOVar2;
  }
  if (pOVar1 != pOVar2) {
    std::_List_node_base::unhook();
    operator_delete(pOVar2);
    return;
  }
  return;
}
