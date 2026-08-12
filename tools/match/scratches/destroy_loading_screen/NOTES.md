# destroy_loading_screen @ 0x418e50

Exact Windows `cRLoadingBar::UnInit()` at 15/15 instructions with all three
masked references clean. Android independently preserves the method in
`LoadingBar.o`.

Startup loads `ECX = 0x503290`, calls this immediately after world
initialization, and ignores EAX. The void member stores the measured loading
budget, releases the background and fill textures through their COM vtables,
and clears the owner's active field.
