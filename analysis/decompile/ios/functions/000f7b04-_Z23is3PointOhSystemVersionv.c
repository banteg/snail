/*
 * mangled: _Z23is3PointOhSystemVersionv
 * demangled: is3PointOhSystemVersion()
 * address: 000f7b04
 * size: 144
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* is3PointOhSystemVersion() */

undefined1 is3PointOhSystemVersion(void)

{
  ID IVar1;

  if (is3PointOhSystemVersion()::hasDoneTheWork == '\0') {
    is3PointOhSystemVersion()::hasDoneTheWork = '\x01';
    IVar1 = UIDevice::currentDevice((ID)&_OBJC_CLASS___UIDevice,"currentDevice");
    IVar1 = UIDevice::systemVersion(IVar1,"systemVersion");
    IVar1 = UIDevice::componentsSeparatedByString_(IVar1,"componentsSeparatedByString:",&cf__);
    IVar1 = UIDevice::objectAtIndex_(IVar1,"objectAtIndex:",0);
    IVar1 = UIDevice::isEqualToString_(IVar1,"isEqualToString:",&cf_3);
    is3PointOhSystemVersion()::is3PointOh = (IVar1 & 0xff) != 0;
  }
  return is3PointOhSystemVersion()::is3PointOh;
}
