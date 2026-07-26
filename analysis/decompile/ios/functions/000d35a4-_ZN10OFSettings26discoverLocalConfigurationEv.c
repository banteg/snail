/*
 * mangled: _ZN10OFSettings26discoverLocalConfigurationEv
 * demangled: OFSettings::discoverLocalConfiguration()
 * address: 000d35a4
 * size: 600
 */

/* OFSettings::discoverLocalConfiguration() */

void __thiscall OFSettings::discoverLocalConfiguration(OFSettings *this)

{
  ID IVar1;
  ID IVar2;
  ID self;

  IVar1 = NSBundle::mainBundle((ID)&_OBJC_CLASS___NSBundle,"mainBundle");
  IVar1 = NSBundle::infoDictionary(IVar1,"infoDictionary");
  IVar2 = NSBundle::valueForKey_(IVar1,"valueForKey:",&cf_CFBundleIdentifier);
  IVar1 = NSBundle::valueForKey_(IVar1,"valueForKey:",&cf_CFBundleVersion);
  self = *(ID *)(this + 0x10);
  if (IVar2 != self) {
    if (self != 0) {
      _objc_msgSend(self,"release");
    }
    *(ID *)(this + 0x10) = IVar2;
    if (IVar2 != 0) {
      NSBundle::retain(IVar2,"retain");
    }
  }
  IVar2 = *(ID *)(this + 0x14);
  if (IVar1 != IVar2) {
    if (IVar2 != 0) {
      _objc_msgSend(IVar2,"release");
    }
    *(ID *)(this + 0x14) = IVar1;
    if (IVar1 != 0) {
      NSBundle::retain(IVar1,"retain");
    }
  }
  IVar1 = NSLocale::currentLocale((ID)&_OBJC_CLASS___NSLocale,"currentLocale");
  IVar1 = NSLocale::localeIdentifier(IVar1,"localeIdentifier");
  IVar2 = *(ID *)(this + 0x18);
  if (IVar1 != IVar2) {
    if (IVar2 != 0) {
      _objc_msgSend(IVar2,"release");
    }
    *(ID *)(this + 0x18) = IVar1;
    if (IVar1 != 0) {
      NSLocale::retain(IVar1,"retain");
    }
  }
  IVar1 = UIDevice::currentDevice((ID)&_OBJC_CLASS___UIDevice,"currentDevice");
  IVar1 = UIDevice::model(IVar1,"model");
  IVar2 = *(ID *)(this + 0x1c);
  if (IVar1 != IVar2) {
    if (IVar2 != 0) {
      _objc_msgSend(IVar2,"release");
    }
    *(ID *)(this + 0x1c) = IVar1;
    if (IVar1 != 0) {
      UIDevice::retain(IVar1,"retain");
    }
  }
  IVar1 = UIDevice::currentDevice((ID)&_OBJC_CLASS___UIDevice,"currentDevice");
  IVar1 = UIDevice::systemName(IVar1,"systemName");
  IVar2 = *(ID *)(this + 0x20);
  if (IVar1 != IVar2) {
    if (IVar2 != 0) {
      _objc_msgSend(IVar2,"release");
    }
    *(ID *)(this + 0x20) = IVar1;
    if (IVar1 != 0) {
      UIDevice::retain(IVar1,"retain");
    }
  }
  IVar1 = UIDevice::currentDevice((ID)&_OBJC_CLASS___UIDevice,"currentDevice");
  IVar1 = UIDevice::systemVersion(IVar1,"systemVersion");
  IVar2 = *(ID *)(this + 0x24);
  if (IVar1 != IVar2) {
    if (IVar2 != 0) {
      _objc_msgSend(IVar2,"release");
    }
    *(ID *)(this + 0x24) = IVar1;
    if (IVar1 != 0) {
      UIDevice::retain(IVar1,"retain");
    }
  }
  return;
}
