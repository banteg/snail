/*
 * mangled: _ZN14OFReachabilityC2Ev
 * demangled: OFReachability::OFReachability()
 * address: 000d30d4
 * size: 536
 */

/* OFReachability::OFReachability() */

void __thiscall OFReachability::OFReachability(OFReachability *this)

{
  undefined4 *puVar1;
  ID IVar2;
  undefined4 uVar3;
  uint uVar4;
  OFReachability *pOVar5;
  undefined1 auStack_c8 [4];
  OFReachability *local_c4;
  undefined *local_c0;
  SEL local_bc;
  ID local_b8;
  undefined4 local_b0;
  OFReachability *local_ac;
  OFReachability *local_a0;
  undefined4 local_9c;
  undefined1 auStack_98 [4];
  undefined4 local_94;
  undefined *local_80;
  undefined *local_7c;
  undefined1 *local_78;
  undefined1 *local_74;
  undefined1 *local_70;
  uint local_64;

  local_78 = &stack0xfffffff8;
  local_70 = auStack_c8;
  local_80 = PTR_001b615c;
  local_7c = &::GCC_except_table3;
  local_74 = &LAB_000d32ec;
  local_c4 = this;
  __Unwind_SjLj_Register(auStack_98);
  *(undefined4 *)local_c4 = 0;
  *(undefined4 *)(local_c4 + 8) = 0;
  *(undefined4 *)(local_c4 + 0xc) = 0;
  local_ac = local_c4 + 8;
  *(OFReachability **)(local_c4 + 8) = local_ac;
  *(OFReachability **)(local_c4 + 0xc) = local_ac;
  local_c0 = &_OBJC_CLASS___NSURL;
  local_bc = "URLWithString:";
  local_94 = 2;
  puVar1 = (undefined4 *)OFSettings::Instance();
  local_b8 = _objc_msgSend((ID)local_c0,local_bc,*puVar1);
  if (local_b8 != 0) {
    _objc_msgSend(local_b8,"retain");
  }
  local_94 = 1;
  IVar2 = _objc_msgSend(local_b8,"host");
  IVar2 = _objc_msgSend(IVar2,"UTF8String");
  uVar3 = _SCNetworkReachabilityCreateWithName(0,IVar2);
  *(undefined4 *)(local_c4 + 4) = uVar3;
  _SCNetworkReachabilitySetCallback(uVar3,networkReachabilityCallBack,0);
  local_9c = *(undefined4 *)(local_c4 + 4);
  uVar3 = _CFRunLoopGetMain();
  _SCNetworkReachabilityScheduleWithRunLoop(local_9c,uVar3,*(undefined4 *)PTR_001b6388);
  local_64 = 0;
  _SCNetworkReachabilityGetFlags(*(undefined4 *)(local_c4 + 4));
  local_b0 = *(undefined4 *)local_c4;
  if ((local_64 & 0x40000) == 0) {
    if ((local_64 & 4) == 0) {
      uVar4 = 1;
    }
    else {
      uVar4 = 0;
    }
  }
  else {
    uVar4 = 1;
  }
  uVar3 = 0;
  if ((uVar4 & local_64 >> 1) != 0) {
    if ((local_64 & 0x40000) == 0) {
      uVar3 = 2;
    }
    else {
      uVar3 = 1;
    }
  }
  *(undefined4 *)local_c4 = uVar3;
  pOVar5 = *(OFReachability **)(local_c4 + 8);
  local_a0 = pOVar5;
  if (pOVar5 != local_ac) {
    do {
      local_94 = 1;
      local_a0 = pOVar5;
      (**(code **)(**(int **)(pOVar5 + 8) + 8))
                (*(int **)(pOVar5 + 8),local_b0,*(undefined4 *)local_c4);
      pOVar5 = *(OFReachability **)local_a0;
    } while (pOVar5 != local_ac);
  }
  if (local_b8 != 0) {
    local_94 = 2;
    _objc_msgSend(local_b8,"release");
  }
  __Unwind_SjLj_Unregister(auStack_98);
  return;
}
