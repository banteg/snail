/*
 * mangled: _ZN14cGLVertexArray18CalcTriStripSimpleEP8cRObject
 * demangled: cGLVertexArray::CalcTriStripSimple(cRObject*)
 * address: 0002d364
 * size: 76
 */

/* cGLVertexArray::CalcTriStripSimple(cRObject*) */

void __thiscall cGLVertexArray::CalcTriStripSimple(cGLVertexArray *this,cRObject *param_1)

{
  uint uVar1;
  undefined2 *puVar2;

  cRObject::RequestStrip(param_1,4);
  puVar2 = *(undefined2 **)(this + 0x48);
  uVar1 = *(uint *)param_1;
  puVar2[3] = 2;
  *puVar2 = 0;
  puVar2[1] = 1;
  puVar2[2] = 3;
  *(uint *)param_1 = uVar1 | 0x10000000;
  return;
}
