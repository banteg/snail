#ifndef SNAIL_BASS_MIN_H
#define SNAIL_BASS_MIN_H

#include "win32_min.h"

/*
 * Minimal legacy BASS declarations matching the dynamically resolved symbols in
 * the game's `tBass.dll` loader. This follows the older BASS 1.x-style API
 * surface used by the 2006 build instead of newer 2.x headers.
 */

typedef DWORD HCHANNEL;
typedef DWORD HSAMPLE;
typedef DWORD HSTREAM;
typedef DWORD HMUSIC;
typedef DWORD HSYNC;

typedef void (CALLBACK *SYNCPROC)(HSYNC sync, DWORD channel, DWORD data, void *user);

BOOL WINAPI BASS_Init(INT device, DWORD freq, DWORD flags, HWND window, const GUID *clsid);
BOOL WINAPI BASS_SetConfig(DWORD option, DWORD value);
BOOL WINAPI BASS_Free(void);
BOOL WINAPI BASS_Update(DWORD length);

HSTREAM WINAPI BASS_StreamCreateFile(BOOL mem, const void *file, DWORD offset, DWORD length, DWORD flags);
BOOL WINAPI BASS_StreamPlay(HSTREAM stream, BOOL flush, DWORD flags);
BOOL WINAPI BASS_StreamPreBuf(HSTREAM stream);
BOOL WINAPI BASS_StreamFree(HSTREAM stream);

HSAMPLE WINAPI BASS_SampleLoad(BOOL mem, const void *file, DWORD offset, DWORD length, DWORD max, DWORD flags);
HCHANNEL WINAPI BASS_SamplePlayEx(HSAMPLE sample, DWORD start, INT volume, INT pan, BOOL loop);
BOOL WINAPI BASS_SampleStop(HSAMPLE sample);

BOOL WINAPI BASS_ChannelStop(DWORD channel);
QWORD WINAPI BASS_ChannelBytes2Seconds(DWORD channel, DWORD bytes);
DWORD WINAPI BASS_ChannelGetLevel(DWORD channel);
DWORD WINAPI BASS_ChannelGetData(DWORD channel, void *buffer, DWORD length);
HSYNC WINAPI BASS_ChannelSetSync(DWORD channel, DWORD sync_type, DWORD parameter, SYNCPROC proc, void *user);
DWORD WINAPI BASS_ChannelGetPosition(DWORD channel);
BOOL WINAPI BASS_ChannelRemoveSync(DWORD channel, HSYNC sync);
DWORD WINAPI BASS_ChannelIsActive(DWORD channel);

DWORD WINAPI BASS_ErrorGetCode(void);
BOOL WINAPI BASS_Start(void);
BOOL WINAPI BASS_Stop(void);
BOOL WINAPI BASS_Pause(void);

typedef BOOL (WINAPI *BASS_InitProc)(INT device, DWORD freq, DWORD flags, HWND window, const GUID *clsid);
typedef BOOL (WINAPI *BASS_SetConfigProc)(DWORD option, DWORD value);
typedef BOOL (WINAPI *BASS_FreeProc)(void);
typedef BOOL (WINAPI *BASS_UpdateProc)(DWORD length);
typedef HSTREAM (WINAPI *BASS_StreamCreateFileProc)(BOOL mem, const void *file, DWORD offset, DWORD length, DWORD flags);
typedef BOOL (WINAPI *BASS_StreamPlayProc)(HSTREAM stream, BOOL flush, DWORD flags);
typedef BOOL (WINAPI *BASS_StreamPreBufProc)(HSTREAM stream);
typedef BOOL (WINAPI *BASS_StreamFreeProc)(HSTREAM stream);
typedef HSAMPLE (WINAPI *BASS_SampleLoadProc)(BOOL mem, const void *file, DWORD offset, DWORD length, DWORD max, DWORD flags);
typedef HCHANNEL (WINAPI *BASS_SamplePlayExProc)(HSAMPLE sample, DWORD start, INT volume, INT pan, BOOL loop);
typedef BOOL (WINAPI *BASS_SampleStopProc)(HSAMPLE sample);
typedef BOOL (WINAPI *BASS_ChannelStopProc)(DWORD channel);
typedef QWORD (WINAPI *BASS_ChannelBytes2SecondsProc)(DWORD channel, DWORD bytes);
typedef DWORD (WINAPI *BASS_ChannelGetLevelProc)(DWORD channel);
typedef DWORD (WINAPI *BASS_ChannelGetDataProc)(DWORD channel, void *buffer, DWORD length);
typedef HSYNC (WINAPI *BASS_ChannelSetSyncProc)(DWORD channel, DWORD sync_type, DWORD parameter, SYNCPROC proc, void *user);
typedef DWORD (WINAPI *BASS_ChannelGetPositionProc)(DWORD channel);
typedef BOOL (WINAPI *BASS_ChannelRemoveSyncProc)(DWORD channel, HSYNC sync);
typedef DWORD (WINAPI *BASS_ChannelIsActiveProc)(DWORD channel);
typedef DWORD (WINAPI *BASS_ErrorGetCodeProc)(void);
typedef BOOL (WINAPI *BASS_StartProc)(void);
typedef BOOL (WINAPI *BASS_StopProc)(void);
typedef BOOL (WINAPI *BASS_PauseProc)(void);

#endif
