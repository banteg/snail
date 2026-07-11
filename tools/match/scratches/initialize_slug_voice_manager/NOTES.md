# initialize_slug_voice_manager

`initialize_slug_voice_manager` @ 0x43f5c0 is exact at 4/4 instructions.
Android retains the authored owner and member as `cRSlugVoiceManager::Init()`.
Both initialize the complete 0x0c-byte object to inactive, zero progress, and a
1/60 update step. Windows embeds it at `SubgameRuntime +0x35bb7c`, immediately
after the two-record `SubRingPool` and immediately before the score-widget
handles at `+0x35bb88`.
