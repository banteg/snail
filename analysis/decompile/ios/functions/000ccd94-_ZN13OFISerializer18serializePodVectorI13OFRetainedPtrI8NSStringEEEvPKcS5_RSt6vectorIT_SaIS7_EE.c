/*
 * mangled: _ZN13OFISerializer18serializePodVectorI13OFRetainedPtrI8NSStringEEEvPKcS5_RSt6vectorIT_SaIS7_EE
 * demangled: void OFISerializer::serializePodVector<OFRetainedPtr<NSString>>(char const*, char const*, std::vector<OFRetainedPtr<NSString>, std::allocator<OFRetainedPtr<NSString>>>&)
 * address: 000ccd94
 * size: 776
 */

/* void OFISerializer::serializePodVector<OFRetainedPtr<NSString> >(char const*, char const*,
   std::vector<OFRetainedPtr<NSString>, std::allocator<OFRetainedPtr<NSString> > >&) */

void __thiscall
OFISerializer::serializePodVector<OFRetainedPtr<NSString>>
          (OFISerializer *this,char *param_1,char *param_2,vector *param_3)

{
  int iVar1;
  ID self;
  ID *pIVar2;
  int local_d4 [2];
  vector *local_cc;
  char *local_c8;
  char *local_c4;
  OFISerializer *local_c0;
  uint local_bc;
  ID *local_b8;
  ID *local_b4;
  SEL local_b0;
  char *local_ac;
  SEL local_a8;
  OFISerializer *local_a4;
  ID *local_a0;
  undefined1 auStack_9c [4];
  undefined4 local_98;
  undefined *local_84;
  undefined *local_80;
  undefined1 *local_7c;
  undefined1 *local_78;
  undefined1 *local_74;
  ID local_68;
  ulong local_64 [17];

  local_7c = &stack0xfffffff8;
  local_74 = (undefined1 *)local_d4;
  local_84 = PTR_001b615c;
  local_80 = &GCC_except_table19;
  local_78 = &LAB_000cd09c;
  local_cc = param_3;
  local_c8 = param_2;
  local_c4 = param_1;
  local_c0 = this;
  __Unwind_SjLj_Register(auStack_9c);
  if (local_c4 != (char *)0x0) {
    local_98 = 0xffffffff;
    pushScope(local_c0,local_c4,true);
    local_a4 = local_c0;
  }
  local_64[0] = *(int *)(local_cc + 4) - *(int *)local_cc >> 2;
  local_98 = 4;
  (**(code **)(*(int *)local_c0 + 0x3c))(local_c0,local_64);
  iVar1 = (**(code **)(*(int *)local_c0 + 0x10))(local_c0);
  if (iVar1 != 0) {
    local_b4 = *(ID **)local_cc;
    local_b8 = *(ID **)(local_cc + 4);
    if (local_b4 != local_b8) {
      local_b0 = "release";
      local_a0 = local_b4;
      do {
        if (*local_a0 != 0) {
          local_98 = 2;
          _objc_msgSend(*local_a0,local_b0);
        }
        local_a0 = local_a0 + 1;
      } while (local_b8 != local_a0);
    }
    *(ID **)(local_cc + 4) = local_b4;
    local_98 = 4;
    std::vector<OFRetainedPtr<NSString>,std::allocator<OFRetainedPtr<NSString>>>::reserve
              ((vector<OFRetainedPtr<NSString>,std::allocator<OFRetainedPtr<NSString>>> *)local_cc,
               local_64[0]);
  }
  if (local_64[0] != 0) {
    local_bc = 0;
    local_a8 = "release";
    local_ac = "retain";
    do {
      local_68 = 0;
      local_98 = 3;
      iVar1 = (**(code **)(*(int *)local_c0 + 0x10))(local_c0);
      if ((iVar1 == 0) &&
         (local_d4[0] = *(int *)local_cc, *(ID *)(local_d4[0] + local_bc * 4) != local_68)) {
        if (local_68 != 0) {
          _objc_msgSend(local_68,local_a8);
        }
        local_68 = *(ID *)(local_d4[0] + local_bc * 4);
        if (local_68 != 0) {
          local_98 = 3;
          _objc_msgSend(local_68,local_ac);
        }
      }
      local_98 = 3;
      io(local_c0,local_c8,(OFRetainedPtr *)&local_68);
      self = (**(code **)(*(int *)local_c0 + 0x10))(local_c0);
      if (self != 0) {
        pIVar2 = *(ID **)(local_cc + 4);
        if (pIVar2 == *(ID **)(local_cc + 8)) {
          local_98 = 3;
          std::vector<OFRetainedPtr<NSString>,std::allocator<OFRetainedPtr<NSString>>>::
          _M_insert_aux((vector<OFRetainedPtr<NSString>,std::allocator<OFRetainedPtr<NSString>>> *)
                        local_cc,pIVar2,&local_68);
        }
        else {
          if (pIVar2 != (ID *)0x0) {
            *pIVar2 = local_68;
            self = local_68;
          }
          if (pIVar2 != (ID *)0x0 && self != 0) {
            local_98 = 1;
            _objc_msgSend(self,local_ac);
          }
          *(int *)(local_cc + 4) = *(int *)(local_cc + 4) + 4;
        }
      }
      if (local_68 != 0) {
        local_98 = 4;
        _objc_msgSend(local_68,local_a8);
      }
      local_bc = local_bc + 1;
    } while (local_bc < local_64[0]);
  }
  if (local_c4 != (char *)0x0) {
    local_98 = 0xffffffff;
    popScope(local_a4);
  }
  __Unwind_SjLj_Unregister(auStack_9c);
  return;
}
