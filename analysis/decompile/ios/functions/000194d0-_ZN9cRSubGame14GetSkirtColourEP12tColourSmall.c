/*
 * mangled: _ZN9cRSubGame14GetSkirtColourEP12tColourSmall
 * demangled: cRSubGame::GetSkirtColour(tColourSmall*)
 * address: 000194d0
 * size: 56
 */

/* cRSubGame::GetSkirtColour(tColourSmall*) */

void __thiscall cRSubGame::GetSkirtColour(cRSubGame *this,tColourSmall *param_1)

{
  tColourSmall::Set(param_1,*(float *)(this + 0x1258),*(float *)(this + 0x125c),
                    *(float *)(this + 0x1260),0.5);
  return;
}
