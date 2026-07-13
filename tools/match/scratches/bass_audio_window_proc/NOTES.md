# bass_audio_window_proc @ 0x4079e0

Window procedure for the hidden class named `"BASS"`. It handles only
`WM_CLOSE` by posting a zero-code quit message; all other messages are forwarded
unchanged to `DefWindowProcA`.
