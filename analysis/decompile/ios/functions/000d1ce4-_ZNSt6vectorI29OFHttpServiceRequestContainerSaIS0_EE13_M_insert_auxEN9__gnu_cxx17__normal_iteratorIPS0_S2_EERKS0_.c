/*
 * mangled: _ZNSt6vectorI29OFHttpServiceRequestContainerSaIS0_EE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPS0_S2_EERKS0_
 * demangled: std::vector<OFHttpServiceRequestContainer, std::allocator<OFHttpServiceRequestContainer>>::_M_insert_aux(__gnu_cxx::__normal_iterator<OFHttpServiceRequestContainer*, std::vector<OFHttpServiceRequestContainer, std::allocator<OFHttpServiceRequestContainer>>>, OFHttpServiceRequestContainer const&)
 * address: 000d1ce4
 * size: 4148
 */

/* std::vector<OFHttpServiceRequestContainer, std::allocator<OFHttpServiceRequestContainer>
   >::_M_insert_aux(__gnu_cxx::__normal_iterator<OFHttpServiceRequestContainer*,
   std::vector<OFHttpServiceRequestContainer, std::allocator<OFHttpServiceRequestContainer> > >,
   OFHttpServiceRequestContainer const&) */

void __thiscall
std::vector<OFHttpServiceRequestContainer,std::allocator<OFHttpServiceRequestContainer>>::
_M_insert_aux(vector<OFHttpServiceRequestContainer,std::allocator<OFHttpServiceRequestContainer>>
              *this,OFHttpServiceRequestContainer *param_2,OFHttpServiceRequestContainer *param_3)

