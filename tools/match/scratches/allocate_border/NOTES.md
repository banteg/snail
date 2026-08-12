# allocate_border

The exact Windows body is the mobile-authored
`cRBorder* cRBorderManager::GetBorder()`. It scans the manager's 150 inline
`0x724`-byte records at `+0x684`, finds the first zero flags lane at record
`+0x1a0`, stamps `created_time +0x19c` from `cRGame::frame_counter`, and
returns that record through its authored `cRBorder` view.

Android and iOS retain the same owner, name, 150-slot lifecycle, and one body
each while using their own platform layouts. Focused Wibo result: 100.00%,
23/23 instructions, three clean masked operands.
