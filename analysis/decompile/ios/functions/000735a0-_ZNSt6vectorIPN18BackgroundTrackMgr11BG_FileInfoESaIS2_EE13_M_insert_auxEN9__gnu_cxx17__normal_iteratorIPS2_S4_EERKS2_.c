/*
 * mangled: _ZNSt6vectorIPN18BackgroundTrackMgr11BG_FileInfoESaIS2_EE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPS2_S4_EERKS2_
 * demangled: std::vector<BackgroundTrackMgr::BG_FileInfo*, std::allocator<BackgroundTrackMgr::BG_FileInfo*>>::_M_insert_aux(__gnu_cxx::__normal_iterator<BackgroundTrackMgr::BG_FileInfo**, std::vector<BackgroundTrackMgr::BG_FileInfo*, std::allocator<BackgroundTrackMgr::BG_FileInfo*>>>, BackgroundTrackMgr::BG_FileInfo* const&)
 * address: 000735a0
 * size: 296
 */

/* std::vector<BackgroundTrackMgr::BG_FileInfo*, std::allocator<BackgroundTrackMgr::BG_FileInfo*>
   >::_M_insert_aux(__gnu_cxx::__normal_iterator<BackgroundTrackMgr::BG_FileInfo**,
   std::vector<BackgroundTrackMgr::BG_FileInfo*, std::allocator<BackgroundTrackMgr::BG_FileInfo*> >
   >, BackgroundTrackMgr::BG_FileInfo* const&) */

void __thiscall
std::vector<BackgroundTrackMgr::BG_FileInfo*,std::allocator<BackgroundTrackMgr::BG_FileInfo*>>::
_M_insert_aux(vector<BackgroundTrackMgr::BG_FileInfo*,std::allocator<BackgroundTrackMgr::BG_FileInfo*>>
              *this,undefined4 *param_2,undefined4 *param_3)

