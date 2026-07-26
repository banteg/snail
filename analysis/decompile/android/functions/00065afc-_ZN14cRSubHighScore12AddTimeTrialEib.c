/*
 * mangled: _ZN14cRSubHighScore12AddTimeTrialEib
 * demangled: cRSubHighScore::AddTimeTrial(int, bool)
 * address: 00065afc
 * size: 228
 */

/* cRSubHighScore::AddTimeTrial(int, bool) */

void __thiscall cRSubHighScore::AddTimeTrial(cRSubHighScore *this,int param_1,bool param_2)

{
  *(int *)(this + 0x12e0) = param_1;
  *(undefined4 *)(this + 0x12dc) = 2;
  *(undefined4 *)(this + 0x12e4) = 0;
  if (param_2) {
    OFAddTimeTrial(*(int *)(this + 0x12ac),*(int *)(this + 0x12b0),*(int *)(this + 0x12b4),
                   *(int *)(this + 0x12c8));
    if ((gCheat & 2) != 0) {
      return;
    }
  }
  else {
    *(undefined4 *)(this + 0x12a8) = 0;
    if ((gCheat & 2) != 0) {
      return;
    }
  }
  if (!param_2) {
    return;
  }
  if ((*(float *)(this + (param_1 + 0x16) * 0x38 + 0xc) <= *(float *)(this + 0x12a8)) &&
     (*(float *)(this + (param_1 + 0x16) * 0x38 + 0xc) != 0.0)) {
    return;
  }
  MiniSave(this,param_1 + 0x16);
  return;
}
