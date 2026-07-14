# set_color_alpha @ 0x44db80

Android names this one-field writer `tColour::Alpha(float)`. Both Windows
callers pass ordinary float constants and ignore `eax`; VC6 naturally copies
the argument bits through `eax` for a void float method. The honest source is
therefore exact at 3/3 instructions without the previous synthetic integer
return.
