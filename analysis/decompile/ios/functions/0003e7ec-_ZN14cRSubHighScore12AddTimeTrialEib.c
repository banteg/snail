/*
 * mangled: _ZN14cRSubHighScore12AddTimeTrialEib
 * demangled: cRSubHighScore::AddTimeTrial(int, bool)
 * address: 0003e7ec
 * size: 184
 */

/* cRSubHighScore::AddTimeTrial(int, bool) */

void __thiscall cRSubHighScore::AddTimeTrial(cRSubHighScore *this,int param_1,bool param_2)

{
  *(undefined4 *)(this + 0x12dc) = 2;
  *(undefined4 *)(this + 0x12e4) = 0;
  *(int *)(this + 0x12e0) = param_1;
  if (param_2) {
    MacOFAddTimeTrial(*(int *)(this + 0x12ac),*(int *)(this + 0x12b0),*(int *)(this + 0x12b4),
                      *(int *)(this + 0x12c8));
  }
  else {
    *(undefined4 *)(this + 0x12a8) = 0;
  }
  if (((*(uint *)PTR__gCheat_001b61dc & 2) == 0) && (param_2)) {
    if ((*(float *)(this + 0x12a8) < *(float *)(this + (param_1 + 0x16) * 0x38 + 0xc)) ||
       (*(float *)(this + (param_1 + 0x16) * 0x38 + 0xc) == 0.0)) {
      MiniSave(this,param_1 + 0x16);
      return;
    }
  }
  return;
}
