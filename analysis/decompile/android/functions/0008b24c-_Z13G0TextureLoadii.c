/*
 * mangled: _Z13G0TextureLoadii
 * demangled: G0TextureLoad(int, int)
 * address: 0008b24c
 * size: 588
 */

/* G0TextureLoad(int, int) */

void G0TextureLoad(int param_1,int param_2)

{
  void *pvVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int aiStack_2c [2];

  iVar4 = param_1 * 0xa4;
  if ((*(uint *)(gTextureList + iVar4 + 8) & 0x8000) == 0) {
    pvVar1 = (void *)RShellMemoryScratch();
    RShellMemoryScratch2();
    iVar3 = *(int *)(gTextureList + iVar4 + 0xa0);
    if (iVar3 == 0) {
      *(uint *)(gTextureList + iVar4 + 8) = *(uint *)(gTextureList + iVar4 + 8) & 0xfffbffff;
      iVar3 = RShellLoadFile(gTextureList + iVar4 + 0x14,pvVar1,aiStack_2c);
      if (iVar3 == 0) {
        RShellError("Cannot find Texture %s",gTextureList + iVar4 + 0x14);
        return;
      }
    }
    uVar5 = (uint)*(ushort *)(iVar3 + 0xc);
    uVar6 = (uint)*(ushort *)(iVar3 + 0xe);
    G0VRamCount = G0VRamCount + uVar6 * uVar5 * 4;
    if ((*(uint *)(gTextureList + param_1 * 0xa4 + 8) & 0x100) == 0) {
      G0BindTexture(param_1);
      glBindTexture(0xde1,*(undefined4 *)(texNameList + param_1 * 4));
      gBindTextureRefLast = 0xffffffff;
      glEnable(0xde1);
      glTexParameteri(0xde1,0x2802,0x2901);
      glTexParameteri(0xde1,0x2803,0x2901);
      glTexParameteri(0xde1,0x2800,0x2601);
      glTexParameteri(0xde1,0x2801,0x2601);
      if (*(char *)(iVar3 + 0x10) == ' ') {
        glTexImage2D(0xde1,0,0x1908,uVar5,uVar6,0,0x1908,0x1401,iVar3 + 0x12);
      }
      else if (*(char *)(iVar3 + 0x10) == '\x18') {
        glTexImage2D(0xde1,0,0x1907,uVar5,uVar6,0,0x1907,0x1401,iVar3 + 0x12);
        wprintf("24bit Texture %s (%i x %i)",param_1 * 0xa4 + 0x9cc84,uVar5,uVar6);
      }
      cRResourceManager::Add
                ((cRResourceManager *)&gResourceManager,0,param_1,param_1 * 0xa4 + 0x9cc84);
    }
    iVar4 = param_1 * 0xa4;
    *(uint *)(gTextureList + iVar4 + 0xc) = uVar5;
    *(uint *)(gTextureList + iVar4 + 0x10) = uVar6;
    if ((*(uint *)(gTextureList + iVar4 + 8) & 0x20) == 0) {
      *(undefined4 *)(gTextureList + iVar4 + 0xa0) = 0;
    }
    else {
      uVar2 = RShellLoadFile(gTextureList + iVar4 + 0x14,(int *)0x0);
      *(undefined4 *)(gTextureList + iVar4 + 0xa0) = uVar2;
    }
  }
  return;
}
