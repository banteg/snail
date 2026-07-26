/*
 * mangled: _Z18getHardwareVersionv
 * demangled: getHardwareVersion()
 * address: 000f7c74
 * size: 132
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* getHardwareVersion() */

ID getHardwareVersion(void)

{
  void *pvVar1;
  ID IVar2;
  size_t local_18;

  local_18 = 0;
  _sysctlbyname("hw.machine",(void *)0x0,&local_18,(void *)0x0,0);
  pvVar1 = _malloc(local_18);
  _sysctlbyname("hw.machine",pvVar1,&local_18,(void *)0x0,0);
  IVar2 = NSString::stringWithUTF8String_
                    ((ID)&_OBJC_CLASS___NSString,"stringWithUTF8String:",pvVar1);
  _free(pvVar1);
  return IVar2;
}
