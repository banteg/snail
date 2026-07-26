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

  fVar1 = *(float *)(this + 0x30);
  *(float *)(this + 0x30) = fVar1 + *(float *)(this + 0x34);
  if (1.0 < fVar1 + *(float *)(this + 0x34)) {
    cRSubLazerManager::Shoot
              (*(int *)(this + 0x2c) + 0x41a8,*(undefined4 *)(this + 0x10),
               *(undefined4 *)(this + 0x14),*(undefined4 *)(this + 0x18),0,0,0xbdcccccd);
  }
  return;
}
