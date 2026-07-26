/*
 * mangled: _ZNK10OFDelegate6invokeEP8NSObjectd
 * demangled: OFDelegate::invoke(NSObject*, double) const
 * address: 000c5fe0
 * size: 104
 */

/* OFDelegate::invoke(NSObject*, double) const */

void OFDelegate::invoke(NSObject *param_1,double param_2)

{
  SEL in_r1;
  ID in_r2;
  undefined4 in_r3;
  undefined4 unaff_r4;

  if ((*(SEL *)param_1 != (SEL)0x0) && (*(ID *)(param_1 + 8) != 0)) {
    OFDeferredThreadedCallback::
    deferredThreadedCallbackWith_selector_paramOne_paramTwo_onThread_withDelay_
              ((OFDeferredThreadedCallback *)&objc::class_t::OFDeferredThreadedCallback,
               (ID)"deferredThreadedCallbackWith:selector:paramOne:paramTwo:onThread:withDelay:",
               *(SEL *)param_1,*(ID *)(param_1 + 0xc),in_r1,*(ID *)(param_1 + 4),
               *(ID *)(param_1 + 8),in_r2,(double)CONCAT44(unaff_r4,in_r3));
  }
  return;
}
