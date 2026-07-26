/*
 * mangled: _ZN13OFViewDataMapD1Ev
 * demangled: OFViewDataMap::~OFViewDataMap()
 * address: 000d97e4
 * size: 248
 */

/* OFViewDataMap::~OFViewDataMap() */

void __thiscall OFViewDataMap::~OFViewDataMap(OFViewDataMap *this)

{
  OFViewDataMap *local_ac;
  OFViewDataMap *local_a8;
  ID *local_a0;
  SEL local_9c;
  ID *local_98;
  undefined1 auStack_94 [4];
  undefined4 local_90;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = (undefined1 *)&local_ac;
  local_7c = PTR_001b615c;
  local_78 = &GCC_except_table6;
  local_70 = &LAB_000d98dc;
  local_ac = this;
  __Unwind_SjLj_Register(auStack_94);
  *(undefined ***)local_ac = &PTR_GetRTTI_001b7604;
  local_a8 = local_ac + 8;
  local_a0 = *(ID **)(local_ac + 0xc);
  if (*(ID **)(local_ac + 8) != local_a0) {
    local_9c = "release";
    local_98 = *(ID **)(local_ac + 8);
    do {
      if (*local_98 != 0) {
        local_90 = 1;
        _objc_msgSend(*local_98,local_9c);
      }
      local_98 = local_98 + 3;
    } while (local_a0 != local_98);
  }
  if (*(void **)local_a8 != (void *)0x0) {
    operator_delete(*(void **)local_a8);
  }
  local_90 = 0xffffffff;
  OFSmartObject::~OFSmartObject((OFSmartObject *)local_ac);
  __Unwind_SjLj_Unregister(auStack_94);
  return;
}
