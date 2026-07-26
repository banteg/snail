/*
 * mangled: _ZN12cRCompletion14RegisterParcelEv
 * demangled: cRCompletion::RegisterParcel()
 * address: 00060b4c
 * size: 180
 */

/* cRCompletion::RegisterParcel() */

void __thiscall cRCompletion::RegisterParcel(cRCompletion *this)

{
  if (*(int *)(this + 0x24) == *(int *)(this + 0x18)) {
    return;
  }
  cRSubGoldy::ScoreAdd((cRSubGoldy *)(Game + 0x81364),4,0);
  OFAddParcelDelivered();
  *(int *)(this + 0x24) = *(int *)(this + 0x24) + 1;
  cRSound::Play((int)&gRSound);
  if (*(int *)(this + 0x24) != *(int *)(this + 0x18)) {
    return;
  }
  if (*(int *)(this + 0x1c) != 0) {
    cRSubGoldy::ScoreAdd((cRSubGoldy *)(Game + 0x81364),5,*(int *)(this + 0x44));
    cRSound::Play((int)&gRSound);
  }
  *(undefined4 *)(this + 0x10) = 3;
  return;
}
