/*
 * mangled: _ZN6cRFace2AIEv
 * demangled: cRFace::AI()
 * address: 0001952c
 * size: 76
 */

/* cRFace::AI() */

void __thiscall cRFace::AI(cRFace *this)

{
  cRMovie::AI((cRMovie *)(this + 0x2c));
  *(undefined4 *)(*(int *)(*(int *)(this + 0x24) + 200) + 0xc) = *(undefined4 *)(this + 0x14c);
  ObjectProcLandScapeUpdate(*(cRObject **)(this + 0x24),0.0,5.0,*(cRTexture **)(this + 0x14c),false)
  ;
  return;
}
