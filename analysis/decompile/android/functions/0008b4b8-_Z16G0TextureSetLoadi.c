/*
 * mangled: _Z16G0TextureSetLoadi
 * demangled: G0TextureSetLoad(int)
 * address: 0008b4b8
 * size: 220
 */

/* G0TextureSetLoad(int) */

void G0TextureSetLoad(int param_1)

{
  int extraout_r1;
  int iVar1;
  int iVar2;

  texNameList = RShellMemoryMalloc(gTextureList._0_4_ << 2,"OpenGL Texture name list");
  texResidentList = RShellMemoryMalloc(gTextureList._0_4_ << 2,"OpenGL Texture resident list");
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
      G0TextureLoad(iVar2,param_1);
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
