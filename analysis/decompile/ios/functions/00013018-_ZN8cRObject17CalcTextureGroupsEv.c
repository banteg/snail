/*
 * mangled: _ZN8cRObject17CalcTextureGroupsEv
 * demangled: cRObject::CalcTextureGroups()
 * address: 00013018
 * size: 452
 */

/* cRObject::CalcTextureGroups() */

void __thiscall cRObject::CalcTextureGroups(cRObject *this)

{
  undefined4 uVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  int iVar5;
  int unaff_r6;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;

  iVar7 = 0;
  do {
    iVar9 = *(int *)(this + 0xc0);
    iVar8 = *(int *)(this + 200);
    iVar6 = unaff_r6;
    if (iVar9 < 1) {
      iVar6 = 0;
    }
    unaff_r6 = iVar6;
    if (0 < iVar9) {
      if (iVar7 == 1) {
        unaff_r6 = 0;
        iVar6 = 0;
        iVar9 = 0;
        iVar7 = *(int *)(iVar8 + 0xc);
        do {
          if ((*(uint *)this & 0x400) != 0) {
            *(ushort *)(iVar9 + iVar8) = *(ushort *)(iVar9 + iVar8) | 2;
            puVar3 = *(uint **)(*(int *)(this + 200) + iVar9 + 0xc);
            *puVar3 = *puVar3 | 0x20;
            iVar8 = *(int *)(this + 200);
          }
          iVar2 = *(int *)(iVar9 + iVar8 + 0xc);
          if ((iVar2 != iVar7) || ((*(ushort *)(iVar9 + iVar8) & 0x10) != 0)) {
            *(int *)(*(int *)(this + 0xdc) + unaff_r6 * 4) = iVar6;
            iVar8 = *(int *)(this + 200);
            unaff_r6 = unaff_r6 + 1;
            iVar2 = *(int *)(iVar9 + iVar8 + 0xc);
          }
          iVar6 = iVar6 + 1;
          iVar9 = iVar9 + 0x30;
          iVar7 = iVar2;
        } while (iVar6 < *(int *)(this + 0xc0));
LAB_00013118:
        *(int *)(*(int *)(this + 0xdc) + unaff_r6 * 4) = iVar6;
        return;
      }
      unaff_r6 = 0;
      iVar5 = 0;
      iVar2 = 0;
      iVar6 = *(int *)(iVar8 + 0xc);
      while( true ) {
        if ((*(uint *)this & 0x400) != 0) {
          *(ushort *)(iVar2 + iVar8) = *(ushort *)(iVar2 + iVar8) | 2;
          puVar3 = *(uint **)(iVar2 + *(int *)(this + 200) + 0xc);
          *puVar3 = *puVar3 | 0x20;
          iVar8 = *(int *)(this + 200);
          iVar9 = *(int *)(this + 0xc0);
        }
        iVar4 = *(int *)(iVar2 + iVar8 + 0xc);
        if ((iVar4 != iVar6) || ((*(ushort *)(iVar2 + iVar8) & 0x10) != 0)) {
          unaff_r6 = unaff_r6 + 1;
        }
        iVar6 = iVar5 + 1;
        if (iVar9 <= iVar6) break;
        iVar5 = iVar5 + 1;
        iVar2 = iVar2 + 0x30;
        iVar6 = iVar4;
      }
    }
    if (iVar7 == 1) goto LAB_00013118;
    iVar6 = unaff_r6 + 1;
    if (*(int *)(this + 0xd4) == 0) {
      uVar1 = RShellMemoryMalloc(iVar6 * 4,"Object FaceQuad Texture Groups");
      *(int *)(this + 0xd8) = iVar6;
      *(undefined4 *)(this + 0xdc) = uVar1;
    }
    else if (*(int *)(this + 0xd8) < iVar6) {
      RShellError("Fixed FaceQuadTextureGroupsNumber too small");
    }
    iVar7 = iVar7 + 1;
    *(int *)(this + 0xd4) = iVar6;
    if (iVar7 == 2) {
      return;
    }
  } while( true );
}
