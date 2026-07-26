/*
 * mangled: _ZN11cRSubTracks4LoadEii
 * demangled: cRSubTracks::Load(int, int)
 * address: 00074888
 * size: 488
 */

/* cRSubTracks::Load(int, int) */

void __thiscall cRSubTracks::Load(cRSubTracks *this,int param_1,int param_2)

{
  int iVar1;
  char local_9c [4];
  char acStack_98 [4];
  char acStack_94 [4];
  uint local_90;
  ushort local_8c;
  undefined1 local_8a;
  int local_1c;

  local_1c = __stack_chk_guard;
  switch(param_1) {
  case 0:
    iVar1 = *(int *)(gOFOData + Game + 0x1ebc);
    if (*(int *)(gOFOData + iVar1 * 0x8e6c + Game + 0x1ed8) + 1 < param_2) {
      if (*(int *)(gOFOData + iVar1 * 0x8e6c + Game + 0x1ed8) + 2 == param_2) {
        local_9c[0] = 'A';
        local_9c[1] = 'r';
        local_9c[2] = 'c';
        local_9c[3] = 'a';
        acStack_98[0] = 'd';
        acStack_98[1] = 'e';
        acStack_98[2] = 'E';
        acStack_98[3] = 'x';
        acStack_94[0] = 't';
        acStack_94[1] = 'r';
        acStack_94[2] = 'a';
        acStack_94[3] = '0';
        local_90._0_1_ = '0';
        local_90._1_1_ = '0';
        local_90._2_1_ = '.';
        local_90._3_1_ = 't';
        local_8c = 0x7478;
        local_8a = 0;
      }
      break;
    }
    if (iVar1 != 0) {
      if (iVar1 == 1) {
        sprintf(local_9c,"ArcadePro%03i.txt");
      }
      break;
    }
    goto LAB_00074a28;
  case 1:
    local_9c[0] = 'C';
    local_9c[1] = 'h';
    local_9c[2] = 'a';
    local_9c[3] = 'l';
    acStack_98[0] = 'l';
    acStack_98[1] = 'e';
    acStack_98[2] = 'n';
    acStack_98[3] = 'g';
    acStack_94[0] = 'e';
    acStack_94[1] = '0';
    acStack_94[2] = '0';
    acStack_94[3] = '0';
    local_90._0_1_ = '.';
    local_90._1_1_ = 't';
    local_90._2_1_ = 'x';
    local_90._3_1_ = 't';
    local_8c = local_8c & 0xff00;
    break;
  case 2:
    goto LAB_000749b4;
  case 3:
LAB_000749b4:
    local_9c[0] = 'A';
    local_9c[1] = 'r';
    local_9c[2] = 'c';
    local_9c[3] = 'a';
    acStack_98[0] = 'd';
    acStack_98[1] = 'e';
    acStack_98[2] = '0';
    acStack_98[3] = '0';
    acStack_94[0] = '0';
    acStack_94[1] = '.';
    acStack_94[2] = 't';
    acStack_94[3] = 'x';
    local_90 = CONCAT22(local_90._2_2_,0x74);
    break;
  case 4:
    if (*(int *)(gOFOData + *(int *)(gOFOData + Game + 0x1ebc) * 0x8e6c + Game + 0x1ed8) + 1 <
        param_2) {
      sprintf(local_9c,"TimeTrialExtra%03i.txt",
              param_2 - *(int *)(gOFOData +
                                *(int *)(gOFOData + Game + 0x1ebc) * 0x8e6c + Game + 0x1ed8));
      break;
    }
LAB_00074a28:
    sprintf(local_9c,"Arcade%03i.txt");
    break;
  case 5:
    break;
  case 6:
    break;
  case 7:
    local_9c[0] = 'T';
    local_9c[1] = 'u';
    local_9c[2] = 't';
    local_9c[3] = 'o';
    acStack_98[0] = 'r';
    acStack_98[1] = 'i';
    acStack_98[2] = 'a';
    acStack_98[3] = 'l';
    acStack_94[0] = '.';
    acStack_94[1] = 't';
    acStack_94[2] = 'x';
    acStack_94[3] = 't';
    local_90 = local_90 & 0xffffff00;
  }
  Init(this,local_9c);
  if (local_1c != __stack_chk_guard) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}
