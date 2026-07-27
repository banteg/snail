# get_authored_view_height

Tiny getter at `0x433040` returning the authored view height float from
`g_authored_view_height`.

## 2026-07-27 mobile owner proof

Android and iOS export this contract as `RShellGetScreenHeight()` and return
their independently named `gG0ScreenHeight` owner. The later ports store the
platform dimension as an integer, whereas Windows retains a float-backed
480-style authored viewport, so the evidence transfers the original
`RShell.o` vocabulary and owner without forcing a cross-platform storage type.
