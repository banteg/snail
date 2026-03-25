/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_bass_audio_backend @ 0x449460 */
/* selector: initialize_bass_audio_backend */

// Extracts Bass.dll from game data into tBass.dll, loads the BASS 2.0 exports dynamically, and initializes the audio backend.
char __thiscall initialize_bass_audio_backend(_BYTE *this, int a2)
{
  _BYTE *file_bytes; // esi
  int ElementCount; // [esp+Ch] [ebp-4h] BYREF

  byte_7516A0 = 0;
  *(this + 24) = 0;
  file_bytes = load_file_bytes(aBassDll, (#83 *)&ElementCount);
  write_file_bytes(LibFileName, file_bytes, ElementCount);
  free_tracked_memory((int)file_bytes);
  MEMORY[0x753C90] = ((int (__stdcall *)(char *))LoadLibraryA)(LibFileName);
  MEMORY[0x753C08] = (int (__stdcall *)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD))((int (__stdcall *)(_DWORD, char *))GetProcAddress)(
                                                                                  MEMORY[0x753C90],
                                                                                  ProcName);
  MEMORY[0x753C1C] = (int (__stdcall *)(_DWORD, _DWORD))((int (__stdcall *)(_DWORD, char *))GetProcAddress)(
                                                          MEMORY[0x753C90],
                                                          aBassSetconfig);
  MEMORY[0x7537D8] = (int (*)(void))((int (__stdcall *)(_DWORD, char *))GetProcAddress)(MEMORY[0x753C90], aBassFree);
  MEMORY[0x751698] = ((int (__stdcall *)(_DWORD, char *))GetProcAddress)(MEMORY[0x753C90], aBassUpdate);
  MEMORY[0x753BF8] = (int (__stdcall *)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD))((int (__stdcall *)(_DWORD, char *))GetProcAddress)(
                                                                                  MEMORY[0x753C90],
                                                                                  aBassStreamcrea);
  MEMORY[0x7517A0] = (int (__stdcall *)(_DWORD, _DWORD, _DWORD))((int (__stdcall *)(_DWORD, char *))GetProcAddress)(
                                                                  MEMORY[0x753C90],
                                                                  aBassStreamplay);
  MEMORY[0x751670] = ((int (__stdcall *)(_DWORD, char *))GetProcAddress)(MEMORY[0x753C90], aBassStreampreb);
  MEMORY[0x753BE4] = (int (__stdcall *)(_DWORD))((int (__stdcall *)(_DWORD, char *))GetProcAddress)(
                                                  MEMORY[0x753C90],
                                                  aBassChannelsto);
  MEMORY[0x753CB0] = (int (__stdcall *)(_DWORD))((int (__stdcall *)(_DWORD, char *))GetProcAddress)(
                                                  MEMORY[0x753C90],
                                                  aBassStreamfree);
  MEMORY[0x7537CC] = (int (__stdcall *)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))((int (__stdcall *)(_DWORD, char *))GetProcAddress)(
                                                                                          MEMORY[0x753C90],
                                                                                          aBassSampleload);
  MEMORY[0x7527B4] = (int (__stdcall *)(_DWORD, _DWORD, _DWORD, _DWORD, _DWORD, _DWORD))((int (__stdcall *)(_DWORD, char *))GetProcAddress)(
                                                                                          MEMORY[0x753C90],
                                                                                          aBassSampleplay);
  MEMORY[0x753C94] = (int (__stdcall *)(_DWORD))((int (__stdcall *)(_DWORD, char *))GetProcAddress)(
                                                  MEMORY[0x753C90],
                                                  aBassSamplestop);
  MEMORY[0x753C1C] = (int (__stdcall *)(_DWORD, _DWORD))((int (__stdcall *)(_DWORD, char *))GetProcAddress)(
                                                          MEMORY[0x753C90],
                                                          aBassSetconfig);
  MEMORY[0x753BFC] = (int (*)(void))((int (__stdcall *)(_DWORD, char *))GetProcAddress)(MEMORY[0x753C90], aBassStop);
  MEMORY[0x751660] = (int (*)(void))((int (__stdcall *)(_DWORD, char *))GetProcAddress)(MEMORY[0x753C90], aBassStart);
  MEMORY[0x753CC0] = (int (*)(void))((int (__stdcall *)(_DWORD, char *))GetProcAddress)(MEMORY[0x753C90], aBassPause);
  MEMORY[0x75162C] = ((int (__stdcall *)(_DWORD, char *))GetProcAddress)(MEMORY[0x753C90], aBassChannelbyt);
  MEMORY[0x753CBC] = ((int (__stdcall *)(_DWORD, char *))GetProcAddress)(MEMORY[0x753C90], aBassChannelget);
  MEMORY[0x753C18] = ((int (__stdcall *)(_DWORD, char *))GetProcAddress)(MEMORY[0x753C90], aBassChannelget_0);
  MEMORY[0x753CC4] = ((int (__stdcall *)(_DWORD, char *))GetProcAddress)(MEMORY[0x753C90], aBassChannelset);
  MEMORY[0x753C98] = ((int (__stdcall *)(_DWORD, char *))GetProcAddress)(MEMORY[0x753C90], aBassChannelget_1);
  MEMORY[0x751674] = ((int (__stdcall *)(_DWORD, char *))GetProcAddress)(MEMORY[0x753C90], aBassErrorgetco);
  MEMORY[0x75165C] = (int (__stdcall *)(_DWORD, _DWORD))((int (__stdcall *)(_DWORD, char *))GetProcAddress)(
                                                          MEMORY[0x753C90],
                                                          aBassChannelrem);
  MEMORY[0x753CA8] = (int (__stdcall *)(_DWORD))((int (__stdcall *)(_DWORD, char *))GetProcAddress)(
                                                  MEMORY[0x753C90],
                                                  aBassChannelisa);
  *((_DWORD *)this + 1) = 0;
  *((_DWORD *)this + 2) = 1028443341;
  *this = 0;
  if ( MEMORY[0x753C08](1, 44100, 0, a2, 0) )
  {
    MEMORY[0x753C1C](1, 50);
    unk_753C20 = 0;
    unk_751680 = 0;
    return 1;
  }
  else
  {
    report_errorf(aCanTInitialize);
    return 0;
  }
}

