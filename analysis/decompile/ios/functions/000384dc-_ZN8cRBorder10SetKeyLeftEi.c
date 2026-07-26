/*
 * mangled: _ZN8cRBorder10SetKeyLeftEi
 * demangled: cRBorder::SetKeyLeft(int)
 * address: 000384dc
 * size: 20
 */

/* cRBorder::SetKeyLeft(int) */

void __thiscall cRBorder::SetKeyLeft(cRBorder *this,int param_1)

{
  *(int *)(this + 0x188) = param_1;
  *(uint *)(this + 0x194) = *(uint *)(this + 0x194) | 0x80000;
  return;
}
