/*
 * mangled: _ZN6cRFace2AIEv
 * demangled: cRFace::AI()
 * address: 00075b20
 * size: 76
 */

/* cRFace::AI() */

void __thiscall cRFace::AI(cRFace *this)

{
  cRObject *pcVar1;
  undefined8 uVar2;

  uVar2 = cRMovie::AI((cRMovie *)(this + 0x2c));
  pcVar1 = *(cRObject **)(this + 0x24);
  *(undefined4 *)(*(int *)(pcVar1 + 200) + 0xc) = *(undefined4 *)(this + 0x14c);
  ObjectProcLandScapeUpdate
            (pcVar1,(float)uVar2,(float)((ulonglong)uVar2 >> 0x20),(cRTexture *)0x0,false);
  return;
}
