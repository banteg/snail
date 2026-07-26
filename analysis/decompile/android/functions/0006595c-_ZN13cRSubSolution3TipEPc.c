/*
 * mangled: _ZN13cRSubSolution3TipEPc
 * demangled: cRSubSolution::Tip(char*)
 * address: 0006595c
 * size: 232
 */

/* cRSubSolution::Tip(char*) */

void __thiscall cRSubSolution::Tip(cRSubSolution *this,char *param_1)

{
  int iVar1;
  int iVar2;
  char local_41c [1024];
  int local_1c;

  iVar1 = DAT_00065a48;
  iVar2 = DAT_00065a44 + 0x65978;
  local_41c[0] = '\0';
  local_1c = **(int **)(iVar2 + DAT_00065a48);
  if (*(int *)(this + 0x2c) == 0) {
    sprintf(local_41c,(char *)(iVar2 + DAT_00065a4c),param_1,*(int *)(this + 0x28) + 1,
            *(undefined4 *)(this + 4),*(undefined4 *)(this + 0x4c),this + 0x54);
  }
  else if (*(int *)(this + 0x2c) == 1) {
    sprintf(local_41c,(char *)(iVar2 + DAT_00065a50),param_1,*(undefined4 *)(this + 4),
            (int)*(float *)(this + 0x20),this + 0x54);
  }
  Rstrcpy(param_1,local_41c);
  if (local_1c == **(int **)(iVar2 + iVar1)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}
