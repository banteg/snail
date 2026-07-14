# AudioBackend::stop_registered_sound_sample @ 0x449a20

The native voice-manager caller loads `ECX = 0x753c58` immediately before the
call, proving the `AudioBackend` member ABI. Its BASS return value is discarded;
the recovered public method therefore keeps the shared `void` declaration while
preserving the native tail call result in `EAX` incidentally.
