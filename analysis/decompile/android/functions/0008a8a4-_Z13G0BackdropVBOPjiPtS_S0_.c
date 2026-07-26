/*
 * mangled: _Z13G0BackdropVBOPjiPtS_S0_
 * demangled: G0BackdropVBO(unsigned int*, int, unsigned short*, unsigned int*, unsigned short*)
 * address: 0008a8a4
 * size: 140
 */

/* G0BackdropVBO(unsigned int*, int, unsigned short*, unsigned int*, unsigned short*) */

void G0BackdropVBO(uint *param_1,int param_2,ushort *param_3,uint *param_4,ushort *param_5)

{
  glGenBuffers(1,param_1);
  glBindBuffer(0x8893,*param_1);
  glBufferData(0x8893,param_2 << 1,param_3,0x88e4);
  glBindBuffer(0x8893,0);
  glGenBuffers(1,param_4);
  glBindBuffer(0x8893,*param_4);
  glBufferData(0x8893,8,param_5,0x88e4);
  glBindBuffer(0x8893,0);
  return;
}
