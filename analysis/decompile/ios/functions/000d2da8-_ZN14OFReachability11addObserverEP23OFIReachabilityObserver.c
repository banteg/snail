/*
 * mangled: _ZN14OFReachability11addObserverEP23OFIReachabilityObserver
 * demangled: OFReachability::addObserver(OFIReachabilityObserver*)
 * address: 000d2da8
 * size: 44
 */

/* OFReachability::addObserver(OFIReachabilityObserver*) */

void __thiscall OFReachability::addObserver(OFReachability *this,OFIReachabilityObserver *param_1)

{
  _List_node_base *p_Var1;

  p_Var1 = operator_new(0xc);
  if (p_Var1 != (_List_node_base *)0xfffffff8) {
    *(OFIReachabilityObserver **)(p_Var1 + 8) = param_1;
  }
  std::_List_node_base::hook(p_Var1);
  return;
}
