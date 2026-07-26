/*
 * mangled: _ZN6cRFade5StartEPFvvE
 * demangled: cRFade::Start(void (*)())
 * address: 0004d588
 * size: 216
 */

/* WARNING: Removing unreachable block (ram,0x0004d5b0) */
/* WARNING: Removing unreachable block (ram,0x0004d5e8) */
/* WARNING: Removing unreachable block (ram,0x0004d604) */
/* cRFade::Start(void (*)()) */

void __thiscall cRFade::Start(cRFade *this,_func_void *param_1)

{
  undefined4 local_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;

  *(undefined4 *)this = 2;
  *(_func_void **)(this + 0x10) = param_1;
  *(undefined4 *)(this + 4) = 0;
  *(undefined4 *)(this + 4) = 0x3d638e39;
  tColour::tColour((tColour *)&local_1c,0.0,0.0,0.0,0.055555556);
  OSDPrint(3,0,0,0x44200000,0x43f00000,0x1000000,local_1c,uStack_18,uStack_14,uStack_10,9);
  return;
}
