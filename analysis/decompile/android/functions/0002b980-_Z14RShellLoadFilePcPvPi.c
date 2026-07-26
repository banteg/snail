/*
 * mangled: _Z14RShellLoadFilePcPvPi
 * demangled: RShellLoadFile(char*, void*, int*)
 * address: 0002b980
 * size: 336
 */

/* RShellLoadFile(char*, void*, int*) */

void RShellLoadFile(char *param_1,void *param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  int local_a8;
  char acStack_a4 [128];
  int local_24;

  local_24 = __stack_chk_guard;
  cRLoadingBar::Signal((cRLoadingBar *)&gLoadingBar);
  if (gDat == 0) {
LAB_0002babc:
    wprintf("No gDat\n");
  }
  else {
    iVar1 = RShellDatFind(param_1);
    if (iVar1 != 0) {
      if (param_3 != (int *)0x0) {
        *param_3 = *(int *)(iVar1 + 8);
      }
      if (param_2 == (void *)0xffffffff) {
        param_2 = *(void **)(iVar1 + 4);
      }
      else {
        if (param_2 == (void *)0x0) {
          param_2 = (void *)RShellMemoryMalloc(*(int *)(iVar1 + 8),param_1);
          iVar2 = *(int *)(iVar1 + 0x10);
        }
        else {
          iVar2 = *(int *)(iVar1 + 0x10);
        }
        PfmLoadFileDat(param_2,*(int *)(iVar1 + 4),*(int *)(iVar1 + 8),*(int *)(iVar1 + 0xc),iVar2,
                       *(ushort *)(iVar1 + 0x14),*(ushort *)(iVar1 + 0x16));
      }
      goto LAB_0002ba20;
    }
    if (gDat == 0) goto LAB_0002babc;
    wprintf("FileMissing from gDat %s\n",param_1);
  }
  RShellConvertFileName(acStack_a4,param_1);
  param_2 = (void *)PfmLoadFile(acStack_a4,param_2,&local_a8);
  wprintf("Loaded Real File %s (%i)",acStack_a4,local_a8);
  if (param_3 != (int *)0x0) {
    *param_3 = local_a8;
  }
LAB_0002ba20:
  if (local_24 == __stack_chk_guard) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __stack_chk_fail(param_2);
}
