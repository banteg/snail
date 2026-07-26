/*
 * mangled: _Z10G0SetBlendi
 * demangled: G0SetBlend(int)
 * address: 0008b6f0
 * size: 224
 */

/* G0SetBlend(int) */

void G0SetBlend(int param_1)

{
  if (param_1 == gG0BlendMode) {
    return;
  }
  gG0BlendMode = param_1;
  switch(param_1) {
  case 0:
    glDisable(0xbe2);
    glDepthMask(1);
    return;
  case 1:
    goto LAB_0008b748;
  case 2:
    goto LAB_0008b748;
  case 3:
    glBlendFunc(1,1);
    break;
  case 4:
    goto LAB_0008b768;
  case 5:
    goto LAB_0008b748;
  case 6:
LAB_0008b768:
    glBlendFunc(0x302,0x300);
    break;
  case 7:
LAB_0008b748:
    glBlendFunc(0x302,0x303);
    break;
  case 8:
    glBlendFunc(0,0x303);
    break;
  case 9:
    glBlendFunc(0x307,0x303);
    break;
  default:
    wprintf("Unknown BlendMode %i\n",param_1);
  }
  glEnable(0xbe2);
  glDepthMask(0);
  return;
}
