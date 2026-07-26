/*
 * mangled: _ZNSt6vectorIN17OFResourceDataMap16FieldDescriptionESaIS1_EEaSERKS3_
 * demangled: std::vector<OFResourceDataMap::FieldDescription, std::allocator<OFResourceDataMap::FieldDescription>>::operator=(std::vector<OFResourceDataMap::FieldDescription, std::allocator<OFResourceDataMap::FieldDescription>> const&)
 * address: 00079f00
 * size: 1928
 */

/* std::vector<OFResourceDataMap::FieldDescription,
   std::allocator<OFResourceDataMap::FieldDescription>
   >::TEMPNAMEPLACEHOLDERVALUE(std::vector<OFResourceDataMap::FieldDescription,
   std::allocator<OFResourceDataMap::FieldDescription> > const&) */

vector<OFResourceDataMap::FieldDescription,std::allocator<OFResourceDataMap::FieldDescription>> *
__thiscall
std::vector<OFResourceDataMap::FieldDescription,std::allocator<OFResourceDataMap::FieldDescription>>
::operator=(vector<OFResourceDataMap::FieldDescription,std::allocator<OFResourceDataMap::FieldDescription>>
            *this,vector *param_1)

{
  ID IVar1;
  ID *pIVar2;
  int iVar3;
  undefined4 local_140;
  vector<OFResourceDataMap::FieldDescription,std::allocator<OFResourceDataMap::FieldDescription>>
  *local_13c;
  vector<OFResourceDataMap::FieldDescription,std::allocator<OFResourceDataMap::FieldDescription>>
  *local_138;
  uint local_134;
  ID *local_130;
  ID *local_12c;
  int local_128;
  SEL local_124;
  SEL local_120;
  ID *local_11c;
  SEL local_118;
  ID *local_114;
  uint local_110;
  char *local_10c;
  SEL local_108;
  SEL local_104;
  ID *local_100;
  int local_fc;
  char *local_f8;
  SEL local_f4;
  ID *local_f0;
  SEL local_ec;
  ID *local_e8;
  SEL local_e4;
  ID *local_e0;
  ID *local_dc;
  ID *local_d8;
  ID *local_d4;
  ID *local_d0;
  ID *local_cc;
  ID *local_c8;
  ID *local_c4;
  int local_c0;
  ID *local_bc;
  ID *local_b8;
  ID *local_b4;
  ID *local_b0;
  ID *local_ac;
  ID *local_a8;
  ID *local_a4;
  ID *local_a0;
  uint local_9c;
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
  local_6c = (undefined1 *)&local_140;
  local_7c = PTR_001b615c;
  local_78 = &::GCC_except_table0;
  local_70 = 0x7a528;
  local_13c = (vector<OFResourceDataMap::FieldDescription,std::allocator<OFResourceDataMap::FieldDescription>>
               *)param_1;
  local_138 = this;
  __Unwind_SjLj_Register(auStack_94);
  if (local_13c == local_138) goto LAB_0007a1e8;
  local_d0 = *(ID **)(local_13c + 4);
  local_100 = *(ID **)local_13c;
  iVar3 = (int)local_d0 - (int)local_100 >> 2;
  local_134 = iVar3 * -0x33333333;
  pIVar2 = *(ID **)local_138;
  if ((uint)((*(int *)(local_138 + 8) - (int)pIVar2 >> 2) * -0x33333333) < local_134) {
    if (0xccccccc < local_134) {
      local_90 = -1;
      std::__throw_bad_alloc();
      local_140 = local_8c;
      if (local_90 != 1) {
        if (local_90 == 2) {
          ___cxa_begin_catch(local_8c);
          if (local_130 != local_ac) {
            local_b0 = local_130;
            local_120 = "release";
            do {
              if (*local_b0 != 0) {
                local_90 = 4;
                _objc_msgSend(*local_b0,local_120);
              }
              local_b0 = local_b0 + 5;
            } while (local_b0 != local_ac);
          }
          local_90 = 4;
                    /* WARNING: Subroutine does not return */
          ___cxa_rethrow();
        }
        if (local_90 == 3) {
          local_90 = 0;
          ___cxa_end_catch();
          ___cxa_begin_catch(local_140);
          if (local_12c != (ID *)0x0) {
            operator_delete(local_130);
          }
          local_90 = 5;
                    /* WARNING: Subroutine does not return */
          ___cxa_rethrow();
        }
        if (local_90 != 4) {
          if ((local_90 != 5) && (local_90 != 6)) {
            ___cxa_begin_catch(local_8c);
            if (local_98 != local_e8) {
              local_e4 = "release";
              do {
                if (*local_bc != 0) {
                  local_90 = 2;
                  _objc_msgSend(*local_bc,local_e4);
                }
                local_bc = local_bc + 5;
              } while (local_bc != local_e8);
            }
            local_90 = 2;
                    /* WARNING: Subroutine does not return */
            ___cxa_rethrow();
          }
          goto LAB_0007a5d8;
        }
      }
      local_90 = 0;
      ___cxa_end_catch();
LAB_0007a5d8:
      local_90 = 0xffffffff;
                    /* WARNING: Subroutine does not return */
      __Unwind_SjLj_Resume(local_140);
    }
    local_128 = iVar3 << 2;
    local_90 = 0xffffffff;
    pIVar2 = operator_new(iVar3 << 2);
    local_dc = local_d0;
    local_a4 = local_100;
    local_130 = pIVar2;
    local_12c = pIVar2;
    if (local_d0 != local_100) {
      local_a8 = local_100;
      local_124 = "retain";
      while( true ) {
        local_e0 = local_a8;
        local_ac = pIVar2;
        if (pIVar2 != (ID *)0x0) {
          IVar1 = *local_a8;
          *pIVar2 = IVar1;
          if (IVar1 != 0) {
            local_90 = 3;
            _objc_msgSend(IVar1,local_124);
          }
          local_ac[1] = local_a8[1];
          local_ac[2] = local_a8[2];
          local_ac[3] = local_a8[3];
          *(char *)(local_ac + 4) = (char)local_a8[4];
        }
        local_a8 = local_e0 + 5;
        if (local_a8 == local_dc) break;
        pIVar2 = (ID *)(((int)local_130 - (int)local_a4) + (int)local_a8);
      }
    }
    local_11c = *(ID **)(local_138 + 4);
    if (*(ID **)local_138 != local_11c) {
      local_118 = "release";
      local_cc = *(ID **)local_138;
      do {
        if (*local_cc != 0) {
          local_90 = 7;
          _objc_msgSend(*local_cc,local_118);
        }
        local_cc = local_cc + 5;
      } while (local_11c != local_cc);
      local_11c = *(ID **)local_138;
    }
    if (local_11c != (ID *)0x0) {
      operator_delete(local_11c);
    }
    *(ID **)local_138 = local_130;
    *(int *)(local_138 + 8) = (int)local_130 + local_128;
    iVar3 = local_128;
LAB_0007a378:
    *(int *)(local_138 + 4) = *(int *)local_138 + iVar3;
  }
  else {
    local_98 = *(ID **)(local_138 + 4);
    iVar3 = (int)local_98 - (int)pIVar2 >> 2;
    if ((uint)(iVar3 * -0x33333333) < local_134) {
      local_f0 = local_100 + iVar3;
      local_fc = (iVar3 * 4 >> 2) * -0x33333333;
      if (0 < local_fc) {
        local_f4 = "release";
        local_f8 = "retain";
        while( true ) {
          IVar1 = *pIVar2;
          local_b8 = pIVar2;
          if (IVar1 != *local_100) {
            if (IVar1 != 0) {
              local_90 = 0xffffffff;
              _objc_msgSend(IVar1,local_f4);
            }
            IVar1 = *local_100;
            *local_b8 = IVar1;
            if (IVar1 != 0) {
              local_90 = 0xffffffff;
              _objc_msgSend(IVar1,local_f8);
            }
          }
          local_b8[1] = local_100[1];
          local_b8[2] = local_100[2];
          local_b8[3] = local_100[3];
          *(char *)(local_b8 + 4) = (char)local_100[4];
          pIVar2 = local_b8 + 5;
          local_fc = local_fc + -1;
          if (local_fc == 0) break;
          local_100 = local_100 + 5;
        }
        local_98 = *(ID **)(local_138 + 4);
        local_f0 = (ID *)(((int)local_98 - *(int *)local_138 & 0xfffffffcU) + *(int *)local_13c);
        local_d0 = *(ID **)(local_13c + 4);
        local_fc = 0;
        local_b8 = pIVar2;
      }
      if (local_f0 == local_d0) {
        iVar3 = local_134 * 0x14;
        goto LAB_0007a378;
      }
      local_ec = "retain";
      local_bc = local_98;
      local_c0 = 0;
      local_b4 = local_98;
      local_a0 = local_f0;
      do {
        local_e8 = local_b4;
        if (local_b4 != (ID *)0x0) {
          IVar1 = *(ID *)(local_c0 + (int)local_f0);
          *(ID *)(local_c0 + (int)local_98) = IVar1;
          if (IVar1 != 0) {
            local_90 = 1;
            _objc_msgSend(IVar1,local_ec);
          }
          local_b4[1] = local_a0[1];
          local_b4[2] = local_a0[2];
          local_b4[3] = local_a0[3];
          *(char *)(local_b4 + 4) = (char)local_a0[4];
        }
        local_a0 = local_a0 + 5;
        local_c0 = local_c0 + 0x14;
        local_b4 = local_b4 + 5;
      } while (local_a0 != local_d0);
    }
    else {
      local_114 = pIVar2;
      local_110 = local_134;
      if (0 < (int)local_134) {
        local_108 = "release";
        local_10c = "retain";
        local_c8 = local_100;
        local_c4 = pIVar2;
        local_9c = local_134;
        do {
          IVar1 = *local_c4;
          if (IVar1 != *local_c8) {
            if (IVar1 != 0) {
              local_90 = 0xffffffff;
              _objc_msgSend(IVar1,local_108);
            }
            IVar1 = *local_c8;
            *local_c4 = IVar1;
            if (IVar1 != 0) {
              local_90 = 0xffffffff;
              _objc_msgSend(IVar1,local_10c);
            }
          }
          local_c4[1] = local_c8[1];
          local_c4[2] = local_c8[2];
          local_c4[3] = local_c8[3];
          pIVar2 = local_c8 + 4;
          local_c8 = local_c8 + 5;
          *(char *)(local_c4 + 4) = (char)*pIVar2;
          local_c4 = local_c4 + 5;
          local_9c = local_9c - 1;
        } while (local_9c != 0);
        local_114 = local_114 + local_110 * 5;
        local_98 = *(ID **)(local_138 + 4);
        local_9c = 0;
      }
      local_d4 = local_98;
      if (local_98 != local_114) {
        local_104 = "release";
        local_d8 = local_114;
        do {
          if (*local_d8 != 0) {
            local_90 = 6;
            _objc_msgSend(*local_d8,local_104);
          }
          local_d8 = local_d8 + 5;
        } while (local_d8 != local_d4);
        iVar3 = local_134 * 0x14;
        goto LAB_0007a378;
      }
    }
    *(uint *)(local_138 + 4) = *(int *)local_138 + local_134 * 0x14;
  }
LAB_0007a1e8:
  __Unwind_SjLj_Unregister(auStack_94);
  return local_138;
}
