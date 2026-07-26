/*
 * mangled: _Z8G0Renderv
 * demangled: G0Render()
 * address: 0008ad84
 * size: 144
 */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* G0Render() */

void G0Render(void)

{
  if (*(int *)(Game + 0x328) == 0) {
    glViewport(0,0,(int)gG0DeviceScreenWidth,(int)gG0DeviceScreenHeight);
    glClearColor(0,0,0,0);
    glDepthMask(1);
    glClearDepthf(0x3f800000);
    glClear(0x4100);
  }
  cRGame::Render(Game);
  return;
}
