/*
 * mangled: _ZN17SoundEngineEffect5StartEv
 * demangled: SoundEngineEffect::Start()
 * address: 00072f14
 * size: 1188
 */

/* SoundEngineEffect::Start() */

pthread_t __thiscall SoundEngineEffect::Start(SoundEngineEffect *this)

{
  mach_port_t mVar1;
  pthread_t local_13c [2];
  SoundEngineEffect *local_134;
  pthread_t local_130;
  pthread_t local_12c;
  pthread_t local_128;
  pthread_t local_124;
  SoundEngineEffect *local_120;
  int *local_11c;
  pthread_t local_118;
  void *local_114;
  pthread_t local_110;
  pthread_t local_10c;
  pthread_t *local_108;
  pthread_t local_104;
  pthread_t local_100;
  pthread_t local_fc;
  undefined1 auStack_f8 [4];
  undefined4 local_f4;
  undefined *local_e0;
  undefined *local_dc;
  undefined1 *local_d8;
  undefined1 *local_d4;
  undefined1 *local_d0;
  integer_t iStack_c4;
  int local_c0;
  integer_t iStack_b0;
  int local_ac;
  integer_t iStack_9c;
  int local_98;
  pthread_attr_t pStack_8c;

  local_d8 = &stack0xfffffff8;
  local_d0 = (undefined1 *)local_13c;
  local_e0 = PTR_001b615c;
  local_dc = &::GCC_except_table0;
  local_d4 = &LAB_000733b8;
  local_134 = this;
  __Unwind_SjLj_Register(auStack_f8);
  local_f4 = 0xffffffff;
  _alSourceStop(*(undefined4 *)local_134);
  local_130 = (pthread_t)_alGetError();
  if (local_130 != (pthread_t)0x0) {
    _printf("%s: %x\n","Error stopping source",local_130);
    local_124 = local_130;
    goto LAB_000730d8;
  }
  if (local_134[0x38] == (SoundEngineEffect)0x0) {
    local_f4 = 0xffffffff;
    _alSourcePlay(*(undefined4 *)local_134);
    local_124 = (pthread_t)_alGetError();
    goto LAB_000730d8;
  }
  local_f4 = 0xffffffff;
  local_11c = operator_new(0x18);
  local_120 = local_134;
  *local_11c = (int)local_130;
  local_f4 = 1;
  local_118 = _pthread_self();
  if (local_118 == (pthread_t)0x0) {
LAB_00073000:
    local_c0 = 0;
  }
  else {
    pStack_8c.__opaque[0x24] = '\n';
    pStack_8c.__opaque[0x25] = '\0';
    pStack_8c.__opaque[0x26] = '\0';
    pStack_8c.__opaque[0x27] = '\0';
    mVar1 = _pthread_mach_thread_np(local_118);
    _thread_info(mVar1,3,&pStack_8c.__sig,(mach_msg_type_number_t *)(pStack_8c.__opaque + 0x24));
    if (pStack_8c.__opaque._16_4_ == 2) {
      pStack_8c.__opaque[0x24] = '\x05';
      pStack_8c.__opaque[0x25] = '\0';
      pStack_8c.__opaque[0x26] = '\0';
      pStack_8c.__opaque[0x27] = '\0';
      local_f4 = 1;
      mVar1 = _pthread_mach_thread_np(local_118);
      _thread_info(mVar1,0xb,&iStack_b0,(mach_msg_type_number_t *)(pStack_8c.__opaque + 0x24));
      local_c0 = local_ac;
    }
    else if (pStack_8c.__opaque._16_4_ == 4) {
      pStack_8c.__opaque[0x24] = pStack_8c.__opaque[0x10];
      pStack_8c.__opaque[0x25] = pStack_8c.__opaque[0x11];
      pStack_8c.__opaque[0x26] = pStack_8c.__opaque[0x12];
      pStack_8c.__opaque[0x27] = pStack_8c.__opaque[0x13];
      local_f4 = 1;
      mVar1 = _pthread_mach_thread_np(local_118);
      _thread_info(mVar1,0xc,&iStack_9c,(mach_msg_type_number_t *)(pStack_8c.__opaque + 0x24));
      local_c0 = local_98;
    }
    else {
      if (pStack_8c.__opaque._16_4_ != 1) goto LAB_00073000;
      pStack_8c.__opaque[0x24] = '\x05';
      pStack_8c.__opaque[0x25] = '\0';
      pStack_8c.__opaque[0x26] = '\0';
      pStack_8c.__opaque[0x27] = '\0';
      local_f4 = 1;
      mVar1 = _pthread_mach_thread_np(local_118);
      _thread_info(mVar1,10,&iStack_c4,(mach_msg_type_number_t *)(pStack_8c.__opaque + 0x24));
    }
  }
  local_11c[1] = local_c0;
  local_11c[2] = DAT_001edd40;
  *(undefined1 *)(local_11c + 5) = 0;
  local_11c[3] = (int)local_120;
  local_11c[4] = 0x1f;
  *(undefined1 *)((int)local_11c + 0x15) = 1;
  *(int **)(local_134 + 0x3c) = local_11c;
  *(undefined4 *)(local_134 + 0x40) = 0;
  pStack_8c.__opaque[0x24] = '\0';
  pStack_8c.__opaque[0x25] = '\0';
  pStack_8c.__opaque[0x26] = '\0';
  pStack_8c.__opaque[0x27] = '\0';
  local_114 = _malloc(0);
  local_f4 = 0xffffffff;
  _alGetSourcei(*(undefined4 *)local_134,0x1015,pStack_8c.__opaque + 0x24);
  local_10c = (pthread_t)_alGetError();
  if (local_10c == (pthread_t)0x0) {
    local_f4 = 0xffffffff;
    _alSourceUnqueueBuffers(*(undefined4 *)local_134,pStack_8c.__opaque._36_4_,local_114);
    local_110 = (pthread_t)_alGetError();
    if (local_110 == (pthread_t)0x0) {
      _free(local_114);
      if (*(int *)(local_134 + 4) != 0) {
        local_f4 = 0xffffffff;
        _alSourceQueueBuffers(*(undefined4 *)local_134,1,local_134 + 4);
        local_12c = (pthread_t)_alGetError();
        if (local_12c != (pthread_t)0x0) {
          _printf("%s: %x\n","Error queueing buffers for attack",local_12c);
          local_124 = local_12c;
          goto LAB_000730d8;
        }
        local_f4 = 0xffffffff;
        _alSourcei(*(undefined4 *)local_134,0x1007,0);
        _alGetError();
      }
      local_f4 = 0xffffffff;
      _alSourceQueueBuffers(*(undefined4 *)local_134,1,local_134 + 8);
      local_128 = (pthread_t)_alGetError();
      if (local_128 == (pthread_t)0x0) {
        local_108 = *(pthread_t **)(local_134 + 0x3c);
        local_13c[0] = *local_108;
        if (local_13c[0] == (pthread_t)0x0) {
          local_f4 = 0xffffffff;
          local_fc = (pthread_t)_pthread_attr_init(&pStack_8c);
          if (local_fc == (pthread_t)0x0) {
            local_f4 = 0xffffffff;
            local_100 = (pthread_t)_pthread_attr_setdetachstate(&pStack_8c,2);
            if (local_100 == (pthread_t)0x0) {
              local_f4 = 0xffffffff;
              local_104 = (pthread_t)_pthread_create(local_108,&pStack_8c,DAT_001edd44,local_108);
              if (local_104 == (pthread_t)0x0) {
                local_f4 = 0xffffffff;
                _pthread_attr_destroy(&pStack_8c);
                local_124 = local_104;
              }
              else {
                _printf("%s: %d\n","Error creating thread",local_104);
                local_124 = local_100;
              }
            }
            else {
              _printf("%s: %d\n","Error setting thread detach state",local_100);
              local_124 = local_fc;
            }
          }
          else {
            _printf("%s: %d\n","Error initializing thread",local_fc);
            local_124 = local_13c[0];
          }
        }
        else {
          local_f4 = 0xffffffff;
          _puts("OpenALThread::Start: can\'t start because the thread is already running");
          local_124 = local_128;
        }
      }
      else {
        _printf("%s: %x\n","Error queueing looping buffer",local_128);
        local_124 = local_128;
      }
      goto LAB_000730d8;
    }
    _printf("%s: %x\n","Error unqueueing buffers from source",local_110);
    local_124 = local_110;
  }
  else {
    local_f4 = 0xffffffff;
    _printf("%s: %x\n","Error getting OpenAL queued buffer size",local_10c);
    local_124 = local_10c;
  }
  _free(local_114);
  local_f4 = 0xffffffff;
  _printf("%s: %d\n","Error clearing buffers",local_124);
LAB_000730d8:
  __Unwind_SjLj_Unregister(auStack_f8);
  return local_124;
}
