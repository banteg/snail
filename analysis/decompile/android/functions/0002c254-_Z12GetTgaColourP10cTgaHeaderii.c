/*
 * mangled: _Z12GetTgaColourP10cTgaHeaderii
 * demangled: GetTgaColour(cTgaHeader*, int, int)
 * address: 0002c254
 * size: 92
 */

/* GetTgaColour(cTgaHeader*, int, int) */

uint GetTgaColour(cTgaHeader *param_1,int param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;

  iVar4 = (uint)((byte)param_1[0x10] >> 3) *
          ((uint)*(ushort *)(param_1 + 0xc) * ((*(ushort *)(param_1 + 0xe) - 1) - param_3) + param_2
          );
  if (param_1[0x10] == (cTgaHeader)0x8) {
    uVar3 = (uint)(byte)param_1[iVar4 + 0x12];
    uVar2 = uVar3;
    uVar1 = uVar3;
  }
  else {
    uVar1 = (uint)(byte)param_1[iVar4 + 0x13];
    uVar2 = (uint)(byte)param_1[iVar4 + 0x12];
    uVar3 = (uint)(byte)param_1[iVar4 + 0x14];
  }
  return uVar1 << 8 | uVar2 << 0x10 | uVar3;
}
