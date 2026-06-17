# release_mouse_input @ 0x44c2c0

Releases the mouse DirectInput device and parent DirectInput object. The device
is unacquired before release, then the non-null release paths clear their
corresponding globals.
