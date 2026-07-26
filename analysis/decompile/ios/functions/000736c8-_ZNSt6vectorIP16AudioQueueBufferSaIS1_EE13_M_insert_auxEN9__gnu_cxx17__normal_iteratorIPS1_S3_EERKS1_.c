/*
 * mangled: _ZNSt6vectorIP16AudioQueueBufferSaIS1_EE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPS1_S3_EERKS1_
 * demangled: std::vector<AudioQueueBuffer*, std::allocator<AudioQueueBuffer*>>::_M_insert_aux(__gnu_cxx::__normal_iterator<AudioQueueBuffer**, std::vector<AudioQueueBuffer*, std::allocator<AudioQueueBuffer*>>>, AudioQueueBuffer* const&)
 * address: 000736c8
 * size: 296
 */

/* std::vector<AudioQueueBuffer*, std::allocator<AudioQueueBuffer*>
   >::_M_insert_aux(__gnu_cxx::__normal_iterator<AudioQueueBuffer**, std::vector<AudioQueueBuffer*,
   std::allocator<AudioQueueBuffer*> > >, AudioQueueBuffer* const&) */

void __thiscall
std::vector<AudioQueueBuffer*,std::allocator<AudioQueueBuffer*>>::_M_insert_aux
          (vector<AudioQueueBuffer*,std::allocator<AudioQueueBuffer*>> *this,undefined4 *param_2,
          undefined4 *param_3)

{
  void *pvVar1;
  void *pvVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  int unaff_r8;
  ulong uVar9;
  undefined1 *puVar10;
  undefined1 uVar11;

  puVar10 = &stack0xffffffe0;
  puVar5 = *(undefined4 **)(this + 4);
  if (puVar5 != *(undefined4 **)(this + 8)) {
    iVar6 = 0;
    if (puVar5 != (undefined4 *)0x0) {
      *puVar5 = puVar5[-1];
      iVar6 = *(int *)(this + 4);
    }
    *(int *)(this + 4) = iVar6 + 4;
    uVar8 = *param_3;
    uVar3 = (iVar6 + -4) - (int)param_2 & 0xfffffffc;
    _memmove((void *)(iVar6 - uVar3),param_2,uVar3);
    *param_2 = uVar8;
    return;
  }
  uVar3 = (int)puVar5 - *(int *)this >> 2;
  uVar11 = uVar3 == 0x3fffffff;
  if (!(bool)uVar11) {
    if (uVar3 == 0) {
      uVar7 = 1;
    }
    else {
      uVar7 = uVar3 * 2;
      if (uVar7 < uVar3) {
        uVar9 = 0xfffffffc;
        goto LAB_00073764;
      }
      uVar11 = uVar7 == 0x3fffffff;
      if (0x3fffffff < uVar7) goto LAB_000737e8;
    }
    uVar9 = uVar7 << 2;
LAB_00073764:
    pvVar1 = operator_new(uVar9);
    pvVar2 = *(void **)this;
    _memmove(pvVar1,pvVar2,(int)param_2 - (int)pvVar2);
    iVar6 = (int)pvVar1 + ((int)param_2 - (int)pvVar2);
    if (iVar6 != 0) {
      *(undefined4 *)((int)pvVar1 + ((int)param_2 - (int)pvVar2)) = *param_3;
    }
    iVar4 = *(int *)(this + 4);
    _memmove((void *)(iVar6 + 4),param_2,iVar4 - (int)param_2);
    if (*(void **)this != (void *)0x0) {
      operator_delete(*(void **)this);
    }
    *(void **)this = pvVar1;
    *(int *)(this + 4) = iVar6 + 4 + (iVar4 - (int)param_2);
    *(ulong *)(this + 8) = (int)pvVar1 + uVar9;
    return;
  }
  std::__throw_length_error("vector::_M_insert_aux");
LAB_000737e8:
  uVar8 = 0x737ec;
  puVar5 = (undefined4 *)std::__throw_bad_alloc();
  if ((bool)uVar11) {
    puVar10 = (undefined1 *)((uint)&stack0xfffffff8 & unaff_r8 >> 0x12);
  }
  *(undefined4 *)(puVar10 + -4) = uVar8;
  *(undefined1 **)(puVar10 + -8) = &stack0xfffffff8;
  *(vector<AudioQueueBuffer*,std::allocator<AudioQueueBuffer*>> **)(puVar10 + -0xc) = this;
  _alSourcePlay(*puVar5);
  iVar6 = _alGetError();
  if (iVar6 == 0) {
    if (puVar5[1] != 0) {
      *(undefined4 *)(puVar10 + -0x10) = 0;
      do {
        _alGetSourcei(*puVar5,0x1016,puVar10 + -0x10);
        iVar6 = _alGetError();
        if (iVar6 != 0) {
          _printf("%s: %x\n","Error getting processed buffer number");
          goto LAB_00073880;
        }
      } while (*(int *)(puVar10 + -0x10) < 1);
      *(undefined4 *)(puVar10 + -0x14) = 0;
      _alSourceUnqueueBuffers(*puVar5,1,puVar10 + -0x14);
      iVar6 = _alGetError();
      if (iVar6 != 0) {
        _printf("%s: %x\n","Error unqueueing buffers from source");
        goto LAB_00073880;
      }
    }
    _alSourcei(*puVar5,0x1007,1);
    _alGetError();
  }
  else {
    _printf("%s: %x\n","Error starting effect playback");
  }
LAB_00073880:
                    /* WARNING: Could not recover jumptable at 0x00073888. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(puVar10 + -4))(0);
  return;
}
