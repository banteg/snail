/*
 * mangled: _Z16G0TextureSetLoadi
 * demangled: G0TextureSetLoad(int)
 * address: 0006ea28
 * size: 200
 */

/* G0TextureSetLoad(int) */

void G0TextureSetLoad(int param_1)

{
  undefined *puVar1;
  int iVar2;

  puVar1 = PTR__gTextureList_001b61d0;
  texNameList = RShellMemoryMalloc(*(int *)PTR__gTextureList_001b61d0 << 2,
                                   "OpenGL Texture name list");
  texResidentList = RShellMemoryMalloc(*(int *)puVar1 << 2,"OpenGL Texture resident list");
  _glShadeModel("b");
  _glPixelStorei(0xcf5,1);
  _glGenTextures(*(undefined4 *)puVar1,texNameList);
  _G0VRamCount = 0;
  if (0 < *(int *)puVar1) {
    iVar2 = 0;
    do {
      G0TextureLoad(iVar2,param_1);
      iVar2 = iVar2 + 1;
    } while (iVar2 < *(int *)PTR__gTextureList_001b61d0);
  }
  iVar2 = _G0VRamCount;
  if (_G0VRamCount < 0) {
    iVar2 = _G0VRamCount + 0x3ff;
  }
  wprintf("Estimate %i K VRAM\n",iVar2 >> 10);
  return;
}
