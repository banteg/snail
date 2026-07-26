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
  uint uVar3;
  cRLogo *pcVar4;
  int iVar5;

  iVar2 = Game;
  gConfig._28_4_ = *(undefined4 *)(this + 0x10);
  if (*(char *)(Game + 0x2c1) == '\0') {
    *(undefined4 *)(Game + 0x15c) = 3;
  }
  else {
    *(undefined4 *)(Game + 0x15c) = 0x14;
  }
  if (*(int *)(this + 0x2101c) < 1) {
    return;
  }
  pcVar4 = this + 0x21024;
  iVar5 = 0;
  do {
    uVar3 = *(uint *)pcVar4;
    if ((uVar3 & 0x200) == 0) {
      RShellError("List remove");
      if (*(int *)(this + 0x2101c) <= iVar5 + 1) {
        return;
      }
    }
    else if ((uVar3 & 0x40) == 0) {
      iVar1 = *(int *)(pcVar4 + 8);
      *(uint *)pcVar4 = uVar3 & 0xfffffdff;
      if (iVar1 != 0) {
        *(undefined4 *)(iVar1 + 8) = *(undefined4 *)(pcVar4 + 4);
      }
      if (*(int *)(pcVar4 + 4) == 0) {
        *(int *)(iVar2 + 0x35c) = iVar1;
      }
      else {
        *(int *)(*(int *)(pcVar4 + 4) + 0xc) = iVar1;
      }
      *(undefined4 *)(pcVar4 + 8) = *(undefined4 *)(iVar2 + 0x360);
      *(cRLogo **)(iVar2 + 0x360) =
           this + (int)("Java_com_sandlotgames_snailmail_MyOpenFeintDelegate_JNIOFOInit" +
                       iVar5 * 0x84 + 0x3b);
      if (*(int *)(this + 0x2101c) <= iVar5 + 1) {
        return;
      }
    }
    else {
      RShellError("List remove NEXTBOD");
      if (*(int *)(this + 0x2101c) <= iVar5 + 1) {
        return;
      }
    }
    iVar5 = iVar5 + 1;
    pcVar4 = pcVar4 + 0x84;
    iVar2 = Game;
  } while( true );
}
