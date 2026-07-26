/*
 * mangled: _ZN7cKeyPad11ConvertCodeEc
 * demangled: cKeyPad::ConvertCode(char)
 * address: 0004b2f0
 * size: 492
 */

/* cKeyPad::ConvertCode(char) */

undefined4 __thiscall cKeyPad::ConvertCode(cKeyPad *this,char param_1)

{
  undefined4 uVar1;

  if (param_1 == 'a') {
    return 0x1e;
  }
  if (param_1 == 'b') {
    return 0x30;
  }
  if (param_1 == 'c') {
    return 0x2e;
  }
  if (param_1 == 'd') {
    return 0x20;
  }
  if (param_1 == 'e') {
    return 0x12;
  }
  if (param_1 == 'f') {
    return 0x21;
  }
  if (param_1 == 'g') {
    return 0x22;
  }
  if (param_1 == 'h') {
    return 0x23;
  }
  if (param_1 == 'i') {
    return 0x17;
  }
  if (param_1 == 'j') {
    return 0x24;
  }
  if (param_1 == 'k') {
    return 0x25;
  }
  if (param_1 == 'l') {
    return 0x26;
  }
  if (param_1 == 'm') {
    return 0x32;
  }
  if (param_1 == 'n') {
    return 0x31;
  }
  if (param_1 == 'o') {
    return 0x18;
  }
  if (param_1 == 'p') {
    return 0x19;
  }
  if (param_1 == 'q') {
    return 0x10;
  }
  if (param_1 == 'r') {
    return 0x13;
  }
  if (param_1 == 's') {
    return 0x1f;
  }
  if (param_1 == 't') {
    return 0x14;
  }
  if (param_1 == 'u') {
    return 0x16;
  }
  if (param_1 == 'v') {
    return 0x2f;
  }
  if (param_1 == 'w') {
    return 0x11;
  }
  if (param_1 == 'x') {
    return 0x2d;
  }
  if (param_1 == 'y') {
    return 0x15;
  }
  if (param_1 == 'z') {
    return 0x2c;
  }
  if (param_1 == '0') {
    return 0xb;
  }
  if (param_1 == '1') {
    return 2;
  }
  if (param_1 == '2') {
    return 3;
  }
  if (param_1 == '3') {
    return 4;
  }
  if (param_1 == '4') {
    return 5;
  }
  if (param_1 != '5') {
    if (param_1 == '6') {
      return 7;
    }
    if (param_1 == '7') {
      return 8;
    }
    if (param_1 == '8') {
      return 9;
    }
    if (param_1 != '9') {
      if (param_1 == ' ') {
        return 0x39;
      }
      if (param_1 != '!') {
        if (param_1 != '@') {
          if (param_1 == '#') {
            uVar1 = 0x1c;
          }
          else {
            uVar1 = 0;
          }
          return uVar1;
        }
        return 0xe;
      }
      this[0x120] = (cKeyPad)0x1;
      return 0;
    }
    return 10;
  }
  return 6;
}
