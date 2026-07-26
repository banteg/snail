/*
 * mangled: _Z18MacAudioLoadSamplePc
 * demangled: MacAudioLoadSample(char*)
 * address: 00074e88
 * size: 176
 */

/* MacAudioLoadSample(char*) */

void MacAudioLoadSample(char *param_1)

{
  ID IVar1;
  ID IVar2;

  IVar1 = NSBundle::mainBundle((ID)&_OBJC_CLASS___NSBundle,"mainBundle");
  IVar2 = NSString::stringWithUTF8String_
                    ((ID)&_OBJC_CLASS___NSString,"stringWithUTF8String:",param_1);
  IVar1 = NSBundle::pathForResource_ofType_(IVar1,"pathForResource:ofType:",IVar2,&cf_wav);
  IVar1 = NSBundle::UTF8String(IVar1,"UTF8String");
  _SoundEngine_LoadEffect(IVar1,&_MacSample + _MacSampleCount * 0x84);
  _strcpy((char *)(_MacSampleCount * 0x84 + 0x4dc064),param_1);
  _MacSampleCount = _MacSampleCount + 1;
  return;
}
