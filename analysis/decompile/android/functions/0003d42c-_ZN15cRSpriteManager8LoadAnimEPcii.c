/*
 * mangled: _ZN15cRSpriteManager8LoadAnimEPcii
 * demangled: cRSpriteManager::LoadAnim(char*, int, int)
 * address: 0003d42c
 * size: 784
 */

/* cRSpriteManager::LoadAnim(char*, int, int) */

void __thiscall
cRSpriteManager::LoadAnim(cRSpriteManager *this,char *param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  uint *puVar3;
  float fVar4;
  uint uVar5;
  char *pcVar6;
  int iVar7;
  char *pcVar8;
  uint in_fpscr;
  float fVar9;
  undefined4 local_230;
  char local_22c;
  char acStack_22b [511];
  int local_2c;

  local_2c = __stack_chk_guard;
  if (199 < param_2) {
    RShellError("Too many Sprite References - Increase RSPRITE_REFERENCE_MAX(%i) in RSprite.h",200);
  }
  pcVar6 = &local_22c;
  Rstrcpy(pcVar6,param_1);
  if (local_22c == '.') {
    pcVar8 = (char *)((int)&local_230 + 1);
  }
  else {
    do {
      pcVar8 = pcVar6;
      pcVar6 = pcVar8 + 1;
    } while (*pcVar6 != '.');
    pcVar8 = pcVar8 + -2;
  }
  if (((*pcVar8 == '0') && (pcVar8[1] == '0')) && (pcVar8[2] == '0')) {
    iVar1 = param_2 * 0x20;
    iVar7 = 0;
    while (iVar2 = RShellFindFile(&local_22c,false), iVar2 != 0) {
      if (iVar7 == 0) {
        puVar3 = (uint *)cRTextures::Add((cRTextures *)gTextureList,&local_22c,(cTgaHeader *)0x0,
                                         param_3);
        uVar5 = *puVar3;
        *(uint **)(gSpriteReference + iVar1 + 4) = puVar3;
        *puVar3 = uVar5 | 0x2000 | param_3;
      }
      else {
        puVar3 = (uint *)cRTextures::Add((cRTextures *)gTextureList,&local_22c,(cTgaHeader *)0x0,
                                         param_3);
        *puVar3 = *puVar3 | param_3;
      }
      iVar7 = iVar7 + 1;
      *pcVar8 = (char)(iVar7 / 100) + '0';
      pcVar8[1] = (char)((iVar7 % 100) / 10) + '0';
      pcVar8[2] = (char)iVar7 + (char)(iVar7 / 10) * -10 + '0';
    }
    iVar2 = *(int *)(gSpriteReference + iVar1 + 4);
    *(undefined4 *)(iVar2 + 0x94) = 0x3c888889;
    *(int *)(iVar2 + 0x90) = iVar7;
    *pcVar8 = '.';
    pcVar8[1] = 't';
    pcVar8[2] = 'x';
    *pcVar6 = 't';
    pcVar8[4] = '\0';
    iVar2 = RShellFindFile(&local_22c,false);
    if (iVar2 != 0) {
      pcVar6 = (char *)RShellLoadFile(&local_22c,(int *)0x0);
      local_230 = (char *)Rstrfind("Rate:",pcVar6);
      if (local_230 != (char *)0x0) {
        fVar4 = (float)Rstrfloat((char **)&local_230);
        fVar9 = (float)VectorSignedToFloat(iVar7,(byte)(in_fpscr >> 0x16) & 3);
        if (fVar4 / fVar9 == 0.0) {
          fVar4 = 0.0;
        }
        else {
          fVar4 = 1.0 / ((fVar4 / fVar9) * 60.0);
        }
        *(float *)(*(int *)(gSpriteReference + iVar1 + 4) + 0x94) = fVar4;
      }
      local_230 = (char *)Rstrfind("PingPong:yes",pcVar6);
      if (local_230 != (char *)0x0) {
        **(uint **)(gSpriteReference + iVar1 + 4) =
             **(uint **)(gSpriteReference + iVar1 + 4) | 0x4000;
      }
      RShellMemoryFree(pcVar6);
    }
  }
  else {
    RShellError("Incompatible Sprite Anim Filename %s",param_1);
  }
  if (local_2c == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}
