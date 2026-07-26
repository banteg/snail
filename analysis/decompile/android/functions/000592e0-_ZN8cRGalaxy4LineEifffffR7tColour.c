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
  undefined4 uVar1;
  float in_r3;
  float fVar2;
  float fVar3;
  float in_stack_00000000;
  float in_stack_00000004;
  float in_stack_00000008;
  undefined4 *in_stack_0000000c;
  float local_34;
  float local_30;
  undefined4 local_2c;

  uVar1 = DAT_000593d4;
  local_34 = in_stack_00000000 - (float)param_7;
  local_2c = DAT_000593d4;
  local_30 = in_stack_00000004 - in_r3;
  tVector::Normalize((tVector *)&local_34);
  fVar2 = in_stack_00000008 * local_34 * DAT_000593d8;
  fVar3 = -(local_30 * in_stack_00000008) * DAT_000593d8;
  OSDPrintUV(param_1,(float)param_7 - fVar3,in_r3 - fVar2,in_stack_00000000 - fVar3,
             in_stack_00000004 - fVar2,in_stack_00000000 + fVar3,in_stack_00000004 + fVar2,
             (float)param_7 + fVar3,in_r3 + fVar2,uVar1,uVar1,0x1000000,*in_stack_0000000c,
             in_stack_0000000c[1],in_stack_0000000c[2],in_stack_0000000c[3],uVar1,uVar1,DAT_000593dc
             ,DAT_000593dc,1,uVar1);
  return;
}
