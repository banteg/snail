/*
 * mangled: _ZN16OFViewDataGetterD1Ev
 * demangled: OFViewDataGetter::~OFViewDataGetter()
 * address: 000fc490
 * size: 160
 */

/* OFViewDataGetter::~OFViewDataGetter() */

void __thiscall OFViewDataGetter::~OFViewDataGetter(OFViewDataGetter *this)

{
  OFViewDataGetter *local_9c [2];
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = (undefined1 *)local_9c;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table0;
  local_70 = &LAB_000fc530;
  local_9c[0] = this;
  __Unwind_SjLj_Register(auStack_94);
  if (*(OFSmartObject **)(local_9c[0] + 4) != (OFSmartObject *)0x0) {
    local_90 = 1;
    OFSmartObject::Release(*(OFSmartObject **)(local_9c[0] + 4));
  }
  if (*(ID *)local_9c[0] != 0) {
    local_90 = 0xffffffff;
    _objc_msgSend(*(ID *)local_9c[0],"release");
  }
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
