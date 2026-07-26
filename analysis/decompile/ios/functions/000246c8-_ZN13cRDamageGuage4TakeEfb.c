/*
 * mangled: _ZN13cRDamageGuage4TakeEfb
 * demangled: cRDamageGuage::Take(float, bool)
 * address: 000246c8
 * size: 540
 */

/* cRDamageGuage::Take(float, bool) */

void __thiscall cRDamageGuage::Take(cRDamageGuage *this,float param_1,bool param_2)

{
  undefined *this_00;
  int iVar1;
  ushort *puVar2;
  int iVar3;
  float fVar4;

  iVar1 = *(int *)PTR__Game_001b60b8;
  if ((((*(uint *)(iVar1 + 0x822e4) & 0x80) == 0) || (param_2)) &&
     ((*(int *)this != 2 ||
      ((param_1 == 0.0 || 0.0 > param_1 &&
       ((0.0 <= param_1 || (*(char *)(iVar1 + 0x8218c) == '\0')))))))) {
    if ((*(float *)(this + 0x24) == 0.0) && (0.0 < param_1)) {
      *(undefined4 *)(iVar1 + 0x85f40) = 0;
      *(undefined4 *)(iVar1 + 0x85f3c) = 1;
      *(undefined4 *)(iVar1 + 0x85f28) = 1;
      *(undefined4 *)(iVar1 + 0x85f44) = 0x3daaaaab;
      this_00 = PTR__gVoiceManager_001b61d8;
      iVar1 = cRVoiceManager::Play((cRVoiceManager *)PTR__gVoiceManager_001b61d8,0,1,-1);
      if (iVar1 == 0) {
        iVar1 = cRVoiceManager::Play((cRVoiceManager *)this_00,9,0,-1);
        if (iVar1 != 0) {
          *(undefined4 *)(this + 0x24) = *(undefined4 *)(this + 0x28);
        }
        iVar1 = *(int *)PTR__Game_001b60b8;
        if (*(char *)(iVar1 + 0x82280) == '\0') {
          puVar2 = *(ushort **)(*(int *)(iVar1 + 0x84bd4) + 0x104);
          *(ushort **)((int)&DAT_000848bc + iVar1) = puVar2;
          if ((*puVar2 & 8) == 0) {
            *(undefined4 *)(OFCloudStorageBlob::getResourceDiscoveredNotification + iVar1) = 0;
            *(float *)(iVar1 + 0x848b8) = ABS(*(float *)(puVar2 + 10));
          }
          else {
            fVar4 = *(float *)(puVar2 + 10);
            *(float *)(iVar1 + 0x848b8) = -ABS(fVar4);
            *(float *)(OFCloudStorageBlob::getResourceDiscoveredNotification + iVar1) =
                 -ABS(fVar4) + 1.0;
          }
          iVar3 = *(int *)(iVar1 + 0x848f0);
          *(undefined4 *)(iVar1 + 0x847dc) = *(undefined4 *)(iVar1 + 0x84bd4);
          *(undefined4 *)(OFCloudStorageBlob::getService + iVar1 + 4) = 0;
          *(uint *)(iVar3 + 4) = *(uint *)(iVar3 + 4) | 0x20;
          iVar3 = *(int *)PTR__Game_001b60b8;
          iVar1 = *(int *)(OFCloudStorageBlob::getService + iVar3 + 4);
          *(undefined4 *)(OFCloudStorageBlob::keyStr + iVar1 * 4 + iVar3 + 4) = 1;
          *(int *)(OFCloudStorageBlob::getService + iVar3 + 4) = iVar1 + 1;
        }
      }
      else {
        *(undefined4 *)(this + 0x24) = *(undefined4 *)(this + 0x28);
      }
    }
    fVar4 = *(float *)(this + 0x1c) + param_1;
    if (fVar4 < 0.0) {
      fVar4 = 0.0;
    }
    else if (1.0 < fVar4) {
      fVar4 = 1.0;
    }
    *(float *)(this + 0x1c) = fVar4;
  }
  return;
}
