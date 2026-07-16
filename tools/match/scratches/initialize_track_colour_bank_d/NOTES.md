# initialize_track_colour_bank_d

CRT constructor body at `0x4349f0` for Windows' second physical 51-entry Slide
bank. Android and iOS address their one original `gLocColourLookupSlide` owner
for both corresponding `BuildColours` calls, but the Windows addresses are
distinct and remain modeled as `slide_0` and `slide_1`. The D suffix remains
only as the stable CRT-table identity. The loop matches the native 12/12
instructions exactly, with both masked operands resolved.
