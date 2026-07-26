/*
 * mangled: _ZN9cROverlay4InitEv
 * demangled: cROverlay::Init()
 * address: 0003f5e8
 * size: 68
 */

/* cROverlay::Init() */

void __thiscall cROverlay::Init(cROverlay *this)

{
  *(undefined4 *)(this + 300) = DAT_0003f62c;
  *(undefined4 *)(this + 0x130) = DAT_0003f630;
  tMatrix::Identity((tMatrix *)(this + 0x2c));
  *(undefined4 *)(this + 0x128) = DAT_0003f634;
  tMatrix::Identity((tMatrix *)(this + 0xa0));
  tMatrix::Invert((tMatrix *)(this + 0xe8),(tMatrix *)(this + 0x2c));
  return;
}
