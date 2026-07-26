/*
 * mangled: _ZN12OpenALThread5EntryEPS_
 * demangled: OpenALThread::Entry(OpenALThread*)
 * address: 00073424
 * size: 220
 */

/* OpenALThread::Entry(OpenALThread*) */

undefined4 OpenALThread::Entry(OpenALThread *param_1)

{
  OpenALThread OVar1;
  pthread_t p_Var2;
  mach_port_t mVar3;
  kern_return_t kVar4;
  undefined4 uVar5;
  integer_t local_18;
  int local_14;

  OVar1 = param_1[0x14];
  param_1[0x14] = OVar1;
  p_Var2 = *(pthread_t *)param_1;
  if (p_Var2 != (pthread_t)0x0) {
    if (OVar1 != (OpenALThread)0x0) {
      local_18 = 0;
      mVar3 = _pthread_mach_thread_np(p_Var2);
      kVar4 = _thread_policy_set(mVar3,1,&local_18,1);
      if (kVar4 != 0) {
        _printf("OpenALThread::SetPriority: failed to set the fixed-priority policy");
        goto LAB_000734a4;
      }
      p_Var2 = *(pthread_t *)param_1;
    }
    local_14 = *(int *)(param_1 + 0x10) - *(int *)(param_1 + 4);
    mVar3 = _pthread_mach_thread_np(p_Var2);
    kVar4 = _thread_policy_set(mVar3,3,&local_14,1);
    if (kVar4 != 0) {
      _printf("OpenALThread::SetPriority: failed to set the precedence policy");
    }
  }
LAB_000734a4:
  if (*(code **)(param_1 + 8) == (code *)0x0) {
    uVar5 = 0;
  }
  else {
    uVar5 = (**(code **)(param_1 + 8))(*(undefined4 *)(param_1 + 0xc));
  }
  *(undefined4 *)param_1 = 0;
  if (param_1[0x15] != (OpenALThread)0x0) {
    operator_delete(param_1);
  }
  return uVar5;
}
