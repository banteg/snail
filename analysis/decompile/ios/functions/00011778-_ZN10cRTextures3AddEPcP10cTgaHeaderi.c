/*
 * mangled: _ZN10cRTextures3AddEPcP10cTgaHeaderi
 * demangled: cRTextures::Add(char*, cTgaHeader*, int)
 * address: 00011778
 * size: 408
 */

/* cRTextures::Add(char*, cTgaHeader*, int) */

cRTextures * __thiscall
cRTextures::Add(cRTextures *this,char *param_1,cTgaHeader *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;

  iVar2 = *(int *)this;
  if (iVar2 == *(int *)(this + 4)) {
    RShellError("Too many Texture References - Increase TextureList.Init(MAX) in g0.cpp");
    iVar2 = *(int *)this;
  }
  if (((param_3 & 0x800U) == 0) && (iVar3 = 0, 0 < iVar2)) {
    do {
      iVar2 = iVar3 * 0xa4;
      iVar1 = RTextCompStart((char *)(this + iVar2 + 0x14),param_1);
      if (iVar1 != 0) goto LAB_000118f8;
      iVar2 = *(int *)this;
      iVar3 = iVar3 + 1;
    } while (iVar3 < iVar2);
  }
  RTextCopy((char *)(this + iVar2 * 0xa4 + 0x14),param_1);
  *(int *)(this + *(int *)this * 0xa4 + 0x94) = *(int *)this;
  *(undefined4 *)(this + *(int *)this * 0xa4 + 8) = 0;
  *(undefined4 *)(this + *(int *)this * 0xa4 + 8) = 0x400;
  *(cTgaHeader **)(this + *(int *)this * 0xa4 + 0xa0) = param_2;
  *(undefined4 *)(this + *(int *)this * 0xa4 + 0xa8) = 1;
  iVar2 = *(int *)this * 0xa4;
  *(int *)this = *(int *)this + 1;
LAB_000118f8:
  return this + iVar2 + 8;
}
