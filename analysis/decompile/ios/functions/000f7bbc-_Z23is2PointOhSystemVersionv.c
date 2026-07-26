/*
 * mangled: _Z23is2PointOhSystemVersionv
 * demangled: is2PointOhSystemVersion()
 * address: 000f7bbc
 * size: 144
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* is2PointOhSystemVersion() */

undefined1 is2PointOhSystemVersion(void)

{
  ID IVar1;

  if (is2PointOhSystemVersion()::hasDoneTheWork == '\0') {
    is2PointOhSystemVersion()::hasDoneTheWork = '\x01';
    IVar1 = UIDevice::currentDevice((ID)&_OBJC_CLASS___UIDevice,"currentDevice");
    IVar1 = UIDevice::systemVersion(IVar1,"systemVersion");
    IVar1 = UIDevice::componentsSeparatedByString_(IVar1,"componentsSeparatedByString:",&cf__);
    IVar1 = UIDevice::objectAtIndex_(IVar1,"objectAtIndex:",0);
    IVar1 = UIDevice::isEqualToString_(IVar1,"isEqualToString:",&cf_2);
    is2PointOhSystemVersion()::is2PointOh = (IVar1 & 0xff) != 0;
  }
  return is2PointOhSystemVersion()::is2PointOh;
}
