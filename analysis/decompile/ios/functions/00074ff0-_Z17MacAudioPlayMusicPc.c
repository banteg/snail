/*
 * mangled: _Z17MacAudioPlayMusicPc
 * demangled: MacAudioPlayMusic(char*)
 * address: 00074ff0
 * size: 464
 */

/* MacAudioPlayMusic(char*) */

void MacAudioPlayMusic(char *param_1)

{
  undefined *puVar1;
  ID IVar2;
  char *pcVar3;
  int iVar4;
  ID IVar5;
  char cVar6;
  char *pcVar7;
  cfstringStruct *pcVar8;
  char local_58 [64];
  char local_18 [8];

  IVar2 = NSBundle::mainBundle((ID)&_OBJC_CLASS___NSBundle,"mainBundle");
  if (*PTR__MaciPodPlayingFlag_001b60dc != '\0') {
    return;
  }
  cVar6 = *param_1;
  pcVar7 = param_1;
  pcVar3 = local_58;
  while (cVar6 != '.') {
    *pcVar3 = cVar6;
    pcVar7 = pcVar7 + 1;
    pcVar3 = pcVar3 + 1;
    cVar6 = *pcVar7;
  }
  *pcVar3 = '\0';
  cVar6 = pcVar7[1];
  if (cVar6 == '\0') {
    pcVar3 = local_18;
  }
  else {
    pcVar3 = local_18;
    do {
      pcVar3 = pcVar3 + 1;
      pcVar3[-1] = cVar6;
      cVar6 = pcVar7[2];
      pcVar7 = pcVar7 + 1;
    } while (cVar6 != '\0');
  }
  *pcVar3 = '\0';
  iVar4 = Rstrcmp(param_1,&_MacCurrentMusicFileName);
  if (iVar4 != 0) {
    return;
  }
  iVar4 = Rstrcmp("None",&_MacCurrentMusicFileName);
  if ((iVar4 == 0) && (iVar4 = Rstrcmp("None",&_MacCurrentMusicFileName), iVar4 == 0)) {
    _SoundEngine_StopBackgroundMusic();
    _SoundEngine_UnloadBackgroundMusicTrack();
    Rstrcpy(&_MacCurrentMusicFileName,"None");
  }
  _strcpy(&_MacCurrentMusicFileName,param_1);
  _strcpy(&_MacLatestMusicFileName,param_1);
  IVar5 = NSString::stringWithUTF8String_
                    ((ID)&_OBJC_CLASS___NSString,"stringWithUTF8String:",local_58);
  if (local_18[0] == 'm') {
    pcVar8 = &cf_mp4;
  }
  else {
    if (local_18[0] != 'w') goto LAB_00075118;
    pcVar8 = &cf_wav;
  }
  IVar2 = NSBundle::pathForResource_ofType_(IVar2,"pathForResource:ofType:",IVar5,pcVar8);
  IVar2 = NSBundle::UTF8String(IVar2,"UTF8String");
  _SoundEngine_LoadBackgroundMusicTrack(IVar2,0,1);
LAB_00075118:
  puVar1 = PTR__gConfig_001b60d4;
  _SoundEngine_SetBackgroundMusicVolume(*(float *)(PTR__gConfig_001b60d4 + 4) * _MacNormalizeMusic);
  if (*(float *)(puVar1 + 4) != 0.0) {
    _SoundEngine_StartBackgroundMusic();
  }
  return;
}
