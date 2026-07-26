/*
 * mangled: _ZN14cRSubHighScore8MiniLoadEi
 * demangled: cRSubHighScore::MiniLoad(int)
 * address: 0003ecec
 * size: 756
 */

/* cRSubHighScore::MiniLoad(int) */

void __thiscall cRSubHighScore::MiniLoad(cRSubHighScore *this,int param_1)

{
  void *pvVar1;
  int iVar2;
  cRSubHighScore *pcVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  char local_a4 [4];
  char acStack_a0 [4];
  undefined2 local_9c;
  undefined1 local_9a;
  int local_24;

  if (param_1 - 0x16U < 0x33) {
    _sprintf(local_a4,"TT_%03i.bin");
    iVar9 = param_1 << 6;
  }
  else if (param_1 == 0x49) {
    iVar9 = 0x1240;
    local_a4[0] = 'S';
    local_a4[1] = 'L';
    local_a4[2] = '_';
    local_a4[3] = '0';
    acStack_a0[0] = '0';
    acStack_a0[1] = '0';
    acStack_a0[2] = '.';
    acStack_a0[3] = 'b';
    local_9c = 0x6e69;
    local_9a = 0;
  }
  else {
    iVar9 = param_1 * 0x40;
    _sprintf(local_a4,"HS_%08i.bin",*(undefined4 *)(this + param_1 * 0x38 + 0x28));
  }
  pvVar1 = (void *)RShellMemoryScratch();
  RShellLoadFile(local_a4,pvVar1,&local_24);
  if (local_24 == 0) {
    this[iVar9 + param_1 * -8 + 0x2c] = (cRSubHighScore)0x0;
  }
  else {
    if (*(uint *)((int)pvVar1 + 0x28) ==
        (*(int *)((int)pvVar1 + 4) * *(int *)((int)pvVar1 + 4) ^ 0xdeadbabeU)) {
      *(undefined4 *)(this + 0x20dcc) = *(undefined4 *)((int)pvVar1 + 0x74);
      *(undefined4 *)(this + 0x20d88) = *(undefined4 *)((int)pvVar1 + 0x2c);
      *(undefined4 *)(this + 0x20d8c) = *(undefined4 *)((int)pvVar1 + 0x30);
      *(undefined4 *)(this + 0x20da8) = *(undefined4 *)((int)pvVar1 + 0x48);
      *(undefined4 *)(this + 0x20d94) = *(undefined4 *)((int)pvVar1 + 0x54);
      Rstrcpy((char *)(this + 0x20db4),(char *)((int)pvVar1 + 0x5c));
      *(undefined4 *)(this + 0x20d64) = *(undefined4 *)((int)pvVar1 + 4);
      uVar5 = *(undefined4 *)((int)pvVar1 + 0xc);
      uVar4 = *(undefined4 *)((int)pvVar1 + 0x10);
      uVar6 = *(undefined4 *)((int)pvVar1 + 0x14);
      *(undefined4 *)(this + 0x20d68) = *(undefined4 *)((int)pvVar1 + 8);
      *(undefined4 *)(this + 0x20d6c) = uVar5;
      *(undefined4 *)(this + 0x20d70) = uVar4;
      *(undefined4 *)(this + 0x20d74) = uVar6;
      uVar5 = *(undefined4 *)((int)pvVar1 + 0x1c);
      *(undefined4 *)(this + 0x20d78) = *(undefined4 *)((int)pvVar1 + 0x18);
      *(undefined4 *)(this + 0x20d7c) = uVar5;
      *(undefined4 *)(this + 0x20d80) = *(undefined4 *)((int)pvVar1 + 0x20);
      *(undefined4 *)(this + 0x20dac) = *(undefined4 *)((int)pvVar1 + 0x4c);
      *(undefined4 *)(this + 0x20db0) = *(undefined4 *)((int)pvVar1 + 0x50);
      *(undefined4 *)(this + 0x40810) = *(undefined4 *)((int)pvVar1 + 0x78);
      *(undefined4 *)(this + 0x40814) = *(undefined4 *)((int)pvVar1 + 0x7c);
      *(undefined4 *)(this + 0x20d84) = *(undefined4 *)((int)pvVar1 + 0x24);
      *(undefined4 *)(this + 0x20dc8) = *(undefined4 *)((int)pvVar1 + 0x70);
      *(undefined4 *)(this + 0x40818) = *(undefined4 *)((int)pvVar1 + 0x80);
      *(undefined4 *)(this + 0x4081c) = *(undefined4 *)((int)pvVar1 + 0x84);
      *(undefined4 *)(this + 0x20d98) = *(undefined4 *)((int)pvVar1 + 0x38);
      *(undefined4 *)(this + 0x20d9c) = *(undefined4 *)((int)pvVar1 + 0x3c);
      *(undefined4 *)(this + 0x20da0) = *(undefined4 *)((int)pvVar1 + 0x40);
      *(undefined4 *)(this + 0x20da4) = *(undefined4 *)((int)pvVar1 + 0x44);
      if (0 < *(int *)(this + 0x20dcc)) {
        iVar2 = 0;
        pcVar3 = this + 0x20dd0;
        do {
          iVar7 = iVar2 * 2;
          iVar2 = iVar2 + 1;
          *(undefined2 *)pcVar3 = *(undefined2 *)((int)pvVar1 + iVar7 + 0x88);
          iVar7 = *(int *)(this + 0x20dcc);
          pcVar3 = pcVar3 + 6;
        } while (iVar2 < iVar7);
        if (0 < iVar7) {
          iVar2 = 0;
          pcVar3 = this + 0x20dd2;
          do {
            iVar8 = iVar2 * 2;
            iVar2 = iVar2 + 1;
            *(undefined2 *)pcVar3 = *(undefined2 *)((int)pvVar1 + iVar8 + iVar7 * 2 + 0x88);
            iVar8 = *(int *)(this + 0x20dcc);
            pcVar3 = pcVar3 + 6;
          } while (iVar2 < iVar8);
          if (0 < iVar8) {
            iVar2 = 0;
            pcVar3 = this + 0x20dd4;
            do {
              iVar7 = iVar2 + iVar8 * 4 + 0x88;
              iVar2 = iVar2 + 1;
              *(ushort *)pcVar3 = (ushort)*(byte *)((int)pvVar1 + iVar7);
              pcVar3 = pcVar3 + 6;
            } while (iVar2 < *(int *)(this + 0x20dcc));
          }
        }
      }
      uVar5 = 1;
      *(undefined4 *)(this + 0x20d60) = 1;
    }
    else {
      uVar5 = 0;
      *(undefined4 *)(this + 0x20d60) = 0;
    }
    iVar9 = iVar9 + param_1 * -8;
    *(undefined4 *)(this + iVar9 + 8) = uVar5;
    uVar5 = *(undefined4 *)(this + 0x20d6c);
    uVar4 = *(undefined4 *)(this + 0x20d70);
    uVar6 = *(undefined4 *)(this + 0x20d74);
    *(undefined4 *)(this + iVar9 + 0xc) = *(undefined4 *)(this + 0x20d68);
    *(undefined4 *)(this + iVar9 + 0x10) = uVar5;
    *(undefined4 *)(this + iVar9 + 0x14) = uVar4;
    *(undefined4 *)(this + iVar9 + 0x18) = uVar6;
    uVar5 = *(undefined4 *)(this + 0x20d7c);
    *(undefined4 *)(this + iVar9 + 0x1c) = *(undefined4 *)(this + 0x20d78);
    *(undefined4 *)(this + iVar9 + 0x20) = uVar5;
    _sprintf((char *)(this + iVar9 + 0x2d),(char *)(this + 0x20db4));
    *(undefined4 *)(this + iVar9 + 0x24) = *(undefined4 *)(this + 0x20d64);
    this[iVar9 + 0x2c] = (cRSubHighScore)0x1;
  }
  return;
}
