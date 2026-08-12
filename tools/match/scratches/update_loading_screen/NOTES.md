# update_loading_screen @ 0x418e80

Exact Windows `cRLoadingBar::AI()` at 204/204 instructions with all 26 masked
references clean. Android and iOS independently preserve the owner and method
in `LoadingBar.o`.

The updater advances the normalized loader percentage, draws the 640x480
background, and clips the fill quad from `(192, 289)` to `(448, 321)`. Its
object builder and two archive-loader callsites discard EAX, confirming the
void contract. The exact source spelling deliberately shortens the clamped
percentage lifetime and uses a chained `u_end` assignment to reproduce VC6's
native register and x87 scheduling.
