/*
 * mangled: _ZNK10OFDelegate6invokeEP8NSObject
 * demangled: OFDelegate::invoke(NSObject*) const
 * address: 000c5f70
 * size: 104
 */

/* OFDelegate::invoke(NSObject*) const */

void __thiscall OFDelegate::invoke(OFDelegate *this,NSObject *param_1)

{
  uint unaff_r4;

  if (((SEL)this->field0_0x0 != (SEL)0x0) && (this->field2_0x8 != 0)) {
    OFDeferredThreadedCallback::
    deferredThreadedCallbackWith_selector_paramOne_paramTwo_onThread_withDelay_
              ((OFDeferredThreadedCallback *)&objc::class_t::OFDeferredThreadedCallback,
               (ID)"deferredThreadedCallbackWith:selector:paramOne:paramTwo:onThread:withDelay:",
               (SEL)this->field0_0x0,(ID)this->field3_0xc,(SEL)param_1,this->field1_0x4,
               this->field2_0x8,0,(double)((ulonglong)unaff_r4 << 0x20));
  }
  return;
}
