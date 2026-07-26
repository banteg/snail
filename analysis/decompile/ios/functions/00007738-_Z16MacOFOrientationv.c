/*
 * mangled: _Z16MacOFOrientationv
 * demangled: MacOFOrientation()
 * address: 00007738
 * size: 180
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* MacOFOrientation() */

void MacOFOrientation(void)

{
  int iVar1;

  iVar1 = (int)*(float *)(_Game + 0x3c);
  if (iVar1 == 0x5a) {
    OpenFeint::setDashboardOrientation_((ID)&objc::class_t::OpenFeint,"setDashboardOrientation:",4);
    return;
  }
  if (iVar1 < 0x5b) {
    if (iVar1 != 0) {
      return;
    }
    OpenFeint::setDashboardOrientation_((ID)&objc::class_t::OpenFeint,"setDashboardOrientation:",1);
    return;
  }
  if (iVar1 == 0xb4) {
    OpenFeint::setDashboardOrientation_((ID)&objc::class_t::OpenFeint,"setDashboardOrientation:",2);
    return;
  }
  if (iVar1 != 0x10e) {
    return;
  }
  OpenFeint::setDashboardOrientation_((ID)&objc::class_t::OpenFeint,"setDashboardOrientation:",3);
  return;
}
