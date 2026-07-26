/*
 * mangled: _ZN9cRSubGame12LevelConvertEcib
 * demangled: cRSubGame::LevelConvert(char, int, bool)
 * address: 0006b980
 * size: 748
 */

/* cRSubGame::LevelConvert(char, int, bool) */

int __thiscall cRSubGame::LevelConvert(cRSubGame *this,char param_1,int param_2,bool param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;

  iVar1 = (int)param_1;
  if (*(int *)(this + 0x78) < param_2) {
    return iVar1;
  }
  switch(iVar1) {
  case 0x20:
    if ((*(uint *)(this + 0x6c) & 0x400) != 0) {
      if ((*(uint *)(this + 0x6c) & 1) == 0) {
        return 0x2e;
      }
      return iVar1;
    }
    goto LAB_0006bc5c;
  case 0x21:
    break;
  case 0x22:
    break;
  case 0x23:
    break;
  case 0x24:
    uVar2 = *(uint *)(this + 0x6c);
    uVar3 = uVar2 & 0x800;
    goto joined_r0x0006bbe8;
  case 0x25:
    break;
  case 0x26:
    break;
  case 0x27:
    break;
  case 0x28:
    break;
  case 0x29:
    break;
  case 0x2a:
    break;
  case 0x2b:
    break;
  case 0x2c:
    break;
  case 0x2d:
    uVar3 = *(uint *)(this + 0x6c) & 0x4000;
    goto joined_r0x0006bb44;
  case 0x2e:
    break;
  case 0x2f:
    break;
  case 0x30:
    break;
  case 0x31:
    break;
  case 0x32:
    break;
  case 0x33:
    break;
  case 0x34:
    break;
  case 0x35:
    break;
  case 0x36:
    break;
  case 0x37:
    break;
  case 0x38:
    break;
  case 0x39:
    break;
  case 0x3a:
    break;
  case 0x3b:
    break;
  case 0x3c:
    goto LAB_0006bb3c;
  case 0x3d:
    uVar3 = *(uint *)(this + 0x6c);
    if ((uVar3 & 0x100) != 0) {
      return iVar1;
    }
    if ((uVar3 & 1) == 0) {
      return 0x2e;
    }
    if ((uVar3 & 0x400) != 0) {
      return 0x20;
    }
    goto LAB_0006bc5c;
  case 0x3e:
LAB_0006bb3c:
    uVar3 = *(uint *)(this + 0x6c) & 0x200;
joined_r0x0006bb44:
    if (uVar3 != 0) {
      return iVar1;
    }
    return 0x2e;
  case 0x3f:
    break;
  case 0x40:
    break;
  case 0x41:
    break;
  case 0x42:
    break;
  case 0x43:
    break;
  case 0x44:
    break;
  case 0x45:
    break;
  case 0x46:
    break;
  case 0x47:
    break;
  case 0x48:
    break;
  case 0x49:
    break;
  case 0x4a:
    break;
  case 0x4b:
    break;
  case 0x4c:
    break;
  case 0x4d:
    break;
  case 0x4e:
    break;
  case 0x4f:
    break;
  case 0x50:
    break;
  case 0x51:
    break;
  case 0x52:
    break;
  case 0x53:
    break;
  case 0x54:
    break;
  case 0x55:
    break;
  case 0x56:
    break;
  case 0x57:
    break;
  case 0x58:
    break;
  case 0x59:
    break;
  case 0x5a:
    break;
  case 0x5b:
    if ((*(uint *)(this + 0x6c) & 0x200) == 0) {
      return 0x2e;
    }
    if ((*(uint *)(this + 0x6c) & 0x20) != 0) {
      return iVar1;
    }
    goto LAB_0006bc1c;
  case 0x5c:
    break;
  case 0x5d:
    if ((*(uint *)(this + 0x6c) & 0x200) == 0) {
      return 0x2e;
    }
    if ((*(uint *)(this + 0x6c) & 0x20) != 0) {
LAB_0006bb28:
      if (this[2] != (cRSubGame)0x0) {
        return 0x7b;
      }
      return iVar1;
    }
LAB_0006bc1c:
    iVar1 = 0x3c;
    break;
  case 0x5e:
    break;
  case 0x5f:
    if (((*(uint *)(this + 0x6c) & 0x40) == 0) && (!param_3)) {
      return 0x2e;
    }
    break;
  case 0x60:
    break;
  case 0x61:
    break;
  case 0x62:
    break;
  case 99:
    break;
  case 100:
    break;
  case 0x65:
    break;
  case 0x66:
    break;
  case 0x67:
    break;
  case 0x68:
    break;
  case 0x69:
    break;
  case 0x6a:
    break;
  case 0x6b:
    break;
  case 0x6c:
    break;
  case 0x6d:
    break;
  case 0x6e:
    break;
  case 0x6f:
    uVar2 = *(uint *)(this + 0x6c);
    uVar3 = uVar2 & 4;
joined_r0x0006bbe8:
    if (uVar3 == 0) {
      if ((uVar2 & 0x40) == 0) {
        return 0x2e;
      }
      iVar1 = 0x5f;
    }
    break;
  case 0x70:
    break;
  case 0x71:
    break;
  case 0x72:
    break;
  case 0x73:
    break;
  case 0x74:
    break;
  case 0x75:
    break;
  case 0x76:
    break;
  case 0x77:
    break;
  case 0x78:
    break;
  case 0x79:
    break;
  case 0x7a:
    break;
  case 0x7b:
    if ((*(uint *)(this + 0x6c) & 0x200) == 0) {
      return 0x2e;
    }
    if ((*(uint *)(this + 0x6c) & 0x20) != 0) {
      if (this[2] != (cRSubGame)0x0) {
        return 0x7d;
      }
      return iVar1;
    }
    goto LAB_0006bc64;
  case 0x7c:
    uVar3 = *(uint *)(this + 0x6c);
    if ((uVar3 & 0x100) != 0) {
      return iVar1;
    }
    if ((uVar3 & 1) == 0) {
      return 0x20;
    }
    if ((uVar3 & 0x400) != 0) {
      return 0x3d;
    }
LAB_0006bc5c:
    iVar1 = 0x2c;
    break;
  case 0x7d:
    if ((*(uint *)(this + 0x6c) & 0x200) == 0) {
      return 0x2e;
    }
    if ((*(uint *)(this + 0x6c) & 0x20) != 0) goto LAB_0006bb28;
LAB_0006bc64:
    iVar1 = 0x3e;
  }
  return iVar1;
}
