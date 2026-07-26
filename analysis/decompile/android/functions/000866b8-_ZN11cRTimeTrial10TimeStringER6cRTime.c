/*
 * mangled: _ZN11cRTimeTrial10TimeStringER6cRTime
 * demangled: cRTimeTrial::TimeString(cRTime&)
 * address: 000866b8
 * size: 140
 */

/* cRTimeTrial::TimeString(cRTime&) */

undefined4 __thiscall cRTimeTrial::TimeString(cRTimeTrial *this,cRTime *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  char *__s;

  iVar1 = DAT_00086748;
  iVar4 = DAT_00086744 + 0x866d8;
  if (*(float *)param_1 == 0.0) {
    puVar3 = *(undefined4 **)(iVar4 + DAT_00086748);
    uVar2 = ((undefined4 *)(iVar4 + DAT_00086754))[1];
    *puVar3 = *(undefined4 *)(iVar4 + DAT_00086754);
    puVar3[1] = uVar2;
  }
  else {
    __s = *(char **)(iVar4 + DAT_00086748);
    sprintf(__s,(char *)(iVar4 + DAT_0008674c),*(undefined4 *)(param_1 + 4),
            *(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0x10));
    sprintf(__s,(char *)(iVar4 + DAT_00086750),*(undefined4 *)(param_1 + 4),
            *(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0xc));
  }
  return *(undefined4 *)(iVar4 + iVar1);
}