{
  OFHttpServiceRequestContainer *pOVar1;
  ID IVar2;
  OFSmartObject *pOVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  undefined4 local_124;
  OFHttpServiceRequestContainer *local_120;
  OFHttpServiceRequestContainer *local_11c;
  vector<OFHttpServiceRequestContainer,std::allocator<OFHttpServiceRequestContainer>> *local_118;
  OFHttpServiceRequestContainer *local_114;
  OFHttpServiceRequestContainer *local_110;
  undefined4 local_10c;
  int local_108;
  char *local_104;
  SEL local_100;
  OFHttpServiceRequestContainer *local_fc;
  OFHttpServiceRequestContainer *local_f8;
  OFHttpServiceRequestContainer *local_f4;
  SEL local_f0;
  OFHttpServiceRequestContainer *local_ec;
  OFHttpServiceRequestContainer *local_e8;
  OFHttpServiceRequestContainer *local_e4;
  ulong local_e0;
  int local_dc;
  OFHttpServiceRequestContainer *local_d8;
  OFHttpServiceRequestContainer *local_d4;
  OFHttpServiceRequestContainer *local_d0;
  OFHttpServiceRequestContainer *local_cc;
  OFHttpServiceRequestContainer *local_c8;
  OFHttpServiceRequestContainer *local_c4;
  OFHttpServiceRequestContainer *local_c0;
  OFHttpServiceRequestContainer *local_bc;
  undefined1 auStack_b8 [4];
  int local_b4;
  undefined4 local_b0;
  undefined *local_a0;
  undefined *local_9c;
  undefined1 *local_98;
  undefined4 local_94;
  undefined1 *local_90;
  undefined **local_84;
  int local_80;
  ID local_7c;
  ID local_78;
  ID local_74;
  ID local_70;
  ID local_6c;
  ID local_68;
  OFSmartObject *local_64;

  local_98 = &stack0xfffffff8;
  local_90 = (undefined1 *)&local_124;
  local_a0 = PTR_001b615c;
  local_9c = &GCC_except_table8;
  local_94 = 0xd27f4;
  local_120 = param_3;
  local_11c = param_2;
  local_118 = this;
  __Unwind_SjLj_Register(auStack_b8);
  local_e4 = local_11c;
  pOVar1 = *(OFHttpServiceRequestContainer **)(local_118 + 4);
  if (pOVar1 != *(OFHttpServiceRequestContainer **)(local_118 + 8)) {
    if (pOVar1 != (OFHttpServiceRequestContainer *)0x0) {
      local_b4 = 0x1f;
      OFHttpServiceRequestContainer::OFHttpServiceRequestContainer(pOVar1,pOVar1 + -0x24);
    }
    *(int *)(local_118 + 4) = *(int *)(local_118 + 4) + 0x24;
    local_80 = *(int *)(local_120 + 4);
    local_7c = *(ID *)(local_120 + 8);
    local_84 = &PTR_GetRTTI_001b7590;
    if (local_7c != 0) {
      local_b4 = 0x1e;
      _objc_msgSend(local_7c,"retain");
    }
    local_78 = *(ID *)(local_120 + 0xc);
    if (local_78 != 0) {
      local_b4 = 0x1d;
      _objc_msgSend(local_78,"retain");
    }
    local_74 = *(ID *)(local_120 + 0x10);
    if (local_74 != 0) {
      local_b4 = 0x1c;
      _objc_msgSend(local_74,"retain");
    }
    local_70 = *(ID *)(local_120 + 0x14);
    if (local_70 != 0) {
      local_b4 = 0x1b;
      _objc_msgSend(local_70,"retain");
    }
    local_6c = *(ID *)(local_120 + 0x18);
    if (local_6c != 0) {
      local_b4 = 0x1a;
      _objc_msgSend(local_6c,"retain");
    }
    local_68 = *(ID *)(local_120 + 0x1c);
    if (local_68 != 0) {
      local_b4 = 0x19;
      _objc_msgSend(local_68,"retain");
    }
    local_64 = *(OFSmartObject **)(local_120 + 0x20);
    if (local_64 != (OFSmartObject *)0x0) {
      *(int *)(local_64 + 4) = *(int *)(local_64 + 4) + 1;
    }
    local_108 = ((*(int *)(local_118 + 4) + -0x48) - (int)local_e4 >> 2) * 0x38e38e39;
    if (0 < local_108) {
      local_100 = "release";
      local_104 = "retain";
      local_dc = *(int *)(local_118 + 4);
      do {
        IVar2 = *(ID *)(local_dc + -0x40);
        *(undefined4 *)(local_dc + -0x44) = *(undefined4 *)(local_dc + -0x68);
        if (IVar2 != *(ID *)(local_dc + -100)) {
          if (IVar2 != 0) {
            local_b4 = 0x23;
            _objc_msgSend(IVar2,local_100);
          }
          IVar2 = *(ID *)(local_dc + -100);
          *(ID *)(local_dc + -0x40) = IVar2;
          if (IVar2 != 0) {
            local_b4 = 0x23;
            _objc_msgSend(IVar2,local_104);
          }
        }
        IVar2 = *(ID *)(local_dc + -0x3c);
        if (IVar2 != *(ID *)(local_dc + -0x60)) {
          if (IVar2 != 0) {
            local_b4 = 0x23;
            _objc_msgSend(IVar2,local_100);
          }
          IVar2 = *(ID *)(local_dc + -0x60);
          *(ID *)(local_dc + -0x3c) = IVar2;
          if (IVar2 != 0) {
            local_b4 = 0x23;
            _objc_msgSend(IVar2,local_104);
          }
        }
        IVar2 = *(ID *)(local_dc + -0x38);
        if (IVar2 != *(ID *)(local_dc + -0x5c)) {
          if (IVar2 != 0) {
            local_b4 = 0x23;
            _objc_msgSend(IVar2,local_100);
          }
          IVar2 = *(ID *)(local_dc + -0x5c);
          *(ID *)(local_dc + -0x38) = IVar2;
          if (IVar2 != 0) {
            local_b4 = 0x23;
            _objc_msgSend(IVar2,local_104);
          }
        }
        IVar2 = *(ID *)(local_dc + -0x34);
        if (IVar2 != *(ID *)(local_dc + -0x58)) {
          if (IVar2 != 0) {
            local_b4 = 0x23;
            _objc_msgSend(IVar2,local_100);
          }
          IVar2 = *(ID *)(local_dc + -0x58);
          *(ID *)(local_dc + -0x34) = IVar2;
          if (IVar2 != 0) {
            local_b4 = 0x23;
            _objc_msgSend(IVar2,local_104);
          }
        }
        IVar2 = *(ID *)(local_dc + -0x30);
        if (IVar2 != *(ID *)(local_dc + -0x54)) {
          if (IVar2 != 0) {
            local_b4 = 0x23;
            _objc_msgSend(IVar2,local_100);
          }
          IVar2 = *(ID *)(local_dc + -0x54);
          *(ID *)(local_dc + -0x30) = IVar2;
          if (IVar2 != 0) {
            local_b4 = 0x23;
            _objc_msgSend(IVar2,local_104);
          }
        }
        IVar2 = *(ID *)(local_dc + -0x2c);
        if (IVar2 != *(ID *)(local_dc + -0x50)) {
          if (IVar2 != 0) {
            local_b4 = 0x23;
            _objc_msgSend(IVar2,local_100);
          }
          IVar2 = *(ID *)(local_dc + -0x50);
          *(ID *)(local_dc + -0x2c) = IVar2;
          if (IVar2 != 0) {
            local_b4 = 0x23;
            _objc_msgSend(IVar2,local_104);
          }
        }
        pOVar3 = *(OFSmartObject **)(local_dc + -0x28);
        if (pOVar3 != *(OFSmartObject **)(local_dc + -0x4c)) {
          if (pOVar3 != (OFSmartObject *)0x0) {
            local_b4 = 0x23;
            OFSmartObject::Release(pOVar3);
          }
          iVar5 = *(int *)(local_dc + -0x4c);
          *(int *)(local_dc + -0x28) = iVar5;
          if (iVar5 != 0) {
            *(int *)(iVar5 + 4) = *(int *)(iVar5 + 4) + 1;
          }
        }
        local_dc = local_dc + -0x24;
        local_108 = local_108 + -1;
      } while (local_108 != 0);
    }
    IVar2 = *(ID *)(local_e4 + 8);
    *(int *)(local_e4 + 4) = local_80;
    if (IVar2 != local_7c) {
      if (IVar2 != 0) {
        local_b4 = 0x23;
        _objc_msgSend(IVar2,"release");
      }
      *(ID *)(local_e4 + 8) = local_7c;
      if (local_7c != 0) {
        local_b4 = 0x23;
        _objc_msgSend(local_7c,"retain");
      }
    }
    IVar2 = *(ID *)(local_e4 + 0xc);
    if (IVar2 != local_78) {
      if (IVar2 != 0) {
        local_b4 = 0x23;
        _objc_msgSend(IVar2,"release");
      }
      *(ID *)(local_e4 + 0xc) = local_78;
      if (local_78 != 0) {
        local_b4 = 0x23;
        _objc_msgSend(local_78,"retain");
      }
    }
    IVar2 = *(ID *)(local_e4 + 0x10);
    if (IVar2 != local_74) {
      if (IVar2 != 0) {
        local_b4 = 0x23;
        _objc_msgSend(IVar2,"release");
      }
      *(ID *)(local_e4 + 0x10) = local_74;
      if (local_74 != 0) {
        local_b4 = 0x23;
        _objc_msgSend(local_74,"retain");
      }
    }
    IVar2 = *(ID *)(local_e4 + 0x14);
    if (IVar2 != local_70) {
      if (IVar2 != 0) {
        local_b4 = 0x23;
        _objc_msgSend(IVar2,"release");
      }
      *(ID *)(local_e4 + 0x14) = local_70;
      if (local_70 != 0) {
        local_b4 = 0x23;
        _objc_msgSend(local_70,"retain");
      }
    }
    IVar2 = *(ID *)(local_e4 + 0x18);
    if (IVar2 != local_6c) {
      if (IVar2 != 0) {
        local_b4 = 0x23;
        _objc_msgSend(IVar2,"release");
      }
      *(ID *)(local_e4 + 0x18) = local_6c;
      if (local_6c != 0) {
        local_b4 = 0x23;
        _objc_msgSend(local_6c,"retain");
      }
    }
    IVar2 = *(ID *)(local_e4 + 0x1c);
    if (IVar2 != local_68) {
      if (IVar2 != 0) {
        local_b4 = 0x23;
        _objc_msgSend(IVar2,"release");
      }
      *(ID *)(local_e4 + 0x1c) = local_68;
      if (local_68 != 0) {
        local_b4 = 0x23;
        _objc_msgSend(local_68,"retain");
      }
    }
    pOVar3 = *(OFSmartObject **)(local_e4 + 0x20);
    if (pOVar3 != local_64) {
      if (pOVar3 != (OFSmartObject *)0x0) {
        local_b4 = 0x23;
        OFSmartObject::Release(pOVar3);
      }
      *(OFSmartObject **)(local_e4 + 0x20) = local_64;
      if (local_64 != (OFSmartObject *)0x0) {
        *(int *)(local_64 + 4) = *(int *)(local_64 + 4) + 1;
      }
    }
    local_84 = &PTR_GetRTTI_001b7590;
    if (local_64 != (OFSmartObject *)0x0) {
      local_b4 = 0xb;
      OFSmartObject::Release(local_64);
    }
    if (local_68 != 0) {
      local_b4 = 0xc;
      _objc_msgSend(local_68,"release");
    }
    if (local_6c != 0) {
      local_b4 = 0xd;
      _objc_msgSend(local_6c,"release");
    }
    if (local_70 != 0) {
      local_b4 = 0xe;
      _objc_msgSend(local_70,"release");
    }
    if (local_74 != 0) {
      local_b4 = 0xf;
      _objc_msgSend(local_74,"release");
    }
    if (local_78 != 0) {
      local_b4 = 0x10;
      _objc_msgSend(local_78,"release");
    }
    if (local_7c != 0) {
      local_b4 = 0x11;
      _objc_msgSend(local_7c,"release");
    }
    local_b4 = 0xffffffff;
    OFSmartObject::~OFSmartObject((OFSmartObject *)&local_84);
LAB_000d2468:
    __Unwind_SjLj_Unregister(auStack_b8);
    return;
  }
  iVar5 = (int)pOVar1 - *(int *)local_118 >> 2;
  uVar4 = iVar5 * 0x38e38e39;
  if (uVar4 != 0x71c71c7) {
    if (uVar4 == 0) {
      uVar6 = 1;
    }
    else {
      uVar6 = iVar5 * 0x71c71c72;
    }
    if (uVar6 < uVar4) {
      local_e0 = 0xfffffffc;
    }
    else {
      if (0x71c71c7 < uVar6) {
        local_b4 = 0xffffffff;
        std::__throw_bad_alloc();
LAB_000d2a38:
        local_10c = local_124;
        local_84 = &PTR_GetRTTI_001b7590;
        if (local_64 != (OFSmartObject *)0x0) {
          local_b4 = 0x12;
          OFSmartObject::Release(local_64);
        }
        if (local_68 != 0) {
          local_b4 = 0x13;
          _objc_msgSend(local_68,"release");
        }
        if (local_6c != 0) {
          local_b4 = 0x14;
          _objc_msgSend(local_6c,"release");
        }
        if (local_70 != 0) {
          local_b4 = 0x15;
          _objc_msgSend(local_70,"release");
        }
        if (local_74 != 0) {
          local_b4 = 0x16;
          _objc_msgSend(local_74,"release");
        }
        if (local_78 != 0) {
          local_b4 = 0x17;
          _objc_msgSend(local_78,"release");
        }
        if (local_7c != 0) {
          local_b4 = 0x18;
          _objc_msgSend(local_7c,"release");
        }
        local_b4 = 0;
        OFSmartObject::~OFSmartObject((OFSmartObject *)&local_84);
        local_b4 = 0xffffffff;
                    /* WARNING: Subroutine does not return */
        __Unwind_SjLj_Resume(local_10c);
      }
      local_e0 = uVar6 * 0x24;
    }
    local_b4 = 0xffffffff;
    local_114 = operator_new(local_e0);
    local_f8 = *(OFHttpServiceRequestContainer **)local_118;
    local_fc = local_114;
    local_cc = local_114;
    if (local_e4 != local_f8) {
      local_110 = local_114;
      local_d0 = local_114 + 0x24;
      do {
        if (local_114 != (OFHttpServiceRequestContainer *)0x0) {
          local_b4 = 9;
          OFHttpServiceRequestContainer::OFHttpServiceRequestContainer(local_114,local_f8);
        }
        pOVar1 = local_d0 + 0x24;
        local_114 = local_d0;
        local_f8 = local_f8 + 0x24;
        local_d0 = pOVar1;
      } while (local_e4 != local_f8);
    }
    local_110 = local_114;
    if (local_114 != (OFHttpServiceRequestContainer *)0x0) {
      local_b4 = 8;
      OFHttpServiceRequestContainer::OFHttpServiceRequestContainer(local_114,local_120);
    }
    local_110 = local_110 + 0x24;
    local_f4 = *(OFHttpServiceRequestContainer **)(local_118 + 4);
    local_bc = local_110;
    if (local_e4 != local_f4) {
      local_d8 = local_e4;
      local_f0 = "retain";
      pOVar1 = local_114 + 0x48;
      local_c0 = local_110;
      do {
        local_d4 = pOVar1;
        if (local_c0 != (OFHttpServiceRequestContainer *)0x0) {
          IVar2 = *(ID *)(local_d8 + 8);
          *(int *)(local_c0 + 4) = *(int *)(local_d8 + 4);
          *(ID *)(local_c0 + 8) = IVar2;
          *(undefined ***)local_c0 = &PTR_GetRTTI_001b7590;
          if (IVar2 != 0) {
            local_b4 = 6;
            _objc_msgSend(IVar2,local_f0);
          }
          IVar2 = *(ID *)(local_d8 + 0xc);
          *(ID *)(local_c0 + 0xc) = IVar2;
          if (IVar2 != 0) {
            local_b4 = 5;
            _objc_msgSend(IVar2,local_f0);
          }
          IVar2 = *(ID *)(local_d8 + 0x10);
          *(ID *)(local_c0 + 0x10) = IVar2;
          if (IVar2 != 0) {
            local_b4 = 4;
            _objc_msgSend(IVar2,local_f0);
          }
          IVar2 = *(ID *)(local_d8 + 0x14);
          *(ID *)(local_c0 + 0x14) = IVar2;
          if (IVar2 != 0) {
            local_b4 = 3;
            _objc_msgSend(IVar2,local_f0);
          }
          IVar2 = *(ID *)(local_d8 + 0x18);
          *(ID *)(local_c0 + 0x18) = IVar2;
          if (IVar2 != 0) {
            local_b4 = 2;
            _objc_msgSend(IVar2,local_f0);
          }
          IVar2 = *(ID *)(local_d8 + 0x1c);
          *(ID *)(local_c0 + 0x1c) = IVar2;
          if (IVar2 != 0) {
            local_b4 = 1;
            _objc_msgSend(IVar2,local_f0);
          }
          iVar5 = *(int *)(local_d8 + 0x20);
          *(int *)(local_c0 + 0x20) = iVar5;
          if (iVar5 != 0) {
            *(int *)(iVar5 + 4) = *(int *)(iVar5 + 4) + 1;
          }
        }
        local_c0 = local_d4;
        local_d8 = local_d8 + 0x24;
        pOVar1 = local_d4 + 0x24;
      } while (local_f4 != local_d8);
      local_e4 = *(OFHttpServiceRequestContainer **)(local_118 + 4);
      local_bc = local_d4;
      local_d4 = local_d4 + 0x24;
    }
    local_ec = *(OFHttpServiceRequestContainer **)local_118;
    if (local_e4 != local_ec) {
      do {
        local_b4 = 0x20;
        (**(code **)(*(int *)local_ec + 4))(local_ec);
        local_ec = local_ec + 0x24;
      } while (local_e4 != local_ec);
      local_e4 = *(OFHttpServiceRequestContainer **)local_118;
    }
    if (local_e4 != (OFHttpServiceRequestContainer *)0x0) {
      operator_delete(local_e4);
    }
    *(OFHttpServiceRequestContainer **)local_118 = local_cc;
    *(OFHttpServiceRequestContainer **)(local_118 + 4) = local_bc;
    *(OFHttpServiceRequestContainer **)(local_118 + 8) = local_cc + local_e0;
    goto LAB_000d2468;
  }
  local_b4 = -1;
  std::__throw_length_error("vector::_M_insert_aux");
  local_124 = local_b0;
  if (local_b4 == 1) {
LAB_000d2934:
    if (*(ID *)(local_c0 + 0x14) != 0) {
      local_b4 = 0;
      _objc_msgSend(*(ID *)(local_c0 + 0x14),"release");
    }
LAB_000d2958:
    if (*(ID *)(local_c0 + 0x10) != 0) {
      local_b4 = 0;
      _objc_msgSend(*(ID *)(local_c0 + 0x10),"release");
    }
LAB_000d297c:
    if (*(ID *)(local_c0 + 0xc) != 0) {
      local_b4 = 0;
      _objc_msgSend(*(ID *)(local_c0 + 0xc),"release");
    }
  }
  else {
    if (local_b4 == 2) goto LAB_000d2958;
    if (local_b4 == 3) goto LAB_000d297c;
    if (local_b4 != 4) {
      if (local_b4 == 5) goto LAB_000d29c4;
      if (local_b4 == 6) {
LAB_000d2cbc:
        local_b4 = 0;
        ___cxa_end_catch();
LAB_000d2cc8:
        ___cxa_begin_catch(local_124);
        local_e8 = local_110;
        if (local_cc != local_110) {
          local_c4 = local_cc;
          do {
            local_b4 = 0x21;
            (**(code **)(*(int *)local_c4 + 4))(local_c4);
            local_c4 = local_c4 + 0x24;
          } while (local_e8 != local_c4);
        }
        if (local_fc != (OFHttpServiceRequestContainer *)0x0) {
          operator_delete(local_cc);
        }
        local_b4 = 0x22;
                    /* WARNING: Subroutine does not return */
        ___cxa_rethrow();
      }
      if (local_b4 == 7) goto LAB_000d2cc8;
      if (local_b4 == 8) {
        ___cxa_begin_catch(local_b0);
        if (local_cc != local_114) {
          local_c8 = local_cc;
          do {
            local_b4 = 10;
            (**(code **)(*(int *)local_c8 + 4))(local_c8);
            local_c8 = local_c8 + 0x24;
          } while (local_c8 != local_114);
        }
        local_b4 = 10;
                    /* WARNING: Subroutine does not return */
        ___cxa_rethrow();
      }
      if (local_b4 == 9) goto LAB_000d2cbc;
      if (local_b4 == 10) {
LAB_000d2b5c:
        if (local_68 != 0) {
          local_b4 = 0;
          _objc_msgSend(local_68,"release");
        }
LAB_000d2b7c:
        if (local_6c != 0) {
          local_b4 = 0;
          _objc_msgSend(local_6c,"release");
        }
LAB_000d2b9c:
        if (local_70 != 0) {
          local_b4 = 0;
          _objc_msgSend(local_70,"release");
        }
LAB_000d2bbc:
        if (local_74 != 0) {
          local_b4 = 0;
          _objc_msgSend(local_74,"release");
        }
LAB_000d2bdc:
        if (local_78 != 0) {
          local_b4 = 0;
          _objc_msgSend(local_78,"release");
        }
LAB_000d2bfc:
        if (local_7c != 0) {
          local_b4 = 0;
          _objc_msgSend(local_7c,"release");
        }
      }
      else {
        if (local_b4 == 0xb) goto LAB_000d2b7c;
        if (local_b4 == 0xc) goto LAB_000d2b9c;
        if (local_b4 == 0xd) goto LAB_000d2bbc;
        if (local_b4 == 0xe) goto LAB_000d2bdc;
        if (local_b4 == 0xf) goto LAB_000d2bfc;
        if (local_b4 == 0x10) goto LAB_000d2c1c;
        if (local_b4 == 0x11) goto LAB_000d2b5c;
        if (local_b4 == 0x12) goto LAB_000d2b7c;
        if (local_b4 == 0x13) goto LAB_000d2b9c;
        if (local_b4 == 0x14) goto LAB_000d2bbc;
        if (local_b4 == 0x15) goto LAB_000d2bdc;
        if (local_b4 == 0x16) goto LAB_000d2bfc;
        if (local_b4 != 0x17) {
          if (local_b4 == 0x18) goto LAB_000d2b7c;
          if (local_b4 == 0x19) goto LAB_000d2b9c;
          if (local_b4 == 0x1a) goto LAB_000d2bbc;
          if (local_b4 == 0x1b) goto LAB_000d2bdc;
          if (local_b4 == 0x1c) goto LAB_000d2bfc;
          if (local_b4 != 0x1d) {
            if ((local_b4 == 0x1e) || (local_b4 == 0x1f)) goto LAB_000d2c2c;
            if ((local_b4 == 0x20) || (local_b4 == 0x21)) {
              local_b4 = 0;
              ___cxa_end_catch();
              local_b4 = 0xffffffff;
                    /* WARNING: Subroutine does not return */
              __Unwind_SjLj_Resume(local_124);
            }
            if (local_b4 == 0x22) goto LAB_000d2a38;
            if (*(ID *)(local_c0 + 0x18) != 0) {
              local_b4 = 0;
              _objc_msgSend(*(ID *)(local_c0 + 0x18),"release");
            }
            goto LAB_000d2934;
          }
        }
      }
LAB_000d2c1c:
      local_b4 = 0;
      OFSmartObject::~OFSmartObject((OFSmartObject *)&local_84);
LAB_000d2c2c:
      local_b4 = 0xffffffff;
                    /* WARNING: Subroutine does not return */
      __Unwind_SjLj_Resume(local_124);
    }
  }
  if (*(ID *)(local_c0 + 8) != 0) {
    local_b4 = 0;
    _objc_msgSend(*(ID *)(local_c0 + 8),"release");
  }
LAB_000d29c4:
  local_b4 = 0;
  OFSmartObject::~OFSmartObject((OFSmartObject *)local_c0);
  ___cxa_begin_catch(local_124);
  if (local_bc != local_c0) {
    do {
      local_b4 = 7;
      (**(code **)(*(int *)local_bc + 4))(local_bc);
      local_bc = local_bc + 0x24;
    } while (local_c0 != local_bc);
  }
  local_b4 = 7;
                    /* WARNING: Subroutine does not return */
  ___cxa_rethrow();
}
