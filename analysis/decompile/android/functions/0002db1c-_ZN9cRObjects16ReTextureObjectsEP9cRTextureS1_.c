/*
 * mangled: _ZN9cRObjects16ReTextureObjectsEP9cRTextureS1_
 * demangled: cRObjects::ReTextureObjects(cRTexture*, cRTexture*)
 * address: 0002db1c
 * size: 204
 */

/* cRObjects::ReTextureObjects(cRTexture*, cRTexture*) */

void __thiscall cRObjects::ReTextureObjects(cRObjects *this,cRTexture *param_1,cRTexture *param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;

  iVar1 = *(int *)this;
  if (iVar1 < 1) {
    return;
  }
  iVar4 = 0;
  iVar6 = 0;
  do {
    iVar7 = *(int *)(this + 8);
    iVar5 = iVar7 + iVar4;
    uVar3 = *(uint *)(iVar7 + iVar4);
    if ((int)uVar3 < 0) {
      wprintf("PATH START");
      uVar3 = *(uint *)(iVar7 + iVar4);
      iVar1 = *(int *)this;
    }
    if (((uVar3 & 0x4000000) != 0) && ((cRTexture *)**(undefined4 **)(iVar5 + 0x10c) == param_2)) {
      **(undefined4 **)(iVar5 + 0x10c) = param_1;
    }
    if (((*(int *)(iVar5 + 0xa0) != 0) && (iVar7 = *(int *)(iVar5 + 200), iVar7 != 0)) &&
       (iVar5 = *(int *)(iVar5 + 0xc0), 0 < iVar5)) {
      iVar2 = 0;
      do {
        iVar2 = iVar2 + 1;
        if (*(cRTexture **)(iVar7 + 0xc) == param_2) {
          *(cRTexture **)(iVar7 + 0xc) = param_1;
        }
        iVar7 = iVar7 + 0x30;
      } while (iVar2 != iVar5);
    }
    iVar6 = iVar6 + 1;
    iVar4 = iVar4 + 0x110;
  } while (iVar6 < iVar1);
  return;
}
