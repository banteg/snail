/*
 * mangled: _ZN13OFISerializer9serializeI21OFHighScoreBatchEntryEEvPKcS3_RSt6vectorI9OFPointerIT_ESaIS7_EE
 * demangled: void OFISerializer::serialize<OFHighScoreBatchEntry>(char const*, char const*, std::vector<OFPointer<OFHighScoreBatchEntry>, std::allocator<OFPointer<OFHighScoreBatchEntry>>>&)
 * address: 0008fab4
 * size: 672
 */

/* void OFISerializer::serialize<OFHighScoreBatchEntry>(char const*, char const*,
   std::vector<OFPointer<OFHighScoreBatchEntry>, std::allocator<OFPointer<OFHighScoreBatchEntry> >
   >&) */

void __thiscall
OFISerializer::serialize<OFHighScoreBatchEntry>
          (OFISerializer *this,char *param_1,char *param_2,vector *param_3)

{
  int iVar1;
  OFISerializer *pOVar2;
  OFISerializer *pOVar3;
  undefined1 auStack_d4 [4];
  vector *local_d0;
  char *local_cc;
  char *local_c8;
  OFISerializer *local_c4;
  OFISerializer *local_c0;
  OFISerializer *local_bc;
  OFISerializer *local_b8;
  OFISerializer *local_b4;
  OFISerializer *local_b0;
  OFISerializer *local_ac;
  OFISerializer *local_a8;
  undefined1 auStack_a4 [4];
  undefined4 local_a0;
  undefined *local_8c;
  undefined *local_88;
  undefined1 *local_84;
  undefined1 *local_80;
  undefined1 *local_7c;
  Scope aSStack_70 [8];
  OFSmartObject *local_68;
  OFISerializer *local_64 [17];

  local_84 = &stack0xfffffff8;
  local_7c = auStack_d4;
  local_8c = PTR_001b615c;
  local_88 = &::GCC_except_table5;
  local_80 = &LAB_0008fd54;
  local_d0 = param_3;
  local_cc = param_2;
  local_c8 = param_1;
  local_c4 = this;
  __Unwind_SjLj_Register(auStack_a4);
  local_a0 = 0xffffffff;
  Scope::Scope(aSStack_70,local_c4,local_c8,true);
  local_64[0] = (OFISerializer *)(*(int *)(local_d0 + 4) - *(int *)local_d0 >> 2);
  local_a0 = 4;
  (**(code **)(*(int *)local_c4 + 0x3c))(local_c4,local_64);
  pOVar2 = local_c4;
  iVar1 = (**(code **)(*(int *)local_c4 + 0x10))(local_c4);
  if (iVar1 == 0) goto LAB_0008fc74;
  local_b8 = *(OFISerializer **)local_d0;
  local_bc = *(OFISerializer **)(local_d0 + 4);
  pOVar2 = local_b8;
  if (local_b8 != local_bc) {
    do {
      local_a8 = pOVar2;
      if (*(OFSmartObject **)local_a8 != (OFSmartObject *)0x0) {
        local_a0 = 2;
        OFSmartObject::Release(*(OFSmartObject **)local_a8);
      }
      local_a8 = local_a8 + 4;
      pOVar2 = local_a8;
    } while (local_bc != local_a8);
  }
  *(OFISerializer **)(local_d0 + 4) = local_b8;
  local_68 = (OFSmartObject *)0x0;
  local_b4 = local_b8;
  pOVar3 = (OFISerializer *)((int)local_b8 - *(int *)local_d0 >> 2);
  pOVar2 = local_64[0];
  if (pOVar3 <= local_64[0]) goto LAB_0008fd34;
  pOVar2 = (OFISerializer *)(*(int *)local_d0 + (int)local_64[0] * 4);
  local_b0 = pOVar2;
  if (local_b8 != pOVar2) {
    do {
      local_ac = pOVar2;
      if (*(OFSmartObject **)pOVar2 != (OFSmartObject *)0x0) {
        local_a0 = 1;
        OFSmartObject::Release(*(OFSmartObject **)pOVar2);
      }
      pOVar2 = local_ac + 4;
      local_ac = pOVar2;
    } while (local_b4 != pOVar2);
  }
  *(OFISerializer **)(local_d0 + 4) = local_b0;
  pOVar2 = local_b0;
  while( true ) {
    if (local_68 != (OFSmartObject *)0x0) {
      local_a0 = 4;
      OFSmartObject::Release(local_68);
    }
LAB_0008fc74:
    if (local_64[0] == (OFISerializer *)0x0) break;
    iVar1 = *(int *)local_d0;
    if ((uint)(*(int *)(local_d0 + 4) - iVar1) >> 2 != 0) {
      local_c0 = (OFISerializer *)0x0;
      do {
        local_a0 = 4;
        pOVar2 = (OFISerializer *)(iVar1 + (int)local_c0 * 4);
        serialize<OFHighScoreBatchEntry>(local_c4,local_cc,pOVar2);
        local_c0 = local_c0 + 1;
        if (local_64[0] <= local_c0) goto LAB_0008fcf8;
        iVar1 = *(int *)local_d0;
      } while (local_c0 < (OFISerializer *)(*(int *)(local_d0 + 4) - iVar1 >> 2));
    }
    pOVar3 = (OFISerializer *)0x4;
    local_a0 = 4;
    std::__throw_out_of_range("vector::_M_range_check");
LAB_0008fd34:
    local_a0 = 3;
    pOVar2 = pOVar2 + -(int)pOVar3;
    std::vector<OFPointer<OFHighScoreBatchEntry>,std::allocator<OFPointer<OFHighScoreBatchEntry>>>::
    _M_fill_insert((vector<OFPointer<OFHighScoreBatchEntry>,std::allocator<OFPointer<OFHighScoreBatchEntry>>>
                    *)local_d0,local_b8,pOVar2,&local_68);
  }
LAB_0008fcf8:
  local_a0 = 0xffffffff;
  Scope::~Scope(aSStack_70);
  __Unwind_SjLj_Unregister(auStack_a4);
  return;
}
