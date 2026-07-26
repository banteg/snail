/*
 * mangled: _ZN17SoundEngineEffect12PlaybackProcEPv
 * demangled: SoundEngineEffect::PlaybackProc(void*)
 * address: 000737f0
 * size: 204
 */

/* SoundEngineEffect::PlaybackProc(void*) */

void SoundEngineEffect::PlaybackProc(void *param_1)

{
  int iVar1;
  code *UNRECOVERED_JUMPTABLE;
  int local_14;
  int local_10;

  _alSourcePlay(*(undefined4 *)param_1);
  iVar1 = _alGetError();
  if (iVar1 == 0) {
    if (*(int *)((int)param_1 + 4) != 0) {
      local_10 = 0;
      do {
        _alGetSourcei(*(undefined4 *)param_1,0x1016,&local_10);
        iVar1 = _alGetError();
        if (iVar1 != 0) {
          _printf("%s: %x\n","Error getting processed buffer number");
          goto LAB_00073880;
        }
      } while (local_10 < 1);
      local_14 = iVar1;
      _alSourceUnqueueBuffers(*(undefined4 *)param_1,1,&local_14);
      iVar1 = _alGetError();
      if (iVar1 != 0) {
        _printf("%s: %x\n","Error unqueueing buffers from source");
        goto LAB_00073880;
      }
    }
    _alSourcei(*(undefined4 *)param_1,0x1007,1);
    _alGetError();
  }
  else {
    _printf("%s: %x\n","Error starting effect playback");
  }
LAB_00073880:
                    /* WARNING: Could not recover jumptable at 0x00073888. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(0);
  return;
}
