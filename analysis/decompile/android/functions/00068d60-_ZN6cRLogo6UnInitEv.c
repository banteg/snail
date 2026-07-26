/*
 * mangled: _ZN6cRLogo6UnInitEv
 * demangled: cRLogo::UnInit()
 * address: 00068d60
 * size: 304
 */

/* cRLogo::UnInit() */

void __thiscall cRLogo::UnInit(cRLogo *this)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  cRLogo *pcVar5;
  int iVar6;
  int iVar7;
  char *pcVar8;
  char *pcVar9;

  iVar1 = DAT_00068e94;
  iVar7 = DAT_00068e90 + 0x68d78;
  iVar3 = **(int **)(iVar7 + DAT_00068e94);
  *(undefined4 *)(*(int *)(iVar7 + DAT_00068e98) + 0x1c) = *(undefined4 *)(this + 0x10);
  if (*(char *)(iVar3 + 0x2c1) == '\0') {
    *(undefined4 *)(iVar3 + 0x15c) = 3;
  }
  else {
    *(undefined4 *)(iVar3 + 0x15c) = 0x14;
  }
  if (*(int *)(this + 0x2101c) < 1) {
    return;
  }
  pcVar5 = this + 0x21024;
  pcVar9 = (char *)(iVar7 + DAT_00068e9c);
  iVar6 = 0;
  pcVar8 = (char *)(iVar7 + DAT_00068ea0);
  do {
    uVar4 = *(uint *)pcVar5;
    if ((uVar4 & 0x200) == 0) {
      RShellError(pcVar8);
      if (*(int *)(this + 0x2101c) <= iVar6 + 1) {
        return;
      }
    }
    else if ((uVar4 & 0x40) == 0) {
      iVar2 = *(int *)(pcVar5 + 8);
      *(uint *)pcVar5 = uVar4 & 0xfffffdff;
      if (iVar2 != 0) {
        *(undefined4 *)(iVar2 + 8) = *(undefined4 *)(pcVar5 + 4);
      }
      if (*(int *)(pcVar5 + 4) == 0) {
        *(int *)(iVar3 + 0x35c) = iVar2;
      }
      else {
        *(int *)(*(int *)(pcVar5 + 4) + 0xc) = iVar2;
      }
      *(undefined4 *)(pcVar5 + 8) = *(undefined4 *)(iVar3 + 0x360);
      *(cRLogo **)(iVar3 + 0x360) =
           this + (int)("Java_com_sandlotgames_snailmail_MyOpenFeintDelegate_JNIOFOInit" +
                       iVar6 * 0x84 + 0x3b);
      if (*(int *)(this + 0x2101c) <= iVar6 + 1) {
        return;
      }
    }
    else {
      RShellError(pcVar9);
      if (*(int *)(this + 0x2101c) <= iVar6 + 1) {
        return;
      }
    }
    iVar6 = iVar6 + 1;
    pcVar5 = pcVar5 + 0x84;
    iVar3 = **(int **)(iVar7 + iVar1);
  } while( true );
}
