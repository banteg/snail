/*
 * mangled: _ZN8cRGalaxy4LineEifffffR7tColour
 * demangled: cRGalaxy::Line(int, float, float, float, float, float, tColour&)
 * address: 000592e0
 * size: 244
 */

/* cRGalaxy::Line(int, float, float, float, float, float, tColour&) */

void __thiscall
cRGalaxy::Line(cRGalaxy *this,int param_1,float param_2,float param_3,float param_4,float param_5,
              float param_6,tColour *param_7)

{
  float in_r3;
  float fVar1;
  float fVar2;
  float in_stack_00000000;
  float in_stack_00000004;
  float in_stack_00000008;
  undefined4 *in_stack_0000000c;
  float local_34;
  float local_30;
  undefined4 local_2c;

  local_34 = in_stack_00000000 - (float)param_7;
  local_2c = 0;
  local_30 = in_stack_00000004 - in_r3;
  tVector::Normalize((tVector *)&local_34);
  fVar1 = in_stack_00000008 * local_34 * 0.5;
  fVar2 = -(local_30 * in_stack_00000008) * 0.5;
  OSDPrintUV(param_1,(float)param_7 - fVar2,in_r3 - fVar1,in_stack_00000000 - fVar2,
             in_stack_00000004 - fVar1,in_stack_00000000 + fVar2,in_stack_00000004 + fVar1,
             (float)param_7 + fVar2,in_r3 + fVar1,0,0,0x1000000,*in_stack_0000000c,
             in_stack_0000000c[1],in_stack_0000000c[2],in_stack_0000000c[3],0,0,0x3f800000,
             0x3f800000,1,0);
  return;
}
