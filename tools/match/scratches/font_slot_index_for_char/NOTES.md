# FontASCIIRemap

`FontASCIIRemap(char)` is the native-authored owner of the Windows routine at
`0x449d20`. The focused match is exact at 145/145 instructions.

It maps letters, digits, punctuation, and UI symbols into font-atlas slots.
The Windows source preserves the native multi-character `'""'` comparison;
mobile `RFontTypeSet` branches differ, but Android and iOS both retain the core
`FontASCIIRemap(char)` owner in `Font.o`. Live Windows analysis finds six
callers.

The directory and manifest retain `font_slot_index_for_char` as the stable
matcher identifier.
