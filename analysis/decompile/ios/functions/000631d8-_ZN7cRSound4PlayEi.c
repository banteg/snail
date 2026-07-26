/*
 * mangled: _ZN7cRSound4PlayEi
 * demangled: cRSound::Play(int)
 * address: 000631d8
 * size: 32
 */

/* cRSound::Play(int) */

void __thiscall cRSound::Play(cRSound *this,int param_1)

{
  RShellSoundPlay(param_1,1.0,-1.0,0.0);
  return;
}
