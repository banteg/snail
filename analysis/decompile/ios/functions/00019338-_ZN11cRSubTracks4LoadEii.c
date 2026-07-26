/*
 * mangled: _ZN11cRSubTracks4LoadEii
 * demangled: cRSubTracks::Load(int, int)
 * address: 00019338
 * size: 340
 */

/* cRSubTracks::Load(int, int) */

void __thiscall cRSubTracks::Load(cRSubTracks *this,int param_1,int param_2)

{
  int iVar1;
  char local_8c [4];
  char acStack_88 [4];
  char acStack_84 [4];
  uint local_80;
  ushort local_7c;
  undefined1 local_7a;

  switch(param_1) {
  case 0:
    iVar1 = *(int *)(&DAT_00364944 + *(int *)PTR__Game_001b60b8);
    if (*(int *)(&DAT_00364960 + iVar1 * 0x8e6c + *(int *)PTR__Game_001b60b8) + 1 < param_2) {
      if (*(int *)(&DAT_00364960 + iVar1 * 0x8e6c + *(int *)PTR__Game_001b60b8) + 2 == param_2) {
        local_8c[0] = 'A';
        local_8c[1] = 'r';
        local_8c[2] = 'c';
        local_8c[3] = 'a';
        acStack_88[0] = 'd';
        acStack_88[1] = 'e';
        acStack_88[2] = 'E';
        acStack_88[3] = 'x';
        acStack_84[0] = 't';
        acStack_84[1] = 'r';
        acStack_84[2] = 'a';
        acStack_84[3] = '0';
        local_80._0_1_ = '0';
        local_80._1_1_ = '0';
        local_80._2_1_ = '.';
        local_80._3_1_ = 't';
        local_7c = 0x7478;
        local_7a = 0;
      }
      break;
    }
    if (iVar1 != 0) {
      if (iVar1 == 1) {
        _sprintf(local_8c,"ArcadePro%03i.txt");
      }
      break;
    }
    goto LAB_00019468;
  case 1:
    local_8c[0] = 'C';
    local_8c[1] = 'h';
    local_8c[2] = 'a';
    local_8c[3] = 'l';
    acStack_88[0] = 'l';
    acStack_88[1] = 'e';
    acStack_88[2] = 'n';
    acStack_88[3] = 'g';
    acStack_84[0] = 'e';
    acStack_84[1] = '0';
    acStack_84[2] = '0';
    acStack_84[3] = '0';
    local_80._0_1_ = '.';
    local_80._1_1_ = 't';
    local_80._2_1_ = 'x';
    local_80._3_1_ = 't';
    local_7c = local_7c & 0xff00;
    break;
  case 2:
  case 3:
    local_8c[0] = 'A';
    local_8c[1] = 'r';
    local_8c[2] = 'c';
    local_8c[3] = 'a';
    acStack_88[0] = 'd';
    acStack_88[1] = 'e';
    acStack_88[2] = '0';
    acStack_88[3] = '0';
    acStack_84[0] = '0';
    acStack_84[1] = '.';
    acStack_84[2] = 't';
    acStack_84[3] = 'x';
    local_80 = CONCAT22(local_80._2_2_,0x74);
    break;
  case 4:
    if (*(int *)(&DAT_00364960 +
                *(int *)(&DAT_00364944 + *(int *)PTR__Game_001b60b8) * 0x8e6c +
                *(int *)PTR__Game_001b60b8) + 1 < param_2) {
      _sprintf(local_8c,"TimeTrialExtra%03i.txt",
               param_2 - *(int *)(&DAT_00364960 +
                                 *(int *)(&DAT_00364944 + *(int *)PTR__Game_001b60b8) * 0x8e6c +
                                 *(int *)PTR__Game_001b60b8));
      break;
    }
LAB_00019468:
    _sprintf(local_8c,"Arcade%03i.txt");
    break;
  case 7:
    local_8c[0] = 'T';
    local_8c[1] = 'u';
    local_8c[2] = 't';
    local_8c[3] = 'o';
    acStack_88[0] = 'r';
    acStack_88[1] = 'i';
    acStack_88[2] = 'a';
    acStack_88[3] = 'l';
    acStack_84[0] = '.';
    acStack_84[1] = 't';
    acStack_84[2] = 'x';
    acStack_84[3] = 't';
    local_80 = local_80 & 0xffffff00;
  }
  Init(this,local_8c);
  return;
}
