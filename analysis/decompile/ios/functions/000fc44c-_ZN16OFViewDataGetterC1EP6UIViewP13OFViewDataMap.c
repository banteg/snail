/*
 * mangled: _ZN16OFViewDataGetterC1EP6UIViewP13OFViewDataMap
 * demangled: OFViewDataGetter::OFViewDataGetter(UIView*, OFViewDataMap*)
 * address: 000fc44c
 * size: 64
 */

/* OFViewDataGetter::OFViewDataGetter(UIView*, OFViewDataMap*) */

void __thiscall
OFViewDataGetter::OFViewDataGetter(OFViewDataGetter *this,UIView *param_1,OFViewDataMap *param_2)

{
  *(UIView **)this = param_1;
  if (param_1 != (UIView *)0x0) {
    _objc_msgSend((ID)param_1,"retain");
  }
  *(OFViewDataMap **)(this + 4) = param_2;
  if (param_2 != (OFViewDataMap *)0x0) {
    *(int *)(param_2 + 4) = *(int *)(param_2 + 4) + 1;
  }
  return;
}
