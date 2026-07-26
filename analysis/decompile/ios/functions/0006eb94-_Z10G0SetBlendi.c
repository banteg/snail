/*
 * mangled: _Z10G0SetBlendi
 * demangled: G0SetBlend(int)
 * address: 0006eb94
 * size: 236
 */

/* G0SetBlend(int) */

void G0SetBlend(int param_1)

{
  if (param_1 != _gG0BlendMode) {
    _gG0BlendMode = param_1;
    switch(param_1) {
    case 0:
      _glDisable(0xbe2);
      _glDepthMask(1);
      return;
    case 1:
    case 7:
      _glBlendFunc(0x302,0x303);
      break;
    case 2:
      _glBlendFunc(0x302,0x303);
      _glEnable(0xbe2);
      _glDepthMask(0);
      return;
    case 3:
      _glBlendFunc(1,1);
      break;
    case 4:
    case 6:
      _glBlendFunc(0x302,0x300);
      _glEnable(0xbe2);
      _glDepthMask(0);
      return;
    case 5:
      _glBlendFunc(0x302,1);
      break;
    case 8:
      _glBlendFunc(0,0x303);
      break;
    case 9:
      _glBlendFunc(0x307,0x303);
      break;
    default:
      wprintf("Unknown BlendMode %i\n",param_1);
    }
    _glEnable(0xbe2);
    _glDepthMask(0);
    return;
  }
  return;
}
