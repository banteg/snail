/*
 * mangled: _Z13G0TextureLoadii
 * demangled: G0TextureLoad(int, int)
 * address: 0006e434
 * size: 1424
 */

/* G0TextureLoad(int, int) */

void G0TextureLoad(int param_1,int param_2)

{
  undefined *puVar1;
  ID IVar2;
  int iVar3;
  undefined4 uVar4;
  size_t sVar5;
  ID IVar6;
  void *pvVar7;
  undefined1 *puVar8;
  char *pcVar9;
  int iVar10;
  int iVar11;
  uint unaff_r10;
  uint uVar12;
  uint in_fpscr;
  undefined4 uVar14;
  undefined4 uVar15;
  double dVar13;
  int local_54;
  undefined1 *local_44;
  uint local_40;
  int local_3c;
  int local_28;
  int local_24;

  puVar1 = PTR__gTextureList_001b61d0;
  iVar3 = param_1 * 0xa4;
  if ((*(uint *)(PTR__gTextureList_001b61d0 + iVar3 + 8) & 0x8000) != 0) {
    return;
  }
  IVar2 = NSAutoreleasePool::alloc((ID)&_OBJC_CLASS___NSAutoreleasePool,"alloc");
  IVar2 = NSAutoreleasePool::init(IVar2,"init");
  local_44 = (undefined1 *)RShellMemoryScratch();
  RShellMemoryScratch2();
  puVar8 = *(undefined1 **)(puVar1 + iVar3 + 0xa0);
  if (puVar8 == (undefined1 *)0x0) {
    *(uint *)(puVar1 + iVar3 + 8) = *(uint *)(puVar1 + iVar3 + 8) & 0xfffbffff;
    pcVar9 = puVar1 + iVar3 + 0x14;
    sVar5 = _strlen(puVar1 + iVar3 + 0x14);
    if (puVar1[iVar3 + sVar5 + 0x12] != 'v') {
      if ((puVar1[iVar3 + sVar5 + 0x11] == 'j') || (puVar1[iVar3 + sVar5 + 0x11] == 'p')) {
        uVar4 = RShellLoadFile(pcVar9,local_44,&local_28);
        IVar6 = NSData::dataWithBytes_length_
                          ((ID)&_OBJC_CLASS___NSData,"dataWithBytes:length:",uVar4,local_28);
        IVar6 = UIImage::imageWithData_((ID)&_OBJC_CLASS___UIImage,"imageWithData:",IVar6);
        IVar6 = UIImage::CGImage(IVar6,"CGImage");
        unaff_r10 = _CGImageGetWidth();
        local_40 = _CGImageGetHeight(IVar6);
        local_54 = local_40 * unaff_r10;
        pvVar7 = (void *)RShellMemoryMalloc(local_54 * 4,"NOT GIVEN");
        _memset(pvVar7,0,local_54 * 4);
        uVar4 = _CGImageGetColorSpace(IVar6);
        uVar4 = _CGBitmapContextCreate(pvVar7,unaff_r10,local_40,8,unaff_r10 << 2,uVar4,1);
        uVar14 = VectorUnsignedToFloat(unaff_r10,(byte)(in_fpscr >> 0x16) & 3);
        uVar15 = VectorUnsignedToFloat(local_40,(byte)(in_fpscr >> 0x16) & 3);
        _CGContextDrawImage(uVar4,0,0,uVar14,uVar15,IVar6);
        _CGContextRelease(uVar4);
        local_44[0x11] = 8;
        local_44[2] = 2;
        local_44[0x10] = 0x20;
        *(short *)(local_44 + 0xc) = (short)unaff_r10;
        local_44[7] = 0;
        local_44[6] = 0;
        local_44[5] = 0;
        local_44[4] = 0;
        local_44[3] = 0;
        local_44[1] = 0;
        *local_44 = 0;
        *(undefined2 *)(local_44 + 8) = 0;
        *(undefined2 *)(local_44 + 10) = 0;
        *(short *)(local_44 + 0xe) = (short)local_40;
        if (local_40 != 0) {
          local_3c = 0;
          do {
            if (unaff_r10 != 0) {
              uVar12 = 0;
              iVar3 = 0;
              do {
                iVar10 = uVar12 + unaff_r10 * ((local_40 - local_3c) + -1);
                iVar11 = uVar12 + unaff_r10 * local_3c;
                local_44[iVar10 * 4 + 0x14] = *(undefined1 *)((int)pvVar7 + iVar11 * 4 + 2);
                local_44[iVar10 * 4 + 0x13] = *(undefined1 *)((int)pvVar7 + iVar11 * 4 + 1);
                local_44[iVar10 * 4 + 0x12] = *(undefined1 *)((int)pvVar7 + iVar11 * 4);
                local_44[iVar10 * 4 + 0x15] = *(undefined1 *)((int)pvVar7 + iVar11 * 4 + 3);
                uVar12 = iVar3 + 1;
                iVar3 = iVar3 + 1;
              } while (unaff_r10 != uVar12);
            }
            uVar12 = local_3c + 1;
            local_3c = local_3c + 1;
          } while (local_40 != uVar12);
        }
        RShellMemoryFree(pvVar7);
      }
      else {
        local_44 = (undefined1 *)RShellLoadFile(pcVar9,local_44,(int *)0x0);
        if (local_44 == (undefined1 *)0x0) {
          iVar3 = 1;
          uVar12 = 0;
          goto LAB_0006e97c;
        }
        unaff_r10 = (uint)*(ushort *)(local_44 + 0xc);
        local_40 = (uint)*(ushort *)(local_44 + 0xe);
        local_54 = local_40 * unaff_r10;
      }
      goto LAB_0006e4d8;
    }
    uVar12 = RShellLoadFile(pcVar9,local_44,&local_24);
    dVar13 = (double)VectorSignedToFloat(local_24 << 1,(byte)(in_fpscr >> 0x16) & 3);
    *(uint *)(puVar1 + iVar3 + 8) = *(uint *)(puVar1 + iVar3 + 8) | 0x40000;
    iVar3 = 1 - uVar12;
    if (1 < uVar12) {
      iVar3 = 0;
    }
    unaff_r10 = VectorFloatToSigned(SQRT(dVar13),3);
    local_44 = puVar8;
    local_40 = unaff_r10;
LAB_0006e97c:
    if (iVar3 != 0) {
      RShellError("Cannot find Texture %s",pcVar9);
      NSAutoreleasePool::release(IVar2,"release");
      return;
    }
    local_54 = local_40 * unaff_r10;
  }
  else {
    local_54 = local_40 * unaff_r10;
    local_44 = puVar8;
LAB_0006e4d8:
    uVar12 = 0;
  }
  _G0VRamCount = local_54 * 4 + _G0VRamCount;
  if ((*(uint *)(PTR__gTextureList_001b61d0 + param_1 * 0xa4 + 8) & 0x100) == 0) {
    G0BindTexture(param_1);
    _glBindTexture(0xde1,*(undefined4 *)(texNameList + param_1 * 4));
    _glEnable(0xde1);
    _glTexParameteri(0xde1,&DAT_00002802,&DAT_00002901);
    _glTexParameteri(0xde1,&DAT_00002803,&DAT_00002901);
    _glTexParameteri(0xde1,&DAT_00002800,&DAT_00002601);
    _glTexParameteri(0xde1,&DAT_00002801,&DAT_00002601);
    if (uVar12 == 0) {
      if (local_44[0x10] == ' ') {
        uVar4 = 0x1908;
      }
      else {
        if (local_44[0x10] != '\x18') goto LAB_0006e520;
        uVar4 = 0x1907;
      }
      _glTexImage2D(0xde1,0,uVar4,unaff_r10,local_40,0,uVar4,0x1401,local_44 + 0x12);
    }
    else {
      _glCompressedTexImage2D(0xde1,0,0x8c02,unaff_r10,local_40,0,local_24,uVar12);
      iVar3 = _glGetError();
      if (iVar3 != 0) {
        wprintf("GL ERROR %i\n");
      }
    }
  }
LAB_0006e520:
  puVar1 = PTR__gTextureList_001b61d0;
  iVar3 = param_1 * 0xa4;
  *(uint *)(PTR__gTextureList_001b61d0 + iVar3 + 0xc) = unaff_r10;
  *(uint *)(puVar1 + iVar3 + 0x10) = local_40;
  if (local_44 != (undefined1 *)0x0) {
    if ((*(uint *)(puVar1 + iVar3 + 8) & 0x20) == 0) {
      *(undefined4 *)(puVar1 + iVar3 + 0xa0) = 0;
    }
    else {
      uVar4 = RShellLoadFile(puVar1 + iVar3 + 0x14,(int *)0x0);
      *(undefined4 *)(puVar1 + iVar3 + 0xa0) = uVar4;
    }
  }
  NSAutoreleasePool::release(IVar2,"release");
  return;
}
