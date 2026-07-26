/*
 * mangled: _ZN9cRObjects3AddEv
 * demangled: cRObjects::Add()
 * address: 0003053c
 * size: 88
 */

/* cRObjects::Add() */

cRObject * __thiscall cRObjects::Add(cRObjects *this)

{
  int iVar1;
  cRObject *this_00;

  iVar1 = *(int *)this;
  if (iVar1 == *(int *)(this + 4)) {
    RShellError((char *)(DAT_00030594 + 0x30558 + DAT_00030598));
    iVar1 = *(int *)this;
  }
  *(int *)this = iVar1 + 1;
  this_00 = (cRObject *)(*(int *)(this + 8) + iVar1 * 0x110);
  cRObject::Init(this_00);
  return this_00;
}
