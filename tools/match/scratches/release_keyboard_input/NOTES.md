# release_keyboard_input @ 0x44bb60

Releases the keyboard DirectInput device and parent DirectInput object. The
device is unacquired before release, then both globals are cleared.

Android retains the authored global as the side-effect-only void
`FreeDirectInputKeyboard()`. Its platform body is an empty stub and leaves an
arbitrary register value; both Windows callers also discard EAX. Removing the
synthetic COM-release result preserves the exact 21/21 Windows body and closes
the process-owned keyboard lifetime as a void teardown operation.