{
  void *pvVar1;
  int *piVar2;
  void *pvVar3;
  undefined4 *puVar4;
  uint uVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  uint uVar9;
  undefined4 *puVar10;
  undefined4 uVar11;
  undefined4 unaff_r5;
  int unaff_r8;
  undefined4 unaff_r11;
  ulong uVar12;
  undefined1 *puVar13;
  undefined1 uVar14;
  int *piVar15;
  undefined8 uVar16;

  puVar13 = &stack0xffffffe0;
  puVar7 = *(undefined4 **)(this + 4);
  puVar4 = *(undefined4 **)(this + 8);
  if (puVar7 != puVar4) {
    iVar8 = 0;
    if (puVar7 != (undefined4 *)0x0) {
      *puVar7 = puVar7[-1];
      iVar8 = *(int *)(this + 4);
    }
    *(int *)(this + 4) = iVar8 + 4;
    uVar11 = *param_3;
    uVar5 = (iVar8 + -4) - (int)param_2 & 0xfffffffc;
    _memmove((void *)(iVar8 - uVar5),param_2,uVar5);
    *param_2 = uVar11;
    return;
  }
  uVar5 = (int)puVar7 - *(int *)this >> 2;
  uVar14 = uVar5 == 0x3fffffff;
  if (!(bool)uVar14) {
    if (uVar5 == 0) {
      uVar9 = 1;
    }
    else {
      uVar9 = uVar5 * 2;
      if (uVar9 < uVar5) {
        uVar12 = 0xfffffffc;
        goto LAB_0007363c;
      }
      uVar14 = uVar9 == 0x3fffffff;
      if (0x3fffffff < uVar9) goto LAB_000736c0;
    }
    uVar12 = uVar9 << 2;
LAB_0007363c:
    pvVar1 = operator_new(uVar12);
    pvVar3 = *(void **)this;
    _memmove(pvVar1,pvVar3,(int)param_2 - (int)pvVar3);
    iVar8 = (int)pvVar1 + ((int)param_2 - (int)pvVar3);
    if (iVar8 != 0) {
      *(undefined4 *)((int)pvVar1 + ((int)param_2 - (int)pvVar3)) = *param_3;
    }
    iVar6 = *(int *)(this + 4);
    _memmove((void *)(iVar8 + 4),param_2,iVar6 - (int)param_2);
    if (*(void **)this != (void *)0x0) {
      operator_delete(*(void **)this);
    }
    *(void **)this = pvVar1;
    *(int *)(this + 4) = iVar8 + 4 + (iVar6 - (int)param_2);
    *(ulong *)(this + 8) = (int)pvVar1 + uVar12;
    return;
  }
  std::__throw_length_error("vector::_M_insert_aux");
LAB_000736c0:
  uVar11 = 0x736c4;
  uVar16 = std::__throw_bad_alloc();
  puVar7 = (undefined4 *)((ulonglong)uVar16 >> 0x20);
  piVar2 = (int *)uVar16;
  if ((bool)uVar14) {
    puVar13 = (undefined1 *)((uint)&stack0xfffffff8 & unaff_r8 >> 0x12);
  }
  *(undefined4 *)(puVar13 + -4) = uVar11;
  *(undefined1 **)(puVar13 + -8) = &stack0xfffffff8;
  *(undefined4 **)(puVar13 + -0xc) = param_2;
  *(undefined4 *)(puVar13 + -0x10) = unaff_r5;
  *(vector<BackgroundTrackMgr::BG_FileInfo*,std::allocator<BackgroundTrackMgr::BG_FileInfo*>> **)
   (puVar13 + -0x14) = this;
  *(undefined4 *)(puVar13 + -0x18) = unaff_r11;
  *(undefined4 **)(puVar13 + -0x1c) = param_3;
  piVar15 = (int *)(puVar13 + -0x20);
  *piVar15 = unaff_r8;
  puVar10 = (undefined4 *)piVar2[1];
  if (puVar10 != (undefined4 *)piVar2[2]) {
    iVar8 = 0;
    if (puVar10 != (undefined4 *)0x0) {
      *puVar10 = puVar10[-1];
      iVar8 = piVar2[1];
    }
    piVar2[1] = iVar8 + 4;
    uVar11 = *puVar4;
    uVar5 = (iVar8 + -4) - (int)puVar7 & 0xfffffffc;
    _memmove((void *)(iVar8 - uVar5),puVar7,uVar5);
    *puVar7 = uVar11;
    return;
  }
  uVar5 = (int)puVar10 - *piVar2 >> 2;
  uVar14 = uVar5 == 0x3fffffff;
  if (!(bool)uVar14) {
    if (uVar5 == 0) {
      uVar9 = 1;
    }
    else {
      uVar9 = uVar5 * 2;
      if (uVar9 < uVar5) {
        uVar12 = 0xfffffffc;
        goto LAB_00073764;
      }
      uVar14 = uVar9 == 0x3fffffff;
      if (0x3fffffff < uVar9) goto LAB_000737e8;
    }
    uVar12 = uVar9 << 2;
LAB_00073764:
    pvVar1 = operator_new(uVar12);
    pvVar3 = (void *)*piVar2;
    _memmove(pvVar1,pvVar3,(int)puVar7 - (int)pvVar3);
    iVar8 = (int)pvVar1 + ((int)puVar7 - (int)pvVar3);
    if (iVar8 != 0) {
      *(undefined4 *)((int)pvVar1 + ((int)puVar7 - (int)pvVar3)) = *puVar4;
    }
    iVar6 = piVar2[1];
    _memmove((void *)(iVar8 + 4),puVar7,iVar6 - (int)puVar7);
    if ((void *)*piVar2 != (void *)0x0) {
      operator_delete((void *)*piVar2);
    }
    *piVar2 = (int)pvVar1;
    piVar2[1] = iVar8 + 4 + (iVar6 - (int)puVar7);
    piVar2[2] = (int)pvVar1 + uVar12;
    return;
  }
  std::__throw_length_error("vector::_M_insert_aux");
LAB_000737e8:
  iVar8 = 0x737ec;
  puVar4 = (undefined4 *)std::__throw_bad_alloc();
  if ((bool)uVar14) {
    piVar15 = (int *)((uint)(puVar13 + -8) & unaff_r8 >> 0x12);
  }
  piVar15[-1] = iVar8;
  piVar15[-2] = (int)(puVar13 + -8);
  piVar15[-3] = (int)piVar2;
  _alSourcePlay(*puVar4);
  iVar8 = _alGetError();
  if (iVar8 == 0) {
    if (puVar4[1] != 0) {
      piVar15[-4] = 0;
      do {
        _alGetSourcei(*puVar4,0x1016,piVar15 + -4);
        iVar8 = _alGetError();
        if (iVar8 != 0) {
          _printf("%s: %x\n","Error getting processed buffer number");
          goto LAB_00073880;
        }
      } while (piVar15[-4] < 1);
      piVar15[-5] = 0;
      _alSourceUnqueueBuffers(*puVar4,1,piVar15 + -5);
      iVar8 = _alGetError();
      if (iVar8 != 0) {
        _printf("%s: %x\n","Error unqueueing buffers from source");
        goto LAB_00073880;
      }
    }
    _alSourcei(*puVar4,0x1007,1);
    _alGetError();
  }
  else {
    _printf("%s: %x\n","Error starting effect playback");
  }
LAB_00073880:
                    /* WARNING: Could not recover jumptable at 0x00073888. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)piVar15[-1])(0);
  return;
}
