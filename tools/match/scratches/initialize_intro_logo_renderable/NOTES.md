# initialize_intro_logo_renderable @ 0x408490

Constructs one Windows `LogoLetter` by running the shared `RenderableBod`
initializer and replacing its callback table with `g_logo_letter_vtable` at
`0x497310`. `construct_game_runtime` invokes the same initializer across both
fixed banks owned by `Logo`: 1024 crawl letters at `+0x18` and 32 preloaded
image donors at `+0x24018`.

Symbol-preserving iOS builds identify the corresponding animated record as
`cRLogoLetter`; its `AI()` body independently matches
`update_intro_logo_renderable`. No constructor symbol survives in those builds,
but the Windows wrapper is the constructor installed across both fixed banks.
The matcher therefore exposes `cRLogoLetter::cRLogoLetter()` while retaining
`initialize_intro_logo_renderable` as its stable harness `FUNCTION` name.

Focused Wibo is exact at 100.00%, 7/7 instructions. The only relocation is the
callback table, resolved by the content-backed `g_logo_letter_vtable` manifest
entry.

## 2026-08-09 authored owner promotion

The primary matcher symbol is `??0cRLogoLetter@@QAE@XZ`. The true constructor
spelling preserves the exact 7/7 body and both clean references; `LogoLetter`
and `IntroLogoRenderable` remain compatibility typedefs for shared callers and
the Windows analyzer projection.
