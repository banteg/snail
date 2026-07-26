/*
 * mangled: _ZN11cRTimeTrial10TimeStringER6cRTime
 * demangled: cRTimeTrial::TimeString(cRTime&)
 * address: 000866b8
 * size: 140
 */

/* cRTimeTrial::TimeString(cRTime&) */

undefined4 * __thiscall cRTimeTrial::TimeString(cRTimeTrial *this,cRTime *param_1)

{
  if (*(float *)param_1 == 0.0) {
    gTimeTrialString = 0x2d2d3a2d;
    DAT_003887f0 = 0x2d2d3a;
  }
  else {
    sprintf((char *)&gTimeTrialString,"%1i:%02i:%03i",*(undefined4 *)(param_1 + 4),
            *(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0x10));
    sprintf((char *)&gTimeTrialString,"%1i:%02i:%02i",*(undefined4 *)(param_1 + 4),
            *(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0xc));
  }
  return &gTimeTrialString;
}
