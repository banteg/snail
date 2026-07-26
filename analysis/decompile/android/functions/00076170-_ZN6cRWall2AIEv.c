/*
 * mangled: _ZN6cRWall2AIEv
 * demangled: cRWall::AI()
 * address: 00076170
 * size: 112
 */

/* cRWall::AI() */

void __thiscall cRWall::AI(cRWall *this)

{
  float fVar1;
  float fVar2;

  fVar1 = DAT_000761e0;
  fVar2 = *(float *)(this + 0x30);
  *(float *)(this + 0x30) = fVar2 + *(float *)(this + 0x34);
  if (fVar1 < fVar2 + *(float *)(this + 0x34)) {
    cRSubLazerManager::Shoot
              (*(int *)(this + 0x2c) + 0x41a8,*(undefined4 *)(this + 0x10),
               *(undefined4 *)(this + 0x14),*(undefined4 *)(this + 0x18),DAT_000761e4,DAT_000761e4,
               DAT_000761e8);
  }
  return;
}
