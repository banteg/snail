# spawn_track_speedup

`spawn_track_speedup` @ 0x43d880 is exact at one instruction (`ret 8`). It is
modeled as the void `SubgameRuntime` member retained cross-port as
`cRSubGame::AddSpeedUp(cRSubLoc*, cRSubGoldy*)`, not as a free stdcall stub.
Android independently retains the same symbol and literal no-op body; iOS v1.9
retains the authored signature.

The no-op does not erase ownership of the already constructed `SubSpeedUp`
singleton. Its exact AI, collision path, reset backlink, and teardown path all
consume the owned record at `SubgameRuntime +0x355db0`.

The same one-instruction Windows address is also called from
`SubHover::update_jetpack_gauge` with `ecx = SubHover*`, a `Vector3*`, and a
float. Android retains a separate literal no-op
`cRSubHover::Hover(tVector&, float)`, proving this is a folded second authored
surface rather than a type-confused call to AddSpeedUp. The stable Windows
target name remains `spawn_track_speedup`; the manifest records
`sub_hover_hover` as an alias.
