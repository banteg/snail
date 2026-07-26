/*
 * mangled: _ZN18BackgroundTrackMgr16QueueStoppedProcEPvP16OpaqueAudioQueuem
 * demangled: BackgroundTrackMgr::QueueStoppedProc(void*, OpaqueAudioQueue*, unsigned long)
 * address: 00074814
 * size: 1308
 */

/* WARNING: Type propagation algorithm not settling */
/* BackgroundTrackMgr::QueueStoppedProc(void*, OpaqueAudioQueue*, unsigned long) */

void BackgroundTrackMgr::QueueStoppedProc(void *param_1,OpaqueAudioQueue *param_2,ulong param_3)

{
  undefined4 uVar1;
  int iVar2;
  void *pvVar3;
  int iVar4;
  bool bVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint in_fpscr;
  double dVar9;
  uint uVar10;
  double dVar11;
  undefined4 local_38 [2];
  undefined4 local_30;
  ulong local_2c [3];

  local_2c[1] = 4;
  _AudioQueueGetProperty(param_2,0x6171726e,local_2c + 2,local_2c + 1);
  if (local_2c[2] != 0) {
    return;
  }
  if (*(char *)((int)param_1 + 0x38) == '\0') {
    return;
  }
  local_2c[0] = _AudioQueueDispose(param_2,1);
  if (local_2c[0] != 0) {
    _printf("%s: %d\n","Error disposing queue",local_2c[0]);
    return;
  }
  iVar7 = *(int *)(*(int *)((int)param_1 + 0x28) + *(int *)((int)param_1 + 0x34) * 4);
  uVar1 = _CFRunLoopGetCurrent();
  iVar2 = _AudioQueueNewOutput
                    (iVar7 + 8,DAT_001edd48,param_1,uVar1,*(undefined4 *)PTR_001b61fc,0,param_1);
  if (iVar2 != 0) {
    _printf("%s: %d\n","Error creating queue",iVar2);
    goto LAB_000748d8;
  }
  local_2c[0] = 4;
  iVar2 = _AudioFileGetPropertyInfo(*(undefined4 *)(iVar7 + 4),0x6d676963,local_2c,0);
  if ((iVar2 == 0) && (local_2c[0] != 0)) {
    pvVar3 = operator_new__(local_2c[0]);
    iVar2 = _AudioFileGetProperty(*(undefined4 *)(iVar7 + 4),0x6d676963,local_2c,pvVar3);
    if (iVar2 != 0) {
      _printf("%s: %d\n","Error getting magic cookie",iVar2);
      goto LAB_000748d8;
    }
    iVar2 = _AudioQueueSetProperty(*(undefined4 *)param_1,0x61716d63,pvVar3,local_2c[0]);
    if (pvVar3 != (void *)0x0) {
      operator_delete__(pvVar3);
    }
    if (iVar2 != 0) {
      _printf("%s: %d\n","Error setting magic cookie",iVar2);
      goto LAB_000748d8;
    }
  }
  iVar2 = _AudioFileGetPropertyInfo(*(undefined4 *)(iVar7 + 4),0x636d6170,local_2c,0);
  if ((iVar2 == 0) && (local_2c[0] != 0)) {
    pvVar3 = _malloc(local_2c[0]);
    iVar2 = _AudioFileGetProperty(*(undefined4 *)(iVar7 + 4),0x636d6170,local_2c,pvVar3);
    if (iVar2 != 0) {
      _printf("%s: %d\n","Error getting channel layout from file",iVar2);
      goto LAB_000748d8;
    }
    iVar2 = _AudioQueueSetProperty(*(undefined4 *)param_1,0x6171636c,pvVar3,local_2c[0]);
    _free(pvVar3);
    if (iVar2 != 0) {
      _printf("%s: %d\n","Error setting channel layout on queue",iVar2);
      goto LAB_000748d8;
    }
  }
  iVar2 = _AudioQueueAddPropertyListener(*(undefined4 *)param_1,0x6171726e,DAT_001edd4c,param_1);
  if (iVar2 != 0) {
    _printf("%s: %d\n","Error adding isRunning property listener to queue",iVar2);
LAB_000748d8:
    _printf("%s: %d\n","Error setting up new queue",iVar2);
    return;
  }
  *(undefined1 *)((int)param_1 + 0x38) = 0;
  iVar2 = _AudioQueueSetParameter
                    (*(undefined4 *)param_1,1,*(float *)((int)param_1 + 0x20) * gMasterVolumeGain);
  if (iVar2 != 0) goto LAB_000748d8;
  iVar7 = *(int *)(*(int *)((int)param_1 + 0x28) + *(int *)((int)param_1 + 0x34) * 4);
  local_30 = 4;
  iVar2 = _AudioFileGetProperty(*(undefined4 *)(iVar7 + 4),0x706b7562,&local_30,local_2c);
  if (iVar2 != 0) {
    _printf("%s: %d\n","Error getting packet upper bound size",iVar2);
    goto LAB_00074b38;
  }
  if (*(int *)(iVar7 + 0x18) == 0) {
    iVar2 = *(int *)(iVar7 + 0x1c);
    if (iVar2 == 0) goto LAB_00074cd8;
    bVar5 = true;
LAB_00074a2c:
    dVar9 = (double)VectorUnsignedToFloat(local_2c[0],(byte)(in_fpscr >> 0x16) & 3);
    dVar11 = (double)VectorUnsignedToFloat(iVar2,(byte)(in_fpscr >> 0x16) & 3);
    uVar10 = VectorFloatToUnsigned(dVar9 * (*(double *)(iVar7 + 8) / dVar11) * 0.5,3);
    *(uint *)((int)param_1 + 0x10) = uVar10;
  }
  else {
    iVar2 = *(int *)(iVar7 + 0x1c);
    if (iVar2 != 0) {
      bVar5 = false;
      goto LAB_00074a2c;
    }
LAB_00074cd8:
    uVar10 = local_2c[0];
    if (local_2c[0] < 0x10000) {
      uVar10 = 0x10000;
    }
    bVar5 = true;
    *(uint *)((int)param_1 + 0x10) = uVar10;
  }
  if (uVar10 < 0x10001) {
    if (uVar10 < 0x4000) {
      uVar10 = 0x4000;
      *(undefined4 *)((int)param_1 + 0x10) = 0x4000;
    }
  }
  else if (local_2c[0] < uVar10) {
    uVar10 = 0x10000;
    *(undefined4 *)((int)param_1 + 0x10) = 0x10000;
  }
  uVar1 = ___udivsi3(*(undefined4 *)((int)param_1 + 0x10));
  *(undefined4 *)((int)param_1 + 0x1c) = uVar1;
  if ((*(int *)(iVar7 + 0x34) == 0) && (*(uint *)(iVar7 + 0x30) < uVar10 * 3)) {
    *(undefined1 *)(iVar7 + 0x38) = 1;
  }
  else if (*(char *)(iVar7 + 0x38) == '\0') {
    uVar1 = ___udivsi3(uVar10,local_2c[0],0);
    iVar8 = 3;
    *(undefined4 *)((int)param_1 + 0x1c) = uVar1;
    goto LAB_00074ab8;
  }
  local_30 = 8;
  iVar2 = _AudioFileGetProperty(*(undefined4 *)(iVar7 + 4),0x70636e74,&local_30,local_38);
  if (iVar2 != 0) {
    _printf("%s: %d\n","Error getting packet count for file",iVar2);
LAB_00074b38:
    _printf("%s: %d\n","Error setting up new queue buffers",iVar2);
    return;
  }
  iVar8 = 1;
  *(undefined4 *)((int)param_1 + 0x1c) = local_38[0];
  *(undefined4 *)((int)param_1 + 0x10) = *(undefined4 *)(iVar7 + 0x30);
LAB_00074ab8:
  if (bVar5) {
    pvVar3 = operator_new__(*(int *)((int)param_1 + 0x1c) << 4);
    *(void **)((int)param_1 + 0x24) = pvVar3;
  }
  else {
    *(undefined4 *)((int)param_1 + 0x24) = 0;
  }
  if (iVar8 != 0) {
    iVar4 = 0;
    do {
      iVar6 = iVar4 + 1;
      iVar2 = _AudioQueueAllocateBuffer
                        (*(undefined4 *)param_1,*(undefined4 *)((int)param_1 + 0x10),
                         (void *)((int)param_1 + iVar6 * 4));
      if (iVar2 != 0) {
        _printf("%s: %d\n","Error allocating buffer for queue",iVar2);
        goto LAB_00074b38;
      }
      QueueCallback(param_1,*(OpaqueAudioQueue **)param_1,
                    *(AudioQueueBuffer **)((int)param_1 + iVar4 * 4 + 4));
      if (*(char *)(iVar7 + 0x38) != '\0') {
        *(undefined1 *)(iVar7 + 0x39) = 1;
      }
      iVar4 = iVar6;
    } while (iVar6 != iVar8);
  }
  iVar2 = _AudioQueuePrime(*(undefined4 *)param_1,1,0);
  if (iVar2 == 0) {
    iVar2 = _AudioQueueStart(*(undefined4 *)param_1,0);
    if (iVar2 == 0) {
      return;
    }
  }
  else {
    _printf("Error priming queue");
  }
  _printf("%s: %d\n","Error starting queue",iVar2);
  return;
}
