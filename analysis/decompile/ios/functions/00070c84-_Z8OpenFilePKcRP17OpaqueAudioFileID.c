/*
 * mangled: _Z8OpenFilePKcRP17OpaqueAudioFileID
 * demangled: OpenFile(char const*, OpaqueAudioFileID*&)
 * address: 00070c84
 * size: 132
 */

/* OpenFile(char const*, OpaqueAudioFileID*&) */

int OpenFile(char *param_1,OpaqueAudioFileID **param_2)

{
  size_t sVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;

  uVar4 = *(undefined4 *)PTR_001b6200;
  sVar1 = _strlen(param_1);
  iVar2 = _CFURLCreateFromFileSystemRepresentation(uVar4,param_1,sVar1,0);
  if (iVar2 == 0) {
    iVar2 = 3;
  }
  else {
    iVar3 = _AudioFileOpenURL(iVar2,1,0,param_2);
    _CFRelease(iVar2);
    iVar2 = 0;
    if (iVar3 != 0) {
      _printf("%s: %d\n","Error opening file",iVar3);
      return iVar3;
    }
  }
  return iVar2;
}
