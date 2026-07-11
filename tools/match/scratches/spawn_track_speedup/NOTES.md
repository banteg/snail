# spawn_track_speedup

`spawn_track_speedup` @ 0x43d880 is exact at one instruction (`ret 8`). It is
modeled as the void `SubgameRuntime` member retained cross-port as
`cRSubGame::AddSpeedUp(cRSubLoc*, cRSubGoldy*)`, not as a free stdcall stub.
Android independently retains the same symbol and literal no-op body; iOS v1.9
retains the authored signature.

The no-op does not erase ownership of the already constructed `SubSpeedUp`
singleton. Its exact AI, collision path, reset backlink, and teardown path all
consume the owned record at `SubgameRuntime +0x355db0`.
