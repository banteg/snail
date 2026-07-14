# destroy_main_menu

Small main-menu teardown helper at 0x419b30. Both BN and IDA decompiles show it
killing all global border-manager widgets and then clearing game sprites.

Exact match: 100.00%, 5/5 instructions, with the root-owned border manager,
`g_sprite_manager`, and both teardown calls resolved. The 2026-07-14 root
client pass names `GameRoot::border_manager` directly without changing codegen.
