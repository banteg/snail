# cRBass::SamplePlaying @ 0x449a40

The native voice-state caller loads `ECX = 0x753c58` immediately before the
call and tests `AL`, proving both the `AudioBackend` receiver and boolean return
surface. The method returns true only for the BASS active-state value `1`.

## 2026-07-27 mobile owner recovery

iOS `BassPlay.o` names this method `cRBass::SamplePlaying(int)`.
`cRVoiceManager::Play()` passes each registered VoiceSet bite id to `gBass`
and branches on the result, matching the Windows voice scan's owner and
boolean use. Both iOS versions deliberately compile the body as
`mov r0, 0; bx lr`; Windows retains the live BASS channel query.
