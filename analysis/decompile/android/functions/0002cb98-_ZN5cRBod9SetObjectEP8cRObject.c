/*
 * mangled: _ZN5cRBod9SetObjectEP8cRObject
 * demangled: cRBod::SetObject(cRObject*)
 * address: 0002cb98
 * size: 20
 */

/* cRBod::SetObject(cRObject*) */

void __thiscall cRBod::SetObject(cRBod *this,cRObject *param_1)

{
  *(cRObject **)(this + 0x24) = param_1;
  *(uint *)(this + 4) = *(uint *)(this + 4) | 2;
  return;
}
