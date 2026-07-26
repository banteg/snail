/*
 * mangled: _ZN9cROverlay4InitEv
 * demangled: cROverlay::Init()
 * address: 0003f5e8
 * size: 68
 */

/* cROverlay::Init() */

void __thiscall cROverlay::Init(cROverlay *this)

{
  *(undefined4 *)(this + 300) = 0;
  *(undefined4 *)(this + 0x130) = 0x39bf9cd1;
  tMatrix::Identity((tMatrix *)(this + 0x2c));
  *(undefined4 *)(this + 0x128) = 0x42180000;
  tMatrix::Identity((tMatrix *)(this + 0xa0));
  tMatrix::Invert((tMatrix *)(this + 0xe8),(tMatrix *)(this + 0x2c));
  return;
}
