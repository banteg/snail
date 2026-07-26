/*
 * mangled: _Z16LoadFileDataInfoPKcRP17OpaqueAudioFileIDR27AudioStreamBasicDescriptionRy
 * demangled: LoadFileDataInfo(char const*, OpaqueAudioFileID*&, AudioStreamBasicDescription&, unsigned long long&)
 * address: 00070d14
 * size: 184
 */

/* LoadFileDataInfo(char const*, OpaqueAudioFileID*&, AudioStreamBasicDescription&, unsigned long
   long&) */

int LoadFileDataInfo(char *param_1,OpaqueAudioFileID **param_2,AudioStreamBasicDescription *param_3,
                    ulonglong *param_4)

{
  int iVar1;
  undefined4 local_1c;

  local_1c = 0x28;
  iVar1 = OpenFile(param_1,param_2);
  if (iVar1 == 0) {
    iVar1 = _AudioFileGetProperty(*param_2,0x64666d74,&local_1c,param_3);
    if (iVar1 == 0) {
      local_1c = 8;
      iVar1 = _AudioFileGetProperty(*param_2,0x62636e74,&local_1c,param_4);
      if (iVar1 != 0) {
        _printf("%s: %d\n","Error getting file data size",iVar1);
      }
    }
    else {
      _printf("%s: %d\n","Error getting file format",iVar1);
    }
  }
  else {
    _printf("%s: %d\n","Error opening file",iVar1);
  }
  return iVar1;
}
