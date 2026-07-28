/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: spawn_track_speedup @ 0x43d880 */
/* selector: spawn_track_speedup */

// Exact one-instruction no-op shared by two authored call surfaces: `cRSubGame::AddSpeedUp(cRSubLoc*, cRSubGoldy*)` and `cRSubHover::Hover(tVector&, float)`. Cross-port Android retains both as separate literal no-ops; Windows callsites prove the two receiver/signature families share this folded address.
void __stdcall spawn_track_speedup(int a1, int a2)
{
  ;
}
