/*
 * mangled: _ZNSt6vectorI13OFRetainedPtrI8NSStringESaIS2_EE7reserveEm
 * demangled: std::vector<OFRetainedPtr<NSString>, std::allocator<OFRetainedPtr<NSString>>>::reserve(unsigned long)
 * address: 000cc4f0
 * size: 772
 */

/* std::vector<OFRetainedPtr<NSString>, std::allocator<OFRetainedPtr<NSString> > >::reserve(unsigned
   long) */

void __thiscall
std::vector<OFRetainedPtr<NSString>,std::allocator<OFRetainedPtr<NSString>>>::reserve
          (vector<OFRetainedPtr<NSString>,std::allocator<OFRetainedPtr<NSString>>> *this,
          ulong param_1)

{
  ID *self;
  undefined4 local_d8;
  uint local_d4;
  vector<OFRetainedPtr<NSString>,std::allocator<OFRetainedPtr<NSString>>> *local_d0;
  ID *local_cc;
  ID *local_c8;
  ID *local_c4;
  ID *local_c0;
  int local_bc;
  ID *local_b8;
  SEL local_b4;
  SEL local_b0;
  ID *local_ac;
  SEL local_a8;
  ID *local_a4;
  ID *local_a0;
  ID *local_9c;
  ID *local_98;
  undefined1 auStack_94 [4];
  int local_90;
  undefined4 local_8c;
  undefined *local_7c;
  undefined *local_78;
  undefined1 *local_74;
  undefined4 local_70;
  undefined1 *local_6c;

  local_74 = &stack0xfffffff8;
  local_6c = (undefined1 *)&local_d8;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table1;
  local_70 = 0xcc704;
  local_d4 = param_1;
  local_d0 = this;
  __Unwind_SjLj_Register(auStack_94);
  if (local_d4 < 0x40000000) {
    local_c8 = *(ID **)local_d0;
    local_b8 = local_c8;
    if ((uint)(*(int *)(local_d0 + 8) - (int)local_c8 >> 2) < local_d4) {
      local_c4 = *(ID **)(local_d0 + 4);
      local_bc = local_d4 << 2;
      local_90 = 0xffffffff;
      self = operator_new(local_d4 << 2);
      local_c0 = self;
      local_9c = self;
      if (local_c8 != local_c4) {
        local_b4 = "retain";
        local_a0 = self;
        do {
          if (local_a0 != (ID *)0x0) {
            self = (ID *)*local_b8;
            *local_a0 = (ID)self;
          }
          local_cc = local_a0;
          if (local_a0 != (ID *)0x0 && self != (ID *)0x0) {
            local_90 = 1;
            self = (ID *)_objc_msgSend((ID)self,local_b4);
          }
          local_b8 = local_b8 + 1;
          local_a0 = local_a0 + 1;
        } while (local_c4 != local_b8);
      }
      local_ac = *(ID **)(local_d0 + 4);
      if (*(ID **)local_d0 != local_ac) {
        local_a8 = "release";
        local_a4 = *(ID **)local_d0;
        do {
          if (*local_a4 != 0) {
            local_90 = 4;
            _objc_msgSend(*local_a4,local_a8);
          }
          local_a4 = local_a4 + 1;
        } while (local_ac != local_a4);
        local_ac = *(ID **)local_d0;
      }
      if (local_ac != (ID *)0x0) {
        operator_delete(local_ac);
      }
      *(ID **)local_d0 = local_9c;
      *(uint *)(local_d0 + 4) = (int)local_9c + ((int)local_c4 - (int)local_c8 & 0xfffffffcU);
      *(int *)(local_d0 + 8) = (int)local_9c + local_bc;
    }
    __Unwind_SjLj_Unregister(auStack_94);
    return;
  }
  local_90 = -1;
  std::__throw_length_error("vector::reserve");
  local_d8 = local_8c;
  if (local_90 == 1) {
    local_90 = 0;
    ___cxa_end_catch();
    ___cxa_begin_catch(local_d8);
    if (local_c0 != (ID *)0x0) {
      operator_delete(local_9c);
    }
    local_90 = 3;
                    /* WARNING: Subroutine does not return */
    ___cxa_rethrow();
  }
  if (local_90 == 2) {
    local_90 = 0;
    ___cxa_end_catch();
    local_90 = 0xffffffff;
                    /* WARNING: Subroutine does not return */
    __Unwind_SjLj_Resume(local_d8);
  }
  if (local_90 != 3) {
    ___cxa_begin_catch(local_8c);
    if (local_9c != local_cc) {
      local_98 = local_9c;
      local_b0 = "release";
      do {
        if (*local_98 != 0) {
          local_90 = 2;
          _objc_msgSend(*local_98,local_b0);
        }
        local_98 = local_98 + 1;
      } while (local_cc != local_98);
    }
    local_90 = 2;
                    /* WARNING: Subroutine does not return */
    ___cxa_rethrow();
  }
  local_90 = 0xffffffff;
                    /* WARNING: Subroutine does not return */
  __Unwind_SjLj_Resume(local_8c);
}
