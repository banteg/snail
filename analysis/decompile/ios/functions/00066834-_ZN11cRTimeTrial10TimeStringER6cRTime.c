/*
 * mangled: _ZN11cRTimeTrial10TimeStringER6cRTime
 * demangled: cRTimeTrial::TimeString(cRTime&)
 * address: 00066834
 * size: 112
 */

/* cRTimeTrial::TimeString(cRTime&) */

undefined * __thiscall cRTimeTrial::TimeString(cRTimeTrial *this,cRTime *param_1)

{
  if (*(float *)param_1 == 0.0) {
    _memcpy(&_gTimeTrialString,"-:--:--",8);
  }
  else {
    _sprintf(&_gTimeTrialString,"%1i:%02i:%03i",*(undefined4 *)(param_1 + 4),
             *(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0x10));
    _sprintf(&_gTimeTrialString,"%1i:%02i:%02i",*(undefined4 *)(param_1 + 4),
             *(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0xc));
  }
  return &_gTimeTrialString;
}
