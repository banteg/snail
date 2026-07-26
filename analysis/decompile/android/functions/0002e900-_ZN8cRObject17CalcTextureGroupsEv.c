/*
 * mangled: _ZN8cRObject17CalcTextureGroupsEv
 * demangled: cRObject::CalcTextureGroups()
 * address: 0002e900
 * size: 336
 */

/* cRObject::CalcTextureGroups() */

void __thiscall cRObject::CalcTextureGroups(cRObject *this)

{
  int iVar1;
  uint *puVar2;
  int iVar3;
  uint *puVar4;
  int unaff_r6;
  int iVar5;
  int iVar6;
  uint uVar7;
  bool bVar8;
  ushort *puVar9;

  bVar8 = false;
  do {
    iVar6 = *(int *)(this + 0xc0);
    iVar1 = *(int *)(this + 200);
    iVar5 = unaff_r6;
    if (iVar6 < 1) {
      iVar5 = 0;
    }
    puVar4 = *(uint **)(iVar1 + 0xc);
    unaff_r6 = iVar5;
    if (0 < iVar6) {
      if (bVar8) {
        iVar6 = 0;
        unaff_r6 = 0;
        iVar5 = 0;
        do {
          puVar9 = (ushort *)(iVar1 + iVar6);
          if ((*(uint *)this & 0x400) == 0) {
            puVar2 = *(uint **)(puVar9 + 6);
          }
          else {
            puVar2 = *(uint **)(puVar9 + 6);
            uVar7 = *puVar2;
            *(ushort *)(iVar1 + iVar6) = *(ushort *)(iVar1 + iVar6) | 2;
            *puVar2 = uVar7 | 0x20;
          }
          iVar3 = iVar1 + iVar6;
          iVar6 = iVar6 + 0x30;
          if ((puVar4 != puVar2) || ((*puVar9 & 0x10) != 0)) {
            puVar4 = *(uint **)(iVar3 + 0xc);
            *(int *)(*(int *)(this + 0xdc) + unaff_r6 * 4) = iVar5;
            unaff_r6 = unaff_r6 + 1;
          }
          iVar5 = iVar5 + 1;
        } while (iVar5 < *(int *)(this + 0xc0));
LAB_0002e9c8:
        *(int *)(*(int *)(this + 0xdc) + unaff_r6 * 4) = iVar5;
        return;
      }
      iVar3 = 0;
      unaff_r6 = 0;
      iVar5 = 0;
      do {
        while( true ) {
          puVar9 = (ushort *)(iVar1 + iVar3);
          if ((*(uint *)this & 0x400) == 0) {
            puVar2 = *(uint **)(puVar9 + 6);
          }
          else {
            puVar2 = *(uint **)(puVar9 + 6);
            uVar7 = *puVar2;
            *(ushort *)(iVar1 + iVar3) = *(ushort *)(iVar1 + iVar3) | 2;
            *puVar2 = uVar7 | 0x20;
            iVar6 = *(int *)(this + 0xc0);
          }
          if ((puVar4 != puVar2) || ((*puVar9 & 0x10) != 0)) break;
          iVar5 = iVar5 + 1;
          iVar3 = iVar3 + 0x30;
          if (iVar6 <= iVar5) goto LAB_0002e9ac;
        }
        iVar5 = iVar5 + 1;
        unaff_r6 = unaff_r6 + 1;
        puVar4 = *(uint **)(puVar9 + 6);
        iVar3 = iVar3 + 0x30;
      } while (iVar5 < iVar6);
    }
LAB_0002e9ac:
    if (bVar8) goto LAB_0002e9c8;
    RequestFaceQuadTextureGroups(this,unaff_r6 + 1);
    bVar8 = true;
  } while( true );
}
