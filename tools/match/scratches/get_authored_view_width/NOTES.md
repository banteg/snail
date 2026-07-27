# get_authored_view_width

Tiny getter at `0x433030` returning the authored view width float from
`g_authored_view_width`.

## 2026-07-27 mobile owner proof

Android and iOS export this contract as `RShellGetScreenWidth()` and return
their independently named `gG0ScreenWidth` owner. The later ports store the
platform dimension as an integer, whereas Windows retains a float-backed
640-style authored viewport, so the evidence transfers the original
`RShell.o` vocabulary and owner without forcing a cross-platform storage type.
