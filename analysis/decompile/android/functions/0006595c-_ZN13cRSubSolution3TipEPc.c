/*
 * mangled: _ZN13cRSubSolution3TipEPc
 * demangled: cRSubSolution::Tip(char*)
 * address: 0006595c
 * size: 232
 */

/* cRSubSolution::Tip(char*) */

void __thiscall cRSubSolution::Tip(cRSubSolution *this,char *param_1)

{
  char local_41c [1024];
  int local_1c;

  local_41c[0] = '\0';
  local_1c = __stack_chk_guard;
  if (*(int *)(this + 0x2c) == 0) {
    sprintf(local_41c,"%s>Arcade %i>Score:%i>Speed:%i%%>Player:%s",param_1,*(int *)(this + 0x28) + 1
            ,*(undefined4 *)(this + 4),*(undefined4 *)(this + 0x4c),this + 0x54);
  }
  else if (*(int *)(this + 0x2c) == 1) {
    sprintf(local_41c,"%s>Warp>Score:%i>Warp Speed:%i%%>Player:%s",param_1,*(undefined4 *)(this + 4)
            ,(int)*(float *)(this + 0x20),this + 0x54);
  }
  Rstrcpy(param_1,local_41c);
  if (local_1c == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail();
}
