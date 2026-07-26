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
  int iVar3;
  int iVar4;
  int *piVar5;
  undefined8 uVar6;

  iVar2 = DAT_00075aa4;
  iVar4 = DAT_00075aa0 + 0x75844;
  if (*(char *)(**(int **)(iVar4 + DAT_00075aa4) + 0x718b9) != '\0') {
    return;
  }
  if (this[0x9c] == (cRClickStart)0x0) {
    uVar6 = cRBorder::UnHideInit(*(cRBorder **)(this + 0x78));
    iVar3 = *(int *)(this + 0x74);
  }
  else {
    uVar6 = cRBorder::HideInit(*(cRBorder **)(this + 0x78));
    iVar3 = *(int *)(this + 0x74);
  }
  if (iVar3 == 3) {
    piVar5 = *(int **)(iVar4 + iVar2);
    RandSeed(*(int *)(*(int *)(gDirectory + *piVar5 + 0x2540) + 0x68));
    iVar3 = *piVar5;
    *(undefined4 *)(this + 0x7c) = DAT_00075a94;
    *(undefined4 *)(this + 0x74) = 4;
    *(undefined4 *)(this + 0x80) = DAT_00075a98;
    cRBorderManager::Kill((cRBorderManager *)(iVar3 + 0xd14),*(cRBorder **)(this + 0x78));
  }
  else if (iVar3 != 4) {
    if (iVar3 != 2) {
      return;
    }
    iVar3 = **(int **)(iVar4 + iVar2);
    iVar2 = *(int *)(gDirectory + iVar3 + 0x2550);
    *(undefined1 *)(iVar3 + 0x4d368) = 1;
    if (8 < iVar2) {
      *(undefined4 *)(gDirectory + iVar3 + 0x2550) = 8;
    }
    if (*(char *)(iVar3 + 0x718b9) != '\0') {
      return;
    }
    if ((*(uint *)(*(int *)(iVar3 + 0x718ac) + 0x194) & 0x20000) != 0) {
      return;
    }
    if (gDirectory[iVar3 + 0x2544] == '\0') {
      if (this[0x9c] != (cRClickStart)0x0) {
        return;
      }
      if ((*(uint *)(*(int *)(iVar3 + 0x224) + 0x30) & 0x4000) == 0) {
        return;
      }
    }
    else if ((*(ushort *)
               (*(int *)(gDirectory + iVar3 + 0x2548) + *(int *)(gDirectory + iVar3 + 0x2550) * 6 +
               0x74) & 0x20) == 0) {
      return;
    }
    *(undefined1 *)(iVar3 + 0x23f) = 1;
    *(undefined1 *)(iVar3 + 0x23d) = 1;
    cVar1 = gDirectory[iVar3 + 0x2544];
    *(undefined4 *)(*(int *)(this + 0x8c) + 0x2ec) = *(undefined4 *)(gDirectory + iVar3 + 0x2550);
    *(undefined4 *)(this + 0x74) = 3;
    if (cVar1 != '\x01') {
      iVar2 = *(int *)(gDirectory + iVar3 + 0x2540) + *(int *)(gDirectory + iVar3 + 0x2550) * 6;
      *(int *)(*(int *)(gDirectory + iVar3 + 0x2540) + 0x24) = *(int *)(gDirectory + iVar3 + 0x2550)
      ;
      *(ushort *)(iVar2 + 0x74) = *(ushort *)(iVar2 + 0x74) & 0xfffe | 0x20;
    }
    uVar6 = RShellSetMouse(0,(float)uVar6,(float)((ulonglong)uVar6 >> 0x20));
    RShellSetMouse(1,(float)uVar6,(float)((ulonglong)uVar6 >> 0x20));
    cRSound::Play(*(int *)(iVar4 + DAT_00075aa8));
    return;
  }
  iVar2 = **(int **)(iVar4 + iVar2);
  *(float *)(this + 0x60) = *(float *)(this + 0x60) + DAT_00075a9c * *(float *)(this + 0x7c);
  *(float *)(this + 0x7c) = *(float *)(this + 0x7c) + *(float *)(this + 0x80);
  cLinkedList<cRBod>::Remove((cLinkedList<cRBod> *)(iVar2 + 0x358),(cRBod *)this);
  *(undefined4 *)(this + 0x74) = 0;
  return;
}
