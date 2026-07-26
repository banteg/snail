/*
 * mangled: _ZN12cRClickStart2AIEv
 * demangled: cRClickStart::AI()
 * address: 0007582c
 * size: 616
 */

/* cRClickStart::AI() */

void __thiscall cRClickStart::AI(cRClickStart *this)

{
  char cVar1;
  int iVar2;
  cLinkedList<cRBod> *this_00;
  int iVar3;
  undefined8 uVar4;

  if (*(char *)(Game + 0x718b9) != '\0') {
    return;
  }
  if (this[0x9c] == (cRClickStart)0x0) {
    uVar4 = cRBorder::UnHideInit(*(cRBorder **)(this + 0x78));
    iVar3 = *(int *)(this + 0x74);
  }
  else {
    uVar4 = cRBorder::HideInit(*(cRBorder **)(this + 0x78));
    iVar3 = *(int *)(this + 0x74);
  }
  iVar2 = Game;
  if (iVar3 == 3) {
    RandSeed(*(int *)(*(int *)(gDirectory + Game + 0x2540) + 0x68));
    iVar3 = Game;
    *(undefined4 *)(this + 0x7c) = 0;
    *(undefined4 *)(this + 0x74) = 4;
    *(undefined4 *)(this + 0x80) = 0x3c888889;
    cRBorderManager::Kill((cRBorderManager *)(iVar3 + 0xd14),*(cRBorder **)(this + 0x78));
  }
  else if (iVar3 != 4) {
    if (iVar3 != 2) {
      return;
    }
    iVar3 = *(int *)(gDirectory + Game + 0x2550);
    *(undefined1 *)(Game + 0x4d368) = 1;
    if (8 < iVar3) {
      *(undefined4 *)(gDirectory + iVar2 + 0x2550) = 8;
    }
    if (*(char *)(iVar2 + 0x718b9) != '\0') {
      return;
    }
    if ((*(uint *)(*(int *)(iVar2 + 0x718ac) + 0x194) & 0x20000) != 0) {
      return;
    }
    if (gDirectory[iVar2 + 0x2544] == '\0') {
      if (this[0x9c] != (cRClickStart)0x0) {
        return;
      }
      if ((*(uint *)(*(int *)(iVar2 + 0x224) + 0x30) & 0x4000) == 0) {
        return;
      }
    }
    else if ((*(ushort *)
               (*(int *)(gDirectory + iVar2 + 0x2548) + *(int *)(gDirectory + iVar2 + 0x2550) * 6 +
               0x74) & 0x20) == 0) {
      return;
    }
    *(undefined1 *)(iVar2 + 0x23f) = 1;
    *(undefined1 *)(iVar2 + 0x23d) = 1;
    cVar1 = gDirectory[iVar2 + 0x2544];
    *(undefined4 *)(*(int *)(this + 0x8c) + 0x2ec) = *(undefined4 *)(gDirectory + iVar2 + 0x2550);
    *(undefined4 *)(this + 0x74) = 3;
    if (cVar1 != '\x01') {
      iVar3 = *(int *)(gDirectory + iVar2 + 0x2540) + *(int *)(gDirectory + iVar2 + 0x2550) * 6;
      *(int *)(*(int *)(gDirectory + iVar2 + 0x2540) + 0x24) = *(int *)(gDirectory + iVar2 + 0x2550)
      ;
      *(ushort *)(iVar3 + 0x74) = *(ushort *)(iVar3 + 0x74) & 0xfffe | 0x20;
    }
    uVar4 = RShellSetMouse(0,(float)uVar4,(float)((ulonglong)uVar4 >> 0x20));
    RShellSetMouse(1,(float)uVar4,(float)((ulonglong)uVar4 >> 0x20));
    cRSound::Play((int)&gRSound);
    return;
  }
  this_00 = (cLinkedList<cRBod> *)(Game + 0x358);
  *(float *)(this + 0x60) = *(float *)(this + 0x60) + *(float *)(this + 0x7c) * 16.0;
  *(float *)(this + 0x7c) = *(float *)(this + 0x7c) + *(float *)(this + 0x80);
  cLinkedList<cRBod>::Remove(this_00,(cRBod *)this);
  *(undefined4 *)(this + 0x74) = 0;
  return;
}
