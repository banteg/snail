/*
 * mangled: _Z18G0TextureSetReLoadv
 * demangled: G0TextureSetReLoad()
 * address: 0008b5b0
 * size: 164
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* G0TextureSetReLoad() */

void G0TextureSetReLoad(void)

{
  int extraout_r1;
  int iVar1;
  int iVar2;

  glShadeModel(0x1d00);
  glPixelStorei(0xcf5,1);
  glGenTextures(gTextureList._0_4_,texNameList);
  iVar2 = 0;
  iVar1 = extraout_r1;
  if ((int)gTextureList._0_4_ < 1) {
    iVar1 = 0;
  }
  G0VRamCount = 0;
  if (0 < (int)gTextureList._0_4_) {
    do {
      G0TextureLoad(iVar2,1);
      iVar2 = iVar2 + 1;
    } while (iVar2 < (int)gTextureList._0_4_);
    iVar1 = G0VRamCount;
    if (G0VRamCount < 0) {
      iVar1 = G0VRamCount + 0x3ff;
    }
    iVar1 = iVar1 >> 10;
  }
  wprintf("Estimate %i K VRAM\n",iVar1);
  return;
}
