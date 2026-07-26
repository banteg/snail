/*
 * mangled: _Z13G0BackdropVBOPjiPt
 * demangled: G0BackdropVBO(unsigned int*, int, unsigned short*)
 * address: 0006ddb0
 * size: 92
 */

/* G0BackdropVBO(unsigned int*, int, unsigned short*) */

void G0BackdropVBO(uint *param_1,int param_2,ushort *param_3)

{
  _glGenBuffers(1,param_1);
  _glBindBuffer(0x8893,*param_1);
  _glBufferData(0x8893,param_2 << 1,param_3,&DAT_000088e4);
  _glBindBuffer(0x8893,0);
  return;
}
