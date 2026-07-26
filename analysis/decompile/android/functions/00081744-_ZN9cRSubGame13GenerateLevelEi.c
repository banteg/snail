/*
 * mangled: _ZN9cRSubGame13GenerateLevelEi
 * demangled: cRSubGame::GenerateLevel(int)
 * address: 00081744
 * size: 104
 */

/* cRSubGame::GenerateLevel(int) */

void __thiscall cRSubGame::GenerateLevel(cRSubGame *this,int param_1)

{
  *(int *)(this + 100) = param_1;
  SetFeatures(this);
  BuildColours();
  BuildLevel();
  PlaceParcels(this);
  SmoothTrack(this);
  WarnTrack(this);
  SlideSmoothTrack(this);
  CondenseTrack(this);
  DeSaltTrack(this);
  FringeEdgeTrack(this);
  cRWorld::ReSet((cRWorld *)(this + 0xf9f0));
  return;
}
