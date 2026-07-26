/*
 * mangled: _Z14FontASCIIRemapc
 * demangled: FontASCIIRemap(char)
 * address: 00031a84
 * size: 512
 */

/* FontASCIIRemap(char) */

int FontASCIIRemap(char param_1)

{
  int iVar1;

  iVar1 = (int)param_1;
  if ((iVar1 - 0x41U & 0xff) < 0x1a) {
    return iVar1 + -0x26;
  }
  if ((iVar1 - 0x61U & 0xff) < 0x1a) {
    return iVar1 + -0x60;
  }
  if ((iVar1 - 0x30U & 0xff) < 10) {
    return iVar1 + 6;
  }
  if (iVar1 != 0x20) {
    if (iVar1 == 0x22) {
      return 0x40;
    }
    if (iVar1 == 0x3a) {
      return 0x42;
    }
    if (iVar1 == 0x28) {
      return 0x43;
    }
    if (iVar1 == 0x29) {
      return 0x44;
    }
    if (iVar1 == 0x21) {
      return 0x45;
    }
    if (iVar1 == 0x40) {
      return 0x46;
    }
    if (iVar1 == 0x23) {
      return 0x47;
    }
    if (iVar1 == 0x24) {
      return 0x48;
    }
    if (iVar1 == 0x25) {
      return 0x49;
    }
    if (iVar1 == 0x3f) {
      return 0x4a;
    }
    if (iVar1 == 0x26) {
      return 0x4b;
    }
    if (iVar1 == 0x2a) {
      return 0x4c;
    }
    if (iVar1 == 0x2b) {
      return 0x4d;
    }
    if (iVar1 == 0x2d) {
      return 0x4f;
    }
    if (iVar1 == 0x2f) {
      return 0x50;
    }
    if (iVar1 == 0x5c) {
      return 0x51;
    }
    if (iVar1 == 0x2c) {
      return 0x52;
    }
    if (iVar1 == 0x2e) {
      return 0x53;
    }
    if (iVar1 == 0x27) {
      return 0x54;
    }
    if (iVar1 == 0x7c) {
      return 0x55;
    }
    if (RFontTypeSet == 1) {
      if (iVar1 == 0x5b) {
        return 0x5f;
      }
      if (iVar1 == 0x7b) {
        return 0x60;
      }
      if (iVar1 == 0x7d) {
        return 0x61;
      }
      if (iVar1 == 0x5d) {
        return 0x62;
      }
    }
    else if (RFontTypeSet == 0) {
      if (iVar1 == 0x7b) {
        return 0x56;
      }
      if (iVar1 == 0x7d) {
        return 0x57;
      }
      if (iVar1 == 0x5b) {
        return 0x58;
      }
      if (iVar1 == 0x5d) {
        return 0x59;
      }
      if (iVar1 == 0x7e) {
        return 0x5a;
      }
      if (iVar1 == 0x3b) {
        return 0x5b;
      }
      if (iVar1 == 0x5f) {
        return 0x5c;
      }
      if (iVar1 == 0x5e) {
        return 0x5d;
      }
      if (iVar1 == 0x3d) {
        return 0x5e;
      }
    }
  }
  return 0x35;
}
