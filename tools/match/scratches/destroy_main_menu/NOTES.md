# MainMenu::destroy_main_menu / Intro::destroy_new_game_menu

Small front-end teardown body at `0x419b30`. Both BN and IDA decompiles show it
killing all global border-manager widgets and then clearing game sprites.

Exact match: 100.00%, 5/5 instructions, with the root-owned border manager,
`g_sprite_manager`, and both teardown calls resolved. The 2026-07-14 root
client pass names `GameRoot::border_manager` directly without changing codegen.

2026-07-14 folded-owner recovery: Windows callers pass either the embedded
`MainMenu` at `GameRoot +0x4f324` or the embedded `Intro` at `+0x4f2dc` as
`ECX`. Android independently retains separate byte-identical
`cRMainMenu::UnInit()` and `cRIntro::UnInit()` functions. Windows therefore
folded two real authored member bodies to this address; the canonical scratch
defines the `MainMenu` form, while `destroy_new_game_menu` is the manifest alias
used by exact `Intro::update_new_game_menu` callsites.
