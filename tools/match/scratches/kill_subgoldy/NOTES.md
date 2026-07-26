# kill_subgoldy

Exact match: 100.00%, 6/6 instructions, one clean masked operand.

The helper calls `begin_post_follow_carryover(player)` and then stores `-8.0`
into `player->body.transform.position.y`. Its sole `update_times_up` caller
uses it as the terminal Goldy death/fall handoff. The matching source is void,
and both decompilers preserve the real thiscall `Player` receiver.

## 2026-07-26 mobile owner recovery

Android preserves the exact authored method as `cRSubGoldy::Kill()`: it calls
`FallingInit(this)` and stores the same `-8.0` value into Goldy's body Y lane.
That independently pins `begin_post_follow_carryover` as the Windows
platform's corresponding falling initializer. The former ghost-hide
description was inconsistent with the tracked Windows body and has been
removed.
