/*
 * mangled: _ZN22OFReachabilityObserver31onGameServerReachabilityChangesE19NetworkReachabilityS0_
 * demangled: OFReachabilityObserver::onGameServerReachabilityChanges(NetworkReachability, NetworkReachability)
 * address: 000b166c
 * size: 48
 */

/* OFReachabilityObserver::onGameServerReachabilityChanges(NetworkReachability, NetworkReachability)
    */

void OFReachabilityObserver::onGameServerReachabilityChanges(int param_1)

{
  NSObject *pNVar1;

  pNVar1 = (NSObject *)NSNumber::numberWithInt_((ID)&_OBJC_CLASS___NSNumber,"numberWithInt:");
  OFDelegate::invoke((OFDelegate *)(param_1 + 0xc),pNVar1);
  return;
}
