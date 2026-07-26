/*
 * mangled: _ZN18BackgroundTrackMgr13QueueCallbackEPvP16OpaqueAudioQueueP16AudioQueueBuffer
 * demangled: BackgroundTrackMgr::QueueCallback(void*, OpaqueAudioQueue*, AudioQueueBuffer*)
 * address: 00073ccc
 * size: 2732
 */

/* BackgroundTrackMgr::QueueCallback(void*, OpaqueAudioQueue*, AudioQueueBuffer*) */

void BackgroundTrackMgr::QueueCallback
               (void *param_1,OpaqueAudioQueue *param_2,AudioQueueBuffer *param_3)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  void *pvVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  bool bVar18;
  uint in_fpscr;
  double dVar19;
  double dVar20;
  undefined4 local_124;
  undefined4 uStack_120;
  uint *local_11c;
  undefined4 local_118;
  int local_114;
  OpaqueAudioQueue *local_10c;
  undefined4 *local_108;
  undefined4 *local_104;
  int local_100;
  int local_fc;
  undefined4 *local_f8;
  int local_f4;
  int local_f0;
  void *local_ec;
  int local_e8;
  int local_e4;
  int local_e0;
  int local_dc;
  int local_d8;
  int local_d4;
  uint local_d0;
  int local_cc;
  int local_c8;
  undefined4 local_c4;
  int local_c0;
  undefined1 auStack_bc [4];
  undefined4 local_b8;
  undefined *local_a4;
  undefined *local_a0;
  undefined1 *local_9c;
  undefined1 *local_98;
  undefined1 *local_94;
  AudioQueueBuffer *local_88;
  undefined4 *local_84;
  undefined4 *local_80;
  int local_7c;
  undefined4 local_78 [2];
  undefined4 local_70;
  ulong local_6c;
  undefined4 local_68;
  uint local_64 [17];

  local_9c = &stack0xfffffff8;
  local_94 = (undefined1 *)&local_124;
  local_a4 = PTR_001b615c;
  local_a0 = &::GCC_except_table2;
  local_98 = &LAB_00074788;
  local_10c = param_2;
  local_108 = param_1;
  local_88 = param_3;
  __Unwind_SjLj_Register(auStack_bc);
  local_104 = local_108;
  uVar5 = (int)(local_108[0x10] - local_108[0xf]) >> 2;
  local_84 = (undefined4 *)0x0;
  local_80 = (undefined4 *)0x0;
  local_7c = 0;
  if (uVar5 != 0) {
    if (0x3fffffff < uVar5) {
      local_b8 = 1;
      std::__throw_bad_alloc();
      goto LAB_0007468c;
    }
    local_fc = uVar5 << 2;
    local_b8 = 1;
    local_80 = operator_new(uVar5 << 2);
    local_7c = (int)local_80 + local_fc;
  }
  pvVar4 = (void *)local_104[0xf];
  local_f8 = local_80;
  local_f4 = local_104[0x10] - (int)pvVar4;
  local_84 = local_80;
  _memmove(local_80,pvVar4,local_104[0x10] - (int)pvVar4);
  local_80 = (undefined4 *)((int)local_f8 + local_f4);
  iVar3 = (int)local_80 - (int)local_84 >> 2;
  if (iVar3 == 0) {
LAB_00073df0:
    local_cc = 0;
  }
  else {
    if (local_88 != (AudioQueueBuffer *)*local_84) {
      iVar7 = 0;
      do {
        iVar7 = iVar7 + 1;
        if (iVar7 == iVar3) goto LAB_00073df0;
      } while (local_88 != (AudioQueueBuffer *)local_84[iVar7]);
    }
    local_b8 = 2;
    iVar3 = _AudioQueueFreeBuffer(local_10c);
    if (iVar3 == 0) {
      local_80 = local_80 + -1;
    }
    local_cc = 1;
  }
  if (local_84 != (undefined4 *)0x0) {
    operator_delete(local_84);
  }
  if (local_cc != 0) goto LAB_00073f20;
  if (*(char *)(*(int *)(local_104[10] + local_104[0xd] * 4) + 0x39) == '\0') {
LAB_00073e34:
    do {
      local_64[0] = local_104[7];
      local_11c = local_64;
      local_124 = local_104[5];
      uStack_120 = local_104[6];
      local_118 = *(undefined4 *)(local_88 + 4);
      local_b8 = 0xffffffff;
      iVar3 = _AudioFileReadPackets
                        (*(undefined4 *)(*(int *)(local_104[10] + local_104[0xd] * 4) + 4),0,
                         &local_68,local_104[9]);
      if (iVar3 != 0) {
        _printf("%s: %d\n","Error reading file data");
        goto LAB_00073f20;
      }
      *(undefined4 *)(local_88 + 8) = local_68;
      if (local_64[0] != 0) break;
      iVar3 = *(int *)(local_104[10] + local_104[0xd] * 4);
      if (*(char *)(iVar3 + 0x38) != '\0') {
        *(undefined1 *)(iVar3 + 0x39) = 1;
      }
      local_104[5] = 0;
      local_104[6] = 0;
      iVar3 = local_104[10];
      uVar5 = local_104[0xd];
      if ((local_104[0xb] - iVar3 >> 2) - 1U <= uVar5) {
        if (*(char *)((int)local_104 + 0x39) == '\0') {
          local_c8 = 0;
          local_100 = 0;
          goto LAB_00073fbc;
        }
        local_b8 = 0xffffffff;
        iVar3 = _AudioQueueStop(local_10c);
joined_r0x00074714:
        if (iVar3 != 0) {
          _printf("%s: %d\n","Error stopping queue");
        }
        goto LAB_00073f20;
      }
      local_100 = uVar5 + 1;
      local_c8 = local_100 * 4;
LAB_00073fbc:
      iVar7 = *(int *)(iVar3 + uVar5 * 4);
      iVar6 = *(int *)(iVar3 + local_c8);
      local_d8 = *(int *)(iVar7 + 0x20);
      *(undefined1 *)(iVar7 + 0x39) = 0;
      uVar17 = *(uint *)(iVar7 + 0x14);
      local_d4 = *(int *)(iVar6 + 0x20);
      uVar15 = *(uint *)(iVar7 + 0x1c);
      uVar5 = in_fpscr & 0xfffffff;
      in_fpscr = uVar5 | (uint)(*(double *)(iVar7 + 8) == 0.0) << 0x1e;
      uVar14 = *(uint *)(iVar7 + 0x24);
      uVar12 = *(uint *)(iVar7 + 0x28);
      iVar3 = *(int *)(iVar7 + 0x10);
      uVar16 = *(uint *)(iVar6 + 0x14);
      local_d0 = *(uint *)(iVar6 + 0x1c);
      uVar11 = *(uint *)(iVar6 + 0x24);
      uVar13 = *(uint *)(iVar6 + 0x28);
      iVar8 = *(int *)(iVar6 + 0x10);
      if (((SUB41(in_fpscr >> 0x1e,0)) ||
          (in_fpscr = uVar5 | (uint)(*(double *)(iVar6 + 8) == 0.0) << 0x1e,
          SUB41(in_fpscr >> 0x1e,0))) ||
         (in_fpscr = uVar5 | (uint)(*(double *)(iVar6 + 8) == *(double *)(iVar7 + 8)) << 0x1e,
         SUB41(in_fpscr >> 0x1e,0))) {
        if (iVar3 != 0 && iVar8 != 0) {
          if (iVar8 != iVar3) goto LAB_00074044;
          if ((uVar17 != 0) && (uVar16 != 0)) {
            iVar3 = 0x6c70636d;
            if (iVar8 == 0x6c70636d) {
              uVar5 = uVar17 & 0x7fffffff;
              uVar10 = uVar16 & 0x7fffffff & uVar5;
              uVar1 = uVar16 & 0x7fffffff;
              if ((uVar10 & 8) != 0) {
                uVar5 = uVar17 & 0x7fffffef;
                uVar10 = uVar16 & 0x7fffffef & uVar5;
                uVar1 = uVar16 & 0x7fffffef;
              }
              uVar16 = uVar1;
              uVar17 = uVar5;
              if ((uVar10 & 1) != 0) {
                uVar17 = uVar5 & 0xfffffffb;
                uVar16 = uVar16 & 0xfffffffb;
              }
              if ((uVar12 < 9) && ((uVar17 & 8) != 0)) {
                uVar17 = uVar17 & 0xfffffffd;
              }
              if ((uVar13 < 9) && ((uVar16 & 8) != 0)) {
                uVar16 = uVar16 & 0xfffffffd;
              }
              uVar5 = uVar14;
              if (uVar14 < 2) {
                uVar5 = uVar11;
              }
              if (uVar5 < 2) {
                uVar17 = uVar17 & 0xffffffdf;
                uVar16 = uVar16 & 0xffffffdf;
              }
            }
            if (uVar17 != uVar16) goto LAB_00074044;
          }
        }
        if ((*(int *)(iVar7 + 0x18) != 0 && *(int *)(iVar6 + 0x18) != 0) &&
           (*(int *)(iVar6 + 0x18) != *(int *)(iVar7 + 0x18))) goto LAB_00074044;
        if (uVar15 != 0) {
          uVar16 = local_d0;
        }
        if ((uVar15 != 0 && uVar16 != 0) && (uVar16 != uVar15)) goto LAB_00074044;
        if (local_d8 != 0) {
          iVar3 = local_d4;
        }
        if ((((local_d8 != 0 && iVar3 != 0) && (iVar3 != local_d8)) ||
            ((uVar14 != 0 && uVar11 != 0 && (uVar11 != uVar14)))) ||
           ((uVar12 != 0 && uVar13 != 0 && (uVar13 != uVar12)))) goto LAB_00074044;
        if (*(char *)(iVar6 + 0x38) == *(char *)(iVar7 + 0x38)) {
          if (*(char *)(iVar6 + 0x38) == '\0') {
            local_c4 = 2;
          }
          else if (*(uint *)(iVar7 + 0x34) < *(uint *)(iVar6 + 0x34)) {
LAB_00074284:
            local_c4 = 3;
          }
          else if (*(uint *)(iVar6 + 0x34) == *(uint *)(iVar7 + 0x34)) {
            if (*(uint *)(iVar7 + 0x30) < *(uint *)(iVar6 + 0x30)) goto LAB_00074284;
            local_c4 = 1;
          }
          else {
            local_c4 = 1;
          }
        }
        else {
          local_c4 = 3;
        }
      }
      else {
LAB_00074044:
        local_c4 = 4;
      }
      if (local_100 != local_104[0xd]) {
        local_b8 = 0xffffffff;
        iVar3 = _AudioFileClose(*(undefined4 *)(*(int *)(local_104[10] + local_104[0xd] * 4) + 4));
        if (iVar3 != 0) {
          _printf("%s: %d\n","Error closing file");
          goto LAB_00073f20;
        }
        local_104[0xd] = local_100;
        puVar9 = *(undefined4 **)(local_104[10] + local_c8);
        local_b8 = 0xffffffff;
        iVar3 = LoadFileDataInfo((char *)*puVar9,(OpaqueAudioFileID **)(puVar9 + 1),
                                 (AudioStreamBasicDescription *)(puVar9 + 2),
                                 (ulonglong *)(puVar9 + 0xc));
        if (iVar3 != 0) {
          _printf("%s: %d\n","Error opening file");
          goto LAB_00073f20;
        }
      }
      switch((char)local_c4) {
      case '\x01':
        *(undefined4 *)(local_88 + 8) =
             *(undefined4 *)(*(int *)(local_104[10] + local_104[0xd] * 4) + 0x30);
      case '\x02':
        local_f0 = *(int *)(local_104[10] + local_104[0xd] * 4);
        local_6c = 4;
        local_b8 = 0xffffffff;
        iVar3 = _AudioFileGetPropertyInfo(*(undefined4 *)(local_f0 + 4),0x6d676963,&local_6c,0);
        if ((iVar3 == 0) && (local_6c != 0)) {
          local_ec = operator_new__(local_6c);
          iVar3 = _AudioFileGetProperty(*(undefined4 *)(local_f0 + 4),0x6d676963,&local_6c,local_ec)
          ;
          if (iVar3 == 0) {
            local_b8 = 0xffffffff;
            local_c0 = _AudioQueueSetProperty(local_10c,0x61716d63,local_ec,local_6c);
            if (local_ec != (void *)0x0) {
              operator_delete__(local_ec);
            }
            if (local_c0 != 0) {
              local_b8 = 0xffffffff;
              _printf("%s: %d\n","Error setting cookie data for queue");
            }
          }
          else {
            _printf("%s: %d\n","Error getting cookie data");
          }
        }
        break;
      case '\x03':
        puVar9 = (undefined4 *)local_104[0x10];
        if (puVar9 == (undefined4 *)local_104[0x11]) {
          local_b8 = 0xffffffff;
          std::vector<AudioQueueBuffer*,std::allocator<AudioQueueBuffer*>>::_M_insert_aux
                    ((vector<AudioQueueBuffer*,std::allocator<AudioQueueBuffer*>> *)
                     (local_104 + 0xf),puVar9,&local_88);
        }
        else {
          if (puVar9 != (undefined4 *)0x0) {
            *puVar9 = local_88;
          }
          local_104[0x10] = local_104[0x10] + 4;
        }
        local_e8 = *(int *)(local_104[10] + local_104[0xd] * 4);
        local_70 = 4;
        local_b8 = 0xffffffff;
        iVar3 = _AudioFileGetProperty(*(undefined4 *)(local_e8 + 4),0x706b7562,&local_70,&local_6c);
        if (iVar3 == 0) {
          if (*(int *)(local_e8 + 0x18) == 0) {
            iVar3 = *(int *)(local_e8 + 0x1c);
            if (iVar3 == 0) goto LAB_000743a4;
            local_e0 = 1;
LAB_000745dc:
            dVar19 = (double)VectorUnsignedToFloat(local_6c,(byte)(in_fpscr >> 0x16) & 3);
            dVar20 = (double)VectorUnsignedToFloat(iVar3,(byte)(in_fpscr >> 0x16) & 3);
            uVar2 = VectorFloatToUnsigned(dVar19 * (*(double *)(local_e8 + 8) / dVar20) * 0.5,3);
            local_104[4] = uVar2;
          }
          else {
            iVar3 = *(int *)(local_e8 + 0x1c);
            if (iVar3 != 0) {
              local_e0 = 0;
              goto LAB_000745dc;
            }
LAB_000743a4:
            uVar5 = local_6c;
            if (local_6c < 0x10000) {
              uVar5 = 0x10000;
            }
            local_104[4] = uVar5;
            local_e0 = 1;
          }
          uVar5 = local_104[4];
          if (uVar5 < 0x10001) {
            if (uVar5 < 0x4000) {
              local_104[4] = 0x4000;
            }
          }
          else if (local_6c < uVar5) {
            local_104[4] = 0x10000;
          }
          uVar2 = ___udivsi3(local_104[4]);
          local_104[7] = uVar2;
          if ((*(int *)(local_e8 + 0x34) == 0) &&
             (*(uint *)(local_e8 + 0x30) < (uint)(local_104[4] * 3))) {
            *(undefined1 *)(local_e8 + 0x38) = 1;
LAB_00074424:
            local_70 = 8;
            local_b8 = 0xffffffff;
            iVar3 = _AudioFileGetProperty
                              (*(undefined4 *)(local_e8 + 4),0x70636e74,&local_70,local_78);
            if (iVar3 != 0) {
              _printf("%s: %d\n","Error getting packet count for file");
              break;
            }
            local_104[7] = local_78[0];
            local_104[4] = *(undefined4 *)(local_e8 + 0x30);
            local_dc = 1;
          }
          else {
            if (*(char *)(local_e8 + 0x38) != '\0') goto LAB_00074424;
            uVar2 = ___udivsi3(local_104[4],local_6c,0);
            local_104[7] = uVar2;
            local_dc = 3;
          }
          if (local_e0 == 0) {
            local_104[9] = 0;
          }
          else {
LAB_0007468c:
            local_b8 = 0xffffffff;
            pvVar4 = operator_new__(local_104[7] << 4);
            local_104[9] = pvVar4;
          }
          if (0 < local_dc) {
            local_e4 = 0;
            do {
              local_114 = local_e4 + 1;
              local_b8 = 0xffffffff;
              iVar3 = _AudioQueueAllocateBuffer(*local_104,local_104[4],local_104 + local_114);
              if (iVar3 != 0) {
                _printf("%s: %d\n","Error allocating buffer for queue");
                break;
              }
              local_b8 = 0xffffffff;
              QueueCallback(local_104,(OpaqueAudioQueue *)*local_104,
                            (AudioQueueBuffer *)local_104[local_e4 + 1]);
              if (*(char *)(local_e8 + 0x38) != '\0') {
                *(undefined1 *)(local_e8 + 0x39) = 1;
              }
              local_e4 = local_114;
            } while (local_114 != local_dc);
          }
        }
        else {
          _printf("%s: %d\n","Error getting packet upper bound size");
        }
        break;
      case '\x04':
        *(undefined1 *)(local_104 + 0xe) = 1;
        local_b8 = 0xffffffff;
        iVar3 = _AudioQueueStop(local_10c,0);
        goto joined_r0x00074714;
      }
    } while (local_64[0] == 0);
  }
  else {
    uVar5 = (int)(local_104[0xb] - local_104[10]) >> 2;
    bVar18 = uVar5 == 1;
    if (bVar18) {
      uVar5 = (uint)*(byte *)((int)local_104 + 0x39);
    }
    if (!bVar18 || uVar5 != 0) goto LAB_00073e34;
    local_64[0] = local_104[7];
  }
  local_b8 = 0xffffffff;
  iVar3 = _AudioQueueEnqueueBuffer(local_10c,local_88);
  if (iVar3 == 0) {
    iVar3 = *(int *)(local_104[10] + local_104[0xd] * 4);
    if (*(char *)(iVar3 + 0x38) != '\0') {
      *(undefined1 *)(iVar3 + 0x39) = 1;
    }
    uVar5 = local_104[5];
    local_104[5] = uVar5 + local_64[0];
    local_104[6] = local_104[6] + (uint)CARRY4(uVar5,local_64[0]);
  }
  else {
    _printf("%s: %d\n","Error enqueuing new buffer");
  }
LAB_00073f20:
  __Unwind_SjLj_Unregister(auStack_bc);
  return;
}
