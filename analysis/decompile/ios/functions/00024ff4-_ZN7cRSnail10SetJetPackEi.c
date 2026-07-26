/*
 * mangled: _ZN7cRSnail10SetJetPackEi
 * demangled: cRSnail::SetJetPack(int)
 * address: 00024ff4
 * size: 500
 */

/* cRSnail::SetJetPack(int) */

void __thiscall cRSnail::SetJetPack(cRSnail *this,int param_1)

{
  bool bVar1;
  undefined *this_00;
  int iVar2;
  ushort *puVar3;
  undefined2 *puVar4;
  int unaff_r8;
  float fVar5;

  if (param_1 == 0) {
    unaff_r8 = 0;
  }
  else if (param_1 == 1) {
    unaff_r8 = 4;
  }
  if (*(int *)(this + 0x117c) != unaff_r8) {
    if (*(int *)(this + 0x117c) == 4) {
      puVar4 = *(undefined2 **)(*(int *)(this + 0x1260) + 0x104);
      *(undefined2 **)(this + 0x118c) = puVar4;
      *puVar4 = 8;
      puVar3 = *(ushort **)(this + 0x118c);
      if ((*puVar3 & 8) == 0) {
        *(undefined4 *)(this + 0x1184) = 0;
        *(float *)(this + 0x1188) = ABS(*(float *)(puVar3 + 10));
      }
      else {
        fVar5 = *(float *)(puVar3 + 10);
        *(float *)(this + 0x1188) = -ABS(fVar5);
        *(float *)(this + 0x1184) = -ABS(fVar5) + 1.0;
      }
      bVar1 = false;
      *(undefined4 *)(this + 0x11bc) = 0;
      *(undefined4 *)(this + 0x10a8) = *(undefined4 *)(this + 0x1260);
      this_00 = PTR__gRSound_001b61e0;
      *(uint *)(*(int *)(this + 0x11c0) + 4) = *(uint *)(*(int *)(this + 0x11c0) + 4) | 0x20;
      cRSound::Play((cRSound *)this_00,0x1a);
    }
    else {
      bVar1 = true;
    }
    if (unaff_r8 == 0) {
      iVar2 = *(int *)(this + 0x11bc);
      *(undefined4 *)(this + iVar2 * 4 + 0x1194) = 0xffffffff;
      *(int *)(this + 0x11bc) = iVar2 + 1;
    }
    else if (unaff_r8 == 4) {
      if (bVar1) {
        puVar4 = *(undefined2 **)(*(int *)(this + 0x1260) + 0x104);
        *(undefined2 **)(this + 0x118c) = puVar4;
        *puVar4 = 4;
        puVar3 = *(ushort **)(this + 0x118c);
        if ((*puVar3 & 8) == 0) {
          *(undefined4 *)(this + 0x1184) = 0;
          *(float *)(this + 0x1188) = ABS(*(float *)(puVar3 + 10));
        }
        else {
          fVar5 = *(float *)(puVar3 + 10);
          *(float *)(this + 0x1188) = -ABS(fVar5);
          *(float *)(this + 0x1184) = -ABS(fVar5) + 1.0;
        }
        *(undefined4 *)(this + 0x10a8) = *(undefined4 *)(this + 0x1260);
        *(undefined4 *)(this + 0x11bc) = 0;
        *(uint *)(*(int *)(this + 0x11c0) + 4) = *(uint *)(*(int *)(this + 0x11c0) + 4) | 0x20;
        iVar2 = *(int *)(this + 0x11bc);
      }
      else {
        iVar2 = *(int *)(this + 0x11bc);
        *(undefined4 *)(this + iVar2 * 4 + 0x1194) = 1;
        iVar2 = iVar2 + 1;
        *(int *)(this + 0x11bc) = iVar2;
      }
      *(undefined4 *)(this + iVar2 * 4 + 0x1194) = 0;
      *(int *)(this + 0x11bc) = iVar2 + 1;
      cRSound::Play((cRSound *)PTR__gRSound_001b61e0,0x10);
      *(undefined4 *)(this + 0x117c) = 4;
      return;
    }
    *(int *)(this + 0x117c) = unaff_r8;
  }
  return;
}
