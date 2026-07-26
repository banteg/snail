/*
 * mangled: _ZNSt6vectorI18OFSdbmHashedStringSaIS0_EE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPS0_S2_EERKS0_
 * demangled: std::vector<OFSdbmHashedString, std::allocator<OFSdbmHashedString>>::_M_insert_aux(__gnu_cxx::__normal_iterator<OFSdbmHashedString*, std::vector<OFSdbmHashedString, std::allocator<OFSdbmHashedString>>>, OFSdbmHashedString const&)
 * address: 000d4f80
 * size: 368
 */

/* std::vector<OFSdbmHashedString, std::allocator<OFSdbmHashedString>
   >::_M_insert_aux(__gnu_cxx::__normal_iterator<OFSdbmHashedString*,
   std::vector<OFSdbmHashedString, std::allocator<OFSdbmHashedString> > >, OFSdbmHashedString
   const&) */

void __thiscall
std::vector<OFSdbmHashedString,std::allocator<OFSdbmHashedString>>::_M_insert_aux
          (vector<OFSdbmHashedString,std::allocator<OFSdbmHashedString>> *this,undefined4 *param_2,
          undefined4 *param_3)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  ulong uVar10;
  int iVar11;
  code *UNRECOVERED_JUMPTABLE;

  puVar6 = *(undefined4 **)(this + 4);
  if (puVar6 != *(undefined4 **)(this + 8)) {
    iVar7 = 0;
    if (puVar6 != (undefined4 *)0x0) {
      *puVar6 = puVar6[-1];
      iVar7 = *(int *)(this + 4);
    }
    *(int *)(this + 4) = iVar7 + 4;
    uVar5 = *param_3;
    iVar4 = (iVar7 + -4) - (int)param_2 >> 2;
    if (0 < iVar4) {
      iVar11 = 0;
      do {
        iVar8 = iVar7 + iVar11;
        iVar4 = iVar4 + -1;
        iVar11 = iVar11 + -4;
        *(undefined4 *)(iVar8 + -4) = *(undefined4 *)(iVar8 + -8);
      } while (iVar4 != 0);
    }
    *param_2 = uVar5;
    return;
  }
  uVar1 = (int)puVar6 - *(int *)this >> 2;
  if (uVar1 == 0x3fffffff) {
LAB_000d50e4:
    UNRECOVERED_JUMPTABLE = (code *)0xd50ec;
    std::__throw_length_error("vector::_M_insert_aux");
                    /* WARNING: Could not recover jumptable at 0x000d50f0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE)();
    return;
  }
  if (uVar1 == 0) {
    uVar2 = 1;
  }
  else {
    uVar2 = uVar1 * 2;
    if (uVar2 < uVar1) {
      uVar10 = 0xfffffffc;
      goto LAB_000d5034;
    }
    if (0x3fffffff < uVar2) {
      std::__throw_bad_alloc();
      goto LAB_000d50e4;
    }
  }
  uVar10 = uVar2 << 2;
LAB_000d5034:
  puVar3 = operator_new(uVar10);
  puVar9 = puVar3;
  for (puVar6 = *(undefined4 **)this; param_2 != puVar6; puVar6 = puVar6 + 1) {
    if (puVar9 != (undefined4 *)0x0) {
      *puVar9 = *puVar6;
    }
    puVar9 = puVar9 + 1;
  }
  if (puVar9 != (undefined4 *)0x0) {
    *puVar9 = *param_3;
  }
  puVar6 = *(undefined4 **)(this + 4);
  for (; puVar9 = puVar9 + 1, param_2 != puVar6; param_2 = param_2 + 1) {
    if (puVar9 != (undefined4 *)0x0) {
      *puVar9 = *param_2;
    }
  }
  if (*(void **)this != (void *)0x0) {
    operator_delete(*(void **)this);
  }
  *(undefined4 **)this = puVar3;
  *(undefined4 **)(this + 4) = puVar9;
  *(ulong *)(this + 8) = (int)puVar3 + uVar10;
  return;
}
