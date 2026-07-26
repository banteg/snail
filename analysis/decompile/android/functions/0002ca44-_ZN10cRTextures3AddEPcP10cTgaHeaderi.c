/*
 * mangled: _ZN10cRTextures3AddEPcP10cTgaHeaderi
 * demangled: cRTextures::Add(char*, cTgaHeader*, int)
 * address: 0002ca44
 * size: 268
 */

/* cRTextures::Add(char*, cTgaHeader*, int) */

cRTextures * __thiscall
cRTextures::Add(cRTextures *this,char *param_1,cTgaHeader *param_2,int param_3)

{
  int iVar1;
  int iVar2;

  if (*(int *)this == *(int *)(this + 4)) {
    RShellError((char *)(DAT_0002cb50 + 0x2ca70 + DAT_0002cb54));
  }
  if (((param_3 & 0x800U) != 0) ||
     (iVar1 = cRHash::Search((cRHash *)(this + 0x39b0),param_1), iVar1 == -1)) {
    cRHash::Add((cRHash *)(this + 0x39b0),param_1,*(int *)this);
    RTextCopy((char *)(this + *(int *)this * 0xa4 + 0x14),param_1);
    *(int *)(this + *(int *)this * 0xa4 + 0x94) = *(int *)this;
    *(undefined4 *)(this + *(int *)this * 0xa4 + 8) = 0;
    *(undefined4 *)(this + *(int *)this * 0xa4 + 8) = 0x400;
    iVar2 = *(int *)this;
    *(undefined4 *)(this + iVar2 * 0xa4 + 0xa8) = 1;
    iVar1 = *(int *)this;
    *(cTgaHeader **)(this + iVar2 * 0xa4 + 0xa0) = param_2;
    *(int *)this = iVar1 + 1;
  }
  return this + iVar1 * 0xa4 + 8;
}
