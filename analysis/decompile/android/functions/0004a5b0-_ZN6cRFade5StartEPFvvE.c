/*
 * mangled: _ZN6cRFade5StartEPFvvE
 * demangled: cRFade::Start(void (*)())
 * address: 0004a5b0
 * size: 24
 */

/* cRFade::Start(void (*)()) */

void __thiscall cRFade::Start(cRFade *this,_func_void *param_1)

{
  *(undefined4 *)(this + 4) = DAT_0004a5c8;
  *(_func_void **)(this + 0x10) = param_1;
  *(undefined4 *)this = 2;
  AI();
  return;
}
